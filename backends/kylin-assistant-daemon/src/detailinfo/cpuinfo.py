#!/usr/bin/python3
# -*- coding: utf-8 -*-
### BEGIN LICENSE
# Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd
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


import sys
import os
import re
import uuid
import socket
import fcntl
import struct
import math
import binascii
import platform
import subprocess
import random
from pprint import pprint

from gi.repository import GLib#20161228
import locale
import gettext
##from gettext import gettext as _
##from gettext import ngettext as __
#locale.setlocale(locale.LC_ALL, "")
#gettext.bindtextdomain("kylin-assistant", "/usr/share/locale")
#gettext.textdomain("kylin-assistant")
#_ = gettext.gettext

CPU_CURRENT_FREQ = ""
CPU_MAX_FREQ = "/sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq"
MEMORY = "/sys/phytium1500a_info"

KILOBYTE_FACTOR = 1000.0
MEGABYTE_FACTOR = (1000.0 * 1000.0)
GIGABYTE_FACTOR = (1000.0 * 1000.0 * 1000.0)
TERABYTE_FACTOR = (1000.0 * 1000.0 * 1000.0 * 1000.0)

def get_human_read_capacity_size(size):
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
    str_list = [str(int(round(displayed_size))), unit]
    size_str = " ".join(str_list)
    return size_str

def get_interface_mac(interface):
    DEVICE_NAME_LEN = 15
    MAC_START = 18
    MAC_END = 24
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        info = fcntl.ioctl(s.fileno(), 0x8927, struct.pack('256s', interface[:DEVICE_NAME_LEN]))
        return ''.join(['%02x:' % ord(char) for char in info[MAC_START:MAC_END]])[:-1]
    except Exception as e:
        return "unknown"

def get_interface_ip(interface):
    DEVICE_NAME_LEN = 15
    IP_START = 20
    IP_END = 24
    if interface == "unknown":
        return "unknown"
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        info = fcntl.ioctl(s.fileno(), 0x8915, struct.pack('256s', interface[:DEVICE_NAME_LEN]))
        return ''.join(['%s.' % ord(char) for char in info[IP_START:IP_END]])[:-1]
    except Exception as e:
        return "unknown"
    #try:
    #    sk = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    #    ip = socket.inet_ntoa(fcntl.ioctl(
    #        sk.fileno(),
    #        0x8915, # SIOCGIFADDR
    #        struct.pack('256s', netItem[:15])
    #    )[20:24])
    #    return ip
    #except Exception as e:
    #    return "unknown"

def get_interface_driver(interface):
    if interface == "unknown":
        return "unknown"
    cmd = "ethtool -i %s |grep 'driver:'" % interface
    fp = os.popen(cmd)
    msg = fp.read().strip('\n')
    fp.close()
    if msg:
        tmp = re.findall('driver: (.*)', msg)
        if tmp[0] in [None, '']:
            return "unknown"
        else:
            return tmp[0]
    else:
        return "unknown"

class DetailInfo:
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
#   Memnum              内存条个数
#   MemInfo             内存条信息
#   MemWidth            数据宽度
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
#   Vga_num             显卡数
#   Vga_product         显卡型号
#   Vga_vendor          显卡产商
#   Vga_businfo         显卡总线地址
#   Vga_Drive           显卡驱动

#Disk :
#   disknum             硬盘个数
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
#   NetSerial           MAC地址
#   NetCapacity         最大带宽
#   NetIp               IP地址
#   NetLink             连接状态
#   NetDrive            网卡驱动
#   WlanProduct         无线网卡型号
#   WlanVendor          无线制造商
#   WlanBusinfo         总线地址
#   WlanLogicalname     设备名称
#   WlanSerial          MAC地址
#   WlanIp              无线IP地址
#   WlanDrive           无线网卡驱动

#multimedia :
#   MulNum              多媒体个数
#   MulProduct          产品型号
#   MulVendor           制造商
#   MulBusinfo          总线地址
#   MulDrive            驱动

#dvd :
#   Dvdnum              光驱个数
#   DvdProduct   		光驱型号
#   DvdVendor		    制造商
#   DvdName	    	    设备名称
#   DvdFw			    固件版本
#   DvdSerial		    序列号 

#usb :
#   Usbnum              usb使用个数
#   UsbVendor           制造商
#   UsbProduct          产品型号
#   UsbBusinfo          总线地址
#   UsbID               设备ID
#   bcdUsb              固件版本
#   UsbMaxpower         最大电流

    def __init__(self):
        self.lshwstr = ''
        self.machine = platform.machine()
        self.osname = self.read_os_name()
#        print platform.platform()
#        print platform.version()
#        print platform.architecture()
#        print platform.node()
#        print platform.processor()
#        print platform.uname()

    def ctoascii(self,buf):
        ch = bytes(buf.encode('utf-8'))
        asci = binascii.b2a_hex(ch)
        asci = int(asci,16)
        return asci

    def strip(self, s):
        if(len(s) == 0):
            return s
        while len(s) > 0 and self.ctoascii(s[0]) <= 32:
            s = s[1: ]
        k = len(s)
        while len(s) > 0 and self.ctoascii(s[k-1]) <= 32:
            s = s[ :k-1]
            k = len(s)
        i = 0
        while i < len(s):
            if self.ctoascii(s[i]) < 32:
                s = s[ :i] + s[i+1: ]
                i -= 1
            i += 1
        return s

    def uptimeinfo(self):
        with open('/proc/uptime') as f:
            for line in f:
                string = line.split('.')[0]
                seconds = int(string)
                minutes = seconds / 60
                upminutes = str(minutes)
        return upminutes

    def read_os_name(self):
        platValue = platform.platform()
        if os.path.exists("/etc/ubuntukylin-release"):
            with open("/etc/ubuntukylin-release", "r") as fsys:
                for line in fsys:
                    if line.startswith("DISTRIB_DESCRIPTION"):
                        tmp = line
                        break
            # kobe: remove '"' and '\n'
            front = tmp.split('=')[1].replace('"', '').replace('\n', '')
            platValue = front
        elif os.path.exists("/etc/os-release"):
            with open("/etc/os-release", "r") as fsys:
                for line in fsys:
                    if line.startswith("NAME"):
                        tmp = line
                        break
            # kobe: remove '"' and '\n'
            front = tmp.split('=')[1].replace('"', '').replace('\n', '')
            platValue = front

            if front == "Kylin" or front == "YHKylin":
                with open("/etc/lsb-release", "r") as fp:
                    for line in fp:
                        if line.startswith("DISTRIB_VERSION_TYPE"):
                            tmp = line
                            # kobe: remove '"' and '\n'
                            id = tmp.split('=')[1].replace('"', '').replace('\n', '')
                            if id == "community":
                                platValue = "YHKylin community"
                            break
        else:
            community = ""
            id = ""
            with open("/etc/lsb-release", "r") as fp:
                for line in fp:
                    if line.startswith("DISTRIB_ID"):#if line.startswith("DISTRIB_DESCRIPTION"):
                        tmp = line
                        # kobe: remove '"' and '\n'
                        id = tmp.split('=')[1].replace('"', '').replace('\n', '')
                    elif line.startswith("DISTRIB_VERSION_TYPE"):
                        tmp = line
                        # kobe: remove '"' and '\n'
                        community = tmp.split('=')[1].replace('"', '').replace('\n', '')
