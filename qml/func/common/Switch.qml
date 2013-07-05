import QtQuick 1.1

Item {
    id: container
    signal switched(bool position)
    property string fontName: "Helvetica"
    property int fontSize: 12
    property color fontColor: "black"
    property string imageOn: '../../img/icons/switch_on.png'
    property string imageOff: '../../img/icons/switch_off.png'
    property bool switchedOn: true
    property alias textOn: textOn.text
    property alias textOff: textOff.text
    property alias spacing: row.spacing
    width: 15//row.width
    height: 26
    Row {
        id: row
        spacing: 8
        Text {
            id: textOn
            text: qsTr("开启")
            height: container.height
            color: container.fontColor
//            font {
//                family: container.fontName
//                pointSize: container.fontSize
//            }
            verticalAlignment: Text.AlignVCenter
        }
        Image {
            id: toggleSwitch
            height: container.height
            source: switchedOn ? imageOn : imageOff
            fillMode: Image.PreserveAspectFit
            smooth: true
        }
        Text {
            id: textOff
            height: container.height
            text: qsTr("关闭")
            color: container.fontColor
//            font {
//                family: container.fontName
//                pointSize: container.fontSize
//            }
            verticalAlignment: Text.AlignVCenter
        }
    }
    MouseArea {
        anchors.fill: row
        onClicked: { switchedOn = !switchedOn; switched(switchedOn) }
    }
}
