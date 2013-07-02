/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Components project.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 1.1
import "." 1.1

Window {
    id: root

    property bool showStatusBar: true
    property bool showToolBar: true
    property variant initialPage
    property alias pageStack: stack

    property bool platformSoftwareInputPanelEnabled: false

    Component.onCompleted: {
        contentArea.initialized = true
        if (initialPage && stack.depth == 0)
            stack.push(initialPage, null, true)
    }

    onInitialPageChanged: {
        if (initialPage && contentArea.initialized) {
            if (stack.depth == 0)
                stack.push(initialPage, null, true)
            else if (stack.depth == 1)
                stack.replace(initialPage, null, true)
        }
    }

    Item {
        id: contentArea

        property bool initialized: false

        anchors {
            top: sbar.bottom; bottom: sip.top;
            left: parent.left; right: parent.right;
        }

        PageStack {
            id: stack
            anchors.fill: parent
            toolBar: tbar
        }
    }

    StatusBar {
        id: sbar

        width: parent.width
        state: root.showStatusBar ? "Visible" : "Hidden"
        platformInverted: root.platformInverted

        states: [
            State {
                name: "Visible"
                PropertyChanges { target: sbar; y: 0; opacity: 1 }
            },
            State {
                name: "Hidden"
                PropertyChanges { target: sbar; y: -height; opacity: 0 }
            }
        ]

        transitions: [
            Transition {
                from: "Hidden"; to: "Visible"
                ParallelAnimation {
                    NumberAnimation { target: sbar; properties: "y"; duration: 200; easing.type: Easing.OutQuad }
                    NumberAnimation { target: sbar; properties: "opacity"; duration: 200; easing.type: Easing.Linear }
                }
            },
            Transition {
                from: "Visible"; to: "Hidden"
                ParallelAnimation {
                    NumberAnimation { target: sbar; properties: "y"; duration: 200; easing.type: Easing.Linear }
                    NumberAnimation { target: sbar; properties: "opacity"; duration: 200; easing.type: Easing.Linear }
                }
            }
        ]
    }

    Item {
        id: sip

        anchors { bottom: parent.bottom; left: parent.left; right: parent.right }

        Behavior on height { PropertyAnimation { duration: 200 } }

        states: [
            State {
                name: "Visible"; when: inputContext.visible && root.platformSoftwareInputPanelEnabled
                PropertyChanges { target: sip; height: inputContext.height }
            },

            State {
                name: "Hidden"; when: root.showToolBar
                PropertyChanges { target: sip; height: tbar.height }
            },

            State {
                name: "HiddenInFullScreen"; when: !root.showToolBar
                PropertyChanges { target: sip; height: 0 }
            }
        ]
    }

    ToolBar {
        id: tbar

        width: parent.width
        state: root.showToolBar ? "Visible" : "Hidden"
        platformInverted: root.platformInverted

        states: [
            State {
                name: "Visible"
                PropertyChanges { target: tbar; y: parent.height - height; opacity: 1 }
            },
            State {
                name: "Hidden"
                PropertyChanges { target: tbar; y: parent.height; opacity: 0 }
            }
        ]

        transitions: [
            Transition {
                from: "Hidden"; to: "Visible"
                ParallelAnimation {
                    NumberAnimation { target: tbar; properties: "y"; duration: 200; easing.type: Easing.OutQuad }
                    NumberAnimation { target: tbar; properties: "opacity"; duration: 200; easing.type: Easing.Linear }
                }
            },
            Transition {
                from: "Visible"; to: "Hidden"
                ParallelAnimation {
                    NumberAnimation { target: tbar; properties: "y"; duration: 200; easing.type: Easing.Linear }
                    NumberAnimation { target: tbar; properties: "opacity"; duration: 200; easing.type: Easing.Linear }
                }
            }
        ]
    }

    // event preventer when page transition is active
    MouseArea {
        anchors.fill: parent
        enabled: pageStack.busy
    }
}
