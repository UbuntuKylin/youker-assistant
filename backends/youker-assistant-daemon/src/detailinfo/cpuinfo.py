#!/usr/bin/python
# -*- coding: utf-8 -*-
### BEGIN LICENSE
# Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd
# This program is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License version 3, as published
# by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranties of
# MERCHANTABILITY, SATISFACTORY QUALITY, or FITNESS FOR A PARTICULAR
# PURPOSE.  See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program.  If not, see <http://www.gnu.org/licenses/>.
### END LICENSE

#from __future__ import print_function
#from collections import OrderedDict
import sys
import os
#import glob
import re
import math
#from gi.repository import Gtk, GLib
import platform
#import time
#import stat
import gettext
#import dmi
from gettext import gettext as _
from gettext import ngettext as __
from dmi import Dmi
class DetailInfo:
    def __init__ (self):
        self.dmi = Dmi()

#Computer：			
#   ComVendor		    制造商
#   ComProduct		    电脑型号
#   ComVersion		    电脑版本
#   ComSerial 		    序列号
#   node 			    主机名
#   uptime  			持续运行时间
#   system  			操作系统类型
#   platform    		操作系统
#   architecture    	系统位数
#   release 			内核版本
#   machine 			内核架构

#CPU：		
#   CpuVersion		    处理器版本
#   CpuVendor 		    制造商
#   CpuSlot 			插槽
#   CpuSerial		    序列号
#   CpuCapacity 		最大主频
#   CpuSize 			当前主频
#   CpuClock		    前端总线
#   cpu_cores 		    cpu内核数
#   cpu_siblings 		cpu线程数
#   clflush_size 		一级缓存
#   cache_size   		二级缓存

#Board and BIOS：
#   BoaProduct		    主板型号
#   BoaVendor		    主板产商
#   BoaSerial		    序列号
#   BioVendor		    BIOS产商
#   BioVersion		    BIOS版本
#   BioRelease		    发布日期

#Memory：
#   MemSlot 			插槽号
#   MemProduct		    内存型号
#   MemVendor		    制造商
#   MemSerial		    序列号
#   MemSize 		    内存大小

#Monitor：
#   Mon_product		    显示器型号
#   Mon_vendor		    显示器制造商
#   Mon_year		    生产日期_年
#   Mon_week		    生产日期_周
#   Mon_size		    可视面积
#   Mon_in			    屏幕尺寸
#   Mon_maxmode	        最大分辨率
#   Mon_gamma		    伽马值
#   Mon_output		    当前接口
#   Mon_support		    支持接口
#   Mon_chip		    当前显卡
#   Vga_product         显卡型号
#   Vga_vendor          显卡制造商
#   Vga_businfo         显卡总线地址

#Disk :
#   DiskProduct 		硬盘型号
#   DiskVendor		    硬盘厂商
#   DiskCapacity		硬盘容量
#   DiskName		    设备名称
#   DiskFw			    固件版本
#   DiskSerial		    序列号

