import QtQuick 1.1
import QtDesktop 0.1

Rectangle {
    id: dialog
    width: 300
    height: 250
    color: "transparent"

    Image {
        id: bgImg
        anchors.fill: parent
        source: "../../img/skin/background.png"
    }
    Column {
        spacing: 10
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        Text {
            text: "点击鼠标左键更换颜色,右键退出"
//            anchors.centerIn: parent
            width: quitBtn.width + okBtn.width + 10
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Row {
            spacing: 20
            Button {
                id: quitBtn
                text: qsTr("取消")
                onClicked: {
//                    Qt.quit()
                }
            }
            Button {
                id: okBtn
                text: qsTr("确定")
            }
        }
    }


//    MouseArea {
//          id: mouseRegion
//          anchors.fill: parent
//          property variant clickPos: "1,1"

//          onPressed: {
//              clickPos  = Qt.point(mouse.x,mouse.y)
//          }

//          onPositionChanged: {
//              var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)
//              modelessdialog.pos = Qt.point(modelessdialog.pos.x+delta.x,
//                                modelessdialog.pos.y+delta.y)
//          }
//      }


}
