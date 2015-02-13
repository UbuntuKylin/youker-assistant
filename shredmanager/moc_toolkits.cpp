/****************************************************************************
** Meta object code from reading C++ file 'toolkits.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../component/toolkits.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'toolkits.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Toolkits[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x08,
      24,    9,    9,    9, 0x08,

 // methods: signature, parameters, type, tag, flags
      46,   36,    9,    9, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_Toolkits[] = {
    "Toolkits\0\0updateAlert()\0hideAlert()\0"
    "alertText\0alertMSG(QString)\0"
};

void Toolkits::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Toolkits *_t = static_cast<Toolkits *>(_o);
        switch (_id) {
        case 0: _t->updateAlert(); break;
        case 1: _t->hideAlert(); break;
        case 2: _t->alertMSG((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Toolkits::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Toolkits::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Toolkits,
      qt_meta_data_Toolkits, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Toolkits::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Toolkits::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Toolkits::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Toolkits))
        return static_cast<void*>(const_cast< Toolkits*>(this));
    return QObject::qt_metacast(_clname);
}

int Toolkits::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
