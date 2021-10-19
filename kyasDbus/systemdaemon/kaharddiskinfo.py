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
from utils import *

class KAHarddiskInfo() :

    def __init__(self, cmdtool):
        self.cmdTool = cmdtool
        pass

    def get_human_read_capacity_size(self, size):
        size_str = ""
        displayed_size = 0.0
        unit = "KB"

        if size < MEGABYTE_FACTOR:
            displayed_size = float(size/KILOBYTE_FACTOR)
            unit = "KB"
        elif size < GIGABYTE_FACTOR:
            displayed_size = float(size/MEGABYTE_FACTOR)
            unit = "MB"
        elif size < TERABYTE_FACTOR:
            displayed_size = float(size/GIGABYTE_FACTOR)
            unit = "GB"
        else:
            displayed_size = float(size/TERABYTE_FACTOR)
            unit = "TB"
        #print "displayed_size=", round(displayed_size)
        #round 不是简单的四舍五入，而是ROUND_HALF_EVEN的策略
        #ceil 取大于或者等于x的最小整数
        #floor 取小于或者等于x的最大整数
        #print round(2.5)#3.0
        #print math.ceil(2.5)#3.0
        #print math.floor(2.5)#2.0
        #print round(2.3)#2.0
        #print math.ceil(2.3)#3.0
        #print math.floor(2.3)#2.0
        if (unit == "TB"):
            str_list = [str(int(round(displayed_size, 1))), unit]
        else:
            str_list = [str(int(round(displayed_size))), unit]

        size_str = " ".join(str_list)
        return size_str

    def chkIsMainDisk(self, devName):
        if len(devName) <= 0 :
            return "0"
        status, output = subprocess.getstatusoutput("lsblk -b "+devName)
        if status :
            return "0"
        for line in output.split("\n"):
            value = line.split()
            if len(value) >= 7 and value[6]:
                if value[6] == "/" :
                    return "1"
        return "0"

    def chkIsSSD(self, devFileName):
        if len(devFileName) <= 0 :
            return "0"
        status, output = subprocess.getstatusoutput("lsblk -d -o name,rota")
        if status :
            return "0"
        for line in output.split("\n"):
            value = line.split()
            if len(value) >= 2 and value[1]:
                if value[0] == devFileName and value[1] == "0" :
                    return "1"
        return "0"

    def get_disk(self):
        disklist = []
        disk_manufacturers = {
                "ST": "Seagate",
                "IBM": "IBM",
                "HITACHI": "Hitachi",
                "IC": "Hitachi",
                "HTS": "Hitachi",
                "FUJITSU": "Fujitsu",
                "MP": "Fujitsu",
                "TOSHIBA": "Toshiba",
                "MK": "Toshiba",
                "MAXTOR": "Maxtor",
                "Pioneer": "Pioneer",
                "PHILIPS": "Philips",
                "QUANTUM": "Quantum",
                "FIREBALL": "Quantum",
                "WDC": "Western Digital",
                "HGST HUS": "Western Digital",
                "FORESEE": "Foresee",
                }

        diskList = self.cmdTool.loadInfoFromHwinfo("--disk")
        self.cmdTool.loadDiskInfoFromLsblk()
        if "list" in diskList and len(diskList["list"]) > 0 :
            length = len(diskList["list"])
            for i in range(length) :
                if "SysFS BusID" in diskList["list"][i] :
                    for mapInfo in self.cmdTool.lshwDiskList :
                        if "bus info" in mapInfo :
                            words = mapInfo["bus info"].split("@")
                            if len(words) != 2 :
                                continue
                            key = words[1].strip()
                            key = key.replace(".",":")
                            if key != diskList["list"][i]["SysFS BusID"] :
                                continue
                            diskList["list"][i].update(mapInfo)
                if "SysFS Device Link" in diskList["list"][i]:
                    for mapInfo in self.cmdTool.lshwStorageList :
                        if "bus info" in mapInfo :
                            words = mapInfo["bus info"].split("@")
                            if len(words) != 2 :
                                continue
                            key = words[1].strip().lower()
                            if key not in diskList["list"][i]["SysFS Device Link"].lower() :
                                continue
                            diskList["list"][i].update(mapInfo)
                for mapInfo in self.cmdTool.lsblkSmartList :
                    if "dev_name" in mapInfo and "Device File" in diskList["list"][i] \
                        and mapInfo["dev_name"] in diskList["list"][i]["Device File"] :
                        diskList["list"][i].update(mapInfo)
            flag = Judgment_HW990()

            for diskInfo in diskList["list"] :
                disk = {}
                DiskProduct,DiskVendor,DiskCapacity,DiskName,DiskFw,DiskSerial,DiskRota,DiskInterface = '','','','','','','',''
                devName = ""
                IsRemoveable = False
                if "dev_name" in diskInfo :
                    devName = diskInfo["dev_name"]
                if "dev_majmin" in diskInfo :
                    majorId = diskInfo["dev_majmin"].split(":")
                    if len(majorId) == 2 and majorId[0] != "259" and majorId[0] != "8" and majorId[0] != "253" :
                        continue
                if flag and len(devName) > 0 :
                    if "sda" == devName or "sdb" == devName or "sdc" == devName :
                        continue
                if "Capacity" in diskInfo :
                    DiskCapacity = diskInfo["Capacity"]
                    result = re.findall("\((.*) bytes\)", DiskCapacity)
                    DiskCapacity = re.sub("\(.*\)", "", DiskCapacity).replace(" ", "")
                    if DiskCapacity.startswith("0") or DiskCapacity == "" :
                        continue
                    if result and len(result) > 0:
                        if result[0].isdigit() :
                            size = float(result[0])/1000.0/1000.0/1000.0
                            if size >= 1000.0 :
                                size = size/1000.0
                                DiskCapacity = str(float("%0.1f" % size))+"TB"
                            else :
                                DiskCapacity = str(int("%d" % size))+"GB"
                if len(DiskCapacity) == 0 and "size" in diskInfo :
                    DiskCapacity = diskInfo["size"]
                    result = re.findall(".*\((.*)\)$", DiskCapacity)
                    if result and len(result) > 0 :
                        DiskCapacity = result[0]
                capacity = ""
                if "User Capacity" in diskInfo :
                    capacity = diskInfo["User Capacity"]
                if len(capacity) == 0 and "Total NVM Capacity" in diskInfo :
                    capacity = diskInfo["Total NVM Capacity"]
                if len(capacity) > 0 :
                    result = re.findall(".*\[(.*)\]$", capacity)
                    if result and len(result) > 0 :
                        DiskCapacity = result[0]
                if DiskCapacity.startswith("0") or DiskCapacity == "" :
                    continue
                DiskName = ("/dev/" + devName)
                IsMainDisk = self.chkIsMainDisk(DiskName)
                IsSSD = "0"
                if "dev_rota" in diskInfo :
                    if diskInfo["dev_rota"] == "0" :
                        IsSSD = "1"
                    else :
                        IsSSD = "0"
                if "Rotation Rate" in diskInfo :
                    if diskInfo["Rotation Rate"] == "Solid State Device" :
                        IsSSD = "1"
                    else :
                        DiskRota = diskInfo["Rotation Rate"]
                if "dev_removeable" in diskInfo :
                    IsRemoveable = (diskInfo["dev_removeable"] == "1")
                if "Vendor" in diskInfo :
                    diskVendor = diskInfo["Vendor"].split("\"")
                    if len(diskVendor) > 1 :
                        DiskVendor = diskVendor[1]
                    else :
                        DiskVendor = diskInfo["Vendor"]
                if "SubVendor" in diskInfo :
                    diskVendor = diskInfo["SubVendor"].split("\"")
                    if len(diskVendor) > 1 :
                        DiskVendor = diskVendor[1]
                    else :
                        DiskVendor = diskInfo["SubVendor"]
                if "vendor" in diskInfo :
                    DiskVendor = diskInfo["vendor"]
                if len(DiskVendor) > 0 :
                    for key, va in list(disk_manufacturers.items()):
                        if DiskVendor.startswith(key):
                            DiskVendor = va
                            break
                if "serial" in diskInfo:
                    DiskSerial = diskInfo["serial"]
                if "Serial Number" in diskInfo :
                    DiskSerial = diskInfo["Serial Number"]
                if "Model" in diskInfo :
                    DiskProduct = diskInfo["Model"]
                if "product" in diskInfo :
                    DiskProduct = diskInfo["product"]
                if "Device Model" in diskInfo and len(diskInfo["Device Model"]) > 0 :
                    DiskProduct = diskInfo["Device Model"]
                if "Model Number" in diskInfo and len(diskInfo["Model Number"]) > 0 :
                    DiskProduct = diskInfo["Model Number"]
                if len(DiskProduct) > 0 :
                    for key, va in list(disk_manufacturers.items()):
                        if DiskProduct.startswith(key):
                            DiskVendor = va
                            break
                if "Firmware Version" in diskInfo :
                    DiskFw = diskInfo["Firmware Version"]
                if "Attached to" in diskInfo :
                    DiskInterface = diskInfo["Attached to"]
                    interface = re.findall(".*\((.*)\).*", DiskInterface)
                    if interface and len(interface) > 0 :
                        DiskInterface = interface[0]
                        DiskInterface = DiskInterface.replace("Controller", "").strip()
                        DiskInterface = DiskInterface.replace("controller", "").strip()

                if len(DiskCapacity) > 0 :
                    disk[HDI_CAPACITY] = DiskCapacity
                if len(DiskName) > 0 :
                    disk[HDI_NAME] = DiskName
                if len(DiskProduct) :
                    disk[HDI_MODEL] = DiskProduct
                if len(DiskVendor) > 0 and DiskVendor != "USB" :
                    disk[HDI_MANUFACTURER] = DiskVendor
                if len(DiskSerial) > 0 :
                    disk[HDI_SERIALNUM] = DiskSerial;
                if len(DiskFw) > 0 :
                    disk[HDI_FIRMWAREVER] = DiskFw
                disk[HDI_ISMAINDISK] = IsMainDisk
                if not IsRemoveable :
                    disk[HDI_ISSSD] = IsSSD
                if len(DiskRota) > 0 :
                    disk[HDI_ROTA] = DiskRota
                if len(DiskInterface) > 0:
                    disk[HDI_INTERFACE] = DiskInterface
                disklist.append(disk)

        return disklist

    #概要信息
    def getOutline(self) :
        outLineObj = self.get_disk()
        outLine = ""
        for info in outLineObj :
            if HDI_ISMAINDISK in info and info[HDI_ISMAINDISK] == '1':
                if HDI_MODEL in info :
                    outLine += info[HDI_MODEL]
                if HDI_CAPACITY in info :
                    outLine += "(" + info[HDI_CAPACITY]+")"
                break
        return outLine

if __name__ == "__main__":
    cmdTool = KACmdTool()
    cmdTool.loadInfoFromLshw()
    cc = KAHarddiskInfo(cmdTool)
    pprint(cc.get_disk())
    #pprint(cc.getOutline())
