/****************************************************************************
** Meta object code from reading C++ file 'CUdpConnection.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Network/CUdpConnection.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CUdpConnection.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CUdpConnection_t {
    QByteArrayData data[9];
    char stringdata0[85];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CUdpConnection_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CUdpConnection_t qt_meta_stringdata_CUdpConnection = {
    {
QT_MOC_LITERAL(0, 0, 14), // "CUdpConnection"
QT_MOC_LITERAL(1, 15, 11), // "sigRecvLine"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 5), // "strIp"
QT_MOC_LITERAL(4, 34, 5), // "nPort"
QT_MOC_LITERAL(5, 40, 6), // "strMsg"
QT_MOC_LITERAL(6, 47, 7), // "sigRecv"
QT_MOC_LITERAL(7, 55, 22), // "sigConnectStateChanged"
QT_MOC_LITERAL(8, 78, 6) // "bState"

    },
    "CUdpConnection\0sigRecvLine\0\0strIp\0"
    "nPort\0strMsg\0sigRecv\0sigConnectStateChanged\0"
    "bState"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CUdpConnection[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   29,    2, 0x06 /* Public */,
       6,    3,   36,    2, 0x06 /* Public */,
       7,    3,   43,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::QString,    3,    4,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::QString,    3,    4,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Bool,    3,    4,    8,

       0        // eod
};

void CUdpConnection::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CUdpConnection *_t = static_cast<CUdpConnection *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigRecvLine((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 1: _t->sigRecv((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 2: _t->sigConnectStateChanged((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CUdpConnection::*_t)(QString , int , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CUdpConnection::sigRecvLine)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CUdpConnection::*_t)(QString , int , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CUdpConnection::sigRecv)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (CUdpConnection::*_t)(QString , int , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CUdpConnection::sigConnectStateChanged)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject CUdpConnection::staticMetaObject = {
    { &AbsConnection::staticMetaObject, qt_meta_stringdata_CUdpConnection.data,
      qt_meta_data_CUdpConnection,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CUdpConnection::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CUdpConnection::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CUdpConnection.stringdata0))
        return static_cast<void*>(const_cast< CUdpConnection*>(this));
    return AbsConnection::qt_metacast(_clname);
}

int CUdpConnection::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbsConnection::qt_metacall(_c, _id, _a);
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
void CUdpConnection::sigRecvLine(QString _t1, int _t2, QString _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CUdpConnection::sigRecv(QString _t1, int _t2, QString _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CUdpConnection::sigConnectStateChanged(QString _t1, int _t2, bool _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
