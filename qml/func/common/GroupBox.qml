import QtQuick 1.1
import "private" as Private
import StyleItemType 0.1
Private.GroupBox {
    id: groupbox
    implicitWidth: Math.max(200, contentWidth + backgroundItem.implicitWidth)
    implicitHeight: contentHeight + backgroundItem.implicitHeight + 4
    property bool flat: false
    background : StyleItem {
        id: styleitem
        elementType: "groupbox"
        anchors.fill: parent
        text: groupbox.title
        hover: checkbox.containsMouse
        on: checkbox.checked
        hasFocus: checkbox.activeFocus
        activeControl: checkable ? "checkbox" : ""
        sunken: !flat
        contentHeight:  (title.length > 0 || checkable) ? 24 : 4
    }
}
