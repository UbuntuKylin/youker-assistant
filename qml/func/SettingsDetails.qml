/*
 * Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * Authors:
 *  Kobe Lee    kobe24_lixiang@126.com
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
         Settings.WidgetTheme {
             id: widgetthemepage
             visible: false
         }
         Settings.DesktopiconSet {
             id: desktopiconsetpage
             visible: false
         }
         Settings.MousePointer {
             id: mousepointerpage
             visible: false
         }

         Settings.SoundEffects {
             id: soundeffectspage
             visible: false
         }
         Settings.BootAnimation {
             id: bootanimationpage
             visible: false
         }
         Settings.LauncherTheme {
             id: launcherthemepage
             visible: false
         }
         Settings.DefaultFont {
             id: defaultfontpage
             visible: false
         }
         Settings.DocumentFont {
             id: documentfontpage
             visible: false
         }
         Settings.TitlebarFont {
             id: titlebarfontpage
             visible: false
         }
         Settings.TouchpadSet {
             id: touchpadsetpage
             visible: false
         }

         states: [
             State {
                 name: "WidgetTheme"; when: settigsDetails.setTitle == "WidgetTheme"
                 PropertyChanges { target: widgetthemepage; x: 0; visible: true }
                 PropertyChanges { target: desktopiconsetpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: mousepointerpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: soundeffectspage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: bootanimationpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: launcherthemepage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: defaultfontpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: documentfontpage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: titlebarfontpage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: touchpadsetpage; visible:false/*; x: -(parent.width * 1.5)*/ }
             },
             State {
                 name: "DesktopiconSet"; when: settigsDetails.setTitle == "DesktopiconSet"
                 PropertyChanges { target: desktopiconsetpage; x: 0; visible: true }
                 PropertyChanges { target: widgetthemepage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: mousepointerpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: soundeffectspage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: bootanimationpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: launcherthemepage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: defaultfontpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: documentfontpage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: titlebarfontpage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: touchpadsetpage; visible:false/*; x: -(parent.width * 1.5)*/ }
             },
             State {
                 name: "MousePointer"; when: settigsDetails.setTitle == "MousePointer"
                 PropertyChanges { target: mousepointerpage; x: 0; visible: true }
                 PropertyChanges { target: desktopiconsetpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: widgetthemepage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: soundeffectspage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: bootanimationpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: launcherthemepage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: defaultfontpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: documentfontpage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: titlebarfontpage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: touchpadsetpage; visible:false/*; x: -(parent.width * 1.5)*/ }
             },
             State {
                 name: "SoundEffects"; when: settigsDetails.setTitle == "SoundEffects"
                 PropertyChanges { target: soundeffectspage; x: 0; visible: true }
                 PropertyChanges { target: desktopiconsetpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: mousepointerpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: widgetthemepage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: bootanimationpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: launcherthemepage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: defaultfontpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: documentfontpage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: titlebarfontpage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: touchpadsetpage; visible:false/*; x: -(parent.width * 1.5)*/ }
             },
             State {
                 name: "BootAnimation"; when: settigsDetails.setTitle == "BootAnimation"
                 PropertyChanges { target: bootanimationpage; x: 0; visible: true }
                 PropertyChanges { target: desktopiconsetpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: mousepointerpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: soundeffectspage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: widgetthemepage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: launcherthemepage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: defaultfontpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: documentfontpage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: titlebarfontpage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: touchpadsetpage; visible:false/*; x: -(parent.width * 1.5)*/ }
             },
             State {
                 name: "LauncherTheme"; when: settigsDetails.setTitle == "LauncherTheme"
                 PropertyChanges { target: launcherthemepage; x: 0; visible: true }
                 PropertyChanges { target: desktopiconsetpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: mousepointerpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: soundeffectspage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: bootanimationpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: widgetthemepage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: defaultfontpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: documentfontpage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: titlebarfontpage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: touchpadsetpage; visible:false/*; x: -(parent.width * 1.5)*/ }
             },
             State {
                 name: "DefaultFont"; when: settigsDetails.setTitle == "DefaultFont"
                 PropertyChanges { target: defaultfontpage; x: 0; visible: true }
                 PropertyChanges { target: desktopiconsetpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: mousepointerpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: soundeffectspage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: bootanimationpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: launcherthemepage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: widgetthemepage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: documentfontpage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: titlebarfontpage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: touchpadsetpage; visible:false/*; x: -(parent.width * 1.5)*/ }
             },
             State {
                 name: "DocumentFont"; when: settigsDetails.setTitle == "DocumentFont"
                 PropertyChanges { target: documentfontpage; x: 0; visible: true }
                 PropertyChanges { target: desktopiconsetpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: mousepointerpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: soundeffectspage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: bootanimationpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: launcherthemepage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: defaultfontpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: widgetthemepage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: titlebarfontpage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: touchpadsetpage; visible:false/*; x: -(parent.width * 1.5)*/ }
             },
             State {
                 name: "TitlebarFont"; when: settigsDetails.setTitle == "TitlebarFont"
                 PropertyChanges { target: titlebarfontpage; x: 0; visible: true }
                 PropertyChanges { target: desktopiconsetpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: mousepointerpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: soundeffectspage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: bootanimationpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: launcherthemepage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: defaultfontpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: documentfontpage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: widgetthemepage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: touchpadsetpage; visible:false/*; x: -(parent.width * 1.5)*/ }
             },
             State {
                 name: "TouchpadSet"; when: settigsDetails.setTitle == "TouchpadSet"
                 PropertyChanges { target: touchpadsetpage; x: 0; visible: true }
                 PropertyChanges { target: desktopiconsetpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: mousepointerpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: soundeffectspage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: bootanimationpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: launcherthemepage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: defaultfontpage; visible:false/*; x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: documentfontpage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: titlebarfontpage; visible:false/*x: -(parent.width * 1.5)*/ }
                 PropertyChanges { target: widgetthemepage; visible:false/*; x: -(parent.width * 1.5)*/ }
             }
         ]

         transitions: Transition {
             NumberAnimation { properties: "x"; duration: 500; easing.type: Easing.InOutQuad }
         }
     }
 }
