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
    QByteArrayData data[6];
    char stringdata0[66];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PluginIO_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PluginIO_t qt_meta_stringdata_PluginIO = {
    {
QT_MOC_LITERAL(0, 0, 8), // "PluginIO"
QT_MOC_LITERAL(1, 9, 20), // "StartShowViewVersion"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 14), // "slot_InputInfo"
QT_MOC_LITERAL(4, 46, 14), // "tagOutputInfo&"
QT_MOC_LITERAL(5, 61, 4) // "info"

    },
    "PluginIO\0StartShowViewVersion\0\0"
    "slot_InputInfo\0tagOutputInfo&\0info"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PluginIO[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   25,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Int, 0x80000000 | 4,    5,

       0        // eod
};

void PluginIO::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PluginIO *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->StartShowViewVersion(); break;
        case 1: { int _r = _t->slot_InputInfo((*reinterpret_cast< tagOutputInfo(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PluginIO::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PluginIO::StartShowViewVersion)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PluginIO::staticMetaObject = { {
    &QCPF_SystemPluginModel::staticMetaObject,
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
    return QCPF_SystemPluginModel::qt_metacast(_clname);
}

int PluginIO::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCPF_SystemPluginModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void PluginIO::StartShowViewVersion()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
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