#                        break
            platValue = id
            if id == "Kylin" or id == "YHKylin":
                if community == "community":
                    platValue = "YHKylin community"
        return platValue

    def get_os_name(self):
        return self.osname

    def get_url(self,v,p):
        vendors = {
#CPU产商
           "INTEL":["Intel"],
           "AMD":["AMD"],
           "VIMICRO":["Vimicro"],
#显卡产商
           "ATI":["ATI"],
           "1002":["ATI"],
           "SIS":["SIS"],
           "1039":["SIS"],
           "NVIDIA":["Nvidia"],
           "VIA":["VIA"],
           "XFX":["XFX"],
           "SUPERGRAPHIC":["Supergraphic"],
#显示器产商
           "AUO":["AUO"],
           "AOC":["AOC"],
           "PHILIPS":["Philips"],
           "PHL":["Philips"],
           "LEN":["Lenovo"],
           "SEC":["SAMSUNG"],
#电脑品牌
           "HASEE":["Hasee"],
           "FOUNDER":["Founder"],
           "TONGFANG":["Tongfang"],
           "TSINGHUA":["Tongfang"],
           "ACER":["Acer"],
           "LENOVO":["Lenovo"],
           "ASUSTEK":["ASUS"],
           "NEC":["NEC"],
           "HP":["HP"],
           "HEWLETT-PACKARD":["HP"],
           "SAMSUNG":["SAMSUNG"],
           "TOSHIBA":["TOSHIBA"],
           "APPLE":["Apple"],
           "DELL":["DELL"],
           "FUJITSU":["FUJITSU"],
           "PANASONIC":["Panasonic"],
           "SONY":["SONY"],
           "IBM":["IBM"],
#虚拟机
           "INNOTEK":["VirtualBox"],
           "VBOX":["VirtualBox"],
           "VIRTUALBOX":["VirtualBox"],
#网卡产商
           "3COM":["3COM"],
           "D-LINK":["D-LINK"],
           "RALINK":["Ralink"],
           "ATHEROS":["Atheros"],
           "MARVELL":["Marvell"],
           "BROADCOM":["Broadcom"],
#硬盘产商
           "EXCELSTOR":["Excelstor"],
           "HITACHI":["Hitachi"],
           "MAXTOR":["Maxtor"],
           "WESTERN":["Western Digital"],
           "LITEON":["Liteon"],
           "SEAGATE":["Seagate"],
           "QUANTUM":["Quantum"],
#光驱产商
           "PLDS":["PLDS"],
           "PBDS":["PLDS"],
           "HL-DT-ST":["LG"],
           "OPTIARC":["SONY"],
           "TSSTCORP":["TSSTcorp"],
           "PIONEER":["Pioneer"],
           "MATSHITA":["Panasonic"],
#声卡产商
           "REALTEK":["Realtek"],
           "CREATIVE":["Creative"],
#摄像头
           "SONIX":["Sonix"],
           "ETRON":["Etron"],
           "AVEO":["Aveo"],
           "SYNTEK":["Syntek"],
           "EMPIA":["Empia"],
           "CHICONY":["Chicony"],
           "OMNIVISION":["OmniVision"],
#鼠标产商
           "LOGITECH":["Logitech"],
           "SUNPLUS":["Sunplus"],
           "PRIMAX":["Primax"],
           "PIXART":["Pixart"],
           "TRUST":["Trust"],
           "1BCF":["Rapoo"],
           "AVAGO":["Avago"],
           "MICROSOFT":["Microsoft"],
#键盘产商
           "RAPOO":["Rapoo"],
#主板产商
           "GIGABYTE":["Gigabyte"],
           "BIOSTAR":["Biostar"],
           "COLORFUL":["Colorful"],
           "YESTON":["Yeston"],
#指纹识别
           "UPEK":["Authentec"],
           "AUTHENTEC":["Authentec"],
#闪存产商
           "KINGSTON":["Kingston"],
           "KINGMAX":["Kingmax"],
           "KINGBOX":["Kingbox"],
           "HYNIX":["Hynix"],
           "HYUNDAI":["Hynix"],
           "MICRON":["Micron"],
           "06C1":["Asint"],
           "ADATA":["ADATA"],
           "ZTE":["ZTE"],
           "EAGET":["Eaget"],
           "TEXAS":["Texas Instruments"],
           "MOTOROLA":["Motorola"],
#电源产商
           "SMP":["SMP"],
           "SIMPLO":["SMP"],
#BIOS产商
           "AMERICAN":["AMI"],
           "AWARD":["Phoenix"],
           "PHOENIX":["Phoenix"]
            }
        tmp = v.split(" ")[0]
        tmp = re.findall("([a-zA-Z0-9-]+)", tmp)
        if tmp :
            url = vendors.get(tmp[0].upper()) 
            if url:
                return url[0]
            else :
                k = p.split(" ")[0]
                url = vendors.get(k.upper())
                if url:
                    return url[0]
        else:
            tmp = p.split(" ")[0]
            url = vendors.get(tmp.upper())
            if url:
                return url[0]
        tmp = re.findall("ATI", v)
        if tmp :
            url = vendors.get(tmp[0].upper())
            if url:
                return url[0]
        tmp = re.findall("SIS", v)
        if tmp :
            url = vendors.get(tmp[0].upper())
            if url:
                return url[0]
        tmp = re.findall("Intel", v)
        if tmp :
            url = vendors.get(tmp[0].upper())
            if url:
                return url[0]
        tmp = re.findall("ATI", p)
        if tmp :
            url = vendors.get(tmp[0].upper())
            if url:
                return url[0]
        tmp = re.findall("SIS", p)
        if tmp :
            url = vendors.get(tmp[0].upper())
            if url:
                return url[0]
        tmp = re.findall("Intel", p)
        if tmp :
            url = vendors.get(tmp[0].upper())
            if url:
                return url[0]
        return v

    def get_computer(self):
        #Computer
        Com = {}
        hw = os.popen("dmidecode -t system")
        computer = hw.read()
        hw.close()
        ComVendor,ComProduct,ComVersion,ComSerial = '','','',''
        if computer :
            tmp = re.findall("Product Name: (.*)",computer)
            if tmp :
                ComProduct = tmp[0]
            tmp = re.findall("Manufacturer: (.*)",computer)
            if tmp :
                ComVendor = tmp[0]
            tmp = re.findall("Version: (.*)",computer)
            if tmp :
                ComVersion = tmp[0]
            tmp = re.findall("Serial Number: (.*)",computer)
            if tmp :
                ComSerial = tmp[0]
        ComVendor = self.get_url(ComVendor,ComProduct)
        Com['ComProduct'],Com['ComVendor'],Com['ComVersion'],Com['ComSerial'] = self.strip(ComProduct),self.strip(ComVendor),self.strip(ComVersion),self.strip(ComSerial)
        with open('/proc/uptime') as f:
            for line in f:
                string = line.split('.')[0]
                seconds = int(string)
                minutes = seconds / 60
                uptime = str(minutes)

#        platValue = platform.platform()
#        if os.path.exists("/etc/ubuntukylin-release"):
#            with open("/etc/ubuntukylin-release", "r") as fsys:
#                for line in fsys:
#                    if line.startswith("DISTRIB_DESCRIPTION"):
#                        tmp = line
#                        break
#            # kobe: remove '"' and '\n'
#            front = tmp.split('=')[1].replace('"', '').replace('\n', '')
#            platValue = front
##            if front.startswith("UbuntuKylin") or front.startswith("Ubuntu Kylin"):
##                platValue = platValue.replace('Ubuntu', 'Ubuntu Kylin')
#        elif os.path.exists("/etc/os-release"):
#            with open("/etc/os-release", "r") as fsys:
#                for line in fsys:
#                    if line.startswith("NAME"):
#                        tmp = line
#                        break
#            # kobe: remove '"' and '\n'
#            front = tmp.split('=')[1].replace('"', '').replace('\n', '')
#            platValue = front
##            if front.startswith("UbuntuKylin") or front.startswith("Ubuntu Kylin"):
##                platValue = platValue.replace('Ubuntu', 'Ubuntu Kylin')
#        else:
#            with open("/etc/lsb-release", "r") as fp:
#                for line in fp:
#                    if line.startswith("DISTRIB_DESCRIPTION"):
#                        tmp = line
#                        break
#            # kobe: remove '"' and '\n'
#            id = tmp.split('=')[1].replace('"', '').replace('\n', '')
#            platValue = id
#            if "Ubuntu" in platValue:
#                platValue = platValue.replace('Ubuntu', id)


#        if not os.path.exists("/etc/ubuntukylin-release"):
#            if "Ubuntu" in platValue and "Kylin" not in platValue:
#                with open("/etc/lsb-release", "r") as fsys:
#                    for line in fsys:
#                        if line.startswith("DISTRIB_DESCRIPTION"):
#                            tmp = line
#                            break
#                # kobe: remove '"' and '\n'
#                front = tmp.split('=')[1].replace('"', '').replace('\n', '')
#                if front.startswith("UbuntuKylin") or front.startswith("Ubuntu Kylin"):
#                    platValue = platValue.replace('Ubuntu', 'Ubuntu Kylin')
#        else:
#            with open("/etc/ubuntukylin-release", "r") as fp:
#                for line in fp:
#                    if line.startswith("DISTRIB_ID"):
#                        tmp = line
#                        break
#            # kobe: remove '"' and '\n'
#            id = tmp.split('=')[1].replace('"', '').replace('\n', '')
#            if "Ubuntu" in platValue:
#                platValue = platValue.replace('Ubuntu', id)

