/*
 * Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd.
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
            source: "../../img/skin/bg-bottom-tab.png"//
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
                text: qsTr("You can perform a full range of customized systems based on personal preferences!")//您可以根据个人喜好对系统进行全方位的定制！
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
                spacing: 25

                Row {
                    spacing: 10
                    Image {
                        id: personal
                        source: "../../img/icons/themeset.png"
//                        anchors.verticalCenter: parent.verticalCenter
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    Column {
                        spacing: 3
                        Row {
                            anchors.left: parent.left
                            anchors.leftMargin: 5
                            Text {
                                id: personaltext
                                text: qsTr(" Personalize")// 个性化
                                font.bold: true
                                font.pixelSize: 14
                                color: "#383838"
                            }
                            Text {
                                id: b1
                                text: qsTr("WindowTheme")//窗口主题
                                visible: false
                            }
                            Text {
                                id: b2
                                text: qsTr("IconSetting")//图标配置
                                visible: false
                            }
                            Text {
                                id: b3
                                text: qsTr("MousePointer")//鼠标指针
                                visible: false
                            }
                            Text {
                                id: b4
                                text: qsTr("SoundEffect")//声音效果
                                visible: false
                            }
                            Text {
                                id: b5
                                text: qsTr("BootAnimation")//开机动画
                                visible: false
                            }
                        }
                        Row {
                            spacing: 18
                            Common.StyleButton {
                                wordname: qsTr("WindowTheme"); width: b1.width//窗口主题
//                                flag: "WidgetTheme"
                                onClicked: {
                                    pageStack.push(widgetthemepage);
                                }
                            }//更改窗口主题
                            //左右分割条
                            Rectangle {height: 18; width: 1; color: "#b9c5cc"; anchors.verticalCenter: parent.verticalCenter}
                            Common.StyleButton {
                                wordname: qsTr("IconSetting"); width: b2.width//图标配置
//                                flag: "Desktopicon"
                                onClicked: {
                                    pageStack.push(desktopiconsetpage);
                                }
                            }//更改图标配置
                            //左右分割条
                            Rectangle {height: 18; width: 1; color: "#b9c5cc"; anchors.verticalCenter: parent.verticalCenter }
                            Common.StyleButton {
                                wordname: qsTr("MousePointer"); width: b3.width//鼠标指针
//                                flag: "MousePointer"
                                onClicked: {
                                    pageStack.push(mousepointerpage);
                                }
                            }//更改鼠标指针
                            //左右分割条
                            Rectangle {height: 18; width: 1; color: "#b9c5cc"; anchors.verticalCenter: parent.verticalCenter }
                            Common.StyleButton {
                                wordname: qsTr("SoundEffect"); width: b4.width//声音效果
//                                flag: "SoundEffects"
                                onClicked: {
                                    pageStack.push(soundeffectspage);
                                }
                            }//更改声音效果
                            //左右分割条
                            Rectangle {height: 18; width: 1; color: "#b9c5cc"; anchors.verticalCenter: parent.verticalCenter }
                            Common.StyleButton {
                                wordname: qsTr("BootAnimation"); width: b5.width//开机动画
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
//                        anchors.verticalCenter: parent.verticalCenter
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    Column {
                        spacing: 3
                        Row {
                            anchors.left: parent.left
                            anchors.leftMargin: 5
                            Text {
                                id: unitytext
                                text: qsTr(" Unity")// Unity
                                font.bold: true
                                font.pixelSize: 14
                                color: "#383838"
                            }
                            Text {
                                id: b6
                                text: qsTr("Custom Launcher")//自定义启动器
                                visible: false
                            }
                        }
                        Row {
                            spacing: 18
                            Common.StyleButton {
                                wordname: qsTr("Custom Launcher"); width: b6.width//自定义启动器
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
//                        anchors.verticalCenter: parent.verticalCenter
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    Column {
                        spacing: 3
                        Row {
                            anchors.left: parent.left
                            anchors.leftMargin: 5
                            Text {
                                id: fonttext
                                text: qsTr(" Fonts")// 字体
                                font.bold: true
                                font.pixelSize: 14
                                color: "#383838"
                            }
                            Text {
                                id: b7
                                text: qsTr("DefaultFont")//默认字体设置
                                visible: false
                            }
                            Text {
                                id: b8
                                text: qsTr("DocumentFont")//文档字体设置
                                visible: false
                            }
                            Text {
                                id: b9
                                text: qsTr("TitlebarFont")//窗口标题栏字体设置
                                visible: false
                            }
                        }
                        Row {
                            spacing: 18
                            Common.StyleButton {
                                wordname: qsTr("DefaultFont"); width: b7.width//默认字体设置
//                                flag: "DefaultFont"
                                onClicked: {
                                    pageStack.push(defaultfontpage);
                                }
                            }//更改默认字体设置
                            Rectangle {height: 18; width: 1; color: "#b9c5cc"; anchors.verticalCenter: parent.verticalCenter }
                            Common.StyleButton {
                                wordname: qsTr("DocumentFont"); width: b8.width//文档字体设置
//                                flag: "DocumentFont"
                                onClicked: {
                                    pageStack.push(documentfontpage);
                                }
                            }//更改文档字体设置
                            Rectangle {height: 18; width: 1; color: "#b9c5cc"; anchors.verticalCenter: parent.verticalCenter }
                            Common.StyleButton {
                                wordname: qsTr("TitlebarFont"); width: b9.width//窗口标题栏字体设置
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
//                        anchors.verticalCenter: parent.verticalCenter
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    Column {
                        spacing: 3
                        Row {
                            anchors.left: parent.left
                            anchors.leftMargin: 5
                            Text {
                                id: systext
                                text: qsTr(" System options")// 系统选项
                                font.bold: true
                                font.pixelSize: 14
                                color: "#383838"
                            }
                            Text {
                                id: b10
                                text: qsTr("Touchpad")//触摸板设置
                                visible: false
                            }
                            Text {
                                id: b11
                                text: qsTr("Dead pixel test")//坏点检测
                                visible: false
                            }
                        }
                        Row {
                            spacing: 18
                            Common.StyleButton {
                                wordname: qsTr("Touchpad"); width: b10.width//触摸板设置
//                                flag: "TouchpadSet"
                                onClicked: {
                                    pageStack.push(touchpadsetpage);
                                }
                            }//更改触摸板设置
                            Rectangle {height: 18; width: 1; color: "#b9c5cc"; anchors.verticalCenter: parent.verticalCenter }
                            Common.StyleButton {
                                wordname: qsTr("Dead pixel test"); width: b11.width//坏点检测
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
