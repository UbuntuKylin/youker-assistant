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
#    ComVendor		制造商
#    ComProduct		电脑型号
#    ComVersion		电脑版本
#    ComSerial 		序列号
#    node 			主机名
#    uptime 			持续运行时间
#    system 			操作系统类型
#    platform			操作系统
#    architecture    	系统位数
#    release 			内核版本
#    machine 			内核架构

#CPU：		
#    CpuVersion		处理器版本
#    CpuVendor 		制造商
#    CpuSlot			插槽
#    CpuSerial		序列号
#    CpuCapacity		最大主频
#    CpuSize			当前主频
#    CpuClock		前端总线
#    cpu_cores 		cpu内核数
#    cpu_siblings 		cpu线程数
#    clflush_size 		一级缓存
#    cache_size 		二级缓存

#Board and BIOS：
#    BoaProduct		主板型号
#    BoaVendor		主板产商
#    BoaSerial		序列号
#    BioVendor		BIOS产商
#    BioVersion		BIOS版本
#    BioRelease		发布日期

#Memory：
#MemSlot			插槽号
#MemProduct		内存型号
#MemVendor		制造商
#MemSerial			序列号
#MemSize			内存大小

#Monitor：
#Mon_product		显示器型号
#Mon_vendor		显示器制造商
#Mon_year			生产日期_年
#Mon_week			生产日期_周
#Mon_size			可视面积
#Mon_in			屏幕尺寸
#Mon_maxmode		最大分辨率
#Mon_gamma		伽马值
#Mon_output		当前接口
#Mon_support		支持接口
#Mon_chip			当前显卡


    def get_sys_msg(self):
#        CLIPS_DICT = {}
#        CLIPS_DICT['node'], CLIPS_DICT['uptime'], CLIPS_DICT['system'], CLIPS_DICT['platform'], CLIPS_DICT['architecture'], CLIPS_DICT['release'], CLIPS_DICT['machine'] = self.get_computer()
#        CLIPS_DICT['vendor'], CLIPS_DICT['cpu_cores'], CLIPS_DICT['cpu_siblings'], CLIPS_DICT['clflush_size'], CLIPS_DICT['cache_size'] = self.get_cpuinfo()
#        CLIPS_DICT.update(self.dmi.scan_dmi())
#        CLIPS_DICT.update(self.get_monitor())
#        print 'CLIPS_DICT->'
#        print CLIPS_DICT
        self.Com = {}
        self.Cpu = {}
        self.Boa = {}
        self.Mem = {}
        self.Com,self.Cpu,self.Boa,self.Mem  = self.dmi.scan_dmi()
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
        print self.Com
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
        print self.Cpu
        return self.Cpu

    def get_board(self):
        #Board and BIOS
        print self.Boa
        return self.Boa

    def get_memory(self):
        #Memory Device
        print self.Mem
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
        print ret
        return ret

if __name__ == "__main__":
    cc = DetailInfo()
    cc.get_sys_msg()
    cc.get_computer()
    cc.get_cpu()
    cc.get_board()
    cc.get_memory()
    cc.get_monitor()
