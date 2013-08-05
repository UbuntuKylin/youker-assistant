import QtQuick 1.1
import "common" as Common
import SessionType 0.1
import QtDesktop 0.1
//Component {

    Item {
        id: clearDelegate
        property SessionDispatcher dis: sessiondispatcher
        property string pagenum: ""
        width: parent.width//clearDelegate.ListView.view.width
        height: 65

//        function itemClicked() {
//            rotateDetails.title = "kobe111";
//            rotateDetails.description = "lixiang111";
//            scaleMe.state = "Details";
//        }

        //kobe: 'flag' comes from ListModel in FastclearModel.qml
        Component.onCompleted: {

        }

        Item {
            Behavior on scale { NumberAnimation { easing.type: Easing.InOutQuad} }
            id: scaleMe
            //checkbox, picture and words
            Row {
                id: lineLayout
                spacing: 10
                anchors {
                    fill: parent
                    left: parent.left
                    leftMargin: 50
                }
                Common.CheckBox {
                    id: checkbox
//                    checked: true
                    //清理历史记录时，chechbox默认为true，首页一键清理和系统清理页面的一键清理默认都为false
//                    checked: (pagenum == "history") ? true : false
                    checked: true    //将所有选项都check
//                    width: 30
                    anchors.verticalCenter: parent.verticalCenter
                    onCheckedChanged: {
                        //kobe: wait for adding function
                        if (checkbox.checked) {
                            //----------------首页一键清理----------------
                            if (pagenum == "first") {
//                                console.log("首页一键清理 checked true...........");
//                                console.log(clearflag);
//                                console.log(titlename);
                                if (clearflag == "cache") {
                                    console.log("ture cache is...........");
                                    console.log(clearflag);
                                    var rubbishlist = systemdispatcher.get_onekey_args();
                                    console.log("ok change............");
                                    var word_flag = "false";
                                    for (var i=0; i<rubbishlist.length; i++) {
                                        if (rubbishlist[i] == clearflag) {
                                            word_flag = "true";
                                            break;
                                        }
                                    }
                                    if (word_flag == "false") {
                                        console.log("no word_flag");
                                        systemdispatcher.set_onekey_args(clearflag);
                                        console.log(systemdispatcher.get_package_args());
                                    }
                                    else
                                        console.log("have word_flag");
                                }
                                else if (clearflag == "history") {
                                    var historylist = systemdispatcher.get_onekey_args();
                                    console.log("ok change............");
                                    var word_flag1 = "false";
                                    for (var j=0; j<historylist.length; j++) {
                                        if (historylist[j] == clearflag) {
                                            word_flag1 = "true";
                                            break;
                                        }
                                    }
                                    if (word_flag1 == "false") {
                                        console.log("no word_flag");
                                        systemdispatcher.set_onekey_args(clearflag);
                                        console.log(systemdispatcher.get_package_args());
                                    }
                                    else
                                        console.log("have word_flag");
                                }
                                else if (clearflag == "cookies") {
                                    var cookieslist = systemdispatcher.get_onekey_args();
                                    console.log("ok change............");
                                    var word_flag2 = "false";
                                    for (var k=0; k<cookieslist.length; k++) {
                                        if (cookieslist[k] == clearflag) {
                                            word_flag2 = "true";
                                            break;
                                        }
                                    }
                                    if (word_flag2 == "false") {
                                        console.log("no word_flag");
                                        systemdispatcher.set_onekey_args(clearflag);
                                        console.log(systemdispatcher.get_package_args());
                                    }
                                    else
                                        console.log("have word_flag");
                                }
                                else if (clearflag == "unneed") {
                                    var mylist = systemdispatcher.get_onekey_args();
                                    console.log("ok change............");
                                    var word_flag3 = "false";
                                    for (var q=0; q<mylist.length; q++) {
                                        if (mylist[q] == clearflag) {
                                            word_flag3 = "true";
                                            break;
                                        }
                                    }
                                    if (word_flag3 == "false") {
                                        console.log("no word_flag");
                                        systemdispatcher.set_onekey_args(clearflag);
                                        console.log(systemdispatcher.get_package_args());
                                    }
                                    else
                                        console.log("have word_flag");
                                }
                                console.log("-------test first------");
                                console.log(clearflag);
                                console.log(systemdispatcher.get_onekey_args());
                            }

                            //----------------系统清理页面的一键清理----------------
                            else if (pagenum == "second") {
                                console.log("second check...........");
                                if (clearflag == "cache") {
                                    var rubbishlist2 = systemdispatcher.get_onekey_args2();
                                    console.log("ok change............");
                                    var second_flag = "false";
                                    for (var x=0; x<rubbishlist2.length; x++) {
                                        if (rubbishlist2[x] == clearflag) {
                                            second_flag = "true";
                                            break;
                                        }
                                    }
                                    if (second_flag == "false") {
                                        console.log("no word_flag");
                                        systemdispatcher.set_onekey_args2(clearflag);
                                        console.log(systemdispatcher.get_package_args());
                                    }
                                    else
                                        console.log("have word_flag");
                                }
                                else if (clearflag == "history") {
                                    var historylist2 = systemdispatcher.get_onekey_args2();
                                    console.log("ok change............");
                                    var second_flag2 = "false";
                                    for (var y=0; y<historylist2.length; y++) {
                                        if (historylist2[y] == clearflag) {
                                            second_flag2 = "true";
                                            break;
                                        }
                                    }
                                    if (second_flag2 == "false") {
                                        console.log("no word_flag");
                                        systemdispatcher.set_onekey_args2(clearflag);
                                        console.log(systemdispatcher.get_package_args());
                                    }
                                    else
                                        console.log("have word_flag");
                                }
                                else if (clearflag == "cookies") {
                                    var cookieslist2 = systemdispatcher.get_onekey_args2();
                                    console.log("ok change............");
                                    var second_flag3 = "false";
                                    for (var z=0; z<cookieslist2.length; z++) {
                                        if (cookieslist2[z] == clearflag) {
                                            second_flag3 = "true";
                                            break;
                                        }
                                    }
                                    if (second_flag3 == "false") {
                                        console.log("no word_flag");
                                        systemdispatcher.set_onekey_args2(clearflag);
                                        console.log(systemdispatcher.get_package_args());
                                    }
                                    else
                                        console.log("have word_flag");
                                }
                                else if (clearflag == "unneed") {
                                    var mylist2 = systemdispatcher.get_onekey_args2();
                                    console.log("ok change............");
                                    var second_flag4 = "false";
                                    for (var w=0; w<mylist2.length; w++) {
                                        if (mylist2[w] == clearflag) {
                                            second_flag4 = "true";
                                            break;
                                        }
                                    }
                                    if (second_flag4 == "false") {
                                        console.log("no word_flag");
                                        systemdispatcher.set_onekey_args2(clearflag);
                                        console.log(systemdispatcher.get_package_args());
                                    }
                                    else
                                        console.log("have word_flag");
                                }
                                console.log("-------test second------");
                                console.log(clearflag);
                                console.log(systemdispatcher.get_onekey_args2());
                            }

                            //----------------清理历史记录----------------
                            else if (pagenum == "history") {
                                console.log("111");
                                systemdispatcher.set_history_flag(true);
                            }

//                            console.log(systemdispatcher.get_onekey_args());

                        }



                        else if (!checkbox.checked) {
//                            console.log("首页一键清理 checked false...........");
                            //----------------首页一键清理----------------
                            if (pagenum == "first") {
                                console.log("fisrt no check...........");
//                                console.log(clearflag);
                                if (clearflag == "cache") {
                                    console.log("false cache is...........");
                                    console.log(clearflag);
                                    systemdispatcher.del_onekey_args(clearflag);
                                }
                                else if (clearflag == "history") {
                                    systemdispatcher.del_onekey_args(clearflag);
                                }
                               else if (clearflag == "cookies") {

                                    systemdispatcher.del_onekey_args(clearflag);
                                }
                                else if (clearflag == "unneed") {
                                    systemdispatcher.del_onekey_args(clearflag);
                                }
                                console.log(clearflag);
                                console.log(systemdispatcher.get_onekey_args());
                            }
                            //----------------系统清理页面的一键清理----------------c
                            else if (pagenum == "second") {
                                console.log("second no check...........");
                                if (clearflag == "cache") {
                                    systemdispatcher.del_onekey_args2(clearflag);
                                }
                                else if (clearflag == "history") {
                                    systemdispatcher.del_onekey_args2(clearflag);
                                }
                               else if (clearflag == "cookies") {

                                    systemdispatcher.del_onekey_args2(clearflag);
                                }
                                else if (clearflag == "unneed") {
                                    systemdispatcher.del_onekey_args2(clearflag);
                                }
                                console.log(clearflag);
                                console.log(systemdispatcher.get_onekey_args2());
                            }

                            //----------------清理历史记录----------------
                            else if (pagenum == "history") {
                                console.log("222");
                                systemdispatcher.set_history_flag(false);
                            }
            //                console.log(systemdispatcher.get_package_args());

//                            console.log(flag);
//                            console.log(systemdispatcher.get_onekey_args());
                        }





//                        if (checkbox.checked) {
//                            if (flag == "rubbish") {
//                                var rubbish_str = sessiondispatcher.get_str();
//                                if (rubbish_str.indexOf("r") < 0)
//                                    sessiondispatcher.set_str("r");
//                            }
//                            else if (flag == "history") {
//                                var history_str = sessiondispatcher.get_str();
//                                if (history_str.indexOf("h") < 0)
//                                    sessiondispatcher.set_str("h");
//                            }
//                            else if (flag == "cookie") {
//                                var cookie_str = sessiondispatcher.get_str();
//                                if (cookie_str.indexOf("c") < 0)
//                                    sessiondispatcher.set_str("c");
//                            }
//                            else if (flag == "plugin") {
//                                var plugin_str = sessiondispatcher.get_str();
//                                if (plugin_str.indexOf("p") < 0)
//                                    sessiondispatcher.set_str("p");
//                            }
////                            console.log("is checked");
//                        }
//                        else if (!checkbox.checked) {
//                            if (flag == "rubbish") {
//                                var rubbish_str1 = sessiondispatcher.get_str();
//                                if (rubbish_str1.indexOf("r") > -1) {
//                                    sessiondispatcher.del_str("r");
//                                }
//                            }
//                            else if (flag == "history") {
//                                var history_str1 = sessiondispatcher.get_str();
//                                if (history_str1.indexOf("h") > -1)
//                                    sessiondispatcher.del_str("h");
//                            }
//                            else if (flag == "cookie") {
//                                var cookie_str1 = sessiondispatcher.get_str();
//                                if (cookie_str1.indexOf("c") > -1)
//                                    sessiondispatcher.del_str("c");
//                            }
//                            else if (flag == "plugin") {
//                                var plugin_str1 = sessiondispatcher.get_str();
//                                if (plugin_str1.indexOf("p") > -1)
//                                    sessiondispatcher.del_str("p");
//                            }
////                            console.log("is not checked");
//                        }
                    }
                }
                Image {
                    id: clearImage
                    width: 40; height: 42
                    source: picturename
                    anchors {
                        left: checkbox.right; leftMargin: 15
                        verticalCenter: parent.verticalCenter
                    }

                }

                Column {
                    spacing: 5
                    anchors {
                        left: clearImage.right; leftMargin: 15
                        verticalCenter: parent.verticalCenter
                    }
                    Text {
                        text: titlename
                        font.bold: true
                        font.pixelSize: 14
                        color: "#383838"
                    }
                    Text {
                        text: detailstr
                        font.pixelSize: 12
                        color: "#7a7a7a"
                    }
                }
            }
            Rectangle {  //分割条
                width: parent.width; height: 1
                anchors { top: lineLayout.bottom; topMargin: 5}
                color: "gray"
            }
        }

//        MouseArea {
//            anchors.fill: clearDelegate
//            onClicked: itemClicked()
//        }
    }
