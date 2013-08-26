import QtQuick 1.1
FocusScope {
    id: focusScope
    width: 100; height: 150
    focus:true

    BorderImage {
        source: "./img/skin/bg-right.png"
        width: parent.width; height: parent.height
        border { left: 4; top: 4; right: 4; bottom: 4 }
    }
    Column {
        anchors { left: parent.left; leftMargin: 8; right: clear.left; rightMargin: 8; verticalCenter: parent.verticalCenter }
        Text {
            text: systemdispatcher.get_cpu_percent_qt();
        }
        Text {
            text: systemdispatcher.get_total_memory_qt();
        }
        Text {
            text: systemdispatcher.get_used_memory_qt();
        }
        Text {
            text: systemdispatcher.get_free_memory_qt();
        }
        Text {
            text: systemdispatcher.get_network_flow_qt()[0] + "k";
        }
        Text {
            text: systemdispatcher.get_network_flow_qt()[1] + "k";
        }
    }
    Image {
        id: clear
        anchors { right: parent.right; rightMargin: 8; verticalCenter: parent.verticalCenter }
        source: "./img/icons/cookie.png"
        opacity: 0

        MouseArea {
            anchors.fill: parent
            onClicked: {}
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
}




//FocusScope {
//    id: focusScope
//    width: 80; height: 40
////    width: 600; height: 40
//    focus:true

//    BorderImage {
//        source: "../images/lineedit-bg.png"
//        width: parent.width; height: parent.height
//        border { left: 4; top: 4; right: 4; bottom: 4 }
//    }

//    Text {
//        id: typeSomething
//        anchors.fill: parent; anchors.leftMargin: 8
//        verticalAlignment: Text.AlignVCenter
//        text: "kobe"
////        text: "\u8BF7\u8F93\u5165\u7F51\u5740"
//        color: "gray"
//    }

//    MouseArea {
//        anchors.fill: parent
//        onClicked: { focusScope.focus = true; textInput.openSoftwareInputPanel(); }
//    }

//    TextInput {
//        id: textInput
//        anchors { left: parent.left; leftMargin: 8; right: clear.left; rightMargin: 8; verticalCenter: parent.verticalCenter }
//        focus: true
//        font.pixelSize:20
//    }

//    Image {
//        id: clear
//        anchors { right: parent.right; rightMargin: 8; verticalCenter: parent.verticalCenter }
//        source: "../images/clear.png"
//        opacity: 0

//        MouseArea {
//            anchors.fill: parent
//            onClicked: { textInput.text = ''; focusScope.focus = true; textInput.openSoftwareInputPanel(); }
//        }
//    }

//    states: State {
//        name: "hasText"; when: textInput.text != ''
//        PropertyChanges { target: typeSomething; opacity: 0 }
//        PropertyChanges { target: clear; opacity: 1 }
//    }

//    transitions: [
//        Transition {
//            from: ""; to: "hasText"
//            NumberAnimation { exclude: typeSomething; properties: "opacity" }
//        },
//        Transition {
//            from: "hasText"; to: ""
//            NumberAnimation { properties: "opacity" }
//        }
//    ]
//}
