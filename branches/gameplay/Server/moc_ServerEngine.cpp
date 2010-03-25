/****************************************************************************
** Meta object code from reading C++ file 'ServerEngine.h'
**
** Created: Wed Mar 24 21:25:33 2010
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "engine/ServerEngine.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ServerEngine.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ServerEngine[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ServerEngine[] = {
    "ServerEngine\0\0timeout()\0"
};

const QMetaObject ServerEngine::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ServerEngine,
      qt_meta_data_ServerEngine, 0 }
};

const QMetaObject *ServerEngine::metaObject() const
{
    return &staticMetaObject;
}

void *ServerEngine::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ServerEngine))
        return static_cast<void*>(const_cast< ServerEngine*>(this));
    return QObject::qt_metacast(_clname);
}

int ServerEngine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: timeout(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
