import QtQuick 1.1
import SystemType 0.1
import SessionType 0.1
import "../common" as Common
import "../bars" as Bars
import "../" as Func

Rectangle {
    id:fcitxconfigtool
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
             text: fcitxconfigtool.actiontitle
             font.bold: true
             font.pixelSize: 14
             color: "#383838"
         }
         Text {
             text: fcitxconfigtool.actiontext
             font.pixelSize: 12
             color: "#7a7a7a"
         }
    }

//    Func.SettingsDelegate{
//        id:setting
//        onEmitFcitxRefresh:{
//            console.log("fcitxconfigtool8888888888");
//            fcitxconfigtool.refreshFcitxFont();
//            console.log("fcitxconfigtool9999999999");
//        }
//    }

    function refreshFcitxFont(){
        pageStack.push(functioncollection)
        //set font==========================================================
        var setFont = fcitxcfgwizard.get_font();
        fontStyleBtn.text = setFont;
        if(fontStyleBtn.text == "")
            fontStyleBtn.text = "Normal";
        console.log(qsTr(setFont));


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

    Component.onCompleted: {
        //set font==========================================================
        var setFont = fcitxcfgwizard.get_font();
        fontStyleBtn.text = setFont;

        console.log(qsTr(setFont));


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
//    //信号绑定，绑定qt的信号finishSetFont，该信号emit时触发onFinishSetFont
//    Connections
//    {
//        target: sessiondispatcher
//        onFinishSetFont: {
//            console.log("onFinishSetFont.........");
//            fontStyleBtn.text = fontFamily;
//              }
//    }
    //设置内容
    Column{
        spacing: 20
        smooth: true
        anchors{
            top:parent.top
            topMargin: 110
            left:parent.left
            leftMargin: 80
        }
        //font
       Row{
           Text {
               id: font
               text: qsTr("字体")
           }
           Common.Button {
                id: fontStyleBtn
                smooth:true
                width: 250;height: 30
                anchors.left: parent.left
                anchors.leftMargin: 250
               //hoverimage: "button_normal.png"
//               text: "Sans"
               onClicked: {
                   fontStyleBtn.text = fcitxcfgwizard.show_font_dialog();
               }
           }
//           Common.Button {
//               id: clearStyleBtn
//               width: 150;height: 30
//               anchors.left: fontStyleBtn.right
//               anchors.leftMargin:30
//               hoverimage: "button_normal.png"
//               text: " 清除字体设置"
//               onClicked: {
//                   fontStyleBtn.text = "Normal";
//               }
//           }

       }
        //候选词
        Row{
            Text {
                id: number
                text: qsTr("候选词个数")
            }
            Common.Slider {
                id: candidateWordNumber
                anchors.left: number.right
                anchors.leftMargin: 172
                minimumValue: 1
                maximumValue: 10
                width: 250
//                value: 　　　　　　　　　　　//要从后台获取
                stepSize: 1
                animated: true
                onValueChanged: {
                    console.log(candidateWordNumber.value)
                    displaynum.text = candidateWordNumber.value;
//
                }
            }
            Text {
                id: displaynum
                text: candidateWordNumber.value
                font.pixelSize: 12
                color: "#7a7a7a"
                anchors.left: candidateWordNumber.right
                anchors.leftMargin: 10
                anchors.verticalCenter: parent.verticalCenter
            }


//            Common.Button {
//                id: numOkBtn
//                width: 95;height: 30
//                anchors.left: parent.left
//                anchors.leftMargin: 470
//                hoverimage: "ok.png"
//                onClicked: {
//                    console.log("设置候选词个数为:");
//                    console.log(sliderNum.value);
//                }
//            }
//            Common.Button {
//                hoverimage: "use.png"
//                anchors.left: numOkBtn.right
//                anchors.leftMargin: 38
//                width: 124
//                height: 30
//                onClicked: {
////                    if() {

//                       // 设置候选词个数为默认状态
////                    }
////                    else
//                        sessiondispatcher.send_warningdialog_msg("友情提示：", "您系统的全局字体缩放已经为默认设置！");
//                }
//            }
        }

        //fontsize
        Row{
            Text {
                id: fontSize
                text: qsTr("字体大小")

            }
            Common.Slider {
                id: sliderFontSize
                anchors.left: fontSize.right
                anchors.leftMargin:187
                minimumValue: 0
                maximumValue: 72
                width: 250
 //               value: sessiondispatcher.  通过dbus从后排获取
                stepSize: 1
                animated: true
                onValueChanged: {
                    console.log(sliderFontSize.value)
                }
            }
            Text {
                id: displayFontSize
                text: sliderFontSize.value
                font.pixelSize: 12
                color: "#7a7a7a"
                anchors.left: sliderFontSize.right
                anchors.leftMargin: 10
                anchors.verticalCenter: parent.verticalCenter
            }

        }




        //竖排候选词列表
        Row{
            Text {
                id: list
                text: qsTr("竖排候选词列表")
            }
            Common.CheckBox{
                id:verticalList
                anchors.left: list.right
                anchors.leftMargin: 147
                anchors.verticalCenter: list.verticalCenter
                titleName: ""
                onCheckedChanged: {
                        console.log(verticalList.checked) ;
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
    Bars.FcitxBar {
        id: toolBar
        height: 50; anchors.bottom: parent.bottom; width: parent.width; opacity: 0.9
//            button1Label: qsTr("退出")
//            button2Label: qsTr("完成")
//            button1Label: qsTr("返回")
//            button2Label: qsTr("继续")
        onCancelBtnClicked: {
            sessiondispatcher.send_warningdialog_msg("友情提示：", "是否确定取消！");
                refreshFcitxFont()

  //             setting.emitFcitxRefresh()

        }

        onGobackBtnClicked: {
            console.log("上一步");
            pageStack.push(fcitxConfigtoolpage);//静态添加页面
        }
        onContinueBtnClicked: {
            console.log("continue ok");
            pageStack.push(fcitxConfigtoolKeypage);//静态添加页面
            fcitxcfgwizard.set_font(fontStyleBtn.text,false);
            fcitxcfgwizard.set_candidate_word_number(candidateWordNumber.value,false);
            fcitxcfgwizard.set_font_size(sliderFontSize.value,false);
            fcitxcfgwizard.set_vertical_list(verticalList.checked,false);

        }
    }
}

