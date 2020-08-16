/****************************************************************************
** Meta object code from reading C++ file 'TSessions.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Widget/TSessions.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TSessions.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TSessions_t {
    QByteArrayData data[13];
    char stringdata0[156];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TSessions_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TSessions_t qt_meta_stringdata_TSessions = {
    {
QT_MOC_LITERAL(0, 0, 9), // "TSessions"
QT_MOC_LITERAL(1, 10, 16), // "sigNewTextEditor"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 9), // "TSession*"
QT_MOC_LITERAL(4, 38, 13), // "newTextEditor"
QT_MOC_LITERAL(5, 52, 20), // "sigCurrentTextEditor"
QT_MOC_LITERAL(6, 73, 16), // "slotVSplitScreen"
QT_MOC_LITERAL(7, 90, 16), // "slotHSplitScreen"
QT_MOC_LITERAL(8, 107, 15), // "slotMergeScreen"
QT_MOC_LITERAL(9, 123, 15), // "slotFocusChange"
QT_MOC_LITERAL(10, 139, 8), // "QWidget*"
QT_MOC_LITERAL(11, 148, 3), // "old"
QT_MOC_LITERAL(12, 152, 3) // "now"

    },
    "TSessions\0sigNewTextEditor\0\0TSession*\0"
    "newTextEditor\0sigCurrentTextEditor\0"
    "slotVSplitScreen\0slotHSplitScreen\0"
    "slotMergeScreen\0slotFocusChange\0"
    "QWidget*\0old\0now"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TSessions[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       5,    1,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   50,    2, 0x0a /* Public */,
       7,    0,   51,    2, 0x0a /* Public */,
       8,    0,   52,    2, 0x0a /* Public */,
       9,    2,   53,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10, 0x80000000 | 10,   11,   12,

       0        // eod
};

void TSessions::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TSessions *_t = static_cast<TSessions *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigNewTextEditor((*reinterpret_cast< TSession*(*)>(_a[1]))); break;
        case 1: _t->sigCurrentTextEditor((*reinterpret_cast< TSession*(*)>(_a[1]))); break;
        case 2: _t->slotVSplitScreen(); break;
        case 3: _t->slotHSplitScreen(); break;
        case 4: _t->slotMergeScreen(); break;
        case 5: _t->slotFocusChange((*reinterpret_cast< QWidget*(*)>(_a[1])),(*reinterpret_cast< QWidget*(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< TSession* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< TSession* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TSessions::*_t)(TSession * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TSessions::sigNewTextEditor)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TSessions::*_t)(TSession * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TSessions::sigCurrentTextEditor)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject TSessions::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TSessions.data,
      qt_meta_data_TSessions,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TSessions::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TSessions::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TSessions.stringdata0))
        return static_cast<void*>(const_cast< TSessions*>(this));
    return QWidget::qt_metacast(_clname);
}

int TSessions::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void TSessions::sigNewTextEditor(TSession * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TSessions::sigCurrentTextEditor(TSession * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
