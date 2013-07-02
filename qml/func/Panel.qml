import QtQuick 1.1
import QtDesktop 0.1

Rectangle {
    id:root

    width: parent.width
    height: 420
    color:"#c3c3c3"

    ScrollArea {
        frame:false
        anchors.fill: parent
        Item {
            width:parent.width
            height:600

            //右边栏
            BorderImage {
                id: page
                source: "../img/icons/unselect.png"
//                anchors.right: parent.right
                anchors.left: parent.left
                anchors.leftMargin: 160
                width: 850 - 160; height: parent.height
                border.left: 12; border.top: 12
                border.right: 12; border.bottom: 12
                Text {
                    id:text
                    anchors.fill: parent
                    anchors.margins: 40
                    text:textfield.text
                }
                Rectangle {
                    border.color: "#444"
                    anchors.centerIn: parent
                    color: Qt.rgba(s1.value, s2.value, s3.value)
                    width: 200
                    height: width
                }

            }

            //左边栏
            BorderImage {
                id: sidebar
                source: "../img/icons/unselect.png"
                anchors.left: parent.left
//                anchors.right: parent.right
                anchors.top: parent.top
                width: show ? 160 : 10
                height:parent.height
                Behavior on width { NumberAnimation { easing.type: Easing.OutSine ; duration: 250 } }
                property bool show: false
                border.left: 0;
                border.right: 26;
//                border.left: 26;
//                border.right: 0;
                MouseArea {
                    id:mouseArea
                    anchors.fill: parent
                    onClicked: sidebar.show = !sidebar.show
                }



                Column {
                    id: panel1
                    opacity: sidebar.show ? 1 : 0
                    Behavior on opacity { NumberAnimation { easing.type:Easing.InCubic; duration: 600} }

                    scale: sidebar.show ? 1 : 0
                    Behavior on scale { NumberAnimation { easing.type:Easing.InCubic; duration: 200 } }
                    transformOrigin: Item.Top

                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.margins: 12
                    spacing:12

                    Button { width: parent.width - 12; text: "Close Panel"; onClicked: sidebar.show = false}
                    TextField{ id:textfield; text: "Some text" ; width: parent.width - 12}
                    SpinBox { width: parent.width - 12}
                    CheckBox{ id: expander; text:"Sliders"}
                }


                Column {
                    id: panel2
                    opacity: expander.checked && sidebar.show ? 1 : 0
                    scale: opacity
                    Behavior on opacity{ NumberAnimation { easing.type:Easing.OutSine; duration: 300}}
                    transformOrigin: Item.Top
                    anchors.top: panel1.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.margins: 12
                    spacing: 12
                    Slider { id: s1; width:parent.width - 12; value:0.5}
                    Slider { id: s2; width:parent.width - 12; value:0.5}
                    Slider { id: s3; width:parent.width - 12; value:0.5}

                }
            }
        }
    }
}





//ApplicationWindow {
//    id: window
//    width: parent.width
//    height: 460

//    SystemPalette { id: palette }

//    Settings { // Store persistant settings here
//        property alias width: window.width
//        property alias height: window.height
//    }

//    toolBar: ToolBar{
//        RowLayout {
//            anchors.fill: parent
//            anchors.margins: 8
//            ToolButton {
//                iconSource: "images/media-skip-backward.png"
//            }
//            ToolButton {
//                iconSource: "images/media-playback-pause.png"
//            }
//            ToolButton {
//                iconSource: "images/media-skip-forward.png"
//            }
//            Label{
//                text: "0:00"
//            }
//            Slider{
//                id: slider
//                Layout.horizontalSizePolicy: Layout.Expanding
//            }
//            Label{
//                text: "4:00"
//            }
//            TextField {
//                id: searchedit
//                styleHint: "rounded"
//            }
//        }
//    }

//    statusBar: StatusBar {
//        Label {
//            anchors.centerIn: parent
//            text: "Currently playing track"
//        }
//    }

