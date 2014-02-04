/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Mon Feb 21 09:39:01 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      43,   11,   11,   11, 0x0a,
      54,   11,   11,   11, 0x0a,
      74,   11,   11,   11, 0x0a,
      93,   11,   11,   11, 0x0a,
     107,   11,   11,   11, 0x0a,
     121,   11,   11,   11, 0x0a,
     137,   11,   11,   11, 0x0a,
     150,   11,   11,   11, 0x0a,
     172,  165,   11,   11, 0x08,
     196,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0displayPluginSettingsUpdated()\0"
    "MainView()\0CreateProjectView()\0"
    "createNewProject()\0openProject()\0"
    "saveProject()\0saveProjectAs()\0"
    "exportData()\0closeProject()\0action\0"
    "tracerChanged(QAction*)\0sendGridToTracers()\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: displayPluginSettingsUpdated(); break;
        case 1: MainView(); break;
        case 2: CreateProjectView(); break;
        case 3: createNewProject(); break;
        case 4: openProject(); break;
        case 5: saveProject(); break;
        case 6: saveProjectAs(); break;
        case 7: exportData(); break;
        case 8: closeProject(); break;
        case 9: tracerChanged((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 10: sendGridToTracers(); break;
        default: ;
        }
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::displayPluginSettingsUpdated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
