/****************************************************************************
** Meta object code from reading C++ file 'MPMainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "MPMainWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MPMainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MPMainWindow_t {
    uint offsetsAndSizes[24];
    char stringdata0[13];
    char stringdata1[16];
    char stringdata2[1];
    char stringdata3[9];
    char stringdata4[7];
    char stringdata5[11];
    char stringdata6[11];
    char stringdata7[22];
    char stringdata8[15];
    char stringdata9[17];
    char stringdata10[18];
    char stringdata11[6];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_MPMainWindow_t::offsetsAndSizes) + ofs), len 
static const qt_meta_stringdata_MPMainWindow_t qt_meta_stringdata_MPMainWindow = {
    {
        QT_MOC_LITERAL(0, 12),  // "MPMainWindow"
        QT_MOC_LITERAL(13, 15),  // "actionTriggered"
        QT_MOC_LITERAL(29, 0),  // ""
        QT_MOC_LITERAL(30, 8),  // "QAction*"
        QT_MOC_LITERAL(39, 6),  // "action"
        QT_MOC_LITERAL(46, 10),  // "saveLayout"
        QT_MOC_LITERAL(57, 10),  // "loadLayout"
        QT_MOC_LITERAL(68, 21),  // "switchLayoutDirection"
        QT_MOC_LITERAL(90, 14),  // "setDockOptions"
        QT_MOC_LITERAL(105, 16),  // "createDockWidget"
        QT_MOC_LITERAL(122, 17),  // "destroyDockWidget"
        QT_MOC_LITERAL(140, 5)   // "about"
    },
    "MPMainWindow",
    "actionTriggered",
    "",
    "QAction*",
    "action",
    "saveLayout",
    "loadLayout",
    "switchLayoutDirection",
    "setDockOptions",
    "createDockWidget",
    "destroyDockWidget",
    "about"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MPMainWindow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   62,    2, 0x0a,    1 /* Public */,
       5,    0,   65,    2, 0x0a,    3 /* Public */,
       6,    0,   66,    2, 0x0a,    4 /* Public */,
       7,    0,   67,    2, 0x0a,    5 /* Public */,
       8,    0,   68,    2, 0x0a,    6 /* Public */,
       9,    0,   69,    2, 0x0a,    7 /* Public */,
      10,    1,   70,    2, 0x0a,    8 /* Public */,
      11,    0,   73,    2, 0x0a,   10 /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

       0        // eod
};

void MPMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MPMainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->actionTriggered((*reinterpret_cast< std::add_pointer_t<QAction*>>(_a[1]))); break;
        case 1: _t->saveLayout(); break;
        case 2: _t->loadLayout(); break;
        case 3: _t->switchLayoutDirection(); break;
        case 4: _t->setDockOptions(); break;
        case 5: _t->createDockWidget(); break;
        case 6: _t->destroyDockWidget((*reinterpret_cast< std::add_pointer_t<QAction*>>(_a[1]))); break;
        case 7: _t->about(); break;
        default: ;
        }
    }
}

const QMetaObject MPMainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MPMainWindow.offsetsAndSizes,
    qt_meta_data_MPMainWindow,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_MPMainWindow_t
, QtPrivate::TypeAndForceComplete<MPMainWindow, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QAction *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QAction *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *MPMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MPMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MPMainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MPMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
