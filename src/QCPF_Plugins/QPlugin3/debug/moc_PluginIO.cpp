/****************************************************************************
** Meta object code from reading C++ file 'PluginIO.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../PluginIO.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/qplugin.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PluginIO.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PluginIO_t {
    QByteArrayData data[3];
    char stringdata0[24];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PluginIO_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PluginIO_t qt_meta_stringdata_PluginIO = {
    {
QT_MOC_LITERAL(0, 0, 8), // "PluginIO"
QT_MOC_LITERAL(1, 9, 13), // "handleTimeout"
QT_MOC_LITERAL(2, 23, 0) // ""

    },
    "PluginIO\0handleTimeout\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PluginIO[] = {

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
       1,    0,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void PluginIO::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PluginIO *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->handleTimeout(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject PluginIO::staticMetaObject = { {
    &QCPF_NonSystemPluginModel::staticMetaObject,
    qt_meta_stringdata_PluginIO.data,
    qt_meta_data_PluginIO,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PluginIO::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PluginIO::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PluginIO.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "io.qt.interface.plugin_interface"))
        return static_cast< Plugin_Interface*>(this);
    return QCPF_NonSystemPluginModel::qt_metacast(_clname);
}

int PluginIO::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPF_NonSystemPluginModel::qt_metacall(_c, _id, _a);
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
    0x03,  0x68,  'P',  'l',  'u',  'g',  'i',  'n', 
    'I',  'O', 
    // "MetaData"
    0x04,  0xa1,  0x64,  'K',  'e',  'y',  's',  0x80, 
    0xff, 
};
QT_MOC_EXPORT_PLUGIN(PluginIO, PluginIO)

QT_WARNING_POP
QT_END_MOC_NAMESPACE
