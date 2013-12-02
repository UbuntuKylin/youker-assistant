/*
 * Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
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

import QtQuick 1.1
import "./func/common" as Common
import "./func/settings" as SysSettings
import "func"

Item {
    id:content
    width: parent.width
    height: parent.height - 30  //去掉StatusWidget所占用的高度30
//    radius: 1
//    color: "lightgray"
    property string text: "homepage"
    Rectangle {
        id: rectangle1
        width: parent.width
        height: titlebar.height + toolwidget.height
        color: "transparent"
        //标题栏
        TitleWidget {
            id: titlebar
            height: 40
        }
        //功能图标栏
        ToolWidget {
            id: toolwidget
            height: 64
            anchors {
                top: titlebar.bottom
                topMargin: 18
            }
        }

        Item {
            id:display_content
            width: parent.width
            anchors {
                top: titlebar.bottom
                topMargin: 59
            }
            height: parent.height - 104 //去掉标题栏 + 功能图标栏 + StatusWidget的高度
            property string text: "homepage"

            Common.PageStack {
                id: pageStack
                Component.onCompleted: {
                    pageStack.push(homepage);
                }
                Common.Page {
                    id: homepage
                    visible: false
                    HomePage {}
                }
                Common.Page {
                    id: systemmessage
                    visible: false
                    DetailInformation {}
                }
                Common.Page {
                    id: clearrubbish
                    visible: false
                    ClearRubbish {}
                }
                Common.Page {
                    id: systemset
                    visible: false
                    SystemSet {}
                }
                Common.Page {
                    id: functioncollection
                    visible: false
                    FunctionCollection {}
                }
                Common.Page {
                    id: softwarerecommend
                    visible: false
                    SoftWareRecommend {}
                }

                //SoftWare-pages
                Common.Page {
                    id: softwarepage
                    visible: false
                    SoftwarePage {}
                }
                //ProcessManager page
                Common.Page {
                    id: processmanagerpage
                    visible: false
                    ProcessManager {}
                }
                //WeatherForecast-page
                Common.Page {
                    id:weatherpage
                    visible: false
                    WeatherForecast {}
                }

                //systemset-pages
                Common.Page {
                    id: widgetthemepage
                    visible: false
                    SysSettings.WidgetTheme {}
                }
                Common.Page {
                    id: desktopiconsetpage
                    visible: false
                    SysSettings.DesktopIcon {}
                }
                Common.Page {
                    id: mousepointerpage
                    visible: false
                    SysSettings.MousePointer {}
                }

                Common.Page {
                    id: soundeffectspage
                    visible: false
                    SysSettings.SoundEffects {}
                }
                Common.Page {
                    id: bootanimationpage
                    visible: false
                    SysSettings.BootAnimation {}
                }
                Common.Page {
                    id: launcherthemepage
                    visible: false
                    SysSettings.LauncherTheme {}
                }
                Common.Page {
                    id: defaultfontpage
                    visible: false
                    SysSettings.DefaultFont {}
                }
                Common.Page {
                    id: documentfontpage
                    visible: false
                    SysSettings.DocumentFont {}
                }
                Common.Page {
                    id: titlebarfontpage
                    visible: false
                    SysSettings.TitlebarFont {}
                }
                Common.Page {
                    id: touchpadsetpage
                    visible: false
                    SysSettings.TouchpadSet {}
                }
                //
                Common.Page {
                    id: fcitxConfigtoolpage
                    visible: false
                    SysSettings.FcitxConfigtool{}
                }
                Common.Page {
                    id: fcitxConfigtoolFontpage
                    visible: false
                    SysSettings.FcitxConfigtoolFont{}
                }
                Common.Page {
                    id: fcitxConfigtoolKeypage
                    visible: false
                    SysSettings.FcitxConfigtoolKey{}
                }
            }
        }
    }
}
