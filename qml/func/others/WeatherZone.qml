/*
 * Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd.
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
import "../common" as Common

Rectangle {
    id: weahterzone
    width: 208;height: 147
    SystemPalette { id: myPalette; colorGroup: SystemPalette.Active }
    color: "transparent"

    //当启动时没有网络的时候，设置默认界面
    function setDefaultWeather() {
        weatherIcon.source = "../../img/weather/d0.gif"
        weatherText.text = qsTr("Weather");//天气
        pmText.text = qsTr("AQI");//空气质量指数
        tempText.text = qsTr("Current temperature");//当前温度（℃）
    }

    //设置天气数据到QML界面上
    function resetCurrentWeather() {
        var ptime = sessiondispatcher.getSingleWeatherInfo("ptime", "current");//eg: 08:00
        var need_str = ptime.substr(0, ptime.lastIndexOf(":"));//eg: 08
        //将字符串类型的时间转成整形
        var pIntTime = parseInt(need_str, 10);//eg: 8
        if(pIntTime > 7 && pIntTime < 20) {
            var img1 = sessiondispatcher.getSingleWeatherInfo("img1", "current");
            weatherIcon.source = sessiondispatcher.getSingleWeatherInfo(img1, "weathericon");
        }
        else {
            var img2 = sessiondispatcher.getSingleWeatherInfo("img2", "current");
            weatherIcon.source = sessiondispatcher.getSingleWeatherInfo(img2, "weathericon");
        }
        locationText.text = sessiondispatcher.getSingleWeatherInfo("city", "current");
        ptimeText.text = sessiondispatcher.getSingleWeatherInfo("time", "current") + qsTr(" ");// 发布
        weatherText.text = sessiondispatcher.getSingleWeatherInfo("weather", "current");
        pmText.text = qsTr("AQI:") + sessiondispatcher.getSingleWeatherInfo("aqi", "current");;//空气质量指数：
        tempText.text = qsTr("Current temperature:") + sessiondispatcher.getSingleWeatherInfo("temp", "current") + "℃";//当前温度：
    }

    //设置yahoo天气到界面上
    function resetCurrentYahooWeather() {
        weatherIcon.source = "http://l.yimg.com/a/i/us/we/52/" + sessiondispatcher.getSingleWeatherInfo("code", "yahoo") + ".gif";
        locationText.text = sessiondispatcher.getSingleWeatherInfo("city", "yahoo");//城市
        ptimeText.text = "";
        pmText.text = sessiondispatcher.getSingleWeatherInfo("time", "yahoo");//发布时间
        weatherText.text = sessiondispatcher.getSingleWeatherInfo("text", "yahoo");//当前天气
        tempText.text = qsTr("Current temperature:") + sessiondispatcher.getSingleWeatherInfo("temp", "yahoo");//当前温度：
    }

    Connections
    {
        target: sessiondispatcher
        onStartUpdateForecastWeahter: {
            if(flag == "weather") {
                weahterzone.resetCurrentWeather();
            }
            else if(flag == "yahoo") {
                weahterzone.resetCurrentYahooWeather();
            }
        }

        //用户修改了城市时更新
        onStartChangeQMLCity: {
            sessiondispatcher.get_current_weather_qt();
        }
    }

    Component.onCompleted: {
        weahterzone.setDefaultWeather();
        sessiondispatcher.get_current_weather_qt();//0104
    }
    Text {
        id: locationText
        text: qsTr("City")//城市
        font.bold: true
        font.pixelSize: 14
        color: "#383838"
        anchors.left: parent.left
    }
    Common.StyleButton {
        id: changeCityBtn
        anchors.left: locationText.right
        wordname: qsTr("[Change]")//[切换]
        width: 60
        height: locationText.height
        onClicked: {
            sessiondispatcher.showWizardController();
        }
    }

    Text {
        id: ptimeText
        text: qsTr("Publish")//发布时间
        font.bold: true
        font.pixelSize: 14
        color: "#383838"
        anchors.right: parent.right
    }
    Image {
        id: weatherIcon
        anchors {
            top: ptimeText.bottom
            topMargin: 5
            right: parent.right
        }
        width: 48; height: 48
        source: ""
     }
    Row {
        anchors.top: parent.top
        anchors.topMargin: 25
        spacing: 15

        Column {
            spacing: 5
            Text {
                id: weatherText
                text: qsTr("N/A")//未知
                font.pixelSize: 12
                color: "#7a7a7a"
            }
            Text {
                id: pmText
                text: qsTr("AQI:N/A")//空气质量指数：未知
                font.pixelSize: 12
                color: "#7a7a7a"
            }
            Text {
                id: tempText
                text: qsTr("Temperature:N/A")//温度：未知
                font.pixelSize: 12
                color: "#7a7a7a"
            }
        }
    }
//    Timer{
//        id: updateTime
//        interval: 600000;running: true;repeat: true
//        onTriggered: {
//            sessiondispatcher.get_current_weather_qt();
////            console.log(Qt.formatDateTime(new Date(), "dddd\nyyyy-MM-dd\n-MMM-\nhh-mm-ss"));
//        }
//    }
}