//    SplitterRow {
//        anchors.fill: parent
//        handleWidth: 1
//        Item {
//            width: 160
//            Splitter.maximumWidth: 200
//            Splitter.minimumWidth: 50
//            TableView {
//                id: view
//                frame: false
//                alternateRowColor: false
//                backgroundColor: palette.alternateBase
//                anchors.top: parent.top
//                anchors.bottom: albumview.top
//                TableColumn{
//                    title: "Playlists"
//                    role: "name"
//                    elideMode: Text.ElideRight
//                }
//                model: ListModel {
//                    Component.onCompleted: {
//                        for (var i = 0 ; i < 10 ; ++i)
//                            append( {"name" : "Playlist "+i})
//                    }
//                }
//            }
//            Image {
//                id: albumview
//                anchors.bottom: parent.bottom
//                width: parent.width
//                height: parent.width
//                fillMode: Image.PreserveAspectCrop
//                clip: true
//                source: "images/album.jpg"
//                Rectangle {
//                    anchors.top: parent.top
//                    width: parent.width
//                    height: 1
//                    color: palette.dark
//                }
//            }
//        }
//        TableView {
//            frame: false
//            TableColumn{
//                title: "Track"
//                role: "name"
//            }
//            TableColumn{
//                title: "Artist"
//                role: "artist"
//            }
//            TableColumn{
//                title: "Album"
//                role: "album"
//            }
//            model: ListModel {
//                Component.onCompleted: {
//                    for (var i = 0 ; i < 100 ; ++i)
//                        append( {"name" : "Track "+i,
//                                 "artist" : "Artist "+i,
//                                 "album" : "Album "+i})
//                }
//            }
//        }
//    }
//}





//Item {
//    width: parent.width
//    height: 460

//    property real defaultWidth: 30
//    property real defaultHeight: 30

//    TabFrame {
//        id:frame
//        anchors.fill: parent

//        Tab {
//            title: "Horizontal"

//            Column {
//                spacing: 4

//                anchors {
//                    top: parent.top
//                    left: parent.left
//                    right: parent.right
//                    margins: 10
//                }

//                // [1]
//                RowLayout {
//                    height: defaultHeight
//                    anchors.left: parent.left
//                    anchors.right: parent.right

//                    Rectangle {
//                        color: "red"
//                        height: parent.height
//                    }
//                    Rectangle {
//                        color: "green"
//                        height: parent.height
//                    }
//                    Rectangle {
//                        color: "blue"
//                        height: parent.height
//                    }
//                }

//                // [2]
//                RowLayout {
//                    height: defaultHeight
//                    anchors.left: parent.left
//                    anchors.right: parent.right

//                    spacing: 5

//                    Rectangle {
//                        color: "red"
//                        height: parent.height
//                    }
//                    Rectangle {
//                        color: "green"
//                        height: parent.height
//                    }
//                    Item {
//                        implicitWidth: 10
//                    }
//                    Rectangle {
//                        color: "blue"
//                        height: parent.height
//                    }
//                }

//                // [3]
//                RowLayout {
//                    height: defaultHeight
//                    anchors.left: parent.left
//                    anchors.right: parent.right

//                    Rectangle {
//                        color: "red"
//                        height: parent.height
//                        Layout.minimumWidth: 50
//                        Layout.maximumWidth: 100
//                        Layout.horizontalSizePolicy: Layout.Expanding
//                    }
//                    Rectangle {
//                        color: "green"
//                        height: parent.height
//                        Layout.minimumWidth: 100
//                        Layout.maximumWidth: 200
//                        Layout.horizontalSizePolicy: Layout.Expanding
//                    }
//                    Rectangle {
//                        color: "blue"
//                        height: parent.height
//                        Layout.minimumWidth: 200
//                        Layout.maximumWidth: 400
//                        Layout.horizontalSizePolicy: Layout.Expanding
//                    }
//                }

//                // [4]
//                RowLayout {
//                    spacing: 100
//                    height: defaultHeight
//                    anchors.left: parent.left
//                    anchors.right: parent.right

