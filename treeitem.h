#ifndef TREEITEM_H
#define TREEITEM_H

#include <QTreeWidgetItem>
#include <QTreeWidget>

class TreeItem : public QObject, public QTreeWidgetItem
{
    Q_OBJECT
    Q_ENUMS(Type)
public:
    enum Type {
	Subject,
	Session,
	Image,
	Trace,
	Point,
	Null
    };

//    TreeItem();
    TreeItem(QTreeWidget *parent, TreeItem::Type t, int subject=-1, int session=-1, int image=-1, int trace=-1, int point=-1);
    TreeItem(QTreeWidgetItem *parent, TreeItem::Type t, int subject=-1, int session=-1, int image=-1, int trace=-1, int point=-1);
    TreeItem(TreeItem *parent, TreeItem::Type t, int subject=-1, int session=-1, int image=-1, int trace=-1, int point=-1);

    int type() const;

    Type theType;
    int subject, session, image, trace, point;
};

#endif // TREEITEM_H
