import QtQuick 1.1
import SystemType 0.1
import "common" as Common

Item {
    id: listViewDelegate
    property int itemHeight: 40
    property string arrow: '../img/icons/arrow.png'
    property bool expanded: true
    property int heightMark:sub_num
    //需要传值:
    property string btn_flag
    property ListModel sub_model
    property int sub_num

    property bool delegate_flag: false
    //子项字体
    property string subItemFontName: "Helvetica"
    property int subItemFontSize: 10
    property color subItemFontColor: "black"

    //传出的值,控制子列表的伸缩
    signal subpressed(int hMark);
    signal checkchanged(bool checkchange);


    property int check_num:sub_num
    property bool maincheck: false
    width: parent.width

    Item {
        id: delegate
        property alias expandedItemCount: subItemRepeater.count
        x: 5; y: 2
        width: parent.width
        height: headerItemRect.height + subItemsRect.height

        //母项
        //checkbox, picture and words
        Row {
            id: headerItemRect
            x: 5; y: 2
            width: parent.width
            height: listViewDelegate.itemHeight
            spacing: 15
            Common.MainCheckBox{
                id:check
                checked:"true"
                anchors.verticalCenter: parent.verticalCenter
                onCheckedChanged: {
                }
            }
            Image {
                id: clearImage
                fillMode: "PreserveAspectFit"
                height: parent.height*0.9
                source: picture
                smooth: true
            }

            Column {
                id: status_update_content
                spacing: 5
                anchors.verticalCenter: parent.verticalCenter
                Text {
                    text: itemTitle
                    font.pointSize: 11
                    color: "black"
                }
                Text {
                    text: detailstr
                    font.family: "URW Bookman L"
                    font.pointSize: 9
                    color: "gray"
                }
            }
        }

        Image {
            id: arrow
            fillMode: "PreserveAspectFit"
//                    height: parent.height*0.3
            height: 28
            width: 26
            x:740
            y:15
            source: listViewDelegate.arrow
            //当鼠标点击后,箭头图片旋转90度
//                    rotation: expanded ? 90 : 0
            rotation: expanded ? 0 : -180
            smooth: true
            MouseArea {
                id: mouseRegion
                anchors.fill: parent
                    onPressed: {
                           expanded = !expanded
                        if(heightMark==listViewDelegate.sub_num)
                            heightMark=0;
                        else
                            heightMark=listViewDelegate.sub_num;
                        listViewDelegate.subpressed(heightMark);
                    }
            }
        }

        //子项
        Item {
            id: subItemsRect
            property int itemHeight: listViewDelegate.itemHeight
            y: headerItemRect.height
            width: 850
            //当高度需要扩展时,根据expandedItemCount数目和itemHeight高度去扩展
            height: expanded ? delegate.expandedItemCount * itemHeight : 0
            clip: true
            opacity: 1
            ListView{
                id: subItemRepeater
                width: listViewDelegate.width
                model: sub_model
                delegate: ldelegate
                anchors.fill: parent
            }
            Component{
                id:ldelegate

                ListItem {
                    id: subListItem
                    split_status: listViewDelegate.delegate_flag
                    width: subItemsRect.width
                    height: subItemsRect.itemHeight
//                            text: subItemTitle
                    text: itemTitle
                    descript: desc
                    size_num: number
                    checkbox_status: check.checkedbool
//                            bgImage: "../../img/icons/list_subitem.png"
                    bgImage: ""
                    fontName: listViewDelegate.subItemFontName
                    fontSize: listViewDelegate.subItemFontSize
                    fontColor: listViewDelegate.subItemFontColor
                    textIndent: 20
                    btn_flag: listViewDelegate.btn_flag
                    onClicked: {}
                    onChange_num: {
                        if(check_status==true)
                            check_num=check_num+1;
                        else
                            check_num=check_num-1;
                        if(sub_num!=0&&check_num ==0/*&&check.checked!="false"*/)
                            check.checked="false";
                        else if(sub_num!=0&&check_num ==sub_num/*&&check.checked!= "true"*/)
                            check.checked="true";
                        else if(sub_num!=0)
                            check.checked="mid";
                        if(check.checked=="true"||listViewDelegate.check_num>0)
                            listViewDelegate.checkchanged(true);
                        else
                            listViewDelegate.checkchanged(false);
                    }
                }
            }
        }//子项Item
    }

}//Component

