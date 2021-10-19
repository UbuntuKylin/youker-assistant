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
import copy

from pprint import pprint

from kajsondef import *
from kathread import *

NetAdaptor_Product=         "Product"
NetAdaptor_Manufacturer=    "Vendor"
NetAdaptor_Type=            "Description"
NetAdaptor_Version=         "Version"
NetAdaptor_Businfo=         "Bus Info"
NetAdaptor_Capabilities=    "Capabilities"
NetAdaptor_Driver=          "Driver"
NetAdaptor_Logicalname=     "Logical Name"
NetAdaptor_Serial=          "Serial"
NetAdaptor_IRQ=             "IRQ"
NetAdaptor_Memory=          "Memory"
NetAdaptor_Width=           "Width"
NetAdaptor_Clock=           "Clock"
NetAdaptor_Broadcast=       "Broadcast"
NetAdaptor_Firmware=        "Firmware"
NetAdaptor_IP=              "IP"
NetAdaptor_Link=            "Link"
NetAdaptor_Port=            "Port"
NetAdaptor_Capacity=        "Capacity"
NetAdaptor_Physicalid=      "Physical ID"
NetAdaptor_Size=            "Size"
NetAdaptor_Multicast=       "Multicast"
NetAdaptor_Autonegotiation= "Autonegotiation"
NetAdaptor_Latency=         "Latency"
NetAdaptor_Mask=            "subnet_mask"
NetAdaptor_Txdata=          "send_bytes"
NetAdaptor_Rxdata=          "recv_bytes"
NetAdaptor_Mtu=             "mtu"

