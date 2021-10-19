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

class KAKeyboardInfo():

    def __init__(self, cmdtool):
        self.cmdTool = cmdtool
        pass

    def getkeyboardInfo(self):
        summary = {"list":[]}

        hwinfoList = self.cmdTool.loadInfoFromHwinfo("--keyboard")["list"]
        for mapInfo in hwinfoList :
            if len(mapInfo) == 0 :
                continue
            kbName,kbManufacturer,kbModel,kbInterface,kbDriver,kbType = "","","","","",""
            kbOne = {}
            ##名称
            if "Device" in mapInfo :
                kbDevice = mapInfo["Device"].split("\"")
                if len(kbDevice) > 1 :
                    kbName = kbDevice[1]
                else :
                    kbName = mapInfo["Device"]

            ##类型
            if "Hardware Class" in mapInfo :
                kbType = mapInfo["Hardware Class"]

            ##制造商
            if "Vendor" in mapInfo :
                kbVendor = mapInfo["Vendor"].split("\"")
                if len(kbVendor) > 1 :
                    kbManufacturer = kbVendor[1]
                else :
                    kbManufacturer = mapInfo["Vendor"]
            if "SubVendor" in mapInfo :
                kbVendor = mapInfo["SubVendor"].split("\"")
                if len(kbVendor) > 1 :
                    kbManufacturer = kbVendor[1]
                else :
                    kbManufacturer = mapInfo["SubVendor"]

            ##接口
            if "Hotplug" in mapInfo :
                kbInterface = mapInfo["Hotplug"]

            ##型号
            if "Model" in mapInfo :
                kbModel = mapInfo["Model"].strip("\"")
                if "bluetooth" in kbModel :
                    kbInterface = "BLUETOOTH"

            ##驱动
            if "Driver" in mapInfo :
                kbDriver = mapInfo["Driver"].strip("\"")

            if len(kbName) > 0 :
                kbOne[KBI_NAME] = kbName
            if len(kbType) > 0 :
                kbOne[KBI_DEVTYPE] = kbType
            if len(kbManufacturer) > 0 :
                kbOne[KBI_MANUFACTURER] = kbManufacturer
            if len(kbInterface) > 0 :
                kbOne[KBI_INTERFACE] = kbInterface
            if len(kbModel) > 0 :
                kbOne[KBI_DEVMODEL] = kbModel
            if len(kbDriver) > 0 :
                kbOne[KBI_DRIVER] = kbDriver

            if len(kbOne) > 0 :
                summary["list"].append(kbOne)
        
        return json.dumps(summary)

    #概要信息
    def getOutline(self) :
        outLine = self.getkeyboardInfo()
        outLineObj = json.loads(outLine)
        outLine = ""
        if len(outLineObj) > 0 and "list" in outLineObj :
            nIndex = 0
            for info in outLineObj["list"] :
                if KBI_NAME in info :
                    if nIndex == 0 :
                        outLine += info[KBI_NAME]
                    else :
                        outLine += " / " + info[KBI_NAME]
                if KBI_DEVMODEL in info :
                        outLine += "("+info[KBI_DEVMODEL]+")"
                nIndex = nIndex + 1
        return outLine

if __name__ == "__main__":
    cmdTool = KACmdTool()
    cc = KAKeyboardInfo(cmdTool)
    pprint(cc.getkeyboardInfo())
    #pprint(cc.getOutline())

