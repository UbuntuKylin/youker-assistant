/****************************************************************************
** Meta object code from reading C++ file 'qdeclarativefolderlistmodel.h'
**
** Created: Tue Aug 20 11:48:04 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qdeclarativefolderlistmodel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qdeclarativefolderlistmodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QDeclarativeFolderListModel[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       9,   49, // properties
       1,   85, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      29,   28,   28,   28, 0x05,
      45,   28,   28,   28, 0x05,

 // slots: signature, parameters, type, tag, flags
      60,   28,   28,   28, 0x08,
      86,   70,   28,   28, 0x08,
     116,   70,   28,   28, 0x08,
     155,  145,   28,   28, 0x08,

 // methods: signature, parameters, type, tag, flags
     209,  203,  198,   28, 0x02,

 // properties: name, type, flags
     228,  223, 0x11495103,
     235,  223, 0x11495001,
     260,  248, 0x0b095103,
     282,  272, 0x0009510b,
     292,  198, 0x01095103,
     305,  198, 0x01095103,
     314,  198, 0x01095103,
     331,  198, 0x01095103,
     352,  348, 0x02495001,

 // properties: notify_signal_id
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       1,

 // enums: name, flags, count, data
     272, 0x0,    5,   89,

 // enum data: key, value
     358, uint(QDeclarativeFolderListModel::Unsorted),
     367, uint(QDeclarativeFolderListModel::Name),
     372, uint(QDeclarativeFolderListModel::Time),
     377, uint(QDeclarativeFolderListModel::Size),
     382, uint(QDeclarativeFolderListModel::Type),

       0        // eod
};

static const char qt_meta_stringdata_QDeclarativeFolderListModel[] = {
    "QDeclarativeFolderListModel\0\0"
    "folderChanged()\0countChanged()\0refresh()\0"
    "index,start,end\0inserted(QModelIndex,int,int)\0"
    "removed(QModelIndex,int,int)\0start,end\0"
    "handleDataChanged(QModelIndex,QModelIndex)\0"
    "bool\0index\0isFolder(int)\0QUrl\0folder\0"
    "parentFolder\0QStringList\0nameFilters\0"
    "SortField\0sortField\0sortReversed\0"
    "showDirs\0showDotAndDotDot\0showOnlyReadable\0"
    "int\0count\0Unsorted\0Name\0Time\0Size\0"
    "Type\0"
};

void QDeclarativeFolderListModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QDeclarativeFolderListModel *_t = static_cast<QDeclarativeFolderListModel *>(_o);
        switch (_id) {
        case 0: _t->folderChanged(); break;
        case 1: _t->countChanged(); break;
        case 2: _t->refresh(); break;
        case 3: _t->inserted((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 4: _t->removed((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 5: _t->handleDataChanged((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< const QModelIndex(*)>(_a[2]))); break;
        case 6: { bool _r = _t->isFolder((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QDeclarativeFolderListModel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QDeclarativeFolderListModel::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_QDeclarativeFolderListModel,
      qt_meta_data_QDeclarativeFolderListModel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QDeclarativeFolderListModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QDeclarativeFolderListModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QDeclarativeFolderListModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QDeclarativeFolderListModel))
        return static_cast<void*>(const_cast< QDeclarativeFolderListModel*>(this));
    if (!strcmp(_clname, "QDeclarativeParserStatus"))
        return static_cast< QDeclarativeParserStatus*>(const_cast< QDeclarativeFolderListModel*>(this));
    if (!strcmp(_clname, "com.trolltech.qml.QDeclarativeParserStatus"))
        return static_cast< QDeclarativeParserStatus*>(const_cast< QDeclarativeFolderListModel*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int QDeclarativeFolderListModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QUrl*>(_v) = folder(); break;
        case 1: *reinterpret_cast< QUrl*>(_v) = parentFolder(); break;
        case 2: *reinterpret_cast< QStringList*>(_v) = nameFilters(); break;
        case 3: *reinterpret_cast< SortField*>(_v) = sortField(); break;
        case 4: *reinterpret_cast< bool*>(_v) = sortReversed(); break;
        case 5: *reinterpret_cast< bool*>(_v) = showDirs(); break;
        case 6: *reinterpret_cast< bool*>(_v) = showDotAndDotDot(); break;
        case 7: *reinterpret_cast< bool*>(_v) = showOnlyReadable(); break;
        case 8: *reinterpret_cast< int*>(_v) = count(); break;
        }
        _id -= 9;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setFolder(*reinterpret_cast< QUrl*>(_v)); break;
        case 2: setNameFilters(*reinterpret_cast< QStringList*>(_v)); break;
        case 3: setSortField(*reinterpret_cast< SortField*>(_v)); break;
        case 4: setSortReversed(*reinterpret_cast< bool*>(_v)); break;
        case 5: setShowDirs(*reinterpret_cast< bool*>(_v)); break;
        case 6: setShowDotAndDotDot(*reinterpret_cast< bool*>(_v)); break;
        case 7: setShowOnlyReadable(*reinterpret_cast< bool*>(_v)); break;
        }
        _id -= 9;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 9;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 9;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QDeclarativeFolderListModel::folderChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void QDeclarativeFolderListModel::countChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
