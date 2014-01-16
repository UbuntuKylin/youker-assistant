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
import "../common" as Common
import "../bars" as Bars

Item {
    id: weatherpage; width: parent.width; height: 475
    Rectangle {
        id: weather_widget
        anchors.fill: parent
        property string actiontext: qsTr("Getting six days weather forecast data from CMA, providing reference information for users to travel.")//获取中国气象局的六天天气预报数据，为用户出行提供参考。

        property string week1
        property string week2
        property string week3
        property string week4
        property string week5
        property string week6
        property string img1
        property string img2
        property string img3
        property string img4
        property string img5
        property string img6
        property string img7
        property string img8
        property string img9
        property string img10
        property string img11
        property string img12
        ListModel { id: weahterModel }

        //设置六天天气预报数据显示在QML界面上
        function initWeatherForcast() {
            //("星期日"),("星期一"),("星期二"),("星期三"),("星期四"),("星期五"),("星期六")
            var dayNames = new Array(qsTr("Sunday"),qsTr("Monday"),qsTr("Tuesday"),qsTr("Wednesday"),qsTr("Thursday"),qsTr("Friday"),qsTr("Saturday"));
            var Stamp = new Date();
            var dateTime = (Stamp.getMonth() + 1) +"月" +Stamp.getDate()+ "日";
            var num = Stamp.getDay();
            weather_widget.week1 = dateTime + " " + dayNames[num];
            var alterNum;
            for(var i = num+1; i<num+6; i++) {
                if(i == num+1) {
                    if(i >=7) {
                        alterNum = i - 7;
                        weather_widget.week2 = dayNames[alterNum];
                    }
                    else
                        weather_widget.week2 = dayNames[i];
                }
                else if(i == num+2) {
                    if(i >=7) {
                        alterNum = i - 7;
                        weather_widget.week3 = dayNames[alterNum];
                    }
                    else
                        weather_widget.week3 = dayNames[i];
                }
                else if(i == num+3) {
                    if(i >=7) {
                        alterNum = i - 7;
                        weather_widget.week4 = dayNames[alterNum];
                    }
                    else
                        weather_widget.week4 = dayNames[i];
                }
                else if(i == num+4) {
                    if(i >=7) {
                        alterNum = i - 7;
                        weather_widget.week5 = dayNames[alterNum];
                    }
                    else
                        weather_widget.week5 = dayNames[i];
                }
                else if(i == num+5) {
                    if(i >=7) {
                        alterNum = i - 7;
                        weather_widget.week6 = dayNames[alterNum];
                    }
                    else
                        weather_widget.week6 = dayNames[i];
                }
            }

            var updateTime = sessiondispatcher.getSingleWeatherInfo("fchh", "forecast");
            //未来六天天气预报，预报时间：          时
            locationLabel.text = sessiondispatcher.getSingleWeatherInfo("city", "forecast") + "  " + sessiondispatcher.getSingleWeatherInfo("date_y", "forecast") + updateTime + qsTr(" o'clock release");//时  发布
            //将字符串类型的时间转成整形
            var updateIntTime = parseInt(updateTime, 10);
            if(updateIntTime >= 6 && updateIntTime < 18) {
                //白天
                var result1 = sessiondispatcher.getSingleWeatherInfo("img1", "forecast");
                var result2 = sessiondispatcher.getSingleWeatherInfo("img2", "forecast");
                if (result1 == "99") {
                    weather_widget.img1 = "../../img/weather/d" + result2 + ".gif";
                }
                else {
                    weather_widget.img1 = "../../img/weather/d" + result1 + ".gif";
                }
                if (result2 == "99") {
                    weather_widget.img2 = "../../img/weather/n" + result1 + ".gif";
                }
                else {
                    weather_widget.img2 = "../../img/weather/n" + result2 + ".gif";
                }


                var result3 = sessiondispatcher.getSingleWeatherInfo("img3", "forecast");
                var result4 = sessiondispatcher.getSingleWeatherInfo("img4", "forecast");
                if (result3 == "99") {
                    weather_widget.img3 = "../../img/weather/d" + result4 + ".gif";
                }
                else {
                    weather_widget.img3 = "../../img/weather/d" + result3 + ".gif";
                }
                if (result4 == "99") {
                    weather_widget.img4 = "../../img/weather/n" + result3 + ".gif";
                }
                else {
                    weather_widget.img4 = "../../img/weather/n" + result4 + ".gif";
                }


                var result5 = sessiondispatcher.getSingleWeatherInfo("img5", "forecast");
                var result6 = sessiondispatcher.getSingleWeatherInfo("img6", "forecast");
                if (result5 == "99") {
                    weather_widget.img5 = "../../img/weather/d" + result6 + ".gif";
                }
                else {
                    weather_widget.img5 = "../../img/weather/d" + result5 + ".gif";
                }
                if (result6 == "99") {
                    weather_widget.img6 = "../../img/weather/n" + result5 + ".gif";
                }
                else {
                    weather_widget.img6 = "../../img/weather/n" + result6 + ".gif";
                }

                var result7 = sessiondispatcher.getSingleWeatherInfo("img7", "forecast");
                var result8 = sessiondispatcher.getSingleWeatherInfo("img8", "forecast");
                if (result7 == "99") {
                    weather_widget.img7 = "../../img/weather/d" + result8 + ".gif";
                }
                else {
                    weather_widget.img7 = "../../img/weather/d" + result7 + ".gif";
                }
                if (result8 == "99") {
                    weather_widget.img8 = "../../img/weather/n" + result7 + ".gif";
                }
                else {
                    weather_widget.img8 = "../../img/weather/n" + result8 + ".gif";
                }


                var result9 = sessiondispatcher.getSingleWeatherInfo("img9", "forecast");
                var result10 = sessiondispatcher.getSingleWeatherInfo("img10", "forecast");
                if (result9 == "99") {
                    weather_widget.img9 = "../../img/weather/d" + result10 + ".gif";
                }
                else {
                    weather_widget.img9 = "../../img/weather/d" + result9 + ".gif";
                }
                if (result10 == "99") {
                    weather_widget.img10 = "../../img/weather/n" + result9 + ".gif";
                }
                else {
                    weather_widget.img10 = "../../img/weather/n" + result10 + ".gif";
                }


                var result11 = sessiondispatcher.getSingleWeatherInfo("img11", "forecast");
                var result12 = sessiondispatcher.getSingleWeatherInfo("img12", "forecast");
                if (result11 == "99") {
                    weather_widget.img11 = "../../img/weather/d" + result12 + ".gif";
                }
                else {
                    weather_widget.img11 = "../../img/weather/d" + result11 + ".gif";
                }
                if (result12 == "99") {
                    weather_widget.img12 = "../../img/weather/n" + result11 + ".gif";
                }
                else {
                    weather_widget.img12 = "../../img/weather/n" + result12 + ".gif";
                }

            }
            else {
                //晚上
                var result1n = sessiondispatcher.getSingleWeatherInfo("img1", "forecast");
                var result2n = sessiondispatcher.getSingleWeatherInfo("img2", "forecast");

                if (result1n == "99") {
                    weather_widget.img1 = "../../img/weather/n" + result2n + ".gif";
                }
                else {
                    weather_widget.img1 = "../../img/weather/n" + result1n + ".gif";
                }
                if (result2n == "99") {
                    weather_widget.img2 = "../../img/weather/d" + result1n + ".gif";
                }
                else {
                    weather_widget.img2 = "../../img/weather/d" + result2n + ".gif";
                }


                var result3n = sessiondispatcher.getSingleWeatherInfo("img3", "forecast");
                var result4n = sessiondispatcher.getSingleWeatherInfo("img4", "forecast");
                if (result3n == "99") {
                    weather_widget.img3 = "../../img/weather/n" + result4n + ".gif";
                }
                else {
                    weather_widget.img3 = "../../img/weather/n" + result3n + ".gif";
                }
                if (result4n == "99") {
                    weather_widget.img4 = "../../img/weather/d" + result3n + ".gif";
                }
                else {
                    weather_widget.img4 = "../../img/weather/d" + result4n + ".gif";
                }


                var result5n = sessiondispatcher.getSingleWeatherInfo("img5", "forecast");
                var result6n = sessiondispatcher.getSingleWeatherInfo("img6", "forecast");
                if (result5n == "99") {
                    weather_widget.img5 = "../../img/weather/n" + result6n + ".gif";
                }
                else {
                    weather_widget.img5 = "../../img/weather/n" + result5n + ".gif";
                }
                if (result6n == "99") {
                    weather_widget.img6 = "../../img/weather/d" + result5n + ".gif";
                }
                else {
                    weather_widget.img6 = "../../img/weather/d" + result6n + ".gif";
                }

                var result7n = sessiondispatcher.getSingleWeatherInfo("img7", "forecast");
                var result8n = sessiondispatcher.getSingleWeatherInfo("img8", "forecast");
                if (result7n == "99") {
                    weather_widget.img7 = "../../img/weather/n" + result8n + ".gif";
                }
                else {
                    weather_widget.img7 = "../../img/weather/n" + result7n + ".gif";
                }
                if (result8n == "99") {
                    weather_widget.img8 = "../img/weather/d" + result7n + ".gif";
                }
                else {
                    weather_widget.img8 = "../../img/weather/d" + result8n + ".gif";
                }


                var result9n = sessiondispatcher.getSingleWeatherInfo("img9", "forecast");
                var result10n = sessiondispatcher.getSingleWeatherInfo("img10", "forecast");
                if (result9n == "99") {
                    weather_widget.img9 = "../../img/weather/n" + result10n + ".gif";
                }
                else {
                    weather_widget.img9 = "../../img/weather/n" + result9n + ".gif";
                }
                if (result10n == "99") {
                    weather_widget.img10 = "../../img/weather/d" + result9n + ".gif";
                }
                else {
                    weather_widget.img10 = "../../img/weather/d" + result10n + ".gif";
                }


                var result11n = sessiondispatcher.getSingleWeatherInfo("img11", "forecast");
                var result12n = sessiondispatcher.getSingleWeatherInfo("img12", "forecast");
                if (result11n == "99") {
                    weather_widget.img11 = "../../img/weather/n" + result12n + ".gif";
                }
                else {
                    weather_widget.img11 = "../../img/weather/n" + result11n + ".gif";
                }
                if (result12n == "99") {
                    weather_widget.img12 = "../../img/weather/d" + result11n + ".gif";
                }
                else {
                    weather_widget.img12 = "../../img/weather/d" + result12n + ".gif";
                }
            }
            weahterModel.clear();
            weahterModel.append({"date": weather_widget.week1, "dayIcon": weather_widget.img1, "nightIcon": weather_widget.img2, "temp": sessiondispatcher.getSingleWeatherInfo("temp1", "forecast"), "weather": sessiondispatcher.getSingleWeatherInfo("weather1", "forecast"),"wind": sessiondispatcher.getSingleWeatherInfo("wind1", "forecast")})
            weahterModel.append({"date": weather_widget.week2, "dayIcon": weather_widget.img3, "nightIcon": weather_widget.img4, "temp": sessiondispatcher.getSingleWeatherInfo("temp2", "forecast"), "weather": sessiondispatcher.getSingleWeatherInfo("weather2", "forecast"),"wind": sessiondispatcher.getSingleWeatherInfo("wind2", "forecast")})
            weahterModel.append({"date": weather_widget.week3, "dayIcon": weather_widget.img5, "nightIcon": weather_widget.img6, "temp": sessiondispatcher.getSingleWeatherInfo("temp3", "forecast"), "weather": sessiondispatcher.getSingleWeatherInfo("weather3", "forecast"),"wind": sessiondispatcher.getSingleWeatherInfo("wind3", "forecast")})
            weahterModel.append({"date": weather_widget.week4, "dayIcon": weather_widget.img7, "nightIcon": weather_widget.img8, "temp": sessiondispatcher.getSingleWeatherInfo("temp4", "forecast"), "weather": sessiondispatcher.getSingleWeatherInfo("weather4", "forecast"),"wind": sessiondispatcher.getSingleWeatherInfo("wind4", "forecast")})
            weahterModel.append({"date": weather_widget.week5, "dayIcon": weather_widget.img9, "nightIcon": weather_widget.img10, "temp": sessiondispatcher.getSingleWeatherInfo("temp5", "forecast"), "weather": sessiondispatcher.getSingleWeatherInfo("weather5", "forecast"),"wind": sessiondispatcher.getSingleWeatherInfo("wind5", "forecast")})
            weahterModel.append({"date": weather_widget.week6, "dayIcon": weather_widget.img11, "nightIcon": weather_widget.img12, "temp": sessiondispatcher.getSingleWeatherInfo("temp6", "forecast"), "weather": sessiondispatcher.getSingleWeatherInfo("weather6", "forecast"),"wind": sessiondispatcher.getSingleWeatherInfo("wind6", "forecast")})
        }



        //设置Yahoo五天天气预报数据显示在QML界面上
        function initYahooWeatherForcast() {
//            {'temp3': u'-6 \xb0C ~ 4 \xb0C', 'temp2': u'-7 \xb0C ~ 7 \xb0C', 'temp1': u'-6 \xb0C ~ 6 \xb0C', 'temp0': u'-6 \xb0C ~ 7 \xb0C', 'temp4': u'-7 \xb0C ~ 5 \xb0C',
//             'date1': u'17 Jan 2014', 'date0': u'16 Jan 2014', 'date3': u'19 Jan 2014', 'date2': u'18 Jan 2014', 'date4': u'20 Jan 2014',
//             'day4': u'Mon', 'day2': u'Sat', 'day3': u'Sun', 'day0': u'Thu', 'day1': u'Fri',
//             'text2': u'Sunny', 'text3': u'Mostly Cloudy', 'text0': u'Sunny', 'text1': u'Partly Cloudy', 'text4': u'Sunny',
//             'code0': u'32', 'code1': u'30', 'code2': u'32', 'code3': u'28', 'code4': u'32'}

            weather_widget.week1 = sessiondispatcher.getSingleWeatherInfo("day0", "yahooforecast") + ", " + sessiondispatcher.getSingleWeatherInfo("date0", "yahooforecast");
            weather_widget.week2 = sessiondispatcher.getSingleWeatherInfo("day1", "yahooforecast") + ", " + sessiondispatcher.getSingleWeatherInfo("date1", "yahooforecast");
            weather_widget.week3 = sessiondispatcher.getSingleWeatherInfo("day2", "yahooforecast") + ", " + sessiondispatcher.getSingleWeatherInfo("date2", "yahooforecast");
            weather_widget.week4 = sessiondispatcher.getSingleWeatherInfo("day3", "yahooforecast") + ", " + sessiondispatcher.getSingleWeatherInfo("date3", "yahooforecast");
            weather_widget.week5 = sessiondispatcher.getSingleWeatherInfo("day4", "yahooforecast") + ", " + sessiondispatcher.getSingleWeatherInfo("date4", "yahooforecast");
            weather_widget.week6 = "";
            //未来五天天气预报，预报时间：
            locationLabel.text = sessiondispatcher.getSingleWeatherInfo("city", "yahooforecast") + "  " + sessiondispatcher.getSingleWeatherInfo("time", "yahooforecast");
            weather_widget.img1 = "http://l.yimg.com/a/i/us/we/52/" + sessiondispatcher.getSingleWeatherInfo("code0", "yahooforecast") + ".gif";
            weather_widget.img2 = "";
            weather_widget.img3 = "http://l.yimg.com/a/i/us/we/52/" + sessiondispatcher.getSingleWeatherInfo("code1", "yahooforecast") + ".gif";
            weather_widget.img4 = "";
            weather_widget.img5 = "http://l.yimg.com/a/i/us/we/52/" + sessiondispatcher.getSingleWeatherInfo("code2", "yahooforecast") + ".gif";
            weather_widget.img6 = "";
            weather_widget.img7 = "http://l.yimg.com/a/i/us/we/52/" + sessiondispatcher.getSingleWeatherInfo("code3", "yahooforecast") + ".gif";
            weather_widget.img8 = "";
            weather_widget.img9 = "http://l.yimg.com/a/i/us/we/52/" + sessiondispatcher.getSingleWeatherInfo("code4", "yahooforecast") + ".gif";
            weather_widget.img10 = "";
            weather_widget.img11 = "";
            weather_widget.img12 = "";

            weahterModel.clear();
            weahterModel.append({"date": weather_widget.week1, "dayIcon": weather_widget.img1, "nightIcon": weather_widget.img2, "temp": sessiondispatcher.getSingleWeatherInfo("temp0", "yahooforecast"), "weather": sessiondispatcher.getSingleWeatherInfo("text0", "yahooforecast"),"wind": ""})
            weahterModel.append({"date": weather_widget.week2, "dayIcon": weather_widget.img3, "nightIcon": weather_widget.img4, "temp": sessiondispatcher.getSingleWeatherInfo("temp1", "yahooforecast"), "weather": sessiondispatcher.getSingleWeatherInfo("text1", "yahooforecast"),"wind": ""})
            weahterModel.append({"date": weather_widget.week3, "dayIcon": weather_widget.img5, "nightIcon": weather_widget.img6, "temp": sessiondispatcher.getSingleWeatherInfo("temp2", "yahooforecast"), "weather": sessiondispatcher.getSingleWeatherInfo("text2", "yahooforecast"),"wind": ""})
            weahterModel.append({"date": weather_widget.week4, "dayIcon": weather_widget.img7, "nightIcon": weather_widget.img8, "temp": sessiondispatcher.getSingleWeatherInfo("temp3", "yahooforecast"), "weather": sessiondispatcher.getSingleWeatherInfo("text3", "yahooforecast"),"wind": ""})
            weahterModel.append({"date": weather_widget.week5, "dayIcon": weather_widget.img9, "nightIcon": weather_widget.img10, "temp": sessiondispatcher.getSingleWeatherInfo("temp4", "yahooforecast"), "weather": sessiondispatcher.getSingleWeatherInfo("text4", "yahooforecast"),"wind": ""})
//            weahterModel.append({"date": weather_widget.week6, "dayIcon": weather_widget.img11, "nightIcon": weather_widget.img12, "temp": sessiondispatcher.getSingleWeatherInfo("temp5", "yahooforecast"), "weather": sessiondispatcher.getSingleWeatherInfo("text5", "yahooforecast"),"wind": "})
        }

        Connections
        {
            target: sessiondispatcher
            onStartUpdateForecastWeahter: {
                if(flag == "forecast") {
                    weather_widget.initWeatherForcast();
                }
                else if(flag == "yahooforecast") {
                    weather_widget.initYahooWeatherForcast();
                }
            }
        }

        Component.onCompleted: {
//            sessiondispatcher.get_forecast_weahter_qt();
//            weather_widget.initWeatherForcast();
        }
        //背景
        Image {
            source: "../../img/skin/bg-middle.png"
            anchors.fill: parent
        }
        //顶层工具栏
        Bars.TopBar {
            id: topBar
            width: 28
            height: 26
            anchors.top: parent.top
            anchors.topMargin: 40
            anchors.left: parent.left
            anchors.leftMargin: 40
            opacity: 0.9
            onButtonClicked: {
                var num = sessiondispatcher.get_page_num();
                if (num == 0) {
                    pageStack.push(homepage);
                }
                else if (num == 3) {
                    pageStack.push(systemset);
                }
                else if (num == 4) {
                    pageStack.push(functioncollection);
                }
            }
        }
        Column {
            spacing: 10
            anchors {
                top: parent.top
                topMargin: 44
                left: parent.left
                leftMargin: 80
            }
            Text {
                 id: locationLabel
                 text: ""
                 font.bold: true
                 font.pixelSize: 14
                 color: "#383838"
            }
            Text {
                text: weather_widget.actiontext
                font.pixelSize: 12
                color: "#7a7a7a"
            }
        }

        Component {
            id: weatherDelegate
            Item {
                Column {
                    spacing: 5
                    Text {
                        text: date
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Row {
                        spacing: 20
                        Image {
                            source: dayIcon
                        }
                        Image {
                            source: nightIcon
                        }
                    }
                    Text {
                        text: temp
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Text {
                        text: weather
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Text {
                        text: wind
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }
            }
        }
        Item {
            width: 700
            anchors {
                top: parent.top
                topMargin: 120
                left: parent.left
                leftMargin: 130
            }
            GridView {
                id: weatherGrid
                anchors.fill: parent
                cellWidth: 700/3; cellHeight: 180
                model: weahterModel
                delegate: weatherDelegate
                focus: true
                cacheBuffer: 1000
            }
        }
    }
}
