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
//import RegisterMyType 0.1
//import SessionType 0.1
import SystemType 0.1
import QtDesktop 0.1
import "../common" as Common

Rectangle {
    id: bootimagepage
    property bool on: true
    width: parent.width
    height: 475
    property string fontName: "Helvetica"
    property int fontSize: 12
    property color fontColor: "black"
//    property SessionDispatcher dis: sessiondispatcher
    property SystemDispatcher dis: systemdispatcher
    property string image_path: ""
    property string actiontitle: "开机动画设置"
    property string actiontext: "点击“自定义图片”按钮选择您需要添加到列表中的图片，在列表中选中您要设置的图片名称，点击“确定”按钮完成设置。"
    property int num: 0
    property string selectedimage: ""
    //背景
    Image {
        source: "../../img/skin/bg-left.png"
        anchors.fill: parent
    }
    Component.onCompleted: {
        systemdispatcher.plymouth_init_check_qt();


        var plymouth_list = systemdispatcher.get_existing_plymouth_list_qt();
        bootimagepage.num = plymouth_list.length;
        mainModel.clear();
        for(var i=0; i < plymouth_list.length; i++) {
            mainModel.append({"itemTitle": plymouth_list[i]});
        }
        bootimagepage.selectedimage = plymouth_list[0];
    }

    //信号绑定，绑定qt的信号finishCleanWork，该信号emit时触发onFinishCleanWork
    Connections
    {
        target: systemdispatcher
        onAddBootImage: {
            systemdispatcher.plymouth_init_check_qt();
            var plymouth_list = systemdispatcher.get_existing_plymouth_list_qt();
            console.log("abaababab.........");
//            console.log(plymouth_list);
            bootimagepage.num = plymouth_list.length;
            console.log(bootimagepage.num);
            mainModel.clear();
            for(var i=0; i < plymouth_list.length; i++) {
                mainModel.append({"itemTitle": plymouth_list[i]});
            }
            bootimagepage.selectedimage = plymouth_list[0];
        }
    }



    Connections {
        target: toolBar
        //按下确定按钮
        onOkBtnClicked: {
            if (settigsDetails.setTitle == "BootAnimation") {
                console.log(bootimagepage.selectedimage);
                systemdispatcher.custom_plymouth_bg_qt(bootimagepage.selectedimage);
            }
        }

    }
    Column {
        spacing: 10
        anchors.top: parent.top
        anchors.topMargin: 44
        anchors.left: parent.left
        anchors.leftMargin: 80
        Text {
             text: bootimagepage.actiontitle
             font.bold: true
             font.pixelSize: 14
             color: "#383838"
         }
         Text {
             text: bootimagepage.actiontext
             font.pixelSize: 12
             color: "#7a7a7a"
         }
    }

    Column {
        anchors {
            top: parent.top
            topMargin: 120
            left: parent.left
            leftMargin: 60
        }
        spacing: 30
        Image {
            id: previewzone
            source: "../../img/icons/previewzone.png"
        }
        Common.Button {
            width: 134
            height: 35
            hoverimage: "selectpic.png"
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                bootimagepage.image_path = systemdispatcher.show_file_dialog("bootanimation");
                bootimage.source = bootimagepage.image_path;
                var imagename = bootimagepage.image_path;
                imagename = imagename.substr(imagename.lastIndexOf("/") + 1, imagename.length - imagename.lastIndexOf("/"));
                systemdispatcher.add_new_plymouth_qt(bootimagepage.image_path, imagename);
                systemdispatcher.send_boot_signal();
            }
        }
    }

    Image {
        id: bootimage
        width: 165
        height: 114
//        width: 180
//        height: 125
        anchors {
            top: parent.top
            topMargin: 136
            left: parent.left
            leftMargin: 73
        }
//        fillMode: Image.TileHorizontally
        source: ""
        smooth: true
    }

    Text {
        id: chooselabel
        anchors {
            top: parent.top
            topMargin: 120
            left: bootimage.right
            leftMargin: 100
        }
        text: "可选开机动画"
        font.bold: true
        font.pixelSize: 14
        color: "#383838"
    }

    ListModel {
        id: mainModel
        ListElement {
            itemTitle: ""
        }
    }


    Rectangle{
        border.color: "#b9c5cc"
        width: 460; height: 250
        clip:true
        anchors {
            top: chooselabel.bottom
            topMargin: 5
            left: bootimage.right
            leftMargin: 100
        }
        Component{
            id:cdelegat
            Item{
                id:wrapper
                width: 460; height: 30
                Text{
                    id:listtext
                    anchors {
                        left: parent.left
                        leftMargin: 10
                        verticalCenter: parent.verticalCenter
                    }
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    text:itemTitle
                }
                Image {
                    id: btnImg
                    anchors.fill: parent
                    source: ""
                }
                MouseArea{
                    anchors.fill:parent
                    hoverEnabled: true
                    onClicked: {
                        wrapper.ListView.view.currentIndex = index;
                        bootimagepage.selectedimage = itemTitle;
                    }
                }

            }
        }
        ListView{
            id:lisv
            anchors.fill: parent
            model: mainModel
            delegate: cdelegat
            highlight: Rectangle{width: 530;height: 30 ; color: "lightsteelblue"}
            focus:true
        }

        Rectangle{
            id:scrollbar
            anchors.right: parent.right
            anchors.rightMargin: 8
            height: parent.height
            width:5
            color: "lightgrey"
        }
        Rectangle{
            id: button
            anchors.right: parent.right
            anchors.rightMargin: 5
            width: 12
            y: lisv.visibleArea.yPosition * scrollbar.height
            height: lisv.visibleArea.heightRatio * scrollbar.height;
            radius: 3
            smooth: true
            color: "white"
            border.color: "lightgrey"
            Column{
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 2
                Rectangle{
                    width: 8;height: 1
                    color: "lightgrey"
                }
                Rectangle{
                    width: 8;height: 1
                    color: "lightgrey"
                }
                Rectangle{
                    width: 8;height: 1
                    color: "lightgrey"
                }
            }
            MouseArea {
                id: mousearea
                anchors.fill: button
                drag.target: button
                drag.axis: Drag.YAxis
                drag.minimumY: 0
                drag.maximumY: scrollbar.height - button.height
                onMouseYChanged: {
                    lisv.contentY = button.y / scrollbar.height * lisv.contentHeight
                }
            }
        }
    }



