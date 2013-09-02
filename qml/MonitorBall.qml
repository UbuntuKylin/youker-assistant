import QtQuick 1.1
import SystemType 0.1
import "./func/common" as Common
Rectangle {
    id:sfloat
    width: 83
    height: 48
    color: "transparent"
    radius: 5
    property string up_speed: "0"
    property string down_speed: "0"
    property double memory_ratio: 0.0
    signal send_signal_to_large;


    function receive_data(value, up, down) {
        sfloat.memory_ratio = value;
        sfloat.up_speed = up;
        sfloat.down_speed = down;
    }

    Component.onCompleted: {
        sfloat.memory_ratio = systemdispatcher.get_used_memory_qt()/systemdispatcher.get_total_memory_qt();
        sfloat.memory_ratio = Math.round(sfloat.memory_ratio*100)/100 * 100
    }
    SystemDispatcher {
        id: systemdispatcher
    }

    function show_float_frame() {
        if (sfloat.visible == true)
            sfloat.visible = false;
        else if (sfloat.visible == false)
            sfloat.visible = true;
    }
    Image {
        id: background
        source: "./img/skin/accelerate-bg0.png"
    }
    Column{
        anchors{
            bottom:parent.bottom
            bottomMargin: 6
            left: parent.left
            leftMargin: 22
        }
        spacing: 3
        Text {
            id:upload
            text: sfloat.up_speed + "K/s"
            font.pixelSize: 10
            color: "#7a7a7a"
        }
        Text {
            id:download
            text: sfloat.down_speed + "K/s"
            font.pixelSize: 10
            color: "#7a7a7a"
        }
    }
    Rectangle{
        id:ball
        width: 31;height: 31
//        border.color: "grey"
        radius:2
        z:1
        smooth:true
        anchors{
            right: parent.right
            rightMargin: 1
            bottom:parent.bottom
            bottomMargin: 2
        }
        Image {
            source: "./img/skin/blister-small.png"
        }
        Text {
            id: cpu
            text: sfloat.memory_ratio + "%";
            font.pointSize: 8
            anchors.centerIn: parent
        }
        gradient: Gradient{
            GradientStop{position: 0.0; color: (sfloat.memory_ratio == 100) ? "#ff2400" : "transparent"}

            GradientStop{position: 1.0 - sfloat.memory_ratio * 0.01; color: (sfloat.memory_ratio == 100) ? "#ff2400" : "transparent"}
            GradientStop{position: (sfloat.memory_ratio <= 0) ? 0.0 : (1.0 - sfloat.memory_ratio * 0.01 + 0.01);
                color: {
                    if(sfloat.memory_ratio > 60)
                        "#ff2400"
                    else if (sfloat.memory_ratio == 0)
                        "transparent"
                    else
                        "#0084ff"
                }
            }
            GradientStop{position: 1.0; color: {
                    if (sfloat.memory_ratio == 0)
                        "transparent"
                    else if (sfloat.memory_ratio > 60)
                        "#ff2400"
                    else
                        "#0084ff"
                }
            }
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                send_signal_to_large();
            }
        }
    }

    MouseArea {
        anchors.fill: sfloat
        acceptedButtons : Qt.RightButton
        onClicked: {
            if (sfloat.visible == true)
                sfloat.visible = false;
            sfloat.focus = false;
        }
    }
    MouseArea {
        anchors.fill: sfloat
        property variant clickPos: "1,1"
        onPressed: {
            clickPos  = Qt.point(mouse.x,mouse.y)
        }
        onPositionChanged: {
            var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)
            smallwindow.pos = Qt.point(smallwindow.pos.x+delta.x,
                              smallwindow.pos.y+delta.y)
        }
    }
}
