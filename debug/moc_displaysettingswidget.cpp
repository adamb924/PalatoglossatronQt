/****************************************************************************
** Meta object code from reading C++ file 'displaysettingswidget.h'
**
** Created: Tue Jan 4 11:51:26 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../displaysettingswidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'displaysettingswidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DisplaySettingsWidget[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,   22,   22,   22, 0x05,

 // slots: signature, parameters, type, tag, flags
      42,   22,   22,   22, 0x0a,
      72,   22,   22,   22, 0x0a,
     101,   22,   22,   22, 0x0a,
     138,   22,   22,   22, 0x0a,
     157,   22,   22,   22, 0x0a,
     176,   22,   22,   22, 0x0a,
     200,   22,   22,   22, 0x0a,
     228,   22,   22,   22, 0x0a,
     255,   22,   22,   22, 0x0a,
     290,   22,   22,   22, 0x0a,
     320,   22,   22,   22, 0x0a,
     336,  331,   22,   22, 0x0a,
     369,  331,   22,   22, 0x0a,
     401,  331,   22,   22, 0x0a,
     441,  331,   22,   22, 0x0a,
     463,  331,   22,   22, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_DisplaySettingsWidget[] = {
    "DisplaySettingsWidget\0\0updateParameters()\0"
    "untransformedTraceLineColor()\0"
    "untransforemdTraceDotColor()\0"
    "untransformedMeasurementPointColor()\0"
    "palatronDotColor()\0palatronBoxColor()\0"
    "transformedBackground()\0"
    "transformedTraceLineColor()\0"
    "transforemdTraceDotColor()\0"
    "transformedMeasurementPointColor()\0"
    "transformedPalatronDotColor()\0fanColor()\0"
    "size\0untransformedTraceLineWidth(int)\0"
    "untransforemdTraceDotWidth(int)\0"
    "untransformedMeasurementPointWidth(int)\0"
    "palatronDotWidth(int)\0palatronBoxWidth(int)\0"
};

const QMetaObject DisplaySettingsWidget::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DisplaySettingsWidget,
      qt_meta_data_DisplaySettingsWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DisplaySettingsWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DisplaySettingsWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DisplaySettingsWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DisplaySettingsWidget))
        return static_cast<void*>(const_cast< DisplaySettingsWidget*>(this));
    return QDialog::qt_metacast(_clname);
}

int DisplaySettingsWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updateParameters(); break;
        case 1: untransformedTraceLineColor(); break;
        case 2: untransforemdTraceDotColor(); break;
        case 3: untransformedMeasurementPointColor(); break;
        case 4: palatronDotColor(); break;
        case 5: palatronBoxColor(); break;
        case 6: transformedBackground(); break;
        case 7: transformedTraceLineColor(); break;
        case 8: transforemdTraceDotColor(); break;
        case 9: transformedMeasurementPointColor(); break;
        case 10: transformedPalatronDotColor(); break;
        case 11: fanColor(); break;
        case 12: untransformedTraceLineWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: untransforemdTraceDotWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: untransformedMeasurementPointWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: palatronDotWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: palatronBoxWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void DisplaySettingsWidget::updateParameters()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
