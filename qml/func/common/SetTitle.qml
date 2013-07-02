import QtQuick 1.1
Item {
    Row {
        Image {
            id: refreshArrow0
            source: "../../img/icons/settings.png"
//            Behavior on rotation { NumberAnimation { duration: 200 } }
        }
        Text {
            id: text0
    //                    x: 30
    //                    y: 11
            width: 69
            height: 20
            text: qsTr("Unity")
            font.bold: true
            font.pointSize: 13
            font.pixelSize: 12
        }
    }
}
