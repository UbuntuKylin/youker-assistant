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
import "settings" as Settings
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

         Settings.Theme {
             id: themepage
             visible: false
         }
         Settings.Sound {
             id: soundpage
             visible: false
         }
         Settings.Fonts {
             id: fontspage
             visible: false
         }
         Settings.Touchpad {
             id: touchpadpage
             visible: false
         }
//         Settings.Login {
//             id: loginpage
//             visible: false
//         }
         Settings.Unity {
             id: unitypage
             visible: false
         }
         Settings.Desktopicon {
             id: desktopiconpage
             visible: false
         }
//         Settings.Wallpaper {
//             id: wallpaperpage
//             visible: false
//         }
         Settings.Window {
             id: windowpage
             visible: false
         }
         Settings.Scrollbar {
             id: scrollbarpage
             visible: false
         }

         states: [
             State {
                 name: "Themes"; when: settigsDetails.setTitle == "theme"
                 PropertyChanges { target: themepage; x: 0; visible: true }
                 PropertyChanges { target: soundpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: fontspage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: touchpadpage; visible:false/*; x: -(parent.width * 1.5)*/ }
//                 PropertyChanges { target: loginpage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: unitypage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: desktopiconpage; visible:false/*x: -(parent.width * 1.5)*/ }
//                 PropertyChanges { target: wallpaperpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: windowpage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: scrollbarpage; visible:false/*; x: -(parent.width * 1.5)*/ }
             },
             State {
                 name: "Voice"; when: settigsDetails.setTitle == "sound"
                 PropertyChanges { target: soundpage; x: 0; visible: true }
                 PropertyChanges { target: themepage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: fontspage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: touchpadpage; visible:false/*; x: -(parent.width * 1.5)*/ }
//                 PropertyChanges { target: loginpage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: unitypage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: desktopiconpage; visible:false/*x: -(parent.width * 1.5)*/ }
//                 PropertyChanges { target: wallpaperpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: windowpage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: scrollbarpage; visible:false/*; x: -(parent.width * 1.5)*/ }
             },
             State {
                 name: "Fonts"; when: settigsDetails.setTitle == "fonts"
                 PropertyChanges { target: fontspage; x: 0; visible: true }
                 PropertyChanges { target: soundpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: themepage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: touchpadpage; visible:false/*; x: -(parent.width * 1.5)*/ }
//                 PropertyChanges { target: loginpage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: unitypage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: desktopiconpage; visible:false/*x: -(parent.width * 1.5)*/ }
//                 PropertyChanges { target: wallpaperpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: windowpage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: scrollbarpage; visible:false/*; x: -(parent.width * 1.5)*/ }
             },
             State {
                 name: "Talk"; when: settigsDetails.setTitle == "touchpad"
                 PropertyChanges { target: touchpadpage; x: 0; visible: true }
                 PropertyChanges { target: soundpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: fontspage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: themepage; visible:false/*; x: -(parent.width * 1.5)*/ }
//                 PropertyChanges { target: loginpage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: unitypage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: desktopiconpage; visible:false/*x: -(parent.width * 1.5)*/ }
//                 PropertyChanges { target: wallpaperpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: windowpage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: scrollbarpage; visible:false/*; x: -(parent.width * 1.5)*/ }
             },
//             State {
//                 name: "Login"; when: settigsDetails.setTitle == "login"
//                 PropertyChanges { target: loginpage; x: 0; visible: true }
//                 PropertyChanges { target: soundpage; visible:false/*; x: -(parent.width * 1.5)*/ }
//                 PropertyChanges { target: fontspage; visible:false/*x: -(parent.width * 1.5)*/ }
//                 PropertyChanges { target: touchpadpage; visible:false/*; x: -(parent.width * 1.5)*/ }
//                 PropertyChanges { target: themepage; visible:false/*x: -(parent.width * 1.5)*/ }
//                 PropertyChanges { target: unitypage; visible:false/*; x: -(parent.width * 1.5)*/ }
//                 PropertyChanges { target: desktopiconpage; visible:false/*x: -(parent.width * 1.5)*/ }
//                 PropertyChanges { target: wallpaperpage; visible:false/*; x: -(parent.width * 1.5)*/ }
//                 PropertyChanges { target: windowpage; visible:false/*x: -(parent.width * 1.5)*/ }
//                 PropertyChanges { target: scrollbarpage; visible:false/*; x: -(parent.width * 1.5)*/ }
//             },
             State {
                 name: "Unity"; when: settigsDetails.setTitle == "unity"
                 PropertyChanges { target: unitypage; x: 0; visible: true }
                 PropertyChanges { target: soundpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: fontspage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: touchpadpage; visible:false/*; x: -(parent.width * 1.5)*/ }
//                 PropertyChanges { target: loginpage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: themepage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: desktopiconpage; visible:false/*x: -(parent.width * 1.5)*/ }
//                 PropertyChanges { target: wallpaperpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: windowpage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: scrollbarpage; visible:false/*; x: -(parent.width * 1.5)*/ }
             },
             State {
                 name: "Desktopicon"; when: settigsDetails.setTitle == "desktopicon"
                 PropertyChanges { target: desktopiconpage; x: 0; visible: true }
                 PropertyChanges { target: soundpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: fontspage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: touchpadpage; visible:false/*; x: -(parent.width * 1.5)*/ }
//                 PropertyChanges { target: loginpage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: unitypage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: themepage; visible:false/*x: -(parent.width * 1.5)*/ }
//                 PropertyChanges { target: wallpaperpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: windowpage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: scrollbarpage; visible:false/*; x: -(parent.width * 1.5)*/ }
             },
//             State {
//                 name: "Wallpaperpage"; when: settigsDetails.setTitle == "wallpaper"
//                 PropertyChanges { target: wallpaperpage; x: 0; visible: true }
//                 PropertyChanges { target: soundpage; visible:false/*; x: -(parent.width * 1.5)*/ }
//                 PropertyChanges { target: fontspage; visible:false/*x: -(parent.width * 1.5)*/ }
//                 PropertyChanges { target: touchpadpage; visible:false/*; x: -(parent.width * 1.5)*/ }
//                 PropertyChanges { target: loginpage; visible:false/*x: -(parent.width * 1.5)*/ }
//                 PropertyChanges { target: unitypage; visible:false/*; x: -(parent.width * 1.5)*/ }
//                 PropertyChanges { target: desktopiconpage; visible:false/*x: -(parent.width * 1.5)*/ }
//                 PropertyChanges { target: themepage; visible:false/*; x: -(parent.width * 1.5)*/ }
//                 PropertyChanges { target: windowpage; visible:false/*x: -(parent.width * 1.5)*/ }
//                 PropertyChanges { target: scrollbarpage; visible:false/*; x: -(parent.width * 1.5)*/ }
//             },
             State {
                 name: "Widgetpage"; when: settigsDetails.setTitle == "window"
                 PropertyChanges { target: windowpage; x: 0; visible: true }
                 PropertyChanges { target: soundpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: fontspage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: touchpadpage; visible:false/*; x: -(parent.width * 1.5)*/ }
//                 PropertyChanges { target: loginpage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: unitypage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: themepage; visible:false/*x: -(parent.width * 1.5)*/ }
//                 PropertyChanges { target: wallpaperpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: desktopiconpage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: scrollbarpage; visible:false/*; x: -(parent.width * 1.5)*/ }
             },
             State {
                 name: "Filespage"; when: settigsDetails.setTitle == "scrollbar"
                 PropertyChanges { target: scrollbarpage; x: 0; visible: true }
                 PropertyChanges { target: soundpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: fontspage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: touchpadpage; visible:false/*; x: -(parent.width * 1.5)*/ }
//                 PropertyChanges { target: loginpage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: unitypage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: desktopiconpage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: themepage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: windowpage; visible:false/*x: -(parent.width * 1.5)*/ }
//                 PropertyChanges { target: wallpaperpage; visible:false/*; x: -(parent.width * 1.5)*/ }
             }
         ]

         transitions: Transition {
             NumberAnimation { properties: "x"; duration: 500; easing.type: Easing.InOutQuad }
         }
     }
 }
