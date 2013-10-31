/*
 * Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

import QtQuick 1.1
import "common" as Common

Item {
    id: itemtitle
    signal clicked
    width: parent.width
    height: 40
    property bool expanded: true
    property string imageSource: ""
    property string itemTitle: ""
    property string detailstr: ""
    property string arrowSource: "../img/icons/arrow.png"


    property int heightMark: sub_num
    property int sub_num
    property int arrow_display: 0   //控制清理界面下拉图标显示还是透明的变量
    property int check_num: sub_num   //记录子项个数，在确定总checkbox状态时需要的变量

    property bool checkboxStatus: true//主checkbox的状态
    signal subpressed(int hMark);

    Connections {
        target: sessiondispatcher
        //得到信号，改变主checkbox的状态
        onStartChangeMaincheckboxStatus: {
            check.checked = status;
        }
    }

    Row {
        id: chrominum
        width: parent.width
        spacing: 15
        Common.MainCheckBox{
            id: check
            checked: "true"
            anchors.verticalCenter: parent.verticalCenter
            onCheckedChanged: {
                itemtitle.checkboxStatus = check.checkedbool;
            }
        }
        Image {
            id: chrominumImage
            fillMode: "PreserveAspectFit"
            height: parent.height*0.9
            source: itemtitle.imageSource
            smooth: true
        }

        Column {
            id: chrominumColumn
            spacing: 5
            anchors.verticalCenter: parent.verticalCenter
            Text {
                text: itemtitle.itemTitle
                font.pointSize: 11
                color: "black"
            }
            Text {
                text: itemtitle.detailstr
                font.family: "URW Bookman L"
                font.pointSize: 9
                color: "gray"
            }
        }

        Image {
            id: chrominumarrow
            fillMode: "PreserveAspectFit"
            height: 28
            width: 26
            source: itemtitle.arrowSource
            opacity: itemtitle.arrow_display//这里初始为0,可以初始时将箭头隐藏,以后根据扫描内容确定其值
            rotation: itemtitle.expanded ? 0 : -180
            smooth: true
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    itemtitle.clicked();
                    itemtitle.expanded = !itemtitle.expanded;//扫描出的子项是否下拉显示的控制变量



                    if(itemtitle.heightMark == itemtitle.sub_num){//通过对heightMark的赋值来实现子项的下拉显示与收缩不显示
                        check.checkedbool=false;//子项收缩时,将总checkbox回到勾选状态
                        check.checked="true";
                        itemtitle.heightMark=0;
                    }
                    else if(itemtitle.heightMark==0) {
                        if(itemtitle.sub_num>0){//子项下拉显示时，根据总checkbox状态进行赋值控制
                            if(check.checked=="true") {
                                check.checkedbool = true;
                                itemtitle.check_num = itemtitle.sub_num;
                                check.checked = "true"
                            }
                            else if(check.checked=="false") {
                                itemtitle.check_num = itemtitle.sub_num-1;
                                check.checkedbool = false;
                                check.checked = "false"
                            }
                        }
                        itemtitle.heightMark=itemtitle.sub_num;
                    }
                    itemtitle.subpressed(itemtitle.heightMark); //将heightMark的值传给清理界面实现对是否下拉显示子项的控制
                }
            }
        }
    }
}
