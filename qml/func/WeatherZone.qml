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
import SessionType 0.1
import "common" as Common

Rectangle {
    width: 208;height: 147
    SystemPalette { id: myPalette; colorGroup: SystemPalette.Active }
    color: "transparent"

    Component.onCompleted: {



        sessiondispatcher.get_current_weather_qt();
        locationText.text = sessiondispatcher.getSingleWeatherInfo("city", "current");
        ptimeText.text = sessiondispatcher.getSingleWeatherInfo("time", "current") + " 发布";
        weatherText.text = sessiondispatcher.getSingleWeatherInfo("weather", "current");
        windText.text = sessiondispatcher.getSingleWeatherInfo("WD", "current") + sessiondispatcher.getSingleWeatherInfo("WS", "current");
        pmText.text = "空气质量指数：" + sessiondispatcher.get_current_pm25_qt()
        tempText.text = "当前温度：" + sessiondispatcher.getSingleWeatherInfo("temp", "current") + "℃";
        temperatureRangeText.text = "温度范围：" + sessiondispatcher.getSingleWeatherInfo("temp2", "current") + "~" + sessiondispatcher.getSingleWeatherInfo("temp1", "current");;
        humidityText.text = "湿度：" + sessiondispatcher.getSingleWeatherInfo("SD", "current");

        sessiondispatcher.read_conf_data_qt();

    }
    Text {
        id: locationText
        text: "长沙"
        font.bold: true
        font.pixelSize: 14
        color: "#383838"
        anchors.left: parent.left
    }
    Text {
        id: ptimeText
        text: "08:00" + " 发布"
        font.bold: true
        font.pixelSize: 14
        color: "#383838"
        anchors.right: parent.right
    }
    Row {
        anchors.top: parent.top
        anchors.topMargin: 30
        spacing: 20
        Column {
            id: leftrow
            spacing: 5
            Image {
                id: weatherIcon
                width: 48; height: 48
                source: "../img/weather/d0.gif"
            }
            Common.Label {
                id: forecastBtn
                text: "预  报"
                font.pixelSize: 14
                color: "#318d11"
                anchors.horizontalCenter: parent.horizontalCenter
                MouseArea {
                    anchors.fill: forecastBtn
                    hoverEnabled: true
                    onClicked: {
                        sessiondispatcher.get_current_weather_qt();
                        pageStack.push(weatherpage);
                    }
                }
            }
            Common.Label {
                id: preferencesBtn
                text: "配  置"
                font.pixelSize: 14
                color: "#318d11"
                anchors.horizontalCenter: parent.horizontalCenter
                MouseArea {
                    anchors.fill: preferencesBtn
                    hoverEnabled: true
                    onClicked: {
                        sessiondispatcher.read_conf_data_qt();
//                        sessiondispatcher.showWizardController();
                    }
                }
            }
//            ERROR:dbus.service:Unable to append ({u'pm2_5': 0, u'area': u'\u957f\u6c99', u'quality': u'\u8f7b\u5ea6\u6c61\u67d3', u'station_code': None, u'time_point': u'2013-10-18T09:00:00Z', u'pm2_5_24h': 0, u'position_name': None, u'aqi': 122, u'primary_pollutant': None},) to message with signature a{sv}: <type 'exceptions.TypeError'>: Don't know which D-Bus type to use to encode type "NoneType"
            Common.Label {
                id: updateBtn
                text: "更  新"
                font.pixelSize: 14
                color: "#318d11"
                anchors.horizontalCenter: parent.horizontalCenter
                MouseArea {
                    anchors.fill: updateBtn
                    hoverEnabled: true
                    onClicked: {
                        if(sessiondispatcher.update_weather_data_qt()) {
                            locationText.text = sessiondispatcher.getSingleWeatherInfo("city", "current");
                            ptimeText.text = sessiondispatcher.getSingleWeatherInfo("time", "current") + " 发布";
                            weatherText.text = sessiondispatcher.getSingleWeatherInfo("weather", "current");
                            windText.text = sessiondispatcher.getSingleWeatherInfo("WD", "current") + sessiondispatcher.getSingleWeatherInfo("WS", "current");
                            pmText.text = "空气质量指数：" + sessiondispatcher.get_current_pm25_qt()
                            tempText.text = "当前温度：" + sessiondispatcher.getSingleWeatherInfo("temp", "current") + "℃";
                            temperatureRangeText.text = "温度范围：" + sessiondispatcher.getSingleWeatherInfo("temp2", "current") + "~" + sessiondispatcher.getSingleWeatherInfo("temp1", "current");;
                            humidityText.text = "湿度：" + sessiondispatcher.getSingleWeatherInfo("SD", "current");
                            toolkits.alertMSG("更新完毕！", mainwindow.pos.x, mainwindow.pos.y);
                        }
                    }
                }
            }
        }
        Column {
            spacing: 5
            Text {
                id: weatherText
                text: "晴"
                font.pixelSize: 12
                color: "#7a7a7a"
            }
            Text {
                id: pmText
                text: "空气质量指数：30 良好"
                font.pixelSize: 12
                color: "#7a7a7a"
            }
            Text {
                id: tempText
                text: "温度：14℃"
                font.pixelSize: 12
                color: "#7a7a7a"
            }
            Text {
                id: humidityText
                text: "湿度：40%"
                font.pixelSize: 12
                color: "#7a7a7a"
            }
            Text {
                id: temperatureRangeText
                text: "温度范围：14-18"
                font.pixelSize: 12
                color: "#7a7a7a"
            }
            Text {
                id: windText
                text: "北风4级"
                font.pixelSize: 12
                color: "#7a7a7a"
            }
        }
    }
//        Timer{
//            interval: 3000;running: true;repeat: true
//            onTriggered: {
//            }
//        }
}



