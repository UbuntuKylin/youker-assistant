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
//    property int textIndent: 0
    property bool checkbox_status: true
    property bool split_status: false

    property string btn_flag: "one_key_scan"
    property string itemFlag//1210 apt/soft标记 //1212 cache
    property string browserFlag//浏览器标记
    signal change_num(bool check_status, string browser_flag)   //作为子项checkbox，当状态改变时需要通过信号传给父项以进行个数统计
    signal clicked

    width: 850
    height: 40
    clip: true
    onSelectedChanged: selected ? state = 'selected' : state = ''
    onCheckbox_statusChanged: {checkbox.checked=checkbox_status}  //当父项传进来的check值改变时，强制改变全部子项的check值以进行统一控制

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
            //单个checkbox状态改变时，先将状态通过信号change_num()传递给BrowserCookies.qml
            container.change_num(checkbox.checked, container.browserFlag);
            //for apt and soft  //pengshuang
//            if (checkbox.checked) {
////                if (btn_flag == "apt_work") {
//                if(container.itemFlag == "apt") {
//                    var aptlist = systemdispatcher.get_cache_args();
//                    var word_flag = "false";
//                    for (var i=0; i<aptlist.length; i++) {
//                        if (aptlist[i] == container.text) {
//                            word_flag = "true";
//                            break;
//                        }
//                    }
//                    if (word_flag == "false") {
//                        systemdispatcher.set_cache_args(container.text);
//                    }
//                }
////                else if (btn_flag == "software_work") {
//                else if(container.itemFlag == "soft") {
//                    var softwarelist = systemdispatcher.get_cache_args();
//                    var word_flag1 = "false";
//                    for (var j=0; j<softwarelist.length; j++) {
//                        if (softwarelist[j] == container.text) {
//                            word_flag1 = "true";
//                            break;
//                        }
//                    }
//                    if (word_flag1 == "false") {
//                        systemdispatcher.set_cache_args(container.text);
//                    }
//                }
//                else {
//                    if (btn_flag == "cookies_work") {
//                        var cookieslist = systemdispatcher.get_cookies_args();
//                        var word_flag2 = "false";
//                        for (var k=0; k<cookieslist.length; k++) {
//                            if (cookieslist[k] == container.text) {
//                                word_flag2 = "true";
//                                break;
//                            }
//                        }
//                        if (word_flag2 == "false") {
//                            systemdispatcher.set_cookies_args(container.text);
//                        }
//                    }
//                    else if (btn_flag == "package_work") {
//                        var mylist = systemdispatcher.get_package_args();
//                        var word_flag3 = "false";
//                        for (var q=0; q<mylist.length; q++) {
//                            if (mylist[q] == container.text) {
//                                word_flag3 = "true";
//                                break;
//                            }
//                        }
//                        if (word_flag3 == "false") {
//                            systemdispatcher.set_package_args(container.text);
//                        }
//                    }

//                    else if (btn_flag == "largestfile_work") {
//                        var filelist = systemdispatcher.get_largestfile_args();
//                        var word_flag4 = "false";
//                        for (var t=0; t<filelist.length; t++) {
//                            if (filelist[t] == container.descript) {
//                                word_flag4 = "true";
//                                break;
//                            }
//                        }
//                        if (word_flag4 == "false") {
//                            systemdispatcher.set_largestfile_args(container.descript);
//                        }
//                    }

//                    else if (btn_flag == "kernel_work") {
//                        var kernellist = systemdispatcher.get_kernel_args();
//                        var word_flag5 = "false";
//                        for (var y=0; y<kernellist.length; y++) {
//                            if (kernellist[y] == container.text) {
//                                word_flag5 = "true";
//                                break;
//                            }
//                        }
//                        if (word_flag5 == "false") {
//                            systemdispatcher.set_kernel_args(container.text);
//                        }
//                    }
//                }
//            }
//            else if (!checkbox.checked) {
//                if(container.itemFlag == "apt") {
////                if (btn_flag == "apt_work") {
//                    systemdispatcher.del_cache_args(container.text);
//                }
//                else if(container.itemFlag == "soft") {
////                else if (btn_flag == "software_work") {
//                    systemdispatcher.del_cache_args(container.text);
//                }
//                else {
//                   if (btn_flag == "cookies_work") {
//                        systemdispatcher.del_cookies_args(container.text);
//                    }
//                    else if (btn_flag == "package_work") {
//                        systemdispatcher.del_package_args(container.text);
//                    }
//                    else if (btn_flag == "kernel_work") {
//                        systemdispatcher.del_kernel_args(container.text);
//                    }
//                    else if (btn_flag == "largestfile_work") {
//                        systemdispatcher.del_largestfile_args(container.descript);
//                    }
//                }
//            }



            //for apt or soft
            if (checkbox.checked) {
                if (btn_flag == "apt_work") {
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
                else if (btn_flag == "software_work") {
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
                else if (btn_flag == "cookies_work") {
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
                else if (btn_flag == "package_work") {
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

                else if (btn_flag == "kernel_work") {
                    var kernellist = systemdispatcher.get_kernel_args();
                    var word_flag5 = "false";
                    for (var y=0; y<kernellist.length; y++) {
                        if (kernellist[y] == container.text) {
                            word_flag5 = "true";
                            break;
                        }
                    }
                    if (word_flag5 == "false") {
                        systemdispatcher.set_kernel_args(container.text);
                    }
                }
            }
            else if (!checkbox.checked) {
                if (btn_flag == "apt_work") {
                    systemdispatcher.del_apt_args(container.text);
                }
                else if (btn_flag == "software_work") {
                    systemdispatcher.del_software_args(container.text);
                }
               else if (btn_flag == "cookies_work") {
                    systemdispatcher.del_cookies_args(container.text);
                }
                else if (btn_flag == "package_work") {
                    systemdispatcher.del_package_args(container.text);
                }
                else if (btn_flag == "kernel_work") {
                    systemdispatcher.del_kernel_args(container.text);
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

    Row {
        spacing: 10
        anchors {
            top: parent.top
            right: parent.right
            rightMargin: 80
            verticalCenter: container.verticalCenter
        }
        Text {
            text: {
                if(container.descript == "True") {//文件夹
                    qsTr("Folder")
                }
                else if(container.descript == "False") {//文件
                    qsTr("File")
                }
                else {
                    container.descript
                }
            }
            anchors.verticalCenter: parent.verticalCenter
            color: container.fontColor
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            text: container.size_num
            anchors.verticalCenter: parent.verticalCenter
            color: container.fontColor
            elide: Text.ElideRight
            verticalAlignment: Text.AlignVCenter
        }
    }

    MouseArea {
        id: mouseArea
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
