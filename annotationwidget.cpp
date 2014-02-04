#include "annotationwidget.h"
#include "experiment.h"
#include "subject.h"
#include "session.h"
#include "treeitem.h"
#include "image.h"
#include "defaultsettings.h"

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>
#include <QtDebug>
#include <QFileInfo>
#include <QCheckBox>
#include <QTabWidget>
#include <QPushButton>
#include <QSlider>
#include <QSpinBox>
#include <QLabel>
#include <QMessageBox>

AnnotationWidget::AnnotationWidget(QWidget *parent, Experiment *exp, int subject, int session) :
    QWidget(parent)
{
    experiment = exp;

    tabWidget = new QTabWidget;
    QVBoxLayout *fulllayout = new QVBoxLayout;
    QWidget *annotationListWidget, *gridWidget;
    annotationListWidget = new QWidget;
    gridWidget = new QWidget;

    QVBoxLayout *vlayout = new QVBoxLayout;
    tree = new QTreeWidget;
    tree->setHeaderHidden(true);
    tree->setColumnCount(3);
    tree->setSelectionBehavior(QAbstractItemView::SelectRows);
    experiment = exp;

    vlayout->addWidget(tree);

    video = tr("Vid");
    ultrasound = tr("Ult");

    free = tr("Free");
    grid = tr("Grid");

    annotationListWidget->setLayout(vlayout);

//    this->setLayout(vlayout);

    connect(tree,SIGNAL(itemSelectionChanged()),this,SLOT(activateItem()));
    connect(tree,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(doubleClick(QTreeWidgetItem*,int)));

    active=0;
    drawTree();

    QVBoxLayout *gridlayout = new QVBoxLayout;

    QPushButton *defineGrid = new QPushButton(tr("Define Radial Grid"));

    QHBoxLayout *linesLayout = new QHBoxLayout;
    QSlider *gridLines = new QSlider(Qt::Horizontal);
    gridLines->setRange(0,experiment->ds->nMaxGridLines);
    gridLines->setValue(experiment->ds->nGridLines);
    QSpinBox *spinGridLines = new QSpinBox;
    spinGridLines->setRange(0,experiment->ds->nMaxGridLines);
    spinGridLines->setValue(experiment->fanLines());
    linesLayout->addWidget(gridLines);
    linesLayout->addWidget(spinGridLines);

    connect(spinGridLines,SIGNAL(valueChanged(int)),gridLines,SLOT(setValue(int)));
    connect(gridLines,SIGNAL(valueChanged(int)),spinGridLines,SLOT(setValue(int)));

    gridlayout->addWidget(defineGrid);
    gridlayout->addWidget(new QLabel(tr("Number of intermediate lines")));
    QLabel *lineWarning = new QLabel(tr("<i>Warning: Changing this will wreak havoc on your traces if you attempt to modify them, although the existing data will not be lost. If you botch it and then go back to the old number, all will be well. (So write it down.)</i>"));
    lineWarning->setWordWrap(true);
    gridlayout->addLayout(linesLayout);
    gridlayout->addWidget(lineWarning);

    gridWidget->setLayout(gridlayout);

    // to the outside world
    connect(gridLines,SIGNAL(valueChanged(int)),this,SIGNAL(updateGridLines(int)));
    connect(gridLines,SIGNAL(valueChanged(int)),this,SIGNAL(sendGridToTracers())); // is this actually connected to anything?
    connect(defineGrid,SIGNAL(clicked()),this,SIGNAL(defineGrid()));

    tabWidget->addTab(annotationListWidget,tr("Annotations"));
    tabWidget->addTab(gridWidget,tr("Grid"));

    fulllayout->addWidget(tabWidget);
    this->setLayout(fulllayout);
}

void AnnotationWidget::drawTree()
{
    if(!active)
    {
	tree->setEnabled(false);
//	return;
    }
    tree->setEnabled(true);

//    QList<QTreeWidgetItem*> traceWidgets;
//    QList<QTreeWidgetItem*> pointWidgets;

    int i;
    TreeItem *it;

    tree->clear();
    traceWidgets.empty();
    pointWidgets.empty();

    it = new TreeItem(tree,TreeItem::Null);
    it->setText(0, tr("Traces") );
    tree->addTopLevelItem(it);
    it->setExpanded(true);

    // trace interpretations
    for(i=0; i < experiment->getTraceInterpretations()->length(); i++)
    {
	traceWidgets << new TreeItem(it,TreeItem::Trace,i); // so i is placed in subitem->subject
	traceWidgets.last()->setText(0, experiment->getTraceInterpretations()->at(i) );
	switch( experiment->getTraceLocations()->at(i) )
	{
	 case Experiment::Video:
	    traceWidgets.last()->setText(1, video);
	    break;
	 case Experiment::Ultrasound:
	    traceWidgets.last()->setText(1, ultrasound);
	    break;
	 default:
	    break;
	}
	switch( experiment->getTraceTypes()->at(i) )
	{
	 case Experiment::Free:
	    traceWidgets.last()->setText(2, free);
	    break;
	 case Experiment::Grid:
	    traceWidgets.last()->setText(2, grid);
	    break;
	 default:
	    break;
	}
	it->addChild(traceWidgets.last());
    }

    it = new TreeItem(tree,TreeItem::Image);
    it->setText(0, tr("Points") );
    tree->addTopLevelItem(it);
    it->setExpanded(true);

    // point interpretations
    for(i=0; i < experiment->getPointInterpretations()->length(); i++)
    {
	pointWidgets << new TreeItem(it,TreeItem::Point,i); // so i is placed in subitem->subject
	pointWidgets.last()->setText(0, experiment->getPointInterpretations()->at(i) );
	switch( experiment->getPointLocations()->at(i) )
	{
	 case Experiment::Video:
	    pointWidgets.last()->setText(1, video);
	    break;
	 case Experiment::Ultrasound:
	    pointWidgets.last()->setText(1, ultrasound);
	    break;
	 default:
	    break;
	}
	it->addChild(pointWidgets.last());
    }

    tree->resizeColumnToContents(0);
    tree->resizeColumnToContents(1);
    tree->resizeColumnToContents(2);

    if(traceWidgets.length()>0)
    {
	selectTrace(0);
    }
    else if(pointWidgets.length()>0)
    {
	selectPoint(0);
    }
}

