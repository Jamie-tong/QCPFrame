/****************************************************************************
** Meta object code from reading C++ file 'SystemManager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../SystemManager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SystemManager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SystemManager_t {
    QByteArrayData data[16];
    char stringdata0[255];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SystemManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SystemManager_t qt_meta_stringdata_SystemManager = {
    {
QT_MOC_LITERAL(0, 0, 13), // "SystemManager"
QT_MOC_LITERAL(1, 14, 8), // "sig_Save"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 10), // "sig_Cancel"
QT_MOC_LITERAL(4, 35, 9), // "sig_Apply"
QT_MOC_LITERAL(5, 45, 15), // "sig_SelAllOrNot"
QT_MOC_LITERAL(6, 61, 4), // "flag"
QT_MOC_LITERAL(7, 66, 14), // "slot_OnULoaded"
QT_MOC_LITERAL(8, 81, 16), // "slot_SelAllOrNot"
QT_MOC_LITERAL(9, 98, 16), // "on_btnOk_clicked"
QT_MOC_LITERAL(10, 115, 20), // "on_btnCancel_clicked"
QT_MOC_LITERAL(11, 136, 19), // "on_btnApply_clicked"
QT_MOC_LITERAL(12, 156, 28), // "on_pluginCheckbox_selChanged"
QT_MOC_LITERAL(13, 185, 5), // "state"
QT_MOC_LITERAL(14, 191, 30), // "on_btnOrigPluginMoveUp_clicked"
QT_MOC_LITERAL(15, 222, 32) // "on_btnOrigPluginMoveDown_clicked"

    },
    "SystemManager\0sig_Save\0\0sig_Cancel\0"
    "sig_Apply\0sig_SelAllOrNot\0flag\0"
    "slot_OnULoaded\0slot_SelAllOrNot\0"
    "on_btnOk_clicked\0on_btnCancel_clicked\0"
    "on_btnApply_clicked\0on_pluginCheckbox_selChanged\0"
    "state\0on_btnOrigPluginMoveUp_clicked\0"
    "on_btnOrigPluginMoveDown_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SystemManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,
       3,    0,   75,    2, 0x06 /* Public */,
       4,    0,   76,    2, 0x06 /* Public */,
       5,    1,   77,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   80,    2, 0x08 /* Private */,
       8,    1,   81,    2, 0x08 /* Private */,
       9,    0,   84,    2, 0x08 /* Private */,
      10,    0,   85,    2, 0x08 /* Private */,
      11,    0,   86,    2, 0x08 /* Private */,
      12,    1,   87,    2, 0x08 /* Private */,
      14,    0,   90,    2, 0x08 /* Private */,
      15,    0,   91,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Bool,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SystemManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SystemManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { int _r = _t->sig_Save();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 1: { int _r = _t->sig_Cancel();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 2: { int _r = _t->sig_Apply();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 3: _t->sig_SelAllOrNot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->slot_OnULoaded(); break;
        case 5: _t->slot_SelAllOrNot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->on_btnOk_clicked(); break;
        case 7: _t->on_btnCancel_clicked(); break;
        case 8: _t->on_btnApply_clicked(); break;
        case 9: _t->on_pluginCheckbox_selChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->on_btnOrigPluginMoveUp_clicked(); break;
        case 11: _t->on_btnOrigPluginMoveDown_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = int (SystemManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemManager::sig_Save)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = int (SystemManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemManager::sig_Cancel)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = int (SystemManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemManager::sig_Apply)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SystemManager::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemManager::sig_SelAllOrNot)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SystemManager::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_SystemManager.data,
    qt_meta_data_SystemManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SystemManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SystemManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SystemManager.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int SystemManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
int SystemManager::sig_Save()
{
    int _t0{};
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t0))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
    return _t0;
}

// SIGNAL 1
int SystemManager::sig_Cancel()
{
    int _t0{};
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t0))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
    return _t0;
}

// SIGNAL 2
int SystemManager::sig_Apply()
{
    int _t0{};
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t0))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
    return _t0;
}

// SIGNAL 3
void SystemManager::sig_SelAllOrNot(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
