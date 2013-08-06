import QtQuick 1.1
import "common" as Common
Item {
    id: container

    property string fontName: "Helvetica"
    property int fontSize: 10
    property color fontColor: "black"
    property bool fontBold: false
    property string text: ""
    property string descript: ""
    property string size_num: ""
    property string bgImage: '../img/icons/list_item.png'

    property string bgImageSelected: '../img/icons/list_item_selected.png'
    property string bgImagePressed: '../img/icons/list_item_pressed.png'
    property bool selected: false
    property bool selectable: false
    property int textIndent: 0
    property bool checkbox_status: true

    property string btn_flag: "one_key_scan"

    signal clicked

    width: 360
    height: 64
    clip: true
    onSelectedChanged: selected ? state = 'selected' : state = ''

    BorderImage {
        id: background
        border { top: 9; bottom: 36; left: 35; right: 35; }
        source: bgImage
        anchors.fill: parent
    }

    Common.CheckBox {
        id: checkbox
//        width: 30
        checked: container.checkbox_status ? true : false
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 30
        onCheckedChanged: {
//            if (checkbox.checked) {
//                var mylist = systemdispatcher.get_package_args();
//                console.log("ok change............");
//                var word_flag = "false";
//                for (var i=0; i<mylist.length; i++) {
//                    if (mylist[i] == container.text) {
//                        word_flag = "true";
//                        break;
//                    }
//                }
//                if (word_flag == "false") {
//                    console.log("no word_flag");
//                    systemdispatcher.set_package_args(container.text);
////                    console.log(systemdispatcher.get_package_args());
//                }
//                else
//                    console.log("have word_flag");
//            }
//            else if (!checkbox.checked) {
//                console.log("no change...........");
////                console.log(systemdispatcher.get_package_args());
//                systemdispatcher.del_package_args(container.text);
////                console.log(container.text);
////                console.log(systemdispatcher.get_package_args());
//            }

            if (checkbox.checked) {
                if (btn_flag == "apt_work" || btn_flag == "apt_scan") {
                    var aptlist = systemdispatcher.get_apt_args();
                    console.log("ok change............");
                    var word_flag = "false";
                    for (var i=0; i<aptlist.length; i++) {
                        if (aptlist[i] == container.text) {
                            word_flag = "true";
                            break;
                        }
                    }
                    if (word_flag == "false") {
                        console.log("no word_flag");
                        systemdispatcher.set_apt_args(container.text);
    //                    console.log(systemdispatcher.get_package_args());
                    }
                    else
                        console.log("have word_flag");
                }
                else if (btn_flag == "software_work" || btn_flag == "software_scan") {
                    var softwarelist = systemdispatcher.get_software_args();
                    console.log("ok change............");
                    var word_flag1 = "false";
                    for (var j=0; j<softwarelist.length; j++) {
                        if (softwarelist[j] == container.text) {
                            word_flag1 = "true";
                            break;
                        }
                    }
                    if (word_flag1 == "false") {
                        console.log("no word_flag");
                        systemdispatcher.set_software_args(container.text);
    //                    console.log(systemdispatcher.get_package_args());
                    }
                    else
                        console.log("have word_flag");
                    console.log(container.text);
                    console.log(systemdispatcher.get_software_args());
                }
                else if (btn_flag == "cookies_work" || btn_flag == "cookies_scan") {
                    var cookieslist = systemdispatcher.get_cookies_args();
                    console.log("ok change............");
                    var word_flag2 = "false";
                    for (var k=0; k<cookieslist.length; k++) {
                        if (cookieslist[k] == container.text) {
                            word_flag2 = "true";
                            break;
                        }
                    }
                    if (word_flag2 == "false") {
                        console.log("no word_flag");
                        systemdispatcher.set_cookies_args(container.text);
    //                    console.log(systemdispatcher.get_package_args());
                    }
                    else
                        console.log("have word_flag");
                }
                else if (btn_flag == "package_work" || btn_flag == "package_scan") {
                    var mylist = systemdispatcher.get_package_args();
                    console.log("ok change............");
                    var word_flag3 = "false";
                    for (var q=0; q<mylist.length; q++) {
                        if (mylist[q] == container.text) {
                            word_flag3 = "true";
                            break;
                        }
                    }
                    if (word_flag3 == "false") {
                        console.log("no word_flag");
                        systemdispatcher.set_package_args(container.text);
    //                    console.log(systemdispatcher.get_package_args());
                    }
                    else
                        console.log("have word_flag");
                    console.log(container.text);
                    console.log(systemdispatcher.get_package_args());
                }
            }
            else if (!checkbox.checked) {
                console.log("no change...........");
//                console.log(systemdispatcher.get_package_args());
                if (btn_flag == "apt_work" || btn_flag == "apt_scan") {
                    systemdispatcher.del_apt_args(container.text);
                }
                else if (btn_flag == "software_work" || btn_flag == "software_scan") {
                    systemdispatcher.del_software_args(container.text);
                    console.log(container.text);
                    console.log(systemdispatcher.get_software_args());
                }
               else if (btn_flag == "cookies_work" || btn_flag == "cookies_scan") {

                    systemdispatcher.del_cookies_args(container.text);
                }
                else if (btn_flag == "package_work" || btn_flag == "package_scan") {
                    systemdispatcher.del_package_args(container.text);
                    console.log(container.text);
                    console.log(systemdispatcher.get_package_args());
                }

            }

        }
        visible: itemText.text=="" ? false : true
    }
    Text {
        id: itemText
        anchors {
            left: checkbox.right
            top: parent.top
            topMargin: 4
            bottomMargin: 4
            leftMargin: 10// + textIndent
            verticalCenter: container.verticalCenter
        }
        font {
            family: container.fontName
            pointSize: container.fontSize
            bold: container.fontBold
        }
        color: container.fontColor
        elide: Text.ElideRight
        text: container.text
        verticalAlignment: Text.AlignVCenter
    }

    Text {
        text: container.descript
        anchors {
            left: itemText.right
            top: parent.top
            leftMargin: 20
            verticalCenter: container.verticalCenter
        }
        color: container.fontColor
        elide: Text.ElideRight
        verticalAlignment: Text.AlignVCenter
    }

    Text {
        text: container.size_num
        anchors {
            top: parent.top
            right: parent.right
            rightMargin: 80
            verticalCenter: container.verticalCenter
        }
        color: container.fontColor
        elide: Text.ElideRight
        verticalAlignment: Text.AlignVCenter
    }

    MouseArea {
        id: mouseArea
//        anchors.fill: parent
        anchors.fill: itemText
        onClicked: container.clicked();
        onReleased: selectable && !selected ? selected = true : selected = false
    }

    states: [
        State {
            name: 'pressed'; when: mouseArea.pressed
            PropertyChanges { target: background; source: bgImagePressed; border { left: 35; top: 35; right: 35; bottom: 10 } }
        },
        State {
            name: 'selected'
            PropertyChanges { target: background; source: bgImageSelected; border { left: 35; top: 35; right: 35; bottom: 10 } }
        }
    ]
}
