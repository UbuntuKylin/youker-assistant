/****************************************************************************
** Meta object code from reading C++ file 'qtmenu.h'
**
** Created: Tue Aug 20 11:47:48 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qtmenu.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtmenu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QtMenu[] = {

 // content:
       6,       // revision
       0,       // classname
       1,   14, // classinfo
      19,   16, // methods
       5,  111, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // classinfo: key, value
      17,    7,

 // signals: signature, parameters, type, tag, flags
      34,   33,   33,   33, 0x05,
      47,   33,   33,   33, 0x05,
      70,   33,   33,   33, 0x05,
     101,   92,   33,   33, 0x05,
     124,   33,   33,   33, 0x05,

 // slots: signature, parameters, type, tag, flags
     137,   92,   33,   33, 0x0a,
     156,   33,   33,   33, 0x08,
     171,   33,   33,   33, 0x08,

 // methods: signature, parameters, type, tag, flags
     189,   33,  185,   33, 0x02,
     206,  204,   33,   33, 0x02,
     245,  227,   33,   33, 0x02,
     276,  272,   33,   33, 0x22,
     299,   33,   33,   33, 0x02,
     311,   33,   33,   33, 0x02,
     333,  328,   33,   33, 0x02,
     368,  362,  354,   33, 0x02,
     384,  362,  354,   33, 0x02,
     401,   33,  185,   33, 0x02,
     419,   33,  414,   33, 0x02,

 // properties: name, type, flags
     328,  354, 0x0a095103,
     445,  436, 0xff495103,
     451,  185, 0x02495103,
     465,  185, 0x02495103,
       7,  478, 0x00095009,

 // properties: notify_signal_id
       0,
       3,
       1,
       2,
       0,

       0        // eod
};

static const char qt_meta_stringdata_QtMenu[] = {
    "QtMenu\0menuItems\0DefaultProperty\0\0"
    "menuClosed()\0selectedIndexChanged()\0"
    "hoveredIndexChanged()\0newModel\0"
    "modelChanged(QVariant)\0rebuldMenu()\0"
    "setModel(QVariant)\0emitSelected()\0"
    "emitHovered()\0int\0minimumWidth()\0w\0"
    "setMinimumWidth(int)\0x,y,atActionIndex\0"
    "showPopup(qreal,qreal,int)\0x,y\0"
    "showPopup(qreal,qreal)\0hidePopup()\0"
    "clearMenuItems()\0text\0addMenuItem(QString)\0"
    "QString\0index\0itemTextAt(int)\0"
    "modelTextAt(int)\0modelCount()\0bool\0"
    "hasNativeModel()\0QVariant\0model\0"
    "selectedIndex\0hoveredIndex\0"
    "QDeclarativeListProperty<QtMenuBase>\0"
};

void QtMenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QtMenu *_t = static_cast<QtMenu *>(_o);
        switch (_id) {
        case 0: _t->menuClosed(); break;
        case 1: _t->selectedIndexChanged(); break;
        case 2: _t->hoveredIndexChanged(); break;
        case 3: _t->modelChanged((*reinterpret_cast< const QVariant(*)>(_a[1]))); break;
        case 4: _t->rebuldMenu(); break;
        case 5: _t->setModel((*reinterpret_cast< const QVariant(*)>(_a[1]))); break;
        case 6: _t->emitSelected(); break;
        case 7: _t->emitHovered(); break;
        case 8: { int _r = _t->minimumWidth();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 9: _t->setMinimumWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->showPopup((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 11: _t->showPopup((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2]))); break;
        case 12: _t->hidePopup(); break;
        case 13: _t->clearMenuItems(); break;
        case 14: _t->addMenuItem((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 15: { QString _r = _t->itemTextAt((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 16: { QString _r = _t->modelTextAt((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 17: { int _r = _t->modelCount();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 18: { bool _r = _t->hasNativeModel();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QtMenu::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QtMenu::staticMetaObject = {
    { &QtMenuBase::staticMetaObject, qt_meta_stringdata_QtMenu,
      qt_meta_data_QtMenu, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QtMenu::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QtMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QtMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtMenu))
        return static_cast<void*>(const_cast< QtMenu*>(this));
    return QtMenuBase::qt_metacast(_clname);
}

int QtMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QtMenuBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = text(); break;
        case 1: *reinterpret_cast< QVariant*>(_v) = model(); break;
        case 2: *reinterpret_cast< int*>(_v) = selectedIndex(); break;
        case 3: *reinterpret_cast< int*>(_v) = hoveredIndex(); break;
        case 4: *reinterpret_cast< QDeclarativeListProperty<QtMenuBase>*>(_v) = menuItems(); break;
        }
        _id -= 5;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setText(*reinterpret_cast< QString*>(_v)); break;
        case 1: setModel(*reinterpret_cast< QVariant*>(_v)); break;
        case 2: setSelectedIndex(*reinterpret_cast< int*>(_v)); break;
        case 3: setHoveredIndex(*reinterpret_cast< int*>(_v)); break;
        }
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
void QtMenu::menuClosed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QtMenu::selectedIndexChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void QtMenu::hoveredIndexChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void QtMenu::modelChanged(const QVariant & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QtMenu::rebuldMenu()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}
QT_END_MOC_NAMESPACE
