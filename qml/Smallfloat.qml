import QtQuick 1.1
import SystemType 0.1
import "./func/common" as Common
Rectangle {
    id:sfloat
    width: 83
    height: 35
    color: "transparent"
    radius: 5
    property string up_speed: "0"
    property string down_speed: "0"
    property double cpu_value: 0.0
    signal floatshow()

    Component.onCompleted: {
        sfloat.cpu_value = systemdispatcher.get_cpu_percent_qt();
//        var speed = systemdispatcher.get_network_flow_qt();
//        sfloat.up_speed = speed[0];
//        sfloat.down_speed = speed[1];
    }
    SystemDispatcher {
        id: systemdispatcher
    }
    signal showWidget();
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
            top:parent.top
            topMargin: 2
            left: parent.left
            leftMargin: 22
        }
        spacing: 3
        Text {
            id:upload
            text: sfloat.up_speed + "K/s";
            font.pixelSize: 10
            color: "#7a7a7a"
        }
        Text {
            id:download
            text: sfloat.down_speed + "K/s";
            font.pixelSize: 10
            color: "#7a7a7a"
        }
    }
    Rectangle{
        id:ball
        width: 30;height: 30
//        border.color: "grey"
        radius:2
        z:1
        smooth:true
        anchors{
            right: parent.right
            rightMargin: 2
            top:parent.top
            topMargin: 1
        }
        Text {
            id: cpu
            text: sfloat.cpu_value + "%";
            font.pointSize: 8
            anchors.centerIn: parent
        }
        gradient: Gradient{
            GradientStop{position: 0.0; color: (sfloat.cpu_value == 100) ? "red" : "transparent"}

            GradientStop{position: 1.0 - sfloat.cpu_value * 0.01; color: (sfloat.cpu_value == 100) ? "red" : "transparent"}
            GradientStop{position: (sfloat.cpu_value <= 0) ? 0.0 : (1.0 - sfloat.cpu_value * 0.01 + 0.01);
                color: {
                    if(sfloat.cpu_value > 60)
                        "red"
                    else if (sfloat.cpu_value == 0)
                        "transparent"
                    else
                        "green"
                }
            }
            GradientStop{position: 1.0; color: {
                    if (sfloat.cpu_value == 0)
                        "transparent"
                    else if (sfloat.cpu_value == 100)
                        "red"
                    else
                        "green"
                }
            }
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                sfloat.floatshow();
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
        onClicked: {
        }
        onDoubleClicked: {
        }
    }
//    onFloatshow: {console.log("11111111111111111111111111")}
    Timer {
        interval: 5000; running: true; repeat: true
        onTriggered: {
            sfloat.cpu_value = systemdispatcher.get_cpu_percent_qt();
//            var speed = systemdispatcher.get_network_flow_qt();
//            sfloat.up_speed = speed[0];
//            sfloat.down_speed = speed[1];
        }
    }
}
