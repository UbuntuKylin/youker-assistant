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
import "../common/InfoGroup.js" as InfoGroup

//右边栏
Rectangle {
    id: rightbar

    property int distrowatch_num:0
    property string update_rate
    property string activetext : qsTr("Active")//活跃发展中
    property string country : qsTr("China")//中国

    function split_last_str(str)
    {
        var need_str = str;
        need_str = need_str.substr(need_str.lastIndexOf("/") + 1, need_str.length - need_str.lastIndexOf("/"));
        return need_str;
    }

    function transTitle(str) {
        //去掉前后空格
        str = str.replace(/^(\s|\u00A0)+/,'');
        for(var i=str.length-1; i>=0; i--){
            if(/\S/.test(str.charAt(i))){
                str = str.substring(0, i+1);
                break;
            }
        }
        //开始国际化
        var pat1 = new RegExp('Active');
        var pat2 = new RegExp('China');
        if(pat1.test(str)) {
            return rightbar.activetext.toString();
        }
        else if(pat2.test(str)) {
            return rightbar.country.toString();
        }
        return str;
    }

    //更新登录状态
    Connections
    {
        target: sessiondispatcher
        onShowLoginAnimatedImage: {//正在登录过程中显示动态图片
            rightbar.state = "Logining";
        }
        onLoginFailedStatus: {//登录失败
            if(status == 99) {
                toolkits.alertMSG(qsTr("Network Error!"));//网络错误！
            }
            else if(status == -1) {
                toolkits.alertMSG(qsTr("No User!"));//没有该用户！
            }
            else if(status == -2) {
                toolkits.alertMSG(qsTr("Password Wrong!"));//密码错误！
            }
            else {
                toolkits.alertMSG(qsTr("Login Failed!"));//登录失败！
            }
            rightbar.state = "OffLine";
        }
        onUpdateLoginStatus: {//登录成功
            logo.source = "../../img/icons/logo.png"
            userText.text = username;
            levelText.text = "Lv" + level;
            scoreText.text = score;
            rightbar.state = "OnLine";
        }
        onRefreshUserInfo: {//刷新成功
            levelText.text = "Lv" + level;
            scoreText.text = score;
        }
    }

    function setDistrowatchData() {
        //set default value
        var img_source = "";
        var result = sessiondispatcher.get_default_all_distrowatch();
        rightbar.distrowatch_num = result.length;
        listModel.clear();//清空
        for(var i=0; i < result.length; i++) {
            var splitlist = result[i].split("+");
            var os_image = "";
            if (splitlist[2] == "opensuse") {
                os_image = "suse";
            }
            else if (splitlist[2] == "suse") {
                os_image = "sle";
            }
            else if (splitlist[2] == "sparkylinux") {
                os_image = "sparky";
            }
            else if (splitlist[2] == "makululinux") {
                os_image = "makulu";
            }
            else if (splitlist[2] == "gobolinux") {
                os_image = "gobo";
            }
            else if (splitlist[2] == "dragonfly") {
                os_image = "dragonflybsd";
            }
            else if (splitlist[2] == "emmabuntüs") {
                os_image = "emmabuntus";
            }
            else if (splitlist[2] == "symphonyos") {
                os_image = "symphony";
            }
            else {
                os_image = splitlist[2];
            }
            img_source = InfoGroup.judgeDistrowatchName(os_image) ? ("../../img/distrowatch/" + os_image +".png") : ("../../img/distrowatch/default.png");
            listModel.append({"rank": splitlist[0], "os": splitlist[1], "os_img": img_source, "today_hit": splitlist[3], "rank_img": "../../img/distrowatch/" + rightbar.split_last_str(splitlist[4]),  "yestoday_hit": splitlist[5]});
        }

        //set new data
        rightbar.update_rate = sessiondispatcher.get_distrowatch_url_qt();
        if (rightbar.update_rate != "") {
            result = sessiondispatcher.get_distrowatch_info_qt();
            rightbar.distrowatch_num = result.length;
            listModel.clear();//清空
            for(var i=0; i < result.length; i++) {
                var splitlist = result[i].split("+");
                var os_image = "";
                if (splitlist[2] == "opensuse") {
                    os_image = "suse";
                }
                else if (splitlist[2] == "suse") {
                    os_image = "sle";
                }
                else if (splitlist[2] == "sparkylinux") {
                    os_image = "sparky";
                }
                else if (splitlist[2] == "makululinux") {
                    os_image = "makulu";
                }
                else if (splitlist[2] == "gobolinux") {
                    os_image = "gobo";
                }
                else if (splitlist[2] == "dragonfly") {
                    os_image = "dragonflybsd";
                }
                else if (splitlist[2] == "emmabuntüs") {
                    os_image = "emmabuntus";
                }
                else if (splitlist[2] == "symphonyos") {
                    os_image = "symphony";
                }
                else {
                    os_image = splitlist[2];
                }
                listModel.append({"rank": splitlist[0], "os": splitlist[1], "os_img": "http://distrowatch.com/images/yvzhuwbpy/" + os_image +".png", "today_hit": splitlist[3], "rank_img": "http://distrowatch.com/" + splitlist[4],  "yestoday_hit": splitlist[5]});
            }
        }
    }

    ListModel {
        id: listModel
        Component.onCompleted: {
            rightbar.setDistrowatchData();
        }
    }
    //背景
    //    Image {
    //        source: "../../img/skin/bg-right.png"
    //        anchors.fill: parent
    //    }

    Rectangle {
        id: offline
        width: parent.width
        property string path: "../../img/en/"
        Component.onCompleted: {
            if(sessiondispatcher.get_locale_version() == "zh_CN") {
                offline.path = "../../img/zh_CN/";
            }
            else {
                offline.path = "../../img/en/";
            }
            login.showImage = offline.path + "login.png";
        }
        Common.KButton {
            id: login
            kflag: "login"
            showImage: ""
            anchors {
                top: parent.top; topMargin: 25
                horizontalCenter: parent.horizontalCenter
            }
            width: 216
            height: 67
            onClicked: {
                sessiondispatcher.popup_login_dialog();
            }
        }
    }

    Rectangle {
        id: logining
        width: parent.width
        x: (parent.width * 1.5)
        Column {
            spacing: 5
            anchors {
                top: parent.top; topMargin: 40
                horizontalCenter: parent.horizontalCenter
            }
            AnimatedImage {
                width: 16
                height: 16
                anchors.horizontalCenter: parent.horizontalCenter
                source: "../../img/icons/move.gif"
            }
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: 14
                color: "#383838"
                text: qsTr("Logging...") //正在登录...
            }
        }
    }

    //------------------login
    Rectangle {
        id: online
        width: parent.width
        x: (parent.width * 1.5)
        Column {
            id: logcolumn
            spacing: 5
            anchors{
                left: parent.left
                leftMargin: 15
                top:parent.top
                topMargin: 10
            }
            Image {
                id: logo
                width: 56; height: 56
                source: ""
            }
            Common.Button {
                id: logout
                picNormal: "../../img/icons/button12-gray.png"
                picHover: "../../img/icons/button12-gray-hover.png"
                picPressed: "../../img/icons/button12-gray-hover.png"
                fontcolor:"#707070"
                fontsize: 12
                width: 56; height: 24
                text: qsTr("Logout")//注销
                onClicked: {
                    sessiondispatcher.logout_ubuntukylin_account();
                    userText.text = "";
                    levelText.text = "";
                    scoreText.text = "";
                    logo.source = "";
                    rightbar.state = "OffLine";
                }
            }
        }
        Column {
            spacing: 10
            anchors{
                left: logcolumn.right
                leftMargin: 10
                top:parent.top
                topMargin: 10
            }
            Text {
                id: userText
                text: ""
                font.bold: true
                font.pixelSize: 20
                color: "#383838"
                width: 160
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("Level:")//当前等级：
                    width: 60
                }
                Text {
                    id: levelText
                    text: ""
                }
            }
            Row {
                spacing: 10
                Text {
                    text: qsTr("Score:")//当前积分：
                    width: 60
                }
                Text {
                    id: scoreText
                    text: ""
                }
            }
        }
        Common.Separator {
            anchors {
                left: parent.left
                leftMargin: 2
                top: parent.top
                topMargin: 100
            }
            width: parent.width - 4
        }
    }

    WeatherZone {
        id: weatherZone
        width: 208;height: 90//147
        anchors {
            top: parent.top
            topMargin: 105
            horizontalCenter: parent.horizontalCenter
        }
    }

    Common.Separator {
        id: splitbar
//        x: 2; y: 270;
        anchors {
            left: parent.left
            leftMargin: 2
            top: weatherZone.bottom
            topMargin: 3
        }
        width: parent.width - 4
    }

