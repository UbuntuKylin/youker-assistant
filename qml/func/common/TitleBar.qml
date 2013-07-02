import QtQuick 1.1

Item {
    id: titleBar
    property string btn_text: "一键清理"
    property string title: "一键清理系统垃圾，有效提高系统运行效率"
    property string description: "全面清理垃圾、痕迹、注册表，高效率解决系统清理问题"
    property string btn_flag: "one_key"
    BorderImage {
        source: "../../img/icons/unselect.png"
        width: parent.width
        height: parent.height + 14
        y: -7
    }
    Row {
        anchors.fill: parent
        anchors.left: parent.left
        anchors.leftMargin: 30
        spacing: 30
        Column {
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width - 150
            spacing: 2
            Text {
                text: qsTr(title)
                color: "black"
                font.pixelSize: 16
                /*; font.bold: true; elide: Text.ElideRight; style: Text.Raised; styleColor: "black" */
            }
            Text {
                text: qsTr(description)
                color: "gray"
                font.pixelSize: 14
                /*; elide: Text.ElideLeft; color: "gray"; style: Text.Raised; styleColor: "black" */
            }
        }
        Button {
            id: bitButton
            width: 95
            height: 32
            text: btn_text
            onClicked: {
                //kobe: wait for adding function
                if (btn_flag == "one_key") {
                    console.log("one_key");
                }
                else if (btn_flag == "rubbish") {
                    console.log("rubbish");
                }
                else if (btn_flag == "plugins") {
                    console.log("plugins");
                    pageStack.pop();
//                    pageStack.push(pluginlist);
                    pageStack.push(Qt.resolvedUrl("PluginList.qml"));
                }
                else if (btn_flag == "traces") {
                    console.log("traces");
                }
            }
            anchors.verticalCenter: parent.verticalCenter
        }

    }
}


//Item {
//    id: titleBar
//    property string btn_text: "一键清理"
//    property string title: "一键清理系统垃圾，有效提高系统运行效率"
//    property string description: "全面清理垃圾、痕迹、注册表，高效率解决系统清理问题"
//    BorderImage {
//        source: "../img/icons/unselect.png"
//        width: parent.width
//        height: parent.height + 14
//        y: -7
//    }
//    Item {
//        width: (parent.width * 2) - 55
//        height: parent.height
////        Row {
////            spacing: 5
////            Image {
////                source: "../img/icons/kysoft.png"
////            }

//            Column {
//                anchors.verticalCenter: parent.verticalCenter
//                x: 30; width: parent.width; spacing: 2
//                Text { text: qsTr(title); color: "black"; width: parent.width; font.pixelSize: 16/*; font.bold: true; elide: Text.ElideRight; style: Text.Raised; styleColor: "black" */}
//                Text { text: qsTr(description); color: "gray"; width: parent.width; font.pixelSize: 14/*; elide: Text.ElideLeft; color: "gray"; style: Text.Raised; styleColor: "black" */}
//            }
////        }
//        Button {
//            id: bitButton
//            x: titleBar.width - 100
//            width: 95; height: 32
//            text: btn_text
//            onClicked: {
//                //kobe: wait for adding function
//            }
//            anchors.verticalCenter: parent.verticalCenter
//        }
//    }
//}
