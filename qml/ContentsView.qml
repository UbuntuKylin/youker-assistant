import QtQuick 1.1
import "./func/common" as Common
Rectangle {
    id: contentview
    width: 100; height: 100
    Column {
        id: panel
        spacing:2
        Text {
            id:memory
            text: "内存大小： " + systemdispatcher.get_total_memory_qt();
            font.pixelSize: 12
            color: "#7a7a7a"
        }
        Text {
            id:usememory
            text: "已使用内存： " + systemdispatcher.get_used_memory_qt();
            font.pixelSize: 12
            color: "#7a7a7a"
        }
        Text {
            id:freememory
            text: "可释放内存：" + systemdispatcher.get_free_memory_qt();
            font.pixelSize: 12
            color: "#7a7a7a"
        }
        Common.Button {
            id: accelerateBtn
            width: 80
            height: 30
            anchors.horizontalCenter: parent.horizontalCenter
//            hoverimage: "scan-start.png"
            onClicked: {
            }
        }
    }
}
