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
import binascii
import ctypes
import MyCppModule

class Dmi:
    def ctoascii(self,buf):
        ch = str(buf)
        asci = binascii.b2a_hex(ch)
        asci = int(asci,16)
        return asci

    def get_efi_systab_smbios(self):
        result = 0
        if os.path.exists("/sys/firmware/efi/systab"):
            with open("sys/firmware/efi/systab") as f:
                for line in f:
                    if line.strip():
                        if line.rstrip("\n").startswith("SMBIOS"):
                            s = line.restrip("\n").split("=")[1]
                            result = int(s,16)
                            result = hex(result)
        elif os.path.exists("/proc/efi/systab"):
            with open("/proc/efi/systab") as f:
                for line in f:
                    if line.strip():
                        if line.rstrip("\n").startswith("SMBIOS"):
                            s = line.restrip("\n").split("=")[1]
                            result = int(s,16)
                            result = hex(result)
        return result

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

    def dmi_string(self, bp, length, s,slen):
        if s == "" :
            return ""
        i = self.ctoascii(length)
        t = self.ctoascii(s)
        while t > 1:
            j = 0
            while i+j < slen and bp[i + j] != '$':
                j+= 1
            i += j
            i += 1
            t -= 1
        n = 0
        while i+n < slen and bp[i + n] != '$':
            n += 1
        return self.strip(bp[i:i+n])


    def dmi_table(self,fd, base, slen, num, dmiversionmaj, dmiversionmin):
        i=0
        dm = {}
        if slen == 0 :
            return
#        fd.seek(base)
#        buf = fd.read(slen)
        buf = MyCppModule.MyCppFun1(base,slen)
        data = buf
#        data = buf.replace('$','\0')
        MemSlot,MemProduct,MemVendor,MemSerial,MemSize = "","","","",""
        while i+4 <= slen :
            typ = data[i]
            length = data[i+1]
            handle = data[i+2:i+4]
            choose = self.ctoascii(typ)
            if choose == 1 :
#System Information Block
                ComVendor = self.dmi_string(data[i:],length,data[i+4],slen-i)
                ComProduct = self.dmi_string(data[i:],length,data[i+5],slen-i)
                ComVersion = self.dmi_string(data[i:],length,data[i+6],slen-i)
                ComSerial = self.dmi_string(data[i:],length,data[i+7],slen-i)
                dm["ComVendor"],dm["ComProduct"],dm["ComVersion"],dm["ComSerial"] = ComVendor,ComProduct,ComVersion,ComSerial

            elif choose == 4 :
#CPU                
                CpuSlot = self.dmi_string(data[i:],length,data[i+4],slen-i)
                CpuVersion = self.dmi_string(data[i:],length,data[i+0x10],slen-i)
                CpuVendor = self.dmi_string(data[i:],length,data[i+7],slen-i)
                dm["CpuSlot"],dm["CpuVersion"],dm["CpuVendor"] = CpuSlot,CpuVersion,CpuVendor

            elif choose == 2 :
#Board Information Block
                BoaProduct = self.dmi_string(data[i:],length,data[i+5],slen-i)
                BoaVendor = self.dmi_string(data[i:],length,data[i+4],slen-i)
                BoaSerial = self.dmi_string(data[i:],length,data[i+7],slen-i)
                dm["BoaProduct"],dm["BoaVendor"],dm["BoaSerial"] = BoaProduct,BoaVendor,BoaSerial

            elif choose == 0 :
#BIOS
                BioVendor = self.dmi_string(data[i:],length,data[i+4],slen-i)
                BioVersion = self.dmi_string(data[i:],length,data[i+5],slen-i)
                BioRelease = self.dmi_string(data[i:],length,data[i+8],slen-i)
                dm["BioVendor"],dm["BioVersion"],dm["BioRelease"] = BioVendor,BioVersion,BioRelease

            elif choose == 17 :
