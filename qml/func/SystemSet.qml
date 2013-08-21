/*
 * Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd.
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
import "common" as Common
import "bars" as Bars
Item {
    id: screen; width: parent.width; height: 475
    property SessionDispatcher dis1: sessiondispatcher
    property SystemDispatcher dis2: systemdispatcher
    Rectangle {
        id: setting_widget
        anchors.fill: parent
        //背景
        Image {
            source: "../img/skin/bg-bottom-tab.png"
            anchors.fill: parent
        }
        Item {
            id: views
            width: parent.width
            height: parent.height

            Image {
                id: titleimage
                anchors {
                    left: parent.left
                    leftMargin: 2
                }
                width: parent.width - 4
                source: "../img/skin/note-bg.png"
            }
            Text {
                anchors {
                    left: parent.left
                    leftMargin: 50
                    top: parent.top
                    topMargin: titleimage.height/2 - 7
                }
                text: "您可以定制属于自己的视觉效果和声音。"
                font.pixelSize: 12
                color: "#383838"
            }

            Column {
                anchors {
                    top: titleimage.bottom
                    topMargin: 40
                    left: parent.left
                    leftMargin: 30
                }
                spacing: 10

                Row {
                    spacing: 10
                    Image {
                        id: personal
                        source: "../img/icons/themeset.png"
                    }
                    Column {
                        spacing: 10
                        Text {
                            id: personaltext
                            text: "个性化"
                            font.bold: true
    //                        font.pointSize: 12
                            font.pixelSize: 14
                            color: "#383838"
                            anchors.top: personal.top
                        }
                        Row {
                            anchors.bottom: personal.bottom
                            anchors.bottomMargin: 10
                            spacing: 5
                            SetWord {wordname: "更改窗口主题"; width: 80; flag: "WidgetTheme"}
                            //左右分割条
                            Rectangle {height: 18; width: 1; color: "#b9c5cc" }
                            SetWord {wordname: "更改图标配置"; width: 80; flag: "DesktopiconSet"}
                            //左右分割条
                            Rectangle {height: 18; width: 1; color: "#b9c5cc" }
                            SetWord {wordname: "更改鼠标指针"; width: 80; flag: "MousePointer"}
                            //左右分割条
                            Rectangle {height: 18; width: 1; color: "#b9c5cc" }
                            SetWord {wordname: "更改声音效果"; width: 80; flag: "SoundEffects"}
                            //左右分割条
                            Rectangle {height: 18; width: 1; color: "#b9c5cc" }
                            SetWord {wordname: "更改开机动画"; width: 80; flag: "BootAnimation"}
                        }
                    }
                }


                Row {
                    spacing: 10
                    Image {
                        id: unity
                        source: "../img/icons/unity.png"
                    }
                    Column {
                        spacing: 10
                        Text {
                            id: unitytext
                            text: "Unity"
                            font.bold: true
                            font.pixelSize: 14
                            color: "#383838"
                            anchors.top: unity.top
                        }
                        Row {
                            anchors.bottom: unity.bottom
                            anchors.bottomMargin: 10
                            spacing: 5
                            SetWord {wordname: "自定义启动器"; width: 120; flag: "LauncherTheme"}
                        }
                    }
                }


                Row {
                    spacing: 10
                    Image {
                        id: fontimage
                        source: "../img/icons/font.png"
                    }
                    Column {
                        spacing: 10
                        Text {
                            id: fonttext
                            text: "字体"
                            font.bold: true
    //                        font.pointSize: 12
                            font.pixelSize: 14
                            color: "#383838"
                            anchors.top: fontimage.top
                        }
                        Row {
                            anchors.bottom: fontimage.bottom
                            anchors.bottomMargin: 10
                            spacing: 5
                            SetWord {wordname: "更改默认字体设置"; width: 110; flag: "DefaultFont"}
                            Rectangle {height: 18; width: 1; color: "#b9c5cc" }
                            SetWord {wordname: "更改文档字体设置"; width: 110; flag: "DocumentFont"}
                            Rectangle {height: 18; width: 1; color: "#b9c5cc" }
                            SetWord {wordname: "更改窗口标题栏字体设置"; width: 140; flag: "TitlebarFont"}
                        }
                    }
                }


                Row {
                    spacing: 10
                    Image {
                        id: sysimage
                        source: "../img/icons/systemset.png"
                    }
                    Column {
                        spacing: 10
                        Text {
                            id: systext
                            text: "系统选项"
                            font.bold: true
    //                        font.pointSize: 12
                            font.pixelSize: 14
                            color: "#383838"
                            anchors.top: sysimage.top
                        }
                        Row {
                            anchors.bottom: sysimage.bottom
                            anchors.bottomMargin: 10
                            spacing: 5
                            SetWord {wordname: "更改触摸板设置"; width: 100; flag: "TouchpadSet"}
                            Rectangle {height: 18; width: 1; color: "#b9c5cc" }
                            SetWord {wordname: "检测屏幕坏点"; width: 90; flag: "CheckScreen"}
                        }
                    }
                }
            }
            Item { id: foreground; anchors.fill: parent }
        }
    }
}
