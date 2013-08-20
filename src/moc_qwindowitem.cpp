/****************************************************************************
** Meta object code from reading C++ file 'qwindowitem.h'
**
** Created: Tue Aug 20 11:47:56 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qwindowitem.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qwindowitem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QWindowItem[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
      14,   99, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      13,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,
      27,   12,   12,   12, 0x05,
      38,   12,   12,   12, 0x05,
      49,   12,   12,   12, 0x05,
      66,   12,   12,   12, 0x05,
      92,   12,   12,   12, 0x05,
     113,   12,   12,   12, 0x05,
     136,   12,   12,   12, 0x05,
     158,   12,   12,   12, 0x05,
     181,   12,   12,   12, 0x05,
     203,   12,   12,   12, 0x05,
     218,   12,   12,   12, 0x05,
     236,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
     259,   12,   12,   12, 0x0a,
     275,  267,   12,   12, 0x09,
     293,   12,   12,   12, 0x09,
     312,  302,   12,   12, 0x09,

 // properties: name, type, flags
     344,  340, 0x02495103,
     346,  340, 0x02495103,
     348,  340, 0x02495103,
     355,  340, 0x02495103,
     361,  340, 0x02495103,
     375,  340, 0x02495103,
     389,  340, 0x02495103,
     402,  340, 0x02495103,
     420,  415, 0x01495103,
     428,  415, 0x01495103,
     445,  415, 0x01495103,
     451,  415, 0x01495103,
     481,  465, 0x0049510b,
     501,  493, 0x0a495103,

 // properties: notify_signal_id
       1,
       2,
       0,
       0,
       6,
       8,
       7,
       9,
       3,
       4,
      11,
      12,
       5,
      10,

       0        // eod
};

static const char qt_meta_stringdata_QWindowItem[] = {
    "QWindowItem\0\0sizeChanged()\0xChanged()\0"
    "yChanged()\0visibleChanged()\0"
    "windowDecorationChanged()\0"
    "windowStateChanged()\0minimumHeightChanged()\0"
    "minimumWidthChanged()\0maximumHeightChanged()\0"
    "maximumWidthChanged()\0titleChanged()\0"
    "modalityChanged()\0deleteOnCloseChanged()\0"
    "close()\0newSize\0updateSize(QSize)\0"
    "center()\0x,y,lx,ly\0moveWindow(int,int,int,int)\0"
    "int\0x\0y\0height\0width\0minimumHeight\0"
    "maximumHeight\0minimumWidth\0maximumWidth\0"
    "bool\0visible\0windowDecoration\0modal\0"
    "deleteOnClose\0Qt::WindowState\0windowState\0"
    "QString\0title\0"
};

void QWindowItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QWindowItem *_t = static_cast<QWindowItem *>(_o);
        switch (_id) {
        case 0: _t->sizeChanged(); break;
        case 1: _t->xChanged(); break;
        case 2: _t->yChanged(); break;
        case 3: _t->visibleChanged(); break;
        case 4: _t->windowDecorationChanged(); break;
        case 5: _t->windowStateChanged(); break;
        case 6: _t->minimumHeightChanged(); break;
        case 7: _t->minimumWidthChanged(); break;
        case 8: _t->maximumHeightChanged(); break;
        case 9: _t->maximumWidthChanged(); break;
        case 10: _t->titleChanged(); break;
        case 11: _t->modalityChanged(); break;
        case 12: _t->deleteOnCloseChanged(); break;
        case 13: _t->close(); break;
        case 14: _t->updateSize((*reinterpret_cast< QSize(*)>(_a[1]))); break;
        case 15: _t->center(); break;
        case 16: _t->moveWindow((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QWindowItem::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QWindowItem::staticMetaObject = {
    { &QDeclarativeItem::staticMetaObject, qt_meta_stringdata_QWindowItem,
      qt_meta_data_QWindowItem, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QWindowItem::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QWindowItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QWindowItem::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QWindowItem))
        return static_cast<void*>(const_cast< QWindowItem*>(this));
    return QDeclarativeItem::qt_metacast(_clname);
}

int QWindowItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDeclarativeItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = x(); break;
        case 1: *reinterpret_cast< int*>(_v) = y(); break;
        case 2: *reinterpret_cast< int*>(_v) = height(); break;
        case 3: *reinterpret_cast< int*>(_v) = width(); break;
        case 4: *reinterpret_cast< int*>(_v) = minimumHeight(); break;
        case 5: *reinterpret_cast< int*>(_v) = maximumHeight(); break;
        case 6: *reinterpret_cast< int*>(_v) = minimumWidth(); break;
        case 7: *reinterpret_cast< int*>(_v) = maximumWidth(); break;
        case 8: *reinterpret_cast< bool*>(_v) = isVisible(); break;
        case 9: *reinterpret_cast< bool*>(_v) = windowDecoration(); break;
        case 10: *reinterpret_cast< bool*>(_v) = modal(); break;
        case 11: *reinterpret_cast< bool*>(_v) = deleteOnClose(); break;
        case 12: *reinterpret_cast< Qt::WindowState*>(_v) = windowState(); break;
        case 13: *reinterpret_cast< QString*>(_v) = title(); break;
        }
        _id -= 14;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setX(*reinterpret_cast< int*>(_v)); break;
        case 1: setY(*reinterpret_cast< int*>(_v)); break;
        case 2: setHeight(*reinterpret_cast< int*>(_v)); break;
        case 3: setWidth(*reinterpret_cast< int*>(_v)); break;
        case 4: setMinimumHeight(*reinterpret_cast< int*>(_v)); break;
        case 5: setMaximumHeight(*reinterpret_cast< int*>(_v)); break;
        case 6: setMinimumWidth(*reinterpret_cast< int*>(_v)); break;
        case 7: setMaximumWidth(*reinterpret_cast< int*>(_v)); break;
        case 8: setVisible(*reinterpret_cast< bool*>(_v)); break;
        case 9: setWindowDecoration(*reinterpret_cast< bool*>(_v)); break;
        case 10: setModal(*reinterpret_cast< bool*>(_v)); break;
        case 11: setDeleteOnClose(*reinterpret_cast< bool*>(_v)); break;
        case 12: setWindowState(*reinterpret_cast< Qt::WindowState*>(_v)); break;
        case 13: setTitle(*reinterpret_cast< QString*>(_v)); break;
        }
        _id -= 14;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 14;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 14;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QWindowItem::sizeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QWindowItem::xChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void QWindowItem::yChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void QWindowItem::visibleChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void QWindowItem::windowDecorationChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void QWindowItem::windowStateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void QWindowItem::minimumHeightChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void QWindowItem::minimumWidthChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}

// SIGNAL 8
void QWindowItem::maximumHeightChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}

// SIGNAL 9
void QWindowItem::maximumWidthChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 9, 0);
}

// SIGNAL 10
void QWindowItem::titleChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 10, 0);
}

// SIGNAL 11
void QWindowItem::modalityChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 11, 0);
}

// SIGNAL 12
void QWindowItem::deleteOnCloseChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 12, 0);
}
QT_END_MOC_NAMESPACE
