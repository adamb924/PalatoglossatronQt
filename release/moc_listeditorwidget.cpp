/****************************************************************************
** Meta object code from reading C++ file 'listeditorwidget.h'
**
** Created: Thu Jul 14 12:31:14 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../listeditorwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'listeditorwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ListEditorWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x0a,
      44,   17,   17,   17, 0x0a,
      54,   17,   17,   17, 0x0a,
      60,   17,   17,   17, 0x0a,
      69,   17,   17,   17, 0x0a,
      78,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ListEditorWidget[] = {
    "ListEditorWidget\0\0saveNamesFromListWidget()\0"
    "refresh()\0add()\0remove()\0moveup()\0"
    "movedown()\0"
};

const QMetaObject ListEditorWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ListEditorWidget,
      qt_meta_data_ListEditorWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ListEditorWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ListEditorWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ListEditorWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ListEditorWidget))
        return static_cast<void*>(const_cast< ListEditorWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int ListEditorWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: saveNamesFromListWidget(); break;
        case 1: refresh(); break;
        case 2: add(); break;
        case 3: remove(); break;
        case 4: moveup(); break;
        case 5: movedown(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