//    Common.ScrollArea {
//        frame:false
//        anchors{
//            top: splitbar.bottom
//            topMargin: 5
//            left:parent.left
//            leftMargin: 5
//        }
//        width: parent.width - 8; height: 230
//        Item {
//            width: parent.width
//            height: rightbar.distrowatch_num * 20//列表长度
//            ListView {
//                focus: true
//                id: distrowatch
//                anchors.fill: parent
//                model: listModel
//                delegate: DistrowatchDelegate {}
//                cacheBuffer: 1000
//            }
//        }
//    }

    Row {
        id: distrowatchname
        anchors {
            top: splitbar.bottom
            topMargin: 5
            left: parent.left
            leftMargin: 8
        }
        spacing: 5
        Image {
            source: "../../img/distrowatch/rank.png"
            width: 16; height: 16
        }
        Text{
            text: qsTr("DistroWatch Ranking")//DistroWatch国际排名
            font.bold:true
            color: "#383838"
            font.pixelSize: 12
        }
    }



    Text {
        id: widthText
        visible: false
        text: qsTr("Details")//详情
    }
    Common.ColorButton {
        id: ubuntukylinBtn
        anchors {
            top: splitbar.bottom
            topMargin: 4
            right: parent.right
            rightMargin: 2
        }
        colorNormal: "#00a0e9"
        colorHover: "#65cfff"
        colorPressed: "#65cfff"
        sizeNormal: 12
        sizeHover: 14
        sizePressed: 14
        height: 20
        wordname: qsTr("Details"); width: widthText.width
        onClicked: {
            ukrect.showFlag = true;
        }
    }//更改鼠标指针


    DistrowatchTitle {
        id: distrowatchtitle
        width: parent.width
        anchors {
            top: distrowatchname.bottom
            topMargin: 10
            left: parent.left
            leftMargin: 5
        }
    }

    Column{//DistroWatch框
        id: distrowatchColumn
        spacing: 5
        width: parent.width
        anchors {
            top: distrowatchtitle.bottom
            topMargin: 5
            left: parent.left
            leftMargin: 5
        }

//        Text{
//            width: parent.width - 20
//            text: qsTr("DistroWatch Rank:")//DistroWatch国际排名：
//            font.bold:true
//            color: "#383838"
//            font.pointSize: 10
//        }

        Rectangle{
            width: parent.width-8; height: 210
            clip:true
            Component{
                id:distrowatchdelegate
                Item{
                    id:wrapper
                    width: parent.width-10; height: 30//220
                    Row {
                        id: degegateRow
                        anchors{
                            verticalCenter: parent.verticalCenter
                            left: parent.left
                            leftMargin: 5
                        }
                        spacing: 5
                        Text {
                            id: ranktext
                            width: 15
                            anchors.verticalCenter: parent.verticalCenter
                            text: rank
//                            color: distrowatchdelegate.ListView.isCurrentItem ? "white" : "black"//选中时字体为白色，未选中时为黑色
                            color: {
                                if (rank == "1") {
                                    "#f2390e"
                                }
                                else if (rank == "2") {
                                    "#f26e0d"
                                }
                                else if (rank == "3") {
                                    "#f5960d"
                                }
                                else {
                                    "black"
                                }
                            }

                            font {
                                family: "Helvetica"
                                pixelSize: {
                                    if (rank == "1") {
                                        18
                                    }
                                    else if (rank == "2") {
                                        16
                                    }
                                    else if (rank == "3") {
                                        14
                                    }
                                    else {
                                        12
                                    }
                                }
                            }

                        }
                        Image {
                            id: icon
                            width: 28; height: 28
//                            width: 90; height: 87
                            source: os_img//"http://distrowatch.com/images/yvzhuwbpy/" + os_img +".png"
                            anchors.verticalCenter: parent.verticalCenter
//                            MouseArea
//                            {
//                                hoverEnabled: true
//                                anchors.fill: parent
//                                onEntered: {
//                                    distrowatchView.spacing = 10;
//                                    degegateRow.spacing = 1;
//                                    distrowatchItem.height = rightbar.distrowatch_num * 30 + (rightbar.distrowatch_num - 1) * 10;
//                                    ranktext.font.pixelSize = 15;
//                                    icon.width = 50;
//                                    icon.height = 50;
//                                }
//                                onPressed: {}
//                                onReleased: {}
//                                onExited: {
//                                    distrowatchView.spacing = 0;
//                                    degegateRow.spacing = 5;
//                                    distrowatchItem.height = rightbar.distrowatch_num * 30;
//                                    ranktext.font.pixelSize = 12;
//                                    icon.width = 28;
//                                    icon.height = 28;
//                                }
//                                onClicked: {}
//                            }
                        }
                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            text: os
                            width: 80
                            color: distrowatchdelegate.ListView.isCurrentItem ? "white" : "black"//选中时字体为白色，未选中时为黑色
                            font {
                                family: "Helvetica"
                                pixelSize: 10
                            }
                        }

                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            text: today_hit
                            width: 25
                            color: distrowatchdelegate.ListView.isCurrentItem ? "white" : "black"//选中时字体为白色，未选中时为黑色
                            font {
                                family: "Helvetica"
                                pixelSize: 12
                            }
                        }
                        Image {
                            width: 7; height: 7
                            source: rank_img//"http://distrowatch.com/" + rank_img
                            anchors.verticalCenter: parent.verticalCenter
                        }

                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            text: yestoday_hit
                            width: 25
                            color: distrowatchdelegate.ListView.isCurrentItem ? "white" : "black"//选中时字体为白色，未选中时为黑色
                            font {
                                family: "Helvetica"
                                pixelSize: 12
                            }
                        }
                    }
                }
            }
            Common.ScrollArea {
                id: scrollArea
                frame:false
                anchors{
                    top:parent.top
                    topMargin: 1
                    left:parent.left
                    leftMargin: 1
                }
                height: parent.height-1
                width: parent.width-1
                Item {
                    id: distrowatchItem
                    width: parent.width
                    height: rightbar.distrowatch_num * 30 //列表长度
                    //垃圾清理显示内容
                    ListView{
                        id: distrowatchView
                        anchors.fill: parent
                        model:listModel
                        delegate: distrowatchdelegate
//                        highlight: Rectangle{width: 530;height: 30 ; color: "lightsteelblue"}
                        focus:true
                        spacing: 0
                    }
                }//Item
            }//ScrollArea
        }
    }

