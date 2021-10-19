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

class KAMouseInfo():

    def __init__(self, cmdtool):
        self.cmdTool = cmdtool
        pass

    def getMouseInfo(self):
        summary = {"list":[]}

        hwinfoList = self.cmdTool.loadInfoFromHwinfo("--mouse")["list"]
        for mapInfo in hwinfoList :
            if len(mapInfo) == 0 :
                continue
            msOne = {}
            msName,msManufacturer,msModel,msInterface,msDriver,msType = "","","","","",""
            ##名称
            if "Device" in mapInfo :
                msDevice = mapInfo["Device"].split("\"")
                if len(msDevice) > 1 :
                    msName = msDevice[1]
                else :
                    msName = mapInfo["Device"]

            ##类型
            if "Hardware Class" in mapInfo :
                msType = mapInfo["Hardware Class"]

            ##制造商
            if "Vendor" in mapInfo :
                msVendor = mapInfo["Vendor"].split("\"")
                if len(msVendor) > 1 :
                    msManufacturer = msVendor[1]
                else :
                    msManufacturer = mapInfo["Vendor"]
            if "SubVendor" in mapInfo :
                msVendor = mapInfo["SubVendor"].split("\"")
                if len(msVendor) > 1 :
                    msManufacturer = msVendor[1]
                else :
                    msManufacturer = mapInfo["SubVendor"]

            ##接口
            if "Hotplug" in mapInfo :
                msInterface = mapInfo["Hotplug"]

            ##型号
            if "Model" in mapInfo :
                msModel = mapInfo["Model"].strip("\"")
                if "bluetooth" in msModel :
                    msInterface = "BLUETOOTH"

            ##驱动
            if "Driver" in mapInfo :
                msDriver = mapInfo["Driver"].strip("\"")

            if len(msName) > 0 :
                msOne[MSI_NAME] = msName
            if len(msType) > 0 :
                msOne[MSI_DEVTYPE] = msType
            if len(msManufacturer) > 0 :
                msOne[MSI_MANUFACTURER] = msManufacturer
            if len(msInterface) > 0 :
                msOne[MSI_INTERFACE] = msInterface
            if len(msModel) > 0 :
                msOne[MSI_DEVMODEL] = msModel
            if len(msDriver) > 0 :
                msOne[MSI_DRIVER] = msDriver
            if len(msOne) > 0 :
                summary["list"].append(msOne)
        
        return json.dumps(summary)

    #概要信息
    def getOutline(self) :
        outLine = self.getMouseInfo()
        outLineObj = json.loads(outLine)
        outLine = ""
        if len(outLineObj) > 0 and "list" in outLineObj :
            nIndex = 0
            for info in outLineObj["list"] :
                if MSI_NAME in info :
                    if nIndex == 0 :
                        outLine += info[MSI_NAME]
                    else :
                        outLine += " / " + info[MSI_NAME]
                if MSI_DEVMODEL in info :
                        outLine += "("+info[MSI_DEVMODEL]+")"
                nIndex = nIndex + 1
        return outLine

if __name__ == "__main__":
    cmdTool = KACmdTool()
    cc = KAMouseInfo(cmdTool)
    pprint(cc.getMouseInfo())
    #pprint(cc.getOutline())

