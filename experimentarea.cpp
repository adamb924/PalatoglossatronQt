#include "experiment.h"
#include "experimentarea.h"
#include "mainwindow.h"
#include "subjectwidget.h"
#include "imagelistwidget.h"
#include "annotationwidget.h"
#include "imagewidget.h"
#include "palatronwidget.h"
#include "palateimagespecifier.h"

#include "subject.h"
#include "session.h"
#include "image.h"
#include "defaultsettings.h"
#include "displaysettingswidget.h"

#include <QDockWidget>
#include <QHBoxLayout>
#include <QtDebug>
#include <QKeyEvent>
#include <QList>
#include <QMdiSubWindow>
#include <QStatusBar>
#include <QLabel>
#include <QFileInfo>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QPushButton>
#include <QMessageBox>

#include <QSignalMapper>

ExperimentArea::ExperimentArea(QMainWindow *parent, Experiment *exp) :
	QMdiArea(parent)
{
    wnd = (MainWindow*)parent;
    experiment = exp;
    CreateDocks();
    CreateStatus();

    parent->setStatusBar(statusBar);

    nSubject = -1;
    nSession = -1;
    nTrace = -1;
    nPoint = -1;

// HACK -- maybe not; I think this is the only way to do it (4/27/2010)
    connect(this,SIGNAL(subWindowActivated(QMdiSubWindow*)),this,SLOT(subwindowActivated()));

}

ExperimentArea::~ExperimentArea()
{
    if(subjectsDock != 0 ) { delete subjectsDock; }
    if(displayDock != 0 ) { delete displayDock; }
    if(imagesDock != 0 ) { delete imagesDock; }
    if(annotationDock != 0 ) { delete annotationDock; }
    if(palateDock != 0 ) { delete palateDock; }
}

