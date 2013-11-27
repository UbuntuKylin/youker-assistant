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
import SystemType 0.1
Item {
    id: btn
    signal clicked
    signal exited
    signal entered
//    property string text
    property string text : ""
    property string hoverimage: "green1.png"
    property string fontcolor: "white"
    property int fontsize: 14


    //-----------------------------------------------
    SystemPalette { id: myPalette; colorGroup: SystemPalette.Active }
    property string setbtn_flag: ""
    property string get_msg: ""
    property bool check_flag: true

    signal send_dynamic_picture(string str);

    Connections
    {
        target: sessiondispatcher
        onFinishScanWork: {
            if(msg == "onekey") {
                btn.setbtn_flag = "onekey";
                btnImg.source = "../../img/icons/green3.png"
                displaytext.text = qsTr("Clean Quickly");//一键清理
            }
        }
    }

    //信号绑定，绑定qt的信号finishCleanWork，该信号emit时触发onFinishCleanWork,按钮恢复使能
    Connections{
         target: systemdispatcher
             onFinishCleanWorkMain: {
                 if(btn.setbtn_flag =="onekey")
                 {
                    if (msg == "") {
                        btn.enabled=true;
                        if (btn.setbtn_flag == "onekey") {
                            btnImg.source = "../../img/icons/green3.png"
                            displaytext.text = qsTr("Clean Quickly");//一键清理
                        }
                    }
                    else if (msg == "u" || msg == "c" || msg == "h" || msg == "k") {
                         btn.enabled=true;
                         displaytext.text = qsTr("Cleaning up...");//正在清理...
                    }
                    else if (msg == "o") {
                        btn.enabled=true;
//                        displaytext.text = qsTr("Clean again");//再次清理
                        displaytext.text = qsTr("Scan Quickly");//一键扫描
                        btn.setbtn_flag = "onekeyscan";
                    }
                 }
          }
    }
    Connections
    {
        target: systemdispatcher
        onFinishCleanWorkSecond: {
            if(btn.setbtn_flag=="smallonekey")
            {
                if (msg == "") {
                     btn.enabled=true;
                    btnImg.source = "../../img/icons/green1.png"
                    displaytext.text = qsTr("A key to clean up");//一键清理
                }
                else if (msg == "u" || msg == "c" || msg == "h" || msg == "k") {
                     btn.enabled=true;
                     displaytext.text = qsTr("Cleaning up...");//正在清理...
                }
                else if (msg == "o") {
                    btn.enabled=true;
                    displaytext.text = qsTr("Clean again");//再次清理
                }
            }
        }
    }
    //-----------------------------------------------

    BorderImage {
        id: buttonImage
        source: "../../img/icons/" + btn.hoverimage
        width: btn.width; height: btn.height
    }
    BorderImage {
        id: pressed
        opacity: 0
        source: "../../img/icons/unselect.png"
        width: btn.width; height: btn.height
    }
    Image {
        id: btnImg
        anchors.fill: parent
        source: ""
    }
    MouseArea {
        id: mouseRegion
        anchors.fill: buttonImage
        hoverEnabled: true
//        id: signaltest
//        anchors.fill: parent

//        onEntered: btnImg.source = "../../img/toolWidget/menu_hover.png"
//        onPressed: btnImg.source = "../../img/toolWidget/menu_press.png"
//        //要判断松开是鼠标位置
//        onReleased: btnImg.source = "../../img/toolWidget/menu_hover.png"
//        onExited: btnImg.source = ""

        onEntered: {
            btn.entered();
            if (hoverimage == "green1.png") {
                btnImg.source = "../../img/icons/green1-hover.png"
//                if(setbtn_flag=="smallonekey")
//                    displaytext.text = "再次清理";
            }
            else if (hoverimage == "blue1.png")
                btnImg.source = "../../img/icons/blue1-hover.png"
            else if (hoverimage == "green2.png")
                btnImg.source = "../../img/icons/green2-hover.png"
            else if (hoverimage == "gray1.png")
                btnImg.source = "../../img/icons/gray1-hover.png"
            else if (hoverimage == "blue2.png")
                btnImg.source = "../../img/icons/blue2-hover.png"
            else if (hoverimage == "blue3.png")
                btnImg.source = "../../img/icons/blue3-hover.png"
            else if (hoverimage == "blue4.png")
                btnImg.source = "../../img/icons/blue4-hover.png"
            else if (hoverimage == "green3.png") {
                btnImg.source = "../../img/icons/green3-hover.png"
//                if(setbtn_flag =="onekey")
//                    displaytext.text = "再次清理";
            }
            else if(hoverimage == "fcitxKey.png")
                  btnImg.source = "../../img/icons/fcitxKey-hover.png"
            else if(hoverimage == "fcitxFont.png")
                  btnImg.source = "../../img/icons/fcitxFont-hover.png"
            else
                btnImg.source = "../../img/toolWidget/menu_hover.png"
//            if (hoverimage == "return.png")
//                btnImg.source = "../../img/icons/return-hover.png"
//            else if (hoverimage == "sort.png")
//                btnImg.source = "../../img/icons/sort-hover.png"
//            else if (hoverimage == "selectpic.png")
//                btnImg.source = "../../img/icons/selectpic-hover.png"
//            else if (hoverimage == "use.png")
//                btnImg.source = "../../img/icons/use-hover.png"
//            else
//                btnImg.source = "../../img/toolWidget/menu_hover.png"
        }
        onPressed: {
            if (hoverimage == "green1.png")
                btnImg.source = "../../img/icons/green1-hover.png"
            else if (hoverimage == "blue1.png")
                btnImg.source = "../../img/icons/blue1-hover.png"
            else if (hoverimage == "green2.png")
                btnImg.source = "../../img/icons/green2-hover.png"
            else if (hoverimage == "gray1.png")
                btnImg.source = "../../img/icons/gray1-hover.png"
            else if (hoverimage == "blue2.png")
                btnImg.source = "../../img/icons/blue2-hover.png"
            else if (hoverimage == "blue3.png")
                btnImg.source = "../../img/icons/blue3-hover.png"
            else if (hoverimage == "blue4.png")
                btnImg.source = "../../img/icons/blue4-hover.png"
            else if (hoverimage == "green3.png")
                btnImg.source = "../../img/icons/green3-hover.png"
            else
                btnImg.source = "../../img/toolWidget/menu_press.png"
//            if (hoverimage == "return.png")
//                btnImg.source = "../../img/icons/return-hover.png"
//            else if (hoverimage == "sort.png")
//                btnImg.source = "../../img/icons/sort-hover.png"
//            else if (hoverimage == "selectpic.png")
//                btnImg.source = "../../img/icons/selectpic-hover.png"
//            else if (hoverimage == "use.png")
//                btnImg.source = "../../img/icons/use-hover.png"
//            else
//                btnImg.source = "../../img/toolWidget/menu_press.png"

        }
        //要判断松开是鼠标位置
        onReleased: {
            if (hoverimage == "green1.png")
                btnImg.source = "../../img/icons/green1.png"
            else if (hoverimage == "blue1.png")
                btnImg.source = "../../img/icons/blue1.png"
            else if (hoverimage == "green2.png")
                btnImg.source = "../../img/icons/green2.png"
            else if (hoverimage == "gray1.png")
                btnImg.source = "../../img/icons/gray1.png"
            else if (hoverimage == "blue2.png")
                btnImg.source = "../../img/icons/blue2.png"
            else if (hoverimage == "blue3.png")
                btnImg.source = "../../img/icons/blue3.png"
            else if (hoverimage == "blue4.png")
                btnImg.source = "../../img/icons/blue4.png"
            else if (hoverimage == "green3.png")
                btnImg.source = "../../img/icons/green3.png"
            else
                btnImg.source = "../../img/toolWidget/menu_hover.png"
//            if (hoverimage == "return.png")
//                btnImg.source = "../../img/icons/return.png"
//            else if (hoverimage == "sort.png")
//                btnImg.source = "../../img/icons/sort.png"
//            else if (hoverimage == "selectpic.png")
//                btnImg.source = "../../img/icons/selectpic.png"
//            else if (hoverimage == "use.png")
//                btnImg.source = "../../img/icons/use.png"
//            else
//                btnImg.source = "../../img/toolWidget/menu_hover.png"
        }

        onExited: {
            btn.exited();
            btnImg.source = ""
        }

        onClicked: {
            btn.clicked();
            //----------------
            if(check_flag)
            {
                if (btn.setbtn_flag == "onekeyscan") {
                    send_dynamic_picture("onekeyscan");
                    sessiondispatcher.onekey_scan_function_qt(systemdispatcher.get_onekey_args());
//                    systemdispatcher.set_user_homedir_qt();
//                    systemdispatcher.clean_by_main_one_key_qt(systemdispatcher.get_onekey_args());
//                    btn.enabled=false;
                }
                else if (btn.setbtn_flag == "onekey") {
                    send_dynamic_picture("onekey");
                    systemdispatcher.set_user_homedir_qt();
                    systemdispatcher.clean_by_main_one_key_qt(systemdispatcher.get_onekey_args());
                }

                else if (btn.setbtn_flag == "smallonekey") {
                    systemdispatcher.set_user_homedir_qt();
                    systemdispatcher.clean_by_second_one_key_qt(systemdispatcher.get_onekey_args2());
                    btn.enabled=false;
                }
            }
            else
                sessiondispatcher.showWarningDialog("友情提示：","对不起，您没有选中清理项，请确认！", mainwindow.pos.x, mainwindow.pos.y);
        }
    }
//    Image {
//        id: testbtn
//        source: "../../img/icons/arrowhead.png"
//        visible: (setbtn_flag == "onekey") ? true : false
//        anchors.verticalCenter: parent.verticalCenter
//        anchors.left: parent.left
//        anchors.leftMargin: 10
//    }
    Text {
        id: displaytext
        color: btn.fontcolor
//        visible: (btn.text == "") ? false : true
        anchors.centerIn: buttonImage
//        font.bold: true
        font.family: "Helvetica"
        font.pixelSize: fontsize
        text: btn.text
        style: Text.Sunken
//        style: Text.Raised
//        styleColor: "black"
        styleColor: "#AAAAAA"
    }
    states: [
        State {
            name: "Pressed"
            when: mouseRegion.pressed == true
            PropertyChanges { target: pressed; opacity: 1 }
        }
    ]
}






//Item {
//    id: btn
////    signal clicked
////    property string text
////    property string text : ""
////    property string hoverimage: "scan-start.png"

////  按钮的颜色和字体处理
//    property string color1:"#87bc1d"
//    property string color2:"#6b9e00"
//    property string bordercolor:"#6fa200"
//    property string text:""
//    property int textsize:10
//    property bool bold: false

//    SystemPalette { id: myPalette; colorGroup: SystemPalette.Active }
////    color: "transparent"
////    property string iconName: "onekeyBtn.png"
//    property string setbtn_flag: ""

//    property string get_msg: ""
//    property bool check_flag: true

//    signal clicked();   //如果没有选中任何清理项，提示警告框！first page

//    signal send_dynamic_picture(string str);
//    //信号绑定，绑定qt的信号finishCleanWork，该信号emit时触发onFinishCleanWork,按钮恢复使能
//    Connections{
//         target: systemdispatcher
//             onFinishCleanWorkMain: {
//                 if(setbtn_flag =="onekey"||setbtn_flag=="smallonekey")
//                 {
//                    if (msg == "") {
//                        btn.enabled=true;
//                        if (setbtn_flag == "onekey")
//                            btnImg.source = "../img/icons/onekeyBtn.png"
//                     }
//                    else if (msg == "u") {
//                         btn.enabled=true;
//                    }
//                    else if (msg == "c") {
//                         btn.enabled=true;
//                    }
//                    else if (msg == "h") {
//                        btn.enabled=true;
//                    }
//                    else if (msg == "k") {
//                        btn.enabled=true;
//                    }
//                 }
//          }
//    }
//    Connections
//    {
//        target: systemdispatcher
//        onFinishCleanWorkSecond: {
//            if(setbtn_flag =="onekey"||setbtn_flag=="smallonekey")
//            {
//                if (msg == "") {
//                     btn.enabled=true;
//                    btnImg.source = "../img/icons/onekey.png"
//                 }
//                 else if (msg == "u") {
//                     btn.enabled=true;
//                 }
//                 else if (msg == "c") {
//                     btn.enabled=true;
//                 }
//                else if (msg == "h") {
//                    btn.enabled=true;
//                }
//                else if (msg == "k") {
//                    btn.enabled=true;
//                }
//            }
//        }
//    }

