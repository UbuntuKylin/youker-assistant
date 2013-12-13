import QtQuick 1.1
import "common" as Common

//Item {
//    id: listViewDelegate
//    property int itemHeight: 40
//    property string arrow: '../img/icons/arrow.png'
//    property bool expanded: true
////    property int heightMark:sub_num
//    //需要传值:
//    property string btn_flag
//    property ListModel sub_model
//    property int sub_num    //接收清理界面扫描出子项的个数
//    property int arrow_display: 0   //控制清理界面下拉图标显示还是透明的变量

//    property bool delegate_flag: false
//    //子项字体
//    property string subItemFontName: "Helvetica"
//    property int subItemFontSize: 10
//    property color subItemFontColor: "black"

//    //总控开关的初始值
//    property string main_check_value: "true"
////    property bool controlMain: true

//    signal checkchanged(bool checkchange);

//    property int check_num:sub_num   //记录子项个数，在确定总checkbox状态时需要的变量
//    property bool maincheck: false
//    property int arrow_num: 0
//    width: parent.width
//    property bool showNum: false
//    property string arrowFlag
////    signal arrowClicked(string cacheFlag, bool expand_flag);

//    Item {
//        id: delegate
//        property alias expandedItemCount: subItemRepeater.count
//        x: 5; y: 2
//        width: parent.width
//        height: headerItemRect.height + subItemsRect.height

//        //母项
//        //checkbox, picture and words
//        Row {
//            id: headerItemRect
//            x: 5; y: 2
//            width: parent.width
//            height: listViewDelegate.itemHeight
//            spacing: 15
//            Image {
//                id: arrow
//                fillMode: "PreserveAspectFit"
//                height: 28
//                width: 26
//                anchors.verticalCenter: parent.verticalCenter
//                source: listViewDelegate.arrow
//                opacity: arrow_display
//                //当鼠标点击后,箭头图片旋转90度
//                rotation: listViewDelegate.expanded ? 0 : -90
//                smooth: true
//                MouseArea {
//                    id: mouseRegion
//                    anchors.fill: parent
//                    onPressed: {
//                        expanded = !expanded;      //扫描出的子项是否下拉显示的控制变量
////                        listViewDelegate.arrowClicked(listViewDelegate.arrowFlag, listViewDelegate.expanded);//1210
//                        if(heightMark==listViewDelegate.sub_num){  //通过对heightMark的赋值来实现子项的下拉显示与收缩不显示
//                            heightMark=0;
//                        }
//                        else if(heightMark==0){
//                            heightMark=listViewDelegate.sub_num;
//                        }
//                    }
//                }
//            }
//            Common.MainCheckBox{
//                id:check
//                checked: mstatus//listViewDelegate.main_check_value//"true"
//                anchors.verticalCenter: parent.verticalCenter
////                checkedbool: listViewDelegate.controlMain
////                onClicked: {
////                    if(check.checkedbool) {
////                        listViewDelegate.checkchanged(true);
////                    }
////                    else {
////                        listViewDelegate.checkchanged(false);
////                    }
////                }
////                onSendMstatus: {
////                    check.checkedbool = status;
//////                    listViewDelegate.main_check_value = str;
//////                    listViewDelegate.checkchanged(status);
////                }
//            }

//            Image {
//                id: clearImage
//                fillMode: "PreserveAspectFit"
//                height: parent.height*0.9
//                source: picture
//                smooth: true
//            }

//            Column {
//                id: status_update_content
//                spacing: 5
//                anchors.verticalCenter: parent.verticalCenter
//                Row {
//                    spacing: 10
//                    Text {
//                        text: itemTitle
//                        font.pointSize: 11
//                        color: "black"
//                        anchors.verticalCenter: parent.verticalCenter
//                    }
//                    Common.Label {
//                        id: numLabel
//                        visible: listViewDelegate.showNum
//                        text: "[ " + listViewDelegate.sub_num + qsTr(" Items ]")
//                        font.pointSize: 11
//                        color: "black"
//                        anchors.verticalCenter: parent.verticalCenter
//                    }
//                }
//                Text {
//                    text: detailstr
//                    width: 600
//                    wrapMode: Text.WordWrap
//                    font.family: "URW Bookman L"
//                    font.pointSize: 9
//                    color: "gray"
//                }
//            }
//        }

