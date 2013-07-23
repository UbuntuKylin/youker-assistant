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
    width: parent.width
    height: 435//420//340

    property string btn_text: "开始扫描"
    property string title: "清理Software"
    property string description: "清理Software可以节省磁盘空间"
    property string btn_flag: "software_scan"
    property SystemDispatcher dis: systemdispatcher
    property ListModel listmodel: mainModel
    property ListModel submodel: subModel
    property int sub_num: 0
    property string work_result: ""

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



    //信号绑定，绑定qt的信号finishCleanWork，该信号emit时触发onFinishCleanWork
    Connections
    {
        target: systemdispatcher
//         onFinishScanWork: {
//             console.log("begin onFinishScanWork..............");
        //             if (btn_flag == "software_scan") {
        //                 console.log("****** software_scan Signal handler received  Start******");
        ////                 console.log(msg);
        //                 titleBar.work_result = msg;
        //                 titleBar.state = "SoftwareWork";
        ////                 console.log("******End******");
        //             }

//         }
        onFinishCleanWork: {
//            console.log("33333333333333");
//            console.log(msg);//apt software   package   history   cookies
//            console.log(btn_flag);
            if (btn_flag == "software_work") {
                if (msg == "software") {
                    console.log("******Clear Signal handler received  Start software_work******");
    //                 console.log(msg);
                    root.work_result = msg;
                    root.state = "SoftwareWorkFinish";
                }
            }
        }
    }


    //titlebar
    Row {
        id: titlebar
        spacing: 50
        width: parent.width
        height: 50
        Column {
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 30
//                width: parent.width - 150
            spacing: 2
            Text {
                text: root.title
                font.bold: true
                font.pixelSize: 14
            }
            Text {
                text: root.description
                font.pixelSize: 12
                color: "#7a7a7a"
            }
        }
        Label {
            id: label
            visible: false
            text: ""
            anchors.right: bitButton.left
            anchors.rightMargin: 20
            anchors.verticalCenter: parent.verticalCenter
        }
        Button {
            id: bitButton
            width: 95
            height: 32
            text: root.btn_text
            anchors.right: parent.right
            anchors.rightMargin: 50
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                 //software cruft
                  if (btn_flag == "software_scan") {
                      console.log("software_scan---------------");
                      root.state = "SoftwareWork";
                      software_signal("SoftwareWork");
                  }
                  else if (btn_flag == "software_work") {
                      console.log("software_work---------------");
                      console.log(systemdispatcher.get_software_args());
                      systemdispatcher.clean_file_cruft_qt(systemdispatcher.get_software_args(), "software");
                  }
            }
        }
    }

    ItemListModel {
        id: pluginlist
        anchors.top: titlebar.bottom
        height: parent.height -titlebar.height
        listmodel: root.listmodel
        submodel: root.submodel
        num: root.sub_num
        btn_flag: root.btn_flag
    }


    states: [
        State {
            name: "SoftwareWork"
             PropertyChanges { target: label; visible: true; text: "software扫描完成"}
            PropertyChanges { target: bitButton; text: "开始清理" }
            PropertyChanges { target: root; btn_flag: "software_work" }
        },
        State {
            name: "SoftwareWorkFinish"
            PropertyChanges { target: label; visible: true; text: root.work_result + "清理完毕！" }
            PropertyChanges { target: bitButton; text: "开始扫描" }
            PropertyChanges { target: root; btn_flag: "software_scan" }
        }
    ]
}