//                    Rectangle {
//                        color: "red"
//                        height: parent.height
//                        Layout.minimumWidth: 100
//                        Layout.horizontalSizePolicy: Layout.Expanding
//                    }
//                    Rectangle {
//                        color: "green"
//                        height: parent.height
//                        Layout.minimumWidth: 200
//                        Layout.horizontalSizePolicy: Layout.Expanding
//                    }
//                    Rectangle {
//                        color: "blue"
//                        height: parent.height
//                        Layout.minimumWidth: 300
//                        Layout.horizontalSizePolicy: Layout.Expanding
//                    }
//                }

//                // [5]
//                RowLayout {
//                    height: defaultHeight
//                    anchors.left: parent.left
//                    anchors.right: parent.right

//                    Rectangle {
//                        color: "red"
//                        height: parent.height
//                        Layout.minimumWidth: 200
//                        Layout.maximumWidth: 500
//                        Layout.horizontalSizePolicy: Layout.Expanding
//                    }
//                }

//                // [6]
//                RowLayout {
//                    spacing: 40
//                    height: defaultHeight
//                    anchors.left: parent.left
//                    anchors.right: parent.right

//                    RowLayout {
//                        spacing: 10
//                        height: parent.height

//                        Rectangle {
//                            color: "red"
//                            height: parent.height
//                            Layout.minimumWidth: 100
//                            Layout.horizontalSizePolicy: Layout.Expanding
//                        }
//                        Rectangle {
//                            color: "blue"
//                            height: parent.height
//                            Layout.minimumWidth: 200
//                            Layout.horizontalSizePolicy: Layout.Expanding
//                        }
//                    }

//                    RowLayout {
//                        spacing: 10
//                        height: parent.height

//                        Rectangle {
//                            color: "green"
//                            height: parent.height
//                            Layout.maximumWidth: 300
//                            Layout.horizontalSizePolicy: Layout.Expanding
//                        }
//                        Rectangle {
//                            color: "red"
//                            height: parent.height
//                            Layout.minimumWidth: 40
//                            Layout.maximumWidth: 100
//                            Layout.horizontalSizePolicy: Layout.Expanding
//                        }
//                    }
//                }
//            }
//        }


//        Tab {
//            title: "Vertical"

//            Row {
//                spacing: 4

//                anchors {
//                    top: parent.top
//                    left: parent.left
//                    bottom: parent.bottom
//                    margins: 10
//                }

//                // [1]
//                ColumnLayout {
//                    width: defaultWidth
//                    anchors.top: parent.top
//                    anchors.bottom: parent.bottom

//                    Rectangle {
//                        color: "red"
//                        width: parent.width
//                    }
//                    Rectangle {
//                        color: "green"
//                        width: parent.width
//                    }
//                    Rectangle {
//                        color: "blue"
//                        width: parent.width
//                    }
//                }

//                // [2]
//                ColumnLayout {
//                    width: defaultWidth
//                    anchors.top: parent.top
//                    anchors.bottom: parent.bottom

//                    spacing: 5

//                    Rectangle {
//                        color: "red"
//                        width: parent.width
//                    }
//                    Rectangle {
//                        color: "green"
//                        width: parent.width
//                    }
//                    Item {
//                        implicitWidth: 10
//                    }
//                    Rectangle {
//                        color: "blue"
//                        width: parent.width
//                    }
//                }

//                // [3]
//                ColumnLayout {
//                    width: defaultWidth
//                    anchors.top: parent.top
//                    anchors.bottom: parent.bottom

//                    Rectangle {
//                        color: "red"
//                        width: parent.width
//                        Layout.minimumHeight: 50
//                        Layout.maximumHeight: 100
//                        Layout.verticalSizePolicy: Layout.Expanding
//                    }
//                    Rectangle {
//                        color: "green"
//                        width: parent.width
//                        Layout.minimumHeight: 100
//                        Layout.maximumHeight: 200
//                        Layout.verticalSizePolicy: Layout.Expanding
//                    }
//                    Rectangle {
//                        color: "blue"
//                        width: parent.width
//                        Layout.minimumHeight: 200
//                        Layout.maximumHeight: 400
//                        Layout.verticalSizePolicy: Layout.Expanding
//                    }
//                }

