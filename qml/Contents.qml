import QtQuick 1.1
import SystemType 0.1
import "./func/common" as Common

FocusScope {
    id: focusScope
    width: parent.width
    height: parent.height
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
                leftMargin: 40
                top:parent.top
                topMargin: 20
            }
            spacing: 8
            Text{
                text:speedtext
            }
            Text{
                text:proposaltext
            }
            Common.Button {
                id: accelerateBtn
                width: 120
                height: 28

    //                anchors.horizontalCenter: parent.horizontalCenter
    //                anchors.top:search.bottom
    //                anchors.topMargin: 10
    //            hoverimage: "move.png"
                text:"一键加速"
                onClicked: {
                    systemdispatcher.cleanup_memory_qt();
//                    console.log("11111111111111")
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
                text: focusScope.up_speed + "K/s";
                font.pixelSize: 12
                color: "#7a7a7a"
            }

            Text {
                id:download
                text: focusScope.down_speed + "K/s";
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

//        Text {
//            id: title
//            anchors.top: myrow.bottom
//            anchors.topMargin: 2
////            anchors.horizontalCenter: parent.horizontalCenter
//            font.pixelSize: 9
//            text: "内存总量|" +  "已用内存|" + "可释放内存";
//        }
//        Text {
//            id: memory
//            anchors.top: title.bottom
//            anchors.topMargin: 2
////            anchors.horizontalCenter: parent.horizontalCenter
//            font.pixelSize: 10
//            text: focusScope.memory_size + "M     " + focusScope.used_memory + "M     " + focusScope.free_memory + "M";
//        }

    Timer {
        interval: 5000; running: true; repeat: true
        onTriggered: {
//            focusScope.cpu_value = systemdispatcher.get_cpu_percent_qt();
//            var speed = systemdispatcher.get_network_flow_qt();
//            focusScope.up_speed = speed[0];
//            focusScope.down_speed = speed[1];
//            focusScope.used_memory = systemdispatcher.get_used_memory_qt();
//            focusScope.free_memory = systemdispatcher.get_free_memory_qt();
        }
    }
}
