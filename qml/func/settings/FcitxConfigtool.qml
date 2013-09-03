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
    property string actiontitle: "小企鹅输入法配置"
    property string actiontext: "可以设置自己喜欢的输入方式，点击＂下一步＂继续设置，点击＂取消＂取消当前设置并返回。"
    property string selectedimage: ""
    property int leftFcitxModelindex: 0
    property int rightFcitxModelindex: 0
    property int leftScrollbar_z:-1    //设置滑动条是否隐藏
    property int rightScrollbar_z:0
    property int scrollbar_z: -1
    property int leftNum: 0
    property int rightNum:0
    property string m_separator: "<5|13)"
    signal emitFcitxRefresh;
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

    function returnUnneed_data()
    {
        var returnUnneed_list = new Array
        leftFcitxModelindex =0;
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
        console.log(leftNum+rightNum);//524
        return returnUnneed_list;

    }

//    Func.SettingsDelegate{
//        id:setting
//        onEmitFcitxRefresh:{
//            console.log("fcitxconfigtool8888888888");
//            fcitxconfigtool.refreshFcitxtool();
//            console.log("fcitxconfigtool9999999999");
//        }
//    }
//    Loader {
//            id: pageLoader
//            source: "../../func/SettingsDelegate.qml"
//        }
//    Connections {
//            target: pageLoader.item
//            onRefreshFcitxtool: console.log("555555");
//        }

    function refreshFcitxtool(){
        pageStack.push(functioncollection);
        console.log("123456789");
        leftFcitxModel.clear();
        rightFcitxModel.clear();
        leftFcitxModelindex = 0;
        rightFcitxModelindex = 0;
        if(leftNum >= 2)
            downBtn.enabled =true;
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
}
    Component.onCompleted: {
        console.log("component......................................");
        leftFcitxModel.clear();
        rightFcitxModel.clear();
        leftFcitxModelindex = 0;
        rightFcitxModelindex = 0;
        var unneed_data = fcitxcfgwizard.get_im_list();
        if (unneed_data == "" || unneed_data.length == 0)
            unneed_data = fcitxcfgwizard.get_im_list();
        for (var i=0; i< unneed_data.length; i++) {
            var chooseList = unneed_data[i].split(m_separator);
//            console.log("11111111111111");
//            console.log(unneed_data[i]);
//            console.log("22222222222222");
//            console.log(chooseList[3]);
//            console.log("33333333333333");
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


    }
    //信号绑定，绑定qt的信号onFcitxWarn
//    Connections
//    {
//        target: fcitxcfgwizard
//        onFcitxWarn:
//            console.log("111111111111111111111111111111111111111111111111qwertyuiopp");
//  //          pageStack.push(functioncollection);

//         }
    //提示
    Text {
        id:currentMethod
        anchors {
            top: parent.top
            topMargin: 100
            left: parent.left
            leftMargin: 80
        }
        text: "当前的输入法"
        font.bold: true
        font.pixelSize: 12
        color: "#7a7a7a"
    }
    Text {
        id:choseMethod
        anchors {
            top: parent.top
            topMargin: 100
            left: parent.left
            leftMargin: 475
        }
        text: "可用的输入法"
        font.bold: true
        font.pixelSize: 12
        color: "#7a7a7a"
    }

    ListModel {
        id: leftFcitxModel
        ListElement {
            itemTitle: "";
            uniqueName:"";
            langClde:""
        }
    }


    ListModel {
        id: rightFcitxModel
        ListElement {
            itemTitle: "";
            uniqueName:"";
            langClde:""
        }
    }
    //左边框
    Rectangle{
        id:leftRectangle
        border.color: "#b9c5cc"
        width: 350; height: 240
        clip:true    //?
        anchors {
            top: parent.top
            topMargin: 120
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
//                Image {
//                    id: btnImg
//                    anchors.fill: parent
//                    source: ""
//                }
                MouseArea{
                    anchors.fill:parent
                    hoverEnabled: true
                    onClicked: {
                        console.log(index)
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
        ListView{
            id:leftLisv
            anchors.fill: parent
            model: leftFcitxModel
            delegate: leftDelegat
            highlight: Rectangle{width: 340;height: 30 ; color: "lightsteelblue"}
            focus:true
        }

        Rectangle{
            id:leftScrollbar
            anchors.right: parent.right
            anchors.rightMargin: -1
            height: parent.height
//            z:scrollbar_z
            width:11
            color: "lightgrey"
        }
        Rectangle{
            id: leftButton
            anchors.right: parent.right
            anchors.rightMargin: 0
            width: 10
            y: leftLisv.visibleArea.yPosition * leftScrollbar.height    //?
            height: leftLisv.visibleArea.heightRatio * leftScrollbar.height; //?
            radius: 3
            smooth: true
            color: "white"
            border.color: "lightgrey"
            Column{
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 2
                Rectangle{
                    width: 8;height: 1
                    color: "lightgrey"
                }
                Rectangle{
                    width: 8;height: 1
                    color: "lightgrey"
                }
                Rectangle{
                    width: 8;height: 1
                    color: "lightgrey"
                }
            }
            MouseArea {
                id: mousearea
                anchors.fill: leftButton
                drag.target: leftButton
                drag.axis: Drag.YAxis
                drag.minimumY: 0
                drag.maximumY: leftScrollbar.height - leftButton.height
                onMouseYChanged: {
                    leftLisv.contentY = leftButton.y / leftScrollbar.height * leftLisv.contentHeight //?
                }
            }
        }
    }

    //右边框
    Column{
        id:rightColum
        anchors {
            top: parent.top
            topMargin: 120
            left: parent.left
            leftMargin: 475
        }
        spacing: 10
        Rectangle{
            id:rightRectangle
            border.color: "#b9c5cc"
            width: 350; height: 240
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
//                            okBtn.enabled = true;
//                            okBtn.hoverimage = "list_item_active.png";
                            console.log(index);
                            wrapper.ListView.view.currentIndex = index; //?
                            state = "lightsteelblueColor";
                            rightFcitxModelindex = index;

                        }
                    }
                }
            }
            ListView{
                id:rightLisv
                anchors.fill: parent
                model: rightFcitxModel
                delegate: rightDelegat
                highlightMoveSpeed: 9999999
                highlight: Rectangle{width: 350;height: 30 ; color: "lightsteelblue"}
                    
            }

            Rectangle{
                id:rightscrollbar
                anchors.right: parent.right
                anchors.rightMargin: -1
                height: parent.height
//                z:scrollbar_z
                width:11
                color: "lightgrey"
            }
            Rectangle{
                id: rightbutton
                anchors.right: parent.right
                anchors.rightMargin: 0
                width: 10
                y: rightLisv.visibleArea.yPosition * rightscrollbar.height    //?
                height: 10*(rightLisv.visibleArea.heightRatio * rightscrollbar.height); //?
//                height:20
                radius: 3
                smooth: true
                color: "white"
                border.color: "lightgrey"
                Column{
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 2
                    Rectangle{
                        width: 8;height: 1
                        color: "lightgrey"
                    }
                    Rectangle{
                        width: 8;height: 1
                        color: "lightgrey"
                    }
                    Rectangle{
                        width: 8;height: 1
                        color: "lightgrey"
                    }
                }
                MouseArea {
                    id: rightmousearea
                    anchors.fill: rightbutton
                    drag.target: rightbutton
                    drag.axis: Drag.YAxis
                    drag.minimumY: 0
                    drag.maximumY: rightscrollbar.height - rightbutton.height/10
                    onMouseYChanged: {
                        rightLisv.contentY = rightbutton.y / rightscrollbar.height * rightLisv.contentHeight //?
                    }
                }
            }
        }

//        Common.CheckBox{
//            id:chooseCurrentLanguageBox
//            anchors{
//                top:rightRectangle.Bottom
//                topMargin: 10
//            }
//                titleName: "只显示本地语言"
//                onClicked: console.log("只显示本地语言")
//            }
//            Row{
//                Common.Button{
//                    id:okBtn
//                    width:60
//                    height:20
//                    enabled: false
//                    hoverimage: ""
//                    text:"ok"
//                    onClicked:{
//                        console.log("okBtn........................")
//                        console.log(rightFcitxModel.get(rightFcitxModelindex).itemTitle)
//                        leftFcitxModel.append({"itemTitle":rightFcitxModel.get(rightFcitxModelindex).itemTitle,
//                                               "uniqueName" :rightFcitxModel.get(rightFcitxModelindex).uniqueName,
//                                                "langClde" :rightFcitxModel.get(rightFcitxModelindex).langClde})
//                        rightFcitxModel.remove(rightFcitxModelindex);
//                        //rightColum.z = -1;
//                        leftNum++;
//                        rightNum--;
////                        okBtn.enabled = false;
////                        cancelBtn.enabled = false;
//                        cutBtn.enabled = true;
//                        if((leftFcitxModelindex==0)&&(leftNum>1))
//                            downBtn.enabled = true;
//                    }
//                }
//                Common.Button{
//                    id:cancelBtn
//                    width:60
//                    height:20
//                    hoverimage: "list_item_active.png"
//                    text:"cancel"
//                    onClicked: {
//                        console.log("cancelBtn........................")
//                        rightColum.z = -1;
//                        okBtn.enabled = false;
//                        cancelBtn.enabled = false;
//                    }
//                }
//            }
    }

