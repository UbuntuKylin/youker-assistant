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

Item {
    id: maincheckbox
    property string checked: "true"    //保存总checkbox处于三种状态中的哪种
    property bool checkedbool: true      //总checkbox的bool型值，check通有的属性，在单独点击总checkbox时进行总控制的变量
    property int minimumWidth: 15//32
    property int minimumHeight: 15//32

    width: minimumWidth
    height: minimumHeight
    signal clicked();
    signal sendMstatus(bool status);

    Rectangle {
        anchors.fill: parent
        anchors.margins: 1
        radius: 5
        smooth:true
        Image {
            id:mainimage
            anchors.fill:parent
            source: "../../img/icons/checkbox.png"
        }
        Image{
            id:simage
            anchors.centerIn: mainimage
            source: "../../img/icons/checkbox_seclect.png"
        }
    }
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: {
            if(checked == "true") {   //当总check处于true状态时，点击后变成false状态
                checked = "false";
            }
            else if(checked== "mid") { //当总check处于中间态时，点击后根据总check的bool型值决定变成true状态还是false状态
                if(checkedbool == false) {
                    checked = "true";
                }
                else if(checkedbool == true) {
                    checked = "false";
                }
            }
            else if(checked == "false") {  //当总check处于false态时，点击后变成true状态
                checked = "true";
            }

            if(checked == "true") {
                simage.source = "../../img/icons/checkbox_seclect.png";
                checkedbool = true;
            }
            else if(checked == "mid") {
                simage.source = "../../img/icons/checkbox_mid.png";
            }
            else if(checked=="false") {
                simage.source = "";
                checkedbool = false;
            }
            maincheckbox.clicked();
        }
    }
    //maincheckbox.checked发生变化时激活该函数
    onCheckedChanged:{
        if(checked == "true") {
            simage.source = "../../img/icons/checkbox_seclect.png";
            checkedbool = true;
            maincheckbox.sendMstatus(true);//1212
        }
        else if(checked == "mid") {
            simage.source = "../../img/icons/checkbox_mid.png";
        }
        else if(checked=="false") {
            simage.source = "";
            checkedbool = false;
            maincheckbox.sendMstatus(false);//1212
        }
    }
}

