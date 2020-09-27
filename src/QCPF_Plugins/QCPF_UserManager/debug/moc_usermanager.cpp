/****************************************************************************
** Meta object code from reading C++ file 'usermanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../usermanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'usermanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_UserManager_t {
    QByteArrayData data[11];
    char stringdata0[203];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UserManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UserManager_t qt_meta_stringdata_UserManager = {
    {
QT_MOC_LITERAL(0, 0, 11), // "UserManager"
QT_MOC_LITERAL(1, 12, 14), // "slot_OnULoaded"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 25), // "on_btnAddUserInfo_clicked"
QT_MOC_LITERAL(4, 54, 16), // "on_btnOk_clicked"
QT_MOC_LITERAL(5, 71, 20), // "on_btnCancel_clicked"
QT_MOC_LITERAL(6, 92, 29), // "on_btnReplaceUserInfo_clicked"
QT_MOC_LITERAL(7, 122, 28), // "on_btnDeleteUserInfo_clicked"
QT_MOC_LITERAL(8, 151, 28), // "on_tableUserInfo_itemClicked"
QT_MOC_LITERAL(9, 180, 17), // "QTableWidgetItem*"
QT_MOC_LITERAL(10, 198, 4) // "item"

    },
    "UserManager\0slot_OnULoaded\0\0"
    "on_btnAddUserInfo_clicked\0on_btnOk_clicked\0"
    "on_btnCancel_clicked\0on_btnReplaceUserInfo_clicked\0"
    "on_btnDeleteUserInfo_clicked\0"
    "on_tableUserInfo_itemClicked\0"
    "QTableWidgetItem*\0item"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UserManager[] = {

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
       1,    0,   49,    2, 0x08 /* Private */,
       3,    0,   50,    2, 0x08 /* Private */,
       4,    0,   51,    2, 0x08 /* Private */,
       5,    0,   52,    2, 0x08 /* Private */,
       6,    0,   53,    2, 0x08 /* Private */,
       7,    0,   54,    2, 0x08 /* Private */,
       8,    1,   55,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,

       0        // eod
};

void UserManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UserManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_OnULoaded(); break;
        case 1: _t->on_btnAddUserInfo_clicked(); break;
        case 2: _t->on_btnOk_clicked(); break;
        case 3: _t->on_btnCancel_clicked(); break;
        case 4: _t->on_btnReplaceUserInfo_clicked(); break;
        case 5: _t->on_btnDeleteUserInfo_clicked(); break;
        case 6: _t->on_tableUserInfo_itemClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject UserManager::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_UserManager.data,
    qt_meta_data_UserManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *UserManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UserManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UserManager.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int UserManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
