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

import sys
import os
import re
import math
import binascii
import platform
import gettext
from gettext import gettext as _
from gettext import ngettext as __
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
#   Vga_product         显卡型号
#   Vga_vendor          显卡产商
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
#   NetSerial           MAC地址
#   NetCapacity         最大带宽
#   NetIp               IP地址
#   NetLink             连接状态

    def ctoascii(self,buf):
        ch = str(buf)
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
            if s[i] < 32:
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

    def get_url(self,v,p):
        vendors = {
#PU产商
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
        Com['node'], Com['uptime'], Com['system'], Com['platform'],Com['architecture'], Com['release'], Com['machine'] = platform.node(),uptime,platform.system(),platform.platform(),platform.architecture()[0],platform.release(),platform.machine()
        return Com

    def get_cpu(self):
        # CPU
        Cpu = {}
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
                         clflush_size = filter(str.isdigit,clflush_size)
                    elif line.rstrip('\n').startswith('cache size'):
                         cache_size = line.rstrip('\n').split(':')[1]
                         cache_size = filter(str.isdigit,cache_size)
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
        MemInfo,MemWidth,Memnum,MemSlot,MemProduct,MemVendor,MemSerial,MemSize,BioVendor = "","","","","","",'','',''
        hw = os.popen("dmidecode -t memory")
        memory = hw.read()
        hw.close()
        num = 0
        memory = memory[memory.index("Memory Device\n")+len("Memory Device\n"):]
        if memory :
            mark = re.findall("Data Width: (.*)",memory)
            if mark :
                for k in mark :
                    if not k == 'Unknown':
                        num += 1
                        if MemWidth :
                            MemWidth += '/' + k
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
                            MemSlot += '/'+ tmp[i-1]
                        else :
                            MemSlot = tmp[i-1]
            tmp = re.findall("Part Number: (.*)",memory)
            i = 0
            if tmp :
                for k in mark :
                    i += 1
                    if not k == 'Unknown':
                        if MemProduct :
                            MemProduct += '/' + tmp[i-1]
                        else :
                            MemProduct = tmp[i-1]
            tmp = re.findall("Manufacturer: (.*)",memory)
            i = 0
            if tmp :
                for k in mark :
                    i += 1
                    if not k == 'Unknown':
                        if MemVendor :
                            MemVendor += '/' + tmp[i-1]
                        else :
                            MemVendor = tmp[i-1]
            tmp = re.findall("Serial Number: (.*)",memory)
            i = 0
            if tmp :
                for k in mark :
                    i += 1
                    if not k == 'Unknown':
                        if MemSerial :
                            MemSerial += '/' + tmp[i-1]
                        else :
                            MemSerial = tmp[i-1]
            tmp = re.findall("Size: (.*)",memory)
            i = 0
            if tmp :
                for k in mark :
                    i += 1
                    if not k == 'Unknown':
                        if MemSize :
                            MemSize += '/' + tmp[i-1]
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
                            MemInfo += '/' + tmp0[i-1] + ' ' + tmp1[i-1] + ' ' + tmp2[i-1] + ' ' + tmp3[i-1]
                        else :
                            MemInfo = tmp0[i-1] + ' ' + tmp1[i-1] + ' ' + tmp2[i-1] + ' ' + tmp3[i-1]
        Mem["MemInfo"],Mem["MemWidth"],Mem["MemSlot"],Mem["MemProduct"],Mem["MemVendor"],Mem["MemSerial"],Mem["MemSize"],Mem["Memnum"] = MemInfo,self.strip(MemWidth),self.strip(MemSlot),self.strip(MemProduct),self.strip(MemVendor),self.strip(MemSerial),self.strip(MemSize),self.strip(Memnum)
        return Mem

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
                if not ret.get("Mon_product"):
                    ret["Mon_product"] = tmp[0][0] + " " + tmp[0][1]
                if not ret.get("Mon_vendor"):
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
                if not ret.get("Mon_chip"):
                    ret["Mon_chip"] = tmp[0]
        n = os.popen('lspci | grep VGA')
        vga = n.read()
        n.close()
        if vga :
            tmp = vga[vga.index('VGA compatible controller: ')+len('VGA compatible controller: '):]
            if tmp :
                ret['Vga_product'] = tmp
            tmp = vga[ :vga.index('VGA compatible controller:')-1]
            if tmp :
                ret['Vga_businfo'] = 'pci@0000:' + tmp
        
        if (ret.get('Mon_vendor')):
            if (ret.get('Mon_product')):
                ret['Mon_vendor'] = self.get_url(ret['Mon_vendor'],ret['Mon_product'])
            else :  
                ret['Mon_vendor'] = self.get_url(ret['Mon_vendor'],'')
        if (ret.get('Vga_product')):
            ret['Vga_vendor'] = self.get_url('',ret['Vga_product'])
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
        li =  os.popen("ls /dev/sd?")
        line = li.read()
        li.close()
        li = os.popen("ls /dev/hd?")
        line += li.read()
        li.close()
        if line :
            line = line.split('\n')
            for k in line :
                if k :
                    st = os.popen("hdparm -i %s" % k)
                    strin = st.read()
                    st.close()
                    tmp = re.findall("Model=(.*), F",strin)
                    if not tmp :
                        continue
                    else :
                        if DiskProduct :
                            DiskProduct += '/'+tmp[0]
                        else :
                            DiskProduct = tmp[0]
                        i = 0
                        while i < len(disk_manufacturers):
                            ven = re.compile(disk_manufacturers[i],re.I)
                            tm = ven.findall(tmp[0])
                            if tm :
                                if DiskVendor :
                                    DiskVendor += '/' + disk_manufacturers[i+1]
                                else :
                                    DiskVendor += disk_manufacturers[i+1]
                                i = len(disk_manufacturers)
                            i += 2
                    tmp = re.findall("FwRev=(.*), ",strin)
                    if tmp :
                        if DiskFw :
                            DiskFw += '/' +tmp[0]
                        else :
                            DiskFw = tmp[0]
                    tmp = re.findall("SerialNo=(.*)",strin)
                    if tmp :
                        if DiskSerial :
                            DiskSerial += '/' +tmp[0]
                        else :
                            DiskSerial = tmp[0]
                    ds = os.popen("fdisk -l %s" % k)
                    d = ds.read()
                    ds.close()
                    tmp = re.findall("%s: (.*)," % k,d)
                    if tmp:
                        if DiskCapacity :
                            DiskCapacity += '/' +tmp[0]
                        else :
                            DiskCapacity = tmp[0]
                    disknum  += 1
                    if DiskName :
                        DiskName += '/' + k
                    else :
                        DiskName = k
        dis['DiskNum'],dis['DiskProduct'],dis['DiskVendor'],dis['DiskCapacity'],dis['DiskName'],dis['DiskFw'],dis['DiskSerial'] = self.strip(str(disknum)),self.strip(DiskProduct),self.strip(DiskVendor),self.strip(DiskCapacity),self.strip(DiskName),self.strip(DiskFw),self.strip(DiskSerial)
        return dis

    def get_network(self):
        net = {}
        NetProduct,NetVendor,NetBusinfo,NetLogicalname,NetSerial,NetIp,NetLink,NetCapacity = '','','','','','','',''
        n = os.popen('lspci | grep Ether')
        network = n.read()
        n.close()
        if network :
            i = 0
            tmp = network[network.index('Ethernet controller: ')+len('Ethernet controller: '):]
            while i < len(tmp) and (self.ctoascii(tmp[i]) < 48 or self.ctoascii(tmp[i]) > 57):
                i += 1
            while i > 0 and (not self.ctoascii(tmp[i]) == 32):
                i -= 1
            if i :
                NetProduct = tmp[i: ]
                NetVendor = tmp[ :i]
            tmp = network[ :network.index('Ethernet controller: ')-1] 
            if tmp :
                NetBusinfo = 'pci@0000:' + tmp
        n = os.popen('dmesg | grep eth')
        network = n.read()
        n.close()
        if network :
            tmp = network[network.index('eth'):]
            if tmp :
                NetLogicalname = tmp[0:4]
            tmp = re.findall("\w\w:\w\w:\w\w:\w\w:\w\w:\w\w",network)
            if tmp :
                NetSerial = tmp[0]
        n = os.popen('ifconfig eth | grep "inet " ')
        network = n.read()
        n.close()
        if network :
            tmp = network[network.index(':')+len(':') : ]
            tmp = tmp[: tmp.index(' ')+len(' ') ]
            if tmp :
                NetIp = tmp
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
        NetVendor = self.get_url(NetVendor,NetProduct)
        net['NetProduct'],net['NetVendor'],net['NetBusinfo'],net['NetLogicalname'],net['NetSerial'],net['NetIp'],net['NetLink'],net['NetCapacity'] = self.strip(NetProduct),self.strip(NetVendor),self.strip(NetBusinfo),self.strip(NetLogicalname),self.strip(NetSerial),self.strip(NetIp),self.strip(NetLink),self.strip(NetCapacity)
        return net

if __name__ == "__main__":
    cc = DetailInfo()
    cc.ctoascii('a')
    cc.strip('a')
    cc.get_url('a','a')
    cc.get_computer()
    cc.get_cpu()
    cc.get_board()
    cc.get_memory()
    cc.get_monitor()
    cc.get_disk()
    cc.get_network()
