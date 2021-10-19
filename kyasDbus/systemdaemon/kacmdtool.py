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

import os
import re
import subprocess

from pprint import pprint

from kajsondef import *

class KACmdTool():

    def __init__(self):
        self.lshwSystemList = []
        self.lshwDiskList = []
        self.lshwCpuList = []
        self.lshwStorageList = []
        self.lshwMemoryList = []
        self.lshwDisplayList = []
        self.lshwMultimediaList = []
        self.lshwNetworkList = []
        self.lshwUsbList = []
        self.lshwCDRomList = []
        self.lsblkSmartList = []
        self.dmesgGPUList = []
        self.nvidiaGpuList = []
        pass

    def loadHwinfoUsbinfo(self, info, summary, mapInfo):
        add = True
        for item in summary:
            if "SysFS BusID" in item:
                curBus = item["SysFS BusID"]
                newBus = mapInfo["SysFS BusID"]
                curBus = re.sub("\\.[0-9]{1,2}$", "", curBus)
                newBus = re.sub("\\.[0-9]{1,2}$", "", newBus)
                if curBus == newBus :
                    add = False
                    break
        ## 这个是用来过滤，没有接入任何设备的usb接口
        if "Model" in mapInfo and "Linux Foundation" in mapInfo["Model"] :
            add = False

        if "Hardware Class" in mapInfo and "hub".lower() in mapInfo["Hardware Class"].lower() :
            add = False

        ## 打印机几信息不从hwinfo --usb里面获取，需要过滤
        if "Printer".lower() in info.lower() or "LaserJet".lower() in info.lower() :
            add = False

        ## 提前过滤掉键盘鼠标
        if "mouse".lower() in info.lower() or "keyboard".lower() in info.lower() :
            add = False

        if "Wacom".lower() in info.lower() :
            add = False

        if add :
            summary["list"].append(mapInfo)

    def loadInfoFromHwinfo(self, param):
        summary = {"list":[]}

        args = ["hwinfo", param]
        pipe = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        output = pipe.stdout.readlines()

        allinfo = ""
        for l in output:
            result = bytes.decode(l, "utf-8", "ignore")
            if result :
                allinfo += result

        infoList = allinfo.split("\n\n")
        for info in infoList:
            if len(info) != 0 :
                mapInfo = {}
                infoLines = info.split("\n")
                for line in infoLines:
                    words = line.split(": ")
                    if len(words) != 2 :
                        continue
                    if words[0].strip() in mapInfo:
                        mapInfo[words[0].strip()] += " "
                    result = re.findall(".*\"(.*)\".*", words[1])
                    if result and len(result) > 0 :
                        key = words[0].strip()
                        value = result[0]
                        ##这里是为了防止  "usb-storage", "sr"  -》 usb-storage", "sr
                        if key == "Driver" :
                            value = value.replace("\"", "");
                        if key in mapInfo :
                            mapInfo[key] += value;
                        else :
                            mapInfo[key] = value;
                    else :
                        if words[0].strip() == "Resolution" and words[0].strip() in mapInfo :
                            mapInfo[words[0].strip()] += words[1].strip();
                        else :
                            mapInfo[words[0].strip()] = words[1].strip();

                if "--usb" == param :
                    self.loadHwinfoUsbinfo(info, summary, mapInfo)
                elif "--keyboard" == param or "--mouse" == param :
                    if "Linux Foundation" not in info and "Elite Remote Control Driver" not in info \
                        and "Model: \"serial console\"" not in info and "Wacom".lower() not in info.lower() :
                        summary["list"].append(mapInfo)
                else :
                    summary["list"].append(mapInfo)
        return summary

    def loadDiskInfoFromSmart(self, devName, mapInfo) :
        indexName = ""

        args = ["smartctl", "--all", "/dev/"+devName]
        pipe = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        output = pipe.stdout.readlines()

        allinfo = ""
        for l in output:
            allinfo += bytes.decode(l,"utf-8","ignore")

        infos = allinfo.split("\n")
        for line in infos:
            if len(line) > 0 :
                index = line.find(": ")
                if index > 0 and not re.findall("^[\s\S]*[\d]:[\d][\s\S]*$", line) and "Error" not in line and "hh:mm:SS" not in line :
                    if line.find("(") < index and line.find(")") > index :
                        continue
                    if line.find("[") < index and line.find("]") > index :
                        continue
                    words = line.split(": ")
                    if len(words) != 2 :
                        continue
                    indexName = words[0].strip().replace(" is", "")
                    if indexName in mapInfo :
                        mapInfo[indexName] += ", "
                        mapInfo[indexName] += words[1].strip()
                    else :
                        mapInfo[indexName] = words[1].strip()
                    continue

                if len(indexName) > 0 and (line.startswith("\t\t") or line.startswith("    ")) and ":" not in line :
                    if indexName in mapInfo :
                        mapInfo[indexName] += ", "
                        mapInfo[indexName] += line.strip()
                    else :
                        mapInfo[indexName] = line.strip()
                    continue

                indexName = ""
                # 1 Raw_Read_Error_Rate     0x002f   200   200   051    Pre-fail  Always       -       0
                result = re.findall("\s*[0-9]+\s+([\w\_]+)\s+0x[0-9a-fA-F\-]+\s+[0-9]+\s+[0-9]+\s+[0-9]+\s+[\w]+\s+[\w]+\s+[\w\-]+\s+([0-9]+)$", line)
                if result and len(result) > 0:
                    mapInfo[result[0][0]] = result[0][1]
                    continue;

                strList = []
                if line.endswith(")") :
                    leftBracket = line.find("(")
                    if leftBracket > 0 :
                        key = line[:leftBracket].strip()
                        strList = key.split(" ")
                        if len(strList) > 2 :
                            strList[-1] += line[leftBracket:]
                elif len(strList) == 0 :
                    strList = line.strip().split(" ")

                if len(strList) < 5 :
                    continue
                
                if "Power_On_Hours" in line :
                    mapInfo["Power_On_Hours"] = strList[-1];
                    continue

                if "Power_Cycle_Count" in line :
                    mapInfo["Power_Cycle_Count"] = strList[-1];
                    continue
                
                if "Raw_Read_Error_Rate" in line :
                    mapInfo["Raw_Read_Error_Rate"] = strList[-1];
                    continue

                if "Spin_Up_Time" in line :
                    mapInfo["Spin_Up_Time"] = strList[-1];
                    continue

                if "Start_Stop_Count" in line :
                    mapInfo["Start_Stop_Count"] = strList[-1];
                    continue

                if "Reallocated_Sector_Ct" in line :
                    mapInfo["Reallocated_Sector_Ct"] = strList[-1];
                    continue

                if "Seek_Error_Rate" in line :
                    mapInfo["Seek_Error_Rate"] = strList[-1];
                    continue

                if "Spin_Retry_Count" in line :
                    mapInfo["Spin_Retry_Count"] = strList[-1];
                    continue

                if "Calibration_Retry_Count" in line :
                    mapInfo["Calibration_Retry_Count"] = strList[-1];
                    continue

                if "G-Sense_Error_Rate" in line :
                    mapInfo["G-Sense_Error_Rate"] = strList[-1];
                    continue

                if "Power-Off_Retract_Count" in line :
                    mapInfo["Power-Off_Retract_Count"] = strList[-1];
                    continue

                if "Load_Cycle_Count" in line :
                    mapInfo["Load_Cycle_Count"] = strList[-1];
                    continue

                if "Temperature_Celsius" in line :
                    mapInfo["Temperature_Celsius"] = strList[-1];
                    continue

                if "Reallocated_Event_Count" in line :
                    mapInfo["Reallocated_Event_Count"] = strList[-1];
                    continue

                if "Current_Pending_Sector" in line :
                    mapInfo["Current_Pending_Sector"] = strList[-1];
                    continue

                if "Offline_Uncorrectable" in line :
                    mapInfo["Offline_Uncorrectable"] = strList[-1];
                    continue

                if "UDMA_CRC_Error_Count" in line :
                    mapInfo["UDMA_CRC_Error_Count"] = strList[-1];
                    continue

                if "Multi_Zone_Error_Rate" in line :
                    mapInfo["Multi_Zone_Error_Rate"] = strList[-1];
                    continue

        return mapInfo

    def loadDiskInfoFromLsblk(self) :
        args = ["lsblk", "-d", "-o", "name,rota,rm,maj:min"]
        pipe = subprocess.Popen(args, env={'LANGUAGE':'en:'}, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        output = pipe.stdout.readlines()

        allinfo = ""
        for l in output:
            allinfo += bytes.decode(l,"utf-8","ignore")

        lines = allinfo.split("\n");
        for line in lines :
            words = re.sub("[\s]+", " ", line).strip().split(" ")
            if len(words) != 4 or words[0] == "NAME" :
                continue
            mapInfo = {}
            mapInfo["dev_name"] = words[0].strip()
            mapInfo["dev_rota"] = words[1].strip()
            mapInfo["dev_removeable"] = words[2].strip()
            mapInfo["dev_majmin"] = words[3].strip()
            self.loadDiskInfoFromSmart(words[0].strip(), mapInfo)
            self.lsblkSmartList.append(mapInfo)
        pass

    def getInfoFromLshw(self, info, mapInfo) :
        infoList = info.split("\n")
        for infoItem in infoList:
            words = infoItem.split(": ")
            if len(words) != 2 :
                continue
            if "configuration" in words[0] :
                keyValues = words[1].split(" ")
                for keyValue in keyValues :
                    attr = keyValue.split("=")
                    if len(attr) != 2 :
                        continue
                    mapInfo[attr[0].strip()] = attr[1].strip()
            elif "resources" in words[0] :
                keyValues = words[1].split(" ")
                for keyValue in keyValues:
                    attr = keyValue.split(":")
                    if len(attr) != 2 :
                        continue
                    if attr[0].strip() in mapInfo :
                        mapInfo[attr[0].strip()] += "  "+attr[1].strip()
                    else :
                        mapInfo[attr[0].strip()] = attr[1].strip()
            else :
                mapInfo[words[0].strip()] = words[1].strip()
        

    def loadInfoFromLshw(self, forceLoad = True):
        if not forceLoad and len(self.lshwSystemList) > 0 :
            return

        args = ["lshw"]
        pipe = subprocess.Popen(args, env={'LANGUAGE':'en:'}, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        output = pipe.stdout.readlines()

        allinfo = ""
        for l in output:
            allinfo += bytes.decode(l,"utf-8","ignore")
        
        items = allinfo.split("*-");
        isFirst = True
        self.lshwSystemList = []
        self.lshwDiskList = []
        self.lshwCpuList = []
        self.lshwStorageList = []
        self.lshwMemoryList = []
        self.lshwDisplayList = []
        self.lshwMultimediaList = []
        self.lshwNetworkList = []
        self.lshwUsbList = []
        self.lshwCDRomList = []
        for item in items :
            if len(item) > 0 :
                mapInfo = {}
                if isFirst :
                    self.getInfoFromLshw(item, mapInfo)
                    self.lshwSystemList.append(mapInfo)
                    isFirst = False
                    continue
                if item.startswith("cpu") :
                    self.getInfoFromLshw(item, mapInfo)
                    self.lshwCpuList.append(mapInfo)
                elif item.startswith("disk") :
                    self.getInfoFromLshw(item, mapInfo)
                    self.lshwDiskList.append(mapInfo)
                elif item.startswith("storage") :
                    self.getInfoFromLshw(item, mapInfo)
                    self.lshwStorageList.append(mapInfo)
                elif (item.startswith("memory") and not item.startswith("memory UNCLAIMED")) or item.startswith("bank") :
                    self.getInfoFromLshw(item, mapInfo)
                    self.lshwMemoryList.append(mapInfo)
                elif item.startswith("display") :
                    self.getInfoFromLshw(item, mapInfo)
                    self.lshwDisplayList.append(mapInfo)
                elif item.startswith("multimedia") :
                    self.getInfoFromLshw(item, mapInfo)
                    self.lshwMultimediaList.append(mapInfo)
                elif item.startswith("network") :
                    self.getInfoFromLshw(item, mapInfo)
                    if not re.findall(".*network:[0-9] DISABLED.*", item) :
                        self.lshwNetworkList.append(mapInfo)
                elif item.startswith("usb") :
                    self.getInfoFromLshw(item, mapInfo)
                    if "description" in mapInfo and "Audio device" in mapInfo["description"] :
                        self.lshwMultimediaList.append(mapInfo)
                    else :
                        self.lshwUsbList.append(mapInfo)
                elif item.startswith("cdrom") :
                    self.getInfoFromLshw(item, mapInfo)
                    self.lshwCDRomList.append(mapInfo)

    def loadNetworkInfoFromIfconfig(self):
        args = ["ifconfig"]
        pipe = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        output = pipe.stdout.readlines()

        allinfo = ""
        for l in output:
            allinfo += bytes.decode(l,"utf-8","ignore")

        infoList = []
        items = allinfo.split("\n\n")
        for item in items :
            lines = item.strip().split("\n")
            lineCount = len(lines)
            mapInfo = {}
            for i in range(lineCount) :
                if i == 0 :
                    result = re.findall("(\S+)\s+.*", lines[i])
                    if result and len(result) > 0 :
                        mapInfo["NetName"] = result[0].strip().strip(":")
                    result = re.findall("mtu\s+(\S+)", lines[i])
                    if result and len(result) > 0 :
                        mapInfo["NetMTU"] = result[0].strip()
                else :
                    result = re.findall("inet\s+(\S+)", lines[i])
                    if result and len(result) > 0 :
                        mapInfo["NetIp"] = result[0].strip()
                    result = re.findall("netmask\s+(\S+)", lines[i])
                    if result and len(result) > 0 :
                        mapInfo["NetMask"] = result[0].strip()
                    result = re.findall("broadcast\s+(\S+)", lines[i])
                    if result and len(result) > 0 :
                        mapInfo["NetBroadcast"] = result[0].strip()
                    result = re.findall("inet6\s+(\S+)", lines[i])
                    if result and len(result) > 0 :
                        mapInfo["NetIp6"] = result[0].strip()
                    result = re.findall("ether\s+(\S+)", lines[i])
                    if result and len(result) > 0 :
                        mapInfo["NetMac"] = result[0].strip()
                    result = re.findall("RX packets\s+.*\((.*)\)", lines[i])
                    if result and len(result) > 0 :
                        mapInfo["NetRxData"] = result[0].strip()
                    result = re.findall("TX packets\s+.*\((.*)\)", lines[i])
                    if result and len(result) > 0 :
                        mapInfo["NetTxData"] = result[0].strip()

            if len(mapInfo) > 0 :
                infoList.append(mapInfo)

        return infoList

    def loadBluetoothInfo(self, mapInfo):
        if "BD Address" not in mapInfo :
            return
        pass

    def loadInfoFromHciconfig(self):
        args = ["hciconfig", "-a"]
        pipe = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        output = pipe.stdout.readlines()

        allinfo = ""
        for l in output:
            allinfo += bytes.decode(l,"utf-8","ignore")

        infoList = []
        items = allinfo.split("\n\n")
        for item in items :
            if len(item) == 0 :
                continue
            mapInfo = {}
            isFirstLine = True
            lines = item.strip().split("\n")
            for line in lines :
                if isFirstLine :
                    result = re.findall("(hci[0-9]+):", line)
                    if result and len(result) > 0 :
                        mapInfo["dev_name"] = result[0]
                        line = re.sub(result[0]+":","", line)
                    isFirstLine = False
                linepairs = line.strip().split("  ")
                if len(linepairs) < 1 :
                    continue
                for pair in linepairs :
                    words = pair.strip().split(": ")
                    if len(words) == 2 :
                        mapInfo[words[0].strip()] = words[1].strip()
            self.loadBluetoothInfo(mapInfo)
            if len(mapInfo) > 0 :
                infoList.append(mapInfo)

        return infoList

    def loadGPUInfoFromDmesg(self, forceUpdate = True) :
        if not forceUpdate and len(self.dmesgGPUList) > 0 :
            return None
        args = ["dmesg"]
        pipe = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        output = pipe.stdout.readlines()

        allinfo = ""
        for l in output:
            allinfo += bytes.decode(l,"utf-8","ignore")

        infoList = []
        lines = allinfo.split("\n")
        mapInfo = {}
        for line in lines :
            if len(line) == 0 :
                continue
            result = re.findall(".*RAM width ([0-9]*bits) (.*DDR.*)", line)
            if result and len(result) > 0 :
                membitwidth = result[0][0]
                memtype = result[0][1]
                mapInfo["mem_bitwidth"] = membitwidth
                mapInfo["mem_type"] = memtype
                continue

            result = re.findall(".*RAM=([0-9]*)M.*", line)
            if result and len(result) > 0 and result[0].isdigit() :
                size = float(result[0])
                sizeS = str(float("%0.1f"%(size/1024)))+"GB"
                mapInfo["size"] = sizeS
                continue
            result = re.findall(".*RAM: ([0-9]*) M.*", line)
            if result and len(result) > 0 and result[0].isdigit() :
                size = float(result[0])
                sizeS = str(float("%0.1f"%(size/1024)))+"GB"
                mapInfo["size"] = sizeS
                continue
            result = re.findall(".*RAM Size ([0-9]*)M.*", line)
            if result and len(result) > 0 and result[0].isdigit() :
                size = float(result[0])
                sizeS = str(float("%0.1f"%(size/1024)))+"GB"
                mapInfo["size"] = sizeS
                continue
        if len(mapInfo) == 0 :
            mapInfo["size"] = ""
            self.dmesgGPUList.append(mapInfo)
        else :
            self.dmesgGPUList.append(mapInfo)
        return self.dmesgGPUList

    def loadGPUInfoFromNvidiaSmi(self, forceUpdate = True) :
        if not forceUpdate and len(self.nvidiaGpuList) > 0 :
            return None
        if not os.path.exists("/usr/bin/nvidia-smi") :
            return None
        args = ["/usr/bin/nvidia-smi", "-q", "-d", "MEMORY"]
        pipe = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        output = pipe.stdout.readlines()

        allinfo = ""
        for l in output:
            allinfo += bytes.decode(l,"utf-8","ignore")

        infoList = []
        value = re.findall("\nGPU (.*)", allinfo)
        for gpuBusId in value :
            singleInfos = allinfo.split("\nGPU ")
            for singleInfo in singleInfos :
                if singleInfo.startswith(gpuBusId) :
                    words = gpuBusId.split(":", 1)
                    gpuOne = {}
                    memFree = 0
                    memUsed = 0
                    if len(words) == 2 :
                        gpuOne["nvidia_id"] = words[1]
                        gpuOne["nvidia_mem"] = ""
                        lines = singleInfo.split("\n")
                        isFBSession = False
                        for line in lines :
                            if len(line) == 0 :
                                continue
                            words = line.strip().split(":")
                            if not isFBSession :
                                if len(words) > 0 and words[0] == "FB Memory Usage" :
                                    isFBSession = True
                            else :
                                if len(words) == 2 :
                                    keyW = words[0].strip()
                                    valW = words[1].strip().replace(" ", "")
                                    if keyW == "Total" :
                                        result = re.findall("(.*)M.*", valW)
                                        if result and len(result) > 0 and result[0].isdigit():
                                            size = float(result[0])
                                            if size % 128 != 0 :
                                                size = size + 128 - (size%128)
                                            sizeS = str(float("%0.1f"%(size/1024)))+"GB"
                                            gpuOne["nvidia_mem"] = sizeS
                                        else :
                                            gpuOne["nvidia_mem"] = valW
                                    elif keyW == "Used" :
                                        gpuOne["nvidia_mem_used"] = valW
                                        result = re.findall("(.*)M.*", valW)
                                        if result and len(result) > 0 and result[0].isdigit():
                                            memUsed = float(result[0])
                                    elif keyW == "Free" :
                                        gpuOne["nvidia_mem_free"] = valW
                                        result = re.findall("(.*)M.*", valW)
                                        if result and len(result) > 0 and result[0].isdigit():
                                            memFree = float(result[0])
                                else :
                                    isFBSession = False
                    if len(gpuOne) > 0 :
                        if memFree != 0 or memUsed != 0 :
                            gpuOne["nvidia_mem_percent"] = float("%0.1f"%((memUsed/(memFree+memUsed))*100))
                        infoList.append(gpuOne)
        self.nvidiaGpuList = infoList
        return infoList

if __name__ == "__main__":
    cc = KACmdTool()
    cc.loadInfoFromLshw()
    # pprint(cc.lshwSystemList)
    # pprint(cc.lshwCpuList)
    # pprint(cc.lshwStorageList)
    # pprint(cc.lshwMemoryList)
    # pprint(cc.lshwDisplayList)
    # pprint(cc.lshwMultimediaList)
    # pprint(cc.lshwNetworkList)
    # pprint(cc.lshwUsbList)
    # pprint(cc.lshwCDRomList)
    # pprint(cc.loadNetworkInfoFromIfconfig())
    # pprint(cc.loadInfoFromHciconfig())
    pprint(cc.loadGPUInfoFromNvidiaSmi())

    # diskList = cc.loadInfoFromHwinfo("--disk")
    # cc.loadDiskInfoFromLsblk()
    # if "list" in diskList and len(diskList["list"]) > 0 :
    #     length = len(diskList["list"])
    #     for i in range(length) :
    #         if "SysFS BusID" in diskList["list"][i] :
    #             for mapInfo in cc.lshwDiskList :
    #                 if "bus info" in mapInfo :
    #                     words = mapInfo["bus info"].split("@")
    #                     if len(words) != 2 :
    #                         continue
    #                     key = words[1].strip()
    #                     key = key.replace(".",":")
    #                     if key != diskList["list"][i]["SysFS BusID"] :
    #                         continue
    #                     diskList["list"][i].update(mapInfo)
    #         if "SysFS Device Link" in diskList["list"][i]:
    #             for mapInfo in cc.lshwStorageList :
    #                 if "bus info" in mapInfo :
    #                     words = mapInfo["bus info"].split("@")
    #                     if len(words) != 2 :
    #                         continue
    #                     key = words[1].strip().lower()
    #                     if key not in diskList["list"][i]["SysFS Device Link"].lower() :
    #                         continue
    #                     diskList["list"][i].update(mapInfo)
    #         for mapInfo in cc.lsblkSmartList :
    #             if "dev_name" in mapInfo and "Device File" in diskList["list"][i] \
    #                 and mapInfo["dev_name"] in diskList["list"][i]["Device File"] :
    #                 diskList["list"][i].update(mapInfo)
    # pprint(diskList)
