/****************************************************************************
** Meta object code from reading C++ file 'processdialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "processdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'processdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ProcessDialog[] = {

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
      15,   14,   14,   14, 0x08,
      44,   33,   14,   14, 0x08,
      72,   14,   14,   14, 0x08,
      94,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ProcessDialog[] = {
    "ProcessDialog\0\0refresh_prolist()\0"
    "row,column\0handlercellClicked(int,int)\0"
    "killSelectedProcess()\0onCloseButtonClicked()\0"
};

void ProcessDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ProcessDialog *_t = static_cast<ProcessDialog *>(_o);
        switch (_id) {
        case 0: _t->refresh_prolist(); break;
        case 1: _t->handlercellClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->killSelectedProcess(); break;
        case 3: _t->onCloseButtonClicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ProcessDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ProcessDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ProcessDialog,
      qt_meta_data_ProcessDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ProcessDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ProcessDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ProcessDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ProcessDialog))
        return static_cast<void*>(const_cast< ProcessDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ProcessDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
