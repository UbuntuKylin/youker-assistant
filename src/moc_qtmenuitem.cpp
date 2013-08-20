/****************************************************************************
** Meta object code from reading C++ file 'qtmenuitem.h'
**
** Created: Tue Aug 20 11:47:49 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qtmenuitem.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtmenuitem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QtMenuBase[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       2,   24, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      32,   11,   11,   11, 0x05,

 // properties: name, type, flags
      55,   50, 0x11495103,
      74,   66, 0x0a495103,

 // properties: notify_signal_id
       0,
       1,

       0        // eod
};

static const char qt_meta_stringdata_QtMenuBase[] = {
    "QtMenuBase\0\0iconSourceChanged()\0"
    "iconNameChanged()\0QUrl\0iconSource\0"
    "QString\0iconName\0"
};

void QtMenuBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QtMenuBase *_t = static_cast<QtMenuBase *>(_o);
        switch (_id) {
        case 0: _t->iconSourceChanged(); break;
        case 1: _t->iconNameChanged(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QtMenuBase::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QtMenuBase::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QtMenuBase,
      qt_meta_data_QtMenuBase, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QtMenuBase::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QtMenuBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QtMenuBase::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtMenuBase))
        return static_cast<void*>(const_cast< QtMenuBase*>(this));
    return QObject::qt_metacast(_clname);
}

int QtMenuBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QUrl*>(_v) = iconSource(); break;
        case 1: *reinterpret_cast< QString*>(_v) = iconName(); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setIconSource(*reinterpret_cast< QUrl*>(_v)); break;
        case 1: setIconName(*reinterpret_cast< QString*>(_v)); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QtMenuBase::iconSourceChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QtMenuBase::iconNameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
static const uint qt_meta_data_QtMenuSeparator[] = {

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

static const char qt_meta_stringdata_QtMenuSeparator[] = {
    "QtMenuSeparator\0"
};

void QtMenuSeparator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QtMenuSeparator::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QtMenuSeparator::staticMetaObject = {
    { &QtMenuBase::staticMetaObject, qt_meta_stringdata_QtMenuSeparator,
      qt_meta_data_QtMenuSeparator, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QtMenuSeparator::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QtMenuSeparator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QtMenuSeparator::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtMenuSeparator))
        return static_cast<void*>(const_cast< QtMenuSeparator*>(this));
    return QtMenuBase::qt_metacast(_clname);
}

int QtMenuSeparator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QtMenuBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_QtMenuItem[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       5,   39, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      24,   11,   11,   11, 0x05,
      38,   11,   11,   11, 0x05,
      56,   11,   11,   11, 0x05,
      70,   11,   11,   11, 0x05,

 // properties: name, type, flags
      95,   87, 0x0a495103,
     100,   87, 0x0a495103,
     114,  109, 0x01095103,
     124,  109, 0x01495103,
     132,  109, 0x01495103,

 // properties: notify_signal_id
       1,
       2,
       0,
       3,
       4,

       0        // eod
};

static const char qt_meta_stringdata_QtMenuItem[] = {
    "QtMenuItem\0\0triggered()\0textChanged()\0"
    "shortcutChanged()\0toggled(bool)\0"
    "enabledChanged()\0QString\0text\0shortcut\0"
    "bool\0checkable\0checked\0enabled\0"
};

void QtMenuItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QtMenuItem *_t = static_cast<QtMenuItem *>(_o);
        switch (_id) {
        case 0: _t->triggered(); break;
        case 1: _t->textChanged(); break;
        case 2: _t->shortcutChanged(); break;
        case 3: _t->toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->enabledChanged(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QtMenuItem::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QtMenuItem::staticMetaObject = {
    { &QtMenuBase::staticMetaObject, qt_meta_stringdata_QtMenuItem,
      qt_meta_data_QtMenuItem, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QtMenuItem::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QtMenuItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QtMenuItem::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtMenuItem))
        return static_cast<void*>(const_cast< QtMenuItem*>(this));
    return QtMenuBase::qt_metacast(_clname);
}

int QtMenuItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QtMenuBase::qt_metacall(_c, _id, _a);
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
        case 0: *reinterpret_cast< QString*>(_v) = text(); break;
        case 1: *reinterpret_cast< QString*>(_v) = shortcut(); break;
        case 2: *reinterpret_cast< bool*>(_v) = checkable(); break;
        case 3: *reinterpret_cast< bool*>(_v) = checked(); break;
        case 4: *reinterpret_cast< bool*>(_v) = enabled(); break;
        }
        _id -= 5;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setText(*reinterpret_cast< QString*>(_v)); break;
        case 1: setShortcut(*reinterpret_cast< QString*>(_v)); break;
        case 2: setCheckable(*reinterpret_cast< bool*>(_v)); break;
        case 3: setChecked(*reinterpret_cast< bool*>(_v)); break;
        case 4: setEnabled(*reinterpret_cast< bool*>(_v)); break;
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
void QtMenuItem::triggered()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QtMenuItem::textChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void QtMenuItem::shortcutChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void QtMenuItem::toggled(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QtMenuItem::enabledChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}
QT_END_MOC_NAMESPACE
