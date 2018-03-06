#ifndef CUSTOMDATALIST_H
#define CUSTOMDATALIST_H

#include <QDBusMetaType>
#include <QList>

#include "customdata.h"

typedef QList<CustomData> CustomDataList;

Q_DECLARE_METATYPE(CustomDataList)

void registerCustomDataListMetaType();

#endif // CUSTOMDATALIST_H
