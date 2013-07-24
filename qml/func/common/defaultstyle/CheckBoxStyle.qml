import QtQuick 1.1

QtObject {
    property int minimumWidth: 13//32
    property int minimumHeight: 13//32

    property Component background:
    Component {
        Item {
            width: minimumWidth; height: minimumHeight
            opacity: enabled ? 1 : 0.7
            Rectangle { // Background center fill
                anchors.fill: parent
                anchors.margins: 1
                radius: 5
                color: backgroundColor
            }
            BorderImage {
                anchors.fill: parent
//                source: "../../../img/icons/lineedit_normal.png"
                source: "../../../img/icons/checkbox-0.png"
                smooth: true
                border.left: 6; border.top: 3
                border.right: 6; border.bottom: 3
            }
        }
    }

    property Component checkmark: Component {
        Image {
//            source: "../../../img/icons/checkbox_check.png"
            source: "../../../img/icons/checkbox.png"
            anchors.verticalCenterOffset: 1
            anchors.horizontalCenterOffset: 1
            anchors.centerIn: parent
            opacity: (!enabled && checked) || pressed == true ? 0.5 : (!checked ? 0 : 1)
            Behavior on opacity { NumberAnimation { duration: 150; easing.type: Easing.OutCubic } }
        }
    }

//    property Component checksomeone: Component {
//        Image {
//            source: "../../../img/icons/check.png"
//            anchors.verticalCenterOffset: 1
//            anchors.horizontalCenterOffset: 1
//            anchors.centerIn: parent
//            opacity: (!enabled && checked) || pressed == true ? 0.5 : (!checked ? 0 : 1)
//            Behavior on opacity { NumberAnimation { duration: 150; easing.type: Easing.OutCubic } }
//        }
//    }
}
