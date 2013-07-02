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

 Item {
     id: titleBar

     BorderImage { source: "../../img/icons/unselect.png"; width: parent.width; height: parent.height + 14; y: -7 }

     Item {
         id: container
         width: (parent.width * 2) - 55 ; height: parent.height

         function accept() {
             rotateDetails.closed()
             titleBar.state = ""
             background.state = ""
         }

         Image {
             id: quitButton
             anchors.left: parent.left//; anchors.leftMargin: 0
             anchors.verticalCenter: parent.verticalCenter
             source: "../../img/icons/kysoft.png"
             MouseArea {
                 anchors.fill: parent
                 onClicked: Qt.quit()
             }
         }

         Text {
             id: categoryText
             anchors {
                 left: quitButton.right; right: tagButton.left; leftMargin: 10; rightMargin: 10
                 verticalCenter: parent.verticalCenter
             }
             elide: Text.ElideLeft
             text: "kobe's tags"
             font.bold: true; font.pixelSize: 15; color: "White"; style: Text.Raised; styleColor: "Black"
         }

         Button {
             id: tagButton; x: titleBar.width - 50; width: 45; height: 32; text: "..."
             onClicked: if (titleBar.state == "Tags") container.accept(); else titleBar.state = "Tags"
             anchors.verticalCenter: parent.verticalCenter
         }

         Item {
             id: lineEdit
             y: 4; height: parent.height - 9
             anchors { left: tagButton.right; leftMargin: 5; right: parent.right; rightMargin: 5 }

             BorderImage { source: "../../img/icons/tab.png"; anchors.fill: parent }

             TextInput {
                 id: editor
                 anchors {
                     left: parent.left; right: parent.right; leftMargin: 10; rightMargin: 10
                     verticalCenter: parent.verticalCenter
                 }
                 cursorVisible: true; font.bold: true
                 color: "#151515"; selectionColor: "Green"
             }

             Keys.forwardTo: [ (returnKey), (editor)]

             Item {
                 id: returnKey
                 Keys.onReturnPressed: container.accept()
                 Keys.onEnterPressed: container.accept()
                 Keys.onEscapePressed: titleBar.state = ""
             }
         }
     }

     //控制ｏｋ点击后换内容
     states: State {
         name: "Tags"
         PropertyChanges { target: container; x: -tagButton.x + 5 }
         PropertyChanges { target: tagButton; text: "OK" }
         PropertyChanges { target: editor; focus: true }
     }

     //控制换内容时的特效(当在两种状态Tags和默认状态间变化时便会触发Transition动画)
     transitions: Transition {
         NumberAnimation { properties: "x"; easing.type: Easing.InOutQuad }
     }
 }
