#include "listeditorwidget.h"

#include <QLineEdit>
#include <QLabel>
#include <QStringListModel>
#include <QListView>
#include <QStringList>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QtDebug>

ListEditorWidget::ListEditorWidget(QStringList list)
{
    QHBoxLayout *hlayout = new QHBoxLayout;
    QVBoxLayout *vlayout = new QVBoxLayout;
    QPushButton *badd = new QPushButton(tr("Add"));
    QPushButton *bremove = new QPushButton(tr("Remove"));
//    QPushButton *bup = new QPushButton(style()->standardIcon(QStyle::SP_ArrowUp),tr("Move Up"));
//    QPushButton *bdown = new QPushButton(style()->standardIcon(QStyle::SP_ArrowDown),tr("Move Down"));
    QPushButton *bup = new QPushButton(style()->standardIcon(QStyle::SP_ArrowUp),"");
    QPushButton *bdown = new QPushButton(style()->standardIcon(QStyle::SP_ArrowDown),"");

    this->list = list;
    listWidget = new QListWidget;
    listWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    listWidget->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::SelectedClicked|QAbstractItemView::EditKeyPressed);
    hlayout->addWidget(listWidget);

    vlayout->addWidget(badd);
    vlayout->addWidget(bremove);
    vlayout->addWidget(bup);
    vlayout->addWidget(bdown);

    connect(badd,SIGNAL(clicked()),this,SLOT(add()));
    connect(bremove,SIGNAL(clicked()),this,SLOT(remove()));
    connect(bup,SIGNAL(clicked()),this,SLOT(moveup()));
    connect(bdown,SIGNAL(clicked()),this,SLOT(movedown()));

    connect(listWidget,SIGNAL(itemChanged( QListWidgetItem *)), this, SLOT(saveNamesFromListWidget()) );

    refresh();

    hlayout->addLayout(vlayout);
    this->setLayout(hlayout);
}

QSize ListEditorWidget::sizeHint() const
{
    return QSize(350,150);
}

void ListEditorWidget::saveNamesFromListWidget()
{
    if( listWidget->count() != list.count() ) // undefined situation, so just quit
	return;

    for(int i=0; i<listWidget->count(); i++)
	list[i] = listWidget->item(i)->text();
}

void ListEditorWidget::refresh()
{
    listWidget->clear();
    listWidget->insertItems(0,list);
    for(int i=0; i<listWidget->count(); i++)
    {
	listWidget->item(i)->setFlags (listWidget->item(i)->flags () | Qt::ItemIsEditable);
    }
}


QStringList ListEditorWidget::stringsList()
{
    return list;
}

void ListEditorWidget::add()
{
    saveNamesFromListWidget();
    list << "New Item";
    refresh();
    listWidget->editItem(listWidget->item(list.length()-1));
}

void ListEditorWidget::remove()
{
    saveNamesFromListWidget();
    QList<QListWidgetItem*> selections = listWidget->selectedItems();
    if(selections.length()==0) { return; }
    for(int i=0; i<selections.length(); i++)
    {
	list.removeAt(listWidget->row(selections.at(i)));
    }
    refresh();
}

void ListEditorWidget::moveup()
{
    saveNamesFromListWidget();
    QList<QListWidgetItem*> selections = listWidget->selectedItems();
    if(selections.length()==0) { return; }
    int ind = listWidget->row(selections.at(0));
    if(ind>0)
    {
	list.swap(ind,ind-1);
	refresh();
	listWidget->setCurrentRow(ind-1,QItemSelectionModel::ClearAndSelect);
    }
}

void ListEditorWidget::movedown()
{
    saveNamesFromListWidget();
    QList<QListWidgetItem*> selections = listWidget->selectedItems();
    if(selections.length()==0) { return; }
    int ind = listWidget->row(selections.at(0));
    if(ind<list.length()-1)
    {
	list.swap(ind,ind+1);
	refresh();
	listWidget->setCurrentRow(ind+1,QItemSelectionModel::ClearAndSelect);
    }
}