void ExperimentArea::CreateDocks()
{
    /////////////////////////////
    // Subjects Dock
    subjectsDock = new QDockWidget(tr("Subjects"),this);
    subjectsWidget = new SubjectWidget(this,experiment);
    subjectsDock->setWidget(subjectsWidget);
    subjectsDock->setFeatures(QDockWidget::DockWidgetFloatable);
    subjectsDock->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    wnd->addDockWidget(Qt::LeftDockWidgetArea,subjectsDock);

    connect(subjectsWidget,SIGNAL(sessionClicked(int,int)),this,SLOT(focusSession(int,int)));

    /////////////////////////////
    // Display Settings Dock
    displayDock = new QDockWidget(tr("Display Settings"),this);
    QWidget *displayWidget = new QWidget;
    QVBoxLayout *displayLayout = new QVBoxLayout;
    traceLinesVisible = new QCheckBox(tr("Trace Lines"));
    tracePointsVisible = new QCheckBox(tr("Trace Points"));
    pointsVisible = new QCheckBox(tr("Measurement Points"));
    palatronBoxesVisible = new QCheckBox(tr("Palatron Boxes Visible"));
    palatronDotsVisible = new QCheckBox(tr("Palatron Dots Visible"));
    gridVisible = new QCheckBox(tr("Grid visible"));
    QPushButton *adjustColorsAndLines = new QPushButton(tr("Adjust colors and line widths"));
    traceLinesVisible->setChecked(true);
    tracePointsVisible->setChecked(true);
    pointsVisible->setChecked(true);
    palatronBoxesVisible->setChecked(true);
    palatronDotsVisible->setChecked(true);
    gridVisible->setChecked(true);
    displayLayout->addWidget(traceLinesVisible);
    displayLayout->addWidget(tracePointsVisible);
    displayLayout->addWidget(pointsVisible);
    displayLayout->addWidget(palatronBoxesVisible);
    displayLayout->addWidget(palatronDotsVisible);
    displayLayout->addWidget(gridVisible);
    displayLayout->addWidget(adjustColorsAndLines);
    displayLayout->setSpacing(0);
    displayWidget->setLayout(displayLayout);
    displayDock->setWidget(displayWidget);
    displayDock->setFeatures(QDockWidget::DockWidgetFloatable);
    displayDock->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    wnd->addDockWidget(Qt::LeftDockWidgetArea,displayDock );
    displayDock->setEnabled(false);

    connect(traceLinesVisible,SIGNAL(toggled(bool)),this,SLOT(updateTraceLinesVisible(bool)));
    connect(tracePointsVisible,SIGNAL(toggled(bool)),this,SLOT(updateTracePointsVisible(bool)));
    connect(pointsVisible,SIGNAL(toggled(bool)),this,SLOT(updatePointsVisible(bool)));
    connect(palatronBoxesVisible,SIGNAL(toggled(bool)),this,SLOT(updatePalatronBoxesVisible(bool)));
    connect(palatronDotsVisible,SIGNAL(toggled(bool)),this,SLOT(updatePalatronDotsVisible(bool)));
    connect(gridVisible,SIGNAL(toggled(bool)),this,SLOT(updateGridVisible(bool)));
    connect(adjustColorsAndLines,SIGNAL(clicked()),this,SLOT(editDisplaySettings()));

    /////////////////////////////
    // Images Dock
    imagesDock = new QDockWidget(tr("Images"),this);
    imagesWidget = new ImageListWidget(this,experiment);
    imagesDock->setWidget(imagesWidget);
    imagesDock->setFeatures(QDockWidget::DockWidgetFloatable);
    wnd->addDockWidget(Qt::RightDockWidgetArea,imagesDock);
//    imagesDock->setEnabled(false);

    connect(imagesWidget,SIGNAL(imageClicked(int,int,int)),this,SLOT(selectImage(int,int,int)));
    connect(imagesWidget,SIGNAL(imageDoubleClicked(int,int,int)),this,SLOT(createImageWindow(int,int,int)));
    connect(imagesWidget, SIGNAL(interlacingChanged()), this, SLOT(interlacingChanged()));

    /////////////////////////////
    // Annotations Dock
    annotationDock = new QDockWidget(tr("Annotations"),this);
    annotationWidget = new AnnotationWidget(this,experiment);
    annotationDock->setWidget(annotationWidget);
    annotationDock->setFeatures(QDockWidget::DockWidgetFloatable);
    wnd->addDockWidget(Qt::RightDockWidgetArea,annotationDock);
    annotationDock->setEnabled(false);

    connect(annotationWidget,SIGNAL(defineGrid()),this,SLOT(defineGrid()));
    connect(annotationWidget,SIGNAL(updateGridLines(int)),this,SLOT(updateGridLines(int)));
    connect(annotationWidget,SIGNAL(sendGridToTracers()),this,SIGNAL(sendGridToTracers()));


    /////////////////////////////
    // Palatron Dock
    palateDock = new QDockWidget(tr("Palatron"),this);
    palatronWidget = new PalatronWidget(experiment,this);
    palateDock->setWidget(palatronWidget);
    palateDock->setFeatures(QDockWidget::DockWidgetFloatable);
    wnd->addDockWidget(Qt::RightDockWidgetArea,palateDock);

    // sync with the Palatron widget
    connect(subjectsWidget,SIGNAL(sessionClicked(int,int)),palatronWidget,SIGNAL(sessionChanged(int,int)));

    connect(palatronWidget,SIGNAL(defineBoxUL()),this,SLOT(defineBoxUL()));
    connect(palatronWidget,SIGNAL(defineBoxUR()),this,SLOT(defineBoxUR()));
    connect(palatronWidget,SIGNAL(defineBoxLL()),this,SLOT(defineBoxLL()));
    connect(palatronWidget,SIGNAL(defineBoxLR()),this,SLOT(defineBoxLR()));

    connect(palatronWidget,SIGNAL(manualDotUL(bool)),this,SLOT(definePointUL(bool)));
    connect(palatronWidget,SIGNAL(manualDotUR(bool)),this,SLOT(definePointUR(bool)));
    connect(palatronWidget,SIGNAL(manualDotLL(bool)),this,SLOT(definePointLL(bool)));
    connect(palatronWidget,SIGNAL(manualDotLR(bool)),this,SLOT(definePointLR(bool)));

    connect(palatronWidget,SIGNAL(dotColorChanged(QColor)),this,SLOT(dotColorChanged(QColor)));
    connect(palatronWidget,SIGNAL(toleranceChanged(int)),this,SLOT(toleranceChanged(int)));

    connect(palatronWidget,SIGNAL(pickColor()),this,SLOT(pickColor()));

    connect(palatronWidget,SIGNAL(viewChanged(int)),this,SLOT(updateView(int)));

    connect(palatronWidget,SIGNAL(selectPalateImages(int,int)),this,SLOT(selectPalateImages(int,int)));

    connect(palatronWidget,SIGNAL(palateClicked(int,int,int)),this,SLOT(selectPalate(int,int,int)));
    connect(palatronWidget,SIGNAL(palateDoubleClicked(int,int,int)),this,SLOT(createPalateWindow(int,int,int)));

    connect(palatronWidget,SIGNAL(drawThePalate(int,int)),this,SLOT(drawThePalate(int,int)));
    connect(palatronWidget,SIGNAL(refreshPalate()), this, SLOT(refreshPalate()));

    connect(palatronWidget,SIGNAL(updateSettingsOrPalateFrom()),this,SIGNAL(repaintAllImageWidgets()));
}

void ExperimentArea::CreateStatus()
{
//    statusCursorPosition
    statusBar = new QStatusBar;

    imageInvertedBox = new QCheckBox(tr("Negative"));
    statusBar->addPermanentWidget(imageInvertedBox);
    connect(imageInvertedBox,SIGNAL(toggled(bool)),this,SLOT(invertedImageAction(bool)));

    statusCursorPosition = new QLabel;
    statusBar->addPermanentWidget(statusCursorPosition);
    statusZoom = new QLabel("100%");
    statusBar->addPermanentWidget(statusZoom);
    statusColor = new QLabel;
    statusBar->addPermanentWidget(statusColor);

    statusCursorPosition->setMinimumWidth(45);
    statusColor->setMinimumWidth(60);
    statusZoom->setMinimumWidth(40);
}

void ExperimentArea::RefreshSubjectsDock()
{
    subjectsWidget->drawTree();
}

void ExperimentArea::RefreshImagesDock()
{
    imagesWidget->setSubjectSession(nSubject,nSession);
    imagesWidget->drawTree();
}

void ExperimentArea::RefreshAnnotationDock()
{
}

void ExperimentArea::RefreshPalateDock()
{
}

void ExperimentArea::focusSession(int subject, int session)
{
//    qDebug() << "focusSession";
    nSubject = subject;
    nSession = session;
    nTrace = -1;
    nPoint = -1;

    RefreshImagesDock();
}

void ExperimentArea::createImageWindow(int subject, int session, int image)
{
    focusSession(subject,session);

    if(nSubject==-1 || nSession==-1) { qDebug() << "Trying to run createImageWindow with a null nSubject or nSession"; return; }

    // refresh the annotation widget
    annotationWidget->setActive(true);
    RefreshAnnotationDock();

    ImageWidget *img = new ImageWidget(experiment,this);
    addSubWindow(img);

    // enable and disable docks
    checkDockStatus();

    img->setImage(nSubject,nSession,image);
    img->show();
    img->forceAppropriateSize();

    childWindowConnections(img);

    img->syncSignals();
    annotationWidget->syncSignals();
}

void ExperimentArea::createPalateWindow(int subject, int session, int image)
{
    focusSession(subject,session);

    if(nSubject==-1 || nSession==-1) { qDebug() << "Trying to run createImageWindow with a null nSubject or nSession"; return; }

    // refresh the annotation widget
    annotationWidget->setActive(true);
    RefreshAnnotationDock();

    ImageWidget *img = new ImageWidget(experiment,this);
    addSubWindow(img);

    // enable and disable docks
    checkDockStatus();

    img->setPalate(nSubject,nSession,image);
    img->show();
    img->forceAppropriateSize();

    childWindowConnections(img);

    img->syncSignals();
    annotationWidget->syncSignals();
}

