#include "palateimagespecifier.h"

#include "session.h"
#include "image.h"

#include <QTableWidget>
#include <QGridLayout>
#include <QCheckBox>
#include <QLabel>
#include <QFileInfo>
#include <QHeaderView>
#include <QtDebug>
#include <QPushButton>

PalateImageSpecifier::PalateImageSpecifier(Session *s, QWidget *parent) :
    QDialog(parent)
{
    QFileInfo f;
    QTableWidget *table = new QTableWidget(s->images()->length(),2,this);
    QGridLayout *gridlayout = new QGridLayout;
    gridlayout->addWidget(table,0,0,1,2,Qt::AlignHCenter);
    this->setLayout(gridlayout);

    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setShowGrid(false);
    table->verticalHeader()->hide();
    table->horizontalHeader()->hide();
    table->setSelectionMode(QAbstractItemView::NoSelection);
    table->resizeColumnToContents(0);

    aCheckBoxes.clear();
    for(int i=0; i<s->images()->length(); i++)
    {
	aCheckBoxes << new QCheckBox(0);

	table->setCellWidget(i,0,aCheckBoxes.last());

	aCheckBoxes.last()->setChecked(s->images()->at(i)->isPalate());

	f = QFileInfo(s->images()->at(i)->filename());
	table->setCellWidget(i,1,new QLabel(f.completeBaseName()));
    }

    table->resizeColumnToContents(0);
    table->resizeColumnToContents(1);

    QPushButton *ok = new QPushButton(tr("OK"));
    QPushButton *cancel = new QPushButton(tr("Cancel"));

    gridlayout->addWidget(ok,2,0);
    gridlayout->addWidget(cancel,2,1);

    connect(ok,SIGNAL(clicked()),this,SLOT(accept()));
    connect(cancel,SIGNAL(clicked()),this,SLOT(reject()));

    connect(table,SIGNAL(cellClicked(int,int)),this,SLOT(rowSelected(int)));

    this->setWindowTitle("Select palate images");
}

void PalateImageSpecifier::rowSelected(int row)
{
//    qDebug() << row;
}
