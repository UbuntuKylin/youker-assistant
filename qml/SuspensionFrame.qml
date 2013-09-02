import QtQuick 1.1
import SystemType 0.1
import "./func/common" as Common
Rectangle{
    id:root
    width:275
    height: 260
    color:"transparent"
    property double cpu_value: 0.0
    property bool detail_flag: false
    visible: false
    property string up_speed: "0"
    property string down_speed: "0"
    property string used_memory: "0"
    property string free_memory: "0"
    property string memory_size: "0"
    property double ratio: 0.0

    SystemDispatcher {
        id: systemdispatcher
    }
    signal tansmitData(double cpu, string up, string down);

    function updateData() {
        root.cpu_value = systemdispatcher.get_cpu_percent_qt();
        root.used_memory = systemdispatcher.get_used_memory_qt();
        root.free_memory = systemdispatcher.get_free_memory_qt();
        root.ratio = root.used_memory /systemdispatcher.get_total_memory_qt();
        root.ratio = Math.round(root.ratio*100)/100 * 100
        systemdispatcher.get_network_flow_qt();
    }
    function show_large_widget() {
        if (root.visible == true)
            root.visible = false;
        else if (root.visible == false) {
            root.visible = true;
        }
    }
    function show_large_frame() {
        if (root.visible == true)
            root.visible = false;
    }

    Connections
    {
        target: systemdispatcher
        onFinishGetNetworkSpeed: {
            root.up_speed = speed[0];
            root.down_speed = speed[1];
            tansmitData(root.ratio, root.up_speed, root.down_speed);
        }
    }

    Component.onCompleted: {
        updateData();
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
        }

    //    Style {
    //        color: "gray"
    //        transformOrigin: "Center"
    //        opacity: 0.97
    //        visible: true
    //        anchors.centerIn: parent
    //        width: 110; height: 50
    //    }

        Rectangle {
            id: search
            anchors{
                top:parent.top
                left:parent.left
            }
            visible: true
            opacity: 1
            Rectangle {
                id:rec
                anchors.fill: parent
                color: "transparent"
//                z:2
                Column{
                    id:colu
                    anchors{
            //                horizontalCenter: parent.horizontalCenter
                        left: parent.left
                        leftMargin: 45
                        top:parent.top
                        topMargin: 5
                    }
                    spacing: 8
                    Text {
                        text: "试试点击屏幕右上角浮动框的右边矩形..."
                        font.pixelSize: 10
                        color: "#7a7a7a"
                    }

                    Text{
                        text: (root.ratio < 50) ? "系统运行流畅" : "系统运行缓慢"
                    }
                    Text{
                        text: (root.ratio < 50) ? "无需进行加速" : "建议您立即加速"
                    }
                    Common.Button {
                        id: accelerateBtn
                        width: 120
                        height: 28
                        text:"一键加速"
                        onClicked: {
                            systemdispatcher.cleanup_memory_qt();
                            updateData();
                        }
                    }
                }

            }
            Rectangle{
                id:detailed
                width: 228
                height: 90
                color: "lightblue"
                anchors{
                    top:parent.top
                    topMargin: 142
                }
                opacity: 0
                Column {
                    anchors {
                        top:parent.top
                        topMargin: 10
                        left: parent.left
                        leftMargin: 10
                    }
                    spacing: 5
                    Row {
                        Text{
                            text:"CPU占用率："
                            font.bold: true
                            font.pixelSize: 12
                            color: "#383838"
                        }
                        Text{
                            id: cpu_show
                            text: root.cpu_value + "%"
                            font.pixelSize: 12
                            color: "#7a7a7a"
                        }
                    }
                    Row {
                        Text{
                            text:"已使用内存："
                            font.bold: true
                            font.pixelSize: 12
                            color: "#383838"
                        }
                        Text{
                            text: root.used_memory + "M"
                            font.pixelSize: 12
                            color: "#7a7a7a"
                        }
                    }
                    Row {
                        Text{
                            text:"空闲内存："
                            font.bold: true
                            font.pixelSize: 12
                            color: "#383838"
                        }
                        Text{
                            text: root.free_memory + "M"
                            font.pixelSize: 12
                            color: "#7a7a7a"
                        }
                    }
                }
            }
        }

    }


    //speed row
    Text {
        id:download
        anchors{
            left: parent.left
            leftMargin: 60
            top:parent.top
            topMargin: 152
        }
        text: root.down_speed + "K/s"
        font.pixelSize: 12
        color: "#7a7a7a"
    }
    Text {
        id:upload
        anchors{
            left: parent.left
            leftMargin: 125
            top:parent.top
            topMargin: 152
        }
        text: root.up_speed + "K/s"
        font.pixelSize: 12
        color: "#7a7a7a"
    }
    Rectangle{width: 8;height: 20;color: "transparent"}
    Text{
        id:detail
        anchors{
            right: parent.right
            rightMargin: 20
            top:parent.top
            topMargin: 152
        }
        text:"详情"
        font.bold:true
        font.pointSize: 9
        color: "grey"
        Image {
            id: btnImg
            anchors.fill: parent
            source: ""
        }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                if(detail_flag==false){
                    page.height=page.height+90;
                    detail_flag=true;
                    detailed.opacity=1
                }
                else{
                    page.height=page.height-90;
                    detail_flag=false;
                    detailed.opacity=0
                }
            }
        }
    }


    Rectangle{
        id:ball
        width: 66;height: 66
        radius:50
        smooth:true
        anchors{
            left: parent.left
            leftMargin: 6
            top:parent.top
            topMargin: 6
        }
        Image {
            id: ballImage
            source: "./img/skin/blister-big.png"
        }
        Text {
            id: cpu
            text: root.ratio  + "%";
            anchors.centerIn: parent
        }
        gradient: Gradient{
            GradientStop{position: 0.0; color: (root.ratio == 100) ? "#ff2f00" : "transparent"}
            GradientStop{position: 1.0 - root.ratio * 0.01; color: (root.ratio == 100) ? "#ff2f00" : "transparent"}
            GradientStop{position: (root.ratio <= 0) ? 0.0 : (1.0 - root.ratio * 0.01 + 0.01);
                color: {
                    if(root.ratio > 60) {
                        ballImage.source = "./img/skin/blister-bigwarn.png";
                        "#ff2f00"
                    }
                    else if (root.ratio == 0)
                        "transparent"
                    else {
                        ballImage.source = "./img/skin/blister-big.png";
                        "#00b0ff"
                    }
                }
            }
            GradientStop{position: 1.0; color: {
                    if (root.ratio == 0)
                        "transparent"
                    else if (root.ratio > 60) {
                        "#ff1900"
                    }
                    else
                        "#006eff"
                }
            }
        }
    }

    Timer {
        interval: 5000; running: true; repeat: true
        onTriggered: {
            updateData();
        }
    }
}