//    ScrollArea {
////        frame:false
//        width: 400
//        height: 200
//        anchors {
////            top: parent.top
////            topMargin: 166
//            top: chooselabel.bottom
//            topMargin: 5
//            left: bootimage.right
//            leftMargin: 100
//        }

//        Item {
//            id: subItemsRect
//            property int itemHeight: 40
//            width: 380
//            //当高度需要扩展时,根据expandedItemCount数目和itemHeight高度去扩展
//            height: bootimagepage.num * itemHeight
//            clip: true
//            opacity: 1
//            Behavior on height {
//                SequentialAnimation {
//                    NumberAnimation { duration: 100; easing.type: Easing.InOutQuad }
//                }
//            }
////            ListView {
////                id: listView
////                height: parent.height
////                model: mainModel
////                delegate:
////                    Text {
////                        text: itemTitle
////                    }

//////                cacheBuffer: 1000
////                opacity: 1
////                spacing: 10
////                snapMode: ListView.NoSnap
////                boundsBehavior: Flickable.DragOverBounds
////                currentIndex: 0
////                preferredHighlightBegin: 0
////                preferredHighlightEnd: preferredHighlightBegin
////                highlightRangeMode: ListView.StrictlyEnforceRange
////            }

//            Column {
//                width: parent.width
//                Repeater {
//                    id: subItemRepeater
//                    model: mainModel
//                    width: parent.width
//                    Common.NameListItem {
//                        id: subListItem
//                        height: subItemsRect.itemHeight
////                        width: parent.width
//                        text: itemTitle
//                        bgImage: ""
//                        onClicked: {}
//                    }
//                }//Repeater
//            }//Column
//        }//子项Item
//    }//ScrollArea
}



