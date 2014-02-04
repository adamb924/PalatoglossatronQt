/****************************************************************************
** Meta object code from reading C++ file 'palatronwidget.h'
**
** Created: Tue Jan 4 12:35:25 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../palatronwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'palatronwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PalatronWidget[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      43,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      24,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   16,   15,   15, 0x05,
      42,   38,   15,   15, 0x05,
      76,   66,   15,   15, 0x05,
     104,  100,   15,   15, 0x05,
     132,  126,   15,   15, 0x05,
     157,   15,   15,   15, 0x05,
     171,   15,   15,   15, 0x05,
     185,   15,   15,   15, 0x05,
     199,   15,   15,   15, 0x05,
     220,  213,   15,   15, 0x05,
     238,  213,   15,   15, 0x05,
     256,  213,   15,   15, 0x05,
     274,  213,   15,   15, 0x05,
     308,  292,   15,   15, 0x05,
     336,  292,   15,   15, 0x05,
     385,  363,   15,   15, 0x05,
     412,  363,   15,   15, 0x05,
     450,  445,   15,   15, 0x05,
     476,   15,   15,   15, 0x05,
     489,   15,   15,   15, 0x05,
     504,  501,   15,   15, 0x05,
     531,  292,   15,   15, 0x05,
     554,   15,   15,   15, 0x05,
     570,   15,   15,   15, 0x05,

 // slots: signature, parameters, type, tag, flags
     599,   15,   15,   15, 0x0a,
     620,   16,   15,   15, 0x0a,
     663,  657,   15,   15, 0x0a,
     685,   66,   15,   15, 0x0a,
     724,  708,   15,   15, 0x0a,
     751,   38,   15,   15, 0x0a,
     771,   15,   15,   15, 0x08,
     785,   15,   15,   15, 0x08,
     810,  100,   15,   15, 0x08,
     834,  100,   15,   15, 0x08,
     855,   15,   15,   15, 0x08,
     881,   15,   15,   15, 0x08,
     909,   15,   15,   15, 0x08,
     932,   15,   15,   15, 0x08,
     949,  657,   15,   15, 0x08,
     976,  657,   15,   15, 0x08,
    1005,   15,   15,   15, 0x08,
    1025,   15,   15,   15, 0x08,
    1040,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PalatronWidget[] = {
    "PalatronWidget\0\0mode\0viewChanged(int)\0"
    "col\0dotColorChanged(QColor)\0subj,sess\0"
    "sessionChanged(int,int)\0tol\0"
    "toleranceChanged(int)\0trans\0"
    "transparencyChanged(int)\0defineBoxUL()\0"
    "defineBoxUR()\0defineBoxLL()\0defineBoxLR()\0"
    "toggle\0manualDotUL(bool)\0manualDotUR(bool)\0"
    "manualDotLL(bool)\0manualDotLR(bool)\0"
    "subject,session\0selectPalateImages(int,int)\0"
    "resetPalateImages(int,int)\0"
    "subject,session,image\0palateClicked(int,int,int)\0"
    "palateDoubleClicked(int,int,int)\0drag\0"
    "dragTransformedView(bool)\0selectFace()\0"
    "pickColor()\0tr\0selectTraceForPalates(int)\0"
    "drawThePalate(int,int)\0refreshPalate()\0"
    "updateSettingsOrPalateFrom()\0"
    "choosePalateImages()\0"
    "changeView(ImageWidget::DisplayMode)\0"
    "index\0viewComboChanged(int)\0"
    "updateSession(int,int)\0subj,sess,image\0"
    "changeOfImage(int,int,int)\0"
    "colorPicked(QColor)\0removeImage()\0"
    "palateSelectionChanged()\0"
    "changeTransparency(int)\0changeTolerance(int)\0"
    "populateCopyFromSession()\0"
    "populatePalateFromSession()\0"
    "populatePalateImages()\0defineDotColor()\0"
    "selectCopyFromSession(int)\0"
    "selectPalateFromSession(int)\0"
    "drawPalateClicked()\0activateItem()\0"
    "selectionChanged()\0"
};

const QMetaObject PalatronWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PalatronWidget,
      qt_meta_data_PalatronWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PalatronWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PalatronWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PalatronWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PalatronWidget))
        return static_cast<void*>(const_cast< PalatronWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int PalatronWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: viewChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: dotColorChanged((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 2: sessionChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: toleranceChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: transparencyChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: defineBoxUL(); break;
        case 6: defineBoxUR(); break;
        case 7: defineBoxLL(); break;
        case 8: defineBoxLR(); break;
        case 9: manualDotUL((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: manualDotUR((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: manualDotLL((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: manualDotLR((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: selectPalateImages((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 14: resetPalateImages((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 15: palateClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 16: palateDoubleClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 17: dragTransformedView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: selectFace(); break;
        case 19: pickColor(); break;
        case 20: selectTraceForPalates((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: drawThePalate((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 22: refreshPalate(); break;
        case 23: updateSettingsOrPalateFrom(); break;
        case 24: choosePalateImages(); break;
        case 25: changeView((*reinterpret_cast< ImageWidget::DisplayMode(*)>(_a[1]))); break;
        case 26: viewComboChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 27: updateSession((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 28: changeOfImage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 29: colorPicked((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 30: removeImage(); break;
        case 31: palateSelectionChanged(); break;
        case 32: changeTransparency((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 33: changeTolerance((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 34: populateCopyFromSession(); break;
        case 35: populatePalateFromSession(); break;
        case 36: populatePalateImages(); break;
        case 37: defineDotColor(); break;
        case 38: selectCopyFromSession((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 39: selectPalateFromSession((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 40: drawPalateClicked(); break;
        case 41: activateItem(); break;
        case 42: selectionChanged(); break;
        default: ;
        }
        _id -= 43;
    }
    return _id;
}

// SIGNAL 0
void PalatronWidget::viewChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PalatronWidget::dotColorChanged(QColor _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PalatronWidget::sessionChanged(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PalatronWidget::toleranceChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void PalatronWidget::transparencyChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void PalatronWidget::defineBoxUL()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void PalatronWidget::defineBoxUR()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void PalatronWidget::defineBoxLL()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}

// SIGNAL 8
void PalatronWidget::defineBoxLR()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}

// SIGNAL 9
void PalatronWidget::manualDotUL(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void PalatronWidget::manualDotUR(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void PalatronWidget::manualDotLL(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void PalatronWidget::manualDotLR(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void PalatronWidget::selectPalateImages(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void PalatronWidget::resetPalateImages(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void PalatronWidget::palateClicked(int _t1, int _t2, int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void PalatronWidget::palateDoubleClicked(int _t1, int _t2, int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void PalatronWidget::dragTransformedView(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void PalatronWidget::selectFace()
{
    QMetaObject::activate(this, &staticMetaObject, 18, 0);
}

// SIGNAL 19
void PalatronWidget::pickColor()
{
    QMetaObject::activate(this, &staticMetaObject, 19, 0);
}

// SIGNAL 20
void PalatronWidget::selectTraceForPalates(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 20, _a);
}

// SIGNAL 21
void PalatronWidget::drawThePalate(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 21, _a);
}

// SIGNAL 22
void PalatronWidget::refreshPalate()
{
    QMetaObject::activate(this, &staticMetaObject, 22, 0);
}

// SIGNAL 23
void PalatronWidget::updateSettingsOrPalateFrom()
{
    QMetaObject::activate(this, &staticMetaObject, 23, 0);
}
QT_END_MOC_NAMESPACE
