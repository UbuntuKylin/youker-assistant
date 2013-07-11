/****************************************************************************
 **
 ** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
 ** Contact: http://www.qt-project.org/legal
 **
 ** This file is part of the QtDeclarative module of the Qt Toolkit.
 **
 ** $QT_BEGIN_LICENSE:LGPL$
 ** Commercial License Usage
 ** Licensees holding valid commercial Qt licenses may use this file in
 ** accordance with the commercial license agreement provided with the
 ** Software or, alternatively, in accordance with the terms contained in
 ** a written agreement between you and Digia.  For licensing terms and
 ** conditions see http://qt.digia.com/licensing.  For further information
 ** use the contact form at http://qt.digia.com/contact-us.
 **
 ** GNU Lesser General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU Lesser
 ** General Public License version 2.1 as published by the Free Software
 ** Foundation and appearing in the file LICENSE.LGPL included in the
 ** packaging of this file.  Please review the following information to
 ** ensure the GNU Lesser General Public License version 2.1 requirements
 ** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
 **
 ** In addition, as a special exception, Digia gives you certain additional
 ** rights.  These rights are described in the Digia Qt LGPL Exception
 ** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
 **
 ** GNU General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU
 ** General Public License version 3.0 as published by the Free Software
 ** Foundation and appearing in the file LICENSE.GPL included in the
 ** packaging of this file.  Please review the following information to
 ** ensure the GNU General Public License version 3.0 requirements will be
 ** met: http://www.gnu.org/copyleft/gpl.html.
 **
 **
 ** $QT_END_LICENSE$
 **
 ****************************************************************************/