//weather_icons={
//    'd0.gif':'weather-clear',
//    'd1.gif':'weather-few-clouds',
//    'd2.gif':'weather-few-clouds',
//    'd3.gif':'weather-showers',
//    'd4.gif':'weather-showers',
//    'd5.gif':'weather-showers',
//    'd6.gif':'weather-snow',
//    'd7.gif':'weather-showers',
//    'd8.gif':'weather-showers',
//    'd9.gif':'weather-showers',
//    'd10.gif':'weather-showers',
//    'd11.gif':'weather-showers',
//    'd12.gif':'weather-showers',
//    'd13.gif':'weather-snow',
//    'd14.gif':'weather-snow',
//    'd15.gif':'weather-snow',
//    'd16.gif':'weather-snow',
//    'd17.gif':'weather-snow',
//    'd18.gif':'weather-fog',
//    'd19.gif':'weather-snow',
//    'd20.gif':'weather-fog',
//    'd21.gif':'weather-showers',
//    'd22.gif':'weather-showers',
//    'd23.gif':'weather-showers',
//    'd24.gif':'weather-showers',
//    'd25.gif':'weather-showers',
//    'd26.gif':'weather-snow',
//    'd27.gif':'weather-snow',
//    'd28.gif':'weather-snow',
//    'd29.gif':'weather-fog',
//    'd30.gif':'weather-fog',
//    'd31.gif':'weather-fog',
//    'd53.gif':'weather-fog',
//    'n0.gif':'weather-clear-night',
//    'n1.gif':'weather-few-clouds-night',
//    'n2.gif':'weather-few-clouds-night',
//    'n3.gif':'weather-showers',
//    'n4.gif':'weather-showers',
//    'n5.gif':'weather-showers',
//    'n6.gif':'weather-snow',
//    'n7.gif':'weather-showers',
//    'n8.gif':'weather-showers',
//    'n9.gif':'weather-showers',
//    'n10.gif':'weather-showers',
//    'n11.gif':'weather-showers',
//    'n12.gif':'weather-showers',
//    'n13.gif':'weather-snow',
//    'n14.gif':'weather-snow',
//    'n15.gif':'weather-snow',
//    'n16.gif':'weather-snow',
//    'n17.gif':'weather-snow',
//    'n18.gif':'weather-fog',
//    'n19.gif':'weather-showers',
//    'n20.gif':'weather-fog',
//    'n21.gif':'weather-showers',
//    'n22.gif':'weather-showers',
//    'n23.gif':'weather-showers',
//    'n24.gif':'weather-showers',
//    'n25.gif':'weather-showers',
//    'n26.gif':'weather-snow',
//    'n27.gif':'weather-snow',
//    'n28.gif':'weather-snow',
//    'n29.gif':'weather-fog',
//    'n30.gif':'weather-fog',
//    'n31.gif':'weather-fog',
//    'n53.gif':'weather-fog'
//}
