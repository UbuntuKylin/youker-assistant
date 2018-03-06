/*
 * Copyright (C) 2013 ~ 2015 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * Authors:
 *  Kobe Lee    xiangli@ubuntukylin.com/kobe24_lixiang@126.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "pluginmanager.h"
#include "../component/plugininterface.h"
#include <QDir>
#include <QDebug>

PluginManager::PluginManager(void)
{

}

PluginManager::~PluginManager(void)
{
}

PluginManager* PluginManager::Instance()
{
    static PluginManager PluginMgr;
    return &PluginMgr;
}

bool PluginManager::loadPlugin(QString plugin_path)
{
//    qDebug() << "plugin_path="<<plugin_path;
    QDir pluginsDir(plugin_path);
    foreach (QString fileName, pluginsDir.entryList(QStringList("*.so"),QDir::Files)) {
        QPluginLoader  *pluginLoader = new  QPluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader->instance();
        if (plugin) {//测试插件是否有效:使用 qobject_cast()测试插件是否给出了相应接口并进行类型转换，转换成接口对象指针.
            PluginInterface* interface = qobject_cast<PluginInterface*>(plugin);
            if (interface) {
                QString guid = interface->getGuid();
                plugin_map.insert(guid, pluginLoader);
                qDebug() << "The plugin interface is: " << interface;
            }
            else {
                qWarning() << pluginLoader->errorString();
                pluginLoader->unload();
                pluginLoader->deleteLater();
            }
        }
        else {
            qDebug() << "The plugin is invalid===" << pluginLoader->errorString();
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
