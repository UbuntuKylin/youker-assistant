import QtQuick 2.0
//import Ubuntu.Components 0.1
//import Ubuntu.Components.ListItems 0.1 as ListItem


//Item {
//    id: clearDelegate
//    width: parent.width
//    height: 65
//    //checkbox, picture and words
//    Row {
//        id: lineLayout
//        spacing: 10
//        anchors {
//            fill: parent
//            left: parent.left
//            leftMargin: 50
//        }

//        CheckBox {
//            id: checkbox
//            checked: true
//            anchors.verticalCenter: parent.verticalCenter
//            onCheckedChanged: {
//                //kobe: wait for adding function
//            }
//        }

//        Image {
//            id: clearImage
//            width: 47; height: 47
//            source: picture
//            anchors {
//                left: checkbox.right; leftMargin: 15
//                verticalCenter: parent.verticalCenter
//            }

//        }

//        Column {
//            spacing: 5
//            anchors {
//                left: clearImage.right; leftMargin: 15
//                verticalCenter: parent.verticalCenter
//            }
//            Text {
//                text: title
//                font.pointSize: 11
//                color: "black"
//            }
//            Text {
//                text: detailstr
//                font.pointSize: 9
//                color: "gray"
//            }
//        }
//    }
//    ListItem.ThinDivider {} //分割条  can be used as header for list

//    //点击不同的项时移动焦点颜色
//    MouseArea {
//        anchors.fill: clearDelegate
//        onClicked: {
//            clearDelegate.ListView.view.currentIndex = index
//        }
//    }
//}







Item {
    id: rubbishDelegate
    width: parent.width
    height: 65

    RubbishStatus {
        id: content
//        width: rubbishDelegate.ListView.width  - units.gu(1)
//        height: childrenRect.height
    }

    //点击不同的项时移动焦点颜色
    MouseArea {
        anchors.fill: rubbishDelegate
        onClicked: {
            rubbishDelegate.ListView.view.currentIndex = index
        }
    }
}




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
