/****************************************************************************
** Meta object code from reading C++ file 'qdeclarativelayout.h'
**
** Created: Tue Aug 20 11:48:05 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qdeclarativelayout.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qdeclarativelayout.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QDeclarativeLayout[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // enums: name, flags, count, data
      19, 0x0,    2,   18,

 // enum data: key, value
      30, uint(QDeclarativeLayout::Fixed),
      36, uint(QDeclarativeLayout::Expanding),

       0        // eod
};

static const char qt_meta_stringdata_QDeclarativeLayout[] = {
    "QDeclarativeLayout\0SizePolicy\0Fixed\0"
    "Expanding\0"
};

void QDeclarativeLayout::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QDeclarativeLayout::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QDeclarativeLayout::staticMetaObject = {
    { &QDeclarativeItem::staticMetaObject, qt_meta_stringdata_QDeclarativeLayout,
      qt_meta_data_QDeclarativeLayout, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QDeclarativeLayout::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QDeclarativeLayout::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QDeclarativeLayout::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QDeclarativeLayout))
        return static_cast<void*>(const_cast< QDeclarativeLayout*>(this));
    return QDeclarativeItem::qt_metacast(_clname);
}

int QDeclarativeLayout::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDeclarativeItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_QDeclarativeLayoutAttached[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       6,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
      33,   27, ((uint)QMetaType::QReal << 24) | 0x00095103,
      46,   27, ((uint)QMetaType::QReal << 24) | 0x00095103,
      60,   27, ((uint)QMetaType::QReal << 24) | 0x00095103,
      73,   27, ((uint)QMetaType::QReal << 24) | 0x00095103,
     118,   87, 0x0009510b,
     137,   87, 0x0009510b,

       0        // eod
};

static const char qt_meta_stringdata_QDeclarativeLayoutAttached[] = {
    "QDeclarativeLayoutAttached\0qreal\0"
    "minimumWidth\0minimumHeight\0maximumWidth\0"
    "maximumHeight\0QDeclarativeLayout::SizePolicy\0"
    "verticalSizePolicy\0horizontalSizePolicy\0"
};

void QDeclarativeLayoutAttached::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

#ifdef Q_NO_DATA_RELOCATION
static const QMetaObjectAccessor qt_meta_extradata_QDeclarativeLayoutAttached[] = {
        QDeclarativeLayout::getStaticMetaObject,
#else
static const QMetaObject *qt_meta_extradata_QDeclarativeLayoutAttached[] = {
        &QDeclarativeLayout::staticMetaObject,
#endif //Q_NO_DATA_RELOCATION
    0
};

const QMetaObjectExtraData QDeclarativeLayoutAttached::staticMetaObjectExtraData = {
    qt_meta_extradata_QDeclarativeLayoutAttached,  qt_static_metacall 
};

const QMetaObject QDeclarativeLayoutAttached::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QDeclarativeLayoutAttached,
      qt_meta_data_QDeclarativeLayoutAttached, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QDeclarativeLayoutAttached::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QDeclarativeLayoutAttached::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QDeclarativeLayoutAttached::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QDeclarativeLayoutAttached))
        return static_cast<void*>(const_cast< QDeclarativeLayoutAttached*>(this));
    return QObject::qt_metacast(_clname);
}

int QDeclarativeLayoutAttached::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
     if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< qreal*>(_v) = minimumWidth(); break;
        case 1: *reinterpret_cast< qreal*>(_v) = minimumHeight(); break;
        case 2: *reinterpret_cast< qreal*>(_v) = maximumWidth(); break;
        case 3: *reinterpret_cast< qreal*>(_v) = maximumHeight(); break;
        case 4: *reinterpret_cast< QDeclarativeLayout::SizePolicy*>(_v) = verticalSizePolicy(); break;
        case 5: *reinterpret_cast< QDeclarativeLayout::SizePolicy*>(_v) = horizontalSizePolicy(); break;
        }
        _id -= 6;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setMinimumWidth(*reinterpret_cast< qreal*>(_v)); break;
        case 1: setMinimumHeight(*reinterpret_cast< qreal*>(_v)); break;
        case 2: setMaximumWidth(*reinterpret_cast< qreal*>(_v)); break;
        case 3: setMaximumHeight(*reinterpret_cast< qreal*>(_v)); break;
        case 4: setVerticalSizePolicy(*reinterpret_cast< QDeclarativeLayout::SizePolicy*>(_v)); break;
        case 5: setHorizontalSizePolicy(*reinterpret_cast< QDeclarativeLayout::SizePolicy*>(_v)); break;
        }
        _id -= 6;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 6;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE
