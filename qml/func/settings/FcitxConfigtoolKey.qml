import QtQuick 1.1
import "../common" as Common
import "../bars" as Bars
import "../../func"  as Func

Rectangle {
    id:fcitxconfigtoolKey
    width: parent.width
    height: 475

    property string actiontitle: qsTr("Appearance Configuration")//外观配置
    property string actiontext: qsTr("According to personal preferences to set input method skin, click 'Previous' to return to the personalized configuration.")//可以设置自己喜欢的皮肤，点击＂应用＂完成设置, 点击＂上一步＂返回个性化配置。
    property int flagCheck: 1
    property int flag_i: 0
    property string h_fcitxSkinImage: ""
    property string v_fcitxSkinImage: ""
    property string currentFcitxFont : "Sans"
    property string set_currentFcitxFont : ""

    //背景
    Image {
        source: "../../img/skin/bg-middle.png"
        anchors.fill: parent
    }

    //温馨提示
    Column {
        spacing: 20
        anchors.top: parent.top
        anchors.topMargin: 44
        anchors.left: parent.left
        anchors.leftMargin: 80
        Row{
            spacing: 50
            Text {
                 text: fcitxconfigtoolKey.actiontitle
                 font.bold: true
                 font.pixelSize: 14
                 color: "#383838"

             }
            //status picture
            Common.StatusImage {
                id: statusImage
                visible: false
                iconName: "green.png"
                text: qsTr("Completed")//已完成
                anchors.verticalCenter: parent.verticalCenter
            }
        }
        Text {
            width: fcitxconfigtoolKey.width - 80 - 20
            text: fcitxconfigtoolKey.actiontext
            wrapMode: Text.WordWrap
            font.pixelSize: 12
            color: "#7a7a7a"
        }
    }

    function refreshFcitxKey(){
        skinModel.clear();
        //set font============================================================
        //将系统初始的全局字体缩放写入QSetting配置文件
        fcitxconfigtoolKey.currentFcitxFont = fcitxcfgwizard.get_font();
        fcitxconfigtoolKey.set_currentFcitxFont = fcitxconfigtoolKey.currentFcitxFont;
        fontStyleBtn.text = fcitxconfigtoolKey.currentFcitxFont;
        sessiondispatcher.write_default_configure_to_qsetting_file("font", "fcitxFont", fcitxconfigtoolKey.currentFcitxFont);
        //get font size=======================================================
        var getFontSize = fcitxcfgwizard.get_font_size();
        if(getFontSize == 0)
            getFontSize = fcitxcfgwizard.get_font_size();
        sliderFontSize.value = getFontSize;

        //get_skin_list and current_skin=================================================
        var getSkinList = fcitxcfgwizard.get_all_skin_type()
        var getCurrentSkin = fcitxcfgwizard.get_skin_type()
        if(getCurrentSkin != "default")
        {
            enableSkinBox.checked = true
            flagCheck = 1;
        }
        else
        {
            enableSkinBox.checked = false;
            flagCheck = 0;
        }
        getSkinList.unshift(getCurrentSkin);   //js将数组第一个添加unshift进来的
        skinModel.clear();
        for(var i=0;i<getSkinList.length;i++)
       {
            skinModel.append({"skinTitle": getSkinList[i]});
            if(i!=0&&(getSkinList[i] == getCurrentSkin))
                skinModel.remove(i);
        }
        //load_skin_image====================================================
        if(getCurrentSkin == "default")
        {
            h_fcitxSkinImage = "../../img/skin/h_default.png"
            v_fcitxSkinImage = "../../img/skin/v_default.png"
        }
        else if(getCurrentSkin == "dark")
        {
            h_fcitxSkinImage = "../../img/skin/h_dark.png"
            v_fcitxSkinImage = "../../img/skin/v_dark.png"
        }
        else if(getCurrentSkin == "classic")
        {
            h_fcitxSkinImage = "../../img/skin/h_classic.png"
            v_fcitxSkinImage = "../../img/skin/v_classic.png"
        }
        else{
            h_fcitxSkinImage = ""
            v_fcitxSkinImage = ""
        }

  }
    //选择皮肤
    ListModel { id: skinModel }

    Connections {
        target: fcitxcfgwizard
        onRefreshFcitxSig: {
            refreshFcitxKey();
        }
    }

    Component.onCompleted: {
        refreshFcitxKey();
    }

    //分割线
    Row{
        anchors{
            left: parent.left
            leftMargin: 40
            top: parent.top
            topMargin: 120
        }
        Text{
            id: skintitle
            text: qsTr("Skin settings")//皮肤设置
            font.bold: true
            font.pixelSize: 12
            color: "#383838"
        }
        //横线
        Common.Separator {
            anchors.verticalCenter: parent.verticalCenter
            width: fcitxconfigtoolKey.width - skintitle.width - 40 * 2
        }
    }
    //使用皮肤
    Row{
        spacing: 75
        anchors {
            top: parent.top
            topMargin: 150
            left: parent.left
            leftMargin: 65
        }
        Common.CheckBox{
            id:enableSkinBox
            anchors.verticalCenter: parent.verticalCenter
            titleName: qsTr("Using skin")//使用皮肤
            onCheckedChanged: {
                if(flagCheck == 1)
                {
                    if(enableSkinBox.checked == false)
                    {
                        var getSkinList = fcitxcfgwizard.get_all_skin_type()
                        for(var i=0;i<getSkinList.length;i++)
                       {
                            if(getSkinList[i] == "default")
                            {
                                flag_i = i;
                                break;
                            }
                        }
                        if(fcitxcfgwizard.get_skin_type()=="default")
                                {
                                    flag_i = 0;
                                }

                        skinCombo.selectedIndex = flag_i;
                    }
                }
            }
        }
        Common.ComboBox {
            id: skinCombo
            model: skinModel
            width: 130
            height: 25
            onSelectedTextChanged: {
                if(skinCombo.selectedText == "default")
                {
                    enableSkinBox.checked = false;
                    flagCheck = 0;

                }
                else{
                    enableSkinBox.checked = true;
                    flagCheck = 1;
                }

                //load_skin_image====================================================
                 if(skinCombo.selectedText == "default")
                {
                    h_fcitxSkinImage = "../../img/skin/h_default.png"
                    v_fcitxSkinImage = "../../img/skin/v_default.png"

                }
                else if(skinCombo.selectedText == "dark")
                {
                    h_fcitxSkinImage = "../../img/skin/h_dark.png"
                    v_fcitxSkinImage = "../../img/skin/v_dark.png"
                }
                else if(skinCombo.selectedText == "classic")
                {
                    h_fcitxSkinImage = "../../img/skin/h_classic.png"
                    v_fcitxSkinImage = "../../img/skin/v_classic.png"
                }
                else{
                    h_fcitxSkinImage = "../../img/skin/fcitxSkin_not.png"
                    v_fcitxSkinImage = ""
                }
           }
        }
     }
    //更换字体
    Row{
        spacing: 75
        anchors {
            top: parent.top
            topMargin: 180
            left: parent.left
            leftMargin: 65
        }
        Common.CheckBox{
            id:enableHotKeyBox
            anchors.verticalCenter: parent.verticalCenter
            titleName: qsTr("Change fonts")//更换字体
            onCheckedChanged: {
                if(enableHotKeyBox.checked == false)
                {
                    sliderFontSize.value = 12;
                    fontStyleBtn.text = "Sans";
                }
            }
        }
        //fontsize
        Row{
            spacing: 10
            Text {
                id: fontSize
                font.pixelSize: 12
                color: "#7a7a7a"
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("Size")//大小
            }
            Row{
                spacing: 10
                Common.Slider {
                    id: sliderFontSize
                    anchors.verticalCenter: parent.verticalCenter
                    minimumValue: 1
                    maximumValue: 72
                    value:12
                    width: 150
                    stepSize: 1
                    animated: true
                    onValueChanged: {
                        if(sliderFontSize.value != 12)
                        {
                            enableHotKeyBox.checked = true;
                        }
                    }
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
     }
    //font
   Row{
       spacing: 10
       anchors {
           top: parent.top
           topMargin: 180
           left: parent.left
           leftMargin: 400
       }
       Text {
           id: font
           font.pixelSize: 12
           color: "#7a7a7a"
           anchors.verticalCenter: parent.verticalCenter
           text: qsTr("Font settings")//字体设置
       }
       Common.Button {
            id: fontStyleBtn
            smooth:true
            width: 160;height: 25
            hoverimage: "fcitxFont.png"//../../img/icons/
            fontcolor:"#929292"
            fontsize: 13
            anchors.verticalCenter: font.verticalCenter
           onClicked: {
               sessiondispatcher.show_font_dialog("fcitxfont");
               set_currentFcitxFont = sessiondispatcher.getSelectedFcitxFont();
               fontStyleBtn.text = fcitxconfigtoolKey.set_currentFcitxFont;
               console.log(set_currentFcitxFont);
           }
           onTextChanged: {
               if(fontStyleBtn.text != "Sans" )
               {
                   enableHotKeyBox = true;
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
    Bars.FcitxThreeBar {
        id: toolBar
        height: 50; anchors.bottom: parent.bottom; width: parent.width; opacity: 0.9
        onGobackHomeClicked: {
            pageStack.push(functioncollection);
        }
        onCancelBtnClicked: {
            fcitxcfgwizard.send_fcitx_ok_warn(mainwindow.x, mainwindow.y);
        }
        onGobackBtnClicked: {
            pageStack.push(fcitxConfigtoolFontpage);//静态添加页面

        }
        onFinishBtnClicked: {
            //接后台应用接口            
            fcitxcfgwizard.set_font(fontStyleBtn.text,false);
            fcitxcfgwizard.set_font_size(sliderFontSize.value,false);
            fcitxcfgwizard.set_skin_type(skinCombo.selectedText, false);
            fcitxcfgwizard.all_cfg_save();
            statusImage.visible = true;
        }
        Timer {
            interval: 5000; running: true; repeat: true
            onTriggered: statusImage.visible = false
        }
    }

}
