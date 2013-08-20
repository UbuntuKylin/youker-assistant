/****************************************************************************
** Meta object code from reading C++ file 'qtoplevelwindow.h'
**
** Created: Tue Aug 20 11:47:50 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qtoplevelwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtoplevelwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QTopLevelWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,
      37,   16,   16,   16, 0x05,
      66,   58,   16,   16, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_QTopLevelWindow[] = {
    "QTopLevelWindow\0\0visibilityChanged()\0"
    "windowStateChanged()\0newSize\0"
    "sizeChanged(QSize)\0"
};

void QTopLevelWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QTopLevelWindow *_t = static_cast<QTopLevelWindow *>(_o);
        switch (_id) {
        case 0: _t->visibilityChanged(); break;
        case 1: _t->windowStateChanged(); break;
        case 2: _t->sizeChanged((*reinterpret_cast< QSize(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QTopLevelWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QTopLevelWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_QTopLevelWindow,
      qt_meta_data_QTopLevelWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QTopLevelWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QTopLevelWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QTopLevelWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QTopLevelWindow))
        return static_cast<void*>(const_cast< QTopLevelWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int QTopLevelWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void QTopLevelWindow::visibilityChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QTopLevelWindow::windowStateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void QTopLevelWindow::sizeChanged(QSize _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
