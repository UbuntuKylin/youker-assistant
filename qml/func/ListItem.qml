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
import "common" as Common
Item {
    id: container

    property string fontName: "Helvetica"
    property int fontSize: 10
    property color fontColor: "black"
    property bool fontBold: false
    property string text: ""
    property string descript: ""
    property string size_num: ""
    property string bgImage: '../img/icons/list_item.png'

    property string bgImageSelected: '../img/icons/list_item_selected.png'
    property string bgImagePressed: '../img/icons/list_item_pressed.png'
    property bool selected: false
    property bool selectable: false
    property int textIndent: 0
    property bool checkbox_status: true
    property bool split_status: false

    property string btn_flag: "one_key_scan"
    signal change_num(bool check_status)
    signal clicked

    width: 360
    height: 64
    clip: true
    onSelectedChanged: selected ? state = 'selected' : state = ''
    onCheckbox_statusChanged: {checkbox.checked=checkbox_status}

    function get_last_name(str)
    {
        var need_str = str;
        need_str = need_str.substr(need_str.lastIndexOf("/") + 1, need_str.length - need_str.lastIndexOf("/"));
        return need_str;
    }

    BorderImage {
        id: background
        border { top: 9; bottom: 36; left: 35; right: 35; }
        source: bgImage
        anchors.fill: parent
    }

    Common.CheckBox {
        id: checkbox
//        width: 30
        checked: true
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 30
        onCheckedChanged: {
            container.change_num(checkbox.checked);
            if (checkbox.checked) {
                if (btn_flag == "apt_work" || btn_flag == "apt_scan") {
                    var aptlist = systemdispatcher.get_apt_args();
                    var word_flag = "false";
                    for (var i=0; i<aptlist.length; i++) {
                        if (aptlist[i] == container.text) {
                            word_flag = "true";
                            break;
                        }
                    }
                    if (word_flag == "false") {
                        systemdispatcher.set_apt_args(container.text);
                    }
                }
                else if (btn_flag == "software_work" || btn_flag == "software_scan") {
                    var softwarelist = systemdispatcher.get_software_args();
                    var word_flag1 = "false";
                    for (var j=0; j<softwarelist.length; j++) {
                        if (softwarelist[j] == container.text) {
                            word_flag1 = "true";
                            break;
                        }
                    }
                    if (word_flag1 == "false") {
                        systemdispatcher.set_software_args(container.text);
                    }
                }
                else if (btn_flag == "cookies_work" || btn_flag == "cookies_scan") {
                    var cookieslist = systemdispatcher.get_cookies_args();
                    var word_flag2 = "false";
                    for (var k=0; k<cookieslist.length; k++) {
                        if (cookieslist[k] == container.text) {
                            word_flag2 = "true";
                            break;
                        }
                    }
                    if (word_flag2 == "false") {
                        systemdispatcher.set_cookies_args(container.text);
                    }
                }
                else if (btn_flag == "package_work" || btn_flag == "package_scan") {
                    var mylist = systemdispatcher.get_package_args();
                    var word_flag3 = "false";
                    for (var q=0; q<mylist.length; q++) {
                        if (mylist[q] == container.text) {
                            word_flag3 = "true";
                            break;
                        }
                    }
                    if (word_flag3 == "false") {
                        systemdispatcher.set_package_args(container.text);
                    }
                }


                else if (btn_flag == "largestfile_work") {
                    var filelist = systemdispatcher.get_largestfile_args();
                    var word_flag4 = "false";
                    for (var t=0; t<filelist.length; t++) {
                        if (filelist[t] == container.descript) {
                            word_flag4 = "true";
                            break;
                        }
                    }
                    if (word_flag4 == "false") {
                        systemdispatcher.set_largestfile_args(container.descript);
                    }
                }
            }
            else if (!checkbox.checked) {
                if (btn_flag == "apt_work" || btn_flag == "apt_scan") {
                    systemdispatcher.del_apt_args(container.text);
                }
                else if (btn_flag == "software_work" || btn_flag == "software_scan") {
                    systemdispatcher.del_software_args(container.text);
                }
               else if (btn_flag == "cookies_work" || btn_flag == "cookies_scan") {
                    systemdispatcher.del_cookies_args(container.text);
                }
                else if (btn_flag == "package_work" || btn_flag == "package_scan") {
                    systemdispatcher.del_package_args(container.text);
                }
                else if (btn_flag == "largestfile_work") {
                    systemdispatcher.del_largestfile_args(container.descript);
                }

            }

        }
        visible: itemText.text=="" ? false : true
    }
    Text {
        id: itemText
        anchors {
            left: checkbox.right
            top: parent.top
            topMargin: 4
            bottomMargin: 4
            leftMargin: 10// + textIndent
            verticalCenter: container.verticalCenter
        }
        font {
            family: container.fontName
            pointSize: container.fontSize
            bold: container.fontBold
        }
        color: container.fontColor
        elide: Text.ElideRight
//        text: get_last_name(container.text)
        text: container.split_status ? get_last_name(container.text) : container.text
        verticalAlignment: Text.AlignVCenter
    }

    Text {
        text: container.descript
        anchors {
            left: itemText.right
            top: parent.top
            leftMargin: 20
            verticalCenter: container.verticalCenter
        }
        color: container.fontColor
        elide: Text.ElideRight
        verticalAlignment: Text.AlignVCenter
    }

    Text {
        text: container.size_num
        anchors {
            top: parent.top
            right: parent.right
            rightMargin: 80
            verticalCenter: container.verticalCenter
        }
        color: container.fontColor
        elide: Text.ElideRight
        verticalAlignment: Text.AlignVCenter
    }

    MouseArea {
        id: mouseArea
//        anchors.fill: parent
        anchors.fill: itemText
        onClicked: container.clicked();
        onReleased: selectable && !selected ? selected = true : selected = false
    }

    states: [
        State {
            name: 'pressed'; when: mouseArea.pressed
            PropertyChanges { target: background; source: bgImagePressed; border { left: 35; top: 35; right: 35; bottom: 10 } }
        },
        State {
            name: 'selected'
            PropertyChanges { target: background; source: bgImageSelected; border { left: 35; top: 35; right: 35; bottom: 10 } }
        }
    ]
}