void AnnotationWidget::activateItem()
{
    TreeItem *curr;
    curr = (TreeItem*)tree->currentItem();

    switch(curr->type())
    {
    case TreeItem::Point:
	emit pointClicked(curr->subject);
	break;
    case TreeItem::Trace:
	emit traceClicked(curr->subject);
	break;
    default:
	emit pointClicked(-1);
	emit traceClicked(-1);
	break;
    }
}

void AnnotationWidget::setActive(bool act)
{
    tree->setEnabled(act);
}

void AnnotationWidget::selectTrace(int tr)
{
    if(tr < 0)
    {
	tree->clearSelection();
	return;
    }
    if(tr < traceWidgets.length() )
    {
	tree->setCurrentItem(traceWidgets.at(tr));
	emit traceClicked(tr);
    }
}

void AnnotationWidget::selectPoint(int pt)
{
    if(pt < 0)
    {
	tree->clearSelection();
	return;
    }
    if(pt < pointWidgets.length() )
    {
	tree->setCurrentItem(pointWidgets.at(pt));
	emit pointClicked(pt);
    }
}

void AnnotationWidget::syncSignals()
{
    TreeItem *curr = (TreeItem*)tree->currentItem();
    if(curr==0)
    {
	emit pointClicked(-1);
	emit traceClicked(-1);
	return;
    }

//    qDebug() << "synchSignals" << curr->type << curr->subject;
    switch(curr->type())
    {
    case TreeItem::Point:
//	qDebug() << "AnnotationWidget::syncSignals point";
	emit pointClicked(curr->subject);
	break;
    case TreeItem::Trace:
	emit traceClicked(curr->subject);
	break;
    default:
//	qDebug() << "neither";
	emit pointClicked(-1);
	emit traceClicked(-1);
	break;
    }
//    qDebug() << "synchSignals" << curr->type << curr->subject;
}

void AnnotationWidget::doubleClick( QTreeWidgetItem * item, int column )
{
    if(column == 1)
    {
	TreeItem *curr;
	curr = (TreeItem*)tree->currentItem();

	switch(curr->type())
	{
	case TreeItem::Point:
	    if(experiment->getPointLocation(curr->subject)==Experiment::Video)
	    {
		experiment->setPointLocation(curr->subject,Experiment::Ultrasound);
		curr->setText(1,ultrasound);
	    }
	    else
	    {
		experiment->setPointLocation(curr->subject,Experiment::Video);
		curr->setText(1,video);
	    }
	    break;
	case TreeItem::Trace:
	    if(experiment->getTraceLocation(curr->subject)==Experiment::Video)
	    {
		experiment->setTraceLocation(curr->subject,Experiment::Ultrasound);
		curr->setText(1,ultrasound);
	    }
	    else
	    {
		experiment->setTraceLocation(curr->subject,Experiment::Video);
		curr->setText(1,video);
	    }
	    break;
	default:
	    break;
	}
    }
    else if(column == 2)
    {
	TreeItem *curr;
	curr = (TreeItem*)tree->currentItem();

	if(curr->type()  == TreeItem::Trace)
	{
	    if(experiment->getTraceType(curr->subject)==Experiment::Grid)
	    {
		experiment->setTraceType(curr->subject,Experiment::Free);
		curr->setText(2,free);
	    }
	    else
	    {
		int ret = QMessageBox::warning(this, tr("Careful!"),
					       tr("If you change this value, any data you have entered for this trace up to this point will be lost, for the entire experiment. Irreversibly.\n"
						  "Are you sure you want to do this?"), QMessageBox::Yes | QMessageBox::No);
		if(ret == QMessageBox::Yes)
		{
		    experiment->setTraceType(curr->subject,Experiment::Grid);
		    curr->setText(2,grid);
		}
	    }
	}
    }
}