#Network :
#   NetProduct          网卡型号
#   NetVendor           制造商
#   NetBusinfo          总线地址
#   NetLogicalname      设备名称
#   NetVersion          固件版本
#   NetSerial           MAC地址
#   NetSize             带宽大小
#   NetCapacity         最大带宽
#   NetWidth            网卡位宽

    def get_sys_msg(self):
        self.Com = {}
        self.Cpu = {}
        self.Boa = {}
        self.Mem = {}
        self.Com,self.Cpu,self.Boa,self.Mem  = self.dmi.scan_dmi()
        h = os.popen("lshw")
        self.hw = h.read()
        h.close()
        return 

    def uptimeinfo(self):
        with open('/proc/uptime') as f:
            for line in f:
                string = line.split('.')[0]
                seconds = int(string)
                minutes = seconds / 60
                upminutes = str(minutes)
        return upminutes

    def get_computer(self):
        #Computer
        with open('/proc/uptime') as f:
            for line in f:
                    string = line.split('.')[0]
                    seconds = int(string)
                    minutes = seconds / 60
                    uptime = str(minutes)
        self.Com['node'], self.Com['uptime'], self.Com['system'], self.Com['platform'],self.Com['architecture'], self.Com['release'], self.Com['machine'] = platform.node(),uptime,platform.system(),platform.platform(),platform.architecture()[0],platform.release(),platform.machine()
        return self.Com

    def get_cpu(self):
        # CPU
        with open('/proc/cpuinfo') as f:
            for line in f:
                if line.strip():
                    if line.rstrip('\n').startswith('vendor_id'):
                         vendor = line.rstrip('\n').split(':')[1]
                    elif line.rstrip('\n').startswith('cpu cores'):
                         cpu_cores = line.rstrip('\n').split(':')[1]
                    elif line.rstrip('\n').startswith('siblings'):
                         cpu_siblings = line.rstrip('\n').split(':')[1]
                    elif line.rstrip('\n').startswith('clflush size'):
                         clflush_size = line.rstrip('\n').split(':')[1]
                         clflush_size = filter(str.isdigit,clflush_size)
                    elif line.rstrip('\n').startswith('cache size'):
                         cache_size = line.rstrip('\n').split(':')[1]
                         cache_size = filter(str.isdigit,cache_size)
        self.Cpu['vendor'], self.Cpu['cpu_cores'], self.Cpu['cpu_siblings'], self.Cpu['clflush_size'], self.Cpu['cache_size'] = vendor,cpu_cores,cpu_siblings,clflush_size,cache_size
        return self.Cpu

    def get_board(self):
        #Board and BIOS
        return self.Boa

    def get_memory(self):
        #Memory Device
        return self.Mem

    def get_monitor(self):
        #Monitor
        ret = {}
        with open('/var/log/Xorg.0.log','r') as fp:
    	    info = fp.read()
            tmp = re.findall('Monitor name: \s*(\w*)\s*(\w*)', info)
            if tmp:
                if tmp[0][1]:
                    ret["Mon_vendor"] = tmp[0][0]
                    ret["Mon_product"] = tmp[0][0] + " " + tmp[0][1]
                else:ret["Mon_product"] = tmp[0][0]
        
            tmp = re.findall("Manufacturer:\s*(\w*)\s*Model:\s*(\w*)", info)
            if tmp:
                if not ret.get("product"):
                    ret["Mon_product"] = tmp[0][0] + " " + tmp[0][1]
                if not ret.get("vendor"):
                    ret["Mon_vendor"] = tmp[0][0]

	    tmp = re.findall("Year:\s*(\w*)\s*Week:\s*(\w*)", info)
	    if tmp:
	        ret["Mon_year"] = tmp[0][0]
	        ret["Mon_week"] = tmp[0][1]

	    #tmp = re.findall("Max Image Size \[(\w*)\]: horiz.: (\w*)\s*vert.: (\w*)", info)
            tmp = re.findall("Image Size: \s*(\w*) x (\w*)", info)
	    if tmp:
                x = float(tmp[0][0])/10
                y = float(tmp[0][1])/10
                d = math.sqrt(x**2 + y**2)/2.54

	        ret["Mon_size"] = str(x) + "cm" + " x " + str(y) + "cm"
                ret["Mon_in"] = "%.1f" %d

	    tmp = re.findall("Gamma: (\S*)", info)
	    if tmp:
	        ret["Mon_gamma"] = tmp[0]

	    h = re.findall("h_active: (\d*)", info)
	    v = re.findall("v_active: (\d*)", info)
	    if h and v:
	        ret["Mon_maxmode"] = h[0] + "x" + v[0]

	    tmp = re.findall("EDID for output (.*)", info)
	    if tmp:
	        ret["Mon_support"] = str(tmp)

	    tmp = re.findall("Output (.*).* connected", info)
	    if tmp:
	        ret["Mon_output"] = tmp[0]

	    tmp = re.findall("Integrated Graphics Chipset: (.*)", info)
	    if tmp:
	        ret["Mon_chip"] = tmp[0]

            tmp = re.findall("Chipset: \"(.*)\"", info)
            if tmp:
                if not ret.get("chip"):
                    ret["Mon_chip"] = tmp[0]
        vga = self.hw[self.hw.index('*-display\n')+len('*-display\n'):]
        vga = vga[:vga.index('*-')-1]
        if vga :
            tmp = re.findall("product:(.*)",vga)
            if tmp :
                ret['Vga_product'] = tmp[0]
            tmp = re.findall("vendor:(.*)",vga)
            if tmp :
                ret['Vga_vendor'] = tmp[0]
            tmp = re.findall("bus info:(.*)",vga)
            if tmp :
                ret['Vga_businfo'] = tmp[0]
            
        return ret

    def get_disk(self):
        dis={}
        disknum = 0
        disk_manufacturers = [
        "^ST.+", "Seagate",
        "^D...-.+", "IBM",
        "^IBM.+", "IBM",
        "^HITACHI.+", "Hitachi",
        "^IC.+", "Hitachi",
        "^HTS.+", "Hitachi",
        "^FUJITSU.+", "Fujitsu",
        "^MP.+", "Fujitsu",
        "^TOSHIBA.+", "Toshiba",
        "^MK.+", "Toshiba",
        "^MAXTOR.+", "Maxtor",
        "^Pioneer.+", "Pioneer",
        "^PHILIPS.+", "Philips",
        "^QUANTUM.+", "Quantum",
        "FIREBALL.+", "Quantum",
        "^WDC.+", "Western Digital",
        "WD.+", "Western Digital",
        ]
        DiskProduct,DiskVendor,DiskCapacity,DiskName,DiskFw,DiskSerial = '','','','','',''
        line = os.popen("ls /dev/sd?").read()
	line += os.popen("ls /dev/hd?").read()
        if line :
            line = line.split('\n')
            for k in line :
                if k :
                    disknum  += 1
                    strin = os.popen("hdparm -i %s" % k).read()
                    if DiskName :
                        DiskName += '   /   ' + k
                    else :
                        DiskName = k
                    tmp = re.findall("Model=(.*), F",strin)
                    if tmp:
                        if DiskProduct :
                            DiskProduct += '  /  '+tmp[0]
                        else :
                            DiskProduct = tmp[0]
                        i = 0
                        while i < len(disk_manufacturers):
                            ven = re.compile(disk_manufacturers[i],re.I)
                            tm = ven.findall(tmp[0])
                            if tm :
                                if DiskVendor :
                                    DiskVendor += '  /  ' + disk_manufacturers[i+1]
                                else :
                                    DiskVendor += disk_manufacturers[i+1]
                                i = len(disk_manufacturers)
                            i += 2
                    tmp = re.findall("FwRev=(.*), ",strin)
                    if tmp :
                        if DiskFw :
                            DiskFw += '  /  ' +tmp[0]
                        else :
                            DiskFw = tmp[0]
                    tmp = re.findall("SerialNo=(.*)",strin)
                    if tmp :
                        if DiskSerial :
                            DiskSerial += '  /  ' +tmp[0]
                        else :
                            DiskSerial = tmp[0]
                    d = os.popen("fdisk -l %s" % k).read()
                    tmp = re.findall("%s: (.*)," % k,d)
                    if tmp:
                        if DiskCapacity :
                            DiskCapacity += '  /  ' +tmp[0]
                        else :
                            DiskCapacity = tmp[0]
        dis['DiskNum'],dis['DiskProduct'],dis['DiskVendor'],dis['DiskCapacity'],dis['DiskName'],dis['DiskFw'],dis['DiskSerial'] = disknum,DiskProduct,DiskVendor,DiskCapacity,DiskName,DiskFw,DiskSerial
        return dis

    def get_network(self):
        net = {}
        NetProduct,NetVendor,NetBusinfo,NetLogicalname,NetVersion,NetSerial,NetSize,NetCapacity,NetWidth = '','','','','','','','',''
        network = self.hw[self.hw.index('*-network\n')+len('*-network\n'):]
        network = network[:network.index('*-')-1]
        if network :
            tmp = re.findall("product:(.*)",network)
            if tmp :
                NetProduct = tmp[0]
            tmp = re.findall("vendor:(.*)",network)
            if tmp :
                NetVendor = tmp[0]
            tmp = re.findall("bus info:(.*)",network)
            if tmp :
                NetBusinfo = tmp[0]
            tmp = re.findall("logical name:(.*)",network)
            if tmp :
                NetLogicalname = tmp[0]
            tmp = re.findall("version:(.*)",network)
            if tmp :
                NetVersion = tmp[0]
            tmp = re.findall("serial:(.*)",network)
            if tmp :
                NetSerial = tmp[0]
            tmp = re.findall("size:(.*)",network)
            if tmp :
                NetSize = tmp[0]
            tmp = re.findall("capacity:(.*)",network)
            if tmp :
                NetCapacity = tmp[0]
            tmp = re.findall("width:(.*)",network)
            if tmp :
                NetWidth = tmp[0]
        net['NetProduct'],net['NetVendor'],net['NetBusinfo'],net['NetLogicalname'],net['NetVersion'],net['NetSerial'],net['NetSize'],net['NetCapacity'],net['NetWidth'] = NetProduct,NetVendor,NetBusinfo,NetLogicalname,NetVersion,NetSerial,NetSize,NetCapacity,NetWidth
        return net

if __name__ == "__main__":
    cc = DetailInfo()
    cc.get_sys_msg()
    cc.get_computer()
    cc.get_cpu()
    cc.get_board()
    cc.get_memory()
    cc.get_monitor()
    cc.get_disk()
    cc.get_network()
