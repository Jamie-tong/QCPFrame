/****************************************************************************
** Meta object code from reading C++ file 'qcpf_viewmodel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../qcpf_viewmodel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qcpf_viewmodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QCPF_ViewModel_t {
    QByteArrayData data[15];
    char stringdata0[183];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QCPF_ViewModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QCPF_ViewModel_t qt_meta_stringdata_QCPF_ViewModel = {
    {
QT_MOC_LITERAL(0, 0, 14), // "QCPF_ViewModel"
QT_MOC_LITERAL(1, 15, 14), // "sig_OutputInfo"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 14), // "tagOutputInfo&"
QT_MOC_LITERAL(4, 46, 4), // "info"
QT_MOC_LITERAL(5, 51, 15), // "slot_Initialize"
QT_MOC_LITERAL(6, 67, 4), // "user"
QT_MOC_LITERAL(7, 72, 3), // "pwd"
QT_MOC_LITERAL(8, 76, 7), // "extInfo"
QT_MOC_LITERAL(9, 84, 19), // "slot_LoadConfigFile"
QT_MOC_LITERAL(10, 104, 16), // "viewConfigModel&"
QT_MOC_LITERAL(11, 121, 6), // "config"
QT_MOC_LITERAL(12, 128, 19), // "slot_SaveConfigFile"
QT_MOC_LITERAL(13, 148, 16), // "slot_ApplyConfig"
QT_MOC_LITERAL(14, 165, 17) // "slot_CancelConfig"

    },
    "QCPF_ViewModel\0sig_OutputInfo\0\0"
    "tagOutputInfo&\0info\0slot_Initialize\0"
    "user\0pwd\0extInfo\0slot_LoadConfigFile\0"
    "viewConfigModel&\0config\0slot_SaveConfigFile\0"
    "slot_ApplyConfig\0slot_CancelConfig"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QCPF_ViewModel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    3,   47,    2, 0x0a /* Public */,
       9,    1,   54,    2, 0x0a /* Public */,
      12,    0,   57,    2, 0x0a /* Public */,
      13,    0,   58,    2, 0x0a /* Public */,
      14,    0,   59,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Int, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::QString,    6,    7,    8,
    QMetaType::Int, 0x80000000 | 10,   11,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,

       0        // eod
};

void QCPF_ViewModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QCPF_ViewModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { int _r = _t->sig_OutputInfo((*reinterpret_cast< tagOutputInfo(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 1: { int _r = _t->slot_Initialize((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 2: { int _r = _t->slot_LoadConfigFile((*reinterpret_cast< viewConfigModel(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 3: { int _r = _t->slot_SaveConfigFile();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 4: { int _r = _t->slot_ApplyConfig();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 5: { int _r = _t->slot_CancelConfig();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = int (QCPF_ViewModel::*)(tagOutputInfo & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QCPF_ViewModel::sig_OutputInfo)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QCPF_ViewModel::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_QCPF_ViewModel.data,
    qt_meta_data_QCPF_ViewModel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QCPF_ViewModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPF_ViewModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPF_ViewModel.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QCPF_ViewModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
int QCPF_ViewModel::sig_OutputInfo(tagOutputInfo & _t1)
{
    int _t0{};
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t0))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
    return _t0;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
