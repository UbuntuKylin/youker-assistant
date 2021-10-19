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

import json
import subprocess

from pprint import pprint

from kajsondef import *
from kathread import *

Mem_Manufacturer=    "Manufacturer"
Mem_BankLocator=     "Bank Locator"
Mem_Type=            "Type"
Mem_TypeDetail=      "Type Detail"
Mem_TotalWidth=      "Total Width"
Mem_DataWidth=       "Data Width"
Mem_SerialNumber=    "Serial Number"
Mem_MinVoltage=      "Minimum Voltage"
Mem_MaxVoltage=      "Maximum Voltage"
Mem_ConfVoltage=     "Configured Voltage"
Mem_Rank=            "Rank"
Mem_FormFactor=      "Form Factor"
Mem_Product=         "Product"


class MemoryInfo():

    def __init__(self, cmdtool):
        self.cmdTool = cmdtool
        pass

    def isEmpty(self, strValue) :
        if len(strValue) == 0 or "NONE" == strValue or "None" == strValue or "NULL" == strValue or "Null" == strValue :
            return True
        return False

    def getMemInfo(self):
        summary = {"list":[]}

        args = ["dmidecode", "-t", "memory"]
        pipe = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        output = pipe.stdout.readlines()

        index = 0
        marker1 = False
        marker2 = False
        memManufacturer,memSize,memType,memSpeed,memTotalBits,memSlot,memSerialNum, \
                        memDataBits,memConfigSpeed,memPipe,memModel,memArrayHandle, memPartNum = "","",\
                        "","","","","","","","","","",""
        oneMem = {}

        for line in [ bytes.decode(l.strip(),"utf-8","ignore") for l in output]:

            ###开启内存概况信息标志位
            if line.startswith("Physical Memory Array"):
                marker1 = True
                if len(memDataBits) > 0 :
                    oneMem[MMI_DATAWIDTH] = memDataBits
                if len(memManufacturer) > 0 :
                    oneMem[MMI_MANUFACTURER] = memManufacturer
                if len(memSize) > 0 :
                    oneMem[MMI_TOTALCAPACITY] = memSize
                if len(memType) > 0 :
                    oneMem[MMI_TYPE] = memType
                if len(memSpeed) > 0 :
                    oneMem[MMI_SPEED] = memSpeed
                if len(memTotalBits) > 0 :
                    oneMem[MMI_BUSWIDTH] = memTotalBits
                if len(memSlot) > 0 :
                    oneMem[MMI_SLOT] = memSlot
                if len(memSerialNum) > 0 :
                    oneMem[MMI_SERIALNUM] = memSerialNum
                if len(memConfigSpeed) > 0 :
                    oneMem[MMI_CONFIGSPEED] = memConfigSpeed
                if len(memPipe) > 0 :
                    oneMem[MMI_PIPE] = memPipe
                if len(memModel) > 0 :
                    oneMem[MMI_MODEL] = memModel
                if len(memArrayHandle) > 0 :
                    oneMem[MMI_ARRAYHANDLE] = memArrayHandle
                if len(memPartNum) > 0 :
                    oneMem[MMI_PARTNUMBER] = memPartNum
                if len(oneMem) > 0 :
                    summary["list"].append(oneMem)
                memManufacturer,memSize,memType,memSpeed,memTotalBits,memSlot,memSerialNum, \
                        memDataBits,memConfigSpeed,memPipe,memModel,memArrayHandle, memPartNum = "","",\
                        "","","","","","","","","","",""
                oneMem = {}

            ###
            if line.startswith("Memory Device"):
                marker2 = True
                if len(memDataBits) > 0 :
                    oneMem[MMI_DATAWIDTH] = memDataBits
                if len(memManufacturer) > 0 :
                    oneMem[MMI_MANUFACTURER] = memManufacturer
                if len(memSize) > 0 :
                    oneMem[MMI_TOTALCAPACITY] = memSize
                if len(memType) > 0 :
                    oneMem[MMI_TYPE] = memType
                if len(memSpeed) > 0 :
                    oneMem[MMI_SPEED] = memSpeed
                if len(memTotalBits) > 0 :
                    oneMem[MMI_BUSWIDTH] = memTotalBits
                if len(memSlot) > 0 :
                    oneMem[MMI_SLOT] = memSlot
                if len(memSerialNum) > 0 :
                    oneMem[MMI_SERIALNUM] = memSerialNum
                if len(memConfigSpeed) > 0 :
                    oneMem[MMI_CONFIGSPEED] = memConfigSpeed
                if len(memPipe) > 0 :
                    oneMem[MMI_PIPE] = memPipe
                if len(memModel) > 0 :
                    oneMem[MMI_MODEL] = memModel
                if len(memArrayHandle) > 0 :
                    oneMem[MMI_ARRAYHANDLE] = memArrayHandle
                if len(memPartNum) > 0 :
                    oneMem[MMI_PARTNUMBER] = memPartNum
                if len(oneMem) > 0 :
                    summary["list"].append(oneMem)
                memManufacturer,memSize,memType,memSpeed,memTotalBits,memSlot,memSerialNum, \
                        memDataBits,memConfigSpeed,memPipe,memModel,memArrayHandle, memPartNum = "","",\
                        "","","","","","","","","","",""
                oneMem = {}

            if line == "":
                marker1 = False
                if marker2:
                    index += 1
                marker2 = False

            ###过滤所有非必要信息
            if not marker1 and not marker2:
                continue

            if ":" not in line:
                continue

            values = [ v.strip() for v in line.split(":", 1)]

            ###内存概况信息
            if marker1:

                ##支持内存容量
                if line.startswith("Maximum Capacity:"):
                    summary["Maximum Capacity"] = values[1]

                ##支持内存条数
                if line.startswith("Number Of Devices:"):
                    summary["Number Of Devices"] = values[1]

            if marker2:
                ##名称
                if line.startswith("Part Number:"):
                    if values and len(values) > 1:
                        tempValue = values[1].strip()
                        if not self.isEmpty(tempValue) :
                            memPartNum = tempValue

                ##制造商
                if line.startswith("Manufacturer:"):
                    if values and len(values) > 1:
                        tempValue = values[1].strip()
                        if not self.isEmpty(tempValue) :
                            memManufacturer = tempValue

                ##内存通道
                if line.startswith("Bank Locator:"):
                    if values and len(values) > 1:
                        tempValue = values[1].strip()
                        if not self.isEmpty(tempValue) :
                            memPipe = tempValue

                ##类型
                if line.startswith("Type:"):
                    if values and len(values) > 1:
                        tempValue = values[1].strip()
                        if not self.isEmpty(tempValue) :
                            memType = tempValue

                ##总位宽
                if line.startswith("Total Width:"):
                    if values and len(values) > 1:
                        tempValue = values[1].strip()
                        if not self.isEmpty(tempValue) :
                            memTotalBits = tempValue

                ##数据位宽
                if line.startswith("Data Width:"):
                    if values and len(values) > 1:
                        tempValue = values[1].strip()
                        if not self.isEmpty(tempValue) :
                            memDataBits = tempValue

                ##序列号
                if line.startswith("Serial Number:"):
                    if values and len(values) > 1:
                        tempValue = values[1].strip()
                        if not self.isEmpty(tempValue) :
                            memSerialNum = tempValue

                # ##最低电压
                # if line.startswith("Minimum Voltage:"):
                #     summary["Mem Infos"][index][Mem_MinVoltage] = values[1]

                # ##最高电压
                # if line.startswith("Maximum Voltage:"):
                #     summary["Mem Infos"][index][Mem_MaxVoltage] = values[1]

                # ##配置电压
                # if line.startswith("Configured Voltage:"):
                #     summary["Mem Infos"][index][Mem_ConfVoltage] = values[1]

                ##尺寸型号
                if line.startswith("Form Factor:"):
                    if values and len(values) > 1:
                        tempValue = values[1].strip()
                        if not self.isEmpty(tempValue) :
                            memModel = tempValue

                ##位列
                # if line.startswith("Rank:"):
                #     summary["Mem Infos"][index][Mem_Rank] = values[1]

                ##容量
                if line.startswith("Volatile Size:") :
                    if values and len(values) > 1:
                        tempValue = values[1].strip()
                        if not self.isEmpty(tempValue) :
                            memSize = tempValue

                if line.startswith("Speed:") :
                    if values and len(values) > 1:
                        tempValue = values[1].strip()
                        if not self.isEmpty(tempValue) :
                            memSpeed = tempValue

                if line.startswith("Configured Memory Speed:") :
                    if values and len(values) > 1:
                        tempValue = values[1].strip()
                        if not self.isEmpty(tempValue) :
                            memConfigSpeed = tempValue

                if memManufacturer == "UNILC" and memPartNum == "6478545886" :
                    memSpeed = "2666 MT/s"
                    memConfigSpeed = "2666 MT/s"

                if line.startswith("Locator:") :
                    if values and len(values) > 1:
                        tempValue = values[1].strip()
                        if not self.isEmpty(tempValue) :
                            memSlot = tempValue

                if line.startswith("Array Handle:") :
                    if values and len(values) > 1:
                        tempValue = values[1].strip()
                        if not self.isEmpty(tempValue) :
                            memArrayHandle = tempValue
        if len(memDataBits) > 0 :
            oneMem[MMI_DATAWIDTH] = memDataBits
        if len(memManufacturer) > 0 :
            oneMem[MMI_MANUFACTURER] = memManufacturer
        if len(memSize) > 0 :
            oneMem[MMI_TOTALCAPACITY] = memSize
        if len(memType) > 0 :
            oneMem[MMI_TYPE] = memType
        if len(memSpeed) > 0 :
            oneMem[MMI_SPEED] = memSpeed
        if len(memTotalBits) > 0 :
            oneMem[MMI_BUSWIDTH] = memTotalBits
        if len(memSlot) > 0 :
            oneMem[MMI_SLOT] = memSlot
        if len(memSerialNum) > 0 :
            oneMem[MMI_SERIALNUM] = memSerialNum
        if len(memConfigSpeed) > 0 :
            oneMem[MMI_CONFIGSPEED] = memConfigSpeed
        if len(memPipe) > 0 :
            oneMem[MMI_PIPE] = memPipe
        if len(memModel) > 0 :
            oneMem[MMI_MODEL] = memModel
        if len(memArrayHandle) > 0 :
            oneMem[MMI_ARRAYHANDLE] = memArrayHandle
        if len(memPartNum) > 0 :
            oneMem[MMI_PARTNUMBER] = memPartNum
        if len(oneMem) > 0 :
            summary["list"].append(oneMem)
        memManufacturer,memSize,memType,memSpeed,memTotalBits,memSlot,memSerialNum, \
                memDataBits,memConfigSpeed,memPipe,memModel,memArrayHandle, memPartNum = "","",\
                "","","","","","","","","","",""
        oneMem = {}
        
        self.cmdTool.loadInfoFromLshw(False)
        for mapInfo in self.cmdTool.lshwMemoryList :
            if "slot" in mapInfo and len(mapInfo["slot"]) > 0 :
                length = len(summary["list"])
                if length > 0 :
                    for index in range(length):
                        if MMI_SLOT in summary["list"][index] and summary["list"][index][MMI_SLOT] == mapInfo["slot"]:
                            if "size" in mapInfo and MMI_TOTALCAPACITY not in summary["list"][index]:
                                tempSize = mapInfo["size"]
                                tempSize = tempSize.replace("GiB","GB")
                                if "MiB" in tempSize :
                                    tempSize = tempSize.replace("MiB","")
                                    if tempSize.isdigit() :
                                        size = float(tempSize)/1024.0
                                        summary["list"][index][MMI_TOTALCAPACITY] = str(float("%.1f" % size))+"GB"
                                else :
                                    summary["list"][index][MMI_TOTALCAPACITY] = tempSize
                            if "vendor" in mapInfo and MMI_MANUFACTURER not in summary["list"][index]:
                                summary["list"][index][MMI_MANUFACTURER] = mapInfo["vendor"]
                            if "product" in mapInfo and MMI_PARTNUMBER not in summary["list"][index]:
                                summary["list"][index][MMI_PARTNUMBER] = mapInfo["product"]
                            if "width" in mapInfo and MMI_DATAWIDTH not in summary["list"][index]:
                                summary["list"][index][MMI_DATAWIDTH] = mapInfo["width"]
                            continue
                else :
                    memInfo = {}
                    memInfo[MMI_SLOT] = mapInfo["slot"]
                    if "size" in mapInfo :
                        tempSize = mapInfo["size"]
                        tempSize = tempSize.replace("GiB","GB")
                        if "MiB" in tempSize :
                            tempSize = tempSize.replace("MiB","")
                            if tempSize.isdigit() :
                                size = float(tempSize)/1024.0
                                memInfo[MMI_TOTALCAPACITY] = str(float("%.1f" % size))+"GB"
                        else :
                            memInfo[MMI_TOTALCAPACITY] = tempSize
                    if "vendor" in mapInfo :
                        memInfo[MMI_MANUFACTURER] = mapInfo["vendor"]
                    if "product" in mapInfo :
                        memInfo[MMI_PARTNUMBER] = mapInfo["product"]
                    if "width" in mapInfo :
                        memInfo[MMI_DATAWIDTH] = mapInfo["width"]
                    if "description" in mapInfo :
                        memInfo[MMI_MODEL] = mapInfo["description"]
                    if "physical id" in mapInfo :
                        memInfo[MMI_PHYSICALID] = mapInfo["physical id"]
                    summary["list"].append(memInfo)
            else : ##没有slot
                if len(summary["list"]) == 0 :
                    memInfo = {}
                    if "slot" in mapInfo :
                        memInfo[MMI_SLOT] = mapInfo["slot"]
                    if "size" in mapInfo :
                        tempSize = mapInfo["size"]
                        tempSize = tempSize.replace("GiB","GB")
                        if "MiB" in tempSize :
                            tempSize = tempSize.replace("MiB","")
                            if tempSize.isdigit() :
                                size = float(tempSize)/1024.0
                                memInfo[MMI_TOTALCAPACITY] = str(float("%.1f" % size))+"GB"
                        else :
                            memInfo[MMI_TOTALCAPACITY] = tempSize
                    if "vendor" in mapInfo :
                        memInfo[MMI_MANUFACTURER] = mapInfo["vendor"]
                    if "product" in mapInfo :
                        memInfo[MMI_PARTNUMBER] = mapInfo["product"]
                    if "width" in mapInfo :
                        memInfo[MMI_DATAWIDTH] = mapInfo["width"]
                    if "description" in mapInfo :
                        memInfo[MMI_MODEL] = mapInfo["description"]
                        if MMI_MANUFACTURER not in memInfo :
                            memInfo[MMI_MANUFACTURER] = mapInfo["description"]
                    if "physical id" in mapInfo :
                        memInfo[MMI_PHYSICALID] = mapInfo["physical id"]
                    summary["list"].append(memInfo)

        return json.dumps(summary)

    #概要信息
    def getOutline(self) :
        outLine = self.getMemInfo()
        outLineObj = json.loads(outLine)
        outLine = ""
        if len(outLineObj) > 0 and "list" in outLineObj :
            nIndex = 0
            for info in outLineObj["list"] :
                if MMI_TOTALCAPACITY in info :
                    if nIndex == 0 :
                        outLine += info[MMI_TOTALCAPACITY]
                    else :
                        outLine += " / " + info[MMI_TOTALCAPACITY]
                if MMI_MANUFACTURER in info :
                        outLine += " "+info[MMI_MANUFACTURER]
                if MMI_TYPE in info :
                        outLine += " "+info[MMI_TYPE]
                if MMI_SPEED in info :
                        outLine += " "+info[MMI_SPEED]
                nIndex = nIndex + 1
        return outLine

if __name__ == "__main__":
    cmdtool = KACmdTool()
    cmdtool.loadInfoFromLshw()
    cc = MemoryInfo(cmdtool)
    pprint(cc.getMemInfo())
    #pprint(cc.getOutline())

