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
import binascii

KILOBYTE_FACTOR = 1000.0
MEGABYTE_FACTOR = (1000.0 * 1000.0)
GIGABYTE_FACTOR = (1000.0 * 1000.0 * 1000.0)
TERABYTE_FACTOR = (1000.0 * 1000.0 * 1000.0 * 1000.0)

def Judgment_HW990():
    if os.path.exists("/proc/hardware"):
        with open("/proc/hardware",'r') as fd:
            info = fd.readline()
            if info.find("HUAWEI Kirin 990") >= 0 or info.find("kirin990") >= 0 or info.find("HUAWEI Kirin 9006C") >= 0:
                return True
            else:
                return False
    else:
        return False

def Judgment_HW9A0():
    if os.path.exists("/proc/hardware"):
        with open("/proc/hardware",'r') as fd:
            info = fd.readline()
            if info.find("HUAWEI Kirin 9006C") >= 0:
                return True
            else:
                return False
    else:
        return False

def myctoascii(buf):
    ch = bytes(buf.encode('utf-8'))
    asci = binascii.b2a_hex(ch)
    asci = int(asci,16)
    return asci

def mystrip(s):
    if(len(s) == 0):
        return s
    while len(s) > 0 and myctoascii(s[0]) <= 32:
        s = s[1: ]
    k = len(s)
    while len(s) > 0 and myctoascii(s[k-1]) <= 32:
        s = s[ :k-1]
        k = len(s)
    i = 0
    while i < len(s):
        if myctoascii(s[i]) < 32:
            s = s[ :i] + s[i+1: ]
            i -= 1
        i += 1
    return s

def get_url(v,p):
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
        "JINGJIA":["JJM"],
        "Wuhan Digital Engineering":["WDE"],
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
        "LOONGSON":["Loongson"],
        "HISILICON":["HiSilicon"],
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

    tmp = re.findall("JingJia", p)
    if tmp :
        url = vendors.get(tmp[0].upper())
        if url:
            return url[0]
    tmp = re.findall("Loongson", p, flags=re.IGNORECASE)
    if tmp :
        url = vendors.get(tmp[0].upper())
        if url:
            return url[0]

    tmp = re.findall("Wuhan Digital Engineering", p)
    if tmp :
        url = vendors.get(tmp[0].upper())
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