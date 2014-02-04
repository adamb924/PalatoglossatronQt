#include "imagelistwidget.h"
#include "experiment.h"
#include "subject.h"
#include "session.h"
#include "treeitem.h"
#include "image.h"

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>
#include <QtDebug>
#include <QFileInfo>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>

ImageListWidget::ImageListWidget(QWidget *parent, Experiment *exp, int subject, int session) :
    QWidget(parent)
{
    QVBoxLayout *vlayout = new QVBoxLayout;
    QHBoxLayout *hlayout = new QHBoxLayout;
    tree = new QTreeWidget;
    tree->setHeaderHidden(true);
    tree->setSelectionMode(QAbstractItemView::ExtendedSelection);

    tree->setColumnCount(2);
    tree->setSelectionBehavior(QAbstractItemView::SelectRows);

    experiment = exp;

    nSubject = subject;
    nSession = session;
    nImage = -1;

    none = tr("None");
    even = tr("Even");
    odd = tr("Odd");

    subjectLabel = new QLabel(tr("<b><i>No subject selected</i></b>"));
    sessionLabel = new QLabel(tr("<i>No session selected</i>"));

    bAddImages = new QPushButton(tr("Add Images"));
    bRemoveImages = new QPushButton(tr("Remove Images"));
    hlayout->addWidget(bAddImages);
    hlayout->addWidget(bRemoveImages);
    bAddImages->setEnabled(false);
    bRemoveImages->setEnabled(false);

    vlayout->addWidget(subjectLabel);
    vlayout->addWidget(sessionLabel);
    vlayout->addWidget(tree);
    vlayout->addLayout(hlayout);


    subjectLabel->setEnabled(true);
    sessionLabel->setEnabled(true);

    this->setLayout(vlayout);

    connect(tree,SIGNAL(itemSelectionChanged()),this,SLOT(selectionChanged()));
    connect(tree,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(doubleClick(QTreeWidgetItem*,int)));

    connect(bAddImages,SIGNAL(clicked()),this,SLOT(addImages()));
    connect(bRemoveImages,SIGNAL(clicked()),this,SLOT(removeImages()));

    drawTree();
}

void ImageListWidget::drawTree()
{
    int i;
    QFileInfo f;

    tree->clear();
    imageWidgets.clear();

    if(nSubject==-1 || nSession==-1)
    {
	tree->setEnabled(false);
	return;
    }
    tree->setEnabled(true);
    bAddImages->setEnabled(true);

    subjectLabel->setText("<b>"+experiment->aSubjects.at(nSubject)->name()+"</b>");
    sessionLabel->setText(experiment->aSubjects.at(nSubject)->sessions()->at(nSession)->name());

    for(i=0; i < experiment->aSubjects.at(nSubject)->sessions()->at(nSession)->images()->length(); i++)
    {
	imageWidgets << new TreeItem(tree,TreeItem::Image,nSubject,nSession,i);
	f = QFileInfo(experiment->aSubjects.at(nSubject)->sessions()->at(nSession)->images()->at(i)->filename());
	imageWidgets.last()->setText(0, f.completeBaseName());

	switch( experiment->aSubjects.at(nSubject)->sessions()->at(nSession)->images()->at(i)->interlacing() )
	{
	case Image::EvenRows:
	    imageWidgets.last()->setText(1, even);
	    break;
	case Image::OddRows:
	    imageWidgets.last()->setText(1, odd);
	    break;
	default:
	    imageWidgets.last()->setText(1, none);
	    break;
	}

	tree->addTopLevelItem(imageWidgets.last());
    }
}

void ImageListWidget::activateItem()
{
//    qDebug() << "double-click";
    TreeItem *curr;
    curr = (TreeItem*)tree->currentItem();

    if(curr->type() != TreeItem::Image)
    {
	qDebug() << "Somehow the ImageListWidget has a non-image type item.";
	return;
    }

    nImage = curr->image;

    emit imageDoubleClicked(nSubject,nSession,nImage);
}

QSize ImageListWidget::sizeHint() const
{
    return QSize(225,300);
}

void ImageListWidget::setSubjectSession(int subject, int session)
{
    nSubject = subject;
    nSession = session;
}

void ImageListWidget::selectImage(int subject, int session, int index)
{
    if(subject==-1 || session==-1 || index==-1) { return; }

    if(subject != nSubject || session != nSession)
    {
	nSubject = subject;
	nSession = session;
	drawTree();
    }

    nImage = index;

    if( index>-1 && index < imageWidgets.length() )
    {
	if( nSubject != subject || nSession != session || nImage != index)
	{
	    tree->setCurrentItem(imageWidgets.at(index));
	}
    }
}

void ImageListWidget::addImages()
{
    QStringList fileNames;
    fileNames= QFileDialog::getOpenFileNames(this, tr("Open Image"), "", tr("All Supported Image  Files (*.bmp *.gif *.jpg *.jpeg *.png *.pbm *.pgm *.ppm *.tif *.tiff *.xbm *.xpm)"));
    for(int i=0; i<fileNames.length(); i++)
    {
	*(experiment->aSubjects.at(nSubject)->sessions()->at(nSession)->images()) << new Image(fileNames.at(i),experiment->getTraceInterpretations()->length(),experiment->getPointInterpretations()->length(),experiment->aSubjects.at(nSubject)->sessions()->at(nSession));
    }
    drawTree();
}

void ImageListWidget::removeImages()
{
    int i;
    QList<int> toDelete;
    for(i=0; i < tree->selectedItems().length(); i++)
    {
	toDelete << ((TreeItem*)tree->selectedItems().at(i))->image;
    }

    qSort(toDelete.begin(), toDelete.end());

    for(i= toDelete.length()-1; i >= 0; i--)
    {
	experiment->aSubjects.at(nSubject)->sessions()->at(nSession)->images()->removeAt(toDelete.at(i));
    }
    drawTree();
}

void ImageListWidget::selectionChanged()
{
//    qDebug() << "click";

    if(tree->selectedItems().length()>0)
    {
	bRemoveImages->setEnabled(true);
    }
    else
    {
	bRemoveImages->setEnabled(false);
    }

    TreeItem *curr;
    curr = (TreeItem*)tree->currentItem();

    if(curr->type() != TreeItem::Image)
    {
	qDebug() << "Somehow the ImageListWidget has a non-image type item.";
	return;
    }

    nImage = curr->image;

// DISABLE CLICK
//    emit imageClicked(nSubject,nSession,nImage);
}

void ImageListWidget::doubleClick( QTreeWidgetItem * item, int column )
{
    if(column == 0)
    {
	activateItem();
    }
    else if(column == 1)
    {
	int index = imageWidgets.indexOf(item);
	if(index == -1) { return; }

	switch( experiment->aSubjects.at(nSubject)->sessions()->at(nSession)->images()->at(index)->interlacing() )
	{
	case Image::EvenRows:
	    experiment->aSubjects.at(nSubject)->sessions()->at(nSession)->images()->at(index)->setInterlacing(Image::OddRows);
	    item->setText(1,odd);
	    break;
	case Image::OddRows:
	    experiment->aSubjects.at(nSubject)->sessions()->at(nSession)->images()->at(index)->setInterlacing(Image::NoInterlacing);
	    item->setText(1,none);
	    break;
	default:
	    experiment->aSubjects.at(nSubject)->sessions()->at(nSession)->images()->at(index)->setInterlacing(Image::EvenRows);
	    item->setText(1,even);
	    break;
	}
	emit interlacingChanged();
    }
}