#        Com['platform'] = platValue
#        Com['platform'] = self.osname
        Com['osname'] = self.osname

        #Com['node'], Com['uptime'], Com['system'], Com['platform'],Com['architecture'], Com['release'], Com['machine'] = platform.node(),uptime,platform.system(),platform.platform(),platform.architecture()[0],platform.release(),platform.machine()
        Com['node'], Com['uptime'], Com['system'], Com['architecture'], Com['release'], Com['machine'] = platform.node(),uptime,platform.system(),platform.architecture()[0],platform.release(),platform.machine()
        return Com

    def get_cpu(self):
        # CPU
        Cpu = {}
        if self.machine == "aarch64":
            if os.path.exists(CPU_MAX_FREQ):
                fp = open(CPU_MAX_FREQ, "r")
                info = fp.read()
                fp.close()
                tmp = float(info.strip()) / (1000 * 1000)
                freq = str("%.1f" % tmp)
                #processor
                Cpu['CpuVersion'] = "1500a v1.0 64bit"
                Cpu['CpuVendor'] = "phytium"#(飞腾)
                Cpu['CpuCapacity'] = "%s GHz" % freq
                #Cpu['cpu_cores'] = "4 cores"#4 核
                if os.path.exists('/proc/cpuinfo'):
                    fp = open('/proc/cpuinfo', "r")
                    info = fp.read()
                    fp.close()
                    cnt = info.count("processor")
#                    Cpu['cpu_cores'] = _("%d cores") % cnt
                    Cpu['cpu_cores'] = cnt
                    with open('/proc/cpuinfo') as f:
                        for line in f:
                            if line.strip():
                                if line.rstrip('\n').startswith('model name'):
                                    modelName = line.rstrip('\n').split(':')[1].strip().strip('\n')
                                    if "phytium" in modelName:
