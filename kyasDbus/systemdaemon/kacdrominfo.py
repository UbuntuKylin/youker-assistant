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

class KACDRomInfo():

    def __init__(self):
        pass

    def getCDRomInfo(self):
        summary = {"list":[]}

        args = ["hwinfo", "--cdrom"]
        pipe = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        output = pipe.stdout.readlines()

        oddindex = -1
        pattern = re.compile(r'^\d+: ')
        cdRomName,cdRomManufacturer,cdRomModel,cdRomVersion,cdRomBusInfo,cdRomDriver, \
            cdRomSpeed,cdRomSerialNum,cdRomDeviceNum = "","","","","","","","",""
        cdRomOne = {}

        for line in [ bytes.decode(l.strip(),"utf-8","ignore") for l in output]:
            if pattern.match(line):
                oddindex += 1
                if len(cdRomOne) > 0 :
                    summary["list"].append(cdRomOne)
                cdRomName,cdRomManufacturer,cdRomModel,cdRomVersion,cdRomBusInfo,cdRomDriver, \
                    cdRomSpeed,cdRomSerialNum,cdRomDeviceNum = "","","","","","","","",""
                cdRomOne = {}
            else:
                if oddindex == -1:
                    continue
                if ":" not in line:
                    continue
                
                results = [ v.strip() for v in line.split(":", 1)]
                
                #名称
                if line.startswith("Device:"):
                    cdDevice = results[1].split("\"")
                    if len(cdDevice) > 1 :
                        cdRomName = cdDevice[1]
                    else :
                        cdRomName = results[1]
                #制造商
                if line.startswith("Vendor:"):
                    cdVendor = results[1].split("\"")
                    if len(cdVendor) > 1 :
                        cdRomManufacturer = cdVendor[1]
                    else :
                        cdRomManufacturer = results[1]
                if line.startswith("SubVendor:"):
                    cdVendor = results[1].split("\"")
                    if len(cdVendor) > 1 :
                        cdRomManufacturer = cdVendor[1]
                    else :
                        cdRomManufacturer = results[1]
                #版本
                if line.startswith("Revision:"):
                    cdRomVersion = results[1].strip("\"")

                #型号
                if line.startswith("Model:"):
                    cdRomModel = results[1].strip("\"")
                #总线信息
                if line.startswith("SysFS BusID:"):
                    cdRomBusInfo = results[1]
                #驱动
                if line.startswith("Driver:"):
                    cdDriver = results[1].split("\"")
                    if len(cdDriver) > 1 :
                        cdRomDriver = cdDriver[1]
                    else :
                        cdRomDriver = results[1].strip("\"")
                #速度
                if line.startswith("Speed:"):
                    cdRomSpeed = results[1]
                #序列号
                if line.startswith("Serial ID:"):
                    cdRomSerialNum = results[1].strip("\"")
                #设备编号
                if line.startswith("Device Number:"):
                    cdRomDeviceNum = results[1]

                if len(cdRomName) > 0 :
                    cdRomOne[CDI_NAME] = cdRomName
                if len(cdRomManufacturer) > 0 :
                    cdRomOne[CDI_MANUFACTURER] = cdRomManufacturer
                if len(cdRomModel) > 0 :
                    cdRomOne[CDI_MODEL] = cdRomModel
                if len(cdRomVersion) > 0 :
                    cdRomOne[CDI_VERSION] = cdRomVersion
                if len(cdRomBusInfo) > 0 :
                    cdRomOne[CDI_BUSINFO] = cdRomBusInfo
                if len(cdRomDriver) > 0 :
                    cdRomOne[CDI_DRIVER] = cdRomDriver
                if len(cdRomSpeed) > 0 :
                    cdRomOne[CDI_SPEED] = cdRomSpeed
                if len(cdRomSerialNum) > 0 :
                    cdRomOne[CDI_SERAILNUM] = cdRomSerialNum
                if len(cdRomDeviceNum) > 0 :
                    cdRomOne[CDI_DEVICENUM] = cdRomDeviceNum
        if len(cdRomOne) > 0 :
            summary["list"].append(cdRomOne)
        return json.dumps(summary)

if __name__ == "__main__":
    cc = KACDRomInfo()
    pprint(cc.getCDRomInfo())

