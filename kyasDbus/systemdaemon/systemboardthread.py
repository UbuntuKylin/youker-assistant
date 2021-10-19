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

Board_Product=                "Product Name"
Board_Manufacturer=           "Manufacturer"
Board_Version=                "Version"
Board_Chipset=                "Chipset"
Board_SMBIOS_Version=         "SMBIOS"
Board_Serial=                 "Serial Number"
Board_Location=               "Location In Chassis"
Board_ChassisHandle=          "Chassis Handle"
Board_Features=               "Features"
Board_ContainedObjHandles=    "Contained Object Handles"
Board_Type=                   "Type"
Board_AssetTag=               "Asset Tag"

BIOS_Manufacturer=            "Vendor"
BIOS_Version=                 "Version"
BIOS_Revision=                "BIOS Revision"
BIOS_FirmwareRevision=        "Firmware Revision"
BIOS_RomSize=                 "ROM Size"
BIOS_ReleaseDate=             "Release Date"
BIOS_InstallableLan=          "Installable Languages"
BIOS_Address=                 "Address"
BIOS_CurrentInstallableLan=   "Currently Installed Language"
BIOS_Characteristics=         "Characteristics"
BIOS_LanguageDescFormat=      "Language Description Format"
BIOS_RuntimeSize=             "Runtime Size"


System_Product=               "Product Name"
System_Manufacturer=          "Manufacturer"
System_Version=               "Version"
System_SKU_Number=            "SKU Number"
System_UUID=                  "UUID"
System_WakeUpType=            "Wake-up Type"
System_Family=                "Family"
System_SerialNumber=          "Serial Number"


Chassis_Manufacturer=         "Manufacturer"
Chassis_Version=              "Version"
Chassis_OEM_Info=             "OEM Information"
Chassis_SKU_Number=           "SKU Number"
Chassis_PowerSupplyState=     "Power Supply State"
Chassis_ContainedElements=    "Contained Elements"
Chassis_SerialNumber=         "Serial Number"
Chassis_BootUpState=          "Boot-up State"
Chassis_ThermalState=         "Thermal State"
Chassis_NumberOfPowerCords=   "Number Of Power Cords"
Chassis_Type=                 "Type"
Chassis_AssetTag=             "Asset Tag"
Chassis_Height=               "Height"


class SystemBoard():

    def __init__(self):
        pass

    def getSystemBoardInfo(self):
        summary = {"BaseBoard Infos":{}, "BIOS Infos":{}, "System Infos":{}, "Chassis Infos":{}}

        summary["BaseBoard Infos"] = self.getBaseBoardInfo()
        summary["BIOS Infos"] = self.getBiosInfo()
        summary["Chassis Infos"] = self.getChassisInfo()
        summary["System Infos"] = self.getSystemInfo()

        return json.dumps(summary)

    def getSystemInfo(self):
        systeminfo = {}

        args = ["dmidecode", "-t", "system"]
        pipe = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        output = pipe.stdout.readlines()

        marker1 = False
        marker2 = False

        for line in [ bytes.decode(l.strip(),"utf-8","ignore") for l in output]:
#            pprint(line)

            ###开启System信息标志位
            if line.startswith("System Information"):
                marker1 = True
                continue
            if line.startswith("System Event Log"):
                marker2 = True
                continue

            if line == "":
                marker1 = False
                marker2 = False

            ###过滤所有非必要信息
            if not marker1 and not marker2:
                continue

            if ":" not in line:
                continue

            values = [ v.strip() for v in line.split(":", 1)]

            ###System信息
            if marker1:
                ##制造商
                if line.startswith("Manufacturer:"):
                    systeminfo[System_Manufacturer] = values[1]
                    pass

                ##版本
                if line.startswith("Version:"):
                    systeminfo[System_Version] = values[1]
                    pass

                ##SKU号
                if line.startswith("SKU Number:"):
                    systeminfo[System_SKU_Number] = values[1]
                    pass

                ##UUID
                if line.startswith("UUID:"):
                    systeminfo[System_UUID] = values[1]
                    pass

                ##产品名称
                if line.startswith("Product Name:"):
                    systeminfo[System_Product] = values[1]
                    pass

                ##唤醒类型
                if line.startswith("Wake-up Type:"):
                    systeminfo[System_WakeUpType] = values[1]
                    pass

                ##家族
                if line.startswith("Family:"):
                    systeminfo[System_Family] = values[1]
                    pass

                ##序列号
                if line.startswith("Serial Number:"):
                    systeminfo[System_SerialNumber] = values[1]
                    pass

        return systeminfo

    def getBaseboardChipFamily(slef):
        chipFamily = ""

        args = ["lspci"]
        pipe = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        output = pipe.stdout.readlines()

        for line in [ bytes.decode(l.strip(),"utf-8","ignore") for l in output]:
            if len(line) > 0 :
                pciid = line.split(" ")

                if len(pciid) >= 2 and pciid[1] == "ISA":
                    args1 = ["lspci", "-v", "-s", pciid[0].strip()]
                    pipe1 = subprocess.Popen(args1, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                    output1 = pipe1.stdout.readlines()
                    
                    for line1 in [ bytes.decode(l1.strip(),"utf-8","ignore") for l1 in output1]:
                        if "Subsystem" in line1 or "subsystem" in line1:
                            chipsinfo = line1.split(": ");
                            if len(chipsinfo) == 2:
                                chipFamily = chipsinfo[1].strip()
                    break
        return chipFamily

    def getBiosInfo(self):
        biosinfo = {}

        args = ["dmidecode", "-t", "bios"]
        pipe = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        output = pipe.stdout.readlines()

        marker1 = False
        marker2 = False
        hasCharacteristics = False
        recordCharacteristic = []

        for line in [ bytes.decode(l.strip(),"utf-8","ignore") for l in output]:
#            pprint(line)

            ###开启BIOS信息标志位
            if line.startswith("BIOS Information"):
                marker1 = True
                continue
            if line.startswith("BIOS Language Information"):
                marker2 = True
                continue

            if line == "":
                marker1 = False
                marker2 = False

            ###过滤所有非必要信息
            if not marker1 and not marker2:
                continue

            ###BIOS信息的特殊处理
            if hasCharacteristics and ":" not in line:
                recordCharacteristic.append(line)

            if ":" not in line:
                continue

            values = [ v.strip() for v in line.split(":", 1)]

            ###BIOS信息
            if marker1:

                ##制造商
                if line.startswith("Vendor:"):
                    biosinfo[BIOS_Manufacturer] = values[1]

                ##版本
                if line.startswith("Version:"):
                    biosinfo[BIOS_Version] = values[1]

                ##BIOS修订版本
                if line.startswith("BIOS Revision:"):
                    biosinfo[BIOS_Revision] = values[1]

                ##固件修订版本
                if line.startswith("Firmware Revision:"):
                    biosinfo[BIOS_FirmwareRevision] = values[1]

                ##ROM大小
                if line.startswith("ROM Size:"):
                    biosinfo[BIOS_RomSize] = values[1]

                ##发布日期
                if line.startswith("Release Date:"):
                    biosinfo[BIOS_ReleaseDate] = values[1]

                ##地址
                if line.startswith("Address:"):
                    biosinfo[BIOS_Address] = values[1]

                ##特性
                if line.startswith("Characteristics:"):
                    biosinfo[BIOS_Characteristics] = values[1]

                ##运行内存大小
                if line.startswith("Runtime Size:"):
                    biosinfo[BIOS_RuntimeSize] = values[1]

            ###BIOS语言信息
            if marker2:
                ##语言描述格式
                if line.startswith("Language Description Format:"):
                    biosinfo[BIOS_LanguageDescFormat] = values[1]
                    pass

                ##可安装语言数
                if line.startswith("Installable Languages:"):
                    biosinfo[BIOS_InstallableLan] = values[1]
                    pass

                ##当前安装语言
                if line.startswith("Currently Installed Language:"):
                    biosinfo[BIOS_CurrentInstallableLan] = values[1]
                    pass

        return biosinfo

    def getBaseBoardInfo(self):
        boardinfo = {}

        args = ["dmidecode", "-t", "baseboard"]
        pipe = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        output = pipe.stdout.readlines()

        marker1 = False
        hasFeature = False

        recordFeature = []

        for line in [ bytes.decode(l.strip(),"utf-8","ignore") for l in output]:
#            pprint(line)

            ###开启主板信息标志位
            if line.startswith("Base Board Information"):
                marker1 = True
                continue

            if line == "":
                marker1 = False

            ###过滤所有非必要信息
            if not marker1:
                continue

            ###主板信息的特殊处理
            if hasFeature and ":" not in line:
                recordFeature.append(line)

            if ":" not in line:
                continue

            values = [ v.strip() for v in line.split(":", 1)]

            ###主板信息
            if marker1:

                ##制造商
                if line.startswith("Manufacturer:"):
                    boardinfo[Board_Manufacturer] = values[1]

                ##版本
                if line.startswith("Version:"):
                    boardinfo[Board_Version] = values[1]

                ##芯片组
                if line.startswith("chipset:"):
                    boardinfo[Board_Chipset] = values[1]

                ##SMBIOS版本
                if line.startswith("Version:"):
                    boardinfo[Board_Version] = values[1]

                ##产品名称
                if line.startswith("Product Name:"):
                    boardinfo[Board_Product] = values[1]


                ##包含对象程序
                if line.startswith("Contained Object Handles:"):
                    boardinfo[Board_ContainedObjHandles] = values[1]

                ##序列号
                if line.startswith("Serial Number:"):
                    boardinfo[Board_Serial] = values[1]


                ##机箱位置
                if line.startswith("Location In Chassis:"):
                    boardinfo[Board_Location] = values[1]


                ##机箱程序
                if line.startswith("Chassis Handle:"):
                    boardinfo[Board_ChassisHandle] = values[1]


                ##包含“特征”字段
                if line.startswith("Features:"):
                    hasFeature = True

                ##类型
                if line.startswith("Type:"):
                    boardinfo[Board_Type] = values[1]

                ##资产编号
                if line.startswith("Asset Tag:"):
                    boardinfo[Board_AssetTag] = values[1]
        ##特征
        if hasFeature:
            boardinfo[Board_Features] = "\n".join(recordFeature)

        ##芯片组
        if len(boardinfo) > 0 and Board_Chipset not in boardinfo:
            chipFamily = self.getBaseboardChipFamily()
            if len(chipFamily) > 0 :
                boardinfo[Board_Chipset] = chipFamily

        return boardinfo

    def getChassisInfo(self):
        chassisinfo = {}

        args = ["dmidecode", "-t", "chassis"]
        pipe = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        output = pipe.stdout.readlines()

        marker1 = False

        for line in [ bytes.decode(l.strip(),"utf-8","ignore") for l in output]:
#            pprint(line)

            ###开启机箱信息标志位
            if line.startswith("Chassis Information"):
                marker1 = True
                continue

            if line == "":
                marker1 = False

            ###过滤所有非必要信息
            if not marker1:
                continue

            values = [ v.strip() for v in line.split(":", 1)]

            ###机箱信息
            if marker1:

                ##制造商
                if line.startswith("Manufacturer:"):
                    chassisinfo[Chassis_Manufacturer] = values[1]
                    pass

                ##版本
                if line.startswith("Version:"):
                    chassisinfo[Chassis_Version] = values[1]
                    pass

                ##OEM信息
                if line.startswith("OEM Information:"):
                    chassisinfo[Chassis_OEM_Info] = values[1]
                    pass

                ##SKU号
                if line.startswith("SKU Number:"):
                    chassisinfo[Chassis_SKU_Number] = values[1]
                    pass

                ##供电状态
                if line.startswith("Power Supply State:"):
                    chassisinfo[Chassis_PowerSupplyState] = values[1]
                    pass

                ##包含组件数
                if line.startswith("Contained Elements:"):
                    chassisinfo[Chassis_ContainedElements] = values[1]
                    pass

                ##序列号
                if line.startswith("Serial Number:"):
                    chassisinfo[Chassis_SerialNumber] = values[1]
                    pass

                ##开机状态
                if line.startswith("Boot-up State:"):
                    chassisinfo[Chassis_BootUpState] = values[1]
                    pass

                ##散热状态
                if line.startswith("Thermal State:"):
                    chassisinfo[Chassis_ThermalState] = values[1]
                    pass

                ##电源线数
                if line.startswith("Number Of Power Cords:"):
                    chassisinfo[Chassis_Manufacturer] = values[1]
                    pass

                ##类型
                if line.startswith("Type:"):
                    chassisinfo[Chassis_Type] = values[1]
                    pass

                ##高度
                if line.startswith("Height:"):
                    chassisinfo[Chassis_Height] = values[1]
                    pass

                ##资产标号
                if line.startswith("Asset Tag:"):
                    chassisinfo[Chassis_AssetTag] = values[1]
                    pass

        return chassisinfo

    #概要信息
    def getOutline(self) :
        outLineObj = self.getBaseBoardInfo()
        outLine = ""
        if Board_Product in outLineObj :
            outLine += outLineObj[Board_Product]
        return outLine

if __name__ == "__main__":
    cc = SystemBoard()
    #pprint(cc.getSystemBoardInfo())
    pprint(cc.getOutline())