#                                        Cpu['CpuVersion'] = _("%s v1.0") % modelName
                                        Cpu['CpuVersion'] = "%s v1.0" % modelName
                                        Cpu['CpuVendor'] = "phytium"#(飞腾)
                                    else:
                                        Cpu['CpuVersion'] = modelName
                                    break
                #Cpu['cpu_siblings'] = "4 thread/core"#4 线程/核
                #Cpu['clflush_size'] = "32 KB"
                #Cpu['cache_size'] = "2 MB"
            else:
                #处理器版本
                Cpu['CpuVersion'] = "1500a v1.0"
                #制造商 phytium
                Cpu['CpuVendor'] = "phytium"#(飞腾)
                #插槽
                #Cpu['CpuSlot'] = "插槽"
                #序列号
                #Cpu['CpuSerial'] = "序列号"
                #最大主频
                Cpu['CpuCapacity'] = "1800 MHz"
                #当前主频
                #Cpu['CpuSize']= "当前主频"
                #前端总线
                #Cpu['CpuClock'] = "前端总线"
                #内核数
                Cpu['cpu_cores'] = "4 "#4 核
                #线程数
                #Cpu['cpu_siblings'] = "4 thread/core"#4 线程/核
                #一级缓存
                #Cpu['clflush_size'] = "32 KB"
                #二级缓存
                #Cpu['cache_size'] = "2 MB"
        else:
            hw = os.popen("dmidecode -t processor")
            cpuin = hw.read()
            hw.close()
            CpuVersion,CpuVendor,CpuSlot,CpuSerial,CpuCapacity,CpuSize,CpuClock,cpu_cores,cpu_siblings,clflush_size,cache_size = '','','','','','','','','','',''
            if cpuin :
                tmp = re.findall("Version: (.*)",cpuin)
                if tmp :
                    CpuVersion = tmp[0]
                tmp = re.findall("Manufacturer: (.*)",cpuin)
                if tmp :
                    CpuVendor = tmp[0]
                tmp = re.findall("Socket Designation: (.*)",cpuin)
                if tmp :
                    CpuSlot = tmp[0]
                tmp = re.findall("Serial Number: (.*)",cpuin)
                if tmp :
                    CpuSerial = tmp[0]
                tmp = re.findall("Max Speed: (.*)",cpuin)
                if tmp :
                    CpuCapacity = tmp[0]
                tmp = re.findall("Current Speed: (.*)",cpuin)
                if tmp :
                    CpuSize = tmp[0]
                tmp = re.findall("External Clock: (.*)",cpuin)
                if tmp :
                    CpuClock = tmp[0]
            CpuVendor = self.get_url(CpuVendor,CpuVersion)
            Cpu['CpuVersion'],Cpu['CpuVendor'],Cpu['CpuSlot'],Cpu['CpuSerial'],Cpu['CpuCapacity'],Cpu['CpuSize'],Cpu['CpuClock'] = self.strip(CpuVersion),self.strip(CpuVendor),self.strip(CpuSlot),self.strip(CpuSerial),self.strip(CpuCapacity),self.strip(CpuSize),self.strip(CpuClock)
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
                             clflush_size = list(filter(str.isdigit,clflush_size))
                        elif line.rstrip('\n').startswith('cache size'):
                             cache_size = line.rstrip('\n').split(':')[1]
                             cache_size = list(filter(str.isdigit,cache_size))
            Cpu['cpu_cores'],Cpu['cpu_siblings'],Cpu['clflush_size'],Cpu['cache_size'] = cpu_cores,cpu_siblings,clflush_size,cache_size
        return Cpu

    def get_board(self):
        #Board and BIOS
        Boa = {}
        hw = os.popen("dmidecode -t baseboard")
        board = hw.read()
        hw.close()
        BoaProduct,BoaVendor,BoaSerial,BioVendor,BioVersion,BioRelease = '','','','','',''
        if board :
            tmp = re.findall("Product Name: (.*)",board)
            if tmp :
                BoaProduct = tmp[0]
            tmp = re.findall("Manufacturer: (.*)",board)
            if tmp :
                BoaVendor = tmp[0]
            tmp = re.findall("Serial Number: (.*)",board)
            if tmp :
                BoaSerial = tmp[0]
        hw = os.popen("dmidecode -t bios")
        bios = hw.read()
        hw.close()
        if bios :
            tmp = re.findall("Vendor: (.*)",bios)
            if tmp:
                BioVendor = tmp[0]
            tmp = re.findall("Version: (.*)",bios)
            if tmp:
                BioVersion = tmp[0]
            tmp = re.findall("Release Date: (.*)",bios)
            if tmp:
                BioRelease = tmp[0]
        BoaVendor = self.get_url(BoaVendor,BoaProduct)
        BioVendor = self.get_url(BioVendor,BioVersion)
        Boa['BoaProduct'],Boa['BoaVendor'],Boa['BoaSerial'],Boa['BioVendor'],Boa['BioVersion'],Boa['BioRelease'] = self.strip(BoaProduct),self.strip(BoaVendor),self.strip(BoaSerial),self.strip(BioVendor),self.strip(BioVersion),self.strip(BioRelease)
        return Boa

    def get_memory(self):
        #Memory Device
        Mem = {}
        if self.machine == "aarch64":
            if os.path.exists(MEMORY):
                memnum = 0
                all_exists = []
                total = [ f for f in os.listdir(MEMORY) if f.startswith("memory")]

                for p in total:
                    exists = os.path.join(MEMORY, p)
                    if os.stat(exists).st_size:
    #                    memnum += 1
                        all_exists.append(exists)

    #            Mem["Memnum"] = str(memnum)
                for i in all_exists:
                    fp = open(i, "r")
                    info = fp.read()
                    fp.close
    #                dic = dict([tuple(x.split(":")) for x in info.split("\n") if x])
                    dic = dict([tuple(x.split(":")) for x in info.split("\n") if x and ":" in x])
                    if dic in(None, {}):
                        continue
                    else:
                        memnum += 1
                    #if Mem.get("MemInfo") == None:
                    #    Mem["MemInfo"] = "DDR3 " + dic["Speed"]
                    #else:
                    #    Mem["MemInfo"] +=  "<1_1>" + "DDR3 " + dic["Speed"]
                    ###add by hebing at 2017.01.23 for 206
                    if Mem.get("MemInfo") == None:
                        Mem["MemInfo"] = "DDR3 "
                    else:
                        Mem["MemInfo"] +=  "<1_1>" + "DDR3 "
                    
                    if dic["Bank Locator"]:
                        median = str(dic["Bank Locator"])
                    else:
                        median = '$'
                    if Mem.get("MemSlot") == None:
                        Mem["MemSlot"] = median
                    else:
                        Mem["MemSlot"] +=  "<1_1>" + median

                    if dic["Size"]:
                        median = str(dic["Size"])
                    else:
                        median = '$'
                    if Mem.get("MemSize") == None:
                        Mem["MemSize"] = median
                    else:
                        Mem["MemSize"] += "<1_1>" + median

                    if dic["Manufacturer ID"]:
                        median = str(dic["Manufacturer ID"].upper())
                    else:
                        median = '$'
                    if Mem.get("MemVendor") == None:
                        Mem["MemVendor"] = median
                    else:
                        Mem["MemVendor"] += "<1_1>" + median

                    if Mem.get("MemWidth") == None:
                        Mem["MemWidth"] = "64bit"
                    else:
                        Mem["MemWidth"] += "<1_1>" + "64bit"
                Mem["Memnum"] = str(memnum)
            if Mem in (None, '', '[]', {}) or  Mem["Memnum"] == '0':#20161228
                Mem["Memnum"] = "1"
                Mem["MemWidth"] = "64bit"
                Mem["MemInfo"] = "DDR3"
                fp = open("/proc/meminfo", "r")
                info = fp.read()
                fp.close()
                dic = dict([tuple(x.split(":")) for x in info.split("\n") if x])
                MemTotal = dic["MemTotal"].strip().split(' ')[0]
                Mem["MemSize"] = GLib.format_size_for_display(int(MemTotal) * 1024)
        else:
            MemInfo,MemWidth,Memnum,MemSlot,MemProduct,MemVendor,MemSerial,MemSize,BioVendor = "","","","","","",'','',''
            hw = os.popen("dmidecode -t memory")
            memory = hw.read()
            hw.close()
            num = 0
            q = re.findall('Memory Device\n',memory)
            if q :
                memory = memory[memory.index("Memory Device\n")+len("Memory Device\n"):]
            else :
                memory = ''
            if memory :
                mark = re.findall("Data Width: (.*)",memory)
                if mark :
                    for k in mark :
                        if not k == 'Unknown':
                            num += 1
                            if MemWidth :
                                MemWidth += "<1_1>" + k
                            else :
                                MemWidth = k
                Memnum = str(num)
                tmp = re.findall("Bank Locator: (.*)",memory)
                i = 0
                if tmp :
                    for k in mark :
                        i += 1
                        if not k == 'Unknown':
                            if MemSlot :
                                MemSlot +="<1_1>"+ tmp[i-1]
                            else :
                                MemSlot = tmp[i-1]
                tmp = re.findall("Part Number: (.*)",memory)
                i = 0
                if tmp :
                    for k in mark :
                        i += 1
                        if not k == 'Unknown':
                            if MemProduct :
                                MemProduct += "<1_1>" + tmp[i-1]
                            else :
                                MemProduct = tmp[i-1]
                tmp = re.findall("Manufacturer: (.*)",memory)
                i = 0
                if tmp :
                    for k in mark :
                        i += 1
                        if not k == 'Unknown':
                            if MemVendor :
                                MemVendor += "<1_1>" + tmp[i-1]
                            else :
                                MemVendor = tmp[i-1]
                tmp = re.findall("Serial Number: (.*)",memory)
                i = 0
                if tmp :
                    for k in mark :
                        i += 1
                        if not k == 'Unknown':
                            if MemSerial :
                                MemSerial += "<1_1>" + tmp[i-1]
                            else :
                                MemSerial = tmp[i-1]
                tmp = re.findall("Size: (.*)",memory)
                i = 0
                if tmp :
                    for k in mark :
                        i += 1
                        if not k == 'Unknown':
                            if MemSize :
                                MemSize += "<1_1>" + tmp[i-1]
                            else :
                                MemSize = tmp[i-1]
                tmp0 = self.strip(re.findall("Form Factor: (.*)",memory))
                tmp1 = self.strip(re.findall("Type: (.*)",memory))
                tmp2 = self.strip(re.findall("Type Detail: (.*)",memory))
                tmp3 = self.strip(re.findall("Speed: (.*)",memory))
                i = 0
                if tmp0 and tmp1 and tmp2 and tmp3 :
                    for k in mark :
                        i += 1
                        if not k == 'Unknown':
                            if MemInfo :
                                MemInfo += "<1_1>" + tmp0[i-1] + ' ' + tmp1[i-1] + ' ' + tmp2[i-1] + ' ' + tmp3[i-1]
                            else :
                                MemInfo = tmp0[i-1] + ' ' + tmp1[i-1] + ' ' + tmp2[i-1] + ' ' + tmp3[i-1]
            Mem["MemInfo"],Mem["MemWidth"],Mem["MemSlot"],Mem["MemProduct"],Mem["MemVendor"],Mem["MemSerial"],Mem["MemSize"],Mem["Memnum"] = MemInfo,self.strip(MemWidth),self.strip(MemSlot),self.strip(MemProduct),self.strip(MemVendor),self.strip(MemSerial),self.strip(MemSize),self.strip(Memnum)
        return Mem
    ## 2017.07.27 add by hebing
    def get_monitor(self):
        ret_output, ret_vendor, ret_product, ret_year, ret_week, \
                ret_size, ret_in, ret_gamma, ret_maxmode = "", "", "", "", "", "", "", "", ""
        Vga_product,Vga_vendor,Vga_businfo,Vga_Drive = "", "", "", ""
        Vga_num = 0
        if os.path.exists("/var/log/Xorg.0.log"):
            with open("/var/log/Xorg.0.log", "r") as fp:
                info = fp.read()
                value = re.findall("EDID for output (.*)", info)
                for monitor in value:
                    ret = {}
                    p = re.compile(r'Output %s connected' % monitor)
                    for m in p.finditer(info):  # p.finditer(info) 返回一个迭代对象，通常只会循环一次
                        Vga_num += 1
                        #print info.split("EDID for output %s" % monitor)[1].split("EDID for output")[0]
                        #ret.setdefault("Mon_output", monitor)
                        ret_output += (monitor + "<1_1>")
                        localinfo = info.split("EDID for output %s" % monitor)[1].split("EDID for output")[0]

                        result = re.findall('Monitor name: \s*(\w*)\s*(\w*)', localinfo)
                        result_bak = re.findall("Manufacturer:\s*(\w*)\s*Model:\s*(\w*)", localinfo)
                        #ret.setdefault("Mon_vendor", result[0][0])
                        #ret.setdefault("Mon_product", " ".join(result[0]))
                        if result: ### 笔记本没有Monitor name
                            ret_vendor += (result[0][0] + "<1_1>")
                            ret_product += (" ".join(result[0]) + "<1_1>")
                        else:
                            ret_vendor += (result_bak[0][0] + "<1_1>")
                            ret_product += (" ".join(result_bak[0]) + "<1_1>")

                        result = re.findall("Year:\s*(\w*)\s*Week:\s*(\w*)", localinfo)
                        #ret.setdefault("Mon_year", result[0][0])
                        #ret.setdefault("Mon_week", result[0][1])
                        ret_year += (result[0][0] + "<1_1>")
                        ret_week += (result[0][1] + "<1_1>")

                        result = re.findall("Image Size: \s*(\w*) x (\w*)", localinfo)
                        x = float(result[0][0])/10; y = float(result[0][1])/10; d = math.sqrt(x**2 + y**2)/2.54
                        #ret.setdefault("Mon_size", (str(x) + " X " + str(y) + " cm"))
                        #ret.setdefault("Mon_in", str("%.1f" %d))
                        ret_size += ((str(x) + " X " + str(y) + " cm") + "<1_1>")
                        ret_in += (str("%.1f" %d) + "<1_1>")

                        result = re.findall("Gamma: (\S*)", localinfo)
                        #ret.setdefault("Mon_gamma", result[0])
                        ret_gamma += (result[0] + "<1_1>")

                        h = re.findall("h_active: (\d*)", localinfo); v = re.findall("v_active: (\d*)", localinfo)
                        #ret.setdefault("Mon_maxmode", h[0] + "X" + v[0])
                        ret_maxmode += ((h[0] + "X" + v[0]) + "<1_1>")

                        Vga_businfo += "<1_1>"; Vga_product += "<1_1>"; Vga_vendor += "<1_1>"; Vga_Drive += "<1_1>"

        status, output = subprocess.getstatusoutput('lspci -vvv')
        if not status:
            for local in output.split("\n\n"):
                if "VGA compatible controller: " in local:
                    Vga_num += 1
                    ret_output += ""; ret_vendor += ""; ret_product += ""; ret_year += ""; ret_week += ""
                    ret_size += ""; ret_in += ""; ret_gamma += ""; ret_maxmode += ""

                    Vga_businfo += "pci@0000:" + local.split(" ")[0]

                    for line in local.split("\n"):
                        if "VGA compatible controller: " in line:
                            print(line)
                            Vga_product += line.split(":")[2][:-30]
                            Vga_vendor += self.get_url("", line.split(":")[2])
                        if "Kernel driver in use: " in line:
                            Vga_Drive += line.split(":")[1]
                        elif "Kernel driver in use: " not in local:
                            Vga_Drive += ""

        ret["Mon_output"], ret["Mon_vendor"], ret["Mon_product"], ret["Mon_year"], ret["Mon_week"], ret["Mon_size"], ret["Mon_in"] = \
                ret_output, ret_vendor, ret_product, ret_year, ret_week, ret_size, ret_in
        ret["Mon_gamma"], ret["Mon_maxmode"] = ret_gamma, ret_maxmode
        ret["Vga_num"], ret['Vga_businfo'],ret['Vga_product'],ret['Vga_vendor'],ret['Vga_Drive'] = self.strip(str(Vga_num)), self.strip(Vga_businfo),self.strip(Vga_product),self.strip(Vga_vendor),self.strip(Vga_Drive)
        return ret

    def get_disk_obsolete(self):
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
        n =  os.popen("ls /dev/sd?")
        line = n.read()
        n.close()
        n = os.popen("ls /dev/hd?")
        line += n.read()
        n.close()
        if line :
            line = line.split('\n')
            for k in line :
                if k :
                    st = os.popen("hdparm -i %s" % k)
                    strin = st.read()
                    st.close()
                    tmp = re.findall("Model=(.*), F",strin)
                    if not tmp and DiskProduct:
                        continue
                    if tmp:
                        median = tmp[0]
                    else:
                        median = '$'
                    if DiskProduct :
                        DiskProduct += "<1_1>" + median
                    else:
                        DiskProduct = median
                    i = 0
                    tm = ''
                    while i < len(disk_manufacturers):
                        ven = re.compile(disk_manufacturers[i],re.I)
                        tm = ven.findall(tmp[0])
                        if tm:
                            break;
                        i += 2
                    if tm:
                        median = disk_manufacturers[i+1]
                    else:
                        median = '$'
                    if DiskVendor :
                        DiskVendor += "<1_1>" + median
                    else:
                        DiskVendor += median

                    tmp = re.findall("FwRev=(.*), ",strin)
                    if tmp :
                        median = tmp[0]
                    else:
                        median = '$'
                    if DiskFw :
                        DiskFw += "<1_1>" + median
                    else:
                        DiskFw = median

                    tmp = re.findall("SerialNo=(.*)",strin)
                    if tmp :
                        median = tmp[0]
                    else:
                        median = '$'
                    if DiskSerial :
                        DiskSerial += "<1_1>" + median
                    else :
                        DiskSerial = median

                    ds = os.popen("fdisk -l %s" % k)
                    d = ds.read()
                    ds.close()
                    tmp = re.findall("%s: (.*)," % k,d)
                    if tmp:
                        median = tmp[0]
                    else:
                        median = '$'
                    ### add by hebing at 2017.01.20
                    ### NAME MAJ:MIN RM SIZE RO TYPE MOUNTPOINT
                    disklist = []
                    status, output = subprocess.getstatusoutput("lsblk -ab")
                    for line in output.split("\n"):
                        value = line.split()
                        if value[1] == "8:0" and value[5] == "disk":
                            disklist.append(int(value[3]))
                    if not status:
                        median = str(sum(disklist) / 1000 / 1000 / 1000) + "G"
                    else:
                        median = '$'
                    if DiskCapacity :
                        DiskCapacity += "<1_1>" + median
                    else :
                        DiskCapacity = median
                    disknum  += 1
                    if DiskName :
                        DiskName += "<1_1>" + k
                    else :
                        DiskName = k
            
        dis['DiskNum'],dis['DiskProduct'],dis['DiskVendor'],dis['DiskCapacity'],dis['DiskName'],dis['DiskFw'],dis['DiskSerial'] = self.strip(str(disknum)),self.strip(DiskProduct),self.strip(DiskVendor),self.strip(DiskCapacity),self.strip(DiskName),self.strip(DiskFw),self.strip(DiskSerial)
        return dis

    # writed by hb at 20170517
    def get_disk(self):
        dis = {}
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
                }
        DiskProduct,DiskVendor,DiskCapacity,DiskName,DiskFw,DiskSerial = '','','','','',''
        diskdict = {}
        disknum = 0
        statusfirst, output = subprocess.getstatusoutput("lsblk -b")

        for line in output.split("\n"):
            value = line.split()
            if value[1].startswith("8:") and value[5] == "disk":
                disknum += 1
                HDSize = get_human_read_capacity_size(int(value[3]))
                DiskCapacity += ((HDSize if not statusfirst else "$") + "<1_1>")