//    Column{//DistroWatch框
//        spacing: 5
//        width: parent.width
//        anchors {
//            top: splitbar.bottom
//            topMargin: 5
//            left: parent.left
//            leftMargin: 5
//        }

//        Text{
//            width: parent.width - 20
//            text: qsTr("DistroWatch Rank:")//DistroWatch国际排名：
//            font.bold:true
//            color: "#383838"
//            font.pointSize: 10
//        }

//        Rectangle{
//            width: parent.width-10; height: 210
//            clip:true
//            Component{
//                id:cdelegat
//                Item{
//                    id:wrapper
//                    width: parent.width-10; height: 30//220
//                    Row {
//                        anchors{
//                            verticalCenter: parent.verticalCenter
//                        }
//                        spacing: 5
//                        Text {
//                            width: 15
//                            anchors.verticalCenter: parent.verticalCenter
//                            text: rank
//                            color: cdelegat.ListView.isCurrentItem ? "white" : "black"//选中时字体为白色，未选中时为黑色
//                            font {
//                                family: "Helvetica"
//                                pixelSize: 12
//                            }
//                        }
//                        Image {
//                            id: icon
//                            width: 35; height: 30
////                            width: 90; height: 87
//                            source: "http://distrowatch.com/images/yvzhuwbpy/" + os_img +".png"
//                            anchors.verticalCenter: parent.verticalCenter
//                        }
//                        Text {
//                            anchors.verticalCenter: parent.verticalCenter
//                            text: os
//                            width: 80
//                            color: cdelegat.ListView.isCurrentItem ? "white" : "black"//选中时字体为白色，未选中时为黑色
//                            font {
//                                family: "Helvetica"
//                                pixelSize: 10
//                            }
//                        }

