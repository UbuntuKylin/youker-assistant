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
//import SystemType 0.1
Rectangle {
    id: scaleMe
    width: 58
    height: 29
    SystemPalette { id: myPalette; colorGroup: SystemPalette.Active }
    color: "transparent"
    property string wordname: ""
    property string flag: ""

    Text {
        text: wordname
        font.pointSize: 10
        color: "#318d11"
    }

    Image {
        id: btnImg
        anchors.fill: parent
        source: ""
    }

    MouseArea {
        hoverEnabled: true
        anchors.fill: parent
        onClicked: {
            //屏幕坏点检测
            if (flag == "CheckScreen")
                sessiondispatcher.send_checkscreen_dialog();
            else if (flag == "WidgetTheme")
                pageStack.push(widgetthemepage);
            else if (flag == "DesktopiconSet")
                pageStack.push(desktopiconsetpage);
            else if (flag == "MousePointer")
                pageStack.push(mousepointerpage);
            else if (flag == "SoundEffects") {
                pageStack.push(soundeffectspage);
//                var component_sound = Qt.createComponent("./settings/SoundEffects.qml");
//                if (component_sound.status == Component.Ready) {
//                    pageStack.push(component_sound);
//                }
            }
            else if (flag == "BootAnimation") {
                pageStack.push(bootanimationpage);
//                var component_boot = Qt.createComponent("./settings/BootAnimation.qml");
//                if (component_boot.status == Component.Ready) {
//                    pageStack.push(component_boot);
//                }
            }
            else if (flag == "LauncherTheme")
                pageStack.push(launcherthemepage);
            else if (flag == "DefaultFont")
                pageStack.push(defaultfontpage);
            else if (flag == "DocumentFont")
                pageStack.push(documentfontpage);
            else if (flag == "TitlebarFont")
                pageStack.push(titlebarfontpage);
            else if (flag == "TouchpadSet")
                pageStack.push(touchpadsetpage);
        }
    }
}