#                DiskCapacity += ( ((str(int(value[3]) / 10**9) + "G") if not statusfirst else "$") + "<1_1>")

                infodict = {}
                status, output = subprocess.getstatusoutput("hdparm -i %s" % ("/dev/" + value[0]))

                if not status:
                    singleinfolist = [ tmp.strip() for tmp in output.split("\n") if tmp]
                    for mid in singleinfolist[1].split(","):
                        needinfo = mid.split("=")
                        infodict.setdefault(needinfo[0].strip(), needinfo[1])
                    for key, va in list(disk_manufacturers.items()):
                        if infodict.get("Model", "$").startswith(key):
                            infodict.setdefault("Vendor", va)
                            break

                    DiskProduct += (infodict.get("Model", "$") + "<1_1>")
                    DiskVendor += (infodict.get("Vendor", "$") + "<1_1>")
                    DiskFw += (infodict.get("FwRev", "$") + "<1_1>")
                    DiskSerial += (infodict.get("SerialNo", "$") + "<1_1>")
                else:
                    pprint(output)
                    DiskProduct += ( "$" + "<1_1>")
                    DiskVendor += ("$" + "<1_1>")
                    DiskFw += ("$" + "<1_1>")
                    DiskSerial += ("$" + "<1_1>")
                DiskName += (("/dev/" + value[0]) + "<1_1>")
        dis['DiskNum'],dis['DiskProduct'],dis['DiskVendor'],dis['DiskCapacity'],dis['DiskName'],dis['DiskFw'],dis['DiskSerial'] = str(disknum),DiskProduct.rstrip("<1_1>"),DiskVendor.rstrip("<1_1>"),DiskCapacity.rstrip("<1_1>"),DiskName.rstrip("<1_1>"),DiskFw.rstrip("<1_1>"),DiskSerial.rstrip("<1_1>")
        return dis



    # writed by kobe 20170318
    def get_network_obsolete(self):
#        net = {'NetNum': 2, 'NetSerial': '00:23:81:21:e4:0b', 'NetProduct': '82574L Gigabit Network Connection', 'NetLogicalname': 'enp1s0', 'NetDrive': 'e1000e', 'NetIp': 'unknown', 'NetType': 'Ethernet interface', 'NetVendor': 'Intel Corporation', 'NetBusinfo': 'pci@0000:01:00.0'}
#        return net
        net = {}
        NetNum = 0
        NetType,NetProduct,NetVendor,NetDrive,NetBusinfo,NetLogicalname,NetSerial,NetIp = '','','','','','','',''
