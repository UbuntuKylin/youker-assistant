import QtQuick 1.1

Item {
    id: tabWidget
    default property alias content: stack.children //将tab页集合设置一个默认属性
    property int current: 0
    onCurrentChanged: setOpacities()
    Component.onCompleted: setOpacities()
    function setOpacities() {
        for(var i = 0; i < content.length; ++i) {
            content[i].opacity = (i == current ? 1 : 0);//将当前的tab设置为非透明,其余透明
        }
    }
    Row {  //此组件为tab选项
        id: header
        Repeater {
            model: content.length
            delegate: Rectangle {
                id: mytab
                width: 90
                height: 36
                color: "#abc2c2"
//                border.color: "grey"
                Image {
                    anchors.fill: parent
                    anchors.leftMargin: 0.5
                    anchors.rightMargin: 0.5
                    source: "../../img/icons/tab.png"
                }
                Rectangle {
                    width: tabWidget.width; height: 1
                    anchors.bottom: parent.bottom
                    color: "#abc2c2"
                }
                BorderImage {  //tab选项图片
                    anchors { fill: parent; leftMargin: 1; topMargin: 0; rightMargin: 1}
//                    border { left: 7; right: 7}
                    source: tabWidget.current == index? "../../img/icons/tab-active.png" : ""
                }
                Text {
                    horizontalAlignment: "AlignHCenter"; verticalAlignment: "AlignVCenter"
                    anchors.fill: parent
                    text: content[index].title
                    font.pointSize: 10
                    elide: Text.ElideRight
                    font.bold: tabWidget.current == index
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: tabWidget.current = index  //存储当前选中tab页
                }
            }

        }
    }
    Item {  //tab页
        id: stack
        width: tabWidget.width
        anchors.top: header.bottom
        anchors.bottom: tabWidget.bottom
    }

}
