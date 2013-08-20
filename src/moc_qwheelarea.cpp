/****************************************************************************
** Meta object code from reading C++ file 'qwheelarea.h'
**
** Created: Tue Aug 20 11:47:47 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qwheelarea.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qwheelarea.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QWheelArea[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       9,   39, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      35,   11,   11,   11, 0x05,
      60,   11,   11,   11, 0x05,
      81,   11,   11,   11, 0x05,
     104,   11,   11,   11, 0x05,

 // properties: name, type, flags
     131,  125, ((uint)QMetaType::QReal << 24) | 0x00495103,
     145,  125, ((uint)QMetaType::QReal << 24) | 0x00495103,
     161,  125, ((uint)QMetaType::QReal << 24) | 0x00095103,
     184,  125, ((uint)QMetaType::QReal << 24) | 0x00095103,
     207,  125, ((uint)QMetaType::QReal << 24) | 0x00095103,
     228,  125, ((uint)QMetaType::QReal << 24) | 0x00095103,
     249,  125, ((uint)QMetaType::QReal << 24) | 0x00095103,
     265,  125, ((uint)QMetaType::QReal << 24) | 0x00095103,
     279,  125, ((uint)QMetaType::QReal << 24) | 0x00495103,

 // properties: notify_signal_id
       2,
       3,
       0,
       0,
       0,
       0,
       0,
       0,
       4,

       0        // eod
};

static const char qt_meta_stringdata_QWheelArea[] = {
    "QWheelArea\0\0verticalValueChanged()\0"
    "horizontalValueChanged()\0verticalWheelMoved()\0"
    "horizontalWheelMoved()\0scrollSpeedChanged()\0"
    "qreal\0verticalDelta\0horizontalDelta\0"
    "horizontalMinimumValue\0horizontalMaximumValue\0"
    "verticalMinimumValue\0verticalMaximumValue\0"
    "horizontalValue\0verticalValue\0scrollSpeed\0"
};

void QWheelArea::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QWheelArea *_t = static_cast<QWheelArea *>(_o);
        switch (_id) {
        case 0: _t->verticalValueChanged(); break;
        case 1: _t->horizontalValueChanged(); break;
        case 2: _t->verticalWheelMoved(); break;
        case 3: _t->horizontalWheelMoved(); break;
        case 4: _t->scrollSpeedChanged(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QWheelArea::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QWheelArea::staticMetaObject = {
    { &QDeclarativeItem::staticMetaObject, qt_meta_stringdata_QWheelArea,
      qt_meta_data_QWheelArea, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QWheelArea::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QWheelArea::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QWheelArea::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QWheelArea))
        return static_cast<void*>(const_cast< QWheelArea*>(this));
    return QDeclarativeItem::qt_metacast(_clname);
}

int QWheelArea::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDeclarativeItem::qt_metacall(_c, _id, _a);
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
        case 0: *reinterpret_cast< qreal*>(_v) = verticalDelta(); break;
        case 1: *reinterpret_cast< qreal*>(_v) = horizontalDelta(); break;
        case 2: *reinterpret_cast< qreal*>(_v) = horizontalMinimumValue(); break;
        case 3: *reinterpret_cast< qreal*>(_v) = horizontalMaximumValue(); break;
        case 4: *reinterpret_cast< qreal*>(_v) = verticalMinimumValue(); break;
        case 5: *reinterpret_cast< qreal*>(_v) = verticalMaximumValue(); break;
        case 6: *reinterpret_cast< qreal*>(_v) = horizontalValue(); break;
        case 7: *reinterpret_cast< qreal*>(_v) = verticalValue(); break;
        case 8: *reinterpret_cast< qreal*>(_v) = scrollSpeed(); break;
        }
        _id -= 9;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setVerticalDelta(*reinterpret_cast< qreal*>(_v)); break;
        case 1: setHorizontalDelta(*reinterpret_cast< qreal*>(_v)); break;
        case 2: setHorizontalMinimumValue(*reinterpret_cast< qreal*>(_v)); break;
        case 3: setHorizontalMaximumValue(*reinterpret_cast< qreal*>(_v)); break;
        case 4: setVerticalMinimumValue(*reinterpret_cast< qreal*>(_v)); break;
        case 5: setVerticalMaximumValue(*reinterpret_cast< qreal*>(_v)); break;
        case 6: setHorizontalValue(*reinterpret_cast< qreal*>(_v)); break;
        case 7: setVerticalValue(*reinterpret_cast< qreal*>(_v)); break;
        case 8: setScrollSpeed(*reinterpret_cast< qreal*>(_v)); break;
        }
        _id -= 9;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 9;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QWheelArea::verticalValueChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QWheelArea::horizontalValueChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void QWheelArea::verticalWheelMoved()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void QWheelArea::horizontalWheelMoved()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void QWheelArea::scrollSpeedChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}
QT_END_MOC_NAMESPACE
