import QtQuick 1.1
import SystemType 0.1
import "./func/common" as Common

FocusScope {
    id: focusScope
    width: parent.width
    height: parent.height
    property double cpu: 0.0
    anchors{
        top:parent.top
        left: parent.left
    }
    focus:true
    property string speedtext:"你难道正在骑蜗牛"
    property string proposaltext:"建议立即加速"
    property bool detail_flag: false
    property string up_speed: "0"
    property string down_speed: "0"
//    property string used_memory: "0"
//    property string free_memory: "0"
//    property string memory_size: "0"
    Component.onCompleted: {
        focusScope.cpu = systemdispatcher.get_cpu_percent_qt();
        console.log("11111111111111111111111");
        console.log(focusScope.cpu);
//        var speed = systemdispatcher.get_network_flow_qt();
//        focusScope.up_speed = speed[0];
//        focusScope.down_speed = speed[1];
//        focusScope.used_memory = systemdispatcher.get_used_memory_qt();
//        focusScope.free_memory = systemdispatcher.get_free_memory_qt();
//        focusScope.memory_size = systemdispatcher.get_total_memory_qt();
    }

    Rectangle {
        id:rec
        anchors.fill: parent
        color: "transparent"
        z:2
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
                text: (focusScope.cpu < 50) ? "系统运行流畅" : "系统运行缓慢"
            }
            Text{
                text: (focusScope.cpu < 50) ? "无需进行加速" : "建议您立即加速"
            }
            Common.Button {
                id: accelerateBtn
                width: 120
                height: 28
                text:"一键加速"
                onClicked: {
                    systemdispatcher.cleanup_memory_qt();
                }
            }
        }

        Row {
            spacing: 35
            anchors{
                left: parent.left
                leftMargin: 28
                top:parent.top
                topMargin: 122
            }
            Text {
                id:upload
                text: focusScope.up_speed + "K/s"
//                text: "K/s"
                font.pixelSize: 12
                color: "#7a7a7a"
            }

            Text {
                id:download
                text: focusScope.down_speed + "K/s"
//                text: "K/s"
                font.pixelSize: 12
                color: "#7a7a7a"
            }

            Rectangle{width: 8;height: 20;color: "transparent"}
            Text{
                id:detail
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
                    hoverEnabled: true
                    onEntered: btnImg.source = "./img/toolWidget/menu_hover.png"
                    onPressed: btnImg.source = "./img/toolWidget/menu_press.png"
                    //要判断松开是鼠标位置
                    onReleased: btnImg.source = "./img/toolWidget/menu_hover.png"
                    onExited: btnImg.source = ""
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
        Text{
            id:detailedtext
            anchors.centerIn: parent
            text:"详细显示的内容，待扩展"
        }
    }



    Timer {
        interval: 5000; running: true; repeat: true
        onTriggered: {
            focusScope.cpu = systemdispatcher.get_cpu_percent_qt();
//            focusScope.cpu =

            //            statustext.text = {
            //                if(focusScope.cpu < 10)
            //                    "系统运行流畅"
            //                else if(focusScope.cpu > 10 && focusScope.cpu < 30)
            //                    "系统运行正常"
            //                if(focusScope.cpu > 30)
            //                    "系统运行缓慢"
            //            }



//            focusScope.cpu_value = systemdispatcher.get_cpu_percent_qt();
//            var speed = systemdispatcher.get_network_flow_qt();
//            focusScope.up_speed = speed[0];
//            focusScope.down_speed = speed[1];
//            focusScope.used_memory = systemdispatcher.get_used_memory_qt();
//            focusScope.free_memory = systemdispatcher.get_free_memory_qt();
        }
    }
}
