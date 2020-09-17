/****************************************************************************
** Meta object code from reading C++ file 'plugininterface.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../interface/plugininterface.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'plugininterface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PluginInterface_t {
    QByteArrayData data[16];
    char stringdata0[181];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PluginInterface_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PluginInterface_t qt_meta_stringdata_PluginInterface = {
    {
QT_MOC_LITERAL(0, 0, 15), // "PluginInterface"
QT_MOC_LITERAL(1, 16, 10), // "sig_Plugin"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 6), // "arg_in"
QT_MOC_LITERAL(4, 35, 9), // "QVariant&"
QT_MOC_LITERAL(5, 45, 7), // "arg_out"
QT_MOC_LITERAL(6, 53, 14), // "sig_OutputInfo"
QT_MOC_LITERAL(7, 68, 14), // "tagOutputInfo&"
QT_MOC_LITERAL(8, 83, 4), // "info"
QT_MOC_LITERAL(9, 88, 11), // "slot_Plugin"
QT_MOC_LITERAL(10, 100, 11), // "slot_Action"
QT_MOC_LITERAL(11, 112, 10), // "checkState"
QT_MOC_LITERAL(12, 123, 16), // "OnCoreInitialize"
QT_MOC_LITERAL(13, 140, 13), // "OnViewCreated"
QT_MOC_LITERAL(14, 154, 12), // "OnViewLoaded"
QT_MOC_LITERAL(15, 167, 13) // "OnViewClosing"

    },
    "PluginInterface\0sig_Plugin\0\0arg_in\0"
    "QVariant&\0arg_out\0sig_OutputInfo\0"
    "tagOutputInfo&\0info\0slot_Plugin\0"
    "slot_Action\0checkState\0OnCoreInitialize\0"
    "OnViewCreated\0OnViewLoaded\0OnViewClosing"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PluginInterface[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x06 /* Public */,
       6,    1,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    2,   62,    2, 0x0a /* Public */,
      10,    1,   67,    2, 0x0a /* Public */,
      12,    0,   70,    2, 0x0a /* Public */,
      13,    0,   71,    2, 0x0a /* Public */,
      14,    0,   72,    2, 0x0a /* Public */,
      15,    0,   73,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Int, QMetaType::QVariant, 0x80000000 | 4,    3,    5,
    QMetaType::Int, 0x80000000 | 7,    8,

 // slots: parameters
    QMetaType::Int, QMetaType::QVariant, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,

       0        // eod
};

void PluginInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PluginInterface *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { int _r = _t->sig_Plugin((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 1: { int _r = _t->sig_OutputInfo((*reinterpret_cast< tagOutputInfo(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 2: { int _r = _t->slot_Plugin((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 3: _t->slot_Action((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: { int _r = _t->OnCoreInitialize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 5: { int _r = _t->OnViewCreated();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 6: { int _r = _t->OnViewLoaded();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 7: { int _r = _t->OnViewClosing();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = int (PluginInterface::*)(QVariant , QVariant & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PluginInterface::sig_Plugin)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = int (PluginInterface::*)(tagOutputInfo & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PluginInterface::sig_OutputInfo)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PluginInterface::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_PluginInterface.data,
    qt_meta_data_PluginInterface,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PluginInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PluginInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PluginInterface.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int PluginInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
int PluginInterface::sig_Plugin(QVariant _t1, QVariant & _t2)
{
    int _t0{};
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t0))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
    return _t0;
}

// SIGNAL 1
int PluginInterface::sig_OutputInfo(tagOutputInfo & _t1)
{
    int _t0{};
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t0))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
    return _t0;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
