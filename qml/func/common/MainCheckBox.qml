import QtQuick 1.1
import StyleItemType 0.1
Item {
    id: maincheckbox
    property string checked: "true"
    property bool checkedbool: true
    property int minimumWidth: 13//32
    property int minimumHeight: 13//32
    width: minimumWidth
    height: minimumHeight
    Rectangle {
        anchors.fill: parent
        anchors.margins: 1
        radius: 5
        smooth:true
        Image {
            id:mainimage
            anchors.fill:parent
            source: "../../img/icons/checkbox-0.png"
        }
        Image{
            id:simage
            anchors.centerIn: mainimage
            source: "../../img/icons/checkbox.png"
        }
    }
    MouseArea {
        id: mouseArea
        anchors.fill: parent

        onClicked: {
            if(checked=="true")
                checked="false";
            else if(checked=="mid")
            {
                if(checkedbool==false)
                    checked="true"
                else if(checkedbool==true)
                    checked="false"
            }
            else if(checked=="false")
                checked="true"
        }
    }
    onCheckedChanged:{
        if(checked=="true")
        {
            simage.source="../../img/icons/checkbox.png";
            checkedbool=true;

        }
        else if(checked=="mid")
            simage.source="../../img/icons/checkbox-2.png"
        else if(checked=="false")
        {
            simage.source=""
            checkedbool=false;
        }
    }
}