//Rectangle {
//    id: lancherpage
//    property bool on: true
//    width: parent.width
//    height: 460
//    property Dispatcher dis: mydispather
//    Column {
//        spacing: 20
//        anchors.top: parent.top
//        anchors.topMargin: 30
//        anchors.left: parent.left
//        anchors.leftMargin: 30

//        Row {
//            Label {
//                id: hidelabel
//                width: 110
//                text: qsTr("自动隐藏:")
//            }
//            CheckBox {
//                id: enabledCheck
//                text: qsTr("开启")
//                checked: false
//                onCheckedChanged: {}
//                onClicked: {
////                    enabledCheck.checked = !enabledCheck.checked;
////                    if (enabledCheck.checked == true) {
//////                        enabledCheck.checked = false;
////                        enabledCheck.text = qsTr("关闭");
////                    }
////                    else if (enabledCheck.checked == false){
//////                        enabledCheck.checked = true;
////                        enabledCheck.text = qsTr("开启");
////                    }
//                }
//            }

////            Common.Switch {
////                id: themeSwitch
////                anchors.right: parent.right
////                height: parent.height
////                spacing: 8
////                textOn: qsTr("On")
////                textOff: qsTr("Off")
////                fontColor: "#666666"
////                onSwitched: lancherpage.on = position
//////                id: switchLauncher
////////                checked: false
//////                x: 130
////////                onClicked: {
////////                    //kobe: wait for adding function
////////                    mydispather.set_launcher(switchLauncher.checked)
////////                }
////            }
//        }

//        Row {
//            Label {
//                id: sizelabel
//                width: 110
//                text: qsTr("图标大小:")
//            }
//            Slider {
//                id: slider
//                x: 130
////                function formatValue(v) { return v.toFixed(2) }
//                minimumValue: 0
//                maximumValue: 100
//                value: 0
////                live: true
////                onTouched: {
////                    console.log(slider.value)
////                }
//            }
//        }

//        Row {
//            Label {
//                id: locationlabel
//                width: 110
//                text: qsTr("位置:")
//            }
//            RadioButton {
//                id: radioleft
//                x: 130
////                text: "靠左"
//            }
//        }

//        Row {
//            Label {
//                id: inputlabel1
//                width: 110
//                text: qsTr("输入用户名:")
//            }
//            TextField {
//                id: textfield1
//                placeholderText: qsTr("put your username")
//                echoMode: TextInput.Normal
////                hasClearButton: true
//                width: 200
//                onTextChanged: {
//                    //kobe: wait for adding function
//                    console.log(textfield1.text)
//                }
//            }
//        }

//        Row {
//            Label {
//                id: inputlabel2
//                width: 110
//                text: qsTr("输入密码:")
//            }
//            TextField {
//                id: textfield2
//                placeholderText: qsTr("put your password")
////                hasClearButton: true
//                echoMode: TextInput.Password
//                width: 200
//                onTextChanged: {
//                    //kobe: wait for adding function
//                    console.log(textfield2.text)
//                }

//            }
//        }

//        Row {
//            Label {
//                id: progresslabel
//                width: 110
//                text: qsTr("进度显示:")
//            }
//            ProgressBar {
//                id: progressbar
////                indeterminate: true
//                value: 24
//                minimumValue: 0
//                maximumValue: 100

//            }
//        }

//        Row {
//            Label {
//                id: modelabel
//                width: 110
//                text: qsTr("模式:")
//            }
//            ComboBox {
//                id: combobox
//                x: 110
////                titel1: "111111111"
////                titel2: "222222222"
////                titel3: "333333333"
////                flags: "launcher"
//            }

//        }
//    }
//}