/****************************************************************************
** Meta object code from reading C++ file 'coreinterface.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../interface/coreinterface.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'coreinterface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QCPF_Interface_t {
    QByteArrayData data[17];
    char stringdata0[184];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QCPF_Interface_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QCPF_Interface_t qt_meta_stringdata_QCPF_Interface = {
    {
QT_MOC_LITERAL(0, 0, 14), // "QCPF_Interface"
QT_MOC_LITERAL(1, 15, 14), // "sig_OutputInfo"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 14), // "tagOutputInfo&"
QT_MOC_LITERAL(4, 46, 4), // "info"
QT_MOC_LITERAL(5, 51, 8), // "sig_Core"
QT_MOC_LITERAL(6, 60, 6), // "arg_in"
QT_MOC_LITERAL(7, 67, 9), // "QVariant&"
QT_MOC_LITERAL(8, 77, 7), // "arg_out"
QT_MOC_LITERAL(9, 85, 14), // "slot_InputInfo"
QT_MOC_LITERAL(10, 100, 9), // "slot_Core"
QT_MOC_LITERAL(11, 110, 21), // "Invoke_PluginFunction"
QT_MOC_LITERAL(12, 132, 10), // "PluginType"
QT_MOC_LITERAL(13, 143, 5), // "pType"
QT_MOC_LITERAL(14, 149, 8), // "pluginID"
QT_MOC_LITERAL(15, 158, 18), // "pluginFunctionName"
QT_MOC_LITERAL(16, 177, 6) // "copyID"

    },
    "QCPF_Interface\0sig_OutputInfo\0\0"
    "tagOutputInfo&\0info\0sig_Core\0arg_in\0"
    "QVariant&\0arg_out\0slot_InputInfo\0"
    "slot_Core\0Invoke_PluginFunction\0"
    "PluginType\0pType\0pluginID\0pluginFunctionName\0"
    "copyID"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QCPF_Interface[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       5,    2,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   52,    2, 0x0a /* Public */,
      10,    2,   55,    2, 0x0a /* Public */,
      11,    5,   60,    2, 0x0a /* Public */,
      11,    6,   71,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Int, 0x80000000 | 3,    4,
    QMetaType::Int, QMetaType::QVariant, 0x80000000 | 7,    6,    8,

 // slots: parameters
    QMetaType::Int, 0x80000000 | 3,    4,
    QMetaType::Int, QMetaType::QVariant, 0x80000000 | 7,    6,    8,
    QMetaType::Int, 0x80000000 | 12, QMetaType::QString, QMetaType::QString, QMetaType::QVariant, 0x80000000 | 7,   13,   14,   15,    6,    8,
    QMetaType::Int, 0x80000000 | 12, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QVariant, 0x80000000 | 7,   13,   14,   16,   15,    6,    8,

       0        // eod
};

void QCPF_Interface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QCPF_Interface *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { int _r = _t->sig_OutputInfo((*reinterpret_cast< tagOutputInfo(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 1: { int _r = _t->sig_Core((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 2: { int _r = _t->slot_InputInfo((*reinterpret_cast< tagOutputInfo(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 3: { int _r = _t->slot_Core((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 4: { int _r = _t->Invoke_PluginFunction((*reinterpret_cast< PluginType(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QVariant(*)>(_a[4])),(*reinterpret_cast< QVariant(*)>(_a[5])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 5: { int _r = _t->Invoke_PluginFunction((*reinterpret_cast< PluginType(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QVariant(*)>(_a[5])),(*reinterpret_cast< QVariant(*)>(_a[6])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = int (QCPF_Interface::*)(tagOutputInfo & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QCPF_Interface::sig_OutputInfo)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = int (QCPF_Interface::*)(QVariant , QVariant & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QCPF_Interface::sig_Core)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QCPF_Interface::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_QCPF_Interface.data,
    qt_meta_data_QCPF_Interface,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QCPF_Interface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPF_Interface::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPF_Interface.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QCPF_Interface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
int QCPF_Interface::sig_OutputInfo(tagOutputInfo & _t1)
{
    int _t0{};
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t0))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
    return _t0;
}

// SIGNAL 1
int QCPF_Interface::sig_Core(QVariant _t1, QVariant & _t2)
{
    int _t0{};
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t0))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
    return _t0;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