//}



//Component {
//    Item {
//        id: clearDelegate
//        width: parent.width//clearDelegate.ListView.view.width
//        height: 65

//        function itemClicked() {
//            rotateDetails.title = "kobe111";
//            rotateDetails.description = "lixiang111";
//            scaleMe.state = "Details";
//        }

//        Item {
//            Behavior on scale { NumberAnimation { easing.type: Easing.InOutQuad} }
//            id: scaleMe
//            //checkbox, picture and words
//            Row {
//                id: lineLayout
//                spacing: 10
//                anchors {
//                    fill: parent
//                    left: parent.left
//                    leftMargin: 50
//                }
//                CheckBox {
//                    id: checkbox
//                    checked: true
//                    anchors.verticalCenter: parent.verticalCenter
//                    onCheckedChanged: {
//                        //kobe: wait for adding function
//                    }
//                }
//                Image {
//                    id: clearImage
//                    width: 47; height: 47
//                    source: picture
//                    anchors {
//                        left: checkbox.right; leftMargin: 15
//                        verticalCenter: parent.verticalCenter
//                    }

//                }

//                Column {
//                    spacing: 5
//                    anchors {
//                        left: clearImage.right; leftMargin: 15
//                        verticalCenter: parent.verticalCenter
//                    }
//                    Text {
//                        text: title
//                        font.pointSize: 11
//                        color: "black"
//                    }
//                    Text {
//                        text: detailstr
//                        font.pointSize: 9
//                        color: "gray"
//                    }
//                }
//            }
//            ListItem.ThinDivider {} //分割条  can be used as header for list