//        //子项
//        Item {
//            id: subItemsRect
//            property int itemHeight: listViewDelegate.itemHeight
//            y: headerItemRect.height
//            width: 850
//            clip: true
//            //当高度需要扩展时,根据expandedItemCount数目和itemHeight高度去扩展
////            height: expanded ? delegate.expandedItemCount * itemHeight : 0
////            opacity: 1
//            height: delegate.expandedItemCount * itemHeight
//            opacity: listViewDelegate.expanded ? 1 : 0
//            ListView{
//                id: subItemRepeater
//                width: listViewDelegate.width
//                model: sub_model
//                delegate: ldelegate
//                anchors.fill: parent
//            }
//            Component{
//                id:ldelegate
//                CruftItem {
////                    exclusive: true//控制是否联动explicit : true
////                    explicit : true
//                    id: subListItem
//                    split_status: listViewDelegate.delegate_flag
//                    width: subItemsRect.width
//                    height: subItemsRect.itemHeight
//                    text: itemTitle
//                    descript: desc
//                    size_num: number
//                    //根据主checkbox的状态来更改所有子checkbox的状态：true、false
//                    checkbox_status: check.checkedbool//listViewDelegate.controlMain
//                    bgImage: ""
//                    fontName: listViewDelegate.subItemFontName
//                    fontSize: listViewDelegate.subItemFontSize
//                    fontColor: listViewDelegate.subItemFontColor
//                    btn_flag: listViewDelegate.btn_flag
//                    itemFlag: listViewDelegate.arrowFlag//ListItem.qml根据该值判断是apt还是soft
//                    onChange_num: {
//                        if(check_status==true)      //已经勾上的子项数量统计,check_num记录
//                            check_num=check_num+1;
//                        else
//                            check_num=check_num-1;

//                        if(sub_num!=0/*&&heightMark!=0*/){  //在扫描出子项并下拉显示了子项的前提下,根据已经勾上的子项个数确定总checkbox处于三种状态中的哪种
//                            if(check_num ==0)
//                                check.checked="false";
//                            else if(check_num ==sub_num)
//                                check.checked="true";
//                            else
//                                check.checked="mid";
//                        }
//                        if(check.checked == "true" || listViewDelegate.check_num > 0) {   //根据是否有勾选项给清理页面传值判断是否能进行清理工作
//                            listViewDelegate.checkchanged(true);
//                        }
//                        else {
//                            listViewDelegate.checkchanged(false);
//                        }
//                    }
//                }
//            }
//        }//子项Item
//    }
////    onControlMainChanged: {
////        if(listViewDelegate.controlMain) {
////            check.checkedbool = true;
////        }
////    }
//}





















