/*
 * Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * Authors:
 *  Kobe Lee    kobe24_lixiang@126.com
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
import SessionType 0.1
import SystemType 0.1
import SudoType 0.1
import FcitxCfgWizard 0.1
import "./func/common" as Common
import "./func/settings" as SysSettings
import "func"
//Rectangle {
Item {
    id:content
    width: parent.width
    height: parent.height - 30  //去掉StatusWidget所占用的高度30

//传给软件推荐二级界面的值
    property string delegate_name: "qq"
    property string delegate_appname: "WineQQ"
    property string delegate_information: "QQ 2013-09-09"
    property string delegate_useinfo: "如果软件安装成功，则可以通过软件的中文/英文名关键子在Dash中搜索并启动软件。"
    property string delegate_image: ""
    property string delegate_introduction: ""
    property string introduction_image1: ""
    property string introduction_image2: ""
    property string soft_status: "n"


//    radius: 10
//    color: "lightgray"

    property string text: "homepage"
//    SessionDispatcher {
//        id: sessiondispatcher
//    }
//    SystemDispatcher {
//        id: systemdispatcher
//    }
//    SudoDispatcher {
//        id: sudodispatcher
//    }
//    FcitxCfgWizard {
//        id: fcitxcfgwizard
//    }

    Rectangle {
        id: rectangle1
        width: parent.width
        height: titlebar.height + toolwidget.height
        color: "transparent"
//        Column {
//            id: layout1
//            anchors.fill: parent
            //标题栏
            TitleWidget {
                id: titlebar
                height: 40//20
//                opacity: 0.3
            }
            //功能图标栏
            ToolWidget {
                id: toolwidget
                height: 64//84
                anchors {
                    top: titlebar.bottom
                    topMargin: 18
//                    topMargin: 45
                }
            }

            Item {
                id:display_content
                width: parent.width
                anchors {
                    top: titlebar.bottom
                    topMargin: 59
//                    topMargin: 45
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
                        HomePage {dis1: sessiondispatcher; dis2: systemdispatcher}
                    }
                    Common.Page {
                        id: systemmessage
                        visible: false
        //                title: "search by kobe"
                        SystemMessage {}
                    }
                    Common.Page {
                        id: clearrubbish
                        visible: false
        //                title: "clearrubbish by kobe"
                        ClearRubbish {}
                    }
                    Common.Page {
                        id: systemset
                        visible: false
        //                title: "softwaremanager by kobe"
                        SystemSet {dis1: sessiondispatcher; dis2: systemdispatcher}
                    }
                    Common.Page {
                        id: functioncollection
                        visible: false
        //                title: "allfunction by kobe"
                        FunctionCollection {dis: systemdispatcher}
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


                    //systemset-pages
                    Common.Page {
                        id: widgetthemepage
                        visible: false
                        SysSettings.WidgetTheme {}
                    }
                    Common.Page {
                        id: desktopiconsetpage
                        visible: false
                        SysSettings.DesktopiconSet {}
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
//        }
    }
}
