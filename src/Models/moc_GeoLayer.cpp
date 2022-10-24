/****************************************************************************
** Meta object code from reading C++ file 'GeoLayer.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "GeoLayer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GeoLayer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GeoLayer_t {
    uint offsetsAndSizes[12];
    char stringdata0[9];
    char stringdata1[18];
    char stringdata2[1];
    char stringdata3[6];
    char stringdata4[17];
    char stringdata5[20];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_GeoLayer_t::offsetsAndSizes) + ofs), len 
static const qt_meta_stringdata_GeoLayer_t qt_meta_stringdata_GeoLayer = {
    {
        QT_MOC_LITERAL(0, 8),  // "GeoLayer"
        QT_MOC_LITERAL(9, 17),  // "pointColorChanged"
        QT_MOC_LITERAL(27, 0),  // ""
        QT_MOC_LITERAL(28, 5),  // "color"
        QT_MOC_LITERAL(34, 16),  // "lineColorChanged"
        QT_MOC_LITERAL(51, 19)   // "polygonColorChanged"
    },
    "GeoLayer",
    "pointColorChanged",
    "",
    "color",
    "lineColorChanged",
    "polygonColorChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GeoLayer[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   32,    2, 0x06,    1 /* Public */,
       4,    1,   35,    2, 0x06,    3 /* Public */,
       5,    1,   38,    2, 0x06,    5 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QColor,    3,
    QMetaType::Void, QMetaType::QColor,    3,
    QMetaType::Void, QMetaType::QColor,    3,

       0        // eod
};

void GeoLayer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GeoLayer *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->pointColorChanged((*reinterpret_cast< std::add_pointer_t<QColor>>(_a[1]))); break;
        case 1: _t->lineColorChanged((*reinterpret_cast< std::add_pointer_t<QColor>>(_a[1]))); break;
        case 2: _t->polygonColorChanged((*reinterpret_cast< std::add_pointer_t<QColor>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GeoLayer::*)(QColor );
            if (_t _q_method = &GeoLayer::pointColorChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GeoLayer::*)(QColor );
            if (_t _q_method = &GeoLayer::lineColorChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (GeoLayer::*)(QColor );
            if (_t _q_method = &GeoLayer::polygonColorChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject GeoLayer::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_GeoLayer.offsetsAndSizes,
    qt_meta_data_GeoLayer,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_GeoLayer_t
, QtPrivate::TypeAndForceComplete<GeoLayer, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QColor, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QColor, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QColor, std::false_type>



>,
    nullptr
} };


const QMetaObject *GeoLayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GeoLayer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GeoLayer.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int GeoLayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void GeoLayer::pointColorChanged(QColor _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GeoLayer::lineColorChanged(QColor _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GeoLayer::polygonColorChanged(QColor _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