//                // [4]
//                ColumnLayout {
//                    spacing: 100
//                    width: defaultWidth
//                    anchors.top: parent.top
//                    anchors.bottom: parent.bottom

//                    Rectangle {
//                        color: "red"
//                        width: parent.width
//                        Layout.minimumHeight: 100
//                        Layout.verticalSizePolicy: Layout.Expanding
//                    }
//                    Rectangle {
//                        color: "green"
//                        width: parent.width
//                        Layout.minimumHeight: 200
//                        Layout.verticalSizePolicy: Layout.Expanding
//                    }
//                    Rectangle {
//                        color: "blue"
//                        width: parent.width
//                        Layout.minimumHeight: 300
//                        Layout.verticalSizePolicy: Layout.Expanding
//                    }
//                }

//                // [5]
//                ColumnLayout {
//                    width: defaultWidth
//                    anchors.top: parent.top
//                    anchors.bottom: parent.bottom

//                    Rectangle {
//                        color: "red"
//                        width: parent.width
//                        Layout.minimumHeight: 200
//                        Layout.maximumHeight: 500
//                        Layout.verticalSizePolicy: Layout.Expanding
//                    }
//                }

//                // [6]
//                ColumnLayout {
//                    spacing: 40
//                    width: defaultWidth
//                    anchors.top: parent.top
//                    anchors.bottom: parent.bottom

//                    ColumnLayout {
//                        spacing: 10
//                        width: parent.width

//                        Rectangle {
//                            color: "red"
//                            width: parent.width
//                            Layout.minimumHeight: 100
//                            Layout.verticalSizePolicy: Layout.Expanding
//                        }
//                        Rectangle {
//                            color: "blue"
//                            width: parent.width
//                            Layout.minimumHeight: 200
//                            Layout.verticalSizePolicy: Layout.Expanding
//                        }
//                    }

//                    ColumnLayout {
//                        spacing: 10
//                        width: parent.width

//                        Rectangle {
//                            color: "green"
//                            width: parent.width
//                            Layout.maximumHeight: 300
//                            Layout.verticalSizePolicy: Layout.Expanding
//                        }
//                        Rectangle {
//                            color: "red"
//                            width: parent.width
//                            Layout.minimumHeight: 40
//                            Layout.maximumHeight: 100
//                            Layout.verticalSizePolicy: Layout.Expanding
//                        }
//                    }
//                }
//            }
//        }


//        Tab {
//            title: "Horizontal and Vertical"

//            ColumnLayout {
//                anchors.fill: parent

//                // [1]
//                RowLayout {
//                    height: defaultHeight
//                    anchors.left: parent.left
//                    anchors.right: parent.right

//                    Layout.minimumHeight: 100

//                    Rectangle {
//                        color: "red"
//                        height: parent.height
//                        Layout.horizontalSizePolicy: Layout.Expanding
//                    }
//                    Rectangle {
//                        color: "green"
//                        height: parent.height
//                        implicitWidth: 100
//                    }
//                    Rectangle {
//                        color: "blue"
//                        height: parent.height
//                        Layout.horizontalSizePolicy: Layout.Expanding
//                    }
//                }

//                // [2]
//                Rectangle {
//                    color: "yellow"
//                    height: parent.height
//                    anchors.left: parent.left
//                    anchors.right: parent.right
//                    Layout.minimumHeight: 10
//                    Layout.maximumHeight: 30
//                    Layout.horizontalSizePolicy: Layout.Expanding
//                    Layout.verticalSizePolicy: Layout.Expanding
//                }

//                // [3]
//                RowLayout {
//                    height: defaultHeight
//                    anchors.left: parent.left
//                    anchors.right: parent.right

//                    Rectangle {
//                        color: "red"
//                        height: parent.height
//                        Layout.maximumHeight: 200
//                        Layout.horizontalSizePolicy: Layout.Expanding
//                    }
//                    Rectangle {
//                        color: "blue"
//                        height: parent.height

//                        ColumnLayout {
//                            anchors.fill: parent
//                            spacing: 10
//                            opacity: 0.6

