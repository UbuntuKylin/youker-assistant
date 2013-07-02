/** **************************************************************************
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
    id: btn
    signal clicked
    property string text
    BorderImage {
        id: buttonImage
        source: "../../img/icons/tab.png"
        width: btn.width; height: btn.height
    }
    BorderImage {
        id: pressed
        opacity: 0
        source: "../../img/icons/unselect.png"
        width: btn.width; height: btn.height
    }
    MouseArea {
        id: mouseRegion
        anchors.fill: buttonImage
        onClicked: { btn.clicked(); }
    }
    Text {
        color: "white"
        anchors.centerIn: buttonImage; font.bold: true; font.pixelSize: 15
        text: btn.text; style: Text.Raised; styleColor: "black"
    }
    states: [
        State {
            name: "Pressed"
            when: mouseRegion.pressed == true
            PropertyChanges { target: pressed; opacity: 1 }
        }
    ]
}






//Button {
//    id: buttonBack
//    anchors {
//        left: parent.left
//        leftMargin: UiConstants.NavBarLongMargin
//    }
//    pressedImage: "qrc:///mobile/navbar/btn_nav_back_pressed"
//    unpressedImage: "qrc:///mobile/navbar/btn_nav_back_unpressed"
//    visible: { currentWebView ? currentWebView.canGoBack : false }
//    onClicked: {
//        currentWebView.goBack()
//        backRequested()
//    }
//}

//Button {
//    id: buttonNext
//    anchors {
//        left: { buttonBack.visible ? buttonBack.right : parent.left }
//        leftMargin: buttonBack.visible ? UiConstants.NavBarShortMargin : UiConstants.NavBarLongMargin
//    }
//    pressedImage: "qrc:///mobile/navbar/btn_nav_forward_pressed"
//    unpressedImage: "qrc:///mobile/navbar/btn_nav_forward_unpressed"
//    visible: { currentWebView ? currentWebView.canGoForward : false }
//    onClicked: {
//        currentWebView.goForward()
//        forwardRequested()
//    }
//}
//Button {
//    id: reloadStopButton
//    property bool loading: { currentWebView ? currentWebView.loading : false }
//    anchors.right: parent.right
//    pressedImage: { loading ? "qrc:///mobile/navbar/btn_nav_stop_pressed" : "qrc:///mobile/navbar/btn_nav_reload_pressed" }
//    unpressedImage: { loading ? "qrc:///mobile/navbar/btn_nav_stop_unpressed" : "qrc:///mobile/navbar/btn_nav_reload_unpressed" }
//    onClicked: {
//        if (loading) {
//            currentWebView.stop();
//            stopRequested();
//        } else {
//            currentWebView.reload();
//            reloadRequested();
//        }
//    }
//}

//import QtQuick 2.0

//Item {
//    id: rootButton

//    property bool disabled

//    property string disabledImage: "../images/urlbar/component_btn_nav_back_over.png"
//    property string hoveredImage: "../images/urlbar/component_btn_nav_back_pressed.png"
//    property string pressedImage: "../images/urlbar/component_btn_nav_cancel_over.png"
//    property string standardImage: "../images/urlbar/component_btn_nav_cancel_pressed.png"

//    signal clicked()

//    height: buttonImage.height
//    width: buttonImage.width

//    Image {
//        id: buttonImage
//        source: {
//            if (rootButton.disabled)
//                return disabledImage
//            if (buttonMouseArea.isPressed)
//                return pressedImage
//            if (buttonMouseArea.isHovered)
//                return hoveredImage
//            else
//                return standardImage
//        }
//        MouseArea {
//            id: buttonMouseArea
//            anchors.fill: parent
//            onClicked: rootButton.clicked();
//            hoverEnabled: true
//            property bool isHovered: false
//            property bool isPressed: false
//            onEntered: { isHovered = true }
//            onExited: { isHovered = false }
//            onPressed: { isPressed = true }
//            onReleased: { isPressed = false }
//        }
//    }
//}


//import QtQuick 2.0

//Item {
//    property string pressedImage
//    property string unpressedImage

//    signal clicked()

//    anchors.verticalCenter: parent.verticalCenter
//    height: image.height
//    width: image.width

//    Image {
//        id: image
//        anchors.centerIn: parent
//        source: mouseArea.pressed ? pressedImage : unpressedImage
//    }

//    MouseArea {
//        id: mouseArea
//        anchors.fill: image
//        onClicked: parent.clicked();
//    }
//}
