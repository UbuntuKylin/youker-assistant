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

OBJPATH_DEVMONITOR = '/com/kylin/assistant/devmonitor'
INTERFACE_DEVMONITOR = 'com.kylin.assistant.systemdaemon'
CPUSTAT_FILE = "/proc/stat"

class KADevMonitor(dbus.service.Object):
    def __init__(self, system_bus, mainloop):
        # Init dbus service.
        dbus.service.Object.__init__(self, system_bus, OBJPATH_DEVMONITOR)

        self.mainloop = mainloop

        self.policykitservice = PolicyKitService()

        self.preTotalTime = 0
        self.preWorkTime = 0
        self.totalTime = 0
        self.workTime = 0
        self.cpuPercent = 0
        self.cpuTimer = threading.Timer(0.3, self.chkCpuUsageTimer)
        self.cpuTimer.start()

    @dbus.service.method(INTERFACE_DEVMONITOR, in_signature='', out_signature='', sender_keyword='sender')
    def exit(self, sender = None):
        self.mainloop.quit()

    @dbus.service.signal(INTERFACE_DEVMONITOR, signature='us')
    def signalUpdateInfo(self, status, msg):
        pass

    @dbus.service.method(INTERFACE_DEVMONITOR, in_signature='', out_signature='s', sender_keyword='sender')
    def getDevMonitorInfo(self, sender=None):
        asyncObj = KAThread(self.readDevMonitorInfo, self.signalUpdateInfo, args=())
        asyncObj.start()
        self.signalUpdateInfo(0, asyncObj.getResult())
        return str(asyncObj.getResult())

    @dbus.service.method(INTERFACE_DEVMONITOR, in_signature='', out_signature='s', sender_keyword='sender')
    def getDevTempsInfo(self, sender=None):
        return ""

    @dbus.service.method(INTERFACE_DEVMONITOR, in_signature='', out_signature='s', sender_keyword='sender')
    def readDevMonitorInfo(self, sender=None):
        devMonitorInfo = {DEVMONITOR_ROOT:{}}
        devTempsInfo = []
        devTempsInfo.append(self.getCpuTemps())
        devMonitorInfo[DEVMONITOR_ROOT][DEVMONITOR_DEVTEMPS] = devTempsInfo
        devUsageInfo = []
        devUsageInfo.append(self.readCpuUsage())
        devUsageInfo.append(self.readMemUsage())
        devMonitorInfo[DEVMONITOR_ROOT][DEVMONITOR_DEVUSAGE] = devUsageInfo
        strJson = json.dumps(devMonitorInfo)
        return strJson

    def chkCpuUsageTimer(self):
        cmd = "cat " + CPUSTAT_FILE
        fp = os.popen(cmd)
        msg = fp.read()
        fp.close()
        result = re.findall('cpu\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)\s*(\S+)', msg);
        self.preTotalTime = self.totalTime
        self.preWorkTime = self.workTime
        if result :
            user = int(result[0][0])
            nice = int(result[0][1])
            system = int(result[0][2])
            idle = int(result[0][3])
            iowait = int(result[0][4])
            irq = int(result[0][5])
            softirq = int(result[0][6])
            steal = int(result[0][7])
            guest = int(result[0][8])
            guestnice = int(result[0][9])
            self.workTime = user + nice + system
            self.totalTime = user + nice + system + idle + iowait + irq + softirq + steal
        if self.preTotalTime != 0 and self.preWorkTime != 0 :
            self.cpuPercent = int(((self.workTime - self.preWorkTime) * 1000 / (self.totalTime - self.preTotalTime)))/10
        else :
            self.cpuPercent = 0
        ## next timer
        self.cpuTimer = threading.Timer(1, self.chkCpuUsageTimer)
        self.cpuTimer.start()

    def readCpuUsage(self):
        cpuUsage = {}
        cpuUsage[DEVMONITOR_DEVUSAGE_NAME] = "CPU"
        cpuUsage[DEVMONITOR_DEVUSAGE_USED] = str(self.cpuPercent)
        cpuUsage[DEVMONITOR_DEVUSAGE_TOTAL] = str(100)
        return cpuUsage
    
    def readMemUsage(self):
        cmd = "free"
        fp = os.popen(cmd)
        msg = fp.read()
        fp.close()
        memUsedByte = 0
        memTotalByte = 0
        memLeftByte = 0
        memUsedPercent = 0
        msgLines = msg.split("\n")
        if msgLines :
            for line in msgLines :
                infoArray = re.split("\s+",line)
                if infoArray and len(infoArray) >= 7 and infoArray[1].isdigit() and infoArray[6].isdigit() : #is mem info
                    memLeftByte = int(infoArray[6])
                    memTotalByte = int(infoArray[1])
                    memUsedByte = memTotalByte - memLeftByte
                    if memTotalByte != 0 :
                        memUsedPercent = int(memUsedByte*1000/memTotalByte)/10
                    else :
                        memUsedPercent = 0
        memUsage = {}
        memUsage[DEVMONITOR_DEVUSAGE_NAME] = "MEM"
        memUsage[DEVMONITOR_DEVUSAGE_USED] = str(memUsedPercent)
        memUsage[DEVMONITOR_DEVUSAGE_TOTAL] = str(100)
        return memUsage

    def getCpuTemps(self):
        sensorTemps = []
        sensorTempAvg = 0
        sensorTempHigh = 0
        sensorTempCrit = 0
        cpuTemps = {}
        status, output = subprocess.getstatusoutput("sensors")
        if(status != -1):
            #Core 0:        +35.0°C  (high = +84.0°C, crit = +100.0°C)
            result = re.findall('Core\s*[0-9]+:\s*(\S+)°C\s*\(high\s*=\s*(\S+)°C,\s*crit\s*=\s*(\S+)°C\)', output)
            #print(result)
            if result :
                for line in result:
                    oneCoreTemp = float(line[0])
                    sensorTempHigh = float(line[1])
                    sensorTempCrit = float(line[2])
                    sensorTemps.append(oneCoreTemp)
                    sensorTempAvg += oneCoreTemp
                if len(sensorTemps) > 0 :
                    sensorTempAvg = int(sensorTempAvg*10/len(sensorTemps))/10
                    cpuTemps[DEVMONITOR_DEVTEMP] = str(sensorTempAvg)
                    cpuTemps[DEVMONITOR_DEVTEMP_HIGH] = str(sensorTempHigh)
                    cpuTemps[DEVMONITOR_DEVTEMP_CRIT] = str(sensorTempCrit)
                    cpuTemps[DEVMONITOR_DEVTEMP_NAME] = "CPU"
        return cpuTemps

if __name__ == "__main__":
    pass
