import QtQuick 1.1
import "../common" as Common
import "../bars" as Bars
import "../../func"  as Func

Rectangle {
    id:fcitxconfigtool
    width: parent.width
    height: 475
    property string actiontitle: qsTr("Input Method Configuration")//输入法配置
    property string actiontext: qsTr("'<<' '>>' button to add/remove input method, Up Arrow and Down Arrow keys to adjust the input method priority, click 'Next' to continue Settings, click 'Cancel' to exit the setup wizard.")//＇<<＇和＇>>＇按钮添加/删除输入法，＇▲＇和＇▼＇按钮调整输入法优先级，点击＂下一步＂继续设置，点击＂取消＂退出设置向导。
    property string selectedimage: ""
    property int leftFcitxModelindex: 0
    property int rightFcitxModelindex: 0
    property int leftNum: 0
    property int rightNum:0
    property string m_separator: "<5|13)"
    property int hotkyScrollBetweenIndex: 0
    //背景
    Image {
        source: "../../img/skin/bg-middle.png"
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
        text: qsTr("Current input method list")//当前输入法列表
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
        text: qsTr("Available input method list")//可用输入法列表
        font.bold: true
        font.pixelSize: 12
        color: "#7a7a7a"
    }

    ListModel { id: leftFcitxModel }
    ListModel { id: rightFcitxModel }
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
            titleName: qsTr("Switch input method")//输入法切换
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
            hoverimage: "blue.png"
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
            hoverimage: "blue.png"
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
            hoverimage: "blue.png"
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
            hoverimage: "blue.png"
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
            if (num == 0) {
                pageStack.push(homepage);
            }
            else if (num == 3) {
                pageStack.push(systemset);
            }
            else if (num == 4) {
                pageStack.push(functioncollection);
            }
        }
    }

    //底层工具栏
    Bars.FcitxBar{
        id: toolBar
        height: 50; anchors.bottom: parent.bottom; width: parent.width; opacity: 0.9
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