//                        Text {
//                            anchors.verticalCenter: parent.verticalCenter
//                            text: today_hit
//                            width: 25
//                            color: cdelegat.ListView.isCurrentItem ? "white" : "black"//选中时字体为白色，未选中时为黑色
//                            font {
//                                family: "Helvetica"
//                                pixelSize: 12
//                            }
//                        }
//                        Image {
//                            width: 7; height: 7
//                            source: "http://distrowatch.com/" + rank_img
//                            anchors.verticalCenter: parent.verticalCenter
//                        }

//                        Text {
//                            anchors.verticalCenter: parent.verticalCenter
//                            text: yestoday_hit
//                            width: 25
//                            color: cdelegat.ListView.isCurrentItem ? "white" : "black"//选中时字体为白色，未选中时为黑色
//                            font {
//                                family: "Helvetica"
//                                pixelSize: 12
//                            }
//                        }
//                    }
//                }
//            }
//            Common.ScrollArea {
//                frame:false
//                anchors{
//                    top:parent.top
//                    topMargin: 1
//                    left:parent.left
//                    leftMargin: 1
//                }
//                height: parent.height-1
//                width: parent.width-1
//                Item {
//                    width: parent.width
//                    height: rightbar.distrowatch_num * 30 //列表长度
//                    //垃圾清理显示内容
//                    ListView{
//                        anchors.fill: parent
//                        model:listModel
//                        delegate: cdelegat
////                        highlight: Rectangle{width: 530;height: 30 ; color: "lightsteelblue"}
//                        focus:true
//                    }
//                }//Item
//            }//ScrollArea
//        }
//    }


