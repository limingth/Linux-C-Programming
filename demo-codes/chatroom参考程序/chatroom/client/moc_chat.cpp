/****************************************************************************
** Meta object code from reading C++ file 'chat.h'
**
** Created: Sun May 25 11:18:22 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "chat.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chat.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Chat[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
       6,    5,    5,    5, 0x08,
      16,    5,    5,    5, 0x08,
      26,    5,    5,    5, 0x08,
      34,    5,    5,    5, 0x08,
      58,    5,    5,    5, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Chat[] = {
    "Chat\0\0sendMsg()\0recvMsg()\0error()\0"
    "updateWhom(QModelIndex)\0openPriv(QModelIndex)\0"
};

const QMetaObject Chat::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Chat,
      qt_meta_data_Chat, 0 }
};

const QMetaObject *Chat::metaObject() const
{
    return &staticMetaObject;
}

void *Chat::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Chat))
	return static_cast<void*>(const_cast< Chat*>(this));
    if (!strcmp(_clname, "Ui_Chat"))
	return static_cast< Ui_Chat*>(const_cast< Chat*>(this));
    return QDialog::qt_metacast(_clname);
}

int Chat::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sendMsg(); break;
        case 1: recvMsg(); break;
        case 2: error(); break;
        case 3: updateWhom((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 4: openPriv((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
