#include "palatronwidget.h"
#include "experiment.h"
#include "subject.h"
#include "session.h"
#include "image.h"
#include "imagewidget.h"
#include "dataentrywidget.h"

#include <QTabWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QIcon>
#include <QPushButton>
#include <QtDebug>
#include <QSlider>
#include <QLineEdit>
#include <QIntValidator>
#include <QSpinBox>
#include <QLabel>
#include <QColorDialog>
#include <QCheckBox>
#include <QComboBox>
#include <QFileDialog>
#include <QStringList>
#include <QFileInfo>
#include <QString>

PalatronWidget::PalatronWidget(Experiment *exp, QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout *fulllayout = new QVBoxLayout;
    this->setLayout(fulllayout);

    experiment = exp;
    session = 0;

    nSubject = -1;
    nSession = -1;

    // tabs
    tabWidget = new QTabWidget;
    QWidget *wDots, *wPalate, *wSessions, *wSettings;
    QVBoxLayout *sessionsLayout;
    QVBoxLayout *dotLayout;
    QVBoxLayout *palateLayout;
    QGridLayout *dotBoxesLayout;
    QVBoxLayout *settingsLayout;
    QGridLayout *manualDotBoxesLayout;
    QPushButton *bPickColor;
    QPushButton *bUL, *bUR, *bLL, *bLR;
//    int i;

    /////////////////////////////////////
    // Dots Tab
    dotLayout = new QVBoxLayout;

    wDots = new QWidget(0);
    wDots->setLayout(dotLayout);
    wPalate = new QWidget(0);

    dotBoxesLayout = new QGridLayout;
    bUL = new QPushButton(tr("UL"));
    dotBoxesLayout->addWidget(bUL,0,0);
    bUR = new QPushButton(tr("UR"));
    dotBoxesLayout->addWidget(bUR,0,1);
    bLL = new QPushButton(tr("LL"));
    dotBoxesLayout->addWidget(bLL,1,0);
    bLR = new QPushButton(tr("LR"));
    dotBoxesLayout->addWidget(bLR,1,1);
    dotLayout->addWidget(new QLabel(tr("Define box locations (<i>for this session</i>)")));
    dotLayout->addLayout(dotBoxesLayout);

    manualDotBoxesLayout = new QGridLayout;
    bManualUL = new QPushButton(tr("UL"));
    manualDotBoxesLayout->addWidget(bManualUL,0,0);
    bManualUR = new QPushButton(tr("UR"));
    manualDotBoxesLayout->addWidget(bManualUR,0,1);
    bManualLL = new QPushButton(tr("LL"));
    manualDotBoxesLayout->addWidget(bManualLL,1,0);
    bManualLR = new QPushButton(tr("LR"));
    manualDotBoxesLayout->addWidget(bManualLR,1,1);
    dotLayout->addWidget(new QLabel(tr("Manually define dot locations (<i>for this image</i>)")));
    dotLayout->addLayout(manualDotBoxesLayout);

    bManualUL->setCheckable(true);
    bManualUR->setCheckable(true);
    bManualLL->setCheckable(true);
    bManualLR->setCheckable(true);

    dotLayout->addStretch(1);

    tabWidget->addTab(wDots,"Dots");

    wDots->setEnabled(false);

    /////////////////////////////////////
    // Palate Tab
    wPalate = new QWidget;
    palateLayout = new QVBoxLayout;

    drawPalate = new QPushButton(tr("Draw the palate"));
    connect(drawPalate,SIGNAL(clicked()),this,SLOT(drawPalateClicked()));

    QPushButton *selectPalates = new QPushButton(tr("Add palate images"));
    connect(selectPalates,SIGNAL(clicked()),this,SLOT(choosePalateImages()));

    QComboBox *traceSelector = new QComboBox;
    traceSelector->addItems(*(experiment->getTraceInterpretations()));

    connect(traceSelector,SIGNAL(currentIndexChanged(int)),this,SIGNAL(selectTraceForPalates(int)));

    palateImagesWidget = new QTreeWidget;
    palateImagesWidget->setHeaderHidden(true);
    palateImagesWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    connect(palateImagesWidget,SIGNAL(itemSelectionChanged()),this,SLOT(palateSelectionChanged()));

    connect(palateImagesWidget,SIGNAL(itemSelectionChanged()),this,SLOT(selectionChanged()));
    connect(palateImagesWidget,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(activateItem()));

    QHBoxLayout *transparencyLayout = new QHBoxLayout;
    transparencySlider = new QSlider(Qt::Horizontal);
    transparencySpin = new QSpinBox;
    transparencySlider->setMinimum(0);
    transparencySlider->setMaximum(100);
    transparencySpin = new QSpinBox;
    transparencySpin->setRange(0,100);

    connect(transparencySpin,SIGNAL(valueChanged(int)),transparencySlider,SLOT(setValue(int)));
    connect(transparencySlider,SIGNAL(valueChanged(int)),transparencySpin,SLOT(setValue(int)));

    connect(transparencySlider,SIGNAL(valueChanged(int)),this,SLOT(changeTransparency(int)));

    transparencyLayout->addWidget(transparencySlider);
    transparencyLayout->addWidget(transparencySpin);

    removePalateImage = new QPushButton(tr("Remove image"));
    connect(removePalateImage,SIGNAL(clicked()),this,SLOT(removeImage()));

    palateLayout->addWidget(drawPalate);
    palateLayout->addWidget(selectPalates);
    palateLayout->addWidget(palateImagesWidget);
    palateLayout->addWidget(new QLabel(tr("Transparency")));
    palateLayout->addLayout(transparencyLayout);
    palateLayout->addWidget(removePalateImage);
    palateLayout->addStretch(1);


    wPalate->setLayout(palateLayout);
    tabWidget->addTab(wPalate,"Palate");

    /////////////////////////////////////
    // Settings Tab
    wSettings = new QWidget;
    settingsLayout = new QVBoxLayout;

    palatronSettingsButton = new QPushButton(tr("Settings for this session"));
    settingsLayout->addWidget(palatronSettingsButton);
    connect(palatronSettingsButton,SIGNAL(clicked()),this,SLOT(launchPalatronSettingsDialog()));

    QHBoxLayout *colorLayout = new QHBoxLayout;
    dotColorButton = new QPushButton(iconFromColor(QColor("white")),"Dot Color");
    bPickColor = new QPushButton(tr("Pick"));
    colorLayout->addWidget(dotColorButton,1);
    colorLayout->addWidget(bPickColor,0);
    connect(dotColorButton,SIGNAL(clicked()),this,SLOT(defineDotColor()));
    connect(bPickColor,SIGNAL(clicked()),this,SIGNAL(pickColor()));
    settingsLayout->addLayout(colorLayout);

    QHBoxLayout *toleranceLayout = new QHBoxLayout;
    toleranceSlider = new QSlider(Qt::Horizontal);
    toleranceSlider->setMinimum(experiment->ds->colorToleranceMinimum);
    toleranceSlider->setMaximum(experiment->ds->colorToleranceMaximum);
    toleranceSpin = new QSpinBox;
    toleranceSpin->setRange(experiment->ds->colorToleranceMinimum,experiment->ds->colorToleranceMaximum); // is this right?

    connect(toleranceSpin,SIGNAL(valueChanged(int)),toleranceSlider,SLOT(setValue(int)));
    connect(toleranceSlider,SIGNAL(valueChanged(int)),toleranceSpin,SLOT(setValue(int)));
    connect(toleranceSlider,SIGNAL(valueChanged(int)),this,SLOT(changeTolerance(int)));

    toleranceLayout->addWidget(toleranceSlider);
    toleranceLayout->addWidget(toleranceSpin);
    settingsLayout->addWidget(new QLabel(tr("Color Tolerance")));
    settingsLayout->addLayout(toleranceLayout);

    QPushButton *dragTraces = new QPushButton(tr("Drag traces around"));
    dragTraces->setCheckable(true);
    connect(dragTraces,SIGNAL(clicked(bool)),this,SIGNAL(dragTransformedView(bool)));

    QPushButton *selectFace = new QPushButton(tr("Set where the face is"));
    connect(selectFace,SIGNAL(clicked()),this,SIGNAL(selectFace()));

    settingsLayout->addWidget(dragTraces);
    settingsLayout->addWidget(selectFace);
    settingsLayout->addStretch(1);

    wSettings->setLayout(settingsLayout);
    tabWidget->addTab(wSettings,"Settings");

    /////////////////////////////////////
    // Sessions Tab
    wSessions = new QWidget;
    sessionsLayout = new QVBoxLayout;
    wSessions->setLayout(sessionsLayout);


    sessionsLayout->addWidget(new QLabel(tr("Current Session:")));
    sessionLabel = new QLabel(tr("<i>No session selected.</i>"));
    sessionsLayout->addWidget(sessionLabel);

    copyFromSession = new QComboBox;
    sessionsLayout->addWidget(new QLabel(tr("Use Palatron settings from:")));
    sessionsLayout->addWidget(copyFromSession);

    palateFromSession = new QComboBox;
    sessionsLayout->addWidget(new QLabel(tr("Use Palate from:")));
    sessionsLayout->addWidget(palateFromSession);

    sessionsLayout->addStretch(1);

    tabWidget->addTab(wSessions,"Sessions");

//    tabWidget->setEnabled(true);

    //////////////////
    // View Combo Box
    viewMode = new QComboBox;
    viewMode->addItem(tr("Untransformed"),ImageWidget::Untransformed);
    viewMode->addItem(tr("Dot View"),ImageWidget::Dot_View);
    viewMode->addItem(tr("Composite Dot View"),ImageWidget::Composite_Dot_View);
    viewMode->addItem(tr("Transformed - Lines only"),ImageWidget::TransformedAbstract);
    viewMode->addItem(tr("Transformed - Images"),ImageWidget::TransformedTraditional);
    viewMode->insertSeparator(viewMode->count());

    connect(viewMode,SIGNAL(currentIndexChanged(int)),this,SLOT(viewComboChanged(int)));

    fulllayout->addWidget(viewMode);
    fulllayout->addWidget(tabWidget);
//    delete this->layout();

    connect(this,SIGNAL(sessionChanged(int,int)),this,SLOT(updateSession(int,int)));
    connect(this,SIGNAL(sessionChanged(int,int)),this,SLOT(populatePalateImages()));

    connect(copyFromSession,SIGNAL(currentIndexChanged(int)),this,SLOT(selectCopyFromSession(int)));
    connect(palateFromSession,SIGNAL(currentIndexChanged(int)),this,SLOT(selectPalateFromSession(int)));


    connect(bUL,SIGNAL(clicked()),this,SIGNAL(defineBoxUL()));
    connect(bUR,SIGNAL(clicked()),this,SIGNAL(defineBoxUR()));
    connect(bLL,SIGNAL(clicked()),this,SIGNAL(defineBoxLL()));
    connect(bLR,SIGNAL(clicked()),this,SIGNAL(defineBoxLR()));

    connect(bManualUL,SIGNAL(toggled(bool)),this,SIGNAL(manualDotUL(bool)));
    connect(bManualUR,SIGNAL(toggled(bool)),this,SIGNAL(manualDotUR(bool)));
    connect(bManualLL,SIGNAL(toggled(bool)),this,SIGNAL(manualDotLL(bool)));
    connect(bManualLR,SIGNAL(toggled(bool)),this,SIGNAL(manualDotLR(bool)));

    populatePalateImages();
    palateSelectionChanged();
//    connect(dotView,SIGNAL(stateChanged(int)),this,SIGNAL(showDotView(int)));
}

void PalatronWidget::defineDotColor()
{
    QColorDialog dlg(session->dotColor());
    if(dlg.exec() == QDialog::Accepted)
    {
	session->setDotColor(dlg.currentColor());
	dotColorButton->setIcon(iconFromColor(session->dotColor()));
	emit dotColorChanged(session->dotColor());
    }
}

QIcon PalatronWidget::iconFromColor(QColor col)
{
    QPixmap pm(16,16);
    pm.fill(col);
    return QIcon(pm);
}

void PalatronWidget::updateSession(int subj, int sess)
{
//    qDebug() << "updateSession";
    if(!experiment->validSession(subj,sess)) {  tabWidget->setEnabled(false); return; }

    session = experiment->aSubjects.at(subj)->sessions()->at(sess);

    tabWidget->setEnabled(true);
    QString str = "<b>" + experiment->aSubjects.at(subj)->name() + ", " + session->name() + "</b>";
    sessionLabel->setText(str);

    nSubject = subj;
    nSession = sess;

    toleranceSlider->setValue(experiment->aSubjects.at(subj)->sessions()->at(sess)->tolerance());
    toleranceSpin->setValue(experiment->aSubjects.at(subj)->sessions()->at(sess)->tolerance());
    dotColorButton->setIcon(iconFromColor(experiment->aSubjects.at(subj)->sessions()->at(sess)->dotColor()));

    populateCopyFromSession();
    populatePalateFromSession();

//    qDebug() << "setCurrentIndex" << experiment->aSubjects.at(nSubject)->sessions()->at(nSession)->palatronSettingsFromSession()+1;
    copyFromSession->setCurrentIndex(experiment->aSubjects.at(nSubject)->sessions()->at(nSession)->palatronSettingsFromSession()+1);
//    qDebug() << "setCurrentIndex" << experiment->aSubjects.at(nSubject)->sessions()->at(nSession)->palateFromSession()+1;
    palateFromSession->setCurrentIndex(experiment->aSubjects.at(nSubject)->sessions()->at(nSession)->palateFromSession()+1);
    //    qDebug() << "updateSession";
}

