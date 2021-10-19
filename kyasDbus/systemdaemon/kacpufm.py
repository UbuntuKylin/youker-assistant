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
from subprocess import PIPE
import threading
import dbus
import dbus.service
import dbus.mainloop.glib
from gi.repository import GLib

import json
import subprocess

from pprint import pprint

from kajsondef import *
from kapolicykit import *
from kathread import *
from utils import *

OBJPATH_CPUFM = '/com/kylin/assistant/cpufm'
INTERFACE_CPUFM = 'com.kylin.assistant.systemdaemon'

class KACpuFM(dbus.service.Object):
    def __init__(self, system_bus, mainloop):
        # Init dbus service.
        dbus.service.Object.__init__(self, system_bus, OBJPATH_CPUFM)

        self.mainloop = mainloop

        self.policykitservice = PolicyKitService()

    @dbus.service.method(INTERFACE_CPUFM, in_signature='', out_signature='', sender_keyword='sender')
    def exit(self, sender = None):
        self.mainloop.quit()

    @dbus.service.signal(INTERFACE_CPUFM, signature='us')
    def signalUpdateInfo(self, status, msg):
        pass

    @dbus.service.method(INTERFACE_CPUFM, in_signature='', out_signature='s', sender_keyword='sender')
    def getCpuFMInfo(self, sender=None):
        asyncObj = KAThread(self.readCpuFMInfo, self.signalUpdateInfo, args=())
        asyncObj.start()
        self.signalUpdateInfo(0, asyncObj.getResult())
        return str(asyncObj.getResult())

    @dbus.service.method(INTERFACE_CPUFM, in_signature='', out_signature='as', sender_keyword='sender')
    def get_cpufreq_scaling_governer_list(self, sender=None):
        cpulist = []
        if not os.path.exists("/sys/devices/system/cpu/cpu0/cpufreq/scaling_available_governors") :
            return cpulist
        cmd = "cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_available_governors"
        fp = os.popen(cmd)
        msg = fp.read().strip('\n')
        fp.close()
        if msg not in ['', None]:
            cpulist = msg.split(' ')
        
        if not os.path.exists("/sys/devices/system/cpu/cpu0/cpufreq/scaling_setspeed"):
            if 'userspace' in cpulist:
                cpulist.remove('userspace')
        else:
            cmd = "cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_setspeed"
            fp = os.popen(cmd)
            msg = fp.read().strip('\n')
            fp.close()
            if msg not in ['',None]:
                if msg == '<unsupported>' and 'userspace' in cpulist:
                    cpulist.remove('userspace')
        
        if Judgment_HW990() and ('userspace' in cpulist):
            cpulist.remove('userspace')
        return cpulist

    @dbus.service.method(INTERFACE_CPUFM, in_signature='', out_signature='s', sender_keyword='sender')
    def readCpuFMInfo(self, sender=None):
        cpuFMInfo = {Cpufm_Root:{}}
        cpuFMInfo[Cpufm_Root][Cpufm_Models] = self.get_cpufreq_scaling_governer_list()
        cpuFMInfo[Cpufm_Root][Cpufm_Freqs] = self.get_cpufreq_scaling_available_frequencies()
        cpuFMInfo[Cpufm_Root][Cpufm_Current_Model] = self.get_current_cpufreq_scaling_governer()
        cpuFMInfo[Cpufm_Root].update(self.get_cpu_average_frequency())
        strJson = json.dumps(cpuFMInfo)
        return strJson

    @dbus.service.method(INTERFACE_CPUFM, in_signature='', out_signature='as', sender_keyword='sender')
    def get_cpufreq_scaling_available_frequencies(self, sender=None):
        cpulist = []
        if not os.path.exists("/sys/devices/system/cpu/cpu0/cpufreq/scaling_available_frequencies") :
            return cpulist
        cmd = "cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_available_frequencies"
        fp = os.popen(cmd)
        msg = fp.read().strip()
        fp.close()
        if msg not in ['', None]:
            cpulist = msg.split(' ')
        
        return cpulist

    @dbus.service.method(INTERFACE_CPUFM, in_signature='', out_signature='s', sender_keyword='sender')
    def get_current_cpufreq_scaling_governer(self, sender=None):
        if not os.path.exists("/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor") :
            return ""
        cmd = "cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor"
        fp = os.popen(cmd)
        msg = fp.read().strip('\n')
        fp.close()
        return msg

    # cpu频率的单位换算
    def num_convert(self,s):
        if not s.isdigit() :
            return "0Ghz"
        num = int(s)
        unit=""
        for i in range(0,10):
            if( i == 1 ):
                unit = "Mhz"
            elif ( i == 2):
                unit = "Ghz"

            if(num >= 10):
                num=round(num/1000,1)
            else:
                break
            
        return str(num)+unit

    def get_cpu_average_frequency(self):
        origin = {Cpufm_Average_Corefreq:""}

        if(not os.path.exists("/sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq")):
            return origin

        v = 0 
        i = 0
        fpath = os.path.expanduser("/sys/devices/system/cpu/")
        for line in os.listdir(fpath): #遍历/sys/devices/system/cpu/下的所有文件
            line = line.strip('\n')
            #pattern = re.compile(r'cpu.*[0-9]$')
            pattern = re.compile(r'cpu.*\d\Z') #筛选cpu的每个核心的配置文件
            m = pattern.match(line)
            if m:
                filepath = "/sys/devices/system/cpu/%s/cpufreq/scaling_cur_freq" % line
                if os.path.exists(filepath):
                    f = open(filepath,'r')
                    curFreq = f.readline().strip()
                    if curFreq.isdigit() :
                        v += int(curFreq)
                        i = i + 1

        v = self.num_convert(str(v//i))
        origin[Cpufm_Average_Corefreq]=v

        return origin
    
    @dbus.service.method(INTERFACE_CPUFM, in_signature='s', out_signature='s', sender_keyword='sender')
    def adjust_cpufreq_scaling_governer(self, value, sender=None):
        cpuFMSetting = json.loads(value)
        validFreqList = self.get_cpufreq_scaling_available_frequencies()
        validFMList = self.get_cpufreq_scaling_governer_list()
        cpuFMModel = ""
        cpuFMFreq = ""
        if cpuFMSetting != None :
            cpuFMModel = cpuFMSetting[Cpufm_Current_Model]
            cpuFMFreq = cpuFMSetting[Cpufm_CurFreq]
        if not validFMList or cpuFMModel not in validFMList or \
            (cpuFMModel == Cpufm_Model_Userspace and (not validFreqList or (cpuFMFreq not in validFreqList))) :
            return "Failed,param mismatch!"
        fpath = os.path.expanduser("/sys/devices/system/cpu/")
        for line in os.listdir(fpath):
            line = line.strip('\n')
            #pattern = re.compile(r'cpu.*[0-9]$')
            pattern = re.compile(r'cpu.*\d\Z')
            m = pattern.match(line)
            if m:
                filepath = "/sys/devices/system/cpu/%s/cpufreq/scaling_governor" % line
                path = "/sys/devices/system/cpu/%s/cpufreq/scaling_setspeed" % line
                if os.path.exists(filepath):
                    if(cpuFMModel == Cpufm_Model_Userspace):
                        cmd = 'echo %s > %s' % (cpuFMModel, filepath)
                        os.system(cmd)
                        cmd = 'echo %s > %s' % (cpuFMFreq, path)
                        os.system(cmd)
                    else:
                        cmd = 'echo %s > %s' % (cpuFMModel, filepath)
                        os.system(cmd)
        return "Success!"

if __name__ == "__main__":
    pass
