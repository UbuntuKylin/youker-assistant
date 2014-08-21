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

//右边栏
Rectangle {
    id: rightbar

    property int distrowatch_num:0
    property string update_rate



    property string activetext : qsTr("Active")//活跃发展中
    property string country : qsTr("China")//中国

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

    //更新列表
//    function updateList() {
//        clearModel.clear();//清空
//        clearModel.append({"icon": "../../img/icons/checkscreen.png", "name": qsTr("DeadpixelTest"), "flag": "CheckScreen"});//坏点检测
//        clearModel.append({"icon": "../../img/icons/iconbeauty.png", "name": qsTr("DesktopIcon"), "flag": "Desktopicon"});//桌面图标
//        clearModel.append({"icon": "../../img/icons/bootanimation.png", "name": qsTr("BootAnimation"), "flag": "BootAnimation"});//开机动画
//        clearModel.append({"icon": "../../img/icons/camera.png", "name": qsTr("Camera"), "flag": "CameraCapture"});//摄像头
//        clearModel.append({"icon": "../../img/icons/mouse.png", "name": qsTr("MousePointer"), "flag": "MousePointer"});//鼠标指针
//        clearModel.append({"icon": "../../img/icons/touchpad.png", "name": qsTr("Touchpad"), "flag": "TouchpadSet"});//触摸板
//    }

    function addList() {
        var result = sessiondispatcher.get_distrowatch_info_qt();
//        console.log(result);
        /*6+openSUSE+opensuse+1141+images/other/adown.png+1142,7+Arch+arch+1100+images/other/adown.png+1101,8+elementary+elementary+1061+images/other/aup.png+1060,9+Zorin+zorin+1018+images/other/aup.png+1016,10+CentOS+centos+906+images/other/aup.png+904,11+Puppy+puppy+804+images/other/aup.png+802,12+Lubuntu+lubuntu+795+images/other/aup.png+794,13+Manjaro+manjaro+742+images/other/adown.png+743,14+Kali+kali+699+images/other/adown.png+700,15+LXLE+lxle+688+images/other/adown.png+690,16+Bodhi+bodhi+663+images/other/aup.png+662,17+PCLinuxOS+pclinuxos+657+images/other/aup.png+650,18+Xubuntu+xubuntu+612+images/other/adown.png+613,19+CrunchBang+crunchbang+578+images/other/adown.png+579,20+Ultimate+ultimate+572+images/other/alevel.png+572,21+Android-x86+androidx86+565+images/other/adown.png+573,22+FreeBSD+freebsd+558+images/other/adown.png+560,23+Robolinux+robolinux+537+images/other/aup.png+533,24+SparkyLinux+sparkylinux+526+images/other/adown.png+527,25+Simplicity+simplicity+507+images/other/alevel.png+507,26+Tails+tails+500+images/other/alevel.png+500,27+Red Hat+redhat+486+images/other/alevel.png+486,28+Deepin+deepin+465+images/other/alevel.png+465,29+Slackware+slackware+437+images/other/alevel.png+437,30+Ubuntu GNOME+ubuntugnome+433+images/other/alevel.png+433,31+Lite+lite+416+images/other/alevel.png+416,32+SteamOS+steamos+411+images/other/alevel.png+411,33+Kubuntu+kubuntu+402+images/other/alevel.png+402,34+OpenMandriva+openmandriva+394+images/other/adown.png+395,35+GhostBSD+ghostbsd+386+images/other/alevel.png+386,36+antiX+antix+383+images/other/alevel.png+383,37+Pinguy+pinguy+381+images/other/alevel.png+381,38+SmartOS+smartos+374+images/other/alevel.png+374,39+Salix+salix+372+images/other/alevel.png+372,40+Sabayon+sabayon+361+images/other/alevel.png+361,41+SolydXK+solydxk+357+images/other/adown.png+358,42+Tiny Core+tinycore+353+images/other/alevel.png+353,43+Peppermint+peppermint+345+images/other/alevel.png+345,44+KNOPPIX+knoppix+344+images/other/alevel.png+344,45+MakuluLinux+makululinux+325+images/other/adown.png+327,46+wattOS+wattos+324+images/other/alevel.png+324,47+PC-BSD+pcbsd+317+images/other/adown.png+318,48+Antergos+antergos+308+images/other/alevel.png+308,49+Netrunner+netrunner+307+images/other/aup.png+306,50+Chakra+chakra+304+images/other/alevel.png+304,51+NixOS+nixos+299+images/other/adown.png+307,52+Gentoo+gentoo+295+images/other/adown.png+296,53+Ubuntu Studio+ubuntustudio+276+images/other/alevel.png+276,54+Voyager+voyager+274+images/other/alevel.png+274,55+OpenELEC+openelec+274+images/other/alevel.png+274,56+Clonezilla+clonezilla+272+images/other/alevel.png+272,57+Scientific+scientific+270+images/other/aup.png+268,58+Elive+elive+261+images/other/aup.png+259,59+SliTaz+slitaz+254+images/other/adown.png+260,60+KaOS+kaos+249+images/other/aup.png+243,61+GoboLinux+gobolinux+249+images/other/alevel.png+249,62+Vector+vector+244+images/other/alevel.png+244,63+Oracle+oracle+239+images/other/alevel.png+239,64+DragonFly+dragonfly+237+images/other/alevel.png+237,65+Porteus+porteus+231+images/other/adown.png+232,66+ClearOS+clearos+224+images/other/alevel.png+224,67+Alpine+alpine+222+images/other/alevel.png+222,68+Mandriva+mandriva+220+images/other/alevel.png+220,69+GParted+gparted+213+images/other/alevel.png+213,70+siduction+siduction+212+images/other/alevel.png+212,71+Ubuntu Kylin+ubuntukylin+211+images/other/alevel.png+211,72+Tanglu+tanglu+207+images/other/adown.png+211,73+Damn Small+damnsmall+201+images/other/alevel.png+201,74+Slackel+slackel+200+images/other/adown.png+203,75+Zenwalk+zenwalk+198+images/other/adown.png+201,76+Kwheezy+kwheezy+196+images/other/alevel.png+196,77+ArchBang+archbang+193+images/other/adown.png+194,78+4MLinux+4mlinux+193+images/other/aup.png+192,79+Parsix+parsix+192+images/other/aup.png+183,80+AV Linux+avlinux+189+images/other/alevel.png+189,81+Zentyal+zentyal+186+images/other/alevel.png+186,82+OpenBSD+openbsd+186+images/other/alevel.png+186,83+Trisquel+trisquel+184+images/other/alevel.png+184,84+ReactOS+reactos+183+images/other/adown.png+184,85+BackBox+backbox+182+images/other/alevel.png+182,86+Point+point+179+images/other/alevel.png+179,87+Wifislax+wifislax+178+images/other/alevel.png+178,88+FreeNAS+freenas+175+images/other/adown.png+176,89+Musix+musix+173+images/other/alevel.png+173,90+ZevenOS+zevenos+172+images/other/alevel.png+172,91+MEPIS+mepis+168+images/other/adown.png+169,92+Bridge+bridge+167+images/other/adown.png+191,93+DreamStudio+dreamstudio+166+images/other/alevel.png+166,94+Solaris+solaris+165+images/other/alevel.png+165,95+SUSE+suse+165+images/other/alevel.png+165,96+ROSA+rosa+158+images/other/alevel.png+158,97+Legacy+legacy+157+images/other/alevel.png+157,98+Emmabuntüs+emmabuntüs+157+images/other/aup.png+156,99+Korora+korora+155+images/other/alevel.png+155,100+Greenie+greenie+154+images/other/alevel.png+154*/
        rightbar.distrowatch_num = result.length;
        listModel.clear();//清空
        for(var i=0; i < result.length; i++) {
            var splitlist = result[i].split("+");
            var os_image = "";
            if (splitlist[2] == "opensuse") {
                os_image = "suse";
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
            else {
                os_image = splitlist[2];
            }
            listModel.append({"rank": splitlist[0], "os": splitlist[1], "os_img": os_image, "today_hit": splitlist[3], "rank_img": splitlist[4],  "yestoday_hit": splitlist[5]});
        }
    }

//    ListModel {
//        id: clearModel
//        Component.onCompleted: {
//            rightbar.updateList();
//        }
//    }

    ListModel {
        id: listModel
        Component.onCompleted: {
            rightbar.update_rate = sessiondispatcher.get_distrowatch_url_qt();
            rightbar.addList();
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
            width: parent.width-10; height: 210
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
                            color: distrowatchdelegate.ListView.isCurrentItem ? "white" : "black"//选中时字体为白色，未选中时为黑色
                            font {
                                family: "Helvetica"
                                pixelSize: 12
                            }
                        }
                        Image {
                            id: icon
                            width: 28; height: 28
//                            width: 90; height: 87
                            source: "http://distrowatch.com/images/yvzhuwbpy/" + os_img +".png"
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
                            source: "http://distrowatch.com/" + rank_img
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
            sessiondispatcher.get_ubuntukylin_distrowatch_info_qt();
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

        Image {
            id: ukIcon
            visible: ukrect.showFlag
            width: 90; height: 87
            source: "http://distrowatch.com/images/yvzhuwbpy/ubuntukylin.png"
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