void PalatronWidget::populateCopyFromSession()
{
//    qDebug() << "populateCopyFromSession";
    if( !experiment->validSession(nSubject,nSession) )
    {
	copyFromSession->setEnabled(false);
    }
    else
    {
	copyFromSession->setEnabled(true);
    }

    copyFromSession->clear();
    copyFromSession->addItem(tr("--None--"),-1);
    for(int i=0; i< experiment->aSubjects.at(nSubject)->sessions()->length(); i++)
    {
	copyFromSession->addItem(experiment->aSubjects.at(nSubject)->sessions()->at(i)->name(),i);
    }
}

void PalatronWidget::populatePalateFromSession()
{
//    qDebug() << "populatePalateFromSession";
    if( !experiment->validSession(nSubject,nSession) )
    {
	palateFromSession->setEnabled(false);
    }
    else
    {
	palateFromSession->setEnabled(true);
    }

    palateFromSession->clear();
    palateFromSession->addItem(tr("--None--"),-1);
    for(int i=0; i< experiment->aSubjects.at(nSubject)->sessions()->length(); i++)
    {
	palateFromSession->addItem(experiment->aSubjects.at(nSubject)->sessions()->at(i)->name(),i);
    }
}

void PalatronWidget::selectCopyFromSession(int index)
{
    if(copyFromSession->count()<2) { return; } // needs to have more than just the first one
//    qDebug() << "PalatronWidget::selectCopyFromSession" << index;
    index--;
    if(index != nSession)
    {
	experiment->aSubjects.at(nSubject)->sessions()->at(nSession)->setPalatronSettingsFromSession(index);
    }
    emit updateSettingsOrPalateFrom();
}

