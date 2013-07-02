import QtQuick 1.1

ListModel {
    id: model
    ListElement {
        itemTitle: "Item title 1"
        itemTitle1: "Item title 11"
        iconpath: "../img/icon/settings.png"
        attributes: [
            ListElement { subItemTitle: "kobe 1/1" },
            ListElement { subItemTitle: "kobe 2/1" }
        ]
    }
    ListElement {
        itemTitle: "Item title 2"
        itemTitle1: "Item title 22"
        iconpath: "../img/icon/history.png"
        attributes: [
            ListElement { subItemTitle: "kobe 1/3" },
            ListElement { subItemTitle: "kobe 2/3" },
            ListElement { subItemTitle: "kobe 3/3" }
        ]
    }
    ListElement {
        itemTitle: "Item title 3"
        itemTitle1: "Item title 33"
        iconpath: "../img/icon/about.png"
        attributes: [
            ListElement { subItemTitle: "kobe 1/4" },
            ListElement { subItemTitle: "kobe 2/4" },
            ListElement { subItemTitle: "kobe 3/4" },
            ListElement { subItemTitle: "kobe 4/4" }
        ]
    }
}

