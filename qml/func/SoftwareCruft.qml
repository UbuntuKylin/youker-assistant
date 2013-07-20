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
import QtDesktop 0.1
//import RegisterMyType 0.1
//import SessionType 0.1
import SystemType 0.1
import "common" as Common

Item {
    id:root
//    property Dispatcher dis: mydispather
    width: parent.width
    height: 435//420//340
//    color:"#c3c3c3"
    //垃圾清理自定义标题栏
    property string btn_text: "开始扫描"
    property string title: "清理Software"
    property string description: "清理Software可以节省磁盘空间"
    property string btn_flag: "software_scan"
    property SystemDispatcher dis: systemdispatcher
    property ListModel listmodel: mainModel
    property ListModel submodel: subModel
    property int sub_num: 0



    signal software_signal(string software_msg);
    onSoftware_signal: {
        if (software_msg == "SoftwareWork") {
            //get data of cookies
            var software_data = systemdispatcher.scan_softwarecenter_cruft_qt();

            root.sub_num = software_data.length;
            systemdispatcher.clear_software_args();
            subModel.clear();
            var num = 0;
            for (var i=0; i< software_data.length; i++) {
//                console.log(software_data[i]);//  /home/kobe/.cache/software-center/piston-helper<2_2>3026257
                var splitlist = software_data[i].split("<2_2>");
                if (splitlist[0] == "") {
                    num++;
                }
                else {
                    subModel.append({"itemTitle": splitlist[0], "desc": "","number": splitlist[1] + "字节"});
                    systemdispatcher.set_software_args(splitlist[0]);
//                    console.log(splitlist[0]);
                }
            }
//            console.log("**********************");
//            console.log(systemdispatcher.get_software_args());
            root.sub_num -= num;
            mainModel.clear();
            mainModel.append({"itemTitle": "清理浏览器Cookies",
                             "picture": "../img/icons/user.png",
                             "detailstr": "清理Cookies，让系统更安全",
                             "flags": "clear_software",
                            "attributes":
                                 [{"subItemTitle": "Cookies1"},
                                 {"subItemTitle": "Cookies2"},
                                 {"subItemTitle": "Cookies3"},
                                 {"subItemTitle": "Cookies4"}]
                             })
        }
    }


    ListModel {
        id: mainModel
        ListElement {
            itemTitle: "清理Software"
            picture: "../img/icons/user.png"
            detailstr: "清理Software可以节省磁盘空间"
            flags: "clear_software"
            attributes: [
                ListElement { subItemTitle: "" }
            ]
        }
    }

    ListModel {
        id: subModel
        ListElement {itemTitle: ""; desc: ""; number: ""}
    }

    ItemListModel {
        id: pluginlist
        height: parent.height
        btn_text: root.btn_text
        title: root.title
        description: root.description
        btn_flag: root.btn_flag
        listmodel: root.listmodel
        submodel: root.submodel
        num: root.sub_num
    }
}
