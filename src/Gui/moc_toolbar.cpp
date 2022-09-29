/****************************************************************************
** Meta object code from reading C++ file 'toolbar.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "toolbar.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'toolbar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ToolBar_t {
    uint offsetsAndSizes[40];
    char stringdata0[8];
    char stringdata1[6];
    char stringdata2[1];
    char stringdata3[10];
    char stringdata4[11];
    char stringdata5[14];
    char stringdata6[14];
    char stringdata7[8];
    char stringdata8[10];
    char stringdata9[2];
    char stringdata10[11];
    char stringdata11[9];
    char stringdata12[12];
    char stringdata13[10];
    char stringdata14[2];
    char stringdata15[11];
    char stringdata16[9];
    char stringdata17[12];
    char stringdata18[11];
    char stringdata19[19];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_ToolBar_t::offsetsAndSizes) + ofs), len 
static const qt_meta_stringdata_ToolBar_t qt_meta_stringdata_ToolBar = {
    {
        QT_MOC_LITERAL(0, 7),  // "ToolBar"
        QT_MOC_LITERAL(8, 5),  // "order"
        QT_MOC_LITERAL(14, 0),  // ""
        QT_MOC_LITERAL(15, 9),  // "randomize"
        QT_MOC_LITERAL(25, 10),  // "addSpinBox"
        QT_MOC_LITERAL(36, 13),  // "removeSpinBox"
        QT_MOC_LITERAL(50, 13),  // "changeMovable"
        QT_MOC_LITERAL(64, 7),  // "movable"
        QT_MOC_LITERAL(72, 9),  // "allowLeft"
        QT_MOC_LITERAL(82, 1),  // "a"
        QT_MOC_LITERAL(84, 10),  // "allowRight"
        QT_MOC_LITERAL(95, 8),  // "allowTop"
        QT_MOC_LITERAL(104, 11),  // "allowBottom"
        QT_MOC_LITERAL(116, 9),  // "placeLeft"
        QT_MOC_LITERAL(126, 1),  // "p"
        QT_MOC_LITERAL(128, 10),  // "placeRight"
        QT_MOC_LITERAL(139, 8),  // "placeTop"
        QT_MOC_LITERAL(148, 11),  // "placeBottom"
        QT_MOC_LITERAL(160, 10),  // "updateMenu"
        QT_MOC_LITERAL(171, 18)   // "insertToolBarBreak"
    },
    "ToolBar",
    "order",
    "",
    "randomize",
    "addSpinBox",
    "removeSpinBox",
    "changeMovable",
    "movable",
    "allowLeft",
    "a",
    "allowRight",
    "allowTop",
    "allowBottom",
    "placeLeft",
    "p",
    "placeRight",
    "placeTop",
    "placeBottom",
    "updateMenu",
    "insertToolBarBreak"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ToolBar[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  104,    2, 0x08,    1 /* Private */,
       3,    0,  105,    2, 0x08,    2 /* Private */,
       4,    0,  106,    2, 0x08,    3 /* Private */,
       5,    0,  107,    2, 0x08,    4 /* Private */,
       6,    1,  108,    2, 0x08,    5 /* Private */,
       8,    1,  111,    2, 0x08,    7 /* Private */,
      10,    1,  114,    2, 0x08,    9 /* Private */,
      11,    1,  117,    2, 0x08,   11 /* Private */,
      12,    1,  120,    2, 0x08,   13 /* Private */,
      13,    1,  123,    2, 0x08,   15 /* Private */,
      15,    1,  126,    2, 0x08,   17 /* Private */,
      16,    1,  129,    2, 0x08,   19 /* Private */,
      17,    1,  132,    2, 0x08,   21 /* Private */,
      18,    0,  135,    2, 0x08,   23 /* Private */,
      19,    0,  136,    2, 0x08,   24 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ToolBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ToolBar *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->order(); break;
        case 1: _t->randomize(); break;
        case 2: _t->addSpinBox(); break;
        case 3: _t->removeSpinBox(); break;
        case 4: _t->changeMovable((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 5: _t->allowLeft((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 6: _t->allowRight((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 7: _t->allowTop((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 8: _t->allowBottom((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 9: _t->placeLeft((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 10: _t->placeRight((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 11: _t->placeTop((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 12: _t->placeBottom((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 13: _t->updateMenu(); break;
        case 14: _t->insertToolBarBreak(); break;
        default: ;
        }
    }
}

const QMetaObject ToolBar::staticMetaObject = { {
    QMetaObject::SuperData::link<QToolBar::staticMetaObject>(),
    qt_meta_stringdata_ToolBar.offsetsAndSizes,
    qt_meta_data_ToolBar,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_ToolBar_t
, QtPrivate::TypeAndForceComplete<ToolBar, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *ToolBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ToolBar::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ToolBar.stringdata0))
        return static_cast<void*>(this);
    return QToolBar::qt_metacast(_clname);
}

int ToolBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QToolBar::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 15;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
