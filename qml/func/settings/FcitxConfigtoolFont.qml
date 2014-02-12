import QtQuick 1.1
import "../common" as Common
import "../bars" as Bars
import "../" as Func

Rectangle {
    id:fcitxconfigtoolFont
    width: parent.width
    height: 475

    property string actiontitle: qsTr("Personalized Configuration")//个性化配置
    property string actiontext: qsTr("Global configuration according to personal habits, click 'Next' to continue Settings, click 'Cancel' to exit the setup wizard.")//根据个人习惯进行全局配置，点击＂下一步＂继续设置，点击＂取消＂退出设置向导。
    property int scanModelIndex:1
    property int scrollbar_z: 1
    property int defaultCandidateWord:0     //恢复默认时用到
    property int defaultFontSize:0
    property int defaultFontStyle:0
    property int scanModelindex: 1
    property string fontFamily: ""
    property string methodBtn1Tmp: ""
    property string methodBtn2Tmp:""
    property string prevpageBtn1Tmp: ""
    property string prevpageBtn2Tmp: ""
    property string nextpageBtn1Tmp: ""
    property string nextpageBtn2Tmp: ""
    property string methodBtn1Buff: ""
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
             text: fcitxconfigtoolFont.actiontitle
             font.bold: true
             font.pixelSize: 14
             color: "#383838"
         }
         Text {
             width: fcitxconfigtoolFont.width - 80 - 20
             text: fcitxconfigtoolFont.actiontext
             wrapMode: Text.WordWrap
             font.pixelSize: 12
             color: "#7a7a7a"
         }
    }

    function refreshFcitxFont(){
        //get_vertical_list===================================================
        var getVerticalList = fcitxcfgwizard.get_vertical_list();
        verticalstyle.checked = getVerticalList

        //get candidate_word_numbe============================================
        var getFontcandidateWord =fcitxcfgwizard.get_candidate_word_number();
        candidateWordNumber.value = getFontcandidateWord;

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
    }
    Connections {
        target: fcitxcfgwizard
        onRefreshFcitxSig: {
            refreshFcitxFont();
        }
    }
    Component.onCompleted: {
        refreshFcitxFont();
    }

    Row{
        anchors{
            left: parent.left
            leftMargin: 40
            top: parent.top
            topMargin: 120

        }
        Text{
            id: showtitle
            text: qsTr("Display settings")//显示设置
            font.bold: true
            font.pixelSize: 12
            color: "#383838"
        }
        //横线
        Common.Separator {
            anchors.verticalCenter: parent.verticalCenter
            width: fcitxconfigtoolFont.width - showtitle.width - 40 * 2
        }
    }
    //显示设置
    Column{
        spacing: 10
        smooth: true
        anchors{
            top:parent.top
            topMargin: 160
            left:parent.left
            leftMargin: 65
        }
        Row{
            spacing: 30
            Text {
                id:listh
//                font.bold: true
                font.pixelSize: 12
                color: "#7a7a7a"
                text: qsTr("Candidate list: ")//候选词列表：
            }
            Common.ButtonRow {
                exclusive: true//控制是否联动
                spacing: 120
                anchors.centerIn: listh.Center
                Common.CheckBox {
                    id: levelstyle
                    checked: (fcitxcfgwizard.get_vertical_list() == false) ? true : false
                    titleName: qsTr("Horizontal display")//横向显示
                    flag: "radio"
                    onClicked: {}
                }
                Common.CheckBox {
                    id: verticalstyle
                    checked: (fcitxcfgwizard.get_vertical_list() == ture) ? true : false
                    titleName: qsTr("Vertical display")//竖向显示
                    flag: "radio"
                    onClicked: {}
                }
            }
        }

        //候选词
        Row{
            spacing: 30
            Text {
                id: numberText
                font.pixelSize: 12
                color: "#7a7a7a"
                text: qsTr("Candidate Word Number: ")//候选词个数：
                anchors.verticalCenter: parent.verticalCenter
            }
            Row{
                spacing: 10
                Common.Slider {
                    id: candidateWordNumber
                    anchors.verticalCenter: parent.verticalCenter
                    minimumValue: 1
                    maximumValue: 10
                    width: 140
                    stepSize: 1
                    animated: true
                }
                Text {
                    id: displaynum
                    text: candidateWordNumber.value
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
        }
    }
   //快捷键设置
    Row{
        anchors{
            left: parent.left
            leftMargin: 40
            top: parent.top
            topMargin: 250

        }
        Text{
            id: keyboardtitle
            text: qsTr("Hotkey")//快捷键
            font.bold: true
            font.pixelSize: 12
            color: "#383838"
            anchors.verticalCenter: parent.verticalCenter
        }
        Rectangle{
            width: fcitxconfigtoolFont.width - keyboardtitle.width - 40 * 2
            height:1
            color:"#b9c5cc"
            anchors.verticalCenter: parent.verticalCenter
        }
    }



    Text{
        id:inputMethod
        anchors{
            top:parent.top
            topMargin: 280
            left:parent.left
            leftMargin: 65
        }
        font.pixelSize: 12
        color: "#7a7a7a"
        text:qsTr("Trigger Input Method: ")//切换激活/非激活输入法：
        anchors.verticalCenter: parent.verticalCenter
    }
    Row{
        spacing: 5
        anchors{
            top:parent.top
            topMargin: 277
            left:parent.left
            leftMargin: 200
        }
        Common.Button{
            id:methodBtn1
            hoverimage: "fcitxKey.png"//../../img/icons/
            fontcolor:"#929292"
            fontsize: 13
            width:200
            height:30
            onClicked: {
                methodBtn1.forceActiveFocus();
                methodBtn1.text = qsTr("Please press the combination keys");//请按下要设置的组合键
            }
            onEntered:{
                methodBtn1Tmp = methodBtn1.text
            }
            onExited: {
                methodBtn1.text = methodBtn1Tmp
            }
            Keys.onPressed: {
                methodBtn1.text = fcitxcfgwizard.get_fcitx_hot_key_string(event.key, event.modifiers);
                methodBtn1Tmp = methodBtn1.text;
            }
        }
        Common.Button{
            id:methodBtn2
            hoverimage: "fcitxKey.png"//../../img/icons/
            fontcolor:"#929292"
            fontsize: 13
            width:200
            height:30
            onClicked: {
                methodBtn2.forceActiveFocus();
                methodBtn2.text = qsTr("Please press the combination keys");//请按下要设置的组合键
            }
            onEntered:{
                methodBtn2Tmp = methodBtn2.text
            }
            onExited: {
                methodBtn2.text = methodBtn2Tmp
            }
            Keys.onPressed: {
                methodBtn2.text = fcitxcfgwizard.get_fcitx_hot_key_string(event.key, event.modifiers);
                methodBtn2Tmp = methodBtn2.text
            }
         }
    }

    //Prev Page

    Text {
        id: prevPage
        anchors{
            top:parent.top
            topMargin: 325
            left:parent.left
            leftMargin: 65
        }
        font.pixelSize: 12
        color: "#7a7a7a"
        text: qsTr("Prev Page: ")//上一页：
        anchors.verticalCenter: parent.verticalCenter
    }
    Row{
        spacing: 5
        anchors{
            top:parent.top
            topMargin: 322
            left:parent.left
            leftMargin: 200
        }
        Common.Button{
            id:prevPageBtn1
            width:200
            height:30
            hoverimage: "fcitxKey.png"//../../img/icons/
            fontcolor:"#929292"
            fontsize: 13
            onClicked: {
                prevPageBtn1.forceActiveFocus();
                prevPageBtn1.text = qsTr("Please press the combination keys");//请按下要设置的组合键
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
            hoverimage: "fcitxKey.png"//../../img/icons/
            fontcolor:"#929292"
            fontsize: 13
            onClicked: {
                prevPageBtn2.forceActiveFocus();
                prevPageBtn2.text = qsTr("Please press the combination keys");//请按下要设置的组合键
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

        //Next Page

    Text {
        id: nextPage
        anchors{
            top:parent.top
            topMargin: 370
            left:parent.left
            leftMargin: 65
        }
        font.pixelSize: 12
        color: "#7a7a7a"
        text: qsTr("Next Page: ")//下一页：
        anchors.verticalCenter: parent.verticalCenter
    }
    Row{
        spacing: 5
        anchors{
            top:parent.top
            topMargin: 367
            left:parent.left
            leftMargin: 200
        }
        Common.Button{
            id:nextPageBtn1
            width:200
            height:30
            hoverimage: "fcitxKey.png"//../../img/icons/
            fontcolor:"#929292"
            fontsize: 13
            onClicked: {
                nextPageBtn1.forceActiveFocus();
                nextPageBtn1.text = qsTr("Please press the combination keys");//请按下要设置的组合键
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
            hoverimage: "fcitxKey.png"//../../img/icons/
            fontcolor:"#929292"
            fontsize: 13
            onClicked: {
                nextPageBtn2.forceActiveFocus();
                nextPageBtn2.text = qsTr("Please press the combination keys");//请按下要设置的组合键
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
    Bars.FcitxBar {
        id: toolBar
        height: 50; anchors.bottom: parent.bottom; width: parent.width; opacity: 0.9
        onCancelBtnClicked: {
            fcitxcfgwizard.send_fcitx_ok_warn(mainwindow.x, mainwindow.y);
        }

        onGobackBtnClicked: {
            pageStack.push(fcitxConfigtoolpage);//静态添加页面
        }
        onContinueBtnClicked: {
            pageStack.push(fcitxConfigtoolKeypage);//静态添加页面

            fcitxcfgwizard.set_candidate_word_number(candidateWordNumber.value,false);
            fcitxcfgwizard.set_vertical_list(verticalstyle.checked,false);

            fcitxcfgwizard.set_trigger_key_first(methodBtn1.text,false);
            fcitxcfgwizard.set_trigger_key_second(methodBtn2.text,false);
            fcitxcfgwizard.set_prev_page_key_first(prevPageBtn1.text,false);
            fcitxcfgwizard.set_prev_page_key_second(prevPageBtn2.text,false);
            fcitxcfgwizard.set_next_page_key_first(nextPageBtn1.text,false);
            fcitxcfgwizard.set_next_page_key_second(nextPageBtn2.text,false);
        }
    }
}

