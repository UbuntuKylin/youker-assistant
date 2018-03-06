#ifndef CUSTOMDATA_H
#define CUSTOMDATA_H

#include <QDBusMetaType>
#include <QDBusArgument>
#include <QString>
#include <QDebug>

class CustomData
{
public:
    QString hash;
    QString name;
    QString description;
    int index;
    bool valid;

//    friend QDebug operator<<(QDebug argument, const CustomData &data);
    friend QDebug operator<<(QDebug argument, const CustomData &data) {
        argument << data.name;
        return argument;
    }

//    friend QDBusArgument &operator<<(QDBusArgument &argument, const CustomData &data);
    friend QDBusArgument &operator<<(QDBusArgument &argument, const CustomData &data) {
        argument.beginStructure();
        argument << data.hash << data.name << data.description << data.index << data.valid;
        argument.endStructure();
        return argument;
    }

    friend const QDBusArgument &operator>>(const QDBusArgument &argument, CustomData &data) {
        argument.beginStructure();
        argument >> data.hash >> data.name >> data.description >> data.index >> data.valid;
        argument.endStructure();
        return argument;
    }

    bool operator==(const CustomData data) const {
        return data.hash == hash;
    }

    bool operator!=(const CustomData data) const {
        return data.hash != hash;
    }

//    static void registerCustomDataMetaType();
};

Q_DECLARE_METATYPE(CustomData)

void registerCustomDataMetaType();

#endif // CUSTOMDATA_H
