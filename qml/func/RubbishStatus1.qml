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
//import QtGraphicalEffects 1.0
//import Ubuntu.Components 0.1
//import Ubuntu.Components.ListItems 0.1 as ListItem
//import Ubuntu.Components.Popups 0.1
import QtDesktop 0.1
import RegisterMyType 0.1


Item {
    id: tile
    width: parent.width
    property real detailsOpacity : 0
    property string trans_flags: flags //把flags标记传递给RubbishStatusDetails
//    property string title1: "清理垃圾"
//    property string title2: "清理系统垃圾，让系统运行跟流畅"
//    property string icon_source: "../img/icons/user.png"
    property Dispatcher dis: mydispather
    Rectangle {
        id: tileRect
        height: status_update_content.height + detailsWrapper.height
        width: parent.width// - units.gu(1)
//        color: detailsOpacity > 0 ? "#f8f8f8" : "white"
        anchors.right: parent.right


        CheckBox {
            id: checkbox
            checked: true
            anchors {
                left: parent.left
//                top: parent.top
                leftMargin: units.gu(1)
                verticalCenter: parent.verticalCenter
//                topMargin: units.gu(1)
            }
            onCheckedChanged: {
                //kobe: wait for adding function
            }
        }

        //kobe:logo图像
        Image {
            id: avatarImage
            source: Qt.resolvedUrl(picture)
            height: 47
            width: 47
            anchors {
                left: checkbox.right
                top: parent.top
                leftMargin: 10
//                topMargin: units.gu(1)
            }
            asynchronous: true
            smooth: true
            fillMode: Image.PreserveAspectCrop
//            sourceSize.width: units.dp(48)
            onStatusChanged: {
            }
        }

//        UbuntuShape {
//            id: avatarImage
//            height: units.dp(48)
//            width: units.dp(48)
//            anchors {
//                left: checkbox.right
//                top: parent.top
//                leftMargin: units.gu(1)
////                topMargin: units.gu(1)
//            }

            //kobe:logo图像
//            image: Image {
//                source: Qt.resolvedUrl(picture)
//                asynchronous: true
//                smooth: true
//                fillMode: Image.PreserveAspectCrop
//                sourceSize.width: units.dp(48)
//                onStatusChanged: {
//                }
//            }
//        }

        Item {
            id: status_update_content
            anchors {
                left: avatarImage.right
                right: parent.right
                top: parent.top
//                topMargin: units.gu(1)
                //leftMargin: units.gu(1)
                bottomMargin: units.gu(1)
                //rightMargin: units.gu(1)
            }
            height: childrenRect.height
            MouseArea {
                anchors.fill: status_update_content
                onClicked: {
//                    console.log(flags);
//                    console.log(trans_flags);
//                    mydispather.set_str(trans_flags);
                    if (tile.state != 'Details') {
                        tile.state = 'Details';

                    } else {
                        tile.state = 'List';
                    }
                }
            }
            Column {
                spacing: units.gu(1)
                anchors {
                    left: parent.left;
                    right: parent.right
                    bottomMargin: units.gu(2)
                }
                Label {
                    text: title
//                    fontSize: "medium"
                    font.bold: true
                    width: parent.width
                }
                Label {
                    id: messageText
                    text: detailstr
                    maximumLineCount: tile.state != 'Details' ? 10 : 0
                    elide: Text.ElideRight
                    visible: true
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    width: parent.width - units.gu(3)
                    textFormat: Text.StyledText
//                    linkColor: "gray"
//                    onLinkActivated: Qt.openUrlExternally(link)
                }
            }
        }

        Item {
            id: detailsWrapper
            height: detailsLoader.height + units.gu(1)
            width: parent.width
            opacity: detailsOpacity
            visible:  detailsOpacity > 0 ? true : false
            anchors {
                top: status_update_content.bottom
                left: parent.left
                right: parent.right
            }
            Loader {
                id: detailsLoader
                width: parent.width
                visible: true
            }
            onVisibleChanged: {
                if (visible && detailsLoader.state != Loader.Ready) {
                    tile.trans_flags = flags;
                    detailsLoader.source = "RubbishStatusDetails.qml";
                }
            }

        }
    }

//    DropShadow {
//        id: tileShadow
//        anchors.fill: tileRect
//        horizontalOffset: 3
//        verticalOffset: 3
//        radius: 8.0
//        samples: 16
//        cached: true
//        fast: true
//        color: "#f0f0f0"
//        source: tileRect
//    }

    states: [State {
                name: "Details"
                PropertyChanges { target: tile; detailsOpacity: 1; x: 0 }
                StateChangeScript {
                    script: {
                        listView.positionViewAtIndex(listView.indexAt(tile.x, tile.y), ListView.Contain);
                    }
                }
            },
            State {
                name: "List"
                PropertyChanges { target: tile; detailsOpacity: 0; x: 0 }
            }]

    transitions: Transition {
        NumberAnimation {
            duration: 300; properties: "detailsOpacity,x,height,width"
        }
    }
}