//                            Rectangle {
//                                color: "darkRed"
//                                height: parent.height
//                                anchors.left: parent.left
//                                anchors.right: parent.right
//                                Layout.minimumHeight: 100
//                                Layout.maximumHeight: 200
//                                Layout.verticalSizePolicy: Layout.Expanding
//                            }

//                            Rectangle {
//                                color: "darkGreen"
//                                height: parent.height
//                                anchors.left: parent.left
//                                anchors.right: parent.right
//                                Layout.verticalSizePolicy: Layout.Expanding
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }
//}




//Rectangle {

//    width: 538 + frame.margins * 2
//    height: 360 + frame.margins * 2

//    ToolBar {
//        id: toolbar
//        width: parent.width
//        //height: 40

//        MouseArea {
//            anchors.fill:  parent
//            acceptedButtons: Qt.RightButton
//            onPressed: editmenu.show(mouseX, mouseY)
//        }

//        ComboBox {
//            id: delegateChooser
//            enabled: frame.current == 4 ? 1 : 0
//            model: delegatemenu
//            anchors.left: parent.left
//            anchors.leftMargin: 8
//            anchors.verticalCenter: parent.verticalCenter
//        }

//        CheckBox {
//            id: enabledCheck
//            text: "Enabled"
//            checked: true
//            anchors.right: parent.right
//            anchors.verticalCenter: parent.verticalCenter
//        }
//    }

//    SystemPalette {id: syspal}
//    StyleItem{ id: styleitem}
//    color: syspal.window

//    XmlListModel {
//        id: flickerModel
//        source: "http://api.flickr.com/services/feeds/photos_public.gne?format=rss2&tags=" + "Qt"
//        query: "/rss/channel/item"
//        namespaceDeclarations: "declare namespace media=\"http://search.yahoo.com/mrss/\";"
//        XmlRole { name: "title"; query: "title/string()" }
//        XmlRole { name: "imagesource"; query: "media:thumbnail/@url/string()" }
//        XmlRole { name: "credit"; query: "media:credit/string()" }
//    }

//    ListModel {
//        id: nestedModel
//        ListElement{attributes:  ListElement { description: "Core" ; color:"#ffaacc"}}
//        ListElement{attributes: ListElement { description: "Second" ; color:"#ffccaa"}}
//        ListElement{attributes: ListElement { description: "Third" ; color:"#ffffaa"}}
//    }

//    ListModel {
//        id: largeModel
//        Component.onCompleted: {
//            for (var i=0 ; i< 5000 ; ++i)
//                largeModel.append({"name":"Person "+i , "age": Math.round(Math.random()*100), "gender": Math.random()>0.5 ? "Male" : "Female"})
//        }
//    }

//    Column {
//        anchors.top: toolbar.bottom
//        anchors.right: parent.right
//        anchors.left: parent.left
//        anchors.bottom:  parent.bottom
//        anchors.margins: 8

//        TabFrame {
//            id:frame
//            focus:true
//            enabled: toolbar.enabled

//            property int margins : styleitem.style == "mac" ? 16 : 0
//            height: parent.height - 34
//            anchors.right: parent.right
//            anchors.left: parent.left
//            anchors.margins: margins

//            Tab {
//                title: "XmlListModel"

//                TableView {
//                    model: flickerModel
//                    anchors.fill: parent
//                    anchors.margins: 12

//                    TableColumn {
//                        role: "title"
//                        title: "Title"
//                        width: 120
//                    }
//                    TableColumn {
//                        role: "credit"
//                        title: "Credit"
//                        width: 120
//                    }
//                    TableColumn {
//                        role: "imagesource"
//                        title: "Image source"
//                        width: 200
//                        visible: true
//                    }

//                    frame: frameCheckbox.checked
//                    headerVisible: headerCheckbox.checked
//                    sortIndicatorVisible: sortableCheckbox.checked
//                    alternateRowColor: alternateCheckbox.checked
//                }
//            }
//            Tab {
//                title: "DirModel"

