import QtQuick 1.1
import StyleItemType 0.1
Item {
    id: maincheckbox
    property string checked: "true"    //保存总checkbox处于三种状态中的哪种
    property bool checkedbool: true      //总checkbox的bool型值，check通有的属性，在单独点击总checkbox时进行总控制的变量
    property int minimumWidth: 15//32
    property int minimumHeight: 15//32
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
            if(checked=="true")   //当总check处于true状态时，点击后变成false状态
                checked="false";
            else if(checked=="mid")  //当总check处于中间态时，点击后根据总check的bool型值决定变成true状态还是false状态
            {
                if(checkedbool==false)
                    checked="true"
                else if(checkedbool==true)
                    checked="false"
            }
            else if(checked=="false")  //当总check处于false态时，点击后变成true状态
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

