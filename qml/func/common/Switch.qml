import QtQuick 1.1

Item {
    id: container

    // Signal that gets fired when switch state has been toggled
    signal switched(bool position)
    // Font properties
    property string fontName: "Helvetica"
    property int fontSize: 12
    property color fontColor: "black"
    // Images for switch states
    property string imageOn: '../../img/icons/switch_on.png'
    property string imageOff: '../../img/icons/switch_off.png'
    // Property indicating current state
    property bool switchedOn: true
    // Labels for the states
    property alias textOn: textOn.text
    property alias textOff: textOff.text
    // Spacing between labels and switch
    property alias spacing: row.spacing

    width: row.width
    height: 44

    Row {
        id: row
        spacing: 8
        Text {
            id: textOn
            text: "On"
            height: container.height
            color: container.fontColor
            font {
                family: container.fontName
                pointSize: container.fontSize
            }
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
            text: "Off"
            color: container.fontColor
            font {
                family: container.fontName
                pointSize: container.fontSize
            }
            verticalAlignment: Text.AlignVCenter
        }
    }
    MouseArea {
        anchors.fill: row
        onClicked: { switchedOn = !switchedOn; switched(switchedOn) }
    }
}
