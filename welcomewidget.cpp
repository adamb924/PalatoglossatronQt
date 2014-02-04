#include "welcomewidget.h"

#include <QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QLineEdit>
#include <QLabel>
#include <QStringListModel>
#include <QListView>
#include <QStringList>

WelcomeWidget::WelcomeWidget(QWidget *parent)
    : QWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);


    create = new QPushButton(QIcon::fromTheme("edit-undo"),tr("Create a new experiment"));
    open = new QPushButton(QIcon::fromTheme("edit-undo"),tr("Open an existing experiment"));
    exit = new QPushButton(QIcon::fromTheme("edit-undo"),tr("Exit the program"));

/*
    QVBoxLayout *vlayout = new QVBoxLayout();
    vlayout->addWidget(create);
    vlayout->addWidget(open);
    vlayout->addWidget(exit);
    this->setLayout(vlayout);
*/
    QGridLayout *grdLayout = new QGridLayout;
    grdLayout->addWidget(create,1,1);
    grdLayout->addWidget(open,2,1);
    grdLayout->addWidget(exit,3,1);
    grdLayout->setRowStretch(0,1);
    grdLayout->setRowStretch(4,1);
    grdLayout->setColumnStretch(0,1);
    grdLayout->setColumnStretch(2,1);
    this->setLayout(grdLayout);
}

QSize WelcomeWidget::sizeHint() const
{
    return QSize(500,500);
}

