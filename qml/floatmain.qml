import QtQuick 1.1
import SystemType 0.1
Rectangle {
    id: page
    width: 114; height: 154
    color: "#7bffffff"
//    radius:5

    SystemDispatcher {
        id: systemdispatcher
    }
    function show_float_frame() {
        if (page.visible == true)
            page.visible = false;
        else if (page.visible == false)
            page.visible = true;
    }

    BorderImage {
        source: "./img/skin/bg-right.png"
        width: parent.width; height: parent.height
        border { left: 4; top: 4; right: 4; bottom: 4 }
    }

//    Column {
//        id: myco
//        Image {
//            id: refreshArrow
//            source: "./img/toolWidget/hardware.png"
////            anchors { top: lineLayout.top; topMargin: 10; left: parent.left; leftMargin: 45 }
//            width: 47; height: 47
//            Behavior on rotation { NumberAnimation { duration: 200 } }
//        }
//        Text {
//            id: text0
//            width: 69
//            text: qsTr("硬件信息:")
//            font.bold: true
//            font.pointSize: 13
//            font.pixelSize: 12
////            anchors { top: lineLayout.top; topMargin: refreshArrow.height/2; left: parent.left; leftMargin: 45 + refreshArrow.width }
//        }
//    }

//    MouseArea {
//        anchors.fill: parent
//        acceptedButtons : Qt.RightButton
//        onClicked: {
//            if (page.visible == true)
//                page.visible = false;
//            page.focus = false;
//        }
//    }
//    Style {
//        color: "gray"
//        transformOrigin: "Center"
//        opacity: 0.97
//        visible: true
//        anchors.centerIn: parent
//        width: 110; height: 150
//    }
    Column {
        anchors.horizontalCenter: parent.horizontalCenter
        Contents {
            id: search
            visible: true
            opacity: 1
    //        anchors.centerIn: parent
        }

        ContentsView {
            id: view
            visible: true

        }
    }

    MouseArea {
        anchors.fill: parent
        property variant clickPos: "1,1"
        onPressed: {
            clickPos  = Qt.point(mouse.x,mouse.y)
        }
        onPositionChanged: {
            var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)
            fmainwindow.pos = Qt.point(fmainwindow.pos.x+delta.x,
                              fmainwindow.pos.y+delta.y)
        }
        onClicked: {
        }
    }

    //------------------------------------------------

//    MouseArea {
//        anchors.fill: parent
//        onClicked: {
//            sidebar.visible != sidebar.visible;
//        }
//    }
}
