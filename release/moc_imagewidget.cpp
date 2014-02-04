/****************************************************************************
** Meta object code from reading C++ file 'imagewidget.h'
**
** Created: Wed Sep 7 15:31:55 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../imagewidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imagewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ImageWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      48,   14, // methods
       0,    0, // properties
       2,  254, // enums/sets
       0,    0, // constructors
       0,       // flags
      16,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,   13,   12,   12, 0x05,
      53,   45,   12,   12, 0x05,
      94,   91,   12,   12, 0x05,
     119,  116,   12,   12, 0x05,
     145,  141,   12,   12, 0x05,
     182,  168,   12,   12, 0x05,
     208,  168,   12,   12, 0x05,
     239,  235,   12,   12, 0x05,
     266,  259,   12,   12, 0x05,
     297,  259,   12,   12, 0x05,
     329,  259,   12,   12, 0x05,
     356,  259,   12,   12, 0x05,
     390,  259,   12,   12, 0x05,
     423,  259,   12,   12, 0x05,
     453,  448,   12,   12, 0x05,
     491,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
     516,  511,   12,   12, 0x0a,
     542,   12,   12,   12, 0x0a,
     555,  448,   12,   12, 0x0a,
     571,   12,   12,   12, 0x0a,
     587,   12,   12,   12, 0x0a,
     618,   12,   12,   12, 0x0a,
     640,  259,   12,   12, 0x0a,
     670,  259,   12,   12, 0x0a,
     701,  259,   12,   12, 0x0a,
     727,  259,   12,   12, 0x0a,
     760,  259,   12,   12, 0x0a,
     792,  259,   12,   12, 0x0a,
     816,   91,   12,   12, 0x0a,
     834,  116,   12,   12, 0x0a,
     852,   12,   12,   12, 0x0a,
     864,   12,   12,   12, 0x0a,
     880,   12,   12,   12, 0x0a,
     894,   12,   12,   12, 0x0a,
     908,   12,   12,   12, 0x0a,
     922,   12,   12,   12, 0x0a,
     936,   12,   12,   12, 0x0a,
     957,  950,   12,   12, 0x0a,
     977,  950,   12,   12, 0x0a,
     997,  950,   12,   12, 0x0a,
    1017,  950,   12,   12, 0x0a,
    1037,  235,   12,   12, 0x0a,
    1065, 1061,   12,   12, 0x0a,
    1092, 1087,   12,   12, 0x0a,
    1109,   12,   12,   12, 0x0a,
    1121,   12,   12,   12, 0x0a,
    1140, 1134,   12,   12, 0x0a,
    1161,   12,   12,   12, 0x0a,

 // enums: name, flags, count, data
    1184, 0x0,    7,  262,
    1196, 0x0,   17,  276,

 // enum data: key, value
    1206, uint(ImageWidget::Untransformed),
    1220, uint(ImageWidget::Dot_View),
    1229, uint(ImageWidget::Composite_Dot_View),
    1248, uint(ImageWidget::TransformedAbstract),
    1268, uint(ImageWidget::TransformedTraditional),
    1291, uint(ImageWidget::PalateDrawing),
    1305, uint(ImageWidget::Plugin),
    1312, uint(ImageWidget::Point),
    1318, uint(ImageWidget::Trace),
    1324, uint(ImageWidget::Box_UL),
    1331, uint(ImageWidget::Box_UR),
    1338, uint(ImageWidget::Box_LL),
    1345, uint(ImageWidget::Box_LR),
    1352, uint(ImageWidget::Dot_UL),
    1359, uint(ImageWidget::Dot_UR),
    1366, uint(ImageWidget::Dot_LL),
    1373, uint(ImageWidget::Dot_LR),
    1380, uint(ImageWidget::ColorPick),
    1390, uint(ImageWidget::Grid_Left),
    1400, uint(ImageWidget::Grid_Right),
    1411, uint(ImageWidget::TransformationPreDrag),
    1433, uint(ImageWidget::TransformationDrag),
    1452, uint(ImageWidget::SelectFace),
    1463, uint(ImageWidget::DrawPalate),

       0        // eod
};

static const char qt_meta_stringdata_ImageWidget[] = {
    "ImageWidget\0\0zoomLevel\0zoomLevelChanged(int)\0"
    "pos,col\0cursorOverImageChanged(QPoint,QColor)\0"
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
        case 0: zoomLevelChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: cursorOverImageChanged((*reinterpret_cast< QPoint(*)>(_a[1])),(*reinterpret_cast< QColor(*)>(_a[2]))); break;
        case 2: editPointChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: editTraceChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: statusMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: imageChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 6: palateChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 7: colorPicked((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 8: traceLinesVisibleChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: tracePointsVisibleChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: pointsVisibleChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: palatronBoxesVisibleChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: palatronDotsVisibleChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: gridVisibleChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: viewChanged((*reinterpret_cast< ImageWidget::DisplayMode(*)>(_a[1]))); break;
        case 15: sendGridToTracers(); break;
        case 16: dragTransformedView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 17: selectFace(); break;
        case 18: changeView((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: updateDotView(); break;
        case 20: updateTraditionalTransformed(); break;
        case 21: updateCompositeView(); break;
        case 22: updateTraceLinesVisible((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 23: updateTracePointsVisible((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 24: updatePointsVisible((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 25: updatePalatronBoxesVisible((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 26: updatePalatronDotsVisible((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 27: updateGridVisible((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 28: setEditPoint((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 29: setEditTrace((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 30: nextImage(); break;
        case 31: previousImage(); break;
        case 32: syncSignals(); break;
        case 33: defineBoxUL(); break;
        case 34: defineBoxUR(); break;
        case 35: defineBoxLL(); break;
        case 36: defineBoxLR(); break;
        case 37: definePointUL((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 38: definePointUR((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 39: definePointLL((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 40: definePointLR((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 41: dotColorChanged((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 42: toleranceChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 43: showDotView((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 44: pickColor(); break;
        case 45: defineGrid(); break;
        case 46: updateGridLines((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 47: updateIfPluginDislay(); break;
        default: ;
        }
        _id -= 48;
    }
    return _id;
}

// SIGNAL 0
void ImageWidget::zoomLevelChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ImageWidget::cursorOverImageChanged(QPoint _t1, QColor _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ImageWidget::editPointChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ImageWidget::editTraceChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ImageWidget::statusMessage(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ImageWidget::imageChanged(int _t1, int _t2, int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ImageWidget::palateChanged(int _t1, int _t2, int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ImageWidget::colorPicked(QColor _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void ImageWidget::traceLinesVisibleChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void ImageWidget::tracePointsVisibleChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void ImageWidget::pointsVisibleChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void ImageWidget::palatronBoxesVisibleChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void ImageWidget::palatronDotsVisibleChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void ImageWidget::gridVisibleChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void ImageWidget::viewChanged(ImageWidget::DisplayMode _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void ImageWidget::sendGridToTracers()
{
    QMetaObject::activate(this, &staticMetaObject, 15, 0);
}
QT_END_MOC_NAMESPACE