#Memory Device
                data13 = self.ctoascii(data[i+13])
                data12 = self.ctoascii(data[i+12])
                u = data13 << 8 | data12
                if u != 0xffff :
                    if u & 0x8000 == 0 :
                        size = 1024 * (u & 0x7fff) * 1024
                    else :
                        size = 1024 * (u & 0x7fff) 
                if MemSlot:
                    MemSlot = MemSlot + '/' + self.dmi_string(data[i:],length,data[i+16],slen-i)
                else:
                    MemSlot = self.dmi_string(data[i:],length,data[i+16],slen-i)
                l = self.ctoascii(length)
                if l > 26 :
                    if MemProduct:
                        MemProduct = MemProduct + '/' + self.dmi_string(data[i:],length,data[i+26],slen-i)
                    else:
                        MemProduct = self.dmi_string(data[i:],length,data[i+26],slen-i)
                if l > 23 :
                    if MemVendor:
                        MemVendor = MemVendor + '/' + self.dmi_string(data[i:],length,data[i+23],slen-i)
                    else:
                        MemVendor = self.dmi_string(data[i:],length,data[i+23],slen-i)
                if l > 24 :
                    if MemSerial:
                        MemSerial = MemSerial + '/' + self.dmi_string(data[i:],length,data[i+24],slen-i)
                    else:
                        MemSerial = self.dmi_string(data[i:],length,data[i+24],slen-i)
                if MemSize:
                    MemSize = MemSize + '/' + str(size)
                else:
                    MemSize = str(size)
                dm["MemSlot"],dm["MemProduct"],dm["MemVendor"],dm["MemSerial"],dm["MemSize"] = MemSlot,MemProduct,MemVendor,MemSerial,MemSize

            i += self.ctoascii(length)
            while i+4 < slen and (data[i]!= '$' or data[i+1]!= '$') :
                i += 1
            i += 2
            #f.close()
        return dm

    def scan_dmi(self):
        fp = self.get_efi_systab_smbios()
        smmajver = 0
        smminver = 0
        dmimaj = 0
        dmimin = 0
        if (fp <= 0):
            efi = False
            fp = 0xE0000
        fp -= 16
        with open("/dev/mem","r") as fd:
            while efi or fp < 0xFFFE0:
                fp += 16
                fd.seek(fp)
                buf = fd.read(20)
                if buf[0:4] == "_SM_":
                    smmajver = buf[6]
                    smminver = buf[7]
                    f = open("/tmp/wb.txt","a+")
                    print >> f,"000000000"
                    print >> f,buf
                    f.close()
                elif smmajver and buf[0:5] == "_DMI_":
                    buf6 = self.ctoascii(buf[6])
                    buf7 = self.ctoascii(buf[7])
                    buf8 = self.ctoascii(buf[8])
                    buf9 = self.ctoascii(buf[9])
                    buf10 = self.ctoascii(buf[10])
                    buf11 = self.ctoascii(buf[11])
                    buf12 = self.ctoascii(buf[12])
                    buf13 = self.ctoascii(buf[13])
                    buf14 = self.ctoascii(buf[14])
                    num = buf13 << 8 | buf12
                    slen = buf7 << 8 | buf6
                    base = buf11 << 24 | buf10 << 16 | buf9 << 8 | buf8
                    if buf[14]:
                        dmimaj = buf14 >> 4
                        dmimin = buf14 & 0x0F
                    else:
                        dmimaj = smmajver
                        dmimin = smminver
                    f = open("/tmp/wb.txt","a+")
                    print >> f,"11111111111"
                    print >> f,buf11
                    print >> f,buf10
                    print >> f,buf9
                    print >> f,buf8
                    print >> f,"22222222"
                    print >> f,buf
                    print >> f,num
                    print >> f,slen
                    print >> f,base
                    f.close()
                    return self.dmi_table(fd, base, slen, num, dmimaj,dmimin)

if __name__ == "__main__":
    a = "A"
    fd = open("/dev/mem","r")
    objc = Dmi()
    objc.get_efi_systab_smbios()
    objc.ctoascii(a)
    objc.strip(a)
    objc.scan_dmi()
    objc.dmi_table(fd,2,3,4,5,6)
    objc.dmi_string('abcd','a','a',4)
    fd.close()