void PalatronWidget::selectPalateFromSession(int index)
{
    if(palateFromSession->count()<2) { return; }
    index--;
    if(index != nSession)
    {
	experiment->aSubjects.at(nSubject)->sessions()->at(nSession)->setPalateFromSession(index);
    }
    emit updateSettingsOrPalateFrom();
}

void PalatronWidget::changeOfImage(int subj, int sess, int image)
{
    updateSession(subj,sess);

    Image *img = session->images()->at(image);

    if(img->mul()) { bManualUL->setChecked(true); } else { bManualUL->setChecked(false); }
    if(img->mur()) { bManualUR->setChecked(true); } else { bManualUR->setChecked(false); }
    if(img->mll()) { bManualLL->setChecked(true); } else { bManualLL->setChecked(false); }
    if(img->mlr()) { bManualLR->setChecked(true); } else { bManualLR->setChecked(false); }
}

void PalatronWidget::colorPicked(QColor col)
{
    session->setDotColor(col);
    dotColorButton->setIcon(iconFromColor(session->dotColor()));
    emit dotColorChanged(session->dotColor());
}

void PalatronWidget::changeTolerance(int tol)
{
    session->setTolerance(tol);
    emit toleranceChanged(tol);
}

void PalatronWidget::changeView(ImageWidget::DisplayMode mode)
{
    for(int i=0; i<viewMode->count(); i++)
    {
	if(viewMode->itemData(i)==mode)
	{
	    viewMode->setCurrentIndex(i);
	    return;
	}
    }
}