//                TableView {
//                    model: FileSystemModel{}
//                    anchors.fill: parent
//                    anchors.margins: 12

//                    TableColumn {
//                        role: "fileName"
//                        title: "File Name"
//                        width: 120
//                    }
//                    TableColumn {
//                        role: "filePath"
//                        title: "File Path"
//                        width: 120
//                    }
//                    TableColumn {
//                        role: "fileSize"
//                        title: "Image source"
//                        width: 200
//                        visible: true
//                    }

//                    frame: frameCheckbox.checked
//                    headerVisible: headerCheckbox.checked
//                    sortIndicatorVisible: sortableCheckbox.checked
//                    alternateRowColor: alternateCheckbox.checked
//                }
//            }
//            Tab {
//                title: "Multivalue "

//                TableView {
//                    model: nestedModel
//                    anchors.fill: parent
//                    anchors.margins: 12

//                    TableColumn {
//                        role: "attributes"
//                        title: "Text and Color"
//                        width: 220
//                    }

//                    itemDelegate:
//                    Item {
//                        Rectangle{
//                            color: itemValue.get(0).color
//                            anchors.top:parent.top
//                            anchors.right:parent.right
//                            anchors.bottom:parent.bottom
//                            anchors.margins: 4
//                            width:32
//                            border.color:"#666"
//                        }
//                        Text {
//                            width: parent.width
//                            anchors.margins: 4
//                            anchors.left: parent.left
//                            anchors.verticalCenter: parent.verticalCenter
//                            elide: itemElideMode
//                            text: itemValue.get(0).description
//                            color: itemForeground
//                        }
//                    }

//                    frame: frameCheckbox.checked
//                    headerVisible: headerCheckbox.checked
//                    sortIndicatorVisible: sortableCheckbox.checked
//                    alternateRowColor: alternateCheckbox.checked
//                }
//            }
//            Tab {
//                title: "Generated"

//                TableView {
//                    model: largeModel
//                    anchors.margins: 12
//                    anchors.fill: parent
//                    TableColumn {
//                        role: "name"
//                        title: "Name"
//                        width: 120
//                    }
//                    TableColumn {
//                        role: "age"
//                        title: "Age"
//                        width: 120
//                    }
//                    TableColumn {
//                        role: "gender"
//                        title: "Gender"
//                        width: 120
//                    }
//                    frame: frameCheckbox.checked
//                    headerVisible: headerCheckbox.checked
//                    sortIndicatorVisible: sortableCheckbox.checked
//                    alternateRowColor: alternateCheckbox.checked
//                }
//            }

//            Tab {
//                title: "Delegates"

//                ListModel {
//                    id: delegatemenu
//                    ListElement { text: "Shiny delegate" }
//                    ListElement { text: "Scale selected" }
//                    ListElement { text: "Editable items" }
//                }

//                Component {
//                    id: delegate1
//                    Item {
//                        clip: true
//                        Text {
//                            width: parent.width
//                            anchors.margins: 4
//                            anchors.left: parent.left
//                            anchors.verticalCenter: parent.verticalCenter
//                            elide: itemElideMode
//                            text: itemValue ? itemValue : ""
//                            color: itemForeground
//                        }
//                    }
//                }

//                Component {
//                    id: slickRowDelegate
//                    Rectangle{
//                        color: itemAlternateBackground ? "#cef" : "white"
//                        //                            selected: itemSelected ? "true" : "false"
//                    }

//                }

//                Component {
//                    id: delegate2
//                    Item {
//                        height: itemSelected? 60 : 20
//                        Behavior on height{ NumberAnimation{}}
//                        Text {
//                            width: parent.width
//                            anchors.margins: 4
//                            anchors.left: parent.left
//                            anchors.verticalCenter: parent.verticalCenter
//                            elide: itemElideMode
//                            text: itemValue ? itemValue : ""
//                            color: itemForeground
//                        }
//                    }
//                }

