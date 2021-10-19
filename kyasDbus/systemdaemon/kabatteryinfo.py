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
from systemboardthread import *


class KABatteryInfo():

    def __init__(self):
        pass

    def getBatteryInfo(self, sysProductName = ""):
        summary = {"list":[]}

        args = ["upower", "--dump"]
        pipe = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        output = pipe.stdout.readlines()

        oddindex = -1
        pattern = re.compile(r'Device: ')
        batSerailNum,batState,batPercentage,batTimeToEmpty,batEnergyFull,batEnergy,batUsedTimes =  \
            "","","","","","",""
        batOne = {}

        for line in [ bytes.decode(l.strip(),"utf-8","ignore") for l in output]:
            if pattern.match(line):
                if "battery" in line.lower() :
                    oddindex = 1
                else :
                    oddindex = -1
                
                if len(batOne) > 0 :
                    if len(sysProductName) > 0 :
                        if "TN140A2" in sysProductName :   ##长城笔记本
                            batOne[BTI_MANUFACTURER] = "飞毛腿（福建）电子有限公司"
                            batOne[BTI_MODEL] = "SNGW001"
                            batOne[BTI_ENERGY] = ""
                            batOne[BTI_ENERGYFULL] = "60Wh"
                        elif "F860-T1" in sysProductName :   ##清华同方笔记本
                            batOne[BTI_MANUFACTURER] = "飞毛腿"
                            batOne[BTI_MODEL] = "SNBL001"
                            batOne[BTI_ENERGY] = ""
                            batOne[BTI_ENERGYFULL] = "63Wh"
                    summary["list"].append(batOne)
                batSerailNum,batState,batPercentage,batTimeToEmpty,batEnergyFull,batEnergy,batUsedTimes,batManufacturer,batModel =  \
                    "","","","","","","","",""
                batOne = {}
            else:
                if oddindex == -1:
                    continue
                if ":" not in line:
                    continue
                
                results = [ v.strip() for v in line.split(":", 1)]
                
                #厂商
                if line.startswith("vendor:"):
                    batManufacturer = results[1]
                #序列号
                if line.startswith("serial:") and len(results[1]) > 0 and "0" != results[1] and "None" != results[1]:
                    batSerailNum = results[1]
                #型号
                if line.startswith("model:"):
                    batModel = results[1]
                #状态
                if line.startswith("state:"):
                    batState = results[1]
                #电量
                if line.startswith("percentage:"):
                    batPercentage = results[1]
                #当前容量
                if line.startswith("energy:"):
                    batEnergy = results[1]
                #满电容量
                if line.startswith("energy-full:"):
                    batEnergyFull = results[1]
                #预计使用时间
                if line.startswith("time to empty:"):
                    batTimeToEmpty = results[1]

                if len(batManufacturer) > 0 :
                    batOne[BTI_MANUFACTURER] = batManufacturer
                if len(batSerailNum) > 0 :
                    batOne[BTI_SERAILNUM] = batSerailNum
                if len(batState) > 0 :
                    batOne[BTI_STATE] = batState
                if len(batPercentage) > 0 :
                    batOne[BTI_PERCENTAGE] = batPercentage
                if len(batEnergy) > 0 :
                    batOne[BTI_ENERGY] = batEnergy
                if len(batEnergyFull) > 0 :
                    batOne[BTI_ENERGYFULL] = batEnergyFull
                if len(batTimeToEmpty) > 0 :
                    batOne[BTI_TTE] = batTimeToEmpty
                if len(batUsedTimes) > 0 :
                    batOne[BTI_USEDTIMES] = batUsedTimes
                if len(batModel) > 0 :
                    batOne[BTI_MODEL] = batModel
        if len(batOne) > 0 :
            if len(sysProductName) > 0 :
                if "TN140A2" in sysProductName :   ##长城笔记本
                    batOne[BTI_MANUFACTURER] = "飞毛腿（福建）电子有限公司"
                    batOne[BTI_MODEL] = "SNGW001"
                    batOne[BTI_ENERGY] = ""
                    batOne[BTI_ENERGYFULL] = "60Wh"
                elif "F860-T1" in sysProductName :   ##清华同方笔记本
                    batOne[BTI_MANUFACTURER] = "飞毛腿"
                    batOne[BTI_MODEL] = "SNBL001"
                    batOne[BTI_ENERGY] = ""
                    batOne[BTI_ENERGYFULL] = "63Wh"
            summary["list"].append(batOne)
        if len(summary["list"]) == 0:
            return ""
        return json.dumps(summary)

if __name__ == "__main__":
    cc = KABatteryInfo()
    pprint(cc.getBatteryInfo())