void ExperimentArea::childWindowConnections(ImageWidget *img)
{
    connect(img,SIGNAL(destroyed()),this,SLOT(checkDockStatus()));

    // connect the image to the status bar update
    connect(img,SIGNAL(zoomLevelChanged(int)),this,SLOT(statusBarZoomUpdate(int)));
    connect(img,SIGNAL(cursorOverImageChanged(QPoint,QColor)),this,SLOT(statusBarCursorUpdate(QPoint,QColor)));
    connect(img,SIGNAL(statusMessage(QString)),statusBar,SLOT(showMessage(QString)));

    // and to annotation points
    connect(annotationWidget,SIGNAL(pointClicked(int)),img,SLOT(setEditPoint(int)));
    connect(annotationWidget,SIGNAL(traceClicked(int)),img,SLOT(setEditTrace(int)));

    // the annotation window knows when a different annotation is selected
    connect(img,SIGNAL(editPointChanged(int)),annotationWidget,SLOT(selectPoint(int)));
    connect(img,SIGNAL(editTraceChanged(int)),annotationWidget,SLOT(selectTrace(int)));

    // moving forward and backward in images
    connect(img,SIGNAL(imageChanged(int,int,int)),imagesWidget,SLOT(selectImage(int,int,int)));

    // sync the image window selection to this window
    connect(imagesWidget,SIGNAL(imageClicked(int,int,int)),this,SLOT(selectImage(int,int,int)));

    connect(img,SIGNAL(imageChanged(int,int,int)),subjectsWidget,SLOT(changeOfImage(int,int,int)));
    connect(img,SIGNAL(imageChanged(int,int,int)),palatronWidget,SLOT(changeOfImage(int,int,int)));

    connect(img,SIGNAL(colorPicked(QColor)),palatronWidget,SLOT(colorPicked(QColor)));

    // sync with the Palatron widget
    connect(img,SIGNAL(viewChanged(ImageWidget::DisplayMode)),palatronWidget,SLOT(changeView(ImageWidget::DisplayMode)));
    connect(palatronWidget,SIGNAL(dragTransformedView(bool)),this,SLOT(dragTransformedView(bool)));
    connect(palatronWidget,SIGNAL(selectFace()),this,SLOT(selectFace()));
    connect(palatronWidget,SIGNAL(resetPalateImages(int,int)),this,SLOT(resetPalate(int,int)));

    // sync with the display settings widget
    connect(img,SIGNAL(traceLinesVisibleChanged(bool)),traceLinesVisible,SLOT(setChecked(bool)));
    connect(img,SIGNAL(tracePointsVisibleChanged(bool)),tracePointsVisible,SLOT(setChecked(bool)));
    connect(img,SIGNAL(pointsVisibleChanged(bool)),pointsVisible,SLOT(setChecked(bool)));
    connect(img,SIGNAL(palatronBoxesVisibleChanged(bool)),palatronBoxesVisible,SLOT(setChecked(bool)));
    connect(img,SIGNAL(palatronDotsVisibleChanged(bool)),palatronDotsVisible,SLOT(setChecked(bool)));
    connect(img,SIGNAL(gridVisibleChanged(bool)),gridVisible,SLOT(setChecked(bool)));

    connect(this,SIGNAL(repaintAllImageWidgets()),img,SLOT(repaint()));

    // the grid updates
    connect(img,SIGNAL(sendGridToTracers()),this,SIGNAL(sendGridToTracers()));
}

void ExperimentArea::keyPressEvent ( QKeyEvent * event )
{
    switch(event->key())
    {
    case Qt::Key_Shift:
	shift=1;
	break;
    case Qt::Key_Control:
	ctrl=1;
	break;
    case Qt::Key_Alt:
	alt=1;
	break;
    }

}

void ExperimentArea::keyReleaseEvent ( QKeyEvent * event )
{
    switch(event->key())
    {
    case Qt::Key_Shift:
	shift=0;
	break;
    case Qt::Key_Control:
	ctrl=0;
	break;
    case Qt::Key_Alt:
	alt=0;
	break;
    }

    if( this->currentSubWindow() != 0 )
    {
	qobject_cast<ImageWidget*>(this->currentSubWindow()->widget())->receiveKeyEvent(event);
    }
}

void ExperimentArea::statusBarZoomUpdate(int zoomLevel)
{
    statusZoom->setText( QString::number(zoomLevel) + "%" );
}

void ExperimentArea::statusBarCursorUpdate(QPoint pos, QColor col)
{
    QString coordinates;
    if(pos.x()>-1 && pos.y()>-1)
	coordinates = QString::number(pos.x()) + ", " + QString::number(pos.y());
    else
	coordinates = "";
    statusCursorPosition->setText(coordinates);
    QString color;
    if(col.alpha()!=0)
	color = QString::number(col.red()) + "," + QString::number(col.green()) + "," + QString::number(col.blue());
    else
	color = "";
    statusColor->setText(color);
}

ImageWidget* ExperimentArea::activeImageWidget() const
{
    if( this->currentSubWindow() != 0 &&  this->currentSubWindow()->widget() != 0)
    {
	return qobject_cast<ImageWidget*>(this->currentSubWindow()->widget());
    }
    return 0;
}

void ExperimentArea::selectImage(int subject, int session, int image)
{
    if(activeImageWidget())
    {
	activeImageWidget()->setImage(subject,session,image);
    }
}