//                Component {
//                    id: editableDelegate
//                    Item {
//                        Text {
//                            width: parent.width
//                            anchors.margins: 4
//                            anchors.left: parent.left
//                            anchors.verticalCenter: parent.verticalCenter
//                            elide: itemElideMode
//                            text: itemValue ? itemValue : ""
//                            color: itemForeground
//                            visible: !itemSelected
//                        }
//                        Loader { // Initialize text editor lazily to improve performance
//                            anchors.fill: parent
//                            anchors.margins: 4
//                            property string modelText: itemValue
//                            property string editorText: item ? item.text : itemValue
//                            onEditorTextChanged: model.setProperty(rowIndex, role, editorText)
//                            sourceComponent: itemSelected ? editor : null
//                            Component {id: editor ; TextInput{ color: itemForeground ; text: modelText} }
//                        }
//                    }
//                }
//                TableView {
//                    model: largeModel
//                    anchors.margins: 12
//                    anchors.fill:parent
//                    frame: frameCheckbox.checked
//                    headerVisible: headerCheckbox.checked
//                    sortIndicatorVisible: sortableCheckbox.checked
//                    alternateRowColor: alternateCheckbox.checked

//                    TableColumn {
//                        role: "name"
//                        title: "Name"
//                        width: 120
//                    }
//                    TableColumn {
//                        role: "age"
//                        title: "Age"
//                        width: 120
//                    }
//                    TableColumn {
//                        role: "sex"
//                        title: "Sex"
//                        width: 120
//                    }

//                    headerDelegate: BorderImage{
//                        source: "images/header.png"
//                        border{left:2;right:2;top:2;bottom:2}
//                        Text {
//                            text: itemValue
//                            anchors.centerIn:parent
//                            color:"#333"
//                        }
//                    }

//                    rowDelegate: Rectangle {
//                        color: itemSelected ? "#448" : (itemAlternateBackground ? "#eee" : "#fff")
//                        border.color:"#ccc"
//                        border.width: 1
//                        anchors.left: parent.left
//                        anchors.leftMargin: -2
//                        anchors.rightMargin: -1
//                        BorderImage{
//                            id:selected
//                            anchors.fill: parent
//                            source: "images/selectedrow.png"
//                            visible: itemSelected
//                            border{left:2;right:2;top:2;bottom:2}
//                            SequentialAnimation {
//                                running: true; loops: Animation.Infinite
//                                NumberAnimation { target:selected; property: "opacity"; to: 1.0; duration: 900}
//                                NumberAnimation { target:selected; property: "opacity"; to: 0.5; duration: 900}
//                            }
//                        }
//                    }

//                    itemDelegate: {
//                        switch(delegateChooser.selectedIndex) {
//                        case 0:
//                            return delegate1
//                        case 1:
//                            return delegate2
//                        case 2:
//                            return editableDelegate
//                        }
//                    }
//                }
//            }
//        }
//        Row{
//            x:12
//            height: 34
//            CheckBox{
//                id: alternateCheckbox
//                checked: true
//                text: "Alternate"
//                anchors.verticalCenter: parent.verticalCenter
//            }
//            CheckBox{
//                id: sortableCheckbox
//                checked: false
//                text: "Sortindicator"
//                anchors.verticalCenter: parent.verticalCenter
//            }
//            CheckBox{
//                id: frameCheckbox
//                checked: true
//                text: "Frame"
//                anchors.verticalCenter: parent.verticalCenter
//            }
//            CheckBox{
//                id: headerCheckbox
//                checked: true
//                text: "Headers"
//                anchors.verticalCenter: parent.verticalCenter
//            }
//        }
//    }
//}




