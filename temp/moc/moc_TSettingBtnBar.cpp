/****************************************************************************
** Meta object code from reading C++ file 'TSettingBtnBar.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Widget/TSettingBtnBar.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TSettingBtnBar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TSettingBtnBar_t {
    QByteArrayData data[7];
    char stringdata0[69];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TSettingBtnBar_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TSettingBtnBar_t qt_meta_stringdata_TSettingBtnBar = {
    {
QT_MOC_LITERAL(0, 0, 14), // "TSettingBtnBar"
QT_MOC_LITERAL(1, 15, 13), // "sigSettingBtn"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 5), // "strId"
QT_MOC_LITERAL(4, 36, 9), // "sigCloset"
QT_MOC_LITERAL(5, 46, 7), // "bIsOpen"
QT_MOC_LITERAL(6, 54, 14) // "slotBtnClicked"

    },
    "TSettingBtnBar\0sigSettingBtn\0\0strId\0"
    "sigCloset\0bIsOpen\0slotBtnClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TSettingBtnBar[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       4,    1,   32,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   35,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Bool,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,

       0        // eod
};

void TSettingBtnBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TSettingBtnBar *_t = static_cast<TSettingBtnBar *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigSettingBtn((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->sigCloset((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->slotBtnClicked((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TSettingBtnBar::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TSettingBtnBar::sigSettingBtn)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TSettingBtnBar::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TSettingBtnBar::sigCloset)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject TSettingBtnBar::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TSettingBtnBar.data,
      qt_meta_data_TSettingBtnBar,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TSettingBtnBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TSettingBtnBar::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TSettingBtnBar.stringdata0))
        return static_cast<void*>(const_cast< TSettingBtnBar*>(this));
    return QWidget::qt_metacast(_clname);
}

int TSettingBtnBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void TSettingBtnBar::sigSettingBtn(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TSettingBtnBar::sigCloset(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