void PalatronWidget::viewComboChanged(int index)
{
    emit viewChanged(viewMode->itemData(index).toInt());
}

void PalatronWidget::choosePalateImages()
{
//    emit selectPalateImages(nSubject,nSession);
    QStringList fileNames;
    fileNames= QFileDialog::getOpenFileNames(this, tr("Open Image"), "", tr("All Supported Image  Files (*.bmp *.gif *.jpg *.jpeg *.png *.pbm *.pgm *.ppm *.tif *.tiff *.xbm *.xpm)"));
    for(int i=0; i<fileNames.length(); i++)
    {
//	qDebug() << fileNames.at(i);
	*(experiment->aSubjects.at(nSubject)->sessions()->at(nSession)->palateImages()) << new Image(fileNames.at(i),experiment->aSubjects.at(nSubject)->sessions()->at(nSession));
	*(session->palateTransparencies()) << experiment->ds->defaultPalateTransparency;
    }
    populatePalateImages();
    emit resetPalateImages(nSubject, nSession);
}

void PalatronWidget::populatePalateImages()
{
    if(session == 0) { return; }

    palateImagesWidget->clear();

    if(session->palateImages()->length()==0)
    {
	palateImagesWidget->setEnabled(false);
	// a convenience call
	drawPalate->setEnabled(false);
	return;
    }
    else
    {
	palateImagesWidget->setEnabled(true);
	// a convenience call
	drawPalate->setEnabled(true);
    }

    int i;
    QFileInfo f;
    for(i=0; i<session->palateImages()->length(); i++)
    {
	f = QFileInfo(session->palateImages()->at(i)->filename());
	palateImagesWidget->addTopLevelItem(new QTreeWidgetItem(QStringList(f.completeBaseName())));
    }
}

int PalatronWidget::selectedPalateImage()
{
    int i;
    for(i=0; i< palateImagesWidget->topLevelItemCount(); i++)
    {
	if(palateImagesWidget->topLevelItem(i)->isSelected())
	{
	    return i;
	}
    }
    return -1;
}

void PalatronWidget::palateSelectionChanged()
{
    int selection = selectedPalateImage();
    if(selection==-1)
    {
	transparencySlider->setEnabled(false);
	transparencySpin->setEnabled(false);
	removePalateImage->setEnabled(false);
	return;
    }
    else
    {
	transparencySlider->setEnabled(true);
	transparencySpin->setEnabled(true);
	removePalateImage->setEnabled(true);
    }
    transparencySlider->setValue(session->palateTransparencies()->at(selection));
}

void PalatronWidget::removeImage()
{
    session->palateTransparencies()->removeAt(selectedPalateImage());
    session->palateImages()->removeAt(selectedPalateImage());
    populatePalateImages();
    emit resetPalateImages(nSubject, nSession);
}

