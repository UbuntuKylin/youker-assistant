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
import math
import glob

import json
import subprocess

from pprint import pprint

from kajsondef import *
from kathread import *
from utils import *

subsystem_id = "LANG=en lspci -d 0731:7200 -v | sed -n '/Subsystem:/p' | awk -F: '{ print $NF }'"
subsystem_id_old = "lspci -d 0731:7200 | awk -F: '{ print $NF }'"        #兼容旧驱动
subsystem_id_re = re.compile(r'Subsystem:(.*?\d{3,5})')
subsystem_id_re_old = re.compile(r'.*')

def get_interface(com, pci_str):
    "输入想要的命令，并获取想要内容的函数,第一个参数是命令，第二个参数是正则表达式"
    res = subprocess.Popen(com, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, bufsize=10)
    inter1 = res.stdout.read()
    inter = inter1.decode('utf-8')
    result = inter
    return result

class KAGraphicsCardInfo() :

    def __init__(self, cmdtool):
        self.cmdTool = cmdtool
        pass

    def get_display_hw990(self):
        displayInfo = {}
        wayland_sock = glob.glob('/run/user/*/wayland-0')[0]
        xdg_runtime_dir = wayland_sock[:-10] # /run/user/1000
        gpuinfo_env = {'XDG_RUNTIME_DIR' : xdg_runtime_dir}
        process = subprocess.run('gpuinfo', env=gpuinfo_env, capture_output=True)
        output = process.stdout.decode()
        ret = process.returncode
        if ret == 1: ## ???
            lines = output.strip().split('\n')
            for line in lines:
                if line.find(':') > 0:
                    if line.find('GPU vendor') >= 0: # GPU vendor: ARM
                        displayInfo[GSI_MANUFACTURER] = line.split(':')[1].strip()
                    elif line.find('GPU type') >= 0: # GPU type: Mali-G76
                        displayInfo[GSI_NAME] = line.split(':')[1].strip()
                    elif "GDDR capacity" in line:
                        displayInfo[GSI_GDDRCAPACITY] = line.split(':')[1].strip()
                    elif "EGL version" in line:
                        displayInfo[GSI_EGLVERSION] = line.split(':')[1].strip()
                    elif "EGL client APIs" in line:
                        displayInfo[GSI_EGLAPIS] = line.split(':')[1].strip()
                    elif "GL version" in line:
                        displayInfo[GSI_GLVERSION] = line.split(':')[1].strip()
                    elif "GLSL version" in line:
                        displayInfo[GSI_GLSLVERSION] = line.split(':')[1].strip()
                    else:
                        pass
                else: # integrated graphics controller
                    displayInfo[GSI_DESC] = line
        return displayInfo

    def getGraphicsCardInfo(self) :
        summary = {"list":[]}

        self.cmdTool.loadGPUInfoFromDmesg(False)
        self.cmdTool.loadInfoFromLshw(False)
        self.cmdTool.loadGPUInfoFromNvidiaSmi(False)
        graphicsCardList = self.cmdTool.lshwDisplayList
        cardList = self.cmdTool.loadInfoFromHwinfo("--display")["list"]
        length = len(graphicsCardList)
        for i in range(length) :
            if "bus info" in graphicsCardList[i] :
                words = graphicsCardList[i]["bus info"].split("@")
                if len(words) != 2 :
                    continue
                key = words[1].strip()
                #key = key.replace(".","" in mapInfo 
                for mapInfo in cardList :
                    if "SysFS BusID" in mapInfo :
                        if key != mapInfo["SysFS BusID"] :
                            continue
                        graphicsCardList[i].update(mapInfo)
                result = key.split(":", 1)
                if result and len(result) == 2 :
                    key = result[1]
                    for mapInfo in self.cmdTool.nvidiaGpuList :
                        if "nvidia_id" in mapInfo :
                            if key != mapInfo["nvidia_id"] :
                                continue
                            graphicsCardList[i].update(mapInfo)
            if len(self.cmdTool.dmesgGPUList) > 0 :
                graphicsCardList[i].update(self.cmdTool.dmesgGPUList[0])

        index = 0
        for mapInfo in graphicsCardList :
            if len(mapInfo) > 0 :
                pciAddr = ""
                summary["list"].append({})
                isJJM = False
                ##名称
                if "product" in mapInfo :
                    summary["list"][index][GSI_NAME] = mapInfo["product"]

                ##制造商
                if "Vendor" in mapInfo :
                    cdVendor = mapInfo["Vendor"].split("\"")
                    if len(cdVendor) > 1 :
                        summary["list"][index][GSI_MANUFACTURER] = cdVendor[1]
                    else :
                        summary["list"][index][GSI_MANUFACTURER] = mapInfo["Vendor"]
                if "SubVendor" in mapInfo :
                    cdVendor = mapInfo["SubVendor"].split("\"")
                    if len(cdVendor) > 1 :
                        summary["list"][index][GSI_MANUFACTURER] = cdVendor[1]
                    else :
                        summary["list"][index][GSI_MANUFACTURER] = mapInfo["SubVendor"]
                if "vendor" in mapInfo :
                    summary["list"][index][GSI_MANUFACTURER] = mapInfo["vendor"]

                    # JJW显卡的特殊处理
                    tmpVendor = mapInfo["vendor"]
                    if tmpVendor.find("JJM") != -1:
                        isJJM = True
                        tmpResult = get_interface(subsystem_id, subsystem_id_re)
                        summary["list"][index][GSI_NAME] = tmpResult.strip()
                        if not tmpResult:
                            summary["list"][index][GSI_NAME] = get_interface(subsystem_id_old, subsystem_id_re_old).strip()


                ##类型
                if "description" in mapInfo :
                    summary["list"][index][GSI_DESC] = mapInfo["description"]

                ##版本
                if "version" in mapInfo :
                    summary["list"][index][GSI_VERSION] = mapInfo["version"]

                ##总线信息
                if "bus info" in mapInfo :
                    summary["list"][index][GSI_DBUSINFO] = mapInfo["bus info"]
                    pciResult = re.findall("pci@(\S+)", mapInfo["bus info"])
                    if pciResult :
                        pciAddr = pciResult[0]

                ##功能
                if "capabilities" in mapInfo :
                    summary["list"][index][GSI_FUNCTION] = mapInfo["capabilities"]

                ##位宽 (不准确，暂时不显示)
                # if "width" in mapInfo :
                #     summary["list"][index][GSI_BITWIDTH] = mapInfo["width"]

                ##物理ID
                if "physical id" in mapInfo :
                    summary["list"][index][GSI_PHYSICS] = mapInfo["physical id"]

                ##时钟频率
                if "clock" in mapInfo :
                    summary["list"][index][GSI_CLOCK] = mapInfo["clock"]

                ##中断
                if "irq" in mapInfo :
                    summary["list"][index][GSI_IRQ] = mapInfo["irq"]

                ##内存
                #if "memory" in mapInfo :
                #    summary["list"][index][GSI_MEMORY] = mapInfo["memory"]

                ##io端口
                if "ioport" in mapInfo :
                    summary["list"][index][GSI_IOPORT] = mapInfo["ioport"]

