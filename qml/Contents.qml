import QtQuick 1.1
FocusScope {
    id: focusScope
    width: 100; height: 50
    focus:true
    property double cpu_value: 0.0
    Component.onCompleted: {
        focusScope.cpu_value = systemdispatcher.get_cpu_percent_qt();
    }

//    Rectangle {
//         width: parent.width; height: parent.height + 8

//         AnimatedImage { id: animation; source: "./img/toolWidget/clear-movie.gif" }

//         Rectangle {
//             property int frames: animation.frameCount
//             width: 4; height: 8
//             x: (animation.width - width) * animation.currentFrame / frames
//             y: animation.height
//             color: "red"
//         }
//     }

//    BorderImage {
//        source: "./img/skin/bg-right.png"
//        width: parent.width; height: parent.height
//        border { left: 4; top: 4; right: 4; bottom: 4 }
//    }
    Row {
        id: myrow
//        anchors { left: parent.left; leftMargin: 8; right: clear.left; rightMargin: 8; verticalCenter: parent.verticalCenter }
        Rectangle{
            id:ball
            width: 50;height: 50
            border.color: "grey"
            radius:50
            smooth:true
            Text {
                id: cpu
                text: focusScope.cpu_value + "%";
                anchors.centerIn: parent
            }
            gradient: Gradient{
                GradientStop{position: 0.0; color: "transparent"}
                GradientStop{position: 1.0 - focusScope.cpu_value * 0.01; color: "transparent"}
                GradientStop{position: 1.0 - focusScope.cpu_value * 0.01 + 0.01; color: "green"}
                GradientStop{position: 1.0; color: "green"}
            }
        }

        Column {
            Row {
                Image {
                    source: "./img/icons/upload.png"
                }
                Text {
                    id:upload
                    text: systemdispatcher.get_network_flow_qt()[0] + "K/s";
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }

            Row {
                Image {
                    source: "./img/icons/download.png"
                }
                Text {
                    id:download
                    text: systemdispatcher.get_network_flow_qt()[1] + "K/s";
                    font.pixelSize: 12
                    color: "#7a7a7a"
                }
            }
        }
    }

//    MouseArea {
//        anchors.fill: parent
//        property variant clickPos: "1,1"
//        onPressed: {
//            clickPos  = Qt.point(mouse.x,mouse.y)
//        }
//        onPositionChanged: {
//            var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)
//            fmainwindow.pos = Qt.point(fmainwindow.pos.x+delta.x,
//                              fmainwindow.pos.y+delta.y)
//        }
//        onClicked: {
//        }
//    }


    Timer {
        interval: 5000; running: true; repeat: true
        onTriggered: {
//             cpu.text = systemdispatcher.get_cpu_percent_qt();
            focusScope.cpu_value = systemdispatcher.get_cpu_percent_qt();
//            console.log(focusScope.cpu_value * 0.01);
//            cputext.text = cpu.text;
//             usememory.text = "已使用内存： " + systemdispatcher.get_used_memory_qt();
//             freememory.text = "可释放内存：" + systemdispatcher.get_free_memory_qt();
             upload.text = systemdispatcher.get_network_flow_qt()[0] + "K/s";
             download.text = systemdispatcher.get_network_flow_qt()[1] + "K/s";
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
