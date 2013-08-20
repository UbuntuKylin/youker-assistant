/****************************************************************************
** Meta object code from reading C++ file 'qrangemodel.h'
**
** Created: Tue Aug 20 11:47:43 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qrangemodel.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qrangemodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QRangeModel[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       8,   84, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: signature, parameters, type, tag, flags
      19,   13,   12,   12, 0x05,
      48,   39,   12,   12, 0x05,
      80,   71,   12,   12, 0x05,
     112,  103,   12,   12, 0x05,
     138,  134,   12,   12, 0x05,
     164,  160,   12,   12, 0x05,
     186,  134,   12,   12, 0x05,
     218,  160,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
     250,   12,   12,   12, 0x0a,
     262,   12,   12,   12, 0x0a,
     274,   13,   12,   12, 0x0a,
     290,   39,   12,   12, 0x0a,

 // methods: signature, parameters, type, tag, flags
     315,   39,  309,   12, 0x02,
     339,   13,  309,   12, 0x02,

 // properties: name, type, flags
      13,  309, ((uint)QMetaType::QReal << 24) | 0x00595103,
     363,  309, ((uint)QMetaType::QReal << 24) | 0x00495003,
     376,  309, ((uint)QMetaType::QReal << 24) | 0x00495003,
      71,  309, ((uint)QMetaType::QReal << 24) | 0x00495103,
      39,  309, ((uint)QMetaType::QReal << 24) | 0x00495103,
     389,  309, ((uint)QMetaType::QReal << 24) | 0x00495103,
     407,  309, ((uint)QMetaType::QReal << 24) | 0x00495103,
     103,  425, 0x01495103,

 // properties: notify_signal_id
       0,
       4,
       5,
       2,
       1,
       6,
       7,
       3,

       0        // eod
};

static const char qt_meta_stringdata_QRangeModel[] = {
    "QRangeModel\0\0value\0valueChanged(qreal)\0"
    "position\0positionChanged(qreal)\0"
    "stepSize\0stepSizeChanged(qreal)\0"
    "inverted\0invertedChanged(bool)\0min\0"
    "minimumChanged(qreal)\0max\0"
    "maximumChanged(qreal)\0"
    "positionAtMinimumChanged(qreal)\0"
    "positionAtMaximumChanged(qreal)\0"
    "toMinimum()\0toMaximum()\0setValue(qreal)\0"
    "setPosition(qreal)\0qreal\0"
    "valueForPosition(qreal)\0positionForValue(qreal)\0"
    "minimumValue\0maximumValue\0positionAtMinimum\0"
    "positionAtMaximum\0bool\0"
};

void QRangeModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QRangeModel *_t = static_cast<QRangeModel *>(_o);
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 1: _t->positionChanged((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 2: _t->stepSizeChanged((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 3: _t->invertedChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->minimumChanged((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 5: _t->maximumChanged((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 6: _t->positionAtMinimumChanged((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 7: _t->positionAtMaximumChanged((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 8: _t->toMinimum(); break;
        case 9: _t->toMaximum(); break;
        case 10: _t->setValue((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 11: _t->setPosition((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 12: { qreal _r = _t->valueForPosition((*reinterpret_cast< qreal(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< qreal*>(_a[0]) = _r; }  break;
        case 13: { qreal _r = _t->positionForValue((*reinterpret_cast< qreal(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< qreal*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QRangeModel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QRangeModel::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QRangeModel,
      qt_meta_data_QRangeModel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QRangeModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QRangeModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QRangeModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QRangeModel))
        return static_cast<void*>(const_cast< QRangeModel*>(this));
    return QObject::qt_metacast(_clname);
}

int QRangeModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< qreal*>(_v) = value(); break;
        case 1: *reinterpret_cast< qreal*>(_v) = minimum(); break;
        case 2: *reinterpret_cast< qreal*>(_v) = maximum(); break;
        case 3: *reinterpret_cast< qreal*>(_v) = stepSize(); break;
        case 4: *reinterpret_cast< qreal*>(_v) = position(); break;
        case 5: *reinterpret_cast< qreal*>(_v) = positionAtMinimum(); break;
        case 6: *reinterpret_cast< qreal*>(_v) = positionAtMaximum(); break;
        case 7: *reinterpret_cast< bool*>(_v) = inverted(); break;
        }
        _id -= 8;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setValue(*reinterpret_cast< qreal*>(_v)); break;
        case 1: setMinimum(*reinterpret_cast< qreal*>(_v)); break;
        case 2: setMaximum(*reinterpret_cast< qreal*>(_v)); break;
        case 3: setStepSize(*reinterpret_cast< qreal*>(_v)); break;
        case 4: setPosition(*reinterpret_cast< qreal*>(_v)); break;
        case 5: setPositionAtMinimum(*reinterpret_cast< qreal*>(_v)); break;
        case 6: setPositionAtMaximum(*reinterpret_cast< qreal*>(_v)); break;
        case 7: setInverted(*reinterpret_cast< bool*>(_v)); break;
        }
        _id -= 8;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 8;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 8;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QRangeModel::valueChanged(qreal _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QRangeModel::positionChanged(qreal _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QRangeModel::stepSizeChanged(qreal _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QRangeModel::invertedChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QRangeModel::minimumChanged(qreal _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QRangeModel::maximumChanged(qreal _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void QRangeModel::positionAtMinimumChanged(qreal _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void QRangeModel::positionAtMaximumChanged(qreal _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_END_MOC_NAMESPACE
