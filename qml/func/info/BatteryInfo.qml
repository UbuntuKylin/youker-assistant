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
import "../common/InfoGroup.js" as InfoGroup

Rectangle {
    id: home
    width: parent.width; height: 476
//    color: "transparent"
//    color: "#e4f2fc"

//    Component.onCompleted: {
    function init_data() {
        if (sessiondispatcher.read_battery_info_qt()) {
            var data = sessiondispatcher.getBatterySingleInfo("POWER_SUPPLY_NAME");
            if (data === '') {
                devicetext.text = qsTr("Unknown");//未知
            }
            else {
                devicetext.text = "battery_" + data;
            }
            data = sessiondispatcher.getBatterySingleInfo("POWER_SUPPLY_MODEL_NAME");
            if (data === '') {
                modeltext.text = qsTr("Unknown");
            }
            else {
                modeltext.text = data;
            }
            data = sessiondispatcher.getBatterySingleInfo("POWER_SUPPLY_MANUFACTURER");

            if (data === '') {
                logo.source = "../../img/toolWidget/ubuntukylin.png";
                manufacturertext.text = qsTr("Unknown");
            }
            else {
                logo.source = InfoGroup.judgeName(data.toUpperCase()) ? ("../../img/logo/Manufacturer/" + data.toUpperCase() + ".jpg") : ("../../img/toolWidget/ubuntukylin.png");
                manufacturertext.text = data;
            }
            data = sessiondispatcher.getBatterySingleInfo("POWER_SUPPLY_SERIAL_NUMBER");
            if (data === '') {
                serialtext.text = qsTr("Unknown");
            }
            else {
                serialtext.text = data;
            }
            data = sessiondispatcher.getBatterySingleInfo("POWER_SUPPLY_TECHNOLOGY");
            if (data === '') {
                technologytext.text = qsTr("Unknown");
            }
            else {
                technologytext.text = data;
            }
            data = sessiondispatcher.getBatterySingleInfo("POWER_SUPPLY_VOLTAGE_NOW");
            if (data === '') {
                voltagetext.text = qsTr("Unknown");
            }
            else {
                voltagetext.text = data;
            }
            data = sessiondispatcher.getBatterySingleInfo("POWER_SUPPLY_ENERGY_FULL_DESIGN");
            if (data === '') {
                energy_design_text.text = qsTr("Unknown");
            }
            else {
                energy_design_text.text = data;
            }
            data = sessiondispatcher.getBatterySingleInfo("POWER_SUPPLY_ENERGY_FULL");
            if (data === '') {
                energy_full_text.text = qsTr("Unknown");
            }
            else {
                energy_full_text.text = data;
            }
            data = sessiondispatcher.getBatterySingleInfo("POWER_SUPPLY_ENERGY_NOW");
            if (data === '') {
                energy_now_text.text = qsTr("Unknown");
            }
            else {
                energy_now_text.text = data;
            }
        }
        else {
            devicetext.text = qsTr("Failed to get data");//获取失败
            modeltext.text = qsTr("Failed to get data");
            manufacturertext.text = qsTr("Failed to get data");
            serialtext.text = qsTr("Failed to get data");
            technologytext.text = qsTr("Failed to get data");
            voltagetext.text = qsTr("Failed to get data");
            energy_design_text.text = qsTr("Failed to get data");
            energy_full_text.text = qsTr("Failed to get data");
            energy_now_text.text = qsTr("Failed to get data");
        }
    }

    Connections
    {
        target: sessiondispatcher
        onTellDetailPageUpdateData: {
            if (infoFlag == "battery") {
                home.init_data();
            }
        }
    }


    Column {
        anchors {
            top: parent.top
            topMargin: 40
            left: parent.left
            leftMargin: 30
        }
        spacing: 20
        Row {
            Common.Label {
                id: desktoptitle
                text: qsTr("Battery Info")//电池信息
                font.bold: true
                font.pixelSize: 14
                color: "#383838"
            }
            Common.Separator {
                anchors.verticalCenter: parent.verticalCenter
                width: home.width - desktoptitle.width - 30 * 2
            }
        }
        Column {
            anchors.left: parent.left
            anchors.leftMargin: 20
            spacing: 10
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Device Name:")//设备名：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 150
                }
                Text {
                    id: devicetext
                    text: ""
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Model:")//型号：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 150
                }
                Text {
                    id: modeltext
                    text: ""//sessiondispatcher.getSingleInfo("distribution"
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Manufacturer:")//发行商：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 150
                }
                Text {
                    id: manufacturertext
                    text: ""//sessiondispatcher.getSingleInfo("language")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }

            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Serial Number:")//序列号：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 150
                }
                Text {
                    id: serialtext
                    text: ""//sessiondispatcher.getSingleInfo("currrent_user")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Technology:")//技术：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 150
                }
                Text {
                    id: technologytext
                    text: ""//sessiondispatcher.getSingleInfo("home_path")
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Voltage:")//电压：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 150
                }
                Text {
                    id: voltagetext
                    text: ""
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Energy Designed:")//能量（设计）：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 150
                }
                Text {
                    id: energy_design_text
                    text: ""
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Energy Full:")//满时能量：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 150
                }
                Text {
                    id: energy_full_text
                    text: ""
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
            Row {
                spacing: 10
                Common.Label {
                    text: qsTr("Energy Now:")//能量：
                    font.pixelSize: 14
                    color: "#7a7a7a"
                    width: 150
                }
                Text {
                    id: energy_now_text
                    text: ""
                    font.pixelSize: 14
                    color: "#7a7a7a"
                }
            }
        }
    }

    //desktop logo
    Image {
        id: logo
        source: ""
        opacity: 0.5
        anchors {
            top: parent.top
            topMargin: 80
            right: parent.right
            rightMargin: 30
        }
    }
}
