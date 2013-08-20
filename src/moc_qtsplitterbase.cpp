/****************************************************************************
** Meta object code from reading C++ file 'qtsplitterbase.h'
**
** Created: Tue Aug 20 11:47:58 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qtsplitterbase.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtsplitterbase.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QtSplitterAttached[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       7,   49, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   20,   19,   19, 0x05,
      51,   20,   19,   19, 0x05,
      78,   20,   19,   19, 0x05,
     106,   20,   19,   19, 0x05,
     134,   20,   19,   19, 0x05,
     157,   20,   19,   19, 0x05,
     184,   20,   19,   19, 0x05,

 // properties: name, type, flags
     212,  206, ((uint)QMetaType::QReal << 24) | 0x00495103,
     225,  206, ((uint)QMetaType::QReal << 24) | 0x00495103,
     238,  206, ((uint)QMetaType::QReal << 24) | 0x00495103,
     252,  206, ((uint)QMetaType::QReal << 24) | 0x00495103,
     266,  206, ((uint)QMetaType::QReal << 24) | 0x00495103,
     286,  281, 0x01495103,
     300,  296, 0x02495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       5,
       4,
       6,

       0        // eod
};

static const char qt_meta_stringdata_QtSplitterAttached[] = {
    "QtSplitterAttached\0\0arg\0"
    "minimumWidthChanged(qreal)\0"
    "maximumWidthChanged(qreal)\0"
    "minimumHeightChanged(qreal)\0"
    "maximumHeightChanged(qreal)\0"
    "expandingChanged(bool)\0"
    "percentageWidthSize(qreal)\0"
    "itemIndexChanged(int)\0qreal\0minimumWidth\0"
    "maximumWidth\0minimumHeight\0maximumHeight\0"
    "percentageSize\0bool\0expanding\0int\0"
    "itemIndex\0"
};

void QtSplitterAttached::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QtSplitterAttached *_t = static_cast<QtSplitterAttached *>(_o);
        switch (_id) {
        case 0: _t->minimumWidthChanged((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 1: _t->maximumWidthChanged((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 2: _t->minimumHeightChanged((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 3: _t->maximumHeightChanged((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 4: _t->expandingChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->percentageWidthSize((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 6: _t->itemIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QtSplitterAttached::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QtSplitterAttached::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QtSplitterAttached,
      qt_meta_data_QtSplitterAttached, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QtSplitterAttached::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QtSplitterAttached::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QtSplitterAttached::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtSplitterAttached))
        return static_cast<void*>(const_cast< QtSplitterAttached*>(this));
    return QObject::qt_metacast(_clname);
}

int QtSplitterAttached::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< qreal*>(_v) = minimumWidth(); break;
        case 1: *reinterpret_cast< qreal*>(_v) = maximumWidth(); break;
        case 2: *reinterpret_cast< qreal*>(_v) = minimumHeight(); break;
        case 3: *reinterpret_cast< qreal*>(_v) = maximumHeight(); break;
        case 4: *reinterpret_cast< qreal*>(_v) = percentageSize(); break;
        case 5: *reinterpret_cast< bool*>(_v) = expanding(); break;
        case 6: *reinterpret_cast< int*>(_v) = itemIndex(); break;
        }
        _id -= 7;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setMinimumWidth(*reinterpret_cast< qreal*>(_v)); break;
        case 1: setMaximumWidth(*reinterpret_cast< qreal*>(_v)); break;
        case 2: setMinimumHeight(*reinterpret_cast< qreal*>(_v)); break;
        case 3: setMaximumHeight(*reinterpret_cast< qreal*>(_v)); break;
        case 4: setPercentageSize(*reinterpret_cast< qreal*>(_v)); break;
        case 5: setExpanding(*reinterpret_cast< bool*>(_v)); break;
        case 6: setItemIndex(*reinterpret_cast< int*>(_v)); break;
        }
        _id -= 7;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 7;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QtSplitterAttached::minimumWidthChanged(qreal _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QtSplitterAttached::maximumWidthChanged(qreal _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QtSplitterAttached::minimumHeightChanged(qreal _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QtSplitterAttached::maximumHeightChanged(qreal _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QtSplitterAttached::expandingChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QtSplitterAttached::percentageWidthSize(qreal _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void QtSplitterAttached::itemIndexChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
static const uint qt_meta_data_QtSplitterBase[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_QtSplitterBase[] = {
    "QtSplitterBase\0"
};

void QtSplitterBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QtSplitterBase::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QtSplitterBase::staticMetaObject = {
    { &QDeclarativeItem::staticMetaObject, qt_meta_stringdata_QtSplitterBase,
      qt_meta_data_QtSplitterBase, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QtSplitterBase::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QtSplitterBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QtSplitterBase::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtSplitterBase))
        return static_cast<void*>(const_cast< QtSplitterBase*>(this));
    return QDeclarativeItem::qt_metacast(_clname);
}

int QtSplitterBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDeclarativeItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