////    BorderImage {
////        id: buttonImage
////        source: "../../img/icons/" + btn.hoverimage
////        width: btn.width; height: btn.height
////    }
////    BorderImage {
////        id: pressed
////        opacity: 0
////        source: "../../img/icons/unselect.png"
////        width: btn.width; height: btn.height
////    }

//    Rectangle{
//        id:btnrec
//        anchors.centerIn: parent
//        width:btn.width
//        height:btn.height
//        border.color: bordercolor
//        radius:3
//        smooth:true
//        gradient: Gradient{
//            GradientStop{position: 0.0; color: color1}
//            GradientStop{position: 1.0; color: color2}
//        }
//        Image {
//            id: btnImg
//            anchors.fill: parent
//            source: ""
//        }
//        MouseArea {
//            id: mouseRegion
//            anchors.fill: parent
//            hoverEnabled: true
//            onEntered:{
//                btnImg.source = "../../img/toolWidget/menu_hover.png"
//            }
//            onPressed: btnImg.source = "../../img/toolWidget/menu_press.png"
//            //要判断松开是鼠标位置
//            onReleased:btnImg.source = "../../img/toolWidget/menu_hover.png"
//            onExited: btnImg.source = ""
//            onClicked: {
//                btn.clicked();    //如果没有选中任何清理项，提示警告框,发出信号...
//                if(check_flag)
//                {
//                    if (setbtn_flag == "onekey") {
//                        send_dynamic_picture("onekey");
//                        systemdispatcher.set_user_homedir_qt();
//                        systemdispatcher.clean_by_main_one_key_qt(systemdispatcher.get_onekey_args());
////                        btnImg.source = "../img/icons/onekeyover.png"  //首页点击后更换图片的位置7-30
//                        btn.text="清理完毕";
//                        btn.enabled=false;
//                    }
//                    else if (setbtn_flag == "smallonekey") {
//                        systemdispatcher.set_user_homedir_qt();
//                        systemdispatcher.clean_by_second_one_key_qt(systemdispatcher.get_onekey_args2());
////                        btnImg.source = "../img/icons/clear-over.png"  //首页点击后更换图片的位置7-30
//                        btn.text="清理完毕";
//                        btn.enabled=false;
//                    }
//                }
//                else
//                    sessiondispatcher.showWarningDialog("友情提示：","对不起，您没有选中清理项，请确认！");
//            }
//        }
//    }
//    Text {
//        anchors.centerIn:parent
//        text: btn.text
//        font.bold: bold
//        font.pointSize: textsize
//        color: "white"
//    }

////    Text {
////        color: "white"
//////        visible: (btn.text == "") ? false : true
////        anchors.centerIn: buttonImage; font.bold: true; font.pixelSize: 15
////        text: btn.text; style: Text.Raised; styleColor: "black"
////    }
////    states: [
////        State {
////            name: "Pressed"
////            when: mouseRegion.pressed == true
////            PropertyChanges { target: pressed; opacity: 1 }
////        }
////    ]
//}
