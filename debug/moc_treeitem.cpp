/****************************************************************************
** Meta object code from reading C++ file 'treeitem.h'
**
** Created: Tue Jan 4 11:51:14 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../treeitem.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'treeitem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TreeItem[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // enums: name, flags, count, data
       9, 0x0,    6,   18,

 // enum data: key, value
      14, uint(TreeItem::Subject),
      22, uint(TreeItem::Session),
      30, uint(TreeItem::Image),
      36, uint(TreeItem::Trace),
      42, uint(TreeItem::Point),
      48, uint(TreeItem::Null),

       0        // eod
};

static const char qt_meta_stringdata_TreeItem[] = {
    "TreeItem\0Type\0Subject\0Session\0Image\0"
    "Trace\0Point\0Null\0"
};

const QMetaObject TreeItem::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TreeItem,
      qt_meta_data_TreeItem, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TreeItem::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TreeItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TreeItem::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TreeItem))
        return static_cast<void*>(const_cast< TreeItem*>(this));
    if (!strcmp(_clname, "QTreeWidgetItem"))
        return static_cast< QTreeWidgetItem*>(const_cast< TreeItem*>(this));
    return QObject::qt_metacast(_clname);
}

int TreeItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