//            Connections {
//                target: toolBar
//                onButton2Clicked: if (scaleMe.state == 'Details' ) scaleMe.state = 'Show'
//            }

//            states: [
//                State {
//                    name: "Show"; when: thumb.status == Image.Ready
//                    PropertyChanges { target: scaleMe; scale: 1 }
//                },
//                State {
//                    name: "Details"
//                    PropertyChanges { target: scaleMe; scale: 1 }
//                    PropertyChanges { target: background; state: "DetailedView" }
//                }
//            ]
//            transitions: [
//                Transition {
//                    from: "Show"; to: "Details"
//                    ParentAnimation {
//                        via: foreground
//                        NumberAnimation { properties: "x,y"; duration: 500; easing.type: Easing.InOutQuad }
//                    }
//                },
//                Transition {
//                    from: "Details"; to: "Show"
//                    ParentAnimation {
//                        via: foreground
//                        NumberAnimation { properties: "x,y"; duration: 500; easing.type: Easing.InOutQuad }
//                    }
//                }
//            ]
//        }

//        MouseArea {
//            anchors.fill: clearDelegate
//            onClicked: itemClicked()
//        }
//        //点击不同的项时移动焦点颜色
//    //    MouseArea {
//    //        anchors.fill: clearDelegate
//    //        onClicked: {
//    //            clearDelegate.ListView.view.currentIndex = index
//    //        }
//    //    }
//    }
//}












