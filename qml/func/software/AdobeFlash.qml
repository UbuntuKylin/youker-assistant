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
//import SessionType 0.1
import SystemType 0.1
import "../common" as Common
import "../bars" as Bars
import "../../func" as Func
Rectangle {
    id: adobeflash
    property bool on: true
    //需要时常变动的变量
    property string software_name: content.delegate_name
    property string software_information: content.delegate_information
    property string software_image: content.delegate_image
    property string software_introduction: content.delegate_introduction
    property string introduction_image1: content.introduction_image1
    property string introduction_image2: content.introduction_image2
    property string installed_status: content.install_status
//    property string appname: ""
    width: parent.width
    height: 475

    function split_string(statusdata) {
        var splitlist = statusdata.split(":");
        adobeflash.appname = splitlist[0];
        adobeflash.installed_status = splitlist[1];
    }

    //背景
    Image {
        source: "../../img/skin/bg-bottom-tab.png"
        anchors.fill: parent
    }
    Rectangle{
        width: parent.width-2;height: 36
        gradient: Gradient{
            GradientStop{position: 0.0; color: "#e2e2e2"}
            GradientStop{position: 1.0; color: "#dedede"}
        }
        anchors{
            top:parent.top
            left: parent.left
            leftMargin: 1
        }
        Common.Button{
            width: 80;height: 28
            anchors{
                left: parent.left
                leftMargin: 8
                verticalCenter: parent.verticalCenter
            }
            hoverimage: "blue1.png"
            text:"返回"
            fontcolor: "grey"
            fontsize: 14
            onClicked: {
                pageStack.push(softwarerecommend);
            }
        }
        Text {
            anchors.centerIn: parent
            text:"详细信息"
            color:"grey"
            font.bold: true
            font.pixelSize: 14
        }
    }
    Rectangle{
        width: parent.width-50;height: 110
        anchors{
            top:parent.top
            topMargin: 47
            left: parent.left
            leftMargin: 25
        }
        border.color: "lightgrey"
        Image {
            id: softwareimage
            source: software_image
//            source: softwaredelegate.delegate_image
            anchors{
                left: parent.left
                leftMargin: 20
                verticalCenter: parent.verticalCenter
            }
        }
        Column{
            anchors{
                left: parent.left
                leftMargin: 105
                verticalCenter: parent.verticalCenter
            }
            spacing: 10
            Text{
                id:softwarename
                text:software_name
//                text:softwaredelegate.delegate_name

                font.pixelSize: 18
            }
            Text {
                id: softwareinformation
                text: software_information
//                text:softwaredelegate.delegate_information

                font.pixelSize: 14
            }
        }
        Common.Button{
            width:145;height: 43
            anchors{
                right:parent.right
                rightMargin: 125
                verticalCenter: parent.verticalCenter
            }
            text:"立即下载"
            fontsize: 20
            onClicked: {
                console.log("立即下载")
                split_string(software_name);
                console.log(adobeflash.installed_status);
//                console.log(adobeflash.appname);
                if(adobeflash.installed_status == "n") {
                    console.log("start to install....");
                    sudodispatcher.install_pkg_qt(adobeflash.software_name);
                    sudodispatcher.show_progress_dialog();
                }
                else if(adobeflash.installed_status == "i")
                    console.log("is installed already....");
            }
        }

    }
    Rectangle {
        id: views
        width: parent.width-50
        height: 276
        anchors{
            bottom:parent.bottom
            bottomMargin: 17
            left: parent.left
            leftMargin: 25
        }
        clip:true
        border.color: "#9aa2af"
        color: "#e6ebfe"
        Rectangle{
            id:rec
            width: parent.width-1;height: 31
            anchors{
                top:parent.top
                topMargin: 1
                left: parent.left
                leftMargin: 1
            }
            gradient: Gradient{
                GradientStop{position: 0.0; color: "#e2e2e2"}
                GradientStop{position: 1.0; color: "#dedede"}
            }
            Text {
                anchors.centerIn: parent
                text:"软件介绍"
                color:"grey"
                font.bold: true
                font.pixelSize: 14
            }
        }
        Rectangle{id: splitbar1; anchors{top:rec.bottom;left: parent.left;leftMargin: 1 }width:parent.width-1 ; height:1; color:"#b8bdc3"}
        Rectangle{id: splitbar2; anchors{top:splitbar1.bottom;left: parent.left;leftMargin: 1  }width:parent.width-1 ; height:1; color:"#ebf0f6"}
        Text {
            id: softwareintroduction
            width: parent.width-30
            anchors{
                left:parent.left
                leftMargin: 15
                top:parent.top
                topMargin: 46
            }
            font.pixelSize: 13
            text: software_introduction
//            text:softwaredelegate.delegate_introduction
            wrapMode: Text.WrapAnywhere
        }
        Row{
            anchors{
                horizontalCenter: parent.horizontalCenter
                bottom: parent.bottom
                bottomMargin: 20
            }
            spacing: 80
            Image {
                id: introductionimage1
                source: introduction_image1
//                source: softwaredelegate.introduction_image1
            }
            Image {
                id: introductionimage2
                source: introduction_image2
//                source: softwaredelegate.introduction_image2
            }
        }
    }

}
