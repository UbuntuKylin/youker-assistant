/****************************************************************************
** Meta object code from reading C++ file 'qdesktopitem.h'
**
** Created: Tue Aug 20 11:48:06 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qdesktopitem.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qdesktopitem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QDesktopItem[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       5,   39, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,
      38,   13,   13,   13, 0x05,
      65,   13,   13,   13, 0x05,

 // methods: signature, parameters, type, tag, flags
      99,   92,   86,   13, 0x02,
     119,   92,   86,   13, 0x02,

 // properties: name, type, flags
     146,  142, 0x02495001,
     158,  142, 0x02495001,
     171,  142, 0x02495001,
     186,  142, 0x02495001,
     202,  142, 0x02495001,

 // properties: notify_signal_id
       0,
       0,
       1,
       1,
       2,

       0        // eod
};

static const char qt_meta_stringdata_QDesktopItem[] = {
    "QDesktopItem\0\0screenGeometryChanged()\0"
    "availableGeometryChanged()\0"
    "screenCountChanged()\0QRect\0screen\0"
    "screenGeometry(int)\0availableGeometry(int)\0"
    "int\0screenWidth\0screenHeight\0"
    "availableWidth\0availableHeight\0"
    "screenCount\0"
};

void QDesktopItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QDesktopItem *_t = static_cast<QDesktopItem *>(_o);
        switch (_id) {
        case 0: _t->screenGeometryChanged(); break;
        case 1: _t->availableGeometryChanged(); break;
        case 2: _t->screenCountChanged(); break;
        case 3: { QRect _r = _t->screenGeometry((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QRect*>(_a[0]) = _r; }  break;
        case 4: { QRect _r = _t->availableGeometry((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QRect*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QDesktopItem::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QDesktopItem::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QDesktopItem,
      qt_meta_data_QDesktopItem, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QDesktopItem::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QDesktopItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QDesktopItem::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QDesktopItem))
        return static_cast<void*>(const_cast< QDesktopItem*>(this));
    return QObject::qt_metacast(_clname);
}

int QDesktopItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = screenWidth(); break;
        case 1: *reinterpret_cast< int*>(_v) = screenHeight(); break;
        case 2: *reinterpret_cast< int*>(_v) = availableWidth(); break;
        case 3: *reinterpret_cast< int*>(_v) = availableHeight(); break;
        case 4: *reinterpret_cast< int*>(_v) = screenCount(); break;
        }
        _id -= 5;
    } else if (_c == QMetaObject::WriteProperty) {
        _id -= 5;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QDesktopItem::screenGeometryChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QDesktopItem::availableGeometryChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void QDesktopItem::screenCountChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
