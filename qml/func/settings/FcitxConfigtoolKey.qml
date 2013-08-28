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
        getSkinList.unshift(getCurrentSkin);   //js
        skinModel.clear();
        for(var i=0;i<getSkinList.length;i++)
       {
            skinModel.append({"skinTitle": getSkinList[i]});
            if(i!=0&&(getSkinList[i] == getCurrentSkin))
                skinModel.remove(i);
        }
    }

    Component.onCompleted: {
        console.log("wuxiaoyi");
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
        getSkinList.unshift(getCurrentSkin);   //js
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
            Text{
                id:inputMethod
                text:qsTr("切换激活/非激活输入法")
            }
            Common.Button{
                id:methodBtn1
                //focus:true

//                text:""
                //hoverimage: "button_normal.png"
                anchors.left: inputMethod.right
                anchors.leftMargin: 179
                width:200
                height:30
                onClicked: {
                    methodBtn1.forceActiveFocus();
                    console.log("methodBtn1")
                }

                Keys.onPressed: {
                    console.log(event.modifiers);
                    console.log(event.nativeModifiers);
                    methodBtn1.text = fcitxcfgwizard.get_fcitx_hot_key_string(event.key, event.modifiers);
                }

            }

            Common.Button{
                id:methodBtn2
                //focus:true

                //hoverimage:"button_normal.png"
//                text:"Empty"
                anchors.left: methodBtn1.right
                anchors.leftMargin: 5
                width:200
                height:30
                onClicked: {
                    methodBtn2.forceActiveFocus();
                    console.log("methodBtn2")
                }

                Keys.onPressed: {
// 　　　　　　　　　　　  eventABC =               //如何将event.key转换成对应字符
                    //  methodBtn1.text ="";
                    //console.log(event.key);
                    console.log(event.modifiers);
                    console.log(event.nativeModifiers);
                    methodBtn2.text = fcitxcfgwizard.get_fcitx_hot_key_string(event.key, event.modifiers);
                }
            }
        }
        Row{
            Text {
                id: hotkyScroll

                text: qsTr("启用热键输入法之间滚动")
            }
            Common.CheckBox{
                id:enableHotKeyBox
                anchors.verticalCenter: hotkyScroll.verticalCenter
                anchors.left: hotkyScroll.right
                anchors.leftMargin: 170
                titleName: ""
                onClicked: console.log("启用热键输入法之间滚动")
            }
        }
        //Prev Page
        Row{
            Text {
                id: prevPage
                text: qsTr("上一页")
            }
            Common.Button{
                id:prevPageBtn1
                //hoverimage: "button_normal.png"
//                text:"-"
                anchors.left: prevPage.right
                anchors.leftMargin: 287
                width:200
                height:30
                onClicked: {
                    prevPageBtn1.forceActiveFocus();
                    console.log("methodBtn1")
                }

                Keys.onPressed: {
                    console.log(event.modifiers);
                    console.log(event.nativeModifiers);
                    prevPageBtn1.text = fcitxcfgwizard.get_fcitx_hot_key_string(event.key, event.modifiers);
                }
            }
            Common.Button{
                id:prevPageBtn2
                //hoverimage: "button_normal.png"
//                text:"UP"
                anchors.left: prevPageBtn1.right
                anchors.leftMargin: 5
                width:200
                height:30
                onClicked: {
                    prevPageBtn2.forceActiveFocus();
                    console.log("methodBtn1")
                }

                Keys.onPressed: {
                    console.log(event.modifiers);
                    console.log(event.nativeModifiers);
                    prevPageBtn2.text = fcitxcfgwizard.get_fcitx_hot_key_string(event.key, event.modifiers);
                }
            }
        }
        //Next Page
        Row{
            Text {
                id: nextPage
                text: qsTr("下一页")
            }
            Common.Button{
                id:nextPageBtn1
                //hoverimage: "button_normal.png"
//                text:"="
                anchors.left: nextPage.right
                anchors.leftMargin: 287
                width:200
                height:30
                onClicked: {
                    nextPageBtn1.forceActiveFocus();
                    console.log("methodBtn1")
                }

                Keys.onPressed: {
                    console.log(event.modifiers);
                    console.log(event.nativeModifiers);
                    nextPageBtn1.text = fcitxcfgwizard.get_fcitx_hot_key_string(event.key, event.modifiers);
                }
            }
            Common.Button{
                id:nextPageBtn2
                //hoverimage: "button_normal.png"
//                text:"DOWN"
                anchors.left: nextPageBtn1.right
                anchors.leftMargin: 5
                width:200
                height:30
                onClicked: {
                    nextPageBtn2.forceActiveFocus();
                    console.log("methodBtn1")
                }

                Keys.onPressed: {
                    console.log(event.modifiers);
                    console.log(event.nativeModifiers);
                    nextPageBtn2.text = fcitxcfgwizard.get_fcitx_hot_key_string(event.key, event.modifiers);
                }
            }

        }
        //Scroll between input Method
        ListModel {
            id: fcitxChangeModel
            ListElement { text: "" }
        }

        Row{
            Text{
                id:scrollBetween
                text:qsTr("输入法切换")
            }
            Common.ComboBox {
                anchors{
                    verticalCenter: scrollBetween.verticalCenter
                    left: scrollBetween.right
                    leftMargin: 256
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
                anchors{
                    left:skinchoose.left
                    leftMargin: 331

                }
                id: skinCombo
                model: skinModel
                width: 405
                onSelectedTextChanged: {
                    console.log(selectedText);
//                    skinCombo.selectedText
                }

            }
        }

        //启用热键输入法之间滚动

        //启用云拼音
//        Row{
//            Text {
//                id: cloudPinyin

//                text: qsTr("启用云拼音")
//            }
//            Common.CheckBox{
//                anchors.verticalCenter: cloudPinyin.verticalCenter
//                anchors.left: cloudPinyin.right
//                anchors.leftMargin: 258
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
            sessiondispatcher.send_warningdialog_msg("友情提示：", "是否确定取消设置！");
            pageStack.push(functioncollection)
            refreshFcitxKey();
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



