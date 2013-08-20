import QtQuick 1.1
import "private" as Private
import StyleItemType 0.1
// jb : Size should not depend on background, we should make it consistent

Private.CheckBox {
    id: radiobutton
    property string text
    property string styleHint

    implicitWidth: Math.max(120, backgroundItem.implicitWidth)
    implicitHeight: backgroundItem.implicitHeight

    background: StyleItem {
        elementType: "radiobutton"
        sunken: pressed
        on: checked || pressed
        hover: containsMouse
        enabled: radiobutton.enabled
        hasFocus: radiobutton.activeFocus
        hint: radiobutton.styleHint
        contentHeight: textitem.implicitHeight
        contentWidth: textitem.implicitWidth + indicatorWidth
        property int indicatorWidth: pixelMetric("indicatorwidth") + 2
        Text {
            id: textitem
            text: radiobutton.text
            anchors.left: parent.left
            anchors.leftMargin: parent.indicatorWidth
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            elide: Text.ElideRight
        }
    }
    Keys.onSpacePressed: {clicked(); checked = !checked; }
}