void ExperimentArea::selectPalate(int subject, int session, int image)
{
    if(activeImageWidget())
    {
	qDebug() << "here2";
	activeImageWidget()->setPalate(subject,session,image);
    }
}

void ExperimentArea::subwindowActivated()
{
    if(activeImageWidget())
    {
	activeImageWidget()->syncSignals();
    }
}

void ExperimentArea::defineBoxUR()
{
    if(activeImageWidget())
    {
	activeImageWidget()->defineBoxUR();
    }
}

void ExperimentArea::defineBoxLL()
{
    if(activeImageWidget())
    {
	activeImageWidget()->defineBoxLL();
    }
}

void ExperimentArea::defineBoxLR()
{
    if(activeImageWidget())
    {
	activeImageWidget()->defineBoxLR();
    }
}

void ExperimentArea::defineBoxUL()
{
    if(activeImageWidget())
    {
	activeImageWidget()->defineBoxUL();
    }
}

void ExperimentArea::definePointUL(bool toggle)
{
    if(activeImageWidget())
    {
	activeImageWidget()->definePointUL(toggle);
    }
}

void ExperimentArea::definePointUR(bool toggle)
{
    if(activeImageWidget())
    {
	activeImageWidget()->definePointUR(toggle);
    }
}

void ExperimentArea::definePointLL(bool toggle)
{
    if(activeImageWidget())
    {
	activeImageWidget()->definePointLL(toggle);
    }
}

void ExperimentArea::definePointLR(bool toggle)
{
    if(activeImageWidget())
    {
	activeImageWidget()->definePointLR(toggle);
    }
}

void ExperimentArea::dotColorChanged(QColor col)
{
    if(activeImageWidget())
    {
	activeImageWidget()->dotColorChanged(col);
    }
}

void ExperimentArea::toleranceChanged(int tol)
{
    if(activeImageWidget())
    {
	activeImageWidget()->toleranceChanged(tol);
    }
}

void ExperimentArea::showDotView(int show)
{
    if(activeImageWidget())
    {
	activeImageWidget()->showDotView(show);
    }
}

void ExperimentArea::pickColor()
{
    if(activeImageWidget())
    {
	activeImageWidget()->pickColor();
    }
}

void ExperimentArea::updateTraceLinesVisible(bool status)
{
    if(activeImageWidget())
    {
	activeImageWidget()->updateTraceLinesVisible(status);
    }
}

void ExperimentArea::updateTracePointsVisible(bool status)
{
    if(activeImageWidget())
    {
	activeImageWidget()->updateTracePointsVisible(status);
    }
}

void ExperimentArea::updatePointsVisible(bool status)
{
    if(activeImageWidget())
    {
	activeImageWidget()->updatePointsVisible(status);
    }
}

void ExperimentArea::updatePalatronBoxesVisible(bool status)
{
    if(activeImageWidget())
    {
	activeImageWidget()->updatePalatronBoxesVisible(status);
    }
}

void ExperimentArea::updatePalatronDotsVisible(bool status)
{
    if(activeImageWidget())
    {
	activeImageWidget()->updatePalatronDotsVisible(status);
    }
}

void ExperimentArea::updateGridVisible(bool status)
{
    if(activeImageWidget())
    {
	activeImageWidget()->updateGridVisible(status);
    }
}

void ExperimentArea::updateView(int mode)
{
    if(activeImageWidget())
    {
	activeImageWidget()->changeView(mode);
    }
}

void ExperimentArea::defineGrid()
{
    if(activeImageWidget())
    {
	activeImageWidget()->defineGrid();
    }
}

void ExperimentArea::updateGridLines(int lines)
{
    if(activeImageWidget())
    {
	activeImageWidget()->updateGridLines(lines);
    }
}

void ExperimentArea::selectPalateImages(int subject, int session)
{
    PalateImageSpecifier form(experiment->aSubjects.at(subject)->sessions()->at(session),this);
    if(form.exec() == QDialog::Accepted)
    {
	for(int i=0; i < experiment->aSubjects.at(subject)->sessions()->at(session)->images()->length(); i++)
	{
	    if( form.aCheckBoxes.at(i)->checkState() == Qt::Checked )
		experiment->aSubjects.at(subject)->sessions()->at(session)->images()->at(i)->setPalate( true );
	    else
		experiment->aSubjects.at(subject)->sessions()->at(session)->images()->at(i)->setPalate( false );
	}
    }
}

