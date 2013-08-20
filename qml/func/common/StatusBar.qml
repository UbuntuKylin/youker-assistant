import QtQuick 1.1
import StyleItemType 0.1

Item {
    width: parent ? parent.width : 200
    height: 24
    StyleItem {
        anchors.fill: parent
        elementType: "statusbar"
    }
}
