#include <QDBusMetaType>

#include "customdata.h"

/*QDBusArgument &operator<<(QDBusArgument &argument, const CustomData &data) {
    argument.beginStructure();
    argument << data.hash << data.name << data.description << data.index << data.valid;
    argument.endStructure();
    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, CustomData &data) {
    argument.beginStructure();
    argument >> data.hash >> data.name >> data.description >> data.index >> data.valid;
    argument.endStructure();
    return argument;
}

void CustomData::registerCustomDataMetaType()
{
    qRegisterMetaType<CustomData>("CustomData");
    qDBusRegisterMetaType<CustomData>();
}*/

void registerCustomDataMetaType()
{
    qRegisterMetaType<CustomData>("CustomData");
    qDBusRegisterMetaType<CustomData>();
}