import QtQuick 1.1
import QtDesktop 0.1
import SessionType 0.1
import SystemType 0.1
Item {
     id: titleBar
     property SessionDispatcher dis1: sessiondispatcher
     property SystemDispatcher dis2: systemdispatcher
     property string btn_text: "一键清理"
     property string title: "一键清理系统垃圾，有效提高系统运行效率"
     property string description: "全面清理垃圾、痕迹、注册表，高效率解决系统清理问题"
     property string btn_flag: "one_key_scan"
     property string work_result: ""

     signal dataRequired();

     //信号绑定，绑定qt的信号finishCleanWork，该信号emit时触发onFinishCleanWork
     Connections
     {
         target: systemdispatcher
         onFinishCleanWork: {
             if (btn_flag == "one_key_work") {
                 console.log(msg);
                 titleBar.work_result = msg;
                 titleBar.state = "OneKeyFinish";
             }
             if (btn_flag == "history_work") {
                 console.log("******Signal handler received  Start******")
                 console.log(msg);
                 titleBar.state = "HistoryWorkFinish";
                 console.log("******End******");
             }
             else if (btn_flag == "cookies_work") {
                 console.log(msg);
                 titleBar.state = "CookiesWorkFinish";
             }
         }
     }



     BorderImage {
         source: "../../img/icons/unselect.png"
         width: parent.width
         height: parent.height + 14
         y: -7
     }
     Row {
         anchors.fill: parent
         anchors.left: parent.left
         anchors.leftMargin: 30
         spacing: 30
         id: container
         width: (parent.width * 2) - 55 ; height: parent.height

         Column {
             anchors.verticalCenter: parent.verticalCenter
             anchors.left: parent.left
             anchors.leftMargin: 30
             width: parent.width - 150
             spacing: 2
             Text {
                 text: qsTr(title)
                 color: "black"
                 font.pixelSize: 16
                 /*; font.bold: true; elide: Text.ElideRight; style: Text.Raised; styleColor: "black" */
             }
             Text {
                 text: qsTr(description)
                 color: "gray"
                 font.pixelSize: 14
                 /*; elide: Text.ElideLeft; color: "gray"; style: Text.Raised; styleColor: "black" */
             }
         }

         Label {
             id: label
             visible: false
             text: ""
             anchors.right: bitButton.left
             anchors.rightMargin: 20
             anchors.verticalCenter: parent.verticalCenter
         }

         Button {
             id: bitButton
             width: 95
             height: 32
             text: btn_text
             anchors.right: parent.right
             anchors.rightMargin: 50
             onClicked: {
                 //kobe: wait for adding function
                 var str = sessiondispatcher.get_str();
                 console.log('cccccc-------');
                 console.log(str)
                 //one key
                 if (btn_flag == "one_key_scan") {
                    if (str.indexOf("r") > -1 || str.indexOf("h") > -1 || str.indexOf("c") > -1 || str.indexOf("p") > -1) {
                        titleBar.state = "OneKeyWork";
                        if (str.indexOf("r") > -1)
                            console.log("rrrrrrrrrrr");
                        if (str.indexOf("h") > -1)
                            console.log("hhhhhhhhhhh");
                        if (str.indexOf("c") > -1)
                            console.log("ccccccccccc");
                        if (str.indexOf("p") > -1)
                            console.log("pppppppppppp");
                    }
                    else {
                        sessiondispatcher.send_warningdialog_msg("对不起，您没有选中一键清理的任何扫描项，请确认！");
                    }
                 }
                 else if (btn_flag == "one_key_work") {
                      if (str.indexOf("r") > -1 || str.indexOf("h") > -1 || str.indexOf("c") > -1 || str.indexOf("p") > -1) {
                          systemdispatcher.clean_the_browser_qt("history");//kobe: need to add other function
                      }
                     else
                          sessiondispatcher.send_warningdialog_msg("对不起，您没有选中历史记录清理项，请确认！");
                 }

                 //rubbish
                 else if (btn_flag == "rubbish") {
                     console.log("rubbish");
                     if (str.indexOf("r") > -1)
                         console.log("rrrrrrrrrrrrr");
                     else
                         console.log("nrnrnrnrnrnrnr");
                 }


                 //broswer history
                 else if (btn_flag == "history_scan") {
                     console.log("dddddd------------");
                      if (str.indexOf("h") > -1)
                          titleBar.state = "HistoryWork";
                     else
                          sessiondispatcher.send_warningdialog_msg("对不起，您没有选中历史记录扫描项，请确认！");
                 }
                 else if (btn_flag == "history_work") {
                     console.log("eeeeeee-------------");
                      if (str.indexOf("h") > -1)
//                          dataRequired();
                          systemdispatcher.clean_the_browser_qt("history");
                     else
                          sessiondispatcher.send_warningdialog_msg("对不起，您没有选中历史记录清理项，请确认！");
                 }

                //broswer cookies
                 else if (btn_flag == "cookies_scan") {
                     if (str.indexOf("c") > -1)
                         titleBar.state = "CookiesWork";
                     else
                         sessiondispatcher.send_warningdialog_msg("对不起，您没有选中Cookies扫描项，请确认！");
                 }
                 else if (btn_flag == "cookies_work") {
                     if (str.indexOf("c") > -1)
                         systemdispatcher.clean_the_browser_qt("cookies");
                     else
                         sessiondispatcher.send_warningdialog_msg("对不起，您没有选中Cookies清理项，请确认！");
                 }

                 //plugins
                 else if (btn_flag == "plugins") {
                     console.log("plugins");
                     pageStack.pop();
 //                    pageStack.push(pluginlist);
                     pageStack.push(Qt.resolvedUrl("../ItemListModel.qml"));
                 }
             }
             anchors.verticalCenter: parent.verticalCenter
         }
     }


     states: [
         State {
             name: "HistoryWork"
             PropertyChanges { target: label; visible: true; text: "共扫描到" + systemdispatcher.get_the_record_qt("history") + "条历史记录" }
             PropertyChanges { target: bitButton; text: "开始清理" }
             PropertyChanges { target: titleBar; btn_flag: "history_work" }
         },
         State {
             name: "CookiesWork"
             PropertyChanges { target: label; visible: true; text: "共扫描到" + systemdispatcher.get_the_record_qt("cookies") + "条Cookies" }
             PropertyChanges { target: bitButton; text: "开始清理" }
             PropertyChanges { target: titleBar; btn_flag: "cookies_work" }
         },
         State {
             name: "OneKeyWork"
             PropertyChanges { target: label; visible: true; text: "one key scan" }
//             PropertyChanges { target: label; visible: true; text: "共扫描到" + systemdispatcher.get_the_record_qt("cookies") + "条Cookies" }
             PropertyChanges { target: bitButton; text: "开始清理" }
             PropertyChanges { target: titleBar; btn_flag: "one_key_work" }
         },
         State {
             name: "HistoryWorkFinish"
             PropertyChanges { target: label; visible: true; text: "清理完毕！" }
             PropertyChanges { target: bitButton; text: "开始扫描" }
             PropertyChanges { target: titleBar; btn_flag: "history_scan" }
         },
         State {
             name: "CookiesWorkFinish"
             PropertyChanges { target: label; visible: true; text: "清理完毕！" }
             PropertyChanges { target: bitButton; text: "开始扫描" }
             PropertyChanges { target: titleBar; btn_flag: "cookies_scan" }
         },
         State {
             name: "OneKeyFinish"
             PropertyChanges { target: label; visible: true; text: titleBar.work_result + "清理完毕！" }
             PropertyChanges { target: bitButton; text: "开始扫描" }
             PropertyChanges { target: titleBar; btn_flag: "one_key_scan" }
         }
     ]
 }
