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
    id: tabWidget
    default property alias content: stack.children //将tab页集合设置一个默认属性
    property int current: 0
    onCurrentChanged: setOpacities()
    Component.onCompleted: setOpacities()
    function setOpacities() {
        for(var i = 0; i < content.length; ++i) {
            content[i].opacity = (i == current ? 1 : 0);//将当前的tab设置为非透明,其余透明
        }
    }
    Row {  //此组件为tab选项
        id: header
        anchors{
            left:parent.left
//            leftMargin: 5
        }

        Repeater {
            model: content.length
            delegate: Rectangle {
                id: mytab
//                width: 165//165每个tab标题的总宽度
//                width: 140//140每个tab标题的总宽度
//                height: 36
                width: 142
                height: 36
                color:"transparent"
                Rectangle{
                    anchors{
                        bottom: parent.bottom
                        horizontalCenter: parent.horizontalCenter
                    }
//                    width: 160//160每个tab标题的宽度，其中：每个tab标题的总宽度-每个tab标题的宽度 = 165 - 160 = 5,即为tab之间的space
//                    width: 135//135每个tab标题的宽度，其中：每个tab标题的总宽度-每个tab标题的宽度 = 140 - 130 = 5,即为tab之间的space
//                    height: 30
                    width: 142
                    height: 36
//                    border.color: "#abc2c2"
                    Image {
                        anchors.fill: parent
//                        anchors.leftMargin: 0.5
//                        anchors.rightMargin: 0.5
//                        source: "../../img/icons/tab.png"
                        source: "../../img/icons/tab-background.png"
                    }
                    Image {
                        id: btnImg
                        anchors.fill: parent
                        source: ""
                    }
                    Rectangle {
                        width: mytab.width//parent.width
                        height: 1
                        anchors.bottom: parent.bottom
                        color: "#abc2c2"
                    }
                    BorderImage {  //tab选项图片
                        anchors { fill: parent/*; leftMargin: 0.5; topMargin: 0; rightMargin: 0.5*/}
//                        source: tabWidget.current == index? "../../img/icons/tab-active.png" : ""
                        source: tabWidget.current == index? "../../img/icons/tab-current.png" : ""
                    }
                    Text {
                        horizontalAlignment: "AlignHCenter"; verticalAlignment: "AlignVCenter"
                        anchors.fill: parent
                        text: content[index].title
                        font.pointSize: 10
                        elide: Text.ElideRight
                        font.bold: tabWidget.current == index
                    }
//                    MouseArea {
//                        anchors.fill: parent
//                        onClicked: tabWidget.current = index  //存储当前选中tab页
//                    }
                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        onEntered: {
                            btnImg.source = "../../img/icons/tab-hover.png";
                        }
                        onPressed: {
                            btnImg.source = "../../img/icons/tab-hover.png";
                        }
                        //要判断松开是鼠标位置
                        onReleased: {
                            btnImg.source = "../../img/icons/tab-hover.png";
                        }
                        onExited: {
                            btnImg.source = "";
                        }
                        onClicked: tabWidget.current = index  //存储当前选中tab页
                    }
                }
                Image {
                    source: "../../img/icons/tab-split-line.png"
                }
            }
        }
    }
    Item {  //tab页
        id: stack
        width: tabWidget.width
        anchors.top: header.bottom
        anchors.bottom: tabWidget.bottom
    }
}
