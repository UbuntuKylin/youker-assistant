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
    Contents {
        id: search
        visible: true
        opacity: 1
        anchors.centerIn: parent
    }


    //--------------------下边隐藏说明栏---------------------
    BorderImage {
        id: sidebar
        source: "./img/icons/unselect.png"
        anchors.top: search.bottom
        width: parent.width
        height:show ? 140 : 10
        Behavior on width { NumberAnimation { easing.type: Easing.OutSine ; duration: 250 } }
        property bool show: false
////        border.left: 0;
////        border.right: 26;
//        border.left: 26;
//        border.right: 0;
        MouseArea {
            id:mouseArea
            anchors.fill: parent
            onClicked: sidebar.show = !sidebar.show
        }
        Column {
            id: panel1
            opacity: sidebar.show ? 1 : 0
            Behavior on opacity { NumberAnimation { easing.type:Easing.InCubic; duration: 600} }

            scale: sidebar.show ? 1 : 0
            Behavior on scale { NumberAnimation { easing.type:Easing.InCubic; duration: 200 } }
            transformOrigin: Item.Top

            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 12
            spacing:12

            Image {
                width: 47
                height: 47
                source: "./img/icons/book.png"
            }
            Text {
                text: "UbuntuKylin Team"
                width: parent.width - 12
            }
            Text {
                text: qsTr("系统助手")
                width: parent.width - 12
            }
            Text {
                text: qsTr("第一期工程 20130601")
                width: parent.width - 12
            }
        }
    }
    //------------------------------------------------
}
