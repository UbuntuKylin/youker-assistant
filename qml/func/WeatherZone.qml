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
    id: weahterzone
    width: 208;height: 147
    SystemPalette { id: myPalette; colorGroup: SystemPalette.Active }
    color: "transparent"

    //设置[更换城市]按钮是否显示
    function resetChangeCityBtn() {
        var len = sessiondispatcher.getLengthOfCityList();
        if(len <= 1) {
            changeCityBtn.visible = false;
        }
        else {
            changeCityBtn.visible = true;
        }
    }

    //设置天气数据到QML界面上
    function resetCurrentWeather() {
        var ptime = sessiondispatcher.getSingleWeatherInfo("ptime", "current");//eg: 08:00
        var need_str = ptime.substr(0, ptime.lastIndexOf(":"));//eg: 08
        //将字符串类型的时间转成整形
        var pIntTime = parseInt(need_str, 10);//eg: 8
//        console.log("111111111111");
//        console.log(pIntTime);
        if(pIntTime > 7 && pIntTime < 20) {
            var img1 = sessiondispatcher.getSingleWeatherInfo("img1", "current");
            weatherIcon.source = sessiondispatcher.getSingleWeatherInfo(img1, "weathericon")
//            console.log("1111111111");
//            console.log(sessiondispatcher.getSingleWeatherInfo(img1, "weathericon"));
        }
        else {
//            weatherIcon.source = sessiondispatcher.getSingleWeatherInfo("img2", "current");
            var img2 = sessiondispatcher.getSingleWeatherInfo("img2", "current");
            weatherIcon.source = sessiondispatcher.getSingleWeatherInfo(img2, "weathericon")
//            console.log("2222222");
//            console.log(sessiondispatcher.getSingleWeatherInfo(img2, "weathericon"));
        }


        locationText.text = sessiondispatcher.getSingleWeatherInfo("city", "current");
        ptimeText.text = sessiondispatcher.getSingleWeatherInfo("time", "current") + " 发布";
        weatherText.text = sessiondispatcher.getSingleWeatherInfo("weather", "current");
        windText.text = sessiondispatcher.getSingleWeatherInfo("WD", "current") + sessiondispatcher.getSingleWeatherInfo("WS", "current");
        var pmData = sessiondispatcher.get_current_pm25_qt();
        if (pmData == "N/A") {
            pmData = "未知";
        }
        pmText.text = "空气质量指数：" + pmData;
        tempText.text = "当前温度：" + sessiondispatcher.getSingleWeatherInfo("temp", "current") + "℃";
        temperatureRangeText.text = "温度范围：" + sessiondispatcher.getSingleWeatherInfo("temp2", "current") + "~" + sessiondispatcher.getSingleWeatherInfo("temp1", "current");;
        humidityText.text = "湿度：" + sessiondispatcher.getSingleWeatherInfo("SD", "current");
    }

    Connections
    {
        target: sessiondispatcher
        onStartChangeQMLCity: {
            sessiondispatcher.get_current_weather_qt();
            weahterzone.resetCurrentWeather();
            weahterzone.resetChangeCityBtn();
        }
        onStartUpdateRateTime: {
            updateTime.interval = 1000 * rate;
        }
    }

    Component.onCompleted: {
        var rate = sessiondispatcher.get_current_rate();
        updateTime.interval = 1000 * rate;
        sessiondispatcher.get_current_weather_qt();
        weahterzone.resetCurrentWeather();
        weahterzone.resetChangeCityBtn();
    }
    Text {
        id: locationText
        text: "长沙"
        font.bold: true
        font.pixelSize: 14
        color: "#383838"
        anchors.left: parent.left
    }
    SetWord {
        id: changeCityBtn
        visible: false
        anchors.left: locationText.right
        wordname: "[更换城市]"
        width: 80
        height: 20
        flag: "ChangeCity"
    }
    Text {
        id: ptimeText
        text: "发布时间"
        font.bold: true
        font.pixelSize: 14
        color: "#383838"
        anchors.right: parent.right
    }
    Row {
        anchors.top: parent.top
        anchors.topMargin: 25
        spacing: 20
        Column {
            id: leftrow
            spacing: 3
            Image {
                id: weatherIcon
                width: 48; height: 48
                source: ""
//                source: "../img/weather/d0.gif"
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
                        //1、获取六天天气预报数据
                        sessiondispatcher.get_forecast_weahter_qt();
                        //2、开始给天气预报界面发送更新数据信号
                        sessiondispatcher.update_forecast_weather();
                        //3、加载天气预报界面
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
                        sessiondispatcher.showWizardController();
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
                            weahterzone.resetCurrentWeather();
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
                text: "未知"
                font.pixelSize: 12
                color: "#7a7a7a"
            }
            Text {
                id: pmText
                text: "空气质量指数：未知"
                font.pixelSize: 12
                color: "#7a7a7a"
            }
            Text {
                id: tempText
                text: "温度：未知"
                font.pixelSize: 12
                color: "#7a7a7a"
            }
            Text {
                id: humidityText
                text: "湿度：未知"
                font.pixelSize: 12
                color: "#7a7a7a"
            }
            Text {
                id: temperatureRangeText
                text: "温度范围：未知"
                font.pixelSize: 12
                color: "#7a7a7a"
            }
            Text {
                id: windText
                text: "风力未知"
                font.pixelSize: 12
                color: "#7a7a7a"
            }
        }
    }
        Timer{
            id: updateTime
            interval: 60 * 1000;running: true;repeat: true
            onTriggered: {
                sessiondispatcher.get_current_weather_qt();
                weahterzone.resetCurrentWeather();
            }
        }
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
