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
    uint offsetsAndSizes[20];
    char stringdata0[13];
    char stringdata1[11];
    char stringdata2[1];
    char stringdata3[11];
    char stringdata4[22];
    char stringdata5[15];
    char stringdata6[17];
    char stringdata7[18];
    char stringdata8[9];
    char stringdata9[7];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_MPMainWindow_t::offsetsAndSizes) + ofs), len 
static const qt_meta_stringdata_MPMainWindow_t qt_meta_stringdata_MPMainWindow = {
    {
        QT_MOC_LITERAL(0, 12),  // "MPMainWindow"
        QT_MOC_LITERAL(13, 10),  // "saveLayout"
        QT_MOC_LITERAL(24, 0),  // ""
        QT_MOC_LITERAL(25, 10),  // "loadLayout"
        QT_MOC_LITERAL(36, 21),  // "switchLayoutDirection"
        QT_MOC_LITERAL(58, 14),  // "setDockOptions"
        QT_MOC_LITERAL(73, 16),  // "createDockWidget"
        QT_MOC_LITERAL(90, 17),  // "destroyDockWidget"
        QT_MOC_LITERAL(108, 8),  // "QAction*"
        QT_MOC_LITERAL(117, 6)   // "action"
    },
    "MPMainWindow",
    "saveLayout",
    "",
    "loadLayout",
    "switchLayoutDirection",
    "setDockOptions",
    "createDockWidget",
    "destroyDockWidget",
    "QAction*",
    "action"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MPMainWindow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x0a,    1 /* Public */,
       3,    0,   51,    2, 0x0a,    2 /* Public */,
       4,    0,   52,    2, 0x0a,    3 /* Public */,
       5,    0,   53,    2, 0x0a,    4 /* Public */,
       6,    0,   54,    2, 0x0a,    5 /* Public */,
       7,    1,   55,    2, 0x0a,    6 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,

       0        // eod
};

void MPMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MPMainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->saveLayout(); break;
        case 1: _t->loadLayout(); break;
        case 2: _t->switchLayoutDirection(); break;
        case 3: _t->setDockOptions(); break;
        case 4: _t->createDockWidget(); break;
        case 5: _t->destroyDockWidget((*reinterpret_cast< std::add_pointer_t<QAction*>>(_a[1]))); break;
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
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QAction *, std::false_type>


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
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