class NetworkAdaptor():

    def __init__(self, cmdtool):
        self.cmdTool = cmdtool
        pass

    def getNetworkAdaptorInfo(self):
        summary = {"list":[]}

        self.cmdTool.loadInfoFromLshw(False)
        networkAdaptorList = copy.deepcopy(self.cmdTool.lshwNetworkList)
        for usbNetwork in self.cmdTool.lshwUsbList :
            if "capabilities" in usbNetwork and "Bluetooth".lower() not in usbNetwork["capabilities"].lower() and \
                ("Wireless".lower() in usbNetwork["capabilities"].lower() or "Ethernet".lower() in usbNetwork["capabilities"].lower()) :
                networkAdaptorList.append(usbNetwork)
        adaptorList = self.cmdTool.loadInfoFromHwinfo("--network")["list"]
        ifconfigList = self.cmdTool.loadNetworkInfoFromIfconfig()
        length = len(networkAdaptorList)
        for i in range(length) :
            if "bus info" in networkAdaptorList[i] :
                words = networkAdaptorList[i]["bus info"].split("@")
                if len(words) != 2 :
                    continue
                key = words[1].strip()
                #key = key.replace(".","" in mapInfo 
                for mapInfo in adaptorList :
                    if "SysFS Device Link" in mapInfo :
                        if key not in mapInfo["SysFS Device Link"] :
                            continue
                        networkAdaptorList[i].update(mapInfo)
            if "logical name" in networkAdaptorList[i] :
                for mapInfo in ifconfigList :
                    if "NetName" in mapInfo and mapInfo["NetName"] == networkAdaptorList[i]["logical name"]:
                        networkAdaptorList[i].update(mapInfo)
                        break


        index = 0
        for mapInfo in networkAdaptorList :
            if len(mapInfo) > 0 :
                summary["list"].append({})
                ##名称
                if "product" in mapInfo :
                    summary["list"][index][NetAdaptor_Product] = mapInfo["product"]

                ##制造商
                if "Vendor" in mapInfo :
                    hwVendor = mapInfo["Vendor"].split("\"")
                    if len(hwVendor) > 1 :
                        summary["list"][index][NetAdaptor_Manufacturer] = hwVendor[1]
                    else :
                        summary["list"][index][NetAdaptor_Manufacturer] = mapInfo["Vendor"]
                if "SubVendor" in mapInfo :
                    hwVendor = mapInfo["SubVendor"].split("\"")
                    if len(hwVendor) > 1 :
                        summary["list"][index][NetAdaptor_Manufacturer] = hwVendor[1]
                    else :
                        summary["list"][index][NetAdaptor_Manufacturer] = mapInfo["SubVendor"]
                if "vendor" in mapInfo :
                    summary["list"][index][NetAdaptor_Manufacturer] = mapInfo["vendor"]

                ##类型
                if "description" in mapInfo :
                    summary["list"][index][NetAdaptor_Type] = mapInfo["description"]

                ##版本
                if "version" in mapInfo :
                    summary["list"][index][NetAdaptor_Version] = mapInfo["version"]

                ##物理地址
                if "serial" in mapInfo :
                    summary["list"][index][NetAdaptor_Serial] = mapInfo["serial"]

                ##总线信息
                if "bus info" in mapInfo :
                    summary["list"][index][NetAdaptor_Businfo] = mapInfo["bus info"]

                ##功能
                if "capabilities" in mapInfo :
                    summary["list"][index][NetAdaptor_Capabilities] = mapInfo["capabilities"]

                ##逻辑名称
                if "logical name" in mapInfo :
                    summary["list"][index][NetAdaptor_Logicalname] = mapInfo["logical name"]

                ##速度
                if "size" in mapInfo :
                    summary["list"][index][NetAdaptor_Size] = mapInfo["size"]

                ##位宽
                if "width" in mapInfo :
                    summary["list"][index][NetAdaptor_Width] = mapInfo["width"]

                ##容量
                if "capacity" in mapInfo :
                    summary["list"][index][NetAdaptor_Capacity] = mapInfo["capacity"]

                ##物理ID
                if "physical id" in mapInfo :
                    summary["list"][index][NetAdaptor_Physicalid] = mapInfo["physical id"]

                ##时钟频率
                if "clock" in mapInfo :
                    summary["list"][index][NetAdaptor_Clock] = mapInfo["clock"]

                ##中断
                if "irq" in mapInfo :
                    summary["list"][index][NetAdaptor_IRQ] = mapInfo["irq"]

                ##内存
                if "memory" in mapInfo :
                    summary["list"][index][NetAdaptor_Memory] = mapInfo["memory"]

                ##驱动
                if "driver" in mapInfo :
                    summary["list"][index][NetAdaptor_Driver] = mapInfo["driver"]

                ##自动协商
                if "autonegotiation" in mapInfo :
                    summary["list"][index][NetAdaptor_Autonegotiation] = mapInfo["autonegotiation"]

                ##广播
                if "broadcast" in mapInfo :
                    summary["list"][index][NetAdaptor_Broadcast] = mapInfo["broadcast"]

                ##固件
                if "firmware" in mapInfo :
                    summary["list"][index][NetAdaptor_Firmware] = mapInfo["firmware"]

                ##IP
                if "ip" in mapInfo :
                    summary["list"][index][NetAdaptor_IP] = mapInfo["ip"]

                ##延迟
                if "latency" in mapInfo :
                    summary["list"][index][NetAdaptor_Latency] = mapInfo["latency"]

                ##连接
                if "link" in mapInfo :
                    summary["list"][index][NetAdaptor_Link] = mapInfo["link"]

                ##组播
                if "multicast" in mapInfo :
                    summary["list"][index][NetAdaptor_Multicast] = mapInfo["multicast"]

                ##端口
                if "port" in mapInfo :
                    summary["list"][index][NetAdaptor_Port] = mapInfo["port"]

                ##子网掩码
                if "NetMask" in mapInfo :
                    summary["list"][index][NetAdaptor_Mask] = mapInfo["NetMask"]

                ##发送数据
                if "NetTxData" in mapInfo :
                    summary["list"][index][NetAdaptor_Txdata] = mapInfo["NetTxData"]

                ##接收数据
                if "NetRxData" in mapInfo :
                    summary["list"][index][NetAdaptor_Rxdata] = mapInfo["NetRxData"]

                ##MTU
                if "NetMTU" in mapInfo :
                    summary["list"][index][NetAdaptor_Mtu] = mapInfo["NetMTU"]

                index += 1

        return json.dumps(summary)

    #概要信息
    def getOutline(self) :
        outLine = self.getNetworkAdaptorInfo()
        outLineObj = json.loads(outLine)
        outLine = ""
        if len(outLineObj) > 0 and "list" in outLineObj :
            nIndex = 0
            for info in outLineObj["list"] :
                if NetAdaptor_Product in info and len(info[NetAdaptor_Product]) > 0:
                    if nIndex == 0 :
                        outLine += info[NetAdaptor_Product]
                    else :
                        outLine += " / " + info[NetAdaptor_Product]
                elif NetAdaptor_Type in info :
                    if nIndex == 0 :
                        outLine += info[NetAdaptor_Type]
                    else :
                        outLine += " / " + info[NetAdaptor_Type]
                nIndex = nIndex + 1
        return outLine

if __name__ == "__main__":
    cmdTool = KACmdTool()
    cmdTool.loadInfoFromLshw()
    cc = NetworkAdaptor(cmdTool)
    pprint(cc.getNetworkAdaptorInfo())

