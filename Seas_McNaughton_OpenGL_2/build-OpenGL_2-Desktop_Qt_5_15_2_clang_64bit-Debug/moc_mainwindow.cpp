/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Code/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[13];
    char stringdata0[275];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 30), // "on_ResetRotationButton_clicked"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 7), // "checked"
QT_MOC_LITERAL(4, 51, 29), // "on_RotationDialX_valueChanged"
QT_MOC_LITERAL(5, 81, 5), // "value"
QT_MOC_LITERAL(6, 87, 29), // "on_RotationDialY_valueChanged"
QT_MOC_LITERAL(7, 117, 29), // "on_RotationDialZ_valueChanged"
QT_MOC_LITERAL(8, 147, 27), // "on_ResetScaleButton_clicked"
QT_MOC_LITERAL(9, 175, 27), // "on_ScaleSlider_valueChanged"
QT_MOC_LITERAL(10, 203, 22), // "on_PhongButton_toggled"
QT_MOC_LITERAL(11, 226, 23), // "on_NormalButton_toggled"
QT_MOC_LITERAL(12, 250, 24) // "on_GouraudButton_toggled"

    },
    "MainWindow\0on_ResetRotationButton_clicked\0"
    "\0checked\0on_RotationDialX_valueChanged\0"
    "value\0on_RotationDialY_valueChanged\0"
    "on_RotationDialZ_valueChanged\0"
    "on_ResetScaleButton_clicked\0"
    "on_ScaleSlider_valueChanged\0"
    "on_PhongButton_toggled\0on_NormalButton_toggled\0"
    "on_GouraudButton_toggled"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x08 /* Private */,
       4,    1,   62,    2, 0x08 /* Private */,
       6,    1,   65,    2, 0x08 /* Private */,
       7,    1,   68,    2, 0x08 /* Private */,
       8,    1,   71,    2, 0x08 /* Private */,
       9,    1,   74,    2, 0x08 /* Private */,
      10,    1,   77,    2, 0x08 /* Private */,
      11,    1,   80,    2, 0x08 /* Private */,
      12,    1,   83,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_ResetRotationButton_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->on_RotationDialX_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_RotationDialY_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_RotationDialZ_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_ResetScaleButton_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->on_ScaleSlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_PhongButton_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->on_NormalButton_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->on_GouraudButton_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