#        fp=os.popen("ifconfig -s|grep -v Iface|grep -v lo|awk '{print $1}' | wc -l");
#        NetNum = int(fp.read().strip('\n'))
#        net['NetNum'] = NetNum
#        fp.close()
        try:
            fp = os.popen("lshw -C network");
            lines = fp.readlines()
            fp.close()
            if lines:
                for line in lines:
                    if ":" in line:
                        line = line.strip()
                        if "description:" in line:
                            tmp = re.findall('description: (.*)', line)
                            NetNum += 1
                            if tmp[0] in [None, '']:
                                if NetType:
                                    NetType += "<1_1>" + "unknown"
                                else:
                                    NetType = "unknown"
                            else:
                                if NetType:
                                    NetType += "<1_1>" + tmp[0]
                                else:
                                    NetType = tmp[0]
                        elif "product:" in line:
                            tmp = re.findall('product: (.*)', line)
                            if tmp[0] in [None, '']:
                                if NetProduct:
                                    NetProduct += "<1_1>" + "unknown"
                                else:
                                    NetProduct = "unknown"
                            else:
                                if NetProduct:
                                    NetProduct += "<1_1>" + tmp[0]
                                else:
                                    NetProduct = tmp[0]
                        elif "vendor:" in line:
                            tmp = re.findall('vendor: (.*)', line)
                            if tmp[0] in [None, '']:
                                if NetVendor:
                                    NetVendor += "<1_1>" + "unknown"
                                else:
                                    NetVendor = "unknown"
                            else:
                                if NetVendor:
                                    NetVendor += "<1_1>" + tmp[0]
                                else:
                                    NetVendor = tmp[0]
                        elif "bus info:" in line:
                            tmp = re.findall('bus info: (.*)', line)
                            if tmp[0] in [None, '']:
                                if NetBusinfo:
                                    NetBusinfo += "<1_1>" + "unknown"
                                else:
                                    NetBusinfo = "unknown"
                            else:
                                if NetBusinfo:
                                    NetBusinfo += "<1_1>" + tmp[0]
                                else:
                                    NetBusinfo = tmp[0]
                        elif "serial:" in line:
                            tmp = re.findall('serial: (.*)', line)
                            if tmp[0] in [None, '']:
                                if NetSerial:
                                    NetSerial += "<1_1>" + "unknown"
                                else:
                                    NetSerial = "unknown"
                            else:
                                if NetSerial:
                                    NetSerial += "<1_1>" + tmp[0]
                                else:
                                    NetSerial = tmp[0]
                        elif "logical name:" in line:
                            tmp = re.findall('logical name: (.*)', line)
                            if tmp[0] in [None, '']:
                                if NetLogicalname:
                                    NetLogicalname += "<1_1>" + "unknown"
                                else:
                                    NetLogicalname = "unknown"
                                if NetIp:
                                    NetIp += "<1_1>" + "unknown"
                                else:
                                    NetIp = "unknown"
                                if NetDrive:
                                    NetDrive += "<1_1>" + "unknown"
                                else:
                                    NetDrive = "unknown"
#                                if NetType:
#                                    NetType += "<1_1>unknown"
#                                else:
#                                    NetType = "unknown"
                            else:
                                if NetLogicalname:
                                    NetLogicalname += "<1_1>" + tmp[0]
                                else:
                                    NetLogicalname = tmp[0]
#                                if tmp[0].startswith('veth') or tmp[0].startswith('virbr'):
#                                    if NetType:
#                                        NetType += "<1_1>VNIC"
#                                    else:
#                                        NetType = "VNIC"
#                                else:
#                                    if NetType:
#                                        NetType += "<1_1>unknown"
#                                    else:
#                                        NetType = "unknown"
                                ip = get_interface_ip(tmp[0])
                                if ip in [None, '']:
                                    if NetIp:
                                        NetIp += "<1_1>" + "unknown"
                                    else:
                                        NetIp = "unknown"
                                else:
                                    if NetIp:
                                        NetIp += "<1_1>" + ip
                                    else:
                                        NetIp = ip
                                driver = get_interface_driver(tmp[0])#enp0s25  wlp3s0
                                if driver in [None, '']:
                                    if NetDrive:
                                        NetDrive += "<1_1>" + "unknown"
                                    else:
                                        NetDrive = "unknown"
                                else:
                                    if NetDrive:
                                        NetDrive += "<1_1>" + driver
                                    else:
                                        NetDrive = driver

#                for line in lines:
#                    if ":" in line:
#                        line = line.strip()
#                        if "description:" in line:
#                            tmp = re.findall('description: (.*)', line)
#                            if tmp[0] in [None, '']:
#                                if NetType:
#                                    NetType += "<1_1>" + "unknown"
#                                else:
#                                    NetType = "unknown"
#                            else:
#                                if NetType:
#                                    NetType += "<1_1>" + tmp[0]
#                                else:
#                                    NetType = tmp[0]
            net['NetNum'] = NetNum
            net['NetType'],net['NetProduct'],net['NetVendor'],net['NetBusinfo'],net['NetLogicalname'],net['NetSerial'],net['NetIp'],net['NetDrive'] = NetType.rstrip("<1_1>"), NetProduct.rstrip("<1_1>"),NetVendor.rstrip("<1_1>"),NetBusinfo.rstrip("<1_1>"),NetLogicalname.rstrip("<1_1>"),NetSeriali.rstrip("<1_1>"),NetIp.rstrip("<1_1>"), NetDrive.rstrip("<1_1>")
            return net
        except Exception as e:
            return net
