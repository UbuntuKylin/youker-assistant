import QtQuick 1.1
import SystemType 0.1
import SessionType 0.1
import FcitxCfgWizard 0.1
import "../common" as Common
import "../bars" as Bars
import "../../func"  as Func

Rectangle {

    id:fcitxconfigtool
    width: parent.width
    height: 475
    property string actiontitle: qsTr("Fcitx list configuration")//小企鹅输入法列表配置
    property string actiontext: qsTr("Set the input mode you like, click 'next' to continue setup, click 'Cancel' cancel the current settings and return.")//可以设置自己喜欢的输入方式，点击＂下一步＂继续设置，点击＂取消＂撤销当前设置并返回。
    property string selectedimage: ""
    property int leftFcitxModelindex: 0
    property int rightFcitxModelindex: 0
    property int leftNum: 0
    property int rightNum:0
    property string m_separator: "<5|13)"
    property int hotkyScrollBetweenIndex: 0
    //背景
    Image {
        source: "../../img/skin/bg-left.png"
        anchors.fill: parent
    }

    //温馨提示
    Column {
        spacing: 10
        anchors.top: parent.top
        anchors.topMargin: 44
        anchors.left: parent.left
        anchors.leftMargin: 80
        Text {
             text: fcitxconfigtool.actiontitle
             font.bold: true
             font.pixelSize: 14
             color: "#383838"
         }
         Text {
             width: fcitxconfigtool.width - 80 - 20
             text: fcitxconfigtool.actiontext
             wrapMode: Text.WordWrap
             font.pixelSize: 12
             color: "#7a7a7a"
         }
    }

    function returnUnneed_data()
    {
        var returnUnneed_list = new Array
        leftFcitxModelindex = 0;
        rightFcitxModelindex = 0;
        for(var i=0;i<leftNum;i++)
        {
            returnUnneed_list.push(leftFcitxModel.get(leftFcitxModelindex).itemTitle+m_separator+
                                   leftFcitxModel.get(leftFcitxModelindex).uniqueName+m_separator+
                                   leftFcitxModel.get(leftFcitxModelindex).langClde+m_separator+"true")
          leftFcitxModelindex++;
        }
        for(var i=0;i<rightNum;i++)
        {
            returnUnneed_list.push(rightFcitxModel.get(rightFcitxModelindex).itemTitle+m_separator+
                                   rightFcitxModel.get(rightFcitxModelindex).uniqueName+m_separator+
                                   rightFcitxModel.get(rightFcitxModelindex).langClde+m_separator+"flase")
            rightFcitxModelindex++;
        }
        leftFcitxModelindex = 0;
        rightFcitxModelindex = 0;
//        console.log(leftNum+rightNum);//524
        return returnUnneed_list;

    }

    function refreshFcitxtool(){
        leftFcitxModel.clear();
        rightFcitxModel.clear();
        fcitxChangeModel.clear();
        leftFcitxModelindex = 0;
        rightFcitxModelindex = 0;
        leftNum = 0;
        rightNum = 0;
        var unneed_data = fcitxcfgwizard.get_im_list();
        if (unneed_data == "" || unneed_data.length == 0)
        unneed_data = fcitxcfgwizard.get_im_list();
        for (var i=0; i< unneed_data.length; i++) {
        var chooseList = unneed_data[i].split(m_separator);
        if(chooseList[3]=="true")
        {
            leftNum++;
            leftFcitxModel.append({"itemTitle": chooseList[0],"uniqueName":chooseList[1],"langClde":chooseList[2]});
        }
        else{
            rightNum++;
            rightFcitxModel.append({"itemTitle": chooseList[0],"uniqueName":chooseList[1],"langClde":chooseList[2]});
        }
        }
        //get_im_switch_key
        var getEnableHotKeybool =fcitxcfgwizard.get_im_switch_key();
        enableHotKeyBox.checked = getEnableHotKeybool;

        var getHotkyScrollBetween = fcitxcfgwizard.get_im_switch_hot_key()
        if(getHotkyScrollBetween==0)
        {
            fcitxChangeModel.append({"text": "CTRL+SHIFT"});
            fcitxChangeModel.append({"text": "ALT+SHIFT"});
            fcitxChangeModel.append({"text": "CTRL+SUPER"});
            fcitxChangeModel.append({"text": "ALT+SUPER"});
        }
        if(getHotkyScrollBetween==1)
        {
            fcitxChangeModel.append({"text": "ALT+SHIFT"});
            fcitxChangeModel.append({"text": "CTRL+SHIFT"});
            fcitxChangeModel.append({"text": "CTRL+SUPER"});
            fcitxChangeModel.append({"text": "ALT+SUPER"});
        }
        if(getHotkyScrollBetween==2)
        {
            fcitxChangeModel.append({"text": "CTRL+SUPER"});
            fcitxChangeModel.append({"text": "CTRL+SHIFT"});
            fcitxChangeModel.append({"text": "ALT+SHIFT"});
            fcitxChangeModel.append({"text": "ALT+SUPER"});
        }
        if(getHotkyScrollBetween==3)
        {
            fcitxChangeModel.append({"text": "ALT+SUPER"});
            fcitxChangeModel.append({"text": "CTRL+SHIFT"});
            fcitxChangeModel.append({"text": "ALT+SHIFT"});
            fcitxChangeModel.append({"text": "CTRL+SUPER"});
        }
}
    Connections {
            target: fcitxcfgwizard
            onRefreshFcitxSig: {
                refreshFcitxtool();
                pageStack.push(functioncollection);
            }
        }

    Component.onCompleted: {
              refreshFcitxtool();
            }

    Text {
        id:currentMethod
        anchors {
            top: parent.top
            topMargin: 110
            left: parent.left
            leftMargin: 80
        }
        text: qsTr("Current input method")//当前的输入法
        font.bold: true
        font.pixelSize: 12
        color: "#7a7a7a"
    }
    Text {
        id:choseMethod
        anchors {
            top: parent.top
            topMargin: 110
            left: parent.left
            leftMargin: 475
        }
        text: qsTr("Available input method")//可用的输入法
        font.bold: true
        font.pixelSize: 12
        color: "#7a7a7a"
    }

    ListModel {
        id: leftFcitxModel
    }


    ListModel {
        id: rightFcitxModel
    }
    //左边框
    Rectangle{
        id:leftRectangle
        border.color: "#b9c5cc"
        width: 300; height: 230
        clip:true    //?
        anchors {
            top: parent.top
            topMargin: 130
            left: parent.left
            leftMargin: 80
        }
        Component{
            id:leftDelegat
            Item{
                id:wrapper
                width:350; height: 30
                Text{
                    id:listtext
                    anchors {
                        left: parent.left
                        leftMargin: 10
                        verticalCenter: parent.verticalCenter
                    }
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    text:itemTitle
                }
                Text{
                    id:listtext2
                    anchors {
                        left: listtext.right
                        leftMargin: 10
                        verticalCenter: parent.verticalCenter
                    }
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    text:uniqueName
                }
                Text{
                    id:listtext3
                    anchors {
                        left: listtext2.right
                        leftMargin: 10
                        verticalCenter: parent.verticalCenter
                    }
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    text:langClde
                }
                MouseArea{
                    anchors.fill:parent
                    hoverEnabled: true
                    onClicked: {
                        upBtn.enabled = true
                      wrapper.ListView.view.currentIndex = index; //?
                        leftFcitxModelindex = wrapper.ListView.view.currentIndex;
                        if(leftFcitxModelindex==0)
                        {
                             upBtn.enabled = false;
                        }
                        else
                        {
                             upBtn.enabled = true;
                        }
                        if(leftFcitxModelindex==leftNum-1)
                        {
                            downBtn.enabled = false;
                        }
                        else
                        {
                            downBtn.enabled = true;
                        }
                    }
                }

            }
        }

        Common.ScrollArea {
            frame:false
            anchors{
                top:parent.top
                topMargin: 1
                left:parent.left
                leftMargin: 1
            }
            height: parent.height-1
            width: parent.width-1
            Item {
                width: parent.width
                height: leftNum * 30 //列表长度
                //垃圾清理显示内容
                ListView{
                    id:leftLisv
                    anchors.fill: parent
                    model: leftFcitxModel
                    delegate: leftDelegat
                    highlight: Rectangle{width: 340;height: 30 ; color: "lightsteelblue"}
                    focus:true
                }
            }//Item
        }//ScrollArea

//        ListView{
//            id:leftLisv
//            anchors.fill: parent
//            model: leftFcitxModel
//            delegate: leftDelegat
//            highlight: Rectangle{width: 340;height: 30 ; color: "lightsteelblue"}
//            focus:true
//        }

//        Rectangle{
//            id:leftScrollbar
//            anchors.right: parent.right
//            anchors.rightMargin: -1
//            height: parent.height
////            z:scrollbar_z
//            width:11
//            color: "lightgrey"
//        }
//        Rectangle{
//            id: leftButton
//            anchors.right: parent.right
//            anchors.rightMargin: 0
//            width: 10
//            y: leftLisv.visibleArea.yPosition * leftScrollbar.height    //?
//            height: leftLisv.visibleArea.heightRatio * leftScrollbar.height; //?
//            radius: 3
//            smooth: true
//            color: "white"
//            border.color: "lightgrey"
//            Column{
//                anchors.verticalCenter: parent.verticalCenter
//                anchors.horizontalCenter: parent.horizontalCenter
//                spacing: 2
//                Rectangle{
//                    width: 8;height: 1
//                    color: "lightgrey"
//                }
//                Rectangle{
//                    width: 8;height: 1
//                    color: "lightgrey"
//                }
//                Rectangle{
//                    width: 8;height: 1
//                    color: "lightgrey"
//                }
//            }
//            MouseArea {
//                id: mousearea
//                anchors.fill: leftButton
//                drag.target: leftButton
//                drag.axis: Drag.YAxis
//                drag.minimumY: 0
//                drag.maximumY: leftScrollbar.height - leftButton.height
//                onMouseYChanged: {
//                    leftLisv.contentY = leftButton.y / leftScrollbar.height * leftLisv.contentHeight //?
//                }
//            }
//        }
    }

  //  右边框
    Rectangle{
        anchors{
            top:parent.top
            topMargin: 129
            left:parent.left
            leftMargin: 475
        }
        width:300
        height:2
        color:"#e4f2fb"
    }
    Column{
        id:rightColum
        anchors {
            top: parent.top
            topMargin: 130
            left: parent.left
            leftMargin: 475
        }
        spacing: 10
        Rectangle{
            id:rightRectangle
            border.color: "#b9c5cc"
            width: 300; height: 230
            clip:true
            Component{
                id:rightDelegat
                Item{
                    id:wrapper
                    state: "transparentColor"
                    width: 280; height: 30
                    Text{
                        id:listtext
                        anchors {
                            left: parent.left
                            leftMargin: 10
                            verticalCenter: parent.verticalCenter
                        }
                        font.pixelSize: 12
                        color: "#7a7a7a"
                        text:itemTitle
                    }
                    Text{
                        id:listtext2
                        anchors {
                            left: listtext.right
                            leftMargin: 10
                            verticalCenter: parent.verticalCenter
                        }
                        font.pixelSize: 12
                        color: "#7a7a7a"
                        text:uniqueName
                    }
                    Text{
                        width: 20
                        id:listtext3
                        anchors {
                            left: listtext2.right
                            leftMargin: 10
                            verticalCenter: parent.verticalCenter
                        }
                        font.pixelSize: 12
                        color: "#7a7a7a"
                        text:langClde
                    }
                    MouseArea{
                        anchors.fill:parent
                        hoverEnabled: true
                        onClicked: {
                            wrapper.ListView.view.currentIndex = index; //?
                            rightFcitxModelindex = index;

                        }
                    }
                }
            }

            Common.ScrollArea {
                frame:false
                anchors{
                    top:parent.top
                    topMargin: 1
                    left:parent.left
                    leftMargin: 1
                }
                height: parent.height-1
                width: parent.width-1
                Item {
                    width: parent.width
                    height: rightNum * 30 //列表长度
                    //垃圾清理显示内容
                    ListView{
                        id:rightLisv
                        anchors.fill: parent
                        model: rightFcitxModel
                        delegate: rightDelegat
                        highlightMoveSpeed: 9999999
                        highlight: Rectangle{width: 350;height: 30 ; color: "lightsteelblue"}
                    }
                }//Item
            }//ScrollArea

//            ListView{
//                id:rightLisv
//                anchors.fill: parent
//                model: rightFcitxModel
//                delegate: rightDelegat
//                highlightMoveSpeed: 9999999
//                highlight: Rectangle{width: 350;height: 30 ; color: "lightsteelblue"}
//            }

//            Rectangle{
//                id:rightscrollbar
//                anchors.right: parent.right
//                anchors.rightMargin: -1
//                height: parent.height
////                z:scrollbar_z
//                width:11
//                color: "lightgrey"
//            }
//            Rectangle{
//                id: rightbutton
//                anchors.right: parent.right
//                anchors.rightMargin: 0
//                width: 10
//                height:30
//                y: rightLisv.visibleArea.yPosition* (rightscrollbar.height-rightbutton.height)   //?
//         //       height: rightLisv.visibleArea.heightRatio * rightscrollbar.height; //?
//                radius: 3
//                smooth: true
//                color: "white"
//                border.color: "lightgrey"
//                Column{
//                    anchors.verticalCenter: parent.verticalCenter
//                    anchors.horizontalCenter: parent.horizontalCenter
//                    spacing: 2
//                    Rectangle{
//                        width: 8;height: 1
//                        color: "lightgrey"
//                    }
//                    Rectangle{
//                        width: 8;height: 1
//                        color: "lightgrey"
//                    }
//                    Rectangle{
//                        width: 8;height: 1
//                        color: "lightgrey"
//                    }
//                }
//                MouseArea {
//                    id: rightmousearea
//                    anchors.fill: rightbutton
//                    drag.target: rightbutton
//                    drag.axis: Drag.YAxis
//                    drag.minimumY: 0
//                    drag.maximumY: rightscrollbar.height - rightbutton.height
//                    onMouseYChanged: {
////                        console.log(rightbutton.y)
////                        console.log(rightLisv.visibleArea.yPosition)
////                        console.log(rightLisv.contentY)
////                        console.log(rightscrollbar.height)
////                        console.log(rightLisv.contentHeight)
////                        console.log(rightLisv.visibleArea.heightRatio)
//                        rightLisv.contentY = (rightbutton.y / (rightscrollbar.height-30+(rightLisv.visibleArea.heightRatio * (rightscrollbar.height-30)))* rightLisv.contentHeight)

//                    }
//                }
//            }
        }
    }
    //Scroll between input Method
    Row{
        spacing: 120
        anchors {
            top: parent.top
            topMargin: 370
            left: parent.left
            leftMargin: 80
        }
        ListModel {
            id: fcitxChangeModel
        }

        Common.CheckBox{
            id:enableHotKeyBox
            anchors.verticalCenter: parent.verticalCenter
            onCheckedChanged: {
            }
            titleName: qsTr("Switch Inputmethod")//输入法切换
        }
        Common.ComboBox {
            anchors{
                verticalCenter: parent.verticalCenter
            }
            id: scrollBetweenCombo
            model: fcitxChangeModel
            width: 130
            height: 25
            onSelectedTextChanged: {
                    hotkyScrollBetweenIndex = scrollBetweenCombo.selectedIndex;
            }
        }
    }

    //提示
    Text {
        id:prompt
        anchors {
            top: parent.top
            topMargin: 398
            left: parent.left
            leftMargin: 80
        }
        text: qsTr("Tip: '<<' add available input method, '>>'delete the currently selected input method, '▲ ▼'change the current position.")//提示:'<<'可以将可用输入法加入当前输入法，'>>'删除当前选中输入法，'▲'和'▼'改变当前输入法的位置。
        font.bold: true
        font.pixelSize: 12
        color: "#7a7a7a"
    }
    //ctrl_key
    Column{
        spacing: 20
        anchors{
         top:parent.top
         topMargin: 162
         left: parent.left
         leftMargin:405

    }
        Common.Button{
            id:addBtn
            width:49
            height:27
            hoverimage: "blue5.png"
            text:"<<"
            fontcolor: "#6a97b4"
            onClicked: {
                leftFcitxModel.append({"itemTitle":rightFcitxModel.get(rightFcitxModelindex).itemTitle,
                                       "uniqueName" :rightFcitxModel.get(rightFcitxModelindex).uniqueName,
                                       "langClde" :rightFcitxModel.get(rightFcitxModelindex).langClde})
                rightFcitxModel.remove(rightFcitxModelindex);
                leftNum++;
                rightNum--;

                cutBtn.enabled = true;
                if((leftFcitxModelindex==0)&&(leftNum>1))
                downBtn.enabled = true;

            }
        }
        Common.Button{
            id:cutBtn
            width:49
            height:27
            text: ">>"
            fontcolor: "#6a97b4"
            hoverimage: "blue5.png"
            onClicked: {
                rightFcitxModel.append({"itemTitle":leftFcitxModel.get(leftFcitxModelindex).itemTitle,
                                       "uniqueName" :leftFcitxModel.get(leftFcitxModelindex).uniqueName,
                                        "langClde" :leftFcitxModel.get(leftFcitxModelindex).langClde})
                leftFcitxModel.remove(leftFcitxModelindex);
                leftNum--;
                rightNum++;

                if((leftFcitxModelindex==leftNum)&&(leftFcitxModelindex!=0))
                {
                    leftFcitxModelindex--;
                }
                if(leftFcitxModelindex==0)
                {
                    leftFcitxModelindex =0;
                }
                if(leftNum==0)
                {
                    cutBtn.enabled = false;
                    upBtn.enabled = false;
                    downBtn.enabled = false;
                }
            }
        }
        Common.Button{
            id:upBtn
            width:49
            height:27
            enabled: false
            text:"▲"
            fontcolor: "#6a97b4"
            hoverimage: "blue5.png"
            onClicked: {
                if(leftFcitxModelindex==0)
                {
                    upBtn.enabled = false
                }
                if(leftFcitxModelindex>0)
                {
                    downBtn.enabled = true
                    leftFcitxModel.move(leftFcitxModelindex,leftFcitxModelindex-1,1)
                    leftFcitxModelindex=leftFcitxModelindex-1;
                    if((leftFcitxModelindex==0)||(leftNum == 0))
                    {
                        upBtn.enabled = false
                    }

                }

            }
        }
        Common.Button{
            id:downBtn
            width:49
            height:27
            text: "▼"
            fontcolor: "#6a97b4"
            hoverimage: "blue5.png"
            onClicked: {
                if((leftFcitxModelindex==leftNum-1)||(leftNum==0))
                {
                    downBtn.enabled = false;
                }
                if(leftFcitxModelindex<leftNum-1)
                {
                    upBtn.enabled = true;
                    leftFcitxModel.move(leftFcitxModelindex,leftFcitxModelindex+1,1)
                    leftFcitxModelindex=leftFcitxModelindex+1;

                    if((leftFcitxModelindex==leftNum-1)||(leftNum==0))
                    {
                        downBtn.enabled = false

                    }
                }
            }
        }
    }
    //顶层工具栏
    Bars.TopBar {
        id: topBar
        width: 28
        height: 26
        anchors.top: parent.top
        anchors.topMargin: 40
        anchors.left: parent.left
        anchors.leftMargin: 40
        opacity: 0.9
        onButtonClicked: {
            var num = sessiondispatcher.get_page_num();
            if (num == 0)
                pageStack.push(homepage)
            else if (num == 3)
                pageStack.push(systemset)
            else if (num == 4)
                pageStack.push(functioncollection)
        }
    }

    //底层工具栏
    Bars.FcitxBar{
        id: toolBar
        height: 50; anchors.bottom: parent.bottom; width: parent.width; opacity: 0.9
//            button1Label: qsTr("取消")
//            button2Label: qsTr("上一步")
//            button3Label: qsTr("下一步")
        onCancelBtnClicked: {
            fcitxcfgwizard.send_fcitx_ok_warn(mainwindow.x, mainwindow.y);
        }
        onGobackBtnClicked: {
                pageStack.push(functioncollection)
        }
        onContinueBtnClicked: {         
            pageStack.push(fcitxConfigtoolFontpage);//静态添加页
            fcitxcfgwizard.set_im_list(returnUnneed_data(),false);
            fcitxcfgwizard.set_im_switch_hot_key(hotkyScrollBetweenIndex,false);
            fcitxcfgwizard.set_im_switch_key(enableHotKeyBox.checked,false);

        }
    }
}

