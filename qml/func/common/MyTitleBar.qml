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
 Item {
     id: titleBar
     property string btn_text: "一键清理"
     property string title: "一键清理系统垃圾，有效提高系统运行效率"
     property string description: "全面清理垃圾、痕迹、注册表，高效率解决系统清理问题"
     property string btn_flag: "one_key"
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

         Button {
             id: bitButton
             width: 95
             height: 32
             text: btn_text
             anchors.right: parent.right
             anchors.rightMargin: 50
             onClicked: {
                 //kobe: wait for adding function
                 if (btn_flag == "one_key") {
                     console.log("one_key");
                 }
                 else if (btn_flag == "rubbish") {
                     console.log("rubbish");
                 }
                 else if (btn_flag == "plugins") {
                     console.log("plugins");
                     pageStack.pop();
 //                    pageStack.push(pluginlist);
                     pageStack.push(Qt.resolvedUrl("../PluginList.qml"));
                 }
                 else if (btn_flag == "traces") {
                     console.log("traces");
                 }
             }
             anchors.verticalCenter: parent.verticalCenter
         }
     }
 }
