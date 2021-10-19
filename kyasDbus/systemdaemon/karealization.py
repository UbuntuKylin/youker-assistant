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

CPUINFO = "/proc/cpuinfo"

class DetailInfo:

    def __init__(self):
        pass

    def getProcessorInfo(self):

        info = {Pro_Manufacturer: "",
                Pro_Product: "",
                Pro_Architecture: "",
                Pro_Frequency: "",
                Pro_Frequency_Max: "",
                Pro_Threads: "",
                Pro_Family: "",
                Pro_Model: "",
                Pro_Stepping: "",
                Pro_L1dCache: "",
                Pro_L1iCache: "",
                Pro_L2Cache: "",
                Pro_L3Cache: "",
                Pro_Cores: ""}

        pipe = subprocess.Popen('lscpu', env={'LANGUAGE':'en:'}, stdout=subprocess.PIPE)
        output = pipe.stdout.readlines()
        socket = ""
        corePerSocket = ""
        thread = ""

        for l in output:
            line = bytes.decode(l.strip(),"utf-8","ignore")

            ##名称
            if line.startswith("Model name:"):
                info[Pro_Product] = line.split(":", 1)[1].strip() if info[Pro_Product] == "" else ""

            ##架构
            if line.startswith("Architecture:"):
                info[Pro_Architecture] = line.split(":", 1)[1].strip() if info[Pro_Architecture] == "" else ""

            ##最大频率
            if line.startswith("CPU max MHz:"):
                value = line.split(":", 1)[1].strip()
                value = value.split(".")[0]
                if value.isdigit() :
                    info[Pro_Frequency_Max] = str(int(float(value))) + " MHz" if info[Pro_Frequency_Max] == "" else ""

            ##线程数
            if line.startswith("Thread(s) per core:"):
                info[Pro_Threads] = line.split(":", 1)[1].strip() if info[Pro_Threads] == "" else ""

            ##型号
            if line.startswith("Model:"):
                info[Pro_Model] = line.split(":", 1)[1].strip() if info[Pro_Model] == "" else ""

            ##步进
            if line.startswith("Stepping:"):
                info[Pro_Stepping] = line.split(":", 1)[1].strip() if info[Pro_Stepping] == "" else ""

            ##L1 数据缓存
            if line.startswith("L1d cache:"):
                info[Pro_L1dCache] = line.split(":", 1)[1].strip() if info[Pro_L1dCache] == "" else ""

            ##L1 指令缓存
            if line.startswith("L1i cache:"):
                info[Pro_L1iCache] = line.split(":", 1)[1].strip() if info[Pro_L1iCache] == "" else ""

            ##L2 缓存
            if line.startswith("L2 cache:"):
                info[Pro_L2Cache] = line.split(":", 1)[1].strip() if info[Pro_L2Cache] == "" else ""

            ##L3 缓存
            if line.startswith("L3 cache:"):
                info[Pro_L3Cache] = line.split(":", 1)[1].strip() if info[Pro_L3Cache] == "" else ""

            ##L3 缓存
            if line.startswith("Flags:"):
                flagsInfo = line.split(":", 1)[1].strip()
                flagsList = flagsInfo.split(" ")
                validSet = ["MMX", "SSE", "SSE2", "SSE3", "3D Now", "SSE4", "SSSE3", "SSE4_1", "SSE4_2", "AMD64", "EM64T"]
                extraInstructSet = []
                for flag in flagsList :
                    for valid in validSet:
                        if valid.lower() == flag.lower() :
                            extraInstructSet.append(valid)
                if len(extraInstructSet) > 0 :
                    info[Pro_Ext_Instruction_Set] = str(extraInstructSet).strip("[").strip("]").replace(",", "").replace("'","")

            ##核数
            if line.startswith("CPU(s):"):
                info[Pro_Cores] = line.split(":", 1)[1].strip() if info[Pro_Cores] == "" else ""

            ##核数
            if line.startswith("Socket(s):"):
                socket = line.split(":", 1)[1].strip()
            if line.startswith("Core(s) per socket:"):
                corePerSocket = line.split(":", 1)[1].strip()
            if line.startswith("Thread(s) per core:"):
                thread = line.split(":", 1)[1].strip()

        if socket != "" and corePerSocket != "" and thread != "" and info[Pro_Cores] != "" and \
            socket.isdigit() and corePerSocket.isdigit() and thread.isdigit() and info[Pro_Cores].isdigit() :
            if(int(info[Pro_Cores]) == int(socket)*int(corePerSocket)*int(thread)):
                info[Pro_Cores_Online] = info[Pro_Cores] = str(int(socket)*int(corePerSocket))
            else:
                info[Pro_Cores_Online] = info[Pro_Cores] = str(int(info[Pro_Cores]))
        
        args = ["dmidecode", "-t", "processor"]
        pipe2 = subprocess.Popen(args, stdout=subprocess.PIPE)
        output2 = pipe2.stdout.readlines()

        for l in output2:
            line = bytes.decode(l.strip(),"utf-8","ignore")

            ##制造商
            if line.startswith("Manufacturer:"):
                info[Pro_Manufacturer] = line.split(":", 1)[1].strip() if info[Pro_Manufacturer] == "" else ""

            ##家族
            if line.startswith("Family:"):
                info[Pro_Family] = line.split(":", 1)[1].strip() if info[Pro_Family] == "" else ""

        return json.dumps(info)

    #旧接口 获取cpu信息
    def get_cpuMHZ_from_cpuinfo(self):
        with open(CPUINFO,'r') as fb:
            for line in fb.readlines():
                if line.startswith("cpu MHz") or line.startswith("CPU MHz"):
                    return line.split(":")[1].split(".")[0].strip() + " MHz"

    # 20200616 trans by hebing
    def get_cpu(self):
        cpuType = ''
        Cpu = {}
        tmpCpu = {}
        pipe = subprocess.Popen('lscpu', env={'LANGUAGE':'en:'}, stdout=subprocess.PIPE)
        output = pipe.stdout.readlines()
        pprint(output)

        for line in output:
            value = bytes.decode(line,"utf-8","ignore").split(":")
            tmpCpu.setdefault(value[0], value[1].strip())
        
        socket = tmpCpu.get("Socket(s)", "")
        i = tmpCpu.get("Core(s) per socket", "")
        thread = tmpCpu.get("Thread(s) per core", "")
        core = tmpCpu.get("CPU(s)", "")
        if core.isdigit() and socket.isdigit() and i.isdigit() and thread.isdigit() :
            if(int(core) == int(socket)*int(i)*int(thread)):
                Cpu['cpu_cores_online'] = Cpu['cpu_cores'] = str(int(socket)*int(i))
            else:
                Cpu['cpu_cores_online'] = Cpu['cpu_cores'] = str(int(core))
             
    
        Cpu['CpuCapacity'] = tmpCpu.get("CPU max MHz", "").split(".")[0] + "MHz" if tmpCpu.get("CPU max MHz", "") else ""
        Cpu['CpuVersion'] = tmpCpu.get("Model name", "")
        Cpu['CpuVendor'] = tmpCpu.get("Model name", "phytium")#kobe 2020
        cpuType = Cpu['CpuVendor'].lower()
        if cpuType.find('phytium') >= 0:#Phytium
            Cpu['CpuVendor'] = 'Phytium'
        elif cpuType.find('huawei') >= 0:#KunPeng
            Cpu['CpuVendor'] = 'Huawei'
        elif cpuType.find('hygon') >= 0:#Hygon
            Cpu['CpuVendor'] = 'Hygon'
        elif cpuType.find('zhaoxin') >= 0:#ZHAOXIN
            Cpu['CpuVendor'] = 'Zhaoxin'
        elif cpuType.find('loongson') >= 0:#Loongson
            Cpu['CpuVendor'] = 'Loongson'
            if Cpu['CpuCapacity'] == '':
                Cpu['CpuCapacity'] = self.get_cpuMHZ_from_cpuinfo()
        elif cpuType.find('intel') >= 0:#Loongson
            Cpu['CpuVendor'] = 'Intel'
        elif cpuType.find('D2000') >= 0:
            Cpu['CpuVendor'] = 'Phytium'
        #Cpu['CpuSlot'] = tmpCpu.get("Socket(s)", "")
        Cpu['cpu_siblings'] = tmpCpu.get("Thread(s) per core", "")
        #Cpu['cpu_cores_online'] = os.sysconf("SC_NPROCESSORS_ONLN")

        return Cpu

    #概要信息
    def getOutline(self) :
        outLine = self.getProcessorInfo()
        outLineObj = json.loads(outLine)
        outLine = ""
        procCores = "1"
        procThreadsPerCore = "1"
        if Pro_Product in outLineObj and len(outLineObj[Pro_Product]) > 0:
            outLine += outLineObj[Pro_Product]
        if Pro_Cores in outLineObj and len(outLineObj[Pro_Cores]) > 0:
            procCores = outLineObj[Pro_Cores]
        if Pro_Threads in outLineObj and len(outLineObj[Pro_Threads]) > 0:
            procThreadsPerCore = outLineObj[Pro_Threads]
        outLine += "("+procCores+"x"+procThreadsPerCore+")"
        return outLine

if __name__ == "__main__":
    cc = DetailInfo()
    pprint(cc.getProcessorInfo())
    #pprint(cc.getOutline())

