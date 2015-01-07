#include "commonobject.h"

CommonObject::CommonObject(QObject *parent) :
    QObject(parent)
{
}


QString CommonObject::get_locale_version() {
    QString locale = QLocale::system().name();
    return locale;
}
