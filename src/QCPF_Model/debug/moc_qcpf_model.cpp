/****************************************************************************
** Meta object code from reading C++ file 'qcpf_model.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../qcpf_model.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qcpf_model.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QCPF_Model_t {
    QByteArrayData data[32];
    char stringdata0[415];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QCPF_Model_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QCPF_Model_t qt_meta_stringdata_QCPF_Model = {
    {
QT_MOC_LITERAL(0, 0, 10), // "QCPF_Model"
QT_MOC_LITERAL(1, 11, 14), // "sig_OutputInfo"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 14), // "tagOutputInfo&"
QT_MOC_LITERAL(4, 42, 4), // "info"
QT_MOC_LITERAL(5, 47, 8), // "sig_Core"
QT_MOC_LITERAL(6, 56, 6), // "arg_in"
QT_MOC_LITERAL(7, 63, 9), // "QVariant&"
QT_MOC_LITERAL(8, 73, 7), // "arg_out"
QT_MOC_LITERAL(9, 81, 27), // "sig_PluginSelOrNSelFinished"
QT_MOC_LITERAL(10, 109, 12), // "origPluginID"
QT_MOC_LITERAL(11, 122, 5), // "isSel"
QT_MOC_LITERAL(12, 128, 17), // "sig_CloneFinished"
QT_MOC_LITERAL(13, 146, 7), // "isExist"
QT_MOC_LITERAL(14, 154, 6), // "copyID"
QT_MOC_LITERAL(15, 161, 13), // "copyAlisaName"
QT_MOC_LITERAL(16, 175, 11), // "copyComment"
QT_MOC_LITERAL(17, 187, 24), // "sig_DestroyCloneFinished"
QT_MOC_LITERAL(18, 212, 14), // "slot_InputInfo"
QT_MOC_LITERAL(19, 227, 9), // "slot_Core"
QT_MOC_LITERAL(20, 237, 21), // "Invoke_PluginFunction"
QT_MOC_LITERAL(21, 259, 10), // "PluginType"
QT_MOC_LITERAL(22, 270, 5), // "pType"
QT_MOC_LITERAL(23, 276, 8), // "pluginID"
QT_MOC_LITERAL(24, 285, 18), // "pluginFunctionName"
QT_MOC_LITERAL(25, 304, 15), // "slot_Initialize"
QT_MOC_LITERAL(26, 320, 19), // "slot_LoadConfigFile"
QT_MOC_LITERAL(27, 340, 12), // "ConfigModel&"
QT_MOC_LITERAL(28, 353, 6), // "config"
QT_MOC_LITERAL(29, 360, 19), // "slot_SaveConfigFile"
QT_MOC_LITERAL(30, 380, 16), // "slot_ApplyConfig"
QT_MOC_LITERAL(31, 397, 17) // "slot_CancelConfig"

    },
    "QCPF_Model\0sig_OutputInfo\0\0tagOutputInfo&\0"
    "info\0sig_Core\0arg_in\0QVariant&\0arg_out\0"
    "sig_PluginSelOrNSelFinished\0origPluginID\0"
    "isSel\0sig_CloneFinished\0isExist\0copyID\0"
    "copyAlisaName\0copyComment\0"
    "sig_DestroyCloneFinished\0slot_InputInfo\0"
    "slot_Core\0Invoke_PluginFunction\0"
    "PluginType\0pType\0pluginID\0pluginFunctionName\0"
    "slot_Initialize\0slot_LoadConfigFile\0"
    "ConfigModel&\0config\0slot_SaveConfigFile\0"
    "slot_ApplyConfig\0slot_CancelConfig"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QCPF_Model[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,
       5,    2,   87,    2, 0x06 /* Public */,
       9,    2,   92,    2, 0x06 /* Public */,
      12,    5,   97,    2, 0x06 /* Public */,
      17,    2,  108,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      18,    1,  113,    2, 0x0a /* Public */,
      19,    2,  116,    2, 0x0a /* Public */,
      20,    5,  121,    2, 0x0a /* Public */,
      20,    6,  132,    2, 0x0a /* Public */,
      25,    0,  145,    2, 0x0a /* Public */,
      26,    1,  146,    2, 0x0a /* Public */,
      29,    0,  149,    2, 0x0a /* Public */,
      30,    0,  150,    2, 0x0a /* Public */,
      31,    0,  151,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Int, 0x80000000 | 3,    4,
    QMetaType::Int, QMetaType::QVariant, 0x80000000 | 7,    6,    8,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   10,   11,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   13,   10,   14,   15,   16,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   10,   14,

 // slots: parameters
    QMetaType::Int, 0x80000000 | 3,    4,
    QMetaType::Int, QMetaType::QVariant, 0x80000000 | 7,    6,    8,
    QMetaType::Int, 0x80000000 | 21, QMetaType::QString, QMetaType::QString, QMetaType::QVariant, 0x80000000 | 7,   22,   23,   24,    6,    8,
    QMetaType::Int, 0x80000000 | 21, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QVariant, 0x80000000 | 7,   22,   23,   14,   24,    6,    8,
    QMetaType::Int,
    QMetaType::Int, 0x80000000 | 27,   28,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,

       0        // eod
};