#        print NetType
#        print NetProduct
#        print NetVendor
#        print NetBusinfo
#        print NetSerial
#        print NetLogicalname
#        print NetIp
#        print NetDrive

    #write by hb at 20170516 for 20x_server
    def get_network(self):
        net = {}
        netflag = ""
        NetType,NetProduct,NetVendor,NetDriver,NetBusinfo,NetLogicalname,NetSerial,NetIp = '','','','','','','',''
        
        try:
            #fp = open("/home/ice/networkinfo")
            #allinfo = fp.read()
            #fp.close()

            fp = os.popen("lshw -C network");
            allinfo = fp.read()
            infolist = allinfo.split("*-network")[1:]
            
            for singleinfo in infolist:
                infodict = {}
                singleinfolist = [ tmp.strip() for tmp in singleinfo.split("\n") ]
                netflag = singleinfolist[0]
                for info in singleinfolist[1:]:
                    if info:
                        tmp = info.split(": ")
                        pprint(tmp)
                        infodict.setdefault(tmp[0], tmp[1])
                pprint(infodict)

                NetType += ( infodict.get("description", "unknown") + "<1_1>" )

                NetProduct += ( infodict.get("product", "unknown") + "<1_1>" )
                
                NetVendor += ( infodict.get("vendor", "unknown") + "<1_1>")

                NetBusinfo += ( infodict.get("bus info", "unknown") + "<1_1>" )

                NetSerial += ( infodict.get("serial", "unknown") + "<1_1>")

                NetLogicalname += ( infodict.get("logical name", "unknown") + "<1_1>")
                NetIp += ( get_interface_ip(infodict.get("logical name", "unknown")) + "<1_1>")
                NetDriver += (get_interface_driver(infodict.get("logical name", "unknown")) + "<1_1>")

            net['NetNum'] = len(infolist)
            net['NetType'],net['NetProduct'],net['NetVendor'],net['NetBusinfo'],net['NetLogicalname'],net['NetSerial'],net['NetIp'],net['NetDrive'] = NetType.rstrip("<1_1>"), NetProduct.rstrip("<1_1>"),NetVendor.rstrip("<1_1>"),NetBusinfo.rstrip("<1_1>"),NetLogicalname.rstrip("<1_1>"),NetSerial.rstrip("<1_1>"),NetIp.rstrip("<1_1>"), NetDriver.rstrip("<1_1>")
        except Exception as e:
            pass
        return net


    #kobe:测试发现服务器上有个网卡名为：lxcbr0，其通过lspci -vvv找不到对应的信息
    def get_network_test(self):
        net = {}
        NetNum = 0
        #NetList = []
        NetProduct,NetVendor,NetDrive,NetBusinfo,NetLogicalname,NetSerial,NetIp,NetLink,NetCapacity,Subsystem = '','','','','','','','','',''
        fp=os.popen("ifconfig -s|grep -v Iface|grep -v lo|awk '{print $1}'")
        interface = fp.readlines()
        fp.close()
        ip_dic={}
        for name in interface:
            name = name.strip()
            if name is not "lo":#20161228
                mac = get_interface_mac(name)
                if NetSerial:
                    NetSerial += "<1_1>" + mac
                else:
                    NetSerial = mac
                ip = get_interface_ip(name)
                if NetIp:
                    NetIp += "<1_1>" + ip
                else:
                    NetIp = ip
                NetNum += 1
                #NetList.append(name)
                if NetLogicalname:
                    NetLogicalname += "<1_1>" + name
                else:
                    NetLogicalname = name

        n = os.popen('lspci -vvv')
        network = n.read()
        n.close()
        bus = re.findall('Ethernet controller: ', network)
        if bus:
            #tmp =network network[network.index('Ethernet controller: ')-8:]
            #network = network[network.index('Ethernet controller: ')+len('Ethernet controller: '):]
            #addr = network.index('Ethernet controller: ')
            #network = network[:network.index('Ethernet controller: ')-1]
            #print network
            while bus:
                st = network[:network.index('Ethernet controller: ')-1]
                tmp = network[st.rindex('\n')+1:network.index('Ethernet controller: ')-1]
                if tmp:
                    if NetBusinfo:
                        NetBusinfo += "<1_1>" + 'pci@0000:' + tmp
                    else:
                        NetBusinfo = 'pci@0000:' + tmp
                network = network[network.index('Ethernet controller: '):]
                tmp = network[network.index('Ethernet controller: ')+len('Ethernet controller: '):network.index('\n')]
                if tmp:
                    if NetVendor:
                        NetVendor += "<1_1>" + self.get_url('', tmp)
                    else:
                        NetVendor = self.get_url('', tmp)
                    if NetProduct:
                        NetProduct += "<1_1>" + tmp
                    else:
                        NetProduct = tmp 
                network = network[network.index('Ethernet controller: ')+len('Ethernet controller: '):]
                idx = network[network.index('Subsystem: '):]
                tmp = idx[idx.index('Subsystem: ')+len('Subsystem: '):idx.index('\n')]
                if tmp:
                    if Subsystem:
                        Subsystem += "<1_1>" + tmp
                    else:
                        Subsystem = tmp  
                idx = network[network.index('Kernel driver in use: '):]
                tmp = idx[idx.index('Kernel driver in use: ')+len('Kernel driver in use: '):idx.index('\n')]
                if tmp:
                    if NetDrive:
                        NetDrive += "<1_1>" + tmp
                    else:
                        NetDrive = tmp
                bus = re.findall('Ethernet controller: ', network)
        #if network :
        #    if re.findall('Ethernet controller: ',network):
        #        tmp = network[network.index('Ethernet controller: ')-8:] 
        #        NetBusinfo = 'pci@0000:' + tmp[:8]
        #        pro = re.findall('Ethernet controller: (.*)',tmp)
        #        NetProduct = pro[0]
        #        NetVendor = self.get_url('',pro[0])
        #        tmp =  re.findall('Kernel driver in use: (.*)',tmp)
        #        NetDrive = tmp[0]
        #n = os.popen('ifconfig eth')
        #network = n.read()
        #n.close()
        #if network :
        #    NetLogicalname = network[:4]
        #    tmp = re.findall("\w\w:\w\w:\w\w:\w\w:\w\w:\w\w",network)
        #    if tmp:
        #        NetSerial = tmp[0]
        #    tmp = re.findall("inet(.*)",network)
        #    if tmp:
        #        ip = tmp[0][tmp[0].index(':')+len(':'): ]
        #        ip = ip[: ip.index(' ')]
        #        NetIp = ip
        # modify by kobe(LP: #1310882 )
        # -------------------get eth interface and ip address-------------------
        #fp=os.popen("ifconfig -s|grep -v Iface|grep -v lo|awk '{print $1}'")
        #interface=fp.readlines()
        #fp.close()
        #print interface
        #ip_dic={}
        #devName = ''
        #for name in interface:
        #    name=name.strip()
        #    if devName:
        #        devName += "<1_1>" + name
        #    else:
        #        devName = name
        #    # remove 'wlan'
        #    #if name.startswith('eth'):
        #    if name is not "lo":#20161228
        #print NetList
        #for netItem in NetList:
        #    try:
        #        sk = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        #        ipaddr=socket.inet_ntoa(fcntl.ioctl(
        #            sk.fileno(),
        #            0x8915, # SIOCGIFADDR
        #            struct.pack('256s', netItem[:15])
        #        )[20:24])
        #        ip_dic[netItem]=ipaddr
        #    except Exception as e:
        #        print e
        #print ip_dic
        #if len(ip_dic) == 0:
        #    #NetLogicalname = 'N/A'
        #    NetIp = 'N/A'
        #else:
        #    #NetLogicalname =  ip_dic.keys()[0]
        #    NetIp =  ip_dic.values()[0]
        # -------------------get mac address-------------------
        #mac_addr = uuid.UUID(int = uuid.getnode()).hex[-12:]
        #NetSerial = ":".join([mac_addr[e:e+2] for e in range(0,11,2)])
        try:
            n = os.popen('mii-tool -v')
            network = n.read()
            n.close()
            if network :
                tmp = re.findall("basic status: (.*)",network)
                if tmp:
                    NetLink = tmp[0]
                tmp = re.findall('capabilities: (\d*)',network)
                if tmp:
                    NetCapacity = tmp[0]
        except Exception as e:
            print(e)
        WlanProduct,WlanVendor,WlanBusinfo,WlanLogicalname,WlanSerial,WlanIp,WlanDrive = '','','','','','',''
        n = os.popen('lspci -vvv')
        wlan = n.read()
        n.close()
        if wlan :
            if re.findall('Network controller: ',wlan):
                tmp = wlan[wlan.index('Network controller: ') - 8:]
                WlanBusinfo = 'pci@0000:' + tmp[:8]
                pro = re.findall('Network controller: (.*)',tmp)
                WlanProduct = pro[0]
                WlanVendor = self.get_url('',pro[0])
                tmp =  re.findall('Kernel driver in use: (.*)',tmp)
                WlanDrive = tmp[0]
        n = os.popen('ifconfig wlan')
        wlan = n.read()
        n.close()
        if wlan:
            WlanLogicalname = wlan[:5]
            tmp = re.findall("\w\w:\w\w:\w\w:\w\w:\w\w:\w\w",wlan)
            if tmp:
                WlanSerial = tmp[0]
            tmp = re.findall("inet(.*)",wlan)
            if tmp:
                ip = tmp[0][tmp[0].index(':')+len(':'):]
                ip = ip[: ip.index(' ')]
                WlanIp = ip
        net['NetNum'] = NetNum
        net['NetProduct'],net['NetVendor'],net['NetBusinfo'],net['NetLogicalname'],net['NetSerial'],net['NetIp'],net['NetLink'],net['NetCapacity'],net['NetDrive'],net['WlanProduct'],net['WlanVendor'],net['WlanBusinfo'],net['WlanLogicalname'],net['WlanSerial'],net['WlanIp'],net['WlanDrive'] = self.strip(NetProduct),self.strip(NetVendor),self.strip(NetBusinfo),self.strip(NetLogicalname),self.strip(NetSerial),self.strip(NetIp),self.strip(NetLink),self.strip(NetCapacity),self.strip(NetDrive),self.strip(WlanProduct),self.strip(WlanVendor),self.strip(WlanBusinfo),self.strip(WlanLogicalname),self.strip(WlanSerial),self.strip(WlanIp),self.strip(WlanDrive)
        return net

    def get_multimedia(self):
        Mul = {}
        MulNum = 0
        MulProduct,MulVendor,MulBusinfo,MulDrive = '','','',''
        n = os.popen('lspci -vvv')
        multimedia = n.read()
        n.close()
        if multimedia:
            if re.findall('Audio device:',multimedia):
                tmp = multimedia[multimedia.index('Audio device:')- 8:]
                multimedia = tmp[30:]
                if MulBusinfo:
                    MulBusinfo += "<1_1>"+ 'pci@0000:' + tmp[ :8]
                else :
                    MulBusinfo = 'pci@0000:' + tmp[ :8]
                if MulProduct:
                    pro = re.findall('Audio device: (.*)',tmp)
                    MulProduct += "<1_1>" + pro[0]
                    MulVendor += "<1_1>" + self.get_url('',self.strip(pro[0]))
                else :
                    pro = re.findall('Audio device: (.*)',tmp)
                    MulProduct = pro[0]
                    MulVendor = self.get_url('',self.strip(pro[0]))
                MulNum += 1
                tmp = re.findall('Kernel driver in use: (.*)',tmp)
                if MulDrive:
                    MulDrive += "<1_1>" + tmp[0]
                else :
                    MulDrive = tmp[0]
            elif re.findall('Multimedia audio controller:',multimedia) :
                tmp = multimedia[multimedia.index('Multimedia audio controller:')- 8:]
                multimedia = tmp[30:]
                if MulBusinfo:
                    MulBusinfo += "<1_1>"+ 'pci@0000:' + tmp[ :8]
                else :
                    MulBusinfo = 'pci@0000:' + tmp[ :8]
                if MulProduct:
                    pro = re.findall('Multimedia audio controller: (.*)',tmp)
                    MulProduct += "<1_1>" + pro[0]
                    MulVendor += "<1_1>" + self.get_url('',self.strip(pro[0]))
                else :
                    pro = re.findall('Multimedia audio controller: (.*)',tmp)
                    MulProduct = pro[0]
                    MulVendor = self.get_url('',self.strip(pro[0]))
                MulNum += 1
                tmp = re.findall('Kernel driver in use: (.*)',tmp)
                if MulDrive:
                    MulDrive += "<1_1>" + tmp[0]
                else :
                    MulDrive = tmp[0]
        Mul['MulNum'],Mul['MulProduct'],Mul['MulVendor'],Mul['MulBusinfo'],Mul['MulDrive'] = self.strip(str(MulNum)),self.strip(MulProduct),self.strip(MulVendor),self.strip(MulBusinfo),self.strip(MulDrive)
        return Mul

    def get_dvd(self):
        dvd = {}
        Dvdnum = 0
        DvdProduct,DvdVendor,DvdName,DvdFw,DvdSerial = '','','','',''
        n = os.popen("hdparm -i /dev/cdrom")
        cdrom = n.read()
        n.close()
        if cdrom:
            tmp = re.findall("Model=(.*), F",cdrom)
            if tmp:
                DvdProduct = tmp[0]
                DvdVendor = self.get_url('',self.strip(DvdProduct))
                if not DvdVendor :
                    pro = DvdProduct[:DvdProduct.index('DVD')]
                    DvdVendor = self.get_url('',self.strip(pro))
                if not DvdVendor :
                    pro = DvdProduct[:DvdProduct.index('CD')]
                    DvdVendor = self.get_url('',self.strip(pro))
                tmp = re.findall("FwRev=(.*), ",cdrom)
                if tmp :
                    DvdFw = tmp[0]
                tmp = re.findall("SerialNo=(.*)",cdrom)
                if tmp :
                    DvdSerial = tmp[0]
                DvdName = '/dev/cdrom'
                Dvdnum += 1
        dvd['Dvdnum'],dvd['DvdProduct'],dvd['DvdVendor'],dvd['DvdName'],dvd['DvdFw'],dvd['DvdSerial'] = self.strip(str(Dvdnum)),self.strip(DvdProduct),self.strip(DvdVendor),self.strip(DvdName),self.strip(DvdFw),self.strip(DvdSerial)
        return dvd

    def get_usb(self):
        usb = {}
        Usbnum = 0
        UsbVendor, UsbBusinfo, UsbID, UsbProduct, bcdUsb, UsbMaxpower = '','','','','',''
        n = os.popen("lsusb -v")
        usbinfo = n.read()
        n.close()
        bus = re.findall('Bus 0',usbinfo)
        if bus:
            usbinfo = usbinfo[usbinfo.index('Bus 0')+len('Bus 0'):]
        while bus:
            usbstr = usbinfo[:usbinfo.index('Device Status:')]
            flag = usbstr[usbstr.index('\n')-8:usbstr.index('\n')]
            if not flag == 'root hub' :
                if UsbBusinfo:
                    UsbBusinfo += "<1_1>" + 'Bus 0'+usbstr[:2]
                else :
                    UsbBusinfo = 'Bus 0'+usbstr[:2]
                
                tmp = re.findall('idVendor(.*)',usbstr)
                vendor = tmp[0].lstrip()
                if UsbVendor:
                    UsbVendor += "<1_1>" + vendor[7:]
                else :
                    UsbVendor = vendor[7:]
                
                tmp = re.findall('idProduct(.*)',usbstr)
                product = tmp[0].lstrip()
                if UsbProduct:
                    UsbProduct += "<1_1>" + product[7:]
                else :
                    UsbProduct = product[7:]
                
                if UsbID:
                    UsbID += "<1_1>" + vendor[2:6] + ':' + product[2:6]
                else :
                    UsbID = vendor[2:6] + ':' + product[2:6]
                
                tmp = re.findall('bcdUSB(.*)',usbstr)
                if bcdUsb:
                    bcdUsb += "<1_1>" + tmp[0].lstrip()
                else :
                    bcdUsb = tmp[0].lstrip()
                
                tmp = re.findall('MaxPower(.*)',usbstr)
                if UsbMaxpower:
                    UsbMaxpower += "<1_1>" + tmp[0].lstrip()
                else :
                    UsbMaxpower = tmp[0].lstrip()
                Usbnum += 1
            bus = re.findall('Bus 0',usbinfo)
            if bus :
                usbinfo = usbinfo[usbinfo.index('Bus 0')+len('Bus 0'):]
        usb['Usbnum'],usb['UsbVendor'],usb['UsbProduct'],usb['UsbBusinfo'],usb['UsbID'],usb['bcdUsb'],usb['UsbMaxpower'] = self.strip(str(Usbnum)),self.strip(UsbVendor),self.strip(UsbProduct),self.strip(UsbBusinfo),self.strip(UsbID),self.strip(bcdUsb),self.strip(UsbMaxpower)
        return usb

    def judge_sensors_exists(self):
        if os.path.exists("/usr/bin/sensors"):
            r = os.popen("/usr/bin/sensors")
            text = r.read()
            r.close()
            if "w83795g-i2c-1-2c" in text or "w83795adg-i2c-1-2c" in text:
                return True
            else:
                return False
        return False

    def get_sensors(self):
