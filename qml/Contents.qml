import QtQuick 1.1

FocusScope {
    id: focusScope
    width: 120; height: 80
    focus:true
    property double cpu_value: 0.0
    property string up_speed: "0"
    property string down_speed: "0"
    property string used_memory: "0"
    property string free_memory: "0"
    property string memory_size: "0"
    Component.onCompleted: {
        focusScope.cpu_value = systemdispatcher.get_cpu_percent_qt();
//        var speed = systemdispatcher.get_network_flow_qt();
//        focusScope.up_speed = speed[0];
//        focusScope.down_speed = speed[1];
        focusScope.used_memory = systemdispatcher.get_used_memory_qt();
        focusScope.free_memory = systemdispatcher.get_free_memory_qt();
        focusScope.memory_size = systemdispatcher.get_total_memory_qt();
    }

    Rectangle {
        Row {
            id: myrow
            spacing: 5
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
                    GradientStop{position: 0.0; color: (focusScope.cpu_value == 100) ? "red" : "transparent"}

                    GradientStop{position: 1.0 - focusScope.cpu_value * 0.01; color: (focusScope.cpu_value == 100) ? "red" : "transparent"}
                    GradientStop{position: (focusScope.cpu_value <= 0) ? 0.0 : (1.0 - focusScope.cpu_value * 0.01 + 0.01);
                        color: {
                            if(focusScope.cpu_value > 60)
                                "red"
                            else if (focusScope.cpu_value == 0)
                                "transparent"
                            else
                                "green"
                        }
                    }
                    GradientStop{position: 1.0; color: {
                            if (focusScope.cpu_value == 0)
                                "transparent"
                            else if (focusScope.cpu_value == 100)
                                "red"
                            else
                                "green"
                        }
                    }
                }
            }

            Column {
                anchors.verticalCenter: parent.verticalCenter
                spacing: 10
                Row {
                    Image {
                        source: "./img/icons/upload.png"
                        width: 16
                        height: 16
                    }
                    Text {
                        id:upload
//                        text: "focusScope.up_speed" + "K/s";
                        text: "NA K/s";
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                }

                Row {
                    Image {
                        source: "./img/icons/download.png"
                        width: 16
                        height: 16
                    }
                    Text {
                        id:download
//                        text: "focusScope.down_speed" + "K/s";
                        text: "NA K/s";
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                }
            }
        }

        Text {
            id: title
            anchors.top: myrow.bottom
            anchors.topMargin: 2
//            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 9
            text: "内存总量|" +  "已用内存|" + "可释放内存";
        }
        Text {
            id: memory
            anchors.top: title.bottom
            anchors.topMargin: 2
//            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 10
            text: focusScope.memory_size + "M     " + focusScope.used_memory + "M     " + focusScope.free_memory + "M";
        }
    }
    Timer {
        interval: 5000; running: true; repeat: true
        onTriggered: {
            focusScope.cpu_value = systemdispatcher.get_cpu_percent_qt();
//            var speed = systemdispatcher.get_network_flow_qt();
//            focusScope.up_speed = speed[0];
//            focusScope.down_speed = speed[1];
            focusScope.used_memory = systemdispatcher.get_used_memory_qt();
            focusScope.free_memory = systemdispatcher.get_free_memory_qt();
        }
    }
}
