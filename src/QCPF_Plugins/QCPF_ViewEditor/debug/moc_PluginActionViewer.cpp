/****************************************************************************
** Meta object code from reading C++ file 'PluginActionViewer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../PluginActionViewer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PluginActionViewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PluginActionViewer_t {
    QByteArrayData data[8];
    char stringdata0[163];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PluginActionViewer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PluginActionViewer_t qt_meta_stringdata_PluginActionViewer = {
    {
QT_MOC_LITERAL(0, 0, 18), // "PluginActionViewer"
QT_MOC_LITERAL(1, 19, 14), // "slot_OnULoaded"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 27), // "on_tabWidget_currentChanged"
QT_MOC_LITERAL(4, 63, 5), // "index"
QT_MOC_LITERAL(5, 69, 33), // "on_cbPluginID_currentIndexCha..."
QT_MOC_LITERAL(6, 103, 37), // "on_cbPluginAction_currentInde..."
QT_MOC_LITERAL(7, 141, 21) // "on_buttonBox_accepted"

    },
    "PluginActionViewer\0slot_OnULoaded\0\0"
    "on_tabWidget_currentChanged\0index\0"
    "on_cbPluginID_currentIndexChanged\0"
    "on_cbPluginAction_currentIndexChanged\0"
    "on_buttonBox_accepted"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PluginActionViewer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x08 /* Private */,
       3,    1,   40,    2, 0x08 /* Private */,
       5,    1,   43,    2, 0x08 /* Private */,
       6,    1,   46,    2, 0x08 /* Private */,
       7,    0,   49,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,

       0        // eod
};

void PluginActionViewer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PluginActionViewer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_OnULoaded(); break;
        case 1: _t->on_tabWidget_currentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_cbPluginID_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_cbPluginAction_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_buttonBox_accepted(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PluginActionViewer::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_PluginActionViewer.data,
    qt_meta_data_PluginActionViewer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PluginActionViewer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PluginActionViewer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PluginActionViewer.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int PluginActionViewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
