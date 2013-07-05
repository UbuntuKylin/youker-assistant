//method 4
import QtQuick 1.1
import QtDesktop 0.1
import "common" as Common
//import RegisterMyType 0.1
import SessionType 0.1
//import SystemType 0.1
Rectangle {
    width: parent.width
    height: 460
//    property Dispatcher dis: mydispather
    property SessionDispatcher dis: sessiondispatcher
    Row {
        spacing: 10
        Button {
            id: quitbtn
            text: "取消"
            onClicked: {
                pageStack.push(homepage);
            }
        }
        Button {
            id: okbtn
            text: "测试"
            onClicked: {
                sessiondispatcher.new_object_test();
            }
        }
    }
}



//method 3
//import QtQuick 1.1
//Rectangle {
//    id: dialog
//    anchors.fill: parent


////    width: 240
////    height: 120
////    anchors.centerIn: parent

//    visible: true
//    color: "black"
//    opacity: 0
//    z: 32
//    signal opened()
//    signal rejected()

//    Behavior on opacity { PropertyAnimation { duration: 200 } }

////    MouseArea{
////        id: area
////        anchors.fill: parent
////        visible: dialog.visible

////        onClicked: {
////            close();
////            rejected();
////        }
////    }

//    function close(){
//        opacity = 0
//    }

//    function open(){
//        opacity = 0.9
//        opened()
//    }

//    property Item content: Item{}

//    onContentChanged: content.parent = dialog


////    MouseArea {
////          id: mouseRegion
////          anchors.fill: dialog;
////          property variant clickPos: "1,1"

////          onPressed: {
////              clickPos  = Qt.point(mouse.x,mouse.y)
////          }

////          onPositionChanged: {
////              var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)
////              mainwindow.pos = Qt.point(mainwindow.pos.x+delta.x,
////                                mainwindow.pos.y+delta.y)
////          }
////      }
//}
