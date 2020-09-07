/****************************************************************************
** Meta object code from reading C++ file 'formloading.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../formloading.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'formloading.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_formLoading_t {
    QByteArrayData data[27];
    char stringdata0[329];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_formLoading_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_formLoading_t qt_meta_stringdata_formLoading = {
    {
QT_MOC_LITERAL(0, 0, 11), // "formLoading"
QT_MOC_LITERAL(1, 12, 20), // "sig_DoCoreInitialize"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 4), // "user"
QT_MOC_LITERAL(4, 39, 3), // "pwd"
QT_MOC_LITERAL(5, 43, 7), // "extInfo"
QT_MOC_LITERAL(6, 51, 25), // "sig_DoViewModelInitialize"
QT_MOC_LITERAL(7, 77, 10), // "sig_Cancel"
QT_MOC_LITERAL(8, 88, 11), // "timerUpdate"
QT_MOC_LITERAL(9, 100, 16), // "on_btnOk_clicked"
QT_MOC_LITERAL(10, 117, 20), // "on_btnCancel_clicked"
QT_MOC_LITERAL(11, 138, 9), // "setBtnQss"
QT_MOC_LITERAL(12, 148, 12), // "QPushButton*"
QT_MOC_LITERAL(13, 161, 3), // "btn"
QT_MOC_LITERAL(14, 165, 11), // "normalColor"
QT_MOC_LITERAL(15, 177, 15), // "normalTextColor"
QT_MOC_LITERAL(16, 193, 10), // "hoverColor"
QT_MOC_LITERAL(17, 204, 14), // "hoverTextColor"
QT_MOC_LITERAL(18, 219, 12), // "pressedColor"
QT_MOC_LITERAL(19, 232, 16), // "pressedTextColor"
QT_MOC_LITERAL(20, 249, 9), // "setTxtQss"
QT_MOC_LITERAL(21, 259, 10), // "QLineEdit*"
QT_MOC_LITERAL(22, 270, 3), // "txt"
QT_MOC_LITERAL(23, 274, 10), // "focusColor"
QT_MOC_LITERAL(24, 285, 23), // "slot_CoreInitializeInfo"
QT_MOC_LITERAL(25, 309, 14), // "tagOutputInfo&"
QT_MOC_LITERAL(26, 324, 4) // "info"

    },
    "formLoading\0sig_DoCoreInitialize\0\0"
    "user\0pwd\0extInfo\0sig_DoViewModelInitialize\0"
    "sig_Cancel\0timerUpdate\0on_btnOk_clicked\0"
    "on_btnCancel_clicked\0setBtnQss\0"
    "QPushButton*\0btn\0normalColor\0"
    "normalTextColor\0hoverColor\0hoverTextColor\0"
    "pressedColor\0pressedTextColor\0setTxtQss\0"
    "QLineEdit*\0txt\0focusColor\0"
    "slot_CoreInitializeInfo\0tagOutputInfo&\0"
    "info"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_formLoading[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   59,    2, 0x06 /* Public */,
       6,    3,   66,    2, 0x06 /* Public */,
       7,    0,   73,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   74,    2, 0x08 /* Private */,
       9,    0,   75,    2, 0x08 /* Private */,
      10,    0,   76,    2, 0x08 /* Private */,
      11,    7,   77,    2, 0x08 /* Private */,
      20,    3,   92,    2, 0x08 /* Private */,
      24,    1,   99,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::QString,    3,    4,    5,
    QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::QString,    3,    4,    5,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   13,   14,   15,   16,   17,   18,   19,
    QMetaType::Void, 0x80000000 | 21, QMetaType::QString, QMetaType::QString,   22,   14,   23,
    QMetaType::Int, 0x80000000 | 25,   26,

       0        // eod
};

void formLoading::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<formLoading *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { int _r = _t->sig_DoCoreInitialize((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 1: { int _r = _t->sig_DoViewModelInitialize((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 2: _t->sig_Cancel(); break;
        case 3: _t->timerUpdate(); break;
        case 4: _t->on_btnOk_clicked(); break;
        case 5: _t->on_btnCancel_clicked(); break;
        case 6: _t->setBtnQss((*reinterpret_cast< QPushButton*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6])),(*reinterpret_cast< QString(*)>(_a[7]))); break;
        case 7: _t->setTxtQss((*reinterpret_cast< QLineEdit*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 8: { int _r = _t->slot_CoreInitializeInfo((*reinterpret_cast< tagOutputInfo(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = int (formLoading::*)(QString , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&formLoading::sig_DoCoreInitialize)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = int (formLoading::*)(QString , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&formLoading::sig_DoViewModelInitialize)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (formLoading::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&formLoading::sig_Cancel)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject formLoading::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_formLoading.data,
    qt_meta_data_formLoading,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *formLoading::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *formLoading::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_formLoading.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int formLoading::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
int formLoading::sig_DoCoreInitialize(QString _t1, QString _t2, QString _t3)
{
    int _t0{};
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t0))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
    return _t0;
}

// SIGNAL 1
int formLoading::sig_DoViewModelInitialize(QString _t1, QString _t2, QString _t3)
{
    int _t0{};
    void *_a[] = { const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t0))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
    return _t0;
}

// SIGNAL 2
void formLoading::sig_Cancel()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
