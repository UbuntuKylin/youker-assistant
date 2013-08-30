import QtQuick 1.1
import SystemType 0.1
import SessionType 0.1
import "../common" as Common
import "../bars" as Bars

Rectangle {
    id:fcitxconfigtoolKey
    width: parent.width
    height: 475

    property string actiontitle: "小企鹅输入法快捷键/云输入/皮肤配置"
    property string actiontext: "可以设置自己喜欢的方式，点击＂下一步＂继续设置，点击＂取消＂取消当前设置并返回,点击“应用”按钮完成输入法设置。"
    property string selectedimage: ""
    property string defaultChangeMethod: ""
    property string eventABC:""
    property int hotkyScrollBetweenIndex: 0
    property string methodBtn1Tmp: ""
    property string methodBtn2Tmp:""
    property string prevpageBtn1Tmp: ""
    property string prevpageBtn2Tmp: ""
    property string nextpageBtn1Tmp: ""
    property string nextpageBtn2Tmp: ""
    //背景
    Image {
        source: "../../img/skin/bg-left.png"
        anchors.fill: parent
    }

    //温馨提示
    Column {
        spacing: 20
        anchors.top: parent.top
        anchors.topMargin: 44
        anchors.left: parent.left
        anchors.leftMargin: 80
        Text {
             text: fcitxconfigtoolKey.actiontitle
             font.bold: true
             font.pixelSize: 14
             color: "#383838"

         }
         Text {
             text: fcitxconfigtoolKey.actiontext
             font.pixelSize: 12
             color: "#7a7a7a"
         }
    }

    function refreshFcitxKey(){
        fcitxChangeModel.clear();
        skinModel.clear();
        //get_trigger_key========================================================
        var getMethodBtn1 = fcitxcfgwizard.get_trigger_key_first();

        methodBtn1.text = getMethodBtn1;

        var getMethodBtn2 = fcitxcfgwizard.get_trigger_key_second();
        methodBtn2.text = getMethodBtn2

        //get_prev_page_key======================================================
        var getPrevPageBtn1 = fcitxcfgwizard.get_prev_page_key_first();
        prevPageBtn1.text = getPrevPageBtn1;
        var getPrevPageBtn2 = fcitxcfgwizard.get_prev_page_key_second();
        prevPageBtn2.text = getPrevPageBtn2

        //get_next_page_key=======================================================
        var getNextpageBtn1 = fcitxcfgwizard.get_next_page_key_first();
        nextPageBtn1.text = getNextpageBtn1;
        var getNextpageBtn2 = fcitxcfgwizard.get_next_page_key_second();
        nextPageBtn2.text = getNextpageBtn2;

        //get_im_switch_key
        var getEnableHotKeybool =fcitxcfgwizard.get_im_switch_key();
        enableHotKeyBox.checked = getEnableHotKeybool;

        //set_im_switch_hot_key=======================================================
          var getHotkyScrollBetween = fcitxcfgwizard.get_im_switch_hot_key()
        if(getHotkyScrollBetween==0)
        {
            fcitxChangeModel.append({"text": "CTRL_SHIFT"});
            fcitxChangeModel.append({"text": "ALT_SHIFT"});
            fcitxChangeModel.append({"text": "CTRL_SUPER"});
            fcitxChangeModel.append({"text": "ALT_SUPER"});
        }
        if(getHotkyScrollBetween==1)
        {
            fcitxChangeModel.append({"text": "ALT_SHIFT"});
            fcitxChangeModel.append({"text": "CTRL_SHIFT"});
            fcitxChangeModel.append({"text": "CTRL_SUPER"});
            fcitxChangeModel.append({"text": "ALT_SUPER"});
        }
        if(getHotkyScrollBetween==2)
        {
            fcitxChangeModel.append({"text": "CTRL_SUPER"});
            fcitxChangeModel.append({"text": "CTRL_SHIFT"});
            fcitxChangeModel.append({"text": "ALT_SHIFT"});
            fcitxChangeModel.append({"text": "ALT_SUPER"});
        }
        if(getHotkyScrollBetween==3)
        {
            fcitxChangeModel.append({"text": "ALT_SUPER"});
            fcitxChangeModel.append({"text": "CTRL_SHIFT"});
            fcitxChangeModel.append({"text": "ALT_SHIFT"});
            fcitxChangeModel.append({"text": "CTRL_SUPER"});
        }

        //get_skin_list and current_skin=================================================
        var getSkinList = fcitxcfgwizard.get_all_skin_type()
        var getCurrentSkin = fcitxcfgwizard.get_skin_type()
        getSkinList.unshift(getCurrentSkin);
        skinModel.clear();
        for(var i=0;i<getSkinList.length;i++)
       {
            skinModel.append({"skinTitle": getSkinList[i]});
            if(i!=0&&(getSkinList[i] == getCurrentSkin))
                skinModel.remove(i);
        }
    }
    Connections {
            target: fcitxcfgwizard
            onRefreshFcitxSig: {
                refreshFcitxKey();
            }
        }
    Component.onCompleted: {
        fcitxChangeModel.clear();
        skinModel.clear();
        //get_trigger_key========================================================
        var getMethodBtn1 = fcitxcfgwizard.get_trigger_key_first();
        methodBtn1.text = getMethodBtn1;
        var getMethodBtn2 = fcitxcfgwizard.get_trigger_key_second();
        methodBtn2.text = getMethodBtn2

        //get_prev_page_key======================================================
        var getPrevPageBtn1 = fcitxcfgwizard.get_prev_page_key_first();
        prevPageBtn1.text = getPrevPageBtn1;
        var getPrevPageBtn2 = fcitxcfgwizard.get_prev_page_key_second();
        prevPageBtn2.text = getPrevPageBtn2

        //get_next_page_key=======================================================
        var getNextpageBtn1 = fcitxcfgwizard.get_next_page_key_first();
        nextPageBtn1.text = getNextpageBtn1;
        var getNextpageBtn2 = fcitxcfgwizard.get_next_page_key_second();
        nextPageBtn2.text = getNextpageBtn2;

        //get_im_switch_key
        var getEnableHotKeybool =fcitxcfgwizard.get_im_switch_key();
        enableHotKeyBox.checked = getEnableHotKeybool;

        //set_im_switch_hot_key=======================================================
          var getHotkyScrollBetween = fcitxcfgwizard.get_im_switch_hot_key()
        if(getHotkyScrollBetween==0)
        {
            fcitxChangeModel.append({"text": "CTRL_SHIFT"});
            fcitxChangeModel.append({"text": "ALT_SHIFT"});
            fcitxChangeModel.append({"text": "CTRL_SUPER"});
            fcitxChangeModel.append({"text": "ALT_SUPER"});
        }
        if(getHotkyScrollBetween==1)
        {
            fcitxChangeModel.append({"text": "ALT_SHIFT"});
            fcitxChangeModel.append({"text": "CTRL_SHIFT"});
            fcitxChangeModel.append({"text": "CTRL_SUPER"});
            fcitxChangeModel.append({"text": "ALT_SUPER"});
        }
        if(getHotkyScrollBetween==2)
        {
            fcitxChangeModel.append({"text": "CTRL_SUPER"});
            fcitxChangeModel.append({"text": "CTRL_SHIFT"});
            fcitxChangeModel.append({"text": "ALT_SHIFT"});
            fcitxChangeModel.append({"text": "ALT_SUPER"});
        }
        if(getHotkyScrollBetween==3)
        {
            fcitxChangeModel.append({"text": "ALT_SUPER"});
            fcitxChangeModel.append({"text": "CTRL_SHIFT"});
            fcitxChangeModel.append({"text": "ALT_SHIFT"});
            fcitxChangeModel.append({"text": "CTRL_SUPER"});
        }

        //get_skin_list and current_skin=================================================
        var getSkinList = fcitxcfgwizard.get_all_skin_type()
        var getCurrentSkin = fcitxcfgwizard.get_skin_type()
        getSkinList.unshift(getCurrentSkin);   //js将数组第一个添加unshift进来的
        skinModel.clear();
        for(var i=0;i<getSkinList.length;i++)
       {
            skinModel.append({"skinTitle": getSkinList[i]});
            if(i!=0&&(getSkinList[i] == getCurrentSkin))
                skinModel.remove(i);
        }

    }

    Column{
        anchors{
            top:parent.top
            topMargin: 110
            left:parent.left
            leftMargin: 80
        }
        spacing: 15
        //Trigger Input Method
        Row{
            spacing: 179
            Text{
                id:inputMethod
                text:qsTr("切换激活/非激活输入法")
            }
            Row{
                spacing: 5
                Common.Button{
                    id:methodBtn1
                    //focus:true

    //                text:""
                    //hoverimage: "button_normal.png"
                    width:200
                    height:30
                    onClicked: {
                        methodBtn1.forceActiveFocus();
                        methodBtn1.text = "请按下要设置的组合键";
                        console.log("methodBtn1");
                    }
                    onEntered:{
                        methodBtn1Tmp = methodBtn1.text
                        console.log(methodBtn1Tmp)
                    }
                    onExited: {
                        methodBtn1.text = methodBtn1Tmp
                        console.log(methodBtn1.text)
                    }
                    Keys.onPressed: {
                        console.log(event.modifiers);
                        console.log(event.nativeModifiers);
                        methodBtn1.text = fcitxcfgwizard.get_fcitx_hot_key_string(event.key, event.modifiers);
                        methodBtn1Tmp = methodBtn1.text;
                    }


                }

                Common.Button{
                    id:methodBtn2
                    //focus:true

                    //hoverimage:"button_normal.png"
    //                text:"Empty"
                    width:200
                    height:30
                    onClicked: {
                        methodBtn2.forceActiveFocus();
                        methodBtn2.text = "请按下要设置的组合键"
                        console.log("methodBtn2")
                    }
                    onEntered:{
                        methodBtn2Tmp = methodBtn2.text
                        console.log(methodBtn2Tmp)
                    }
                    onExited: {
                        methodBtn2.text = methodBtn2Tmp
                        console.log(methodBtn1.text)
                    }
                    Keys.onPressed: {
                        console.log(event.modifiers);
                        console.log(event.nativeModifiers);
                        methodBtn2.text = fcitxcfgwizard.get_fcitx_hot_key_string(event.key, event.modifiers);
                        methodBtn2Tmp = methodBtn2.text
                    }
                 }
            }
        }
        //Prev Page
        Row{
            spacing: 287
            Text {
                id: prevPage
                text: qsTr("上一页")
            }
            Row{
                spacing: 5
                Common.Button{
                    id:prevPageBtn1
                    width:200
                    height:30
                    onClicked: {
                        prevPageBtn1.forceActiveFocus();
                        prevPageBtn1.text = "请按下要设置的组合键"
                    }
                    onEntered:{
                        prevpageBtn1Tmp = prevPageBtn1.text
                    }
                    onExited: {
                        prevPageBtn1.text = prevpageBtn1Tmp
                    }
                    Keys.onPressed: {
                        prevPageBtn1.text = fcitxcfgwizard.get_fcitx_hot_key_string(event.key, event.modifiers);
                        prevpageBtn1Tmp = prevPageBtn1.text;
                    }
                }
                Common.Button{
                    id:prevPageBtn2
                    width:200
                    height:30
                    onClicked: {
                        prevPageBtn2.forceActiveFocus();
                        prevPageBtn2.text = "请按下要设置的组合键";
                    }
                    onEntered:{
                        prevpageBtn2Tmp = prevPageBtn2.text;
                    }
                    onExited: {
                        prevPageBtn2.text = prevpageBtn2Tmp;
                    }
                    Keys.onPressed: {
                        prevPageBtn2.text = fcitxcfgwizard.get_fcitx_hot_key_string(event.key, event.modifiers);
                        prevpageBtn2Tmp = prevPageBtn2.text;
                    }
                }
            }
        }
        //Next Page
        Row{
            spacing: 287
            Text {
                id: nextPage
                text: qsTr("下一页")
            }
            Row{
                spacing: 5
                Common.Button{
                    id:nextPageBtn1
                    width:200
                    height:30
                    onClicked: {
                        nextPageBtn1.forceActiveFocus();
                        nextPageBtn1.text = "请按下要设置的组合键";
                    }
                    onEntered:{
                        nextpageBtn1Tmp = nextPageBtn1.text;
                    }
                    onExited: {
                        nextPageBtn1.text = nextpageBtn1Tmp;
                    }
                    Keys.onPressed: {
                        nextPageBtn1.text = fcitxcfgwizard.get_fcitx_hot_key_string(event.key, event.modifiers);
                        nextpageBtn1Tmp = nextPageBtn1.text;
                    }
                }
                Common.Button{
                    id:nextPageBtn2
                    width:200
                    height:30
                    onClicked: {
                        nextPageBtn2.forceActiveFocus();
                        nextPageBtn2.text = "请按下要设置的组合键";
                    }
                    onEntered:{
                        nextpageBtn2Tmp = nextPageBtn2.text;
                    }
                    onExited: {
                        nextPageBtn2.text = nextpageBtn2Tmp;
                    }
                    Keys.onPressed: {
                        nextPageBtn2.text = fcitxcfgwizard.get_fcitx_hot_key_string(event.key, event.modifiers);
                        nextpageBtn2Tmp = nextPageBtn2.text;
                    }
                }
             }
        }
        Row{
            spacing: 272
            //选择皮肤
            ListModel {
                id: skinModel
                ListElement {skinTitle: "";}
            }
            Text{
                id:skinchoose
                text:qsTr("皮肤选择")
            }

            Common.ComboBox {
                id: skinCombo
                model: skinModel
                width: 405
                onSelectedTextChanged: {
//                    console.log(selectedText);
//                    skinCombo.selectedText
                }
            }
        }
        //Scroll between input Method
        Row{
            spacing: 256
            ListModel {
                id: fcitxChangeModel
                ListElement { text: "" }
            }
                Text{
                    id:scrollBetween
                    text:qsTr("输入法切换")
                }
                Common.ComboBox {
                    anchors{
                        verticalCenter: scrollBetween.verticalCenter
                    }
                    id: scrollBetweenCombo
                        model: fcitxChangeModel
                        width: 405
                        onSelectedTextChanged: {
                            hotkyScrollBetweenIndex = scrollBetweenCombo.selectedIndex;
                            console.log(hotkyScrollBetweenIndex);
                        }
                    }
            }

        Row{
            spacing: 213
            Text {
                id: hotkyScroll
                text: qsTr("启用输入法间切换")
            }
            Common.CheckBox{
                id:enableHotKeyBox
                anchors.verticalCenter: hotkyScroll.verticalCenter
                titleName: ""
            }
        }

        //启用云拼音
//        Row{
//        spacing: 258
//            Text {
//                id: cloudPinyin

//                text: qsTr("启用云拼音")
//            }
//            Common.CheckBox{
//                anchors.verticalCenter: cloudPinyin.verticalCenter
//                titleName: ""
//                onClicked: console.log("启用云拼音")
//            }
//        }
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
            console.log("aaaaaaaaa->");
            console.log(num);
            if (num == 0)
                pageStack.push(homepage)
            else if (num == 3)
                pageStack.push(systemset)
            else if (num == 4)
                pageStack.push(functioncollection)
        }
    }
    //底层工具栏
    Bars.FcitxThreeBar {
        id: toolBar
        height: 50; anchors.bottom: parent.bottom; width: parent.width; opacity: 0.9
//            button1Label: qsTr("退出")
//            button1Label: qsTr("返回")
//            button2Label: qsTr("应用")
        onCancelBtnClicked: {
            fcitxcfgwizard.send_fcitx_ok_warn();
        }
        onGobackBtnClicked: {
            console.log("上一步");
            pageStack.push(fcitxConfigtoolFontpage);//静态添加页面

        }
        onFinishBtnClicked: {
            //接后台应用接口
            console.log(" 应用");
            fcitxcfgwizard.set_trigger_key_first(methodBtn1.text,false);
            fcitxcfgwizard.set_trigger_key_second(methodBtn2.text,false);
            fcitxcfgwizard.set_prev_page_key_first(prevPageBtn1.text,false);
            fcitxcfgwizard.set_prev_page_key_second(prevPageBtn2.text,false);
            fcitxcfgwizard.set_next_page_key_first(nextPageBtn1.text,false);
            fcitxcfgwizard.set_next_page_key_second(nextPageBtn2.text,false);

            //fcitxcfgwizard.set_skin_type(skinCombo.selectedText,false);
            fcitxcfgwizard.set_skin_type(skinCombo.selectedText, false);

            fcitxcfgwizard.set_im_switch_hot_key(hotkyScrollBetweenIndex,false);
            fcitxcfgwizard.set_im_switch_key(enableHotKeyBox.checked,false);
            fcitxcfgwizard.all_cfg_save()
            pageStack.push(functioncollection);
        }

    }

}



