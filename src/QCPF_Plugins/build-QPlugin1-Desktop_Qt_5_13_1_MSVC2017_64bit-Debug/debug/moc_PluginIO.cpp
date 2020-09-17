/****************************************************************************
** Meta object code from reading C++ file 'PluginIO.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../QPlugin1/PluginIO.h"
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
    QByteArrayData data[13];
    char stringdata0[150];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PluginIO_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PluginIO_t qt_meta_stringdata_PluginIO = {
    {
QT_MOC_LITERAL(0, 0, 8), // "PluginIO"
QT_MOC_LITERAL(1, 9, 11), // "slot_Plugin"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 6), // "arg_in"
QT_MOC_LITERAL(4, 29, 9), // "QVariant&"
QT_MOC_LITERAL(5, 39, 7), // "arg_out"
QT_MOC_LITERAL(6, 47, 11), // "slot_Action"
QT_MOC_LITERAL(7, 59, 10), // "checkState"
QT_MOC_LITERAL(8, 70, 16), // "OnCoreInitialize"
QT_MOC_LITERAL(9, 87, 21), // "OnViewModelInitialize"
QT_MOC_LITERAL(10, 109, 13), // "OnViewCreated"
QT_MOC_LITERAL(11, 123, 12), // "OnViewLoaded"
QT_MOC_LITERAL(12, 136, 13) // "OnViewClosing"

    },
    "PluginIO\0slot_Plugin\0\0arg_in\0QVariant&\0"
    "arg_out\0slot_Action\0checkState\0"
    "OnCoreInitialize\0OnViewModelInitialize\0"
    "OnViewCreated\0OnViewLoaded\0OnViewClosing"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PluginIO[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   49,    2, 0x0a /* Public */,
       6,    1,   54,    2, 0x0a /* Public */,
       8,    0,   57,    2, 0x0a /* Public */,
       9,    0,   58,    2, 0x0a /* Public */,
      10,    0,   59,    2, 0x0a /* Public */,
      11,    0,   60,    2, 0x0a /* Public */,
      12,    0,   61,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Int, QMetaType::QVariant, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,

       0        // eod
};

void PluginIO::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PluginIO *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { int _r = _t->slot_Plugin((*reinterpret_cast< QVariant(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 1: _t->slot_Action((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: { int _r = _t->OnCoreInitialize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 3: { int _r = _t->OnViewModelInitialize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 4: { int _r = _t->OnViewCreated();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 5: { int _r = _t->OnViewLoaded();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 6: { int _r = _t->OnViewClosing();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PluginIO::staticMetaObject = { {
    &PluginInterface::staticMetaObject,
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
    if (!strcmp(_clname, "io.qt.interface.pluginInterface"))
        return static_cast< PluginInterface*>(this);
    return PluginInterface::qt_metacast(_clname);
}

int PluginIO::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PluginInterface::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
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
    0x02,  0x78,  0x1f,  'i',  'o',  '.',  'q',  't', 
    '.',  'i',  'n',  't',  'e',  'r',  'f',  'a', 
    'c',  'e',  '.',  'p',  'l',  'u',  'g',  'i', 
    'n',  'I',  'n',  't',  'e',  'r',  'f',  'a', 
    'c',  'e', 
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
