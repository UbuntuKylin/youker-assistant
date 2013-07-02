import QtQuick 2.0
import "./defaultstyle" as DefaultStyle

Item {
    id: checkbox

    property int minimumWidth: defaultStyle.minimumWidth
    property int minimumHeight: defaultStyle.minimumHeight
    width: Math.max(minimumWidth, backgroundComponent.item.width)
    height: Math.max(minimumHeight, backgroundComponent.item.height)

    property alias containsMouse: behavior.containsMouse
    property Component background: defaultStyle.background
    property Component checkmark: defaultStyle.checkmark

    property color backgroundColor: "#fff";

    signal clicked
    property alias pressed: behavior.pressed
    property alias checked: behavior.checked

    Loader {
        id: backgroundComponent
        anchors.centerIn: parent
        sourceComponent: background
    }

    Loader {
        id: checkComponent
        anchors.centerIn: parent
        sourceComponent: checkmark
    }

    ButtonBehavior {
        id: behavior
        anchors.fill: parent
        checkable: true
        onClicked:checkbox.clicked()
    }

    DefaultStyle.CheckBoxStyle { id: defaultStyle }
}
