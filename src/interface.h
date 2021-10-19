/*
 * Copyright (C) 2021 KylinSoft Co., Ltd.
 *
 * Authors:
 *  Yang Min yangmin@kylinos.cn
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef INTERFACE_H
#define INTERFACE_H

class QString;
class QWidget;
class QStringLiteral;

enum FunType{
    MACHINE_INFO,
    HARDWARE_PARAMETERS,
    HARDWARE_MONITOR,
    DRIVER_MANAGER,
    FUNCTYPE_MAX
};

class PluginInterface{
public:
    virtual ~PluginInterface(){}

    /**
     * \brief getPluginName
     * get plugin's name
     */
    virtual QString getPluginName() = 0;

    /**
     * \brief getPluginType
     * get plugin's type
     */
    virtual int getPluginType() = 0;

    /**
     * \brief getPluginMainWnd
     * get plugin's main window
     */
    virtual QWidget* getPluginMainWnd() = 0;

    /**
     * \brief pluginDelayControl
     * do plugin's delay things
     */
    virtual void pluginDelayControl() = 0;

    /**
     * \brief name
     * module name (用于搜索？)
     */
    virtual const QString name() const = 0;

    /**
     * \brief updatePluginContent
     * update plugin's content
     */
    virtual void updatePluginContent() {};
};

#define PluginInterfaceIID "org.kyya.PluginInterface"

Q_DECLARE_INTERFACE(PluginInterface, PluginInterfaceIID)

#endif // INTERFACE_H
