/****************************************************************************
** Meta object code from reading C++ file 'Panel.h'
**
** Created: Tue Mar 9 10:41:27 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../GUI/Panel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Panel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Panel[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,    7,    6,    6, 0x08,
      38,    7,    6,    6, 0x08,
      60,    6,    6,    6, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Panel[] = {
    "Panel\0\0val\0updateSelectionStep(qreal)\0"
    "updateFlipStep(qreal)\0flip()\0"
};

const QMetaObject Panel::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_Panel,
      qt_meta_data_Panel, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Panel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Panel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Panel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Panel))
        return static_cast<void*>(const_cast< Panel*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int Panel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: updateSelectionStep((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 1: updateFlipStep((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 2: flip(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
