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
import SessionType 0.1
import SystemType 0.1
import "common" as Common

Rectangle {
    width: 208;height: 147
    SystemPalette { id: myPalette; colorGroup: SystemPalette.Active }
    color: "transparent"
    Component.onCompleted: {
//        sessiondispatcher
    }
    Row {
        Column {
            id: leftrow
            Image {
                id: weatherIcon
                width: 48; height: 48
                source: "../img/weather/d0.gif"
            }
            Common.Label {
                id: forecastBtn
                text: "预报"
                font.pixelSize: 12
                color: "#318d11"
                MouseArea {
                      anchors.fill: forecastBtn
                      hoverEnabled: true
                      onClicked: {

                      }
                }
            }
            Common.Label {
                id: preferencesBtn
                text: "配置"
                font.pixelSize: 12
                color: "#318d11"
                MouseArea {
                      anchors.fill: preferencesBtn
                      hoverEnabled: true
                      onClicked: {

                      }
                }
            }
            Common.Label {
                id: updateBtn
                text: "更新"
                font.pixelSize: 12
                color: "#318d11"
                MouseArea {
                      anchors.fill: updateBtn
                      hoverEnabled: true
                      onClicked: {
                      }
                }
            }
        }
        Column {
            Text {
                id: locationText
                text: "长沙"
            }
            Text {
                id: weatherText
                text: "小雨转阴"
            }
            Text {
                id: windText
                text: "北风4级"
            }
            Text {
                id: pmText
                text: "PM2.5：30 良好"
            }
            Text {
                id: tempText
                text: "温度：14-18"
            }
            Text {
                id: humidityText
                text: "湿度：40"
            }

        }
    }
//        Timer{
//            interval: 3000;running: true;repeat: true
//            onTriggered: {
//            }
//        }
}
