import QtQuick 1.1
import SystemType 0.1
import SessionType 0.1
import "../common" as Common
import "../bars" as Bars
import "../" as Func

Rectangle {
    id:fcitxconfigtoolFont
    width: parent.width
    height: 475

    property string actiontitle: "小企鹅输入法字体配置"
    property string actiontext: "可以设置自己喜欢的字体风格，点击＂下一步＂继续设置，点击＂取消＂取消当前设置并返回。"
    property int scanModelIndex:1
    property int scrollbar_z: 1
    property int defaultCandidateWord:0     //恢复默认时用到
    property int defaultFontSize:0
    property int defaultFontStyle:0
    property int scanModelindex: 1
    property string fontFamily: ""
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
             text: fcitxconfigtoolFont.actiontitle
             font.bold: true
             font.pixelSize: 14
             color: "#383838"
         }
         Text {
             text: fcitxconfigtoolFont.actiontext
             font.pixelSize: 12
             color: "#7a7a7a"
         }
    }

    function refreshFcitxFont(){
        //set font============================================================
        var setFont = fcitxcfgwizard.get_font();
        fontStyleBtn.text = setFont;
        //get candidate_word_numbe============================================
        var getFontcandidateWord =fcitxcfgwizard.get_candidate_word_number();
        candidateWordNumber.value = getFontcandidateWord;
        //get font size=======================================================
        var getFontSize = fcitxcfgwizard.get_font_size();
        sliderFontSize.value = getFontSize;
        //get_vertical_list===================================================
        var getVerticalList = fcitxcfgwizard.get_vertical_list();
        verticalList.checked = getVerticalList
    }
    Connections {
            target: fcitxcfgwizard
            onRefreshFcitxSig: {
                refreshFcitxFont();
            }
        }
    Component.onCompleted: {
        //set font============================================================
        var setFont = fcitxcfgwizard.get_font();
        fontStyleBtn.text = setFont;
        //get candidate_word_numbe============================================
        var getFontcandidateWord =fcitxcfgwizard.get_candidate_word_number();
        candidateWordNumber.value = getFontcandidateWord;
        //get font size=======================================================
        var getFontSize = fcitxcfgwizard.get_font_size();
        sliderFontSize.value = getFontSize;
        //get_vertical_list===================================================
        var getVerticalList = fcitxcfgwizard.get_vertical_list();
        verticalList.checked = getVerticalList
        //通过后台接口可以默认添加窗口中内容
    }
    //设置内容
    Column{
        spacing: 15
        smooth: true
        anchors{
            top:parent.top
            topMargin: 110
            left:parent.left
            leftMargin: 80
        }
        //font
       Row{
           spacing: 218
           Text {
               id: font
               text: qsTr("字体")
           }
           Common.Button {
                id: fontStyleBtn
                smooth:true
                width: 250;height: 30
                anchors.verticalCenter: font.verticalCenter
               onClicked: {
                   fontStyleBtn.text = fcitxcfgwizard.show_font_dialog();
               }
           }

       }
        //候选词
        Row{
            spacing: 172
            Text {
                id: number
                text: qsTr("候选词个数")
            }
            Row{
                spacing: 10
                Common.Slider {
                    id: candidateWordNumber
                    anchors.verticalCenter: parent.verticalCenter
                    minimumValue: 1
                    maximumValue: 10
                    width: 250
                    stepSize: 1
                    animated: true
                }
                Text {
                    id: displaynum
                    text: candidateWordNumber.value
                    font.pixelSize: 12
                    color: "#7a7a7a"
//                    anchors.left: candidateWordNumber.right
//                    anchors.leftMargin: 10
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

        }

        //fontsize
        Row{
            spacing: 187
            Text {
                id: fontSize
                text: qsTr("字体大小")
            }
            Row{
                spacing: 10
                Common.Slider {
                    id: sliderFontSize
                    anchors.verticalCenter: parent.verticalCenter
                    minimumValue: 0
                    maximumValue: 72
                    width: 250
                    stepSize: 1
                    animated: true
                }
                Text {
                    id: displayFontSize
                    text: sliderFontSize.value
                    font.pixelSize: 12
                    color: "#7a7a7a"
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
        }
        //竖排候选词列表
        Row{
            spacing: 145
            Text {
                id:listh
                text: qsTr("竖排候选词列表")
            }
            Common.CheckBox{
                id:verticalList
                anchors.verticalCenter: listh.verticalCenter
                titleName: ""
                onCheckedChanged: {
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
    Bars.FcitxBar {
        id: toolBar
        height: 50; anchors.bottom: parent.bottom; width: parent.width; opacity: 0.9
        onCancelBtnClicked: {
            fcitxcfgwizard.send_fcitx_ok_warn();
        }

        onGobackBtnClicked: {
            pageStack.push(fcitxConfigtoolpage);//静态添加页面
        }
        onContinueBtnClicked: {
            pageStack.push(fcitxConfigtoolKeypage);//静态添加页面
            fcitxcfgwizard.set_font(fontStyleBtn.text,false);
            fcitxcfgwizard.set_candidate_word_number(candidateWordNumber.value,false);
            fcitxcfgwizard.set_font_size(sliderFontSize.value,false);
            fcitxcfgwizard.set_vertical_list(verticalList.checked,false);

        }
    }
}