void PalatronWidget::changeTransparency(int tol)
{
    session->palateTransparencies()->replace(selectedPalateImage(),tol);
    emit refreshPalate();
}

void PalatronWidget::drawPalateClicked()
{
    emit drawThePalate(nSubject, nSession);
}

void PalatronWidget::setDotsTabEnabled(bool enabled)
{
    tabWidget->widget(0)->setEnabled(enabled);
}

void PalatronWidget::setPalateTabEnabled(bool enabled)
{
    tabWidget->widget(1)->setEnabled(enabled);
}

void PalatronWidget::setSettingsTabEnabled(bool enabled)
{
    tabWidget->widget(2)->setEnabled(enabled);
}

void PalatronWidget::setSessionsTabEnabled(bool enabled)
{
    tabWidget->widget(3)->setEnabled(enabled);
}

void PalatronWidget::activateItem()
{
    int img = selectedPalateImage();
    if(img!=-1)
    {
	emit palateDoubleClicked(nSubject,nSession,img);
    }
}

void PalatronWidget::selectionChanged()
{
    int img = selectedPalateImage();
    if(img!=-1)
    {
	emit palateClicked(nSubject,nSession,img);
    }
}

void PalatronWidget::addDisplayPlugin(QString str)
{
    if(viewMode->itemData(viewMode->count()-1).toInt() < 1000)
    {
	viewMode->addItem(str,1000);
    }
    else
    {
	viewMode->addItem(str,viewMode->itemData(viewMode->count()-1).toInt() + 1);
    }
}

void PalatronWidget::launchPalatronSettingsDialog()
{
    qDebug() << "Launch";

    QStringList names, values;
    names << "OverlayX" << "OverlayY" << "Angle" << "UsScale" << "tranlrmm" << "ortranrmm" << "ortranlmm" << "usoriginx" << "usoriginy" << "vertical_distortion_correction" << "horizontal_distortion_correction" << "faceLocation";
    values << QString::number(session->palatronSettings.OverlayX) << QString::number(session->palatronSettings.OverlayY) << QString::number(session->palatronSettings.Angle) << QString::number(session->palatronSettings.UsScale) << QString::number(session->palatronSettings.tranlrmm) << QString::number(session->palatronSettings.ortranrmm) << QString::number(session->palatronSettings.ortranlmm) << QString::number(session->palatronSettings.usoriginx) << QString::number(session->palatronSettings.usoriginy) << QString::number(session->palatronSettings.vertical_distortion_correction) << QString::number(session->palatronSettings.horizontal_distortion_correction) << QString::number(session->palatronSettings.faceLocation);

    DataEntryWidget *form = new DataEntryWidget(&names,&values,"",0);
    if( form->exec() == QDialog::Accepted)
    {
	session->palatronSettings.OverlayX = values.at(0).toShort();
	session->palatronSettings.OverlayY = values.at(1).toShort();
	session->palatronSettings.Angle = values.at(2).toDouble();
	session->palatronSettings.UsScale = values.at(3).toDouble();
	session->palatronSettings.tranlrmm = values.at(4).toDouble();
	session->palatronSettings.ortranrmm = values.at(5).toDouble();
	session->palatronSettings.ortranlmm = values.at(6).toDouble();
	session->palatronSettings.usoriginx = values.at(7).toDouble();
	session->palatronSettings.usoriginy = values.at(8).toDouble();
	session->palatronSettings.vertical_distortion_correction = values.at(9).toDouble();
	session->palatronSettings.horizontal_distortion_correction = values.at(10).toDouble();
	session->palatronSettings.faceLocation = values.at(11).toInt();
/*
	short OverlayX, OverlayY;
	double Angle, UsScale,tranlrmm,ortranrmm,ortranlmm;
	double usoriginx, usoriginy;
	double vertical_distortion_correction, horizontal_distortion_correction;
	int faceLocation;
*/
    }
}
