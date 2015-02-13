#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

/*-----------------------plugin接口类(纯虚类)-----------------------*/

#include <QtCore/QtPlugin>
#include <QString>

class PluginInterface
{
public:
    virtual ~PluginInterface() {}
    virtual QString getGuid()  = 0;
    virtual QString getName() = 0;
    virtual QString getDescribe() = 0;
    virtual QString getPicture() = 0;
    virtual void doAction() = 0;
//    virtual QString getPluginValue() = 0;
};

//Q_DECLARE_INTERFACE定义在在qobject.h中，用来告诉Qt meta-object system 这个接口名称
//Q_DECLARE_INTERFACE(PluginInterface, "0895260D-9053-4e8a-B37C-9C05CCFE4A14")
Q_DECLARE_INTERFACE(PluginInterface, "com.ubuntukylin.Plugin.PluginInterface ")

#endif // PLUGININTERFACE_H

