/****************************************************************************
** Meta object code from reading C++ file 'imagewidget.h'
**
** Created: Tue Jan 4 12:35:23 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../imagewidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imagewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ImageWidget[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      47,   14, // methods
       0,    0, // properties
       2,  249, // enums/sets
       0,    0, // constructors
       0,       // flags
      15,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   13,   12,   12, 0x05,
      62,   59,   12,   12, 0x05,
      87,   84,   12,   12, 0x05,
     113,  109,   12,   12, 0x05,
     150,  136,   12,   12, 0x05,
     176,  136,   12,   12, 0x05,
     207,  203,   12,   12, 0x05,
     234,  227,   12,   12, 0x05,
     265,  227,   12,   12, 0x05,
     297,  227,   12,   12, 0x05,
     324,  227,   12,   12, 0x05,
     358,  227,   12,   12, 0x05,
     391,  227,   12,   12, 0x05,
     421,  416,   12,   12, 0x05,
     459,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
     484,  479,   12,   12, 0x0a,
     510,   12,   12,   12, 0x0a,
     523,  416,   12,   12, 0x0a,
     539,   12,   12,   12, 0x0a,
     555,   12,   12,   12, 0x0a,
     586,   12,   12,   12, 0x0a,
     608,  227,   12,   12, 0x0a,
     638,  227,   12,   12, 0x0a,
     669,  227,   12,   12, 0x0a,
     695,  227,   12,   12, 0x0a,
     728,  227,   12,   12, 0x0a,
     760,  227,   12,   12, 0x0a,
     784,   59,   12,   12, 0x0a,
     802,   84,   12,   12, 0x0a,
     820,   12,   12,   12, 0x0a,
     832,   12,   12,   12, 0x0a,
     848,   12,   12,   12, 0x0a,
     862,   12,   12,   12, 0x0a,
     876,   12,   12,   12, 0x0a,
     890,   12,   12,   12, 0x0a,
     904,   12,   12,   12, 0x0a,
     925,  918,   12,   12, 0x0a,
     945,  918,   12,   12, 0x0a,
     965,  918,   12,   12, 0x0a,
     985,  918,   12,   12, 0x0a,
    1005,  203,   12,   12, 0x0a,
    1033, 1029,   12,   12, 0x0a,
    1060, 1055,   12,   12, 0x0a,
    1077,   12,   12,   12, 0x0a,
    1089,   12,   12,   12, 0x0a,
    1108, 1102,   12,   12, 0x0a,
    1129,   12,   12,   12, 0x0a,

 // enums: name, flags, count, data
    1152, 0x0,    7,  257,
    1164, 0x0,   17,  271,

 // enum data: key, value
    1174, uint(ImageWidget::Untransformed),
    1188, uint(ImageWidget::Dot_View),
    1197, uint(ImageWidget::Composite_Dot_View),
    1216, uint(ImageWidget::TransformedAbstract),
    1236, uint(ImageWidget::TransformedTraditional),
    1259, uint(ImageWidget::PalateDrawing),
    1273, uint(ImageWidget::Plugin),
    1280, uint(ImageWidget::Point),
    1286, uint(ImageWidget::Trace),
    1292, uint(ImageWidget::Box_UL),
    1299, uint(ImageWidget::Box_UR),
    1306, uint(ImageWidget::Box_LL),
    1313, uint(ImageWidget::Box_LR),
    1320, uint(ImageWidget::Dot_UL),
    1327, uint(ImageWidget::Dot_UR),
    1334, uint(ImageWidget::Dot_LL),
    1341, uint(ImageWidget::Dot_LR),
    1348, uint(ImageWidget::ColorPick),
    1358, uint(ImageWidget::Grid_Left),
    1368, uint(ImageWidget::Grid_Right),
    1379, uint(ImageWidget::TransformationPreDrag),
    1401, uint(ImageWidget::TransformationDrag),
    1420, uint(ImageWidget::SelectFace),
    1431, uint(ImageWidget::DrawPalate),

       0        // eod
};

static const char qt_meta_stringdata_ImageWidget[] = {
    "ImageWidget\0\0pos,col\0"
    "cursorOverImageChanged(QPoint,QColor)\0"
    "pt\0editPointChanged(int)\0tr\0"
    "editTraceChanged(int)\0msg\0"
    "statusMessage(QString)\0subj,sess,img\0"
    "imageChanged(int,int,int)\0"
    "palateChanged(int,int,int)\0col\0"
    "colorPicked(QColor)\0status\0"
    "traceLinesVisibleChanged(bool)\0"
    "tracePointsVisibleChanged(bool)\0"
    "pointsVisibleChanged(bool)\0"
    "palatronBoxesVisibleChanged(bool)\0"
    "palatronDotsVisibleChanged(bool)\0"
    "gridVisibleChanged(bool)\0mode\0"
    "viewChanged(ImageWidget::DisplayMode)\0"
    "sendGridToTracers()\0drag\0"
    "dragTransformedView(bool)\0selectFace()\0"
    "changeView(int)\0updateDotView()\0"
    "updateTraditionalTransformed()\0"
    "updateCompositeView()\0"
    "updateTraceLinesVisible(bool)\0"
    "updateTracePointsVisible(bool)\0"
    "updatePointsVisible(bool)\0"
    "updatePalatronBoxesVisible(bool)\0"
    "updatePalatronDotsVisible(bool)\0"
    "updateGridVisible(bool)\0setEditPoint(int)\0"
    "setEditTrace(int)\0nextImage()\0"
    "previousImage()\0syncSignals()\0"
    "defineBoxUL()\0defineBoxUR()\0defineBoxLL()\0"
    "defineBoxLR()\0toggle\0definePointUL(bool)\0"
    "definePointUR(bool)\0definePointLL(bool)\0"
    "definePointLR(bool)\0dotColorChanged(QColor)\0"
    "tol\0toleranceChanged(int)\0show\0"
    "showDotView(int)\0pickColor()\0defineGrid()\0"
    "lines\0updateGridLines(int)\0"
    "updateIfPluginDislay()\0DisplayMode\0"
    "InputMode\0Untransformed\0Dot_View\0"
    "Composite_Dot_View\0TransformedAbstract\0"
    "TransformedTraditional\0PalateDrawing\0"
    "Plugin\0Point\0Trace\0Box_UL\0Box_UR\0"
    "Box_LL\0Box_LR\0Dot_UL\0Dot_UR\0Dot_LL\0"
    "Dot_LR\0ColorPick\0Grid_Left\0Grid_Right\0"
    "TransformationPreDrag\0TransformationDrag\0"
    "SelectFace\0DrawPalate\0"
};

const QMetaObject ImageWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ImageWidget,
      qt_meta_data_ImageWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ImageWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ImageWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ImageWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ImageWidget))
        return static_cast<void*>(const_cast< ImageWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int ImageWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: cursorOverImageChanged((*reinterpret_cast< QPoint(*)>(_a[1])),(*reinterpret_cast< QColor(*)>(_a[2]))); break;
        case 1: editPointChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: editTraceChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: statusMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: imageChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 5: palateChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 6: colorPicked((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 7: traceLinesVisibleChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: tracePointsVisibleChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: pointsVisibleChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: palatronBoxesVisibleChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: palatronDotsVisibleChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: gridVisibleChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: viewChanged((*reinterpret_cast< ImageWidget::DisplayMode(*)>(_a[1]))); break;
        case 14: sendGridToTracers(); break;
        case 15: dragTransformedView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: selectFace(); break;
        case 17: changeView((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: updateDotView(); break;
        case 19: updateTraditionalTransformed(); break;
        case 20: updateCompositeView(); break;
        case 21: updateTraceLinesVisible((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 22: updateTracePointsVisible((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 23: updatePointsVisible((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 24: updatePalatronBoxesVisible((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 25: updatePalatronDotsVisible((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 26: updateGridVisible((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 27: setEditPoint((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 28: setEditTrace((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 29: nextImage(); break;
        case 30: previousImage(); break;
        case 31: syncSignals(); break;
        case 32: defineBoxUL(); break;
        case 33: defineBoxUR(); break;
        case 34: defineBoxLL(); break;
        case 35: defineBoxLR(); break;
        case 36: definePointUL((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 37: definePointUR((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 38: definePointLL((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 39: definePointLR((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 40: dotColorChanged((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 41: toleranceChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 42: showDotView((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 43: pickColor(); break;
        case 44: defineGrid(); break;
        case 45: updateGridLines((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 46: updateIfPluginDislay(); break;
        default: ;
        }
        _id -= 47;
    }
    return _id;
}

// SIGNAL 0
void ImageWidget::cursorOverImageChanged(QPoint _t1, QColor _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ImageWidget::editPointChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ImageWidget::editTraceChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ImageWidget::statusMessage(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ImageWidget::imageChanged(int _t1, int _t2, int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ImageWidget::palateChanged(int _t1, int _t2, int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ImageWidget::colorPicked(QColor _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ImageWidget::traceLinesVisibleChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void ImageWidget::tracePointsVisibleChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void ImageWidget::pointsVisibleChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void ImageWidget::palatronBoxesVisibleChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void ImageWidget::palatronDotsVisibleChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void ImageWidget::gridVisibleChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void ImageWidget::viewChanged(ImageWidget::DisplayMode _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void ImageWidget::sendGridToTracers()
{
    QMetaObject::activate(this, &staticMetaObject, 14, 0);
}
QT_END_MOC_NAMESPACE
