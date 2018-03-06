#include "customdatalist.h"

void registerCustomDataListMetaType()
{
    qRegisterMetaType<CustomDataList>("CustomDataList");
    qDBusRegisterMetaType<CustomDataList>();
}