#        origin = {"IN0": "0.75V", #"内存参考电压"
#                "IN2": "1.0V", #"SATA控制器电压"
#                "IN3": "1.5V", #"内存电压",
#                "IN5": "1.8V", #"CPU管脚电压",
#                "IN6": "1.25 V", #"桥片电压",
#                "TR1": "1.65 V", #"ATX_3V3",
#                "TR2": "1.67 V", #"ATX_5V",
#                "TR3": "1.0 V", #"ATX_12V",
#                "TR4": "1.0 V", #"CPU核电压",
#                "TR5": "", #"CPU温度",
#                "TR6": "", #"主板温度"
#                "FANIN1": "" #"CPU风扇转速"
#                }
        origin = {"IN0": "", #"内存参考电压"
                "IN2": "", #"SATA控制器电压"
                "IN3": "", #"内存电压",
                "IN5": "", #"CPU管脚电压",
                "IN6": "", #"桥片电压",
                "TR1": "", #"ATX_3V3",
                "TR2": "", #"ATX_5V",
                "TR3": "", #"ATX_12V",
                "TR4": "", #"CPU核电压",
                "TR5": "", #"CPU温度",
                "TR6": "", #"主板温度"
                "FANIN1": "" #"CPU风扇转速"
                }

        opposite = {"IN0": "in0",
                "IN2": "in2",
                "IN3": "in3",
                "IN5": "in5",
                "IN6": "in6",
                "TR1": "in17",
                "TR2": "in18",
                "TR3": "in19",
                "TR4": "in20",
                "TR5": "temp5",
                "TR6": "temp6",
                "FANIN1": "fan1"
                }

        product = {"in17": 2,
                "in18": 3,
                "in19": 12,
                }

        status, output = subprocess.getstatusoutput("sensors")
        for line in output.split("\n"):
            for key in list(opposite.items()):
                if line.split(":")[0] == key[1]:
                    if key[1] in ["in17", "in18", "in19"]:
                        value = (line.split(":")[1]).split("(")[0].strip()
                        origin[key[0]] = value[0:1] + str(float(value[1:-1]) * product[key[1]]) + " V"
                        break
                    if key[1] in ["temp5", "temp6"]:
                        origin[key[0]] = ((line.split(":")[1]).split("(")[0].strip())[0:5] + "℃ "
                        break
                    origin[key[0]] = (line.split(":")[1]).split("(")[0].strip()
                    break
        return origin

if __name__ == "__main__":
    pass
    #cc = DetailInfo()
    #cc.ctoascii('a')
    #cc.strip('a')
    #cc.get_url('a','a')
    #cc.get_computer()
    #cc.get_cpu()
    #cc.get_board()
    #cc.get_memory()
    #cc.get_monitor()
    #cc.get_disk()
    #cc.get_network()
    #cc.get_multimedia()
    #cc.get_dvd()
    #cc.get_usb()
    #pprint(cc.get_sensors())
