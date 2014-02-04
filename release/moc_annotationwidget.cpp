/****************************************************************************
** Meta object code from reading C++ file 'annotationwidget.h'
**
** Created: Thu Dec 30 11:46:57 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../annotationwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'annotationwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AnnotationWidget[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   18,   17,   17, 0x05,
      48,   42,   17,   17, 0x05,
      66,   17,   17,   17, 0x05,
      85,   79,   17,   17, 0x05,
     106,   17,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
     126,   17,   17,   17, 0x0a,
     144,  141,   17,   17, 0x0a,
     164,  161,   17,   17, 0x0a,
     181,   17,   17,   17, 0x0a,
     207,  195,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AnnotationWidget[] = {
    "AnnotationWidget\0\0trace\0traceClicked(int)\0"
    "point\0pointClicked(int)\0defineGrid()\0"
    "lines\0updateGridLines(int)\0"
    "sendGridToTracers()\0activateItem()\0"
    "tr\0selectTrace(int)\0pt\0selectPoint(int)\0"
    "syncSignals()\0item,column\0"
    "doubleClick(QTreeWidgetItem*,int)\0"
};

const QMetaObject AnnotationWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AnnotationWidget,
      qt_meta_data_AnnotationWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AnnotationWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AnnotationWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AnnotationWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AnnotationWidget))
        return static_cast<void*>(const_cast< AnnotationWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int AnnotationWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: traceClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: pointClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: defineGrid(); break;
        case 3: updateGridLines((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: sendGridToTracers(); break;
        case 5: activateItem(); break;
        case 6: selectTrace((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: selectPoint((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: syncSignals(); break;
        case 9: doubleClick((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void AnnotationWidget::traceClicked(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AnnotationWidget::pointClicked(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void AnnotationWidget::defineGrid()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void AnnotationWidget::updateGridLines(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void AnnotationWidget::sendGridToTracers()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}
QT_END_MOC_NAMESPACE
