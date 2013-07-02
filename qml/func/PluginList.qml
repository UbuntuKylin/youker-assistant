import QtQuick 1.1
import QtDesktop 0.1
import "common" as Common
Item {
    id: container
    width: parent.width
    height: parent.height
    // Subitem expansion duration
    property int animationDuration: 100
    // Subitem indentation
    property int indent: 20
    // Scrollbar width
    property int scrollBarWidth: 8
    // Background for list item
    property string bgImage: '../img/icons/list_item.png'
    // Background image for pressed list item
    property string bgImagePressed: '../img/icons/list_item_pressed.png'
    // Background image for active list item (currently not used)
    property string bgImageActive: '../img/icons/list_item_active.png'
    // Background image for subitem
    property string bgImageSubItem: "../img/icons/list_subitem.png"
    // Arrow indicator for item expansion
    property string arrow: '../img/icons/arrow.png'
    // Font properties for top level items
    property string headerItemFontName: "Helvetica"
    property int headerItemFontSize: 12
    property color headerItemFontColor: "black"
    // Font properties for  subitems
    property string subItemFontName: "Helvetica"
    property int subItemFontSize: headerItemFontSize-1
    property color subItemFontColor: "black"

    property string logoIcon: "../img/icons/settings.png"

    signal itemClicked(string itemTitle, string subItemTitle)



    //标题栏
//        Common.RotateTitleBar { id: titleBar; width: parent.width; height: 40; y: 80; opacity: 0.9 }
    //垃圾清理自定义标题栏
    Common.MyTitleBar {
        id: titleBar; width: parent.width; height: 45; opacity: 0.9
        btn_text: "开始扫描"
        title: "测试"
        description:  "test"
        btn_flag: "rubbish"}

    PluginListModel {
        id: mainModel
    }

    ListView {
        id: listView
        height: parent.height - titleBar.height
        anchors {
            left: parent.left
            right: parent.right

//            width: parent.width
            top: parent.top
            topMargin: titleBar.height
        }
        model: mainModel
        delegate: listViewDelegate
        focus: true
        spacing: 0
    }

    Component {
        id: listViewDelegate
        Item {
            id: delegate
            // Modify appearance from these properties
            property int itemHeight: 40
            property alias expandedItemCount: subItemRepeater.count

            // Flag to indicate if this delegate is expanded
            property bool expanded: false

            x: 0; y: 0;
            width: container.width
            height: headerItemRect.height + subItemsRect.height

            // Top level list item.
            ListItem {
                id: headerItemRect
                x: 0; y: 0
                width: parent.width
                height: parent.itemHeight
                text: itemTitle
                text1: itemTitle1
                icon_path: iconpath
                onClicked: expanded = !expanded

                bgImage: container.bgImage
                bgImagePressed: container.bgImagePressed
                bgImageActive: container.bgImageActive
                fontName: container.headerItemFontName
                fontSize: container.headerItemFontSize
                fontColor: container.headerItemFontColor
                fontBold: true

                // Arrow image indicating the state of expansion.
                Image {
                    id: arrow
                    fillMode: "PreserveAspectFit"
                    height: parent.height*0.3
                    source: container.arrow
                    rotation: expanded ? 90 : 0
                    smooth: true
                    anchors {
                        right: parent.right
                        verticalCenter: parent.verticalCenter
                        rightMargin: 10
                    }
                }
            }

            // Subitems are in a column whose height depends
            // on the expanded status. When not expandend, it is zero.
            Item {
                id: subItemsRect
                property int itemHeight: delegate.itemHeight

                y: headerItemRect.height
                width: parent.width
                height: expanded ? expandedItemCount * itemHeight : 0
                clip: true

                opacity: 1
                Behavior on height {
                    // Animate subitem expansion. After the final height is reached,
                    // ensure that it is visible to the user.
                    SequentialAnimation {
                        NumberAnimation { duration: container.animationDuration; easing.type: Easing.InOutQuad }
                    }
                }

                Column {
                    width: parent.width

                    // Repeater creates each sub-ListItem using attributes
                    // from the model.
                    Repeater {
                        id: subItemRepeater
                        model: attributes
                        width: subItemsRect.width

                        MyListItem {
                            id: subListItem
                            width: delegate.width
                            height: subItemsRect.itemHeight
                            text: subItemTitle
                            bgImage: container.bgImageSubItem
                            fontName: container.subItemFontName
                            fontSize: container.subItemFontSize
                            fontColor: container.subItemFontColor
                            textIndent: container.indent
                            onClicked: {
                            }
                        }
                    }
                }
            }
        }
    }
}




