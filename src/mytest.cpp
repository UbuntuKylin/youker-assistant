#include "mytest.h"
mytest::mytest(const QString & service="com.ubuntukylin_tools.daemon", const QString & path="/", const QString & interface="com.ubuntukylin_tools.daemon", const QDBusConnection & connection=QDBusConnection::systemBus(), QDeclarativeItem *parent = 0) :
    QDBusInterface(parent)
{

}
////"com.ubuntukylin_tools.daemon",
//"/",
//"com.ubuntukylin_tools.daemon",
////QDBusConnection::systemBus());
