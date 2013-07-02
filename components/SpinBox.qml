import QtQuick 1.1
import "custom" as Components

Components.SpinBox {
    id:spinbox

    property variant __upRect;
    property variant __downRect;
    property int __margin: (height -16)/2
    property string styleHint

    // Align height with button
    topMargin: __margin
    bottomMargin: __margin

    leftMargin:6
    rightMargin:6

    StyleItem {
        id:edititem
        elementType: "edit"
        visible: false
        contentWidth: 70
        contentHeight: 20
    }

    implicitWidth: edititem.implicitWidth
    implicitHeight: edititem.implicitHeight

    clip:false

    background: Item {
        anchors.fill: parent
        property variant __editRect

        Rectangle {
            id: editBackground
            x: __editRect.x - 1
            y: __editRect.y
            width: __editRect.width + 1
            height: __editRect.height
        }

        Item {
            id: focusFrame
            anchors.fill: editBackground
            visible: frameitem.styleHint("focuswidget")
            StyleItem {
                id: frameitem
                anchors.margins: -6
                anchors.leftMargin: -5
                anchors.rightMargin: -6
                anchors.fill: parent
                visible: spinbox.activeFocus
                elementType: "focusframe"
            }
        }

        function updateRect() {
            __upRect = styleitem.subControlRect("up");
            __downRect = styleitem.subControlRect("down");
            __editRect = styleitem.subControlRect("edit");
            spinbox.leftMargin = __editRect.x + 2
            spinbox.rightMargin = spinbox.width -__editRect.width - __editRect.x
        }

        Component.onCompleted: updateRect()
        onWidthChanged: updateRect()
        onHeightChanged: updateRect()

        StyleItem {
            id: styleitem
            anchors.fill: parent
            elementType: "spinbox"
            sunken: (downEnabled && downPressed) | (upEnabled && upPressed)
            hover: containsMouse
            hasFocus: spinbox.focus
            enabled: spinbox.enabled
            value: (upPressed ? 1 : 0)           |
                   (downPressed == 1 ? 1<<1 : 0) |
                   (upEnabled ? (1<<2) : 0)      |
                   (downEnabled == 1 ? (1<<3) : 0)
            hint: spinbox.styleHint
        }
    }

    up: Item {
        x: __upRect.x
        y: __upRect.y
        width: __upRect.width
        height: __upRect.height
    }

    down: Item {
        x: __downRect.x
        y: __downRect.y
        width: __downRect.width
        height: __downRect.height
    }
}
