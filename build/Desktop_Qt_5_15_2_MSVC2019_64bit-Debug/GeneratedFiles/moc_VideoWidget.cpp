/****************************************************************************
** Meta object code from reading C++ file 'VideoWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../VideoWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'VideoWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VideoWidget_t {
    QByteArrayData data[14];
    char stringdata0[158];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VideoWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VideoWidget_t qt_meta_stringdata_VideoWidget = {
    {
QT_MOC_LITERAL(0, 0, 11), // "VideoWidget"
QT_MOC_LITERAL(1, 12, 12), // "sig_OpenFile"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 8), // "fileList"
QT_MOC_LITERAL(4, 35, 14), // "sig_OpenFloder"
QT_MOC_LITERAL(5, 50, 4), // "path"
QT_MOC_LITERAL(6, 55, 16), // "sig_OpenPlayList"
QT_MOC_LITERAL(7, 72, 11), // "sig_TotalMs"
QT_MOC_LITERAL(8, 84, 8), // "duration"
QT_MOC_LITERAL(9, 93, 24), // "sig_VideoPositionChanged"
QT_MOC_LITERAL(10, 118, 3), // "pos"
QT_MOC_LITERAL(11, 122, 15), // "sig_SliderMoved"
QT_MOC_LITERAL(12, 138, 5), // "value"
QT_MOC_LITERAL(13, 144, 13) // "onSliderMoved"

    },
    "VideoWidget\0sig_OpenFile\0\0fileList\0"
    "sig_OpenFloder\0path\0sig_OpenPlayList\0"
    "sig_TotalMs\0duration\0sig_VideoPositionChanged\0"
    "pos\0sig_SliderMoved\0value\0onSliderMoved"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VideoWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       4,    1,   52,    2, 0x06 /* Public */,
       6,    0,   55,    2, 0x06 /* Public */,
       7,    1,   56,    2, 0x06 /* Public */,
       9,    1,   59,    2, 0x06 /* Public */,
      11,    1,   62,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    1,   65,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QStringList,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong,    8,
    QMetaType::Void, QMetaType::LongLong,   10,
    QMetaType::Void, QMetaType::Int,   12,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,   12,

       0        // eod
};

void VideoWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<VideoWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_OpenFile((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 1: _t->sig_OpenFloder((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->sig_OpenPlayList(); break;
        case 3: _t->sig_TotalMs((*reinterpret_cast< const qint64(*)>(_a[1]))); break;
        case 4: _t->sig_VideoPositionChanged((*reinterpret_cast< const qint64(*)>(_a[1]))); break;
        case 5: _t->sig_SliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->onSliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (VideoWidget::*)(const QStringList & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VideoWidget::sig_OpenFile)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (VideoWidget::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VideoWidget::sig_OpenFloder)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (VideoWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VideoWidget::sig_OpenPlayList)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (VideoWidget::*)(const qint64 & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VideoWidget::sig_TotalMs)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (VideoWidget::*)(const qint64 & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VideoWidget::sig_VideoPositionChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (VideoWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VideoWidget::sig_SliderMoved)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VideoWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_VideoWidget.data,
    qt_meta_data_VideoWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VideoWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VideoWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VideoWidget.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QAbstractNativeEventFilter"))
        return static_cast< QAbstractNativeEventFilter*>(this);
    return QWidget::qt_metacast(_clname);
}

int VideoWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void VideoWidget::sig_OpenFile(const QStringList & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VideoWidget::sig_OpenFloder(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void VideoWidget::sig_OpenPlayList()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void VideoWidget::sig_TotalMs(const qint64 & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void VideoWidget::sig_VideoPositionChanged(const qint64 & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void VideoWidget::sig_SliderMoved(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
