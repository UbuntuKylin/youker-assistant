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
import glob

AudioAdaptor_Product=         "Product"
AudioAdaptor_Manufacturer=    "Vendor"
AudioAdaptor_Model=           "Model"
AudioAdaptor_Type=            "Description"
AudioAdaptor_Version=         "Version"
AudioAdaptor_Businfo=         "Bus Info"
AudioAdaptor_Capabilities=    "Capabilities"
AudioAdaptor_IRQ=             "IRQ"
AudioAdaptor_Memory=          "Memory"
AudioAdaptor_Width=           "Width"
AudioAdaptor_Clock=           "Clock"
AudioAdaptor_SubVendor=       "SubVendor"
AudioAdaptor_SubDevice=       "SubDevice"
AudioAdaptor_Physicalid=      "Physical ID"
AudioAdaptor_Latency=         "Latency"
AudioAdaptor_ConfigStatus=    "Config Status"
AudioAdaptor_Driver=          "Driver"
AudioAdaptor_DriverMod=       "Driver Modules"
AudioAdaptor_DriverStatus=    "Driver Status"
AudioAdaptor_DriverActiveCMD= "Driver Activation Cmd"


class AudioAdaptor():

    def __init__(self, cmdtool):
        self.cmdTool = cmdtool
        pass

    def getAudioAdaptorInfo(self):
        summary = {"list":[]}
        index = 0
        self.cmdTool.loadInfoFromLshw(False)
        audioAdaptorList = self.cmdTool.lshwMultimediaList
        adaptorList = self.cmdTool.loadInfoFromHwinfo("--sound")["list"]
        length = len(audioAdaptorList)
        for i in range(length) :
            if "bus info" in audioAdaptorList[i] :
                words = audioAdaptorList[i]["bus info"].split("@")
                if len(words) != 2 :
                    continue
                key = words[1].strip()
                isDone = False
                #key = key.replace(".",":")
                for mapInfo in adaptorList :
                    if "SysFS BusID" in mapInfo :
                        if key != mapInfo["SysFS BusID"] :
                            continue
                        audioAdaptorList[i].update(mapInfo)
                        isDone = True
                if not isDone and ":" in key :
                    key = key.replace(":", "-")
                    for mapInfo in adaptorList :
                        if "SysFS BusID" in mapInfo :
                            sysBusIds = mapInfo["SysFS BusID"].split(":")
                            if key not in sysBusIds :
                                continue
                            audioAdaptorList[i].update(mapInfo)
                            isDone = True


        for mapInfo in audioAdaptorList :
            if len(mapInfo) > 0 :
                summary["list"].append({})

                ##名称
                if "product" in mapInfo :
                    summary["list"][index][AudioAdaptor_Product] = mapInfo["product"]

                ##制造商
                if "Vendor" in mapInfo :
                    devVendor = mapInfo["Vendor"].split("\"")
                    if len(devVendor) > 1 :
                        summary["list"][index][AudioAdaptor_Manufacturer] = devVendor[1]
                    else :
                        summary["list"][index][AudioAdaptor_Manufacturer] = mapInfo["Vendor"]
                if "SubVendor" in mapInfo :
                    devVendor = mapInfo["SubVendor"].split("\"")
                    if len(devVendor) > 1 :
                        summary["list"][index][AudioAdaptor_Manufacturer] = devVendor[1]
                    else :
                        summary["list"][index][AudioAdaptor_Manufacturer] = mapInfo["SubVendor"]
                if "vendor" in mapInfo :
                    summary["list"][index][AudioAdaptor_Manufacturer] = mapInfo["vendor"]

                ##类型
                if "description" in mapInfo:
                    summary["list"][index][AudioAdaptor_Type] = mapInfo["description"]

                ##版本
                if "version" in mapInfo:
                    summary["list"][index][AudioAdaptor_Version] = mapInfo["version"]

                ##总线信息
                if "bus info" in mapInfo:
                    summary["list"][index][AudioAdaptor_Businfo] = mapInfo["bus info"]

                ##功能
                if "capabilities" in mapInfo:
                    summary["list"][index][AudioAdaptor_Capabilities] = mapInfo["capabilities"]

                ##位宽
                if "width" in mapInfo:
                    summary["list"][index][AudioAdaptor_Width] = mapInfo["width"]

                ##物理ID
                if "physical id" in mapInfo:
                    summary["list"][index][AudioAdaptor_Physicalid] = mapInfo["physical id"]

                ##时钟频率
                if "clock" in mapInfo:
                    summary["list"][index][AudioAdaptor_Clock] = mapInfo["clock"]

                 ##中断
                if "irq" in mapInfo :
                    summary["list"][index][AudioAdaptor_IRQ] = mapInfo["irq"]

                ##内存
                if "memory" in mapInfo :
                    summary["list"][index][AudioAdaptor_Memory] = mapInfo["memory"]
                
                ##驱动
                if "driver" in mapInfo :
                    summary["list"][index][AudioAdaptor_Driver] = mapInfo["driver"]

                ##延迟
                if "latency" in mapInfo :
                    summary["list"][index][AudioAdaptor_Latency] = mapInfo["latency"]

                ##型号
                if "Model" in mapInfo :
                    summary["list"][index][AudioAdaptor_Model] = mapInfo["Model"].strip("\"")

                ##子制造商
                if "SubVendor" in mapInfo :
                    summary["list"][index][AudioAdaptor_SubVendor] = mapInfo["SubVendor"]

                ##子设备
                if "SubDevice" in mapInfo :
                    summary["list"][index][AudioAdaptor_SubDevice] = mapInfo["SubDevice"]

                ##配置状态
                if "Config Status" in mapInfo :
                    summary["list"][index][AudioAdaptor_ConfigStatus] = mapInfo["Config Status"]

                ##驱动
                if "Driver" in mapInfo :
                    summary["list"][index][AudioAdaptor_Driver] = mapInfo["Driver"].strip("\"")

                ##驱动模块
                if "Driver Modules" in mapInfo :
                    summary["list"][index][AudioAdaptor_DriverMod] = mapInfo["Driver Modules"]

                ##驱动状态
                if "Driver Status" in mapInfo :
                    summary["list"][index][AudioAdaptor_DriverStatus] = mapInfo["Driver Status"]

                ##驱动激活命令
                if "Driver Activation Cmd" in mapInfo :
                    summary["list"][index][AudioAdaptor_DriverActiveCMD] = mapInfo["Driver Activation Cmd"]

                index += 1

        if len(summary["list"]) == 0 :
            # non-pci bus
            sound_card_paths = glob.glob('/sys/class/sound/card*')
            for sound_card_path in sound_card_paths:
                card_num = sound_card_path.split('/')[-1][4:]
                driver_path = sound_card_path + '/device/driver'
                driver_realpath_split = os.path.realpath(driver_path).split('/')
                # /sys/bus/platform/drivers/hisi-dp-audio
                bus_type = driver_realpath_split[3]
                if bus_type == 'platform':# soc devices
                    audioAdaptor = {}
                    audioAdaptor[AudioAdaptor_Businfo] = bus_type
                    vendor = ''
                    product = 'Soc Integrated'
                    compatible_path = sound_card_path + "/device/of_node/compatible"
                    codec_path = "/proc/asound/card%s/codec#0" % card_num
                    if os.path.exists(codec_path):
                        #Name:da_combine_v5
                        #Vendor:HISILICON
                        #Model:da_combine_v5
                        with open(codec_path, 'r') as f:
                            line = f.readline()
                            while line:
                                if line.startswith('Name:'):
                                    product = line.strip().split(':', 1)[-1]
                                elif line.startswith('Vendor:'):
                                    vendor = line.strip().split(':', 1)[-1]
                                line = f.readline()
                    elif os.path.exists(compatible_path):
                        # hisilicon,hisi-dp-audio-machine\x00
                        with open(compatible_path, 'r') as f:
                            compatible_content_split = f.read().split(',')
                            vendor = compatible_content_split[0]
                            product = compatible_content_split[1].strip()
                    flag_9a0 = Judgment_HW9A0()
                    if flag_9a0 and "da_combine_v5" in product:
                        product = "Hi6405"
                    audioAdaptor[AudioAdaptor_Product] = mystrip(product)
                    if len(vendor) > 0 :
                        audioAdaptor[AudioAdaptor_Manufacturer] = get_url('', mystrip(vendor))
                    driver_name = driver_realpath_split[-1]
                    audioAdaptor[AudioAdaptor_Driver] = driver_name
                    summary["list"].append(audioAdaptor)
                else:
                    # pci bus devices have been parsed
                    # other bus device is unsupported
                    pass

        return json.dumps(summary)

    #概要信息
    def getOutline(self) :
        outLine = self.getAudioAdaptorInfo()
        outLineObj = json.loads(outLine)
        outLine = ""
        if len(outLineObj) > 0 and "list" in outLineObj :
            nIndex = 0
            for info in outLineObj["list"] :
                if AudioAdaptor_Product in info and len(info[AudioAdaptor_Product]) > 0:
                    if nIndex == 0 :
                        outLine += info[AudioAdaptor_Product]
                    else :
                        outLine += " / " + info[AudioAdaptor_Product]
                elif AudioAdaptor_Model in info :
                    if nIndex == 0 :
                        outLine += info[AudioAdaptor_Model]
                    else :
                        outLine += " / " + info[AudioAdaptor_Model]
                nIndex = nIndex + 1
        return outLine

if __name__ == "__main__":
    cmdTool = KACmdTool()
    cmdTool.loadInfoFromLshw()
    cc = AudioAdaptor(cmdTool)
    pprint(cc.getAudioAdaptorInfo())

