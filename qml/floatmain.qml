import QtQuick 1.1
import SystemType 0.1
import "./func/common" as Common

Rectangle {
    id: page
    width: 124; height: 114
    color: "#7bffffff"
//    radius:5

    SystemDispatcher {
        id: systemdispatcher
    }
    signal showWidget();
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

//    Style {
//        color: "gray"
//        transformOrigin: "Center"
//        opacity: 0.97
//        visible: true
//        anchors.centerIn: parent
//        width: 110; height: 50
//    }
    Column {
        anchors.top: parent.top
        anchors.topMargin: 5
        spacing: 2
        Contents {
            id: search
            visible: true
            opacity: 1
            anchors.horizontalCenter: parent.horizontalCenter
            MouseArea {
                anchors.fill: search
                acceptedButtons : Qt.RightButton
                onClicked: {
                    if (page.visible == true)
                        page.visible = false;
                    page.focus = false;
                }
            }
            MouseArea {
                anchors.fill: search
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
                onDoubleClicked: {
                }
            }
        }
        Common.Button {
            id: accelerateBtn
            width: 60
            height: 19
            anchors.horizontalCenter: parent.horizontalCenter
//            hoverimage: "move.png"
            text:"一键加速"
            onClicked: {
                systemdispatcher.cleanup_memory_qt();
            }
        }
    }


}
