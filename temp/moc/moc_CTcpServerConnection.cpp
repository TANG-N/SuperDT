/****************************************************************************
** Meta object code from reading C++ file 'CTcpServerConnection.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Network/CTcpServerConnection.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CTcpServerConnection.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CTcpServerConnection_t {
    QByteArrayData data[6];
    char stringdata0[53];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CTcpServerConnection_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CTcpServerConnection_t qt_meta_stringdata_CTcpServerConnection = {
    {
QT_MOC_LITERAL(0, 0, 20), // "CTcpServerConnection"
QT_MOC_LITERAL(1, 21, 11), // "sigRecvLine"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 5), // "strIp"
QT_MOC_LITERAL(4, 40, 5), // "nPort"
QT_MOC_LITERAL(5, 46, 6) // "strMsg"

    },
    "CTcpServerConnection\0sigRecvLine\0\0"
    "strIp\0nPort\0strMsg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CTcpServerConnection[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::QString,    3,    4,    5,

       0        // eod
};

void CTcpServerConnection::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CTcpServerConnection *_t = static_cast<CTcpServerConnection *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigRecvLine((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CTcpServerConnection::*_t)(QString , int , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CTcpServerConnection::sigRecvLine)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject CTcpServerConnection::staticMetaObject = {
    { &AbsConnection::staticMetaObject, qt_meta_stringdata_CTcpServerConnection.data,
      qt_meta_data_CTcpServerConnection,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CTcpServerConnection::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CTcpServerConnection::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CTcpServerConnection.stringdata0))
        return static_cast<void*>(const_cast< CTcpServerConnection*>(this));
    return AbsConnection::qt_metacast(_clname);
}

int CTcpServerConnection::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbsConnection::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void CTcpServerConnection::sigRecvLine(QString _t1, int _t2, QString _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