// Accordion list
//Item {
//    id: container

//    // Default width
//    width: parent.width
//    // Default height
//    height: parent.height
//    // Subitem expansion duration
//    property int animationDuration: 100
//    // Subitem indentation
//    property int indent: 20
//    // Scrollbar width
//    property int scrollBarWidth: 8
//    // Background for list item
//    property string bgImage: '../img/icons/list_item.png'
//    // Background image for pressed list item
//    property string bgImagePressed: '../img/icons/list_item_pressed.png'
//    // Background image for active list item (currently not used)
//    property string bgImageActive: '../img/icons/list_item_active.png'
//    // Background image for subitem
//    property string bgImageSubItem: "../img/icons/list_subitem.png"
//    // Arrow indicator for item expansion
//    property string arrow: '../img/icons/arrow.png'
//    // Font properties for top level items
//    property string headerItemFontName: "Helvetica"
//    property int headerItemFontSize: 12
//    property color headerItemFontColor: "black"
//    // Font properties for  subitems
//    property string subItemFontName: "Helvetica"
//    property int subItemFontSize: headerItemFontSize-1
//    property color subItemFontColor: "black"

//    signal itemClicked(string itemTitle, string subItemTitle)

//    PluginListModel {
//        id: mainModel
//    }

//    ListView {
//        id: listView
//        height: parent.height
//        anchors {
//            left: parent.left
//            right: parent.right
//        }
//        model: mainModel
//        delegate: listViewDelegate
//        focus: true
//        spacing: 0
//    }

//    Component {
//        id: listViewDelegate
//        Item {
//            id: delegate
//            // Modify appearance from these properties
//            property int itemHeight: 64
//            property alias expandedItemCount: subItemRepeater.count

//            // Flag to indicate if this delegate is expanded
//            property bool expanded: false

//            x: 0; y: 0;
//            width: container.width
//            height: headerItemRect.height + subItemsRect.height

//            // Top level list item.
//            MyListItem {
//                id: headerItemRect
//                x: 0; y: 0
//                width: parent.width
//                height: parent.itemHeight
//                text: itemTitle
//                onClicked: expanded = !expanded

//                bgImage: container.bgImage
//                bgImagePressed: container.bgImagePressed
//                bgImageActive: container.bgImageActive
//                fontName: container.headerItemFontName
//                fontSize: container.headerItemFontSize
//                fontColor: container.headerItemFontColor
//                fontBold: true

//                // Arrow image indicating the state of expansion.
//                Image {
//                    id: arrow
//                    fillMode: "PreserveAspectFit"
//                    height: parent.height*0.3
//                    source: container.arrow
//                    rotation: expanded ? 90 : 0
//                    smooth: true
//                    anchors {
//                        right: parent.right
//                        verticalCenter: parent.verticalCenter
//                        rightMargin: 10
//                    }
//                }
//            }

//            // Subitems are in a column whose height depends
//            // on the expanded status. When not expandend, it is zero.
//            Item {
//                id: subItemsRect
//                property int itemHeight: delegate.itemHeight

//                y: headerItemRect.height
//                width: parent.width
//                height: expanded ? expandedItemCount * itemHeight : 0
//                clip: true

//                opacity: 1
//                Behavior on height {
//                    // Animate subitem expansion. After the final height is reached,
//                    // ensure that it is visible to the user.
//                    SequentialAnimation {
//                        NumberAnimation { duration: container.animationDuration; easing.type: Easing.InOutQuad }
//                    }
//                }

//                Column {
//                    width: parent.width

//                    // Repeater creates each sub-ListItem using attributes
//                    // from the model.
//                    Repeater {
//                        id: subItemRepeater
//                        model: attributes
//                        width: subItemsRect.width

//                        MyListItem {
//                            id: subListItem
//                            width: delegate.width
//                            height: subItemsRect.itemHeight
//                            text: subItemTitle
//                            bgImage: container.bgImageSubItem
//                            fontName: container.subItemFontName
//                            fontSize: container.subItemFontSize
//                            fontColor: container.subItemFontColor
//                            textIndent: container.indent
//                            onClicked: {
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }
//}
