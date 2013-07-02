import QtQuick 2.0

Rectangle {
    id: container
    height: textLabel.height + 5
    width: textLabel.width + 5
    color: "gray"
    property string text: "kobe lee"
    property bool check: false
    property int pixelSize: 10
    Row {
        anchors.fill: parent
        spacing: 2

        Rectangle {
            id: imageRect
            border.color: "gray"
            anchors.verticalCenter: parent.verticalCenter
            height: textLabel.height
            width: height
            Image {
                id: imageTick
//                source: "../img/icons/check.png"
                source: "./styles/images/radiobutton_normal.png"
                anchors.fill: parent
                fillMode: Image.Stretch
                opacity: (container.check == true ? 1 : 0)
            }
        }

        Text {
            id: textLabel
            text: container.text
            width: 60
            height: 30
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: container.pixelSize
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            if (container.state == "pressed")
                container.state = "";
            else
                container.state = "pressed";

            container.check = ! container.check;
        }
    }

    states: [
        State {
            name: "pressed"
            PropertyChanges { target: container; color: "orange"; text: "靠右"}
            PropertyChanges { target: imageTick; source: "./styles/images/radiobutton_check.png"}
        }
    ]
}
