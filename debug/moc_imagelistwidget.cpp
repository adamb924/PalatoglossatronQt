/****************************************************************************
** Meta object code from reading C++ file 'imagelistwidget.h'
**
** Created: Tue Jan 4 11:51:16 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../imagelistwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imagelistwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ImageListWidget[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      39,   17,   16,   16, 0x05,
      65,   17,   16,   16, 0x05,
      97,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
     118,   16,   16,   16, 0x0a,
     155,  133,   16,   16, 0x0a,
     180,   16,   16,   16, 0x08,
     192,   16,   16,   16, 0x08,
     207,   16,   16,   16, 0x08,
     238,  226,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ImageListWidget[] = {
    "ImageListWidget\0\0subject,session,image\0"
    "imageClicked(int,int,int)\0"
    "imageDoubleClicked(int,int,int)\0"
    "interlacingChanged()\0activateItem()\0"
    "subject,session,index\0selectImage(int,int,int)\0"
    "addImages()\0removeImages()\0"
    "selectionChanged()\0item,column\0"
    "doubleClick(QTreeWidgetItem*,int)\0"
};

const QMetaObject ImageListWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ImageListWidget,
      qt_meta_data_ImageListWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ImageListWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ImageListWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ImageListWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ImageListWidget))
        return static_cast<void*>(const_cast< ImageListWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int ImageListWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: imageClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: imageDoubleClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: interlacingChanged(); break;
        case 3: activateItem(); break;
        case 4: selectImage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 5: addImages(); break;
        case 6: removeImages(); break;
        case 7: selectionChanged(); break;
        case 8: doubleClick((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void ImageListWidget::imageClicked(int _t1, int _t2, int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ImageListWidget::imageDoubleClicked(int _t1, int _t2, int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ImageListWidget::interlacingChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
