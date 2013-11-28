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
    property string text : ""
    property string hoverimage: "green1.png"
    property string fontcolor: "white"
    property int fontsize: 14

    SystemPalette { id: myPalette; colorGroup: SystemPalette.Active }
    property string setbtn_flag: ""
    property string get_msg: ""
    property bool check_flag: true

    signal send_dynamic_picture(string str);

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
        onEntered: {
            btn.entered();
            if (hoverimage == "green1.png") {
                btnImg.source = "../../img/icons/green1-hover.png"
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
            }
            else if(hoverimage == "fcitxKey.png")
                  btnImg.source = "../../img/icons/fcitxKey-hover.png"
            else if(hoverimage == "fcitxFont.png")
                  btnImg.source = "../../img/icons/fcitxFont-hover.png"
            else
                btnImg.source = "../../img/toolWidget/menu_hover.png"
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
        }

        onExited: {
            btn.exited();
            btnImg.source = ""
        }

        onClicked: {
            btn.clicked();
            if(check_flag)
            {
                if (setbtn_flag == "onekeyscan") {
                    send_dynamic_picture("onekeyscan");
                    sessiondispatcher.onekey_scan_function_qt(systemdispatcher.get_onekey_args());
                }
                else if (setbtn_flag == "onekey") {
                    send_dynamic_picture("onekey");
                    systemdispatcher.set_user_homedir_qt();
                    systemdispatcher.clean_by_main_one_key_qt(systemdispatcher.get_onekey_args());
                }

                else if (setbtn_flag == "smallonekey") {
                    systemdispatcher.set_user_homedir_qt();
                    systemdispatcher.clean_by_second_one_key_qt(systemdispatcher.get_onekey_args2());
                }
            }
            else
                sessiondispatcher.showWarningDialog("友情提示：","对不起，您没有选中清理项，请确认！", mainwindow.pos.x, mainwindow.pos.y);
        }
    }

    Text {
        id: displaytext
        color: btn.fontcolor
        anchors.centerIn: buttonImage
        font.family: "Helvetica"
        font.pixelSize: fontsize
        text: btn.text
        style: Text.Sunken
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