void ExperimentArea::editDisplaySettings()
{
    DisplaySettingsWidget *form = new DisplaySettingsWidget(experiment,this);

    connect(form,SIGNAL(updateParameters()),this,SIGNAL(repaintAllImageWidgets()));

    form->exec();
}

void ExperimentArea::dragTransformedView(bool drag)
{
    if(activeImageWidget())
    {
	activeImageWidget()->dragTransformedView(drag);
    }
}

void ExperimentArea::selectFace()
{
    if(activeImageWidget())
    {
	activeImageWidget()->selectFace();
    }
}

void ExperimentArea::checkDockStatus()
{
    if(subWindowList().length()>0)
    {
	if(displayDock)
	    displayDock->setEnabled(true);
	if(annotationDock)
	    annotationDock->setEnabled(true);
	if(palateDock)
	    qobject_cast<PalatronWidget*>(palateDock->widget())->setDotsTabEnabled(true);
    }
    else
    {
	if(displayDock)
	    displayDock->setEnabled(false);
	if(annotationDock)
	    annotationDock->setEnabled(false);
	if(palateDock)
	    qobject_cast<PalatronWidget*>(palateDock->widget())->setDotsTabEnabled(false);
    }
}

void ExperimentArea::setSubjectsDockVisible(bool visible)
{
    subjectsDock->setVisible(visible);
}

void ExperimentArea::setDisplayDockVisible(bool visible)
{
    displayDock->setVisible(visible);
}

void ExperimentArea::setImagesDockVisible(bool visible)
{
    imagesDock->setVisible(visible);
}

void ExperimentArea::setAnnotationsDockVisible(bool visible)
{
    annotationDock->setVisible(visible);
}

void ExperimentArea::setPalatronDockVisible(bool visible)
{
    palateDock->setVisible(visible);
}

void ExperimentArea::drawThePalate(int subject, int session)
{
//    qDebug() << "ExperimentArea::drawThePalate";
    if(subject == -1 || session == -1) { return; }
    if(activeImageWidget())
    {
	activeImageWidget()->drawThePalate(subject,session);
    }
    else
    {
	if( experiment->aSubjects.at(subject)->sessions()->at(session)->images()->length() < 1 )
	{
	    QMessageBox::critical(this,tr("PalatoglossatronQt Error"),tr("This is a quirk of the program: you have to have at least one regular tongue image in your session before you can define a palate."));
	}
	else
	{
	    this->createImageWindow(subject,session,0);
	    activeImageWidget()->drawThePalate(subject,session);
	}
    }
}

void ExperimentArea::resetPalate(int subject,int session)
{
    if(activeImageWidget())
    {
	activeImageWidget()->resetPalateImages(subject,session);
    }
}

void ExperimentArea::interlacingChanged()
{
    if(activeImageWidget())
    {
	activeImageWidget()->LoadImage();
    }
}

int ExperimentArea::currentTracing()
{
    return wnd->currentTracing();
}

QList<TrackingInterface*>* ExperimentArea::automaticTracers()
{
    return wnd->automaticTracers();
}

DisplayInterface* ExperimentArea::displayPlugin(int i)
{
    return wnd->displayPlugin(i);
}

void ExperimentArea::refreshPalate()
{
    if(activeImageWidget())
    {
	activeImageWidget()->refreshPalate();
    }
}

void ExperimentArea::addDisplayPlugin(QString str)
{
    palatronWidget->addDisplayPlugin(str);
}

void ExperimentArea::displayPluginSettingsUpdated()
{
    qDebug() << "displayPluginSettingsUpdated()";

    for(int i=0; i< this->subWindowList().count(); i++)
    {
	ImageWidget *tmp = qobject_cast<ImageWidget*>(this->subWindowList().at(i)->widget());
	if(tmp)
	{
	    tmp->updateIfPluginDislay();
	}
    }
}

QList<QPoint*>* ExperimentArea::currentTrace() const
{
    if(activeImageWidget())
    {
	return activeImageWidget()->currentTrace();
    }
    else
    {
//	return new QList<QPoint*>;
	return 0;
    }
}

void ExperimentArea::invertedImageAction(bool state)
{
    if(activeImageWidget())
    {
	activeImageWidget()->setInvertedImage(state);;
    }
}
