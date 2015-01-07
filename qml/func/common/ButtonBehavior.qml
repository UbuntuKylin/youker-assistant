import QtQuick 1.1

Item {
    id: behavior

    signal clicked
    property bool pressed: false
    property alias containsMouse: mouseArea.containsMouse
    property bool checkable: true
    property bool checked: true
    property bool triState: false

    onCheckableChanged: { if(!checkable) checked = false }
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onPressed: behavior.pressed = true
        onEntered: if(pressed && enabled) behavior.pressed = true
        onExited: behavior.pressed = false
        onCanceled: behavior.pressed = false
        onReleased: {
            if(behavior.pressed && behavior.enabled) {
                behavior.pressed = false
                if(behavior.checkable)
                    behavior.checked = !behavior.checked;
                behavior.clicked()
            }
        }
    }
}
