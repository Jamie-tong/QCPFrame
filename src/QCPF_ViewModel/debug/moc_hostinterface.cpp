/****************************************************************************
** Meta object code from reading C++ file 'hostinterface.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../interface/hostinterface.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'hostinterface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QCPF_Interface_t {
    QByteArrayData data[6];
    char stringdata0[122];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QCPF_Interface_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QCPF_Interface_t qt_meta_stringdata_QCPF_Interface = {
    {
QT_MOC_LITERAL(0, 0, 14), // "QCPF_Interface"
QT_MOC_LITERAL(1, 15, 20), // "HostSignal_OnLoading"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 29), // "HostSignal_OnMainFrameCreated"
QT_MOC_LITERAL(4, 67, 26), // "HostSignal_OnMainFrameLoad"
QT_MOC_LITERAL(5, 94, 27) // "HostSignal_OnMainFrameClose"

    },
    "QCPF_Interface\0HostSignal_OnLoading\0"
    "\0HostSignal_OnMainFrameCreated\0"
    "HostSignal_OnMainFrameLoad\0"
    "HostSignal_OnMainFrameClose"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QCPF_Interface[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,
       4,    0,   36,    2, 0x06 /* Public */,
       5,    0,   37,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,

       0        // eod
};

void QCPF_Interface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QCPF_Interface *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { int _r = _t->HostSignal_OnLoading();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 1: { int _r = _t->HostSignal_OnMainFrameCreated();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 2: { int _r = _t->HostSignal_OnMainFrameLoad();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 3: { int _r = _t->HostSignal_OnMainFrameClose();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = int (QCPF_Interface::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QCPF_Interface::HostSignal_OnLoading)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = int (QCPF_Interface::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QCPF_Interface::HostSignal_OnMainFrameCreated)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = int (QCPF_Interface::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QCPF_Interface::HostSignal_OnMainFrameLoad)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = int (QCPF_Interface::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QCPF_Interface::HostSignal_OnMainFrameClose)) {
                *result = 3;
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
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
int QCPF_Interface::HostSignal_OnLoading()
{
    int _t0{};
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t0))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
    return _t0;
}

// SIGNAL 1
int QCPF_Interface::HostSignal_OnMainFrameCreated()
{
    int _t0{};
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t0))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
    return _t0;
}

// SIGNAL 2
int QCPF_Interface::HostSignal_OnMainFrameLoad()
{
    int _t0{};
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t0))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
    return _t0;
}

// SIGNAL 3
int QCPF_Interface::HostSignal_OnMainFrameClose()
{
    int _t0{};
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t0))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
    return _t0;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
