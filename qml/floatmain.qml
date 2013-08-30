import QtQuick 1.1
import SystemType 0.1
import "./func/common" as Common
Rectangle{
    id:root
    width:275
//    height: 170
    height: 260
//    color: "transparent"
    color:"transparent"
    property double cpu_value: 0.0
    visible: false

    property string up_speed: "0"
    property string down_speed: "0"
    //    property string used_memory: "0"
    //    property string free_memory: "0"
    //    property string memory_size: "0"

    signal tansmitData(double cpu, string up, string down);

    Component.onCompleted: {
        root.cpu_value = systemdispatcher.get_cpu_percent_qt();
        tansmitData(root.cpu_value, "10", "20");
        //        var speed = systemdispatcher.get_network_flow_qt();
        //        focusScope.up_speed = speed[0];
        //        focusScope.down_speed = speed[1];
        //        focusScope.used_memory = systemdispatcher.get_used_memory_qt();
        //        focusScope.free_memory = systemdispatcher.get_free_memory_qt();
        //        focusScope.memory_size = systemdispatcher.get_total_memory_qt();
    }

//    signal show_in_qt;

//    function receive_data(value, up, down) {
//        root.cpu_value = value;
//        root.up_speed = up;
//        root.down_speed = down;
//    }

    function show_large_widget() {
        if (root.visible == true)
            root.visible = false;
        else if (root.visible == false) {
//            show_in_qt();
            root.visible = true;
        }
    }
    function show_large_frame() {
        if (root.visible == true)
            root.visible = false;
    }

    Image {
        id: background
        source: "./img/skin/accelerate-bg.png"
    }
    Rectangle {
        id: page
        width: 228; height: 142
        anchors{
            left: parent.left
            leftMargin: 35
            top: parent.top
            topMargin: 30
        }
        color: "transparent"
    //    radius:5
        SystemDispatcher {
            id: systemdispatcher
        }

    //    Style {
    //        color: "gray"
    //        transformOrigin: "Center"
    //        opacity: 0.97
    //        visible: true
    //        anchors.centerIn: parent
    //        width: 110; height: 50
    //    }


        Contents {
            id: search
            visible: true
            opacity: 1
            anchors.horizontalCenter: parent.horizontalCenter
            up_speed: root.up_speed
            down_speed: root.down_speed
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
            }
        }

    }
    Rectangle{
        id:ball
        width: 66;height: 66
//        border.color: "grey"
        radius:50
        smooth:true
        anchors{
            left: parent.left
            leftMargin: 6
            top:parent.top
            topMargin: 6
        }
        Text {
            id: cpu
            text: root.cpu_value + "%";
            anchors.centerIn: parent
        }
        gradient: Gradient{
            GradientStop{position: 0.0; color: (root.cpu_value == 100) ? "red" : "transparent"}

            GradientStop{position: 1.0 - root.cpu_value * 0.01; color: (root.cpu_value == 100) ? "red" : "transparent"}
            GradientStop{position: (root.cpu_value <= 0) ? 0.0 : (1.0 - root.cpu_value * 0.01 + 0.01);
                color: {
                    if(root.cpu_value > 60)
                        "red"
                    else if (root.cpu_value == 0)
                        "transparent"
                    else
                        "green"
                }
            }
            GradientStop{position: 1.0; color: {
                    if (root.cpu_value == 0)
                        "transparent"
                    else if (root.cpu_value == 100)
                        "red"
                    else
                        "green"
                }
            }
        }
    }
    Timer {
        interval: 5000; running: true; repeat: true
        onTriggered: {
            root.cpu_value = systemdispatcher.get_cpu_percent_qt();
            tansmitData(root.cpu_value, "10", "20");
            //            var speed = systemdispatcher.get_network_flow_qt();
            //            focusScope.up_speed = speed[0];
            //            focusScope.down_speed = speed[1];
            //            focusScope.used_memory = systemdispatcher.get_used_memory_qt();
            //            focusScope.free_memory = systemdispatcher.get_free_memory_qt();
        }
    }
}
