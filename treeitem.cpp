#include "treeitem.h"

TreeItem::TreeItem(QTreeWidget *parent, TreeItem::Type t, int subject, int session, int image, int trace, int point) : 	QTreeWidgetItem(parent)
{
    theType = t;
    this->subject = subject;
    this->session = session;
    this->image = image;
    this->trace = trace;
    this->point = point;
}

TreeItem::TreeItem(QTreeWidgetItem *parent, TreeItem::Type t, int subject, int session, int image, int trace, int point) : QTreeWidgetItem(parent)
{
    theType = t;
    this->subject = subject;
    this->session = session;
    this->image = image;
    this->trace = trace;
    this->point = point;
}

TreeItem::TreeItem(TreeItem *parent, TreeItem::Type t, int subject, int session, int image, int trace, int point) : QTreeWidgetItem(parent)
{
    theType = t;
    this->subject = subject;
    this->session = session;
    this->image = image;
    this->trace = trace;
    this->point = point;
}

int TreeItem::type() const
{
    return theType;
}