//提示
Text {
    id:prompt
    anchors {
        top: parent.top
        topMargin: 400
        left: parent.left
        leftMargin: 80
    }
    text: qsTr("提示:'+'可以将可用输入法加入当前输入法,'-'删除当前选中输入法,'▲'和'▼'改变选中输入法的位置")
    font.bold: true
    font.pixelSize: 12
    color: "#7a7a7a"
}
Row{
    spacing: 5
    anchors{        
//     top:parent.top
//     topMargin: 190
//     left: parent.left
//     leftMargin:410
        left: parent.left
        leftMargin: 80;
        top:leftRectangle.bottom
        topMargin: 10

    }
Common.Button{
    id:addBtn
    width:60
    height:20
    //hoverimage: "list_item_active.png"
    text:"+"
    onClicked: {
        console.log("add......................")
        console.log("okBtn........................")
        console.log(rightFcitxModel.get(rightFcitxModelindex).itemTitle)
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
//    anchors.top: addBtn.bottom
//    anchors.topMargin: 20
    width:60
    height:20
    //hoverimage: "list_item_active.png"
    text: "－"
    onClicked: {
        console.log(leftFcitxModelindex)
        console.log(leftFcitxModel.get(leftFcitxModelindex).itemTitle)
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

        console.log(leftFcitxModelindex)


    }
}
Common.Button{
    id:upBtn
    width:60
    height:20
    //hoverimage: "list_item_active.png"
    enabled: false
    text:"▲"
    onClicked: {
        console.log("up......................")
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
//    anchors.top: addBtn.bottom
//    anchors.topMargin: 20
    width:60
    height:20
    //hoverimage: "list_item_active.png"
    text: "▼"
    onClicked: {
        console.log("down......................")
        if((leftFcitxModelindex==leftNum-1)||(leftNum==0))
        {
            downBtn.enabled = false;
            console.log("a")
            console.log(leftFcitxModelindex);
            console.log(leftNum);
        }
        if(leftFcitxModelindex<leftNum-1)
        {
            upBtn.enabled = true;
            leftFcitxModel.move(leftFcitxModelindex,leftFcitxModelindex+1,1)
            leftFcitxModelindex=leftFcitxModelindex+1;
            console.log("b")
            console.log(leftFcitxModelindex);
            console.log(leftNum);
            if((leftFcitxModelindex==leftNum-1)||(leftNum==0))
            {
                downBtn.enabled = false
                console.log("c")
                console.log(leftFcitxModelindex);
                console.log(leftNum);
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
    Bars.FcitxBar{
        id: toolBar
        height: 50; anchors.bottom: parent.bottom; width: parent.width; opacity: 0.9
//            button1Label: qsTr("取消")
//            button2Label: qsTr("上一步")
//            button3Label: qsTr("下一步")
        onCancelBtnClicked: {
            fcitxcfgwizard.send_fcitx_ok_warn();
 //           refreshFcitxtool()

        }

        onGobackBtnClicked: {
                pageStack.push(functioncollection)

        }
        onContinueBtnClicked: {         
            console.log("continue ok");
            pageStack.push(fcitxConfigtoolFontpage);//静态添加页
//            console.log(returnUnneed_data());
            fcitxcfgwizard.set_im_list(returnUnneed_data(),false);

        }
    }
}