//    Column {
//        width: parent.width
//        height: 200
//        anchors {
//            top: splitbar.bottom
//            topMargin: 5
//            left: parent.left
//            leftMargin: 5
//        }
//        Item {
//            id: views
//            width: parent.width
//            GridView {
//                id: gridView
//                anchors.fill: parent
//                model: clearModel
//                delegate: ToolsDelegate {}
//                cellWidth: (parent.width-20)/3; cellHeight: cellWidth
//                cacheBuffer: 1000
//                focus: true
//            }
//        }
//    }


    Rectangle {
//    BorderImage {
        id: ukrect
        property bool showFlag: false
        color: "#e4f2fc"
//        source: "../../img/skin/bg-right.png"
        width: showFlag ? parent.width-4 : 0
        height: 350//scrollArea.height + 40
        anchors{
            right: parent.right
            rightMargin: 2
//            top: splitbar.bottom
            top: parent.top
            topMargin: 100
        }
        Behavior on width { NumberAnimation { easing.type: Easing.OutSine ; duration: 250 } }

        Component.onCompleted: {
            //set default value
            sessiondispatcher.get_default_ubuntukylin_distrowatch();
            lastupdateText.text = sessiondispatcher.getDistrowatchSingleInfo("lastupdate");
            ostypeText.text = sessiondispatcher.getDistrowatchSingleInfo("ostype");
            basedonText.text = sessiondispatcher.getDistrowatchSingleInfo("basedon");
            originText.text = rightbar.transTitle(sessiondispatcher.getDistrowatchSingleInfo("origin"));
            architectureText.text = sessiondispatcher.getDistrowatchSingleInfo("architecture");
            desktopText.text = sessiondispatcher.getDistrowatchSingleInfo("desktop");
            categoryText.text = sessiondispatcher.getDistrowatchSingleInfo("category");
            statusText.text = rightbar.transTitle(sessiondispatcher.getDistrowatchSingleInfo("status"));
            var popularity = sessiondispatcher.getDistrowatchSingleInfo("popularity");
            var popularityList=  popularity.split("(");
            popularityText.text = popularityList[0] + "( " + qsTr("Hits per day ") + popularityList[1] + " )";//每日点击次数

            // set new data
            var result = sessiondispatcher.get_ubuntukylin_distrowatch_info_qt();
            if (result) {
                lastupdateText.text = sessiondispatcher.getDistrowatchSingleInfo("lastupdate");
                ostypeText.text = sessiondispatcher.getDistrowatchSingleInfo("ostype");
                basedonText.text = sessiondispatcher.getDistrowatchSingleInfo("basedon");
                originText.text = rightbar.transTitle(sessiondispatcher.getDistrowatchSingleInfo("origin"));
                architectureText.text = sessiondispatcher.getDistrowatchSingleInfo("architecture");
                desktopText.text = sessiondispatcher.getDistrowatchSingleInfo("desktop");
                categoryText.text = sessiondispatcher.getDistrowatchSingleInfo("category");
                statusText.text = rightbar.transTitle(sessiondispatcher.getDistrowatchSingleInfo("status"));
                var popularity = sessiondispatcher.getDistrowatchSingleInfo("popularity");
                var popularityList=  popularity.split("(");
                popularityText.text = popularityList[0] + "( " + qsTr("Hits per day ") + popularityList[1] + " )";//每日点击次数
            }
        }

        Image {
            id: ukIcon
            visible: ukrect.showFlag
            width: 90; height: 87
            source: "../../img/distrowatch/ubuntukylin.png"    //"http://distrowatch.com/images/yvzhuwbpy/ubuntukylin.png"
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Text {
            id: hideText
            visible: false
            text: qsTr("Hide")//隐藏
        }
        Common.ColorButton {
            id: hideBtn
            visible: ukrect.showFlag
            anchors {
                top: parent.top
                topMargin: 2
                right: parent.right
                rightMargin: 2
            }
            colorNormal: "#00a0e9"
            colorHover: "#65cfff"
            colorPressed: "#65cfff"
            sizeNormal: 10
            sizeHover: 12
            sizePressed: 12
            height: 20
            wordname: qsTr("Hide"); width: hideText.width
            onClicked: {
                ukrect.showFlag = false;
            }
        }
        Column {
            anchors {
                left: parent.left
                leftMargin: 5
                top: ukIcon.bottom
                topMargin: 15
            }
            spacing: 10
            Row {
                spacing: 5
                Common.Label {
                    text: qsTr("Last Update:")//最后更新：
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: 12
                    color: "#383838"
                    width: 90
                }
                Text {
                    id: lastupdateText
                    anchors.verticalCenter: parent.verticalCenter
                    width: 140
                    elide: Text.ElideRight
//                    clip: true
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 5
                Common.Label {
                    text: qsTr("OS Type:")//发行归类：
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: 12
                    color: "#383838"
                    width: 90
                }
                Text {
                    id: ostypeText
                    anchors.verticalCenter: parent.verticalCenter
                    width: 160
                    elide: Text.ElideRight
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 5
                Common.Label {
                    text: qsTr("Based on:")//基于何种发行：
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: 12
                    color: "#383838"
                    width: 90
                }
                Text {
                    id: basedonText
                    anchors.verticalCenter: parent.verticalCenter
                    width: 160
                    elide: Text.ElideRight
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 5
                Common.Label {
                    text: qsTr("Origin: ")//来源：
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: 12
                    color: "#383838"
                    width: 90
                }
                Text {
                    id: originText
                    anchors.verticalCenter: parent.verticalCenter
                    width: 160
                    elide: Text.ElideRight
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 5
                Common.Label {
                    text: qsTr("Architecture:")//处理器架构：
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: 12
                    color: "#383838"
                    width: 90
                }
                Text {
                    id: architectureText
                    anchors.verticalCenter: parent.verticalCenter
                    width: 160
                    elide: Text.ElideRight
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }

            Row {
                spacing: 5
                Common.Label {
                    text: qsTr("Desktop:")//桌面：
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: 12
                    color: "#383838"
                    width: 90
                }
                Text {
                    id: desktopText
                    anchors.verticalCenter: parent.verticalCenter
                    width: 160
                    elide: Text.ElideRight
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }

            Row {
                spacing: 5
                Common.Label {
                    text: qsTr("Category:")//类型：
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: 12
                    color: "#383838"
                    width: 90
                }
                Text {
                    id: categoryText
                    anchors.verticalCenter: parent.verticalCenter
                    width: 160
                    elide: Text.ElideRight
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 5
                Common.Label {
                    text: qsTr("Status:")//状态：
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: 12
                    color: "#383838"
                    width: 90
                }
                Text {
                    id: statusText
                    anchors.verticalCenter: parent.verticalCenter
                    width: 160
                    elide: Text.ElideRight
                    font.pixelSize: 12
                    color: "#65cfff"
                }
            }
            Row {
                spacing: 5
                Common.Label {
                    text: qsTr("Popularity:")//受欢迎程度排名：
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: 12
                    color: "#383838"
                    width: 90
                }
                Text {
                    id: popularityText
                    anchors.verticalCenter: parent.verticalCenter
                    width: 140
                    elide: Text.ElideRight
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }
        }
    }

    Common.Separator {
        anchors {
            left: parent.left
            leftMargin: 2
            top: distrowatchColumn.bottom
            topMargin: 3
        }
        width: parent.width - 4
    }

    Row {
        id: versionrow
        spacing: 25
        anchors {
            bottom: parent.bottom
            bottomMargin: 3
            left: parent.left
            leftMargin: 20
        }

        Common.StyleButton {
            id: helplabel
            wordname: qsTr("Forum Help")//论坛求助
            width: 50
            height: 25
            onClicked: {
                Qt.openUrlExternally("http://www.ubuntukylin.com/ukylin/forum.php");
            }
        }
//        Text {
//            id: helplabel
//            width: 50
//            height: 25
//            textFormat: Text.RichText
//            text:  qsTr("<a href=\"http://www.ubuntukylin.com/ukylin/forum.php\">Forum Help</a>")
//            onLinkActivated: { Qt.openUrlExternally(link); }
//        }
        Common.StyleButton {
            id: versionlabel
            wordname: qsTr("Features")//新版本特性
            width: 60
            height: 25
            onClicked: {
                sessiondispatcher.showFeatureDialog();
            }
        }
        Common.StyleButton {
            id: buglabel
            wordname: qsTr("Feedback")//问题反馈
            width: 40
            height: 25
            onClicked: {
                Qt.openUrlExternally("https://bugs.launchpad.net/youker-assistant");
            }
        }
    }

    states: [
        State {
            name: "OnLine"
            PropertyChanges { target: online; x: 0 }
            PropertyChanges { target: offline; x: (parent.width * 1.5) }
            PropertyChanges { target: logining; x: (parent.width * 1.5) }
        },
        State {
            name: "Logining"
            PropertyChanges { target: logining; x: 0 }
            PropertyChanges { target: online; x: (parent.width * 1.5) }
            PropertyChanges { target: offline; x: (parent.width * 1.5) }
        },
        State {
            name: "OffLine"
            PropertyChanges { target: offline; x: 0 }
            PropertyChanges { target: online; x: (parent.width * 1.5) }
            PropertyChanges { target: logining; x: (parent.width * 1.5) }
        }
    ]
}