//Item {
//    id: tile
//    width: parent.width
//    anchors {
//        topMargin: units.gu(1)
////        leftMargin: units.gu(1)
//        bottomMargin: units.gu(1)
////        rightMargin: units.gu(1)
//    }

//    property real detailsOpacity : 0
//    property string trans_flags: flags //把flags标记传递给RubbishStatusDetails
////    property string title1: "清理垃圾"
////    property string title2: "清理系统垃圾，让系统运行跟流畅"
////    property string icon_source: "../img/icons/user.png"
//    property Dispatcher dis: mydispather
//    Rectangle {
//        id: tileRect
//        height: status_update_content.height + detailsWrapper.height
//        width: parent.width// - units.gu(1)
//        color: detailsOpacity > 0 ? "#f8f8f8" : "white"
//        anchors.right: parent.right

//        CheckBox {
//            id: checkbox
//            checked: true
//            anchors {
//                left: parent.left
//                top: parent.top
//                leftMargin: units.gu(1)
//                topMargin: units.gu(1)
//            }
//            onCheckedChanged: {
//                //kobe: wait for adding function
//            }
//        }

//        UbuntuShape {
//            id: avatarImage
//            height: units.dp(48)
//            width: units.dp(48)
//            anchors {
//                left: checkbox.right
//                top: parent.top
//                leftMargin: units.gu(1)
////                topMargin: units.gu(1)
//            }

//            //kobe:logo图像
//            image: Image {
//                source: Qt.resolvedUrl(picture)
//                asynchronous: true
//                smooth: true
//                fillMode: Image.PreserveAspectCrop
//                sourceSize.width: units.dp(48)
//                onStatusChanged: {
//                }
//            }
//        }

//        Item {
//            id: status_update_content
//            anchors {
//                left: avatarImage.right
//                right: parent.right
//                top: parent.top
////                topMargin: units.gu(1)
//                //leftMargin: units.gu(1)
//                bottomMargin: units.gu(1)
//                //rightMargin: units.gu(1)
//            }
//            height: childrenRect.height
//            MouseArea {
//                anchors.fill: status_update_content
//                onClicked: {
////                    console.log("aaaaaaaaaaaa");
////                    console.log(flags);
////                    console.log(trans_flags);
////                    mydispather.set_str(trans_flags);
////                    console.log("bbbbbbbbbbbb");
//                    if (tile.state != 'Details') {
//                        tile.state = 'Details';

//                    } else {
//                        tile.state = 'List';
//                    }
//                }
//            }
//            Column {
//                spacing: units.gu(1)
//                anchors {
//                    left: parent.left;
//                    right: parent.right
//                    bottomMargin: units.gu(2)
//                }
//                Label {
//                    text: title
//                    fontSize: "medium"
//                    font.bold: true
//                    width: parent.width
//                }
//                Label {
//                    id: messageText
//                    text: detailstr
//                    maximumLineCount: tile.state != 'Details' ? 10 : 0
//                    elide: Text.ElideRight
//                    visible: true
//                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
//                    width: parent.width - units.gu(3)
//                    textFormat: Text.StyledText
//                    linkColor: "gray"
////                    onLinkActivated: Qt.openUrlExternally(link)
//                }
//            }
//        }

//        Item {
//            id: detailsWrapper
//            height: detailsLoader.height + units.gu(1)
//            width: parent.width
//            opacity: detailsOpacity
//            visible:  detailsOpacity > 0 ? true : false
//            anchors {
//                top: status_update_content.bottom
//                left: parent.left
//                right: parent.right
//            }
//            Loader {
//                id: detailsLoader
//                width: parent.width
//                visible: true
//            }
//            onVisibleChanged: {
//                if (visible && detailsLoader.state != Loader.Ready) {
//                    tile.trans_flags = flags;
//                    detailsLoader.source = "RubbishStatusDetails.qml";
//                }
//            }

//        }


//    }

//    DropShadow {
//        id: tileShadow
//        anchors.fill: tileRect
//        horizontalOffset: 3
//        verticalOffset: 3
//        radius: 8.0
//        samples: 16
//        cached: true
//        fast: true
//        color: "#f0f0f0"
//        source: tileRect
//    }

//    states: [State {
//                name: "Details"
//                PropertyChanges { target: tile; detailsOpacity: 1; x: 0 }
//                StateChangeScript {
//                    script: {
//                        listView.positionViewAtIndex(listView.indexAt(tile.x, tile.y), ListView.Contain);
//                    }
//                }
//            },
//            State {
//                name: "List"
//                PropertyChanges { target: tile; detailsOpacity: 0; x: 0 }
//            }]

//    transitions: Transition {
//        NumberAnimation {
//            duration: 300; properties: "detailsOpacity,x,height,width"
//        }
//    }
//}
