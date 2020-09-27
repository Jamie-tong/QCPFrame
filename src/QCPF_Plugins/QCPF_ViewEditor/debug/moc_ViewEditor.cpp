/****************************************************************************
** Meta object code from reading C++ file 'ViewEditor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../ViewEditor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ViewEditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ViewEditor_t {
    QByteArrayData data[61];
    char stringdata0[1411];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ViewEditor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ViewEditor_t qt_meta_stringdata_ViewEditor = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ViewEditor"
QT_MOC_LITERAL(1, 11, 15), // "sig_SelAllOrNot"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 4), // "flag"
QT_MOC_LITERAL(4, 33, 14), // "slot_OnULoaded"
QT_MOC_LITERAL(5, 48, 16), // "on_btnOk_clicked"
QT_MOC_LITERAL(6, 65, 15), // "getConfigFromUI"
QT_MOC_LITERAL(7, 81, 20), // "on_btnCancel_clicked"
QT_MOC_LITERAL(8, 102, 21), // "on_btnAddNode_clicked"
QT_MOC_LITERAL(9, 124, 24), // "on_btnDeleteNode_clicked"
QT_MOC_LITERAL(10, 149, 16), // "on_btnUp_clicked"
QT_MOC_LITERAL(11, 166, 18), // "on_btnDown_clicked"
QT_MOC_LITERAL(12, 185, 18), // "on_btnLeft_clicked"
QT_MOC_LITERAL(13, 204, 19), // "on_btnRight_clicked"
QT_MOC_LITERAL(14, 224, 34), // "on_treeMenuEdit_currentItemCh..."
QT_MOC_LITERAL(15, 259, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(16, 276, 7), // "current"
QT_MOC_LITERAL(17, 284, 8), // "previous"
QT_MOC_LITERAL(18, 293, 25), // "on_btnClearAction_clicked"
QT_MOC_LITERAL(19, 319, 24), // "on_btnIconFinder_clicked"
QT_MOC_LITERAL(20, 344, 31), // "on_btnAddAction_Toolbar_clicked"
QT_MOC_LITERAL(21, 376, 31), // "on_btnAddWidget_Toolbar_clicked"
QT_MOC_LITERAL(22, 408, 32), // "on_btnDeleteItem_Toolbar_clicked"
QT_MOC_LITERAL(23, 441, 28), // "on_btnMoveUp_Toolbar_clicked"
QT_MOC_LITERAL(24, 470, 30), // "on_btnMoveDown_Toolbar_clicked"
QT_MOC_LITERAL(25, 501, 33), // "on_btnAddWidget_Statusbar_cli..."
QT_MOC_LITERAL(26, 535, 34), // "on_btnDeleteItem_Statusbar_cl..."
QT_MOC_LITERAL(27, 570, 30), // "on_btnMoveUp_Statusbar_clicked"
QT_MOC_LITERAL(28, 601, 32), // "on_btnMoveDown_Statusbar_clicked"
QT_MOC_LITERAL(29, 634, 24), // "on_btnAddToolbar_clicked"
QT_MOC_LITERAL(30, 659, 27), // "on_btnDeleteToolbar_clicked"
QT_MOC_LITERAL(31, 687, 15), // "TableItemMoveUp"
QT_MOC_LITERAL(32, 703, 13), // "QTableWidget*"
QT_MOC_LITERAL(33, 717, 5), // "table"
QT_MOC_LITERAL(34, 723, 17), // "TableItemMoveDown"
QT_MOC_LITERAL(35, 741, 14), // "TreeItemMoveUp"
QT_MOC_LITERAL(36, 756, 12), // "QTreeWidget*"
QT_MOC_LITERAL(37, 769, 10), // "treeWidget"
QT_MOC_LITERAL(38, 780, 16), // "TreeItemMoveDown"
QT_MOC_LITERAL(39, 797, 16), // "TreeItemMoveLeft"
QT_MOC_LITERAL(40, 814, 17), // "TreeItemMoveRight"
QT_MOC_LITERAL(41, 832, 24), // "on_btnLoadAction_clicked"
QT_MOC_LITERAL(42, 857, 32), // "on_tablePluginWidget_itemClicked"
QT_MOC_LITERAL(43, 890, 17), // "QTableWidgetItem*"
QT_MOC_LITERAL(44, 908, 4), // "item"
QT_MOC_LITERAL(45, 913, 31), // "on_btnAddSpacer_Toolbar_clicked"
QT_MOC_LITERAL(46, 945, 34), // "on_btnAddSeparator_Toolbar_cl..."
QT_MOC_LITERAL(47, 980, 26), // "on_btnAddSeparator_clicked"
QT_MOC_LITERAL(48, 1007, 33), // "on_treeMenuEdit_itemDoubleCli..."
QT_MOC_LITERAL(49, 1041, 6), // "column"
QT_MOC_LITERAL(50, 1048, 36), // "on_treeToolbarEdit_itemDouble..."
QT_MOC_LITERAL(51, 1085, 41), // "on_tableStatusbarEditer_itemD..."
QT_MOC_LITERAL(52, 1127, 37), // "on_treeToolbarEdit_currentIte..."
QT_MOC_LITERAL(53, 1165, 42), // "on_tableStatusbarEditer_curre..."
QT_MOC_LITERAL(54, 1208, 16), // "slot_SelAllOrNot"
QT_MOC_LITERAL(55, 1225, 31), // "OnLineEdit_EditingFinished_Tree"
QT_MOC_LITERAL(56, 1257, 30), // "OnKeyEdit_EditingFinished_Tree"
QT_MOC_LITERAL(57, 1288, 31), // "OnComboBox_Activated_Index_Tree"
QT_MOC_LITERAL(58, 1320, 30), // "OnComboBox_Activated_Text_Tree"
QT_MOC_LITERAL(59, 1351, 27), // "OnSpinBox_ValueChanged_Tree"
QT_MOC_LITERAL(60, 1379, 31) // "OnComboBox_Activated_Text_Table"

    },
    "ViewEditor\0sig_SelAllOrNot\0\0flag\0"
    "slot_OnULoaded\0on_btnOk_clicked\0"
    "getConfigFromUI\0on_btnCancel_clicked\0"
    "on_btnAddNode_clicked\0on_btnDeleteNode_clicked\0"
    "on_btnUp_clicked\0on_btnDown_clicked\0"
    "on_btnLeft_clicked\0on_btnRight_clicked\0"
    "on_treeMenuEdit_currentItemChanged\0"
    "QTreeWidgetItem*\0current\0previous\0"
    "on_btnClearAction_clicked\0"
    "on_btnIconFinder_clicked\0"
    "on_btnAddAction_Toolbar_clicked\0"
    "on_btnAddWidget_Toolbar_clicked\0"
    "on_btnDeleteItem_Toolbar_clicked\0"
    "on_btnMoveUp_Toolbar_clicked\0"
    "on_btnMoveDown_Toolbar_clicked\0"
    "on_btnAddWidget_Statusbar_clicked\0"
    "on_btnDeleteItem_Statusbar_clicked\0"
    "on_btnMoveUp_Statusbar_clicked\0"
    "on_btnMoveDown_Statusbar_clicked\0"
    "on_btnAddToolbar_clicked\0"
    "on_btnDeleteToolbar_clicked\0TableItemMoveUp\0"
    "QTableWidget*\0table\0TableItemMoveDown\0"
    "TreeItemMoveUp\0QTreeWidget*\0treeWidget\0"
    "TreeItemMoveDown\0TreeItemMoveLeft\0"
    "TreeItemMoveRight\0on_btnLoadAction_clicked\0"
    "on_tablePluginWidget_itemClicked\0"
    "QTableWidgetItem*\0item\0"
    "on_btnAddSpacer_Toolbar_clicked\0"
    "on_btnAddSeparator_Toolbar_clicked\0"
    "on_btnAddSeparator_clicked\0"
    "on_treeMenuEdit_itemDoubleClicked\0"
    "column\0on_treeToolbarEdit_itemDoubleClicked\0"
    "on_tableStatusbarEditer_itemDoubleClicked\0"
    "on_treeToolbarEdit_currentItemChanged\0"
    "on_tableStatusbarEditer_currentItemChanged\0"
    "slot_SelAllOrNot\0OnLineEdit_EditingFinished_Tree\0"
    "OnKeyEdit_EditingFinished_Tree\0"
    "OnComboBox_Activated_Index_Tree\0"
    "OnComboBox_Activated_Text_Tree\0"
    "OnSpinBox_ValueChanged_Tree\0"
    "OnComboBox_Activated_Text_Table"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ViewEditor[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      48,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  254,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,  257,    2, 0x08 /* Private */,
       5,    0,  258,    2, 0x08 /* Private */,
       6,    0,  259,    2, 0x08 /* Private */,
       7,    0,  260,    2, 0x08 /* Private */,
       8,    0,  261,    2, 0x08 /* Private */,
       9,    0,  262,    2, 0x08 /* Private */,
      10,    0,  263,    2, 0x08 /* Private */,
      11,    0,  264,    2, 0x08 /* Private */,
      12,    0,  265,    2, 0x08 /* Private */,
      13,    0,  266,    2, 0x08 /* Private */,
      14,    2,  267,    2, 0x08 /* Private */,
      18,    0,  272,    2, 0x08 /* Private */,
      19,    0,  273,    2, 0x08 /* Private */,
      20,    0,  274,    2, 0x08 /* Private */,
      21,    0,  275,    2, 0x08 /* Private */,
      22,    0,  276,    2, 0x08 /* Private */,
      23,    0,  277,    2, 0x08 /* Private */,
      24,    0,  278,    2, 0x08 /* Private */,
      25,    0,  279,    2, 0x08 /* Private */,
      26,    0,  280,    2, 0x08 /* Private */,
      27,    0,  281,    2, 0x08 /* Private */,
      28,    0,  282,    2, 0x08 /* Private */,
      29,    0,  283,    2, 0x08 /* Private */,
      30,    0,  284,    2, 0x08 /* Private */,
      31,    1,  285,    2, 0x08 /* Private */,
      34,    1,  288,    2, 0x08 /* Private */,
      35,    1,  291,    2, 0x08 /* Private */,
      38,    1,  294,    2, 0x08 /* Private */,
      39,    1,  297,    2, 0x08 /* Private */,
      40,    1,  300,    2, 0x08 /* Private */,
      41,    0,  303,    2, 0x08 /* Private */,
      42,    1,  304,    2, 0x08 /* Private */,
      45,    0,  307,    2, 0x08 /* Private */,
      46,    0,  308,    2, 0x08 /* Private */,
      47,    0,  309,    2, 0x08 /* Private */,
      48,    2,  310,    2, 0x08 /* Private */,
      50,    2,  315,    2, 0x08 /* Private */,
      51,    1,  320,    2, 0x08 /* Private */,
      52,    2,  323,    2, 0x08 /* Private */,
      53,    2,  328,    2, 0x08 /* Private */,
      54,    1,  333,    2, 0x0a /* Public */,
      55,    0,  336,    2, 0x0a /* Public */,
      56,    0,  337,    2, 0x0a /* Public */,
      57,    1,  338,    2, 0x0a /* Public */,
      58,    1,  341,    2, 0x0a /* Public */,
      59,    1,  344,    2, 0x0a /* Public */,
      60,    1,  347,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 15, 0x80000000 | 15,   16,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 32,   33,
    QMetaType::Void, 0x80000000 | 32,   33,
    QMetaType::Void, 0x80000000 | 36,   37,
    QMetaType::Void, 0x80000000 | 36,   37,
    QMetaType::Void, 0x80000000 | 36,   37,
    QMetaType::Void, 0x80000000 | 36,   37,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 43,   44,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 15, QMetaType::Int,   44,   49,
    QMetaType::Void, 0x80000000 | 15, QMetaType::Int,   44,   49,
    QMetaType::Void, 0x80000000 | 43,   44,
    QMetaType::Void, 0x80000000 | 15, 0x80000000 | 15,   16,   17,
    QMetaType::Void, 0x80000000 | 43, 0x80000000 | 43,   16,   17,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void ViewEditor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ViewEditor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_SelAllOrNot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->slot_OnULoaded(); break;
        case 2: _t->on_btnOk_clicked(); break;
        case 3: { int _r = _t->getConfigFromUI();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 4: _t->on_btnCancel_clicked(); break;
        case 5: _t->on_btnAddNode_clicked(); break;
        case 6: _t->on_btnDeleteNode_clicked(); break;
        case 7: _t->on_btnUp_clicked(); break;
        case 8: _t->on_btnDown_clicked(); break;
        case 9: _t->on_btnLeft_clicked(); break;
        case 10: _t->on_btnRight_clicked(); break;
        case 11: _t->on_treeMenuEdit_currentItemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        case 12: _t->on_btnClearAction_clicked(); break;
        case 13: _t->on_btnIconFinder_clicked(); break;
        case 14: _t->on_btnAddAction_Toolbar_clicked(); break;
        case 15: _t->on_btnAddWidget_Toolbar_clicked(); break;
        case 16: _t->on_btnDeleteItem_Toolbar_clicked(); break;
        case 17: _t->on_btnMoveUp_Toolbar_clicked(); break;
        case 18: _t->on_btnMoveDown_Toolbar_clicked(); break;
        case 19: _t->on_btnAddWidget_Statusbar_clicked(); break;
        case 20: _t->on_btnDeleteItem_Statusbar_clicked(); break;
        case 21: _t->on_btnMoveUp_Statusbar_clicked(); break;
        case 22: _t->on_btnMoveDown_Statusbar_clicked(); break;
        case 23: _t->on_btnAddToolbar_clicked(); break;
        case 24: _t->on_btnDeleteToolbar_clicked(); break;
        case 25: _t->TableItemMoveUp((*reinterpret_cast< QTableWidget*(*)>(_a[1]))); break;
        case 26: _t->TableItemMoveDown((*reinterpret_cast< QTableWidget*(*)>(_a[1]))); break;
        case 27: _t->TreeItemMoveUp((*reinterpret_cast< QTreeWidget*(*)>(_a[1]))); break;
        case 28: _t->TreeItemMoveDown((*reinterpret_cast< QTreeWidget*(*)>(_a[1]))); break;
        case 29: _t->TreeItemMoveLeft((*reinterpret_cast< QTreeWidget*(*)>(_a[1]))); break;
        case 30: _t->TreeItemMoveRight((*reinterpret_cast< QTreeWidget*(*)>(_a[1]))); break;
        case 31: _t->on_btnLoadAction_clicked(); break;
        case 32: _t->on_tablePluginWidget_itemClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 33: _t->on_btnAddSpacer_Toolbar_clicked(); break;
        case 34: _t->on_btnAddSeparator_Toolbar_clicked(); break;
        case 35: _t->on_btnAddSeparator_clicked(); break;
        case 36: _t->on_treeMenuEdit_itemDoubleClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 37: _t->on_treeToolbarEdit_itemDoubleClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 38: _t->on_tableStatusbarEditer_itemDoubleClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 39: _t->on_treeToolbarEdit_currentItemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        case 40: _t->on_tableStatusbarEditer_currentItemChanged((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTableWidgetItem*(*)>(_a[2]))); break;
        case 41: _t->slot_SelAllOrNot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 42: _t->OnLineEdit_EditingFinished_Tree(); break;
        case 43: _t->OnKeyEdit_EditingFinished_Tree(); break;
        case 44: _t->OnComboBox_Activated_Index_Tree((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 45: _t->OnComboBox_Activated_Text_Tree((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 46: _t->OnSpinBox_ValueChanged_Tree((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 47: _t->OnComboBox_Activated_Text_Table((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 25:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QTableWidget* >(); break;
            }
            break;
        case 26:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QTableWidget* >(); break;
            }
            break;
        case 27:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QTreeWidget* >(); break;
            }
            break;
        case 28:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QTreeWidget* >(); break;
            }
            break;
        case 29:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QTreeWidget* >(); break;
            }
            break;
        case 30:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QTreeWidget* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ViewEditor::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ViewEditor::sig_SelAllOrNot)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ViewEditor::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_ViewEditor.data,
    qt_meta_data_ViewEditor,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ViewEditor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ViewEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ViewEditor.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int ViewEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 48)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 48;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 48)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 48;
    }
    return _id;
}

// SIGNAL 0
void ViewEditor::sig_SelAllOrNot(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
