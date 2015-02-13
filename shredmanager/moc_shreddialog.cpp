/****************************************************************************
** Meta object code from reading C++ file 'shreddialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "shreddialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'shreddialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ShredDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      37,   12,   12,   12, 0x0a,
      60,   12,   12,   12, 0x0a,
      89,   83,   12,   12, 0x0a,
     118,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ShredDialog[] = {
    "ShredDialog\0\0onSelectButtonClicked()\0"
    "onShredButtonClicked()\0onCacelButtonClicked()\0"
    "index\0onSelecteComboActivated(int)\0"
    "onCloseButtonClicked()\0"
};

void ShredDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ShredDialog *_t = static_cast<ShredDialog *>(_o);
        switch (_id) {
        case 0: _t->onSelectButtonClicked(); break;
        case 1: _t->onShredButtonClicked(); break;
        case 2: _t->onCacelButtonClicked(); break;
        case 3: _t->onSelecteComboActivated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->onCloseButtonClicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ShredDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ShredDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ShredDialog,
      qt_meta_data_ShredDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ShredDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ShredDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ShredDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ShredDialog))
        return static_cast<void*>(const_cast< ShredDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ShredDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
