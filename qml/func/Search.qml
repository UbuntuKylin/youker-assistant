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
//import RegisterMyType 0.1
//import SessionType 0.1
import SystemType 0.1
import QtDesktop 0.1
import "common" as Common

Item {
    width: parent.width
    height: 460
//    property Dispatcher dis: mydispather
    property SystemDispatcher dis: systemdispatcher


    Component.onCompleted: {
//        choices.clear();
//        choices.append({"text": mydispather.get_themes()[0]});
//        choices.append({"text": mydispather.get_themes()[1]});
//        choices.append({"text": mydispather.get_themes()[2]});
//        choices.append({"text": mydispather.get_themes()[3]});

//        streamModel.sync();
    }

    ListModel {
        id: choices
        ListElement { text: "kobe" }
        ListElement { text: "lixiang" }
        ListElement { text: "ps" }
        ListElement { text: "baby" }
    }
    TabFrame {
        id:frame
        position: tabPositionGroup.checkedButton == r2 ? "South" : "North"
        KeyNavigation.tab:button1
        KeyNavigation.backtab: button2
//        property int margins : styleitem.style == "mac" ? 16 : 0
        width: parent.width
        height: parent.height
//        anchors.top: toolbar.bottom
//        anchors.bottom: parent.bottom
//        anchors.right: parent.right
//        anchors.left: parent.left
//        anchors.margins: margins
        onCurrentChanged: {}

        Tab {
            title: qsTr("一键清理")
            contentMargin: 20

            Item {
                id: flickable
                anchors.fill: parent
                enabled: true//enabledCheck.checked

                Row {
                    id: contentRow
                    anchors.fill:parent
                    anchors.margins: 8
                    spacing: 16
                    Column {
                        spacing: 9
                        Row {
                            spacing:8
                            Button {
                                id: button1
                                text:"Button 1"
                                width: 96
                                tooltip:"This is an interesting tool tip"
                                KeyNavigation.tab: button2
                                KeyNavigation.backtab: frame.tabBar
                                onClicked: {
                                    console.log("aaaaaaaaaaaaaaaaaaa");
//                                    mydispather.check_screen_break_point();
//                                    mydispather.custom_plymouth_bg("/home/kobe/a.png");

                                }
                            }
                            Button {
                                id:button2
                                text:"Button 2"
                                width:96
                                KeyNavigation.tab: combo
                                KeyNavigation.backtab: button1
                                onClicked: {
                                    console.log("1111111111111");
                                    console.log(combo.selectedText);
//                                    mydispather.set_theme(combo.selectedText);
                                    console.log("222222222222");
                                }
                            }
                        }
                        ComboBox {
                            id: combo;
                            model: choices;
                            width: parent.width;
                            KeyNavigation.tab: t1
                            KeyNavigation.backtab: button2
                            onSelectedIndexChanged: console.log(selectedText)
                        }
                        Row {
                            spacing: 8
                            SpinBox {
                                id: t1
                                width: 97

                                minimumValue: -50
                                value: -20

                                KeyNavigation.tab: t2
                                KeyNavigation.backtab: combo
                            }
                            SpinBox {
                                id: t2
                                width:97
                                KeyNavigation.tab: t3
                                KeyNavigation.backtab: t1
                            }
                        }
                        TextField {
                            id: t3
                            KeyNavigation.tab: slider
                            KeyNavigation.backtab: t2
                            placeholderText: "This is a placeholder for a TextField"
                        }
                        ProgressBar {
                            // normalize value [0.0 .. 1.0]
                            value: (slider.value - slider.minimumValue) / (slider.maximumValue - slider.minimumValue)
                        }
                        ProgressBar {
                            indeterminate: true
                        }
                        Slider {
                            id: slider
                            value: 0.5
                            tickmarksEnabled: tickmarkCheck.checked
                            KeyNavigation.tab: frameCheckbox
                            KeyNavigation.backtab: t3
                        }
                    }
                    Column {
                        id: rightcol
                        spacing: 12
                        GroupBox {
                            id: group1
                            title: "CheckBox"
                            width: area.width
                            adjustToContentSize: true
                            ButtonRow {
                                exclusive: false
                                CheckBox {
                                    id: frameCheckbox
                                    text: "Text frame"
                                    checked: true
                                    KeyNavigation.tab: tickmarkCheck
                                    KeyNavigation.backtab: slider
                                }
                                CheckBox {
                                    id: tickmarkCheck
                                    text: "Tickmarks"
                                    checked: true
                                    KeyNavigation.tab: r1
                                    KeyNavigation.backtab: frameCheckbox
                                }
                            }
                        }
                        GroupBox {
                            id: group2
                            title:"Tab Position"
                            width: area.width
                            adjustToContentSize: true
                            ButtonRow {
                                id: tabPositionGroup
                                exclusive: true
                                RadioButton {
                                    id: r1
                                    text: "North"
//                                    KeyNavigation.tab: r2
//                                    KeyNavigation.backtab: tickmarkCheck
                                    checked: true
                                }
                                RadioButton {
                                    id: r2
                                    text: "South"
//                                    KeyNavigation.tab: area
//                                    KeyNavigation.backtab: r1
                                }
                            }
                        }

                        TextArea {
                            id: area
                            frame: frameCheckbox.checked
//                            text: mydispather.get_themes()
                            text: "kobe111"//loremIpsum + loremIpsum
                            KeyNavigation.tab: button1
                        }
                    }
                }
            }
        }
        Tab {
            id:mytab
            title: qsTr("清理垃圾")
            contentMargin: 20
//            ModelView {
//                anchors.fill: parent
//                anchors.margins: 6
//            }
        }
        Tab {
            title: qsTr("清理插件")
            contentMargin: 20
            Row {
                anchors.fill: parent
                anchors.margins:16
                spacing:16

                Column {
                    spacing:12

                    GroupBox {
                        title: "Animation options"
                        adjustToContentSize: true
                        ButtonRow {
                            exclusive: false
                            CheckBox {
                                id:fade
                                text: "Fade on hover"
                            }
                            CheckBox {
                                id: scale
                                text: "Scale on hover"
                            }
                        }
                    }
                    Row {
                        spacing: 20
                        Column {
                            spacing: 10
                            Button {
                                width:200
                                text: "Push button"
                                scale: scale.checked && containsMouse ? 1.1 : 1
                                opacity: !fade.checked || containsMouse ? 1 : 0.5
                                Behavior on scale { NumberAnimation { easing.type: Easing.OutCubic ; duration: 120} }
                                Behavior on opacity { NumberAnimation { easing.type: Easing.OutCubic ; duration: 220} }
                                onClicked: {
//                                    console.log("555555555555555555");
//                                    console.log(systemdispatcher.get_record_number("cookies"));
//                                    console.log("666666666666666666");
//                                    console.log(systemdispatcher.get_record_number("history"));
//                                    console.log("777777777777777777");
                                }
                            }

                            Button {
                                width:200
                                text: "Clean button"
//                                scale: scale.checked && containsMouse ? 1.1 : 1
//                                opacity: !fade.checked || containsMouse ? 1 : 0.5
//                                Behavior on scale { NumberAnimation { easing.type: Easing.OutCubic ; duration: 120} }
//                                Behavior on opacity { NumberAnimation { easing.type: Easing.OutCubic ; duration: 220} }
                                onClicked: {
                                    console.log("888888888");
                                    mydispather.clean_browser_record("cookies")
                                    mydispather.clean_browser_record("history")
                                    console.log("9999999999");
                                }
                            }

                            Slider {
                                value: 0.5
                                scale: scale.checked && containsMouse ? 1.1 : 1
                                opacity: !fade.checked || containsMouse ? 1 : 0.5
                                Behavior on scale { NumberAnimation { easing.type: Easing.OutCubic ; duration: 120} }
                                Behavior on opacity { NumberAnimation { easing.type: Easing.OutCubic ; duration: 220} }
                            }
                            Slider {
                                id : slider1
                                value: 50
                                tickmarksEnabled: false
                                scale: scale.checked && containsMouse ? 1.1 : 1
                                opacity: !fade.checked || containsMouse ? 1 : 0.5
                                Behavior on scale { NumberAnimation { easing.type: Easing.OutCubic ; duration: 120} }
                                Behavior on opacity { NumberAnimation { easing.type: Easing.OutCubic ; duration: 220} }
                            }
                            ProgressBar {
                                value: 0.5
                                scale: scale.checked && containsMouse ? 1.1 : 1
                                opacity: !fade.checked || containsMouse ? 1 : 0.5
                                Behavior on scale { NumberAnimation { easing.type: Easing.OutCubic ; duration: 120} }
                                Behavior on opacity { NumberAnimation { easing.type: Easing.OutCubic ; duration: 220} }
                            }
                            ProgressBar {
                                indeterminate: true
                                scale: scale.checked && containsMouse ? 1.1 : 1
                                opacity: !fade.checked || containsMouse ? 1 : 0.5
                                Behavior on scale { NumberAnimation { easing.type: Easing.OutCubic ; duration: 120} }
                                Behavior on opacity { NumberAnimation { easing.type: Easing.OutCubic ; duration: 220} }
                            }
                        }
                        Dial{
                            width: 120
                            height: 120
                            scale: scale.checked && containsMouse ? 1.1 : 1
                            opacity: !fade.checked || containsMouse ? 1 : 0.5
                            Behavior on scale { NumberAnimation { easing.type: Easing.OutCubic ; duration: 120} }
                            Behavior on opacity { NumberAnimation { easing.type: Easing.OutCubic ; duration: 220} }
                        }
                    }
                }
            }
        }
        Tab {
            title: qsTr("清理痕迹")
            contentMargin: 20

//            Panel {
//                anchors.fill:parent
//            }
        }
    }
}