#               ##驱动
#               if "driver" in mapInfo :
#                   summary["list"][index][GSI_DRIVER] = mapInfo["driver"]

                ##延迟
                if "latency" in mapInfo :
                    summary["list"][index][GSI_DELAY] = mapInfo["latency"]

                ##显存
                if isJJM and os.path.exists("/proc/gpuinfo_0"):
                    args4 = ["cat", "/proc/gpuinfo_0"]
                    pipe4 = subprocess.Popen(args4, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                    output4 = pipe4.stdout.readlines()

                    for line in [ bytes.decode(l.strip(),"utf-8","ignore") for l in output4]:
                        if "Memory Size" not in line:
                            continue
                    
                        results = line.strip().split(":")
                        if len(results) == 2 :
                            temSize = results[1].strip()
                            summary["list"][index][GSI_CAPCITY] = temSize.replace(" ","")
                
                if (GSI_NAME in summary["list"][index] and "X100" in summary["list"][index][GSI_NAME]) or \
                    (GSI_MANUFACTURER in summary["list"][index] and "X100" in summary["list"][index][GSI_MANUFACTURER]):    ## X100
                    args3 = ["lspci", "-n"]
                    pipe3 = subprocess.Popen(args3, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                    output3 = pipe3.stdout.readlines()
                    totalMem = 0
                    for line in [ bytes.decode(l.strip(),"utf-8","ignore") for l in output3]:
                        if "1db7:dc20" not in line and "1db7:dc21" not in line and "1db7:dc22" not in line :
                            continue
                        infoItems = line.split(" ")
                        if len(infoItems) != 3 :
                            continue
                        args4 = ["lspci", "-vs"]
                        args4.append(infoItems[0].strip())
                        pipe4 = subprocess.Popen(args4, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                        output4 = pipe4.stdout.readlines()
                        singleMem = 0
                        for line1 in [ bytes.decode(l.strip(),"utf-8","ignore") for l in output4]:
                                if "Memory" not in line1:
                                    continue
                            
                                results = [ v.strip().strip("\)") for v in line1.split() ]
                                if "prefetchable" in results and len(results) >=6 :
                                    ## Memory at a0000000 (64-bit, prefetchable) [size=256M]
                                    strMem = results[5].strip("[").strip("]").split("=")
                                    if len(strMem) == 2 :
                                        sizeN = re.findall("([0-9]+)M.*",strMem[1])
                                        if sizeN and len(sizeN) > 0 and sizeN[0].isdigit() :
                                            if int(sizeN[0]) > singleMem :
                                                singleMem = int(sizeN[0])
                                        sizeN = re.findall("([0-9]+)G.*",strMem[1])
                                        if sizeN and len(sizeN) > 0 and sizeN[0].isdigit() :
                                            if int(sizeN[0])*1024 > singleMem :
                                                singleMem = int(sizeN[0])*1024
                        totalMem += singleMem
                    if totalMem > 0 :
                        if totalMem > 1024 :
                            summary["list"][index][GSI_CAPCITY] = str(float("%0.1f"%(float(totalMem)/1024)))+"GB"
                        else :
                            summary["list"][index][GSI_CAPCITY] = str(totalMem)+"MB"

                if GSI_CAPCITY not in summary["list"][index] :
                    if "size" in mapInfo and len(mapInfo["size"]) > 0:
                        summary["list"][index][GSI_CAPCITY] = mapInfo["size"]
                    else :
                        if len(pciAddr) > 0 :
                            args3 = ["lspci", "-vs"]
                            args3.append(pciAddr)
                            pipe3 = subprocess.Popen(args3, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                            output3 = pipe3.stdout.readlines()
                            totalMem = 0

                            for line in [ bytes.decode(l.strip(),"utf-8","ignore") for l in output3]:
                                if "Memory" not in line:
                                    continue
                            
                                results = [ v.strip().strip("\)") for v in line.split() ]
                                if "prefetchable" in results and len(results) >=6 :
                                    ## Memory at a0000000 (64-bit, prefetchable) [size=256M]
                                    strMem = results[5].strip("[").strip("]").split("=")
                                    if len(strMem) == 2 :
                                        sizeN = re.findall("([0-9]+)M.*",strMem[1])
                                        if sizeN and len(sizeN) > 0 and sizeN[0].isdigit() :
                                            if int(sizeN[0]) > totalMem :
                                                totalMem = int(sizeN[0])
                                        sizeN = re.findall("([0-9]+)G.*",strMem[1])
                                        if sizeN and len(sizeN) > 0 and sizeN[0].isdigit() :
                                            if int(sizeN[0])*1024 > totalMem :
                                                totalMem = int(sizeN[0])*1024

                            if totalMem > 0 :
                                if totalMem > 1024 :
                                    summary["list"][index][GSI_CAPCITY] = str(float("%0.1f"%(float(totalMem)/1024)))+"GB"
                                else :
                                    summary["list"][index][GSI_CAPCITY] = str(totalMem)+"MB"
                if "nvidia_mem" in mapInfo and len(mapInfo["nvidia_mem"]) > 0 :
                    summary["list"][index][GSI_CAPCITY] = mapInfo["nvidia_mem"]

                #显存类型
                if GSI_CAPCITY in summary["list"][index] and "mem_type" in mapInfo and len(mapInfo["mem_type"]) > 0 :
                    summary["list"][index][GSI_MEMTYPE] = mapInfo["mem_type"]

                #子制造商
                if len(pciAddr) > 0 :
                    args3 = ["lspci", "-vs"]
                    args3.append(pciAddr)
                    pipe3 = subprocess.Popen(args3, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
                    output3 = pipe3.stdout.readlines()
                    subSystemInfo = ""

                    for line in [ bytes.decode(l.strip(),"utf-8","ignore") for l in output3]:
                        if "Subsystem" not in line:
                            continue
                        words = line.split(":")
                        if len(words) == 2 :
                            subSystemInfo = words[1].strip()
                            break
                    if len(subSystemInfo) > 0 :
                        summary["list"][index][GSI_SUBSYSTEM] = subSystemInfo

                ##型号
                if "Model" in mapInfo :
                    summary["list"][index][GSI_MODEL] = mapInfo["Model"].strip("\"")
                    if GSI_NAME in summary["list"][index] :
                        if GSI_MANUFACTURER in summary["list"][index] and \
                            summary["list"][index][GSI_MANUFACTURER] != summary["list"][index][GSI_NAME] :
                            summary["list"][index][GSI_MODEL] = summary["list"][index][GSI_NAME]
                else :
                    if GSI_NAME in summary["list"][index] :
                        summary["list"][index][GSI_MODEL] = summary["list"][index][GSI_NAME]

                ##配置状态
                if "Config Status" in mapInfo :
                    summary["list"][index][GSI_CONFSTATUS] = mapInfo["Config Status"]

                ##驱动
                if "Driver" in mapInfo :
                    summary["list"][index][GSI_DRIVER] = mapInfo["Driver"].strip("\"")

                ##驱动模块
                if "Driver Modules" in mapInfo :
                    summary["list"][index][GSI_DRIVERMODULE] = mapInfo["Driver Modules"]

                ##设备
                if "Device" in mapInfo :
                    summary["list"][index][GSI_DEVICE] = mapInfo["Device"]

                index += 1
        
        if Judgment_HW990() :
            displayList = self.get_display_hw990()
            if len(displayList) > 0 :
                summary["list"].append(displayList)

        return json.dumps(summary)

    #概要信息
    def getOutline(self) :
        outLine = self.getGraphicsCardInfo()
        outLineObj = json.loads(outLine)
        outLine = ""
        if len(outLineObj) > 0 and "list" in outLineObj :
            nIndex = 0
            for info in outLineObj["list"] :
                if GSI_NAME in info and len(info[GSI_NAME]) > 0:
                    if nIndex == 0 :
                        outLine += info[GSI_NAME]
                    else :
                        outLine += " / " + info[GSI_NAME]
                elif MMI_MODEL in info :
                        if nIndex == 0 :
                            outLine += info[MMI_MODEL]
                        else :
                            outLine += " / " + info[MMI_MODEL]
                nIndex = nIndex + 1
        return outLine

if __name__ == "__main__":
    cmdTool = KACmdTool()
    cmdTool.loadInfoFromLshw()
    cc = KAGraphicsCardInfo(cmdTool)
    pprint(cc.getGraphicsCardInfo())
    #pprint(cc.getOutline())