void QCPF_Model::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QCPF_Model *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { int _r = _t->sig_OutputInfo((*reinterpret_cast< tagOutputInfo(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 1: { int _r = _t->sig_Core((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 2: _t->sig_PluginSelOrNSelFinished((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 3: _t->sig_CloneFinished((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        case 4: _t->sig_DestroyCloneFinished((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 5: { int _r = _t->slot_InputInfo((*reinterpret_cast< tagOutputInfo(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 6: { int _r = _t->slot_Core((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 7: { int _r = _t->Invoke_PluginFunction((*reinterpret_cast< PluginType(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QVariant(*)>(_a[4])),(*reinterpret_cast< QVariant(*)>(_a[5])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 8: { int _r = _t->Invoke_PluginFunction((*reinterpret_cast< PluginType(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QVariant(*)>(_a[5])),(*reinterpret_cast< QVariant(*)>(_a[6])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 9: { int _r = _t->slot_Initialize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 10: { int _r = _t->slot_LoadConfigFile((*reinterpret_cast< ConfigModel(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 11: { int _r = _t->slot_SaveConfigFile();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 12: { int _r = _t->slot_ApplyConfig();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 13: { int _r = _t->slot_CancelConfig();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = int (QCPF_Model::*)(tagOutputInfo & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QCPF_Model::sig_OutputInfo)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = int (QCPF_Model::*)(QVariant , QVariant & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QCPF_Model::sig_Core)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (QCPF_Model::*)(QString , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QCPF_Model::sig_PluginSelOrNSelFinished)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (QCPF_Model::*)(bool , QString , QString , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QCPF_Model::sig_CloneFinished)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (QCPF_Model::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QCPF_Model::sig_DestroyCloneFinished)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QCPF_Model::staticMetaObject = { {
    &QCPF_Interface::staticMetaObject,
    qt_meta_stringdata_QCPF_Model.data,
    qt_meta_data_QCPF_Model,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QCPF_Model::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPF_Model::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPF_Model.stringdata0))
        return static_cast<void*>(this);
    return QCPF_Interface::qt_metacast(_clname);
}

int QCPF_Model::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPF_Interface::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
int QCPF_Model::sig_OutputInfo(tagOutputInfo & _t1)
{
    int _t0{};
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t0))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
    return _t0;
}

// SIGNAL 1
int QCPF_Model::sig_Core(QVariant _t1, QVariant & _t2)
{
    int _t0{};
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t0))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
    return _t0;
}

// SIGNAL 2
void QCPF_Model::sig_PluginSelOrNSelFinished(QString _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QCPF_Model::sig_CloneFinished(bool _t1, QString _t2, QString _t3, QString _t4, QString _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QCPF_Model::sig_DestroyCloneFinished(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
