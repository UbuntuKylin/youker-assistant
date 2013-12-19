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
import "../common" as Common
import "../bars" as Bars
Item {
    id: screen; width: parent.width; height: 475
    Rectangle {
        id: setting_widget
        anchors.fill: parent
        //背景
        Image {
            source: "../../img/skin/bg-bottom-tab.png"
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
                source: "../../img/skin/note-bg.png"
            }
            Text {
                anchors {
                    left: parent.left
                    leftMargin: 50
                    top: parent.top
                    topMargin: titleimage.height/2 - 7
                }
                text: qsTr("You can customize your own visual effects and sound.")//您可以定制属于自己的视觉效果和声音。
                font.pixelSize: 12
                color: "#383838"
            }

            Column {
                anchors {
                    top: titleimage.bottom
                    topMargin: 40
                    left: parent.left
                    leftMargin: 25
                }
                spacing: 10

                Row {
                    spacing: 10
                    Image {
                        id: personal
                        source: "../../img/icons/themeset.png"
                    }
                    Column {
                        spacing: 7
                        Row {
                            Text {
                                id: personaltext
                                text: qsTr(" Individualization")// 个性化
                                font.bold: true
                                font.pixelSize: 14
                                color: "#383838"
                            }
                            Text {
                                id: b1
                                text: qsTr("Change WindowTheme")
                                visible: false
                            }
                            Text {
                                id: b2
                                text: qsTr("Change IconSetting")
                                visible: false
                            }
                            Text {
                                id: b3
                                text: qsTr("Change MousePointer")
                                visible: false
                            }
                            Text {
                                id: b4
                                text: qsTr("Change SoundEffect")
                                visible: false
                            }
                            Text {
                                id: b5
                                text: qsTr("Change BootAnimation")
                                visible: false
                            }
                        }
                        Row {
                            spacing: 5
                            Common.StyleButton {
                                wordname: qsTr("Change WindowTheme"); width: b1.width
//                                flag: "WidgetTheme"
                                onClicked: {
                                    pageStack.push(widgetthemepage);
                                }
                            }//更改窗口主题
                            //左右分割条
                            Rectangle {height: 18; width: 1; color: "#b9c5cc"; anchors.verticalCenter: parent.verticalCenter}
                            Common.StyleButton {
                                wordname: qsTr("Change IconSetting"); width: b2.width
//                                flag: "Desktopicon"
                                onClicked: {
                                    pageStack.push(desktopiconsetpage);
                                }
                            }//更改图标配置
                            //左右分割条
                            Rectangle {height: 18; width: 1; color: "#b9c5cc"; anchors.verticalCenter: parent.verticalCenter }
                            Common.StyleButton {
                                wordname: qsTr("Change MousePointer"); width: b3.width
//                                flag: "MousePointer"
                                onClicked: {
                                    pageStack.push(mousepointerpage);
                                }
                            }//更改鼠标指针
                            //左右分割条
                            Rectangle {height: 18; width: 1; color: "#b9c5cc"; anchors.verticalCenter: parent.verticalCenter }
                            Common.StyleButton {
                                wordname: qsTr("Change SoundEffect"); width: b4.width
//                                flag: "SoundEffects"
                                onClicked: {
                                    pageStack.push(soundeffectspage);
                                }
                            }//更改声音效果
                            //左右分割条
                            Rectangle {height: 18; width: 1; color: "#b9c5cc"; anchors.verticalCenter: parent.verticalCenter }
                            Common.StyleButton {
                                wordname: qsTr("Change BootAnimation"); width: b5.width
//                                flag: "BootAnimation"
                                onClicked: {
                                    pageStack.push(bootanimationpage);
                                }
                            }//更改开机动画

                        }

                    }
                }


                Row {
                    spacing: 10
                    Image {
                        id: unity
                        source: "../../img/icons/unity.png"
                    }
                    Column {
                        spacing: 7
                        Row {
                            Text {
                                id: unitytext
                                text: qsTr(" Unity")// Unity
                                font.bold: true
                                font.pixelSize: 14
                                color: "#383838"
                            }
                            Text {
                                id: b6
                                text: qsTr("Custom Launcher")
                                visible: false
                            }
                        }
                        Row {
                            spacing: 5
                            Common.StyleButton {
                                wordname: qsTr("Custom Launcher"); width: b6.width
//                                flag: "LauncherTheme"
                                onClicked: {
                                    pageStack.push(launcherthemepage);
                                }
                            }//自定义启动器
                        }
                    }
                }


                Row {
                    spacing: 10
                    Image {
                        id: fontimage
                        source: "../../img/icons/font.png"
                    }
                    Column {
                        spacing: 7
                        Row {
                            Text {
                                id: fonttext
                                text: qsTr(" Font")// 字体
                                font.bold: true
                                font.pixelSize: 14
                                color: "#383838"
                            }
                            Text {
                                id: b7
                                text: qsTr("Change Default Font")
                                visible: false
                            }
                            Text {
                                id: b8
                                text: qsTr("Change Document Font")
                                visible: false
                            }
                            Text {
                                id: b9
                                text: qsTr("Change Titlebar Font")
                                visible: false
                            }
                        }
                        Row {
                            spacing: 5
                            Common.StyleButton {
                                wordname: qsTr("Change Default Font"); width: b7.width
//                                flag: "DefaultFont"
                                onClicked: {
                                    pageStack.push(defaultfontpage);
                                }
                            }//更改默认字体设置
                            Rectangle {height: 18; width: 1; color: "#b9c5cc"; anchors.verticalCenter: parent.verticalCenter }
                            Common.StyleButton {
                                wordname: qsTr("Change Document Font"); width: b8.width
//                                flag: "DocumentFont"
                                onClicked: {
                                    pageStack.push(documentfontpage);
                                }
                            }//更改文档字体设置
                            Rectangle {height: 18; width: 1; color: "#b9c5cc"; anchors.verticalCenter: parent.verticalCenter }
                            Common.StyleButton {
                                wordname: qsTr("Change Titlebar Font"); width: b9.width
//                                flag: "TitlebarFont"
                                onClicked: {
                                    pageStack.push(titlebarfontpage);
                                }
                            }//更改窗口标题栏字体设置
                        }
                    }
                }


                Row {
                    spacing: 10
                    Image {
                        id: sysimage
                        source: "../../img/icons/systemset.png"
                    }
                    Column {
                        spacing: 7
                        Row {
                            Text {
                                id: systext
                                text: qsTr(" System options")// 系统选项
                                font.bold: true
                                font.pixelSize: 14
                                color: "#383838"
                            }
                            Text {
                                id: b10
                                text: qsTr("Change Touchpad")
                                visible: false
                            }
                            Text {
                                id: b11
                                text: qsTr("Check Screen")
                                visible: false
                            }
                        }
                        Row {
                            spacing: 5
                            Common.StyleButton {
                                wordname: qsTr("Change Touchpad"); width: b10.width
//                                flag: "TouchpadSet"
                                onClicked: {
                                    pageStack.push(touchpadsetpage);
                                }
                            }//更改触摸板设置
                            Rectangle {height: 18; width: 1; color: "#b9c5cc"; anchors.verticalCenter: parent.verticalCenter }
                            Common.StyleButton {
                                wordname: qsTr("Check Screen"); width: b11.width
//                                flag: "CheckScreen"
                                onClicked: {
                                    sessiondispatcher.showCheckscreenDialog(mainwindow.pos.x, mainwindow.pos.y);
                                }
                            }//检测屏幕坏点
                        }
                    }
                }
            }
            Item { id: foreground; anchors.fill: parent }
        }
    }
}