//Rectangle {
//    width: parent.width
//    height: 460
//    color: syspal.window
//    SystemPalette{id:syspal}
//    SplitterRow {
//        id: sr
//        anchors.fill: parent
//        Item {
//            id: r1
//            Splitter.minimumWidth: 140
//            Splitter.expanding: false
//            width: 200
//            CheckBox {
//                id: be1
//                anchors.centerIn: parent
//                checked: parent.Splitter.expanding
//                text: "Set expanding"
//                onClicked: {
//                    parent.Splitter.expanding = true
//                    be2.checked = !parent.Splitter.expanding
//                }
//            }
//        }
//        Item {
//            id: r2
//            Splitter.minimumWidth: 140
//            Splitter.expanding: true
//            width: 200
//            CheckBox {
//                id: be2
//                anchors.centerIn: parent
//                text: "Set expanding"
//                checked: true
//                onClicked: {
//                    parent.Splitter.expanding = true
//                    be1.checked = !parent.Splitter.expanding
//                }
//            }
//        }
//        Item {
//            id: r3
//            Splitter.expanding: false
//            Splitter.minimumWidth: 140
//            width: 200
//            SplitterColumn {
//                id: sc
//                anchors.left: parent.left
//                anchors.right: parent.right
//                anchors.top: parent.top
//                anchors.bottom: parent.bottom
//                Item {
//                    id: cr1
//                    height:200
//                }
//                Item {
//                    id: cr2
//                    height: 200
//                }
//            }
//        }
//    }
//}



//Rectangle {
//    id: rect

//    width: 360
//    height: 360
//    color: "blue"

//    property string nextState: "green"

//    Text {
//        text: "Click me!"
//        color: "white"
//        anchors.centerIn: parent
//    }
//    MouseArea {
//        anchors.fill: parent
//        onClicked: rect.state = rect.nextState
//    }

//    states : [
//        State {
//            name: "blue"
//            PropertyChanges { target: rect; color: rect.nextState }
//            PropertyChanges { target: rect; nextState: rect.color }
//        },
//        State {
//            name: "green"
//            PropertyChanges { target: rect; color: rect.nextState }
//            PropertyChanges { target: rect; nextState: rect.color }
//        }
//    ]

//    Settings {
//        property alias state: rect.state
//        property alias width: rect.width
//        property alias height: rect.height
//    }
//}














//Item {
//    id: root
//    width: parent.width
//    height: 460

////    XmlListModel {
////        id: flickerModel
////        source: "http://api.flickr.com/services/feeds/photos_public.gne?format=rss2&tags=" + "Cat"
////        query: "/rss/channel/item"
////        namespaceDeclarations: "declare namespace media=\"http://search.yahoo.com/mrss/\";"
////        XmlRole { name: "title"; query: "title/string()" }
////        XmlRole { name: "imagesource"; query: "media:thumbnail/@url/string()" }
////        XmlRole { name: "credit"; query: "media:credit/string()" }
////    }

//    ListModel {
//        id: dummyModel
//        Component.onCompleted: {
//            for (var i = 0 ; i < 100 ; ++i) {
//                append({"title": "A title " + i, "imagesource" :"http://someurl.com", "credit" : "N/A"})
//            }
//        }
//    }

//    TableView{
//        model: dummyModel
//        anchors.fill: parent

//        TableColumn {
//            role: "title"
//            title: "Title"
//            width: 120
//        }
//        TableColumn {
//            role: "credit"
//            title: "Credit"
//            width: 120
//        }
//        TableColumn {
//            role: "imagesource"
//            title: "Image source"
//            width: 200
//            visible: true
//        }
//    }
//}





//Rectangle {
//    width: 540
//    height: 340
//    color: "white"
//    id : rect

//    Text {
//        id : selctedLabel
//        anchors.centerIn: parent
//        text : editMenu.selected
//    }

//    ContextMenu {
//        id : editMenu

//        // MenuItem API:
//        MenuItem {
//            text : "blue"
//            //onSelected : { rect.color = "blue" }
//        }
//        MenuItem {
//            text : "red"
//            //onSelected : { rect.color = "red" }
//        }
//        MenuItem {
//            text : "pink"
//            //onSelected : { rect.color = "pink" }
//        }

//        // ListModel API:
//        // # no way to do onSelected.
//        model: ListModel {
//            id: menu
//            ListElement { text: "Elememt1" }
//            ListElement { text: "Elememt2" }
//            ListElement { text: "Elememt2" }
//        }
//    }

//    MouseArea {
//        anchors.fill: parent
//        acceptedButtons : Qt.RightButton
//        onClicked: editMenu.showPopup(mouseX, mouseY)
//    }
//}
