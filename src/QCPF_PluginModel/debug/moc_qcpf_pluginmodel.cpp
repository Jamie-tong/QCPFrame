/****************************************************************************
** Meta object code from reading C++ file 'qcpf_pluginmodel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../qcpf_pluginmodel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/qplugin.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qcpf_pluginmodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QCPF_PluginModel_t {
    QByteArrayData data[4];
    char stringdata0[41];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QCPF_PluginModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QCPF_PluginModel_t qt_meta_stringdata_QCPF_PluginModel = {
    {
QT_MOC_LITERAL(0, 0, 16), // "QCPF_PluginModel"
QT_MOC_LITERAL(1, 17, 11), // "slot_Action"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 10) // "checkState"

    },
    "QCPF_PluginModel\0slot_Action\0\0checkState"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QCPF_PluginModel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,

       0        // eod
};

void QCPF_PluginModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QCPF_PluginModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_Action((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QCPF_PluginModel::staticMetaObject = { {
    &Plugin_Interface::staticMetaObject,
    qt_meta_stringdata_QCPF_PluginModel.data,
    qt_meta_data_QCPF_PluginModel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QCPF_PluginModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCPF_PluginModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCPF_PluginModel.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "io.qt.interface.plugin_interface"))
        return static_cast< Plugin_Interface*>(this);
    return Plugin_Interface::qt_metacast(_clname);
}

int QCPF_PluginModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Plugin_Interface::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

QT_PLUGIN_METADATA_SECTION
static constexpr unsigned char qt_pluginMetaData[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', '!',
    // metadata version, Qt version, architectural requirements
    0, QT_VERSION_MAJOR, QT_VERSION_MINOR, qPluginArchRequirements(),
    0xbf, 
    // "IID"
    0x02,  0x78,  0x20,  'i',  'o',  '.',  'q',  't', 
    '.',  'i',  'n',  't',  'e',  'r',  'f',  'a', 
    'c',  'e',  '.',  'p',  'l',  'u',  'g',  'i', 
    'n',  '_',  'i',  'n',  't',  'e',  'r',  'f', 
    'a',  'c',  'e', 
    // "className"
    0x03,  0x70,  'Q',  'C',  'P',  'F',  '_',  'P', 
    'l',  'u',  'g',  'i',  'n',  'M',  'o',  'd', 
    'e',  'l', 
    // "MetaData"
    0x04,  0xa1,  0x64,  'K',  'e',  'y',  's',  0x80, 
    0xff, 
};
QT_MOC_EXPORT_PLUGIN(QCPF_PluginModel, QCPF_PluginModel)

QT_WARNING_POP
QT_END_MOC_NAMESPACE
