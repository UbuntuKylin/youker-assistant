import QtQuick 1.1
//import Ubuntu.Components 0.1
//import Ubuntu.Components.ListItems 0.1 as ListItem
import QtDesktop 0.1
import "common" as Common
//Component {
Item {
    id: clearDelegate
    property real detailsOpacity : 0
    property string check_flag : "clear_rubbish"
//        property string trans_flags: flags //把flags标记传递给RubbishStatusDetails
    width: parent.width//clearDelegate.ListView.view.width
    height: 65
    Item {
        Behavior on scale { NumberAnimation { easing.type: Easing.InOutQuad} }
        id: scaleMe
        anchors.verticalCenter: parent.verticalCenter//need or not?
        //checkbox, picture and words
        Row {
            id: lineLayout
            spacing: 10
            anchors {
                fill: parent
                left: parent.left
                leftMargin: 50
            }
            Common.CheckBox {
                id: checkbox
                checked: true
                anchors.verticalCenter: parent.verticalCenter
                onCheckedChanged: {
                    //kobe: wait for adding function
                    if (checkbox.checked) {
                        if (flags == "clear_rubbish")
                            check_flag = "clear_rubbish";
                        else if (flags == "clear_traces")
                            check_flag = "clear_traces";
                        else if (flags == "clear_plugins")
                            check_flag = "clear_plugins";
//                        console.log("lilililili");
                    }
                    else {
                        check_flag = "";
//                        console.log("xiangxiang");
                    }
                }
            }
            Image {
                id: clearImage
                width: 47; height: 47
                source: picture
                anchors {
                    left: checkbox.right; leftMargin: 15
                    verticalCenter: parent.verticalCenter
                }

            }

            Column {
                id: status_update_content
                spacing: 5
                anchors {
                    left: clearImage.right; leftMargin: 15
                    verticalCenter: parent.verticalCenter
                }
                Text {
                    text: title
                    font.pointSize: 11
                    color: "black"
                }
                Text {
                    text: detailstr
                    font.pointSize: 9
                    color: "gray"
                }
            }
            MouseArea {
                anchors.fill: status_update_content
                onClicked: {
                    console.log("1111111111111111");
                    console.log(flags);
//                    console.log(trans_flags);
//                    mydispather.set_str(trans_flags);
                    if (clearDelegate.state != 'Details') {
                        clearDelegate.state = 'Details';
                        console.log("2222222222222222222");

                    } else {
                        clearDelegate.state = 'List';
                        console.log("33333333333333333");
                    }
                }
            }

            Item {
                id: detailsWrapper
                height: detailsLoader.height
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
//                            clearDelegate.trans_flags = flags;
                        detailsLoader.source = "RubbishStatusDetails.qml";
                    }
                }

            }



        }
//            ListItem.ThinDivider {} //分割条  can be used as header for list
    }


    states: [State {
                name: "Details"
                PropertyChanges { target: clearDelegate; detailsOpacity: 1; x: 0 }
                StateChangeScript {
                    script: {
                        listView.positionViewAtIndex(listView.indexAt(clearDelegate.x, clearDelegate.y), ListView.Contain);
                    }
                }
            },
            State {
                name: "List"
                PropertyChanges { target: clearDelegate; detailsOpacity: 0; x: 0 }
            }]

    transitions: Transition {
        NumberAnimation {
            duration: 300; properties: "detailsOpacity,x,height,width"
        }
    }

//        MouseArea {
//            anchors.fill: clearDelegate
//            onClicked: itemClicked()
//        }
    //点击不同的项时移动焦点颜色
//    MouseArea {
//        anchors.fill: clearDelegate
//        onClicked: {
//            clearDelegate.ListView.view.currentIndex = index
//        }
//    }
}
//}







//Item {
//    id: rubbishDelegate
//    width: parent.width
//    height: 65

//    RubbishStatus {
//        id: content
////        width: rubbishDelegate.ListView.width  - units.gu(1)
////        height: childrenRect.height
//    }

//    //点击不同的项时移动焦点颜色
//    MouseArea {
//        anchors.fill: rubbishDelegate
//        onClicked: {
//            rubbishDelegate.ListView.view.currentIndex = index
//        }
//    }
//}




//    ListView {
//        id: listView
//        objectName: "listView"
//        height: parent.height - toolbar.height - units.gu(2)
//        width: parent.width
//        anchors {
//            top: updatesBanner.bottom
//            topMargin: units.gu(1)
//        }
//        opacity: 1
//        spacing: units.gu(1)
//        model: streamModel
//        snapMode: ListView.NoSnap
//        cacheBuffer: parent.height
//        boundsBehavior: Flickable.DragOverBounds
//        currentIndex: 0
//        delegate: statusDelegate

//        preferredHighlightBegin: 0
//        preferredHighlightEnd: preferredHighlightBegin
//        highlightRangeMode: ListView.StrictlyEnforceRange
//    }

//    Item {
//        id: updatesBanner
//        anchors {
//            top: parent.top
//            left: parent.left
//            right: parent.right
//        }
////            visible: unseen > 0
//        visible: true
//        height: visible ? units.gu(3) : 0
//        Text {
//            id: updatesText
//            anchors {
//                centerIn: parent
//                bottom: parent.bottom
//            }
//            text: ""
//            font.family: "Ubuntu"
//            font.bold: true
//            font.pointSize: 12
//            color: "gray"
//        }
//        MouseArea {
//            anchors.fill: parent
//            onClicked: {

//            }
//        }
//    }
