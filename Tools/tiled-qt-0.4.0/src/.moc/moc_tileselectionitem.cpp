/****************************************************************************
** Meta object code from reading C++ file 'tileselectionitem.h'
**
** Created: Fri Apr 2 13:41:02 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../tileselectionitem.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tileselectionitem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Tiled__Internal__TileSelectionItem[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      62,   36,   35,   35, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Tiled__Internal__TileSelectionItem[] = {
    "Tiled::Internal::TileSelectionItem\0\0"
    "newSelection,oldSelection\0"
    "selectionChanged(QRegion,QRegion)\0"
};

const QMetaObject Tiled::Internal::TileSelectionItem::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Tiled__Internal__TileSelectionItem,
      qt_meta_data_Tiled__Internal__TileSelectionItem, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Tiled::Internal::TileSelectionItem::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Tiled::Internal::TileSelectionItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Tiled::Internal::TileSelectionItem::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Tiled__Internal__TileSelectionItem))
        return static_cast<void*>(const_cast< TileSelectionItem*>(this));
    if (!strcmp(_clname, "QGraphicsItem"))
        return static_cast< QGraphicsItem*>(const_cast< TileSelectionItem*>(this));
    if (!strcmp(_clname, "com.trolltech.Qt.QGraphicsItem"))
        return static_cast< QGraphicsItem*>(const_cast< TileSelectionItem*>(this));
    return QObject::qt_metacast(_clname);
}

int Tiled::Internal::TileSelectionItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: selectionChanged((*reinterpret_cast< const QRegion(*)>(_a[1])),(*reinterpret_cast< const QRegion(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
