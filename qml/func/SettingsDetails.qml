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
 Rectangle {
     id: settigsDetails

     property string setTitle: ""
     signal closed

     transform: Rotation {
         id: itemRotation
         origin.x: settigsDetails.width / 2;
         axis.y: 1; axis.z: 0
     }



    Item {
         id: containerFront; anchors.fill: settigsDetails

         Rectangle {
             anchors.fill: parent
             color: "black"; opacity: 0.4
         }

//         Column {
//             id: launchercolumn
//             spacing: 10
//             visible: false
//             anchors {
//                 left: parent.left; leftMargin: 10
//                 right: parent.right; rightMargin: 10
//                 top: parent.top; topMargin: 120
//             }
//             Text { font.bold: true; color: "white"; elide: Text.ElideRight; text: "container.photoTitle"; width: parent.width }
//             Text { color: "white"; elide: Text.ElideRight; text: "Size: "; width: parent.width }
//             Text { color: "white"; elide: Text.ElideRight; text: "Type: "; width: parent.width }
//             Text { color: "white"; elide: Text.ElideRight; text: "Author: "; width: parent.width }
//             Text { color: "white"; elide: Text.ElideRight; text: "Published: "; width: parent.width }
//             Text { color: "white"; elide: Text.ElideRight; text: "container.photoTags"; width: parent.width }
//             Text { color: "white"; elide: Text.ElideRight; text: "container.photoTags"; width: parent.width }
//         }


//         Column {
//             id: searchcolumn
//             visible: false
//             spacing: 10
//             anchors {
//                 left: parent.left; leftMargin: 10
//                 right: parent.right; rightMargin: 10
//                 top: parent.top; topMargin: 120
//             }
//             Text { font.bold: true; color: "white"; elide: Text.ElideRight; text: "container.photoTitle"; width: parent.width }
//             Text { color: "white"; elide: Text.ElideRight; text: "jjj: "; width: parent.width }
//             Text { color: "white"; elide: Text.ElideRight; text: "jjj: "; width: parent.width }
//             Text { color: "white"; elide: Text.ElideRight; text: "aaa: "; width: parent.width }
//             Text { color: "white"; elide: Text.ElideRight; text: "bbb: "; width: parent.width }
//             Text { color: "white"; elide: Text.ElideRight; text: "ccc.photoTags"; width: parent.width }
//             Text { color: "white"; elide: Text.ElideRight; text: "ggg.photoTags"; width: parent.width }
//         }

         Launcher {
             id: launchpage
             visible: false
         }
         Search {
             id: searchpage
             visible: false
         }
         Panel {
             id: panelpage
             visible: false
         }


         states: [
             State {
                 name: "Launcher"; when: settigsDetails.setTitle == "launcher"
                 PropertyChanges { target: launchpage; x: 0; visible: true }
                 PropertyChanges { target: searchpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: panelpage; visible:false/*x: -(parent.width * 1.5)*/ }
//                 PropertyChanges { target: launchercolumn; x: 0; visible: true }
//                 PropertyChanges { target: searchcolumn; visible:false/*; x: -(parent.width * 1.5)*/ }
//                 PropertyChanges { target: launchpage; visible:false/*x: -(parent.width * 1.5)*/ }
             },
             State {
                 name: "Search"; when: settigsDetails.setTitle == "search"
                 PropertyChanges { target: searchpage; x: 0; visible: true }
                 PropertyChanges { target: launchpage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: panelpage; visible:false/*x: -(parent.width * 1.5)*/ }
//                 PropertyChanges { target: searchcolumn; x: 0; visible: true }
//                 PropertyChanges { target: launchercolumn; visible:false/*x: -(parent.width * 1.5)*/ }
//                 PropertyChanges { target: launchpage; visible:false/*x: -(parent.width * 1.5)*/ }
             },
             State {
                 name: "Panel"; when: settigsDetails.setTitle == "panel"
                 PropertyChanges { target: panelpage; x: 0; visible: true }
                 PropertyChanges { target: launchpage;visible:false/* x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: searchpage; visible:false/*x: -(parent.width * 1.5)*/ }
//                 PropertyChanges { target: launchpage; x: 0; visible: true }
//                 PropertyChanges { target: launchercolumn;visible:false/* x: -(parent.width * 1.5)*/ }
//                 PropertyChanges { target: searchcolumn; visible:false/*x: -(parent.width * 1.5)*/ }
             }
         ]

         transitions: Transition {
             NumberAnimation { properties: "x"; duration: 500; easing.type: Easing.InOutQuad }
         }
     }
 }
