import QtQuick 1.1

QtObject {
    property int minimumWidth: 13//32
    property int minimumHeight: 13//32

    property string styleflag: ""
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
//                source: "../../../img/icons/checkbox.png"
                source: {
                    if(styleflag == "radio")
                         "../../../img/icons/radiobox.png";
                    else if(styleflag == "flowradio")
                        "../../../img/icons/dot_normal.png";
                    else
                        "../../../img/icons/checkbox.png";
                }

//                source: (styleflag == "radio") ? "../../../img/icons/radiobox.png" : "../../../img/icons/checkbox.png"
                smooth: true
                border.left: 6; border.top: 3
                border.right: 6; border.bottom: 3
            }
        }
    }

    property Component checkmark: Component {
        Image {
//            source: "../../../img/icons/checkbox_seclect.png"
            source: {
                if(styleflag == "radio")
                     "../../../img/icons/radiobox-check.png";
                else if(styleflag == "flowradio")
                    "../../../img/icons/dot_active.png";
                else
                    "../../../img/icons/checkbox_seclect.png";
            }
//            source: (styleflag == "radio") ? "../../../img/icons/radiobox-check.png" : "../../../img/icons/checkbox_seclect.png"
//            anchors.verticalCenterOffset: 1
//            anchors.horizontalCenterOffset: 1
            anchors.centerIn: parent
            opacity: (!enabled && checked) || pressed == true ? 0.5 : (!checked ? 0 : 1)
            Behavior on opacity { NumberAnimation { duration: 150; easing.type: Easing.OutCubic } }
        }
    }
}
