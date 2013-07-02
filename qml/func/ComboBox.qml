import QtQuick 2.0
import Ubuntu.Components 0.1
import Ubuntu.Components.ListItems 0.1 as ListItem
import Ubuntu.Components.Popups 0.1

Item {
    id: container
    property string headertitle: "Select Launcher Model"
    property string titel1: ""
    property string titel2: ""
    property string titel3: ""
    property string flags: "launcher"

    Button {
        id: selector
        text: qsTr(headertitle)
        width: 200
        onClicked: PopupUtils.open(popoverLauncher, selector)
        onTextChanged: {
            //kobe: wait for adding function
        }
    }

    Component.onCompleted: {
        launchModel.clear();
        launchModel.append({"title": titel1});
        launchModel.append({"title": titel2});
        launchModel.append({"title": titel3});
        if (flags == "launcher1") {
            launchModel.append({"title": "test for add a item"});
        }

//        streamModel.sync();
    }

    ListModel {
        id: launchModel
        ListElement {
            title: "Launcher1"
//            index: 0
        }
    }
    //List
    Component {
        id: popoverLauncher
        Popover {
            Column {
                anchors {
                    top: parent.top
                    left: parent.left
                    right: parent.right
                }
                // Make sure the Popover doesn't flow off the screen
                height: 300
                // Header displaying title
                ListItem.Header {
                    id: header
                    text: qsTr(headertitle)
                }
                // List of Launcher modes
                ListView {
                    clip: true
                    width: parent.width
                    height: parent.height - header.height
                    model: launchModel
                    delegate: ListItem.Standard {
                        text: title
                        onClicked: {
                            //kobe: wait for adding function
                            caller.text = title
                            hide()
                        }
                    }
                }
            }
        }
    }
}
