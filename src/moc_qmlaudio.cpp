/****************************************************************************
** Meta object code from reading C++ file 'qmlaudio.h'
**
** Created: Tue Aug 20 11:47:42 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qmlaudio.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qmlaudio.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QmlAudio[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   10,    9,    9, 0x0a,
      32,    9,    9,    9, 0x0a,
      39,    9,    9,    9, 0x0a,
      47,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QmlAudio[] = {
    "QmlAudio\0\0songUrl\0setSong(QUrl)\0play()\0"
    "pause()\0stop()\0"
};

void QmlAudio::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QmlAudio *_t = static_cast<QmlAudio *>(_o);
        switch (_id) {
        case 0: _t->setSong((*reinterpret_cast< const QUrl(*)>(_a[1]))); break;
        case 1: _t->play(); break;
        case 2: _t->pause(); break;
        case 3: _t->stop(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QmlAudio::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QmlAudio::staticMetaObject = {
    { &QDeclarativeItem::staticMetaObject, qt_meta_stringdata_QmlAudio,
      qt_meta_data_QmlAudio, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QmlAudio::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QmlAudio::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QmlAudio::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QmlAudio))
        return static_cast<void*>(const_cast< QmlAudio*>(this));
    return QDeclarativeItem::qt_metacast(_clname);
}

int QmlAudio::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDeclarativeItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
