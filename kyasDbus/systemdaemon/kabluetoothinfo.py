#!/usr/bin/python3
# -*- coding: utf-8 -*-

### BEGIN LICENSE
 # Copyright (C) 2021 KylinSoft Co., Ltd.
 #
 # Authors:
 #  Yang Min yangmin@kylinos.cn
 #
 # This program is free software; you can redistribute it and/or modify
 # it under the terms of the GNU General Public License as published by
 # the Free Software Foundation, either version 3 of the License, or
 # (at your option) any later version.
 #
 # This program is distributed in the hope that it will be useful,
 # but WITHOUT ANY WARRANTY; without even the implied warranty of
 # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 # GNU General Public License for more details.
 #
 # You should have received a copy of the GNU General Public License
 # along with this program.  If not, see <http://www.gnu.org/licenses/>.
### END LICENSE


import sys
import os
import re

import json
import subprocess

from pprint import pprint

from kajsondef import *
from kathread import *

class KABluetoothInfo():

    def __init__(self, cmdtool):
        self.cmdTool = cmdtool
        pass

    def getBluetoothInfo(self):
        summary = {"list":[]}

        baseList = self.cmdTool.loadInfoFromHciconfig()
        hwinfoList = self.cmdTool.loadInfoFromHwinfo("--usb")["list"]
        length = len(baseList)
        for i in range(length) :
            if len(baseList[i]) == 0 :
                continue
            for mapInfo in hwinfoList :
                if len(mapInfo) == 0 :
                    continue
                if "Hardware Class" not in mapInfo :
                    continue
                if mapInfo["Hardware Class"] == "hub" or mapInfo["Hardware Class"] == "mouse" or mapInfo["Hardware Class"] == "keyboard" :
                    continue
                if mapInfo["Hardware Class"] == "bluetooth" or ("Driver" in mapInfo and mapInfo["Driver"] == "btusb") \
                    or ("Device" in mapInfo and mapInfo["Device"] == "BCM20702A0") :
                    if "Vendor" in mapInfo and len(mapInfo["Vendor"]) > 0 :
                        words = mapInfo["Vendor"].split(" ")
                        if len(words) < 1 :
                            continue
                        if "Manufacturer" in baseList[i] and len(baseList[i]["Manufacturer"]) > 0 :
                            if words[0] not in baseList[i]["Manufacturer"] :
                                continue
                            baseList[i].update(mapInfo)
        
        self.cmdTool.loadInfoFromLshw(False)
        lshwinfoList = self.cmdTool.lshwUsbList
        for i in range(length) :
            if len(baseList[i]) == 0 :
                continue
            if "SysFS BusID" not in baseList[i] :
                continue
            for mapInfo in lshwinfoList :
                if len(mapInfo) == 0 :
                    continue
                if "bus info" in mapInfo :
                    words = mapInfo["bus info"].split("@")
                    if len(words) != 2 :
                        continue
                    key = words[1].strip()
                    #key = key.replace(".","" in mapInfo 
                    if key != baseList[i]["SysFS BusID"] :
                        continue
                    baseList[i].update(mapInfo)
        
        index = 0
        for mapInfo in baseList :
            summary["list"].append({})
            ##名称
            if "product" in mapInfo :
                summary["list"][index][BLI_PRODUCT] = mapInfo["product"]

            ##制造商
            if "Manufacturer" in mapInfo :
                summary["list"][index][BLI_MANUFACTURER] = mapInfo["Manufacturer"]

            if "Vendor" in mapInfo :
                summary["list"][index][BLI_MANUFACTURER] = mapInfo["Vendor"]

            if "vendor" in mapInfo :
                summary["list"][index][BLI_MANUFACTURER] = mapInfo["vendor"]

            ##类型
            if "description" in mapInfo :
                summary["list"][index][BLI_DEVTYPE] = mapInfo["description"]

            ##版本
            if "Revision" in mapInfo :
                summary["list"][index][BLI_DEVVERSION] = mapInfo["Revision"]
            if "version" in mapInfo :
                summary["list"][index][BLI_DEVVERSION] = mapInfo["version"]

            ##总线信息
            if "bus info" in mapInfo :
                summary["list"][index][BLI_BUSADDR] = mapInfo["bus info"]

            ##驱动
            if "driver" in mapInfo :
                summary["list"][index][BLI_DRIVER] = mapInfo["driver"]

            ##型号
            if "Model" in mapInfo :
                summary["list"][index][BLI_DEVMODEL] = mapInfo["Model"].strip("\"")

            ##驱动
            if "Driver" in mapInfo :
                summary["list"][index][BLI_DRIVER] = mapInfo["Driver"].strip("\"")

            ##速度
            if "Speed" in mapInfo :
                summary["list"][index][BLI_SPEED] = mapInfo["Speed"]
            if "speed" in mapInfo :
                summary["list"][index][BLI_SPEED] = mapInfo["speed"]

            ##序列号
            if "Serial ID" in mapInfo :
                summary["list"][index][BLI_SERIALNUM] = mapInfo["Serial ID"].strip("\"")

            ##名称
            if "Name" in mapInfo :
                summary["list"][index][BLI_NAME] = mapInfo["Name"]

            ##名称
            if "BD Address" in mapInfo :
                summary["list"][index][BLI_ADDRESS] = mapInfo["BD Address"]

            ##功能
            if "capabilities" in mapInfo :
                summary["list"][index][BLI_CAPABILITIES] = mapInfo["capabilities"]

            ##总线
            if "Bus" in mapInfo :
                summary["list"][index][BLI_BUS] = mapInfo["Bus"]

            ##SCO MTU
            if "SCO MTU" in mapInfo :
                summary["list"][index][BLI_SCOMTU] = mapInfo["SCO MTU"]

            ##ALC MTU
            if "ACL MTU" in mapInfo :
                summary["list"][index][BLI_ALCMTU] = mapInfo["ACL MTU"]

            ##数据包类型
            if "Packet type" in mapInfo :
                summary["list"][index][BLI_PACKETTYPE] = mapInfo["Packet type"]

            ##特征
            if "Features" in mapInfo :
                summary["list"][index][BLI_FEATURES] = mapInfo["Features"]

            ##连接模式
            if "Link mode" in mapInfo :
                summary["list"][index][BLI_LINKMODE] = mapInfo["Link mode"]

            ##连接策略
            if "Link policy" in mapInfo :
                summary["list"][index][BLI_LINKPOLICY] = mapInfo["Link policy"]

            index += 1

        return json.dumps(summary)

    #概要信息
    def getOutline(self) :
        outLine = self.getBluetoothInfo()
        outLineObj = json.loads(outLine)
        outLine = ""
        if len(outLineObj) > 0 and "list" in outLineObj :
            nIndex = 0
            for info in outLineObj["list"] :
                if BLI_NAME in info and len(info[BLI_NAME]) > 0:
                    if nIndex == 0 :
                        outLine += info[BLI_NAME]
                    else :
                        outLine += " / " + info[BLI_NAME]
                elif BLI_DEVMODEL in info :
                    if nIndex == 0 :
                        outLine += info[BLI_DEVMODEL]
                    else :
                        outLine += " / " + info[BLI_DEVMODEL]
                nIndex = nIndex + 1
        return outLine

if __name__ == "__main__":
    cmdtool = KACmdTool()
    cmdtool.loadInfoFromLshw()
    cc = KABluetoothInfo(cmdtool)
    pprint(cc.getBluetoothInfo())