//Component {
//    Item {
//        id: clearDelegate
//        width: parent.width//clearDelegate.ListView.view.width
//        height: 65
//        //checkbox, picture and words
//        Row {
//            id: lineLayout
//            spacing: 10
//            anchors {
//                fill: parent
//                left: parent.left
//                leftMargin: 50
//            }

//            CheckBox {
//                id: checkbox
//                checked: true
//                anchors.verticalCenter: parent.verticalCenter
//                onCheckedChanged: {
//                    //kobe: wait for adding function
//                }
//            }

//            Image {
//                id: clearImage
//                width: 47; height: 47
//                source: picture
//                anchors {
//                    left: checkbox.right; leftMargin: 15
//                    verticalCenter: parent.verticalCenter
//                }

//            }

//            Column {
//                spacing: 5
//                anchors {
//                    left: clearImage.right; leftMargin: 15
//                    verticalCenter: parent.verticalCenter
//                }
//                Text {
//                    text: title
//                    font.pointSize: 11
//                    color: "black"
//                }
//                Text {
//                    text: detailstr
//                    font.pointSize: 9
//                    color: "gray"
//                }
//            }
//        }
//        ListItem.ThinDivider {} //分割条  can be used as header for list

//        //点击不同的项时移动焦点颜色
//    //    MouseArea {
//    //        anchors.fill: clearDelegate
//    //        onClicked: {
//    //            clearDelegate.ListView.view.currentIndex = index
//    //        }
//    //    }
//    }
//}
