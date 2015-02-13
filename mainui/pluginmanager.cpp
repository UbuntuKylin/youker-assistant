#include "pluginmanager.h"
#include "../component/plugininterface.h"
#include <QDir>
#include <QDebug>

PluginManager::PluginManager(void)
{

}

PluginManager::~PluginManager(void)
{
//    QMap<QString, QPluginLoader*>::iterator itbegin = plugin_map.begin();
//    QMap<QString, QPluginLoader*>::iterator  itend = plugin_map.end();
//    for (;itbegin != itend; ++itbegin)
//    {
//        itbegin.value()->unload();
//    }
//    plugin_map.clear();
}

PluginManager* PluginManager::Instance()
{
    static PluginManager PluginMgr;
    return &PluginMgr;
}

bool PluginManager::loadPlugin(QString plugin_path)
{
    QDir pluginsDir(plugin_path + "/libs");
    foreach (QString fileName, pluginsDir.entryList(QStringList("*.so"),QDir::Files)) {
        qDebug() << "111111111->" << fileName;
        QPluginLoader  *pluginLoader = new  QPluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader->instance();
        if (plugin) {//测试插件是否有效:使用 qobject_cast()测试插件是否给出了相应接口并进行类型转换，转换成接口对象指针.
            qDebug() << "22222";
            PluginInterface* interface = qobject_cast<PluginInterface*>(plugin);
            if (interface) {
                qDebug() << "3333";
                QString guid = interface->getGuid();
                plugin_map.insert(guid, pluginLoader);
            }
        }
        else {
            qDebug() << "4444";
            delete pluginLoader;
        }
    }
    return true;
}

bool PluginManager::unloadPlugin(QString plugin_guid)
{
    QMap<QString, QPluginLoader*>::iterator iter = plugin_map.find(plugin_guid);
    if (iter == plugin_map.end())
    {
        return false;
    }
    iter.value()->unload();
    plugin_map.erase(iter);
    return true;
}
