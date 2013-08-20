/****************************************************************************
** Meta object code from reading C++ file 'qcursorarea.h'
**
** Created: Tue Aug 20 11:47:52 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qcursorarea.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qcursorarea.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QCursorArea[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       1,   19, // properties
       1,   23, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,

 // properties: name, type, flags
      36,   29, 0x0049510b,

 // properties: notify_signal_id
       0,

 // enums: name, flags, count, data
      29, 0x0,    9,   27,

 // enum data: key, value
      43, uint(QCursorArea::DefaultCursor),
      57, uint(QCursorArea::ArrowCursor),
      69, uint(QCursorArea::SizeHorCursor),
      83, uint(QCursorArea::SizeVerCursor),
      97, uint(QCursorArea::SizeAllCursor),
     111, uint(QCursorArea::SplitHCursor),
     124, uint(QCursorArea::SplitVCursor),
     137, uint(QCursorArea::WaitCursor),
     148, uint(QCursorArea::PointingHandCursor),

       0        // eod
};

static const char qt_meta_stringdata_QCursorArea[] = {
    "QCursorArea\0\0cursorChanged()\0Cursor\0"
    "cursor\0DefaultCursor\0ArrowCursor\0"
    "SizeHorCursor\0SizeVerCursor\0SizeAllCursor\0"
    "SplitHCursor\0SplitVCursor\0WaitCursor\0"
    "PointingHandCursor\0"
};

void QCursorArea::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QCursorArea *_t = static_cast<QCursorArea *>(_o);
        switch (_id) {
        case 0: _t->cursorChanged(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QCursorArea::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QCursorArea::staticMetaObject = {
    { &QDeclarativeItem::staticMetaObject, qt_meta_stringdata_QCursorArea,
      qt_meta_data_QCursorArea, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QCursorArea::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QCursorArea::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QCursorArea::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QCursorArea))
        return static_cast<void*>(const_cast< QCursorArea*>(this));
    return QDeclarativeItem::qt_metacast(_clname);
}

int QCursorArea::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDeclarativeItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< Cursor*>(_v) = cursor(); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setCursor(*reinterpret_cast< Cursor*>(_v)); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QCursorArea::cursorChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
