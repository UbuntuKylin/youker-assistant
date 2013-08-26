import QtQuick 1.1
import SystemType 0.1
Rectangle {
    id: page
    width: 114; height: 154
    color: "#7bffffff"
//    radius:5

    SystemDispatcher {
        id: systemdispatcher
    }
    function show_float_frame() {
        if (page.visible == true)
            page.visible = false;
        else if (page.visible == false)
            page.visible = true;
    }

    MouseArea {
        anchors.fill: parent
        acceptedButtons : Qt.RightButton
        onClicked: {
            if (page.visible == true)
                page.visible = false;
            page.focus = false;
        }
    }
    Style {
        color: "gray"
        transformOrigin: "Center"
        opacity: 0.97
        visible: true
        anchors.centerIn: parent
        width: 110; height: 150
    }
    Contents {
        id: search;
        visible: true
        opacity: 1
        anchors.centerIn: parent
    }
}
