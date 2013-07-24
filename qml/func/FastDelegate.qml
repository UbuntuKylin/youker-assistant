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
//            if (checkbox.checked) {
//                if (flag == "rubbish") {
//                    var rubbish_str = sessiondispatcher.get_str();
//                    if (rubbish_str.indexOf("r") < 0)
//                        sessiondispatcher.set_str("r");
//                }
//                else if (flag == "history") {
//                    var history_str = sessiondispatcher.get_str();
//                    if (history_str.indexOf("h") < 0)
//                        sessiondispatcher.set_str("h");
//                }
//                else if (flag == "cookie") {
//                    var cookie_str = sessiondispatcher.get_str();
//                    if (cookie_str.indexOf("c") < 0)
//                        sessiondispatcher.set_str("c");
//                }
//                else if (flag == "plugin") {
//                    var plugin_str = sessiondispatcher.get_str();
//                    if (plugin_str.indexOf("p") < 0)
//                        sessiondispatcher.set_str("p");
//                }

//                if (flag == "rubbish") {
//                    systemdispatcher.set_onekey_args("rubbish");
//                }
//                else if (flag == "history") {
//                    systemdispatcher.set_onekey_args("history");
//                }
//                else if (flag == "cookie") {
//                    systemdispatcher.set_onekey_args("cookie");
//                }
//                else if (flag == "package") {
//                    systemdispatcher.set_onekey_args("package");
//                }
//                console.log("OMG........");
//                console.log(systemdispatcher.get_onekey_args());
//            }
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
                    checked: (pagenum == "history") ? true : false
