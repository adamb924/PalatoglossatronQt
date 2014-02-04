/****************************************************************************
** Meta object code from reading C++ file 'subjectwidget.h'
**
** Created: Tue Jan 4 11:51:13 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../subjectwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'subjectwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SubjectWidget[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      31,   15,   14,   14, 0x05,
      63,   55,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      83,   14,   14,   14, 0x0a,
     120,   98,   14,   14, 0x08,
     147,   15,   14,   14, 0x08,
     172,   55,   14,   14, 0x08,
     193,   14,   14,   14, 0x08,
     206,   14,   14,   14, 0x08,
     222,   14,   14,   14, 0x08,
     235,   14,   14,   14, 0x08,
     251,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SubjectWidget[] = {
    "SubjectWidget\0\0subject,session\0"
    "sessionClicked(int,int)\0subject\0"
    "subjectClicked(int)\0activateItem()\0"
    "subject,session,image\0changeOfImage(int,int,int)\0"
    "selectedSession(int,int)\0selectedSubject(int)\0"
    "addSubject()\0removeSubject()\0addSession()\0"
    "removeSession()\0doubleClickItem()\0"
};

const QMetaObject SubjectWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SubjectWidget,
      qt_meta_data_SubjectWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SubjectWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SubjectWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SubjectWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SubjectWidget))
        return static_cast<void*>(const_cast< SubjectWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int SubjectWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sessionClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: subjectClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: activateItem(); break;
        case 3: changeOfImage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 4: selectedSession((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: selectedSubject((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: addSubject(); break;
        case 7: removeSubject(); break;
        case 8: addSession(); break;
        case 9: removeSession(); break;
        case 10: doubleClickItem(); break;
        default: ;
        }
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void SubjectWidget::sessionClicked(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SubjectWidget::subjectClicked(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