Item {
    id: broswerDelegate
    property int itemHeight: 40
    property string arrow: '../img/icons/arrow.png'
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
        x: 5; y: 2
        width: parent.width
        height: headerItemRect.height + subItemsRect.height

        //母项
        //checkbox, picture and words
        Row {
            id: headerItemRect
            x: 5; y: 2
            width: parent.width
            height: broswerDelegate.itemHeight
            spacing: 15
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
                fillMode: "PreserveAspectFit"
                height: parent.height*0.9
                source: picture
                smooth: true
            }

            Column {
                id: status_update_content
                spacing: 5
                anchors.verticalCenter: parent.verticalCenter
                Row {
                    spacing: 10
                    Text {
                        text: itemTitle
                        font.pointSize: 11
                        color: "black"
                        anchors.verticalCenter: parent.verticalCenter
                    }
                    Common.Label {
                        id: numLabel
                        visible: broswerDelegate.showNum
                        text: "[ " + broswerDelegate.sub_num + qsTr(" Items ]")
                        font.pointSize: 11
                        color: "black"
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
                Text {
                    text: detailstr
                    width: 450
                    wrapMode: Text.WordWrap
                    font.family: "URW Bookman L"
                    font.pointSize: 9
                    color: "gray"
                }
            }

            Row {
                spacing: 15
                Row {
                    spacing: 20
                    Item {
                        id: resetBtn
                        visible: broswerDelegate.resetStatus//false
                        width: 60
                        height: 29
                        Text {
                            id:backText
                            height: 10
                            anchors.centerIn: parent
                            text: qsTr("Go back")//返回
                            font.pointSize: 10
                            color: "#318d11"
                        }
                        Rectangle {
                            id: btnImg
                            anchors.top: parent.bottom
                            anchors.horizontalCenter: parent.horizontalCenter
                            width: backText.width
                            height: 1
                            color: "transparent"
                        }
                        MouseArea {
                            hoverEnabled: true
                            anchors.fill: parent
                            onEntered: btnImg.color = "#318d11"
                            onPressed: btnImg.color = "#318d11"
                            onReleased: btnImg.color = "#318d11"
                            onExited: btnImg.color = "transparent"
                            onClicked: {
                                broswerDelegate.sendBrowserType(broswerDelegate.flag, "reset");
                            }
                        }
                    }
                    Item {
                        id: rescanBtn
                        visible: broswerDelegate.resetStatus//false
                        width: 49
                        height: 29
                        Text {
                            id:rescanText
                            height: 10
                            anchors.centerIn: parent
                            text: qsTr("Scan again")//重新扫描
                            font.pointSize: 10
                            color: "#318d11"
                        }
                        Rectangle {
                            id: btnImg2
                            anchors.top: parent.bottom
                            anchors.horizontalCenter: parent.horizontalCenter
                            width: rescanText.width
                            height: 1
                            color: "transparent"
                        }
                        MouseArea {
                            hoverEnabled: true
                            anchors.fill: parent
                            onEntered: btnImg2.color = "#318d11"
                            onPressed: btnImg2.color = "#318d11"
                            onReleased: btnImg2.color = "#318d11"
                            onExited: btnImg2.color = "transparent"
                            onClicked: {
                                broswerDelegate.sendBrowserType(broswerDelegate.flag, "rescan");
                            }
                        }
                    }
                }
                Common.Button {
                    id: scanBtn
                    width: 95
                    height: 30
                    hoverimage: "green2.png"
                    text: broswerDelegate.actionTitle
                    anchors.verticalCenter: parent.verticalCenter
                    onClicked: {
                        if(broswerDelegate.btn_flag == "cookies_scan") {
                            broswerDelegate.sendBrowserType(broswerDelegate.flag, "cookies_scan");
                        }
                        else if(broswerDelegate.btn_flag == "cookies_scanc") {
                            broswerDelegate.sendBrowserType(broswerDelegate.flag, "cookies_scanc");
                        }
                        else if(broswerDelegate.btn_flag == "cookies_work") {
                            itemtitle.sendBrowserType(broswerDelegate.flag, "cookies_work");
                        }
                        else if(broswerDelegate.btn_flag == "cookies_workc") {
                            broswerDelegate.sendBrowserType(broswerDelegate.flag, "cookies_workc");
                        }
                    }
                }
            }
        }

        //子项
        Item {
            id: subItemsRect
            property int itemHeight: broswerDelegate.itemHeight
            y: headerItemRect.height
            width: 850
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
                ListItems {
                    id: subListItem
                    split_status: broswerDelegate.delegate_flag
                    width: subItemsRect.width
                    height: subItemsRect.itemHeight
                    text: itemTitle
                    descript: desc
                    size_num: number
                    bgImage: ""
                    fontName: broswerDelegate.subItemFontName
                    fontSize: broswerDelegate.subItemFontSize
                    fontColor: broswerDelegate.subItemFontColor
                    browserFlag: broswerDelegate.flag
                }
            }
        }//子项Item
    }
}

