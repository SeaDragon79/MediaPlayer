/****************************************************************************
** Meta object code from reading C++ file 'CVlcKits.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../CVlcKits.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CVlcKits.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CVlcKits_t {
    QByteArrayData data[7];
    char stringdata0[77];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CVlcKits_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CVlcKits_t qt_meta_stringdata_CVlcKits = {
    {
QT_MOC_LITERAL(0, 0, 8), // "CVlcKits"
QT_MOC_LITERAL(1, 9, 17), // "sig_TimeSliderPos"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 5), // "value"
QT_MOC_LITERAL(4, 34, 19), // "sig_VolumeSliderPos"
QT_MOC_LITERAL(5, 54, 18), // "sig_UpdateTimeText"
QT_MOC_LITERAL(6, 73, 3) // "str"

    },
    "CVlcKits\0sig_TimeSliderPos\0\0value\0"
    "sig_VolumeSliderPos\0sig_UpdateTimeText\0"
    "str"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CVlcKits[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       4,    1,   32,    2, 0x06 /* Public */,
       5,    1,   35,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString,    6,

       0        // eod
};

void CVlcKits::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CVlcKits *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_TimeSliderPos((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->sig_VolumeSliderPos((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->sig_UpdateTimeText((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CVlcKits::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CVlcKits::sig_TimeSliderPos)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CVlcKits::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CVlcKits::sig_VolumeSliderPos)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CVlcKits::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CVlcKits::sig_UpdateTimeText)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CVlcKits::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CVlcKits.data,
    qt_meta_data_CVlcKits,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CVlcKits::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CVlcKits::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CVlcKits.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CVlcKits::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void CVlcKits::sig_TimeSliderPos(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CVlcKits::sig_VolumeSliderPos(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CVlcKits::sig_UpdateTimeText(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