//                    width: 30
                    anchors.verticalCenter: parent.verticalCenter
                    onCheckedChanged: {
                        //kobe: wait for adding function
                        if (checkbox.checked) {
                            if (pagenum == "first") {
                                console.log("fisrt check fastdelegate...........");
                                if (flag == "cache") {
                                    var rubbishlist = systemdispatcher.get_onekey_args();
                                    console.log("ok change............");
                                    var word_flag = "false";
                                    for (var i=0; i<rubbishlist.length; i++) {
                                        if (rubbishlist[i] == flag) {
                                            word_flag = "true";
                                            break;
                                        }
                                    }
                                    if (word_flag == "false") {
                                        console.log("no word_flag");
                                        systemdispatcher.set_onekey_args(flag);
                    //                    console.log(systemdispatcher.get_package_args());
                                    }
                                    else
                                        console.log("have word_flag");
                                }
                                else if (flag == "history") {
                                    var historylist = systemdispatcher.get_onekey_args();
                                    console.log("ok change............");
                                    var word_flag1 = "false";
                                    for (var j=0; j<historylist.length; j++) {
                                        if (historylist[j] == flag) {
                                            word_flag1 = "true";
                                            break;
                                        }
                                    }
                                    if (word_flag1 == "false") {
                                        console.log("no word_flag");
                                        systemdispatcher.set_onekey_args(flag);
                    //                    console.log(systemdispatcher.get_package_args());
                                    }
                                    else
                                        console.log("have word_flag");
                                }
                                else if (flag == "cookies") {
                                    var cookieslist = systemdispatcher.get_onekey_args();
                                    console.log("ok change............");
                                    var word_flag2 = "false";
                                    for (var k=0; k<cookieslist.length; k++) {
                                        if (cookieslist[k] == flag) {
                                            word_flag2 = "true";
                                            break;
                                        }
                                    }
                                    if (word_flag2 == "false") {
                                        console.log("no word_flag");
                                        systemdispatcher.set_onekey_args(flag);
                    //                    console.log(systemdispatcher.get_package_args());
                                    }
                                    else
                                        console.log("have word_flag");
                                }
                                else if (flag == "unneed") {
                                    var mylist = systemdispatcher.get_onekey_args();
                                    console.log("ok change............");
                                    var word_flag3 = "false";
                                    for (var q=0; q<mylist.length; q++) {
                                        if (mylist[q] == flag) {
                                            word_flag3 = "true";
                                            break;
                                        }
                                    }
                                    if (word_flag3 == "false") {
                                        console.log("no word_flag");
                                        systemdispatcher.set_onekey_args(flag);
                    //                    console.log(systemdispatcher.get_package_args());
                                    }
                                    else
                                        console.log("have word_flag");
                                }
                                console.log(flag);
                                console.log(systemdispatcher.get_onekey_args());
                            }
                            else if (pagenum == "second") {
                                console.log("second check...........");
                                if (flag == "cache") {
                                    var rubbishlist2 = systemdispatcher.get_onekey_args2();
                                    console.log("ok change............");
                                    var second_flag = "false";
                                    for (var x=0; x<rubbishlist2.length; x++) {
                                        if (rubbishlist2[x] == flag) {
                                            second_flag = "true";
                                            break;
                                        }
                                    }
                                    if (second_flag == "false") {
                                        console.log("no word_flag");
                                        systemdispatcher.set_onekey_args2(flag);
                    //                    console.log(systemdispatcher.get_package_args());
                                    }
                                    else
                                        console.log("have word_flag");
                                }
                                else if (flag == "history") {
                                    var historylist2 = systemdispatcher.get_onekey_args2();
                                    console.log("ok change............");
                                    var second_flag2 = "false";
                                    for (var y=0; y<historylist2.length; y++) {
                                        if (historylist2[y] == flag) {
                                            second_flag2 = "true";
                                            break;
                                        }
                                    }
                                    if (second_flag2 == "false") {
                                        console.log("no word_flag");
                                        systemdispatcher.set_onekey_args2(flag);
                    //                    console.log(systemdispatcher.get_package_args());
                                    }
                                    else
                                        console.log("have word_flag");
                                }
                                else if (flag == "cookies") {
                                    var cookieslist2 = systemdispatcher.get_onekey_args2();
                                    console.log("ok change............");
                                    var second_flag3 = "false";
                                    for (var z=0; z<cookieslist2.length; z++) {
                                        if (cookieslist2[z] == flag) {
                                            second_flag3 = "true";
                                            break;
                                        }
                                    }
                                    if (second_flag3 == "false") {
                                        console.log("no word_flag");
                                        systemdispatcher.set_onekey_args2(flag);
                    //                    console.log(systemdispatcher.get_package_args());
                                    }
                                    else
                                        console.log("have word_flag");
                                }
                                else if (flag == "unneed") {
                                    var mylist2 = systemdispatcher.get_onekey_args2();
                                    console.log("ok change............");
                                    var second_flag4 = "false";
                                    for (var w=0; w<mylist2.length; w++) {
                                        if (mylist2[w] == flag) {
                                            second_flag4 = "true";
                                            break;
                                        }
                                    }
                                    if (second_flag4 == "false") {
                                        console.log("no word_flag");
                                        systemdispatcher.set_onekey_args2(flag);
                    //                    console.log(systemdispatcher.get_package_args());
                                    }
                                    else
                                        console.log("have word_flag");
                                }
                                console.log(flag);
                                console.log(systemdispatcher.get_onekey_args2());
                            }
                            else if (pagenum == "history") {
                                console.log("111");
                                systemdispatcher.set_history_flag(true);
                            }

//                            console.log(flag);
//                            console.log(systemdispatcher.get_onekey_args());

                        }
                        else if (!checkbox.checked) {
                            console.log("no change fastdelegate...........");
                            if (pagenum == "first") {
                                console.log("fisrt no check...........");
                                if (flag == "cache") {
                                    systemdispatcher.del_onekey_args(flag);
                                }
                                else if (flag == "history") {
                                    systemdispatcher.del_onekey_args(flag);
                                }
                               else if (flag == "cookies") {

                                    systemdispatcher.del_onekey_args(flag);
                                }
                                else if (flag == "unneed") {
                                    systemdispatcher.del_onekey_args(flag);
                                }
                                console.log(flag);
                                console.log(systemdispatcher.get_onekey_args());
                            }
                            else if (pagenum == "second") {
                                console.log("second no check...........");
                                if (flag == "cache") {
                                    systemdispatcher.del_onekey_args2(flag);
                                }
                                else if (flag == "history") {
                                    systemdispatcher.del_onekey_args2(flag);
                                }
                               else if (flag == "cookies") {

                                    systemdispatcher.del_onekey_args2(flag);
                                }
                                else if (flag == "unneed") {
                                    systemdispatcher.del_onekey_args2(flag);
                                }
                                console.log(flag);
                                console.log(systemdispatcher.get_onekey_args2());
                            }
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
                    source: picture
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
                        text: title
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
