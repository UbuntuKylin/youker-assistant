import QtQuick 1.1
import "../common" as Common

Item {
    id: broswerDelegate
    property int itemHeight: 30
    property string arrow: '../../img/icons/arrow.png'
    property bool expanded: true
    property int heightMark:sub_num
    //需要传值:
    property string btn_flag
    property ListModel sub_model
    property int sub_num    //接收清理界面扫描出子项的个数
    property int arrow_display: 0   //控制清理界面下拉图标显示还是透明的变量

    property bool delegate_flag: false
    //子项字体
    property string subItemFontName: "Helvetica"
    property int subItemFontSize: 10
    property color subItemFontColor: "black"
    property int check_num:sub_num   //记录子项个数，在确定总checkbox状态时需要的变量
    property bool maincheck: false
    property int arrow_num: 0
    width: parent.width
    property bool showNum: false
    property string flag//决定是firefox还是chromium
    property string actionTitle//按钮上显示的扫描或者清理文字
    property bool resetStatus: false//是否显示返回和重新扫描按钮
    signal browserArrowClicked(string browserFlag, bool expand_flag);//点击伸缩按钮时告诉BrowserCookies.qml
    signal sendBrowserType(string browserFlag, string status);//browserFlag判断是firefox还是chromium，status判断是扫描还是清理

    Item {
        id: delegate
        property alias expandedItemCount: subItemRepeater.count
        x: 2; y: 2
        width: parent.width
        height: headerItemRect.height + subItemsRect.height

        //母项
        //checkbox, picture and words
        Item {
            x: 20; y: 2
            id: headerItemRect
            width: parent.width
            height: broswerDelegate.itemHeight
            Row {
                spacing: 15
                anchors {
                    left: parent.left
                    leftMargin: 5
                }
                Image {
                    id: arrow
                    fillMode: "PreserveAspectFit"
                    height: 28
                    width: 26
                    anchors.verticalCenter: parent.verticalCenter
                    source: broswerDelegate.arrow
                    opacity: arrow_display
                    //当鼠标点击后,箭头图片旋转90度
                    rotation: broswerDelegate.expanded ? 0 : -90
                    smooth: true
                    MouseArea {
                        id: mouseRegion
                        anchors.fill: parent
                        onPressed: {
                            expanded = !expanded;//扫描出的子项是否下拉显示的控制变量
                            broswerDelegate.browserArrowClicked(broswerDelegate.flag, broswerDelegate.expanded);//1210
                        }
                    }
                }

                Image {
                    id: clearImage
                    anchors.verticalCenter: parent.verticalCenter
                    fillMode: "PreserveAspectFit"
//                    height: parent.height*0.9
                    source: picture
                    smooth: true
                }

                Row {
                    spacing: 10
                    anchors.verticalCenter: parent.verticalCenter
                    Text {
                        text: itemTitle
                        font.pointSize: 11
                        color: "black"
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    Common.Label {
                        id: numLabel
                        visible: broswerDelegate.showNum
                        text: "[ " + broswerDelegate.sub_num + qsTr(" Items ]")// 个项目 ]
                        font.pointSize: 11
                        color: "black"
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
            }

//            Row {
//                anchors {
////                    left: parent.left
////                    leftMargin: 600
//                    right: parent.right
//                    rightMargin: 30
//                }
//                spacing: 20
            Common.StyleButton {
                id: resetBtn
                visible: broswerDelegate.resetStatus//false
                anchors {
                    left: parent.left
                    leftMargin: 580
                }
                anchors.verticalCenter: parent.verticalCenter
                wordname: qsTr("Back")//返回
                width: 40
                height: 20
                onClicked: {
                    broswerDelegate.sendBrowserType(broswerDelegate.flag, "reset");
                }
            }
            Common.StyleButton {
                id: rescanBtn
                visible: broswerDelegate.resetStatus//false
                anchors {
                    left: parent.left
                    leftMargin: 640
                }
                anchors.verticalCenter: parent.verticalCenter
                wordname: qsTr("Rescan")//重新扫描
                width: 40
                height: 20
                onClicked: {
                    broswerDelegate.sendBrowserType(broswerDelegate.flag, "rescan");
                }
            }
            Common.Button {
                id: scanBtn
                width: 94
                height: 29
                fontsize: 13
                hoverimage: "green.png"
                text: broswerDelegate.actionTitle
                anchors {
                    left: parent.left
                    leftMargin: 700
                }
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    if(broswerDelegate.btn_flag == "cookies_scan") {
                        broswerDelegate.sendBrowserType(broswerDelegate.flag, "cookies_scan");
                    }
                    else if(broswerDelegate.btn_flag == "cookies_scanc") {
                        broswerDelegate.sendBrowserType(broswerDelegate.flag, "cookies_scanc");
                    }
                    else if(broswerDelegate.btn_flag == "cookies_work") {
                        broswerDelegate.sendBrowserType(broswerDelegate.flag, "cookies_work");
                    }
                    else if(broswerDelegate.btn_flag == "cookies_workc") {
                        broswerDelegate.sendBrowserType(broswerDelegate.flag, "cookies_workc");
                    }
                }
            }
        }

        //子项
        Item {
            id: subItemsRect
            property int itemHeight: broswerDelegate.itemHeight
            y: headerItemRect.height + 20
            width: 850 - 2
            clip: true
            height: delegate.expandedItemCount * itemHeight
            opacity: broswerDelegate.expanded ? 1 : 0
            ListView{
                id: subItemRepeater
                width: broswerDelegate.width
                model: sub_model
                delegate: ldelegate
                anchors.fill: parent
            }
            Component{
                id:ldelegate
                CookiesItem {
                    id: subListItem
                    split_status: broswerDelegate.delegate_flag
                    width: subItemsRect.width
                    height: subItemsRect.itemHeight
                    text: itemTitle
                    descript: desc
                    size_num: number
                    item_index: index
                    fontName: broswerDelegate.subItemFontName
                    fontSize: broswerDelegate.subItemFontSize
                    fontColor: broswerDelegate.subItemFontColor
                    browserFlag: broswerDelegate.flag
                    onRefreshed: {
                        broswerDelegate.sendBrowserType(broswerDelegate.flag, "refresh");
                    }
                }
            }
        }//子项Item
    }
}

