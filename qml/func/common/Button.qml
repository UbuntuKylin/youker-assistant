import QtQuick 1.1
Item {
    id: btn
    signal clicked
//    property string text
    property string hoverimage: "scan-start.png"
    BorderImage {
        id: buttonImage
        source: "../../img/icons/" + btn.hoverimage
        width: btn.width; height: btn.height
    }
    BorderImage {
        id: pressed
        opacity: 0
        source: "../../img/icons/unselect.png"
        width: btn.width; height: btn.height
    }
    Image {
        id: btnImg
        anchors.fill: parent
        source: ""
    }
    MouseArea {
        id: mouseRegion
        anchors.fill: buttonImage
        hoverEnabled: true
//        id: signaltest
//        anchors.fill: parent
        onEntered: btnImg.source = "../../img/toolWidget/menu_hover.png"
        onPressed: btnImg.source = "../../img/toolWidget/menu_press.png"
        //要判断松开是鼠标位置
        onReleased: btnImg.source = "../../img/toolWidget/menu_hover.png"
        onExited: btnImg.source = ""



        onClicked: { btn.clicked(); }
    }
//    Text {
//        color: "white"
//        anchors.centerIn: buttonImage; font.bold: true; font.pixelSize: 15
//        text: btn.text; style: Text.Raised; styleColor: "black"
//    }
    states: [
        State {
            name: "Pressed"
            when: mouseRegion.pressed == true
            PropertyChanges { target: pressed; opacity: 1 }
        }
    ]
}
