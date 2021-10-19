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
import dbus
import dbus.service
import dbus.mainloop.glib
from gi.repository import GLib

import subprocess

from karealization import *
from kapolicykit import *
from kathread import *
from utils import *

from memoryinfothread import MemoryInfo
from networkadaptorthread import NetworkAdaptor
from audioadaptorthread import AudioAdaptor
from kamonitorthread import KAMonitor
from kaharddiskinfo import KAHarddiskInfo
from kagraphicscardinfo import KAGraphicsCardInfo
from systemboardthread import *
from kakeyboardinfo import KAKeyboardInfo
from kamouseinfo import KAMouseInfo
from kacdrominfo import KACDRomInfo
from kamachineinfo import KAMachineInfo
from kabluetoothinfo import KABluetoothInfo
from kafaninfo import KAFanInfo
from kacmdtool import KACmdTool
from kacamerainfo import KACameraInfo
from kabatteryinfo import KABatteryInfo

OBJPATH = '/com/kylin/assistant/systemdaemon'
INTERFACE = 'com.kylin.assistant.systemdaemon'

THREAD_INDEX_OUTLINE = 0
THREAD_INDEX_HARDWARE = 1
THREAD_INDEX_MEMORY = 2
THREAD_INDEX_NETWORK = 3
THREAD_INDEX_AUDIOADAPTER = 4
THREAD_INDEX_SYSTEMBOARD = 5
THREAD_INDEX_RELOADLSHW = 6
THREAD_INDEX_MAX = 7

class HardwareInfo(dbus.service.Object):
    def __init__(self, system_bus, mainloop):
        # Init dbus service.
        dbus.service.Object.__init__(self, system_bus, OBJPATH)
        self.mainloop = mainloop

        self.policykitservice = PolicyKitService()

        self.hwobj = DetailInfo()

        self.cmdtool = KACmdTool()
        #self.cmdtool.loadInfoFromLshw()

        self.threadPool = [None] * THREAD_INDEX_MAX

    @dbus.service.method(INTERFACE, in_signature='', out_signature='', sender_keyword='sender')
    def exit(self, sender = None):
        self.mainloop.quit()

    @dbus.service.signal(INTERFACE, signature='s')
    def signalGettingInfo(self, msg):
        pass

    @dbus.service.method(INTERFACE, in_signature='', out_signature='s', sender_keyword='sender')
    def mdObtainProcessorInfo(self, sender=None):
        return self.hwobj.getProcessorInfo()

    @dbus.service.method(INTERFACE, in_signature='', out_signature='s', sender_keyword='sender')
    def mdObtainMemoryInfo(self, sender=None):
        self.threadPool[THREAD_INDEX_MEMORY] = KAThread(MemoryInfo(self.cmdtool).getMemInfo, None, args=())
        #改为信号的方式
        self.threadPool[THREAD_INDEX_MEMORY].start()
        self.threadPool[THREAD_INDEX_MEMORY].join()
        return self.threadPool[THREAD_INDEX_MEMORY].getResult()

    @dbus.service.method(INTERFACE, in_signature='', out_signature='s', sender_keyword='sender')
    def mdObtainNetworkAdaptorInfo(self, sender=None):
        self.threadPool[THREAD_INDEX_NETWORK] = KAThread(NetworkAdaptor(self.cmdtool).getNetworkAdaptorInfo, None, args=())
        #改为信号的方式
        self.threadPool[THREAD_INDEX_NETWORK].start()
        self.threadPool[THREAD_INDEX_NETWORK].join()
        return self.threadPool[THREAD_INDEX_NETWORK].getResult()

    @dbus.service.method(INTERFACE, in_signature='', out_signature='s', sender_keyword='sender')
    def mdObtainAudioAdaptorInfo(self, sender=None):
        self.threadPool[THREAD_INDEX_AUDIOADAPTER] = KAThread(AudioAdaptor(self.cmdtool).getAudioAdaptorInfo, None, args=())
        #改为信号的方式
        self.threadPool[THREAD_INDEX_AUDIOADAPTER].start()
        self.threadPool[THREAD_INDEX_AUDIOADAPTER].join()
        return self.threadPool[THREAD_INDEX_AUDIOADAPTER].getResult()

    # harddisk
    @dbus.service.signal(INTERFACE, signature='us')
    def signalHDUpdateInfo(self, status, msg):
        pass

    @dbus.service.method(INTERFACE, in_signature='', out_signature='s', sender_keyword='sender')
    def readHDInfo(self, sender=None):
        harddiskInfo = KAHarddiskInfo(self.cmdtool)
        hdInfo = {"list":harddiskInfo.get_disk()}
        strJson = json.dumps(hdInfo)
        return strJson

    #memory info
    @dbus.service.signal(INTERFACE, signature='us')
    def signalMemUpdateInfo(self, status, msg):
        pass

    @dbus.service.method(INTERFACE, in_signature='', out_signature='s', sender_keyword='sender')
    def readMemInfo(self, sender=None):
        memObj = MemoryInfo(self.cmdtool)
        memInfo = memObj.getMemInfo()
        return memInfo

    #processor info
    @dbus.service.signal(INTERFACE, signature='us')
    def signalProcUpdateInfo(self, status, msg):
        pass

    @dbus.service.method(INTERFACE, in_signature='', out_signature='s', sender_keyword='sender')
    def readProcInfo(self, sender=None):
        return self.hwobj.getProcessorInfo()

    #network card info
    @dbus.service.signal(INTERFACE, signature='us')
    def signalNWUpdateInfo(self, status, msg):
        pass

    @dbus.service.method(INTERFACE, in_signature='', out_signature='s', sender_keyword='sender')
    def readNWInfo(self, sender=None):
        return self.mdObtainNetworkAdaptorInfo()

    #voice card info
    @dbus.service.signal(INTERFACE, signature='us')
    def signalVCUpdateInfo(self, status, msg):
        pass

    @dbus.service.method(INTERFACE, in_signature='', out_signature='s', sender_keyword='sender')
    def readVCInfo(self, sender=None):
        return self.mdObtainAudioAdaptorInfo()

    #mother board info
    @dbus.service.signal(INTERFACE, signature='us')
    def signalMBUpdateInfo(self, status, msg):
        pass

    @dbus.service.method(INTERFACE, in_signature='', out_signature='s', sender_keyword='sender')
    def readMBInfo(self, sender=None):
        motherBoard = {}
        systemBoardInfo = SystemBoard()
        boardInfo = systemBoardInfo.getBaseBoardInfo()
        if Board_Manufacturer in boardInfo :
            motherBoard[MBI_MANUFACTURER] = boardInfo[Board_Manufacturer]
        if Board_Product in boardInfo :
            motherBoard[MBI_NAME] = boardInfo[Board_Product]
        if Board_Chipset in boardInfo :
            motherBoard[MBI_CHIPSET] = boardInfo[Board_Chipset]
        if Board_Version in boardInfo :
            motherBoard[MBI_VERSION] = boardInfo[Board_Version]
        if Board_Serial in boardInfo :
            motherBoard[MBI_SERIALNUM] = boardInfo[Board_Serial]
        biosInfo = systemBoardInfo.getBiosInfo()
        if BIOS_Manufacturer in biosInfo :
            motherBoard[MBI_BIOSMANUFACTURER] = biosInfo[BIOS_Manufacturer]
        if BIOS_Version in biosInfo :
            motherBoard[MBI_BIOSVERSION] = biosInfo[BIOS_Version]
        if BIOS_ReleaseDate in biosInfo :
            motherBoard[MBI_PUBDATE] = biosInfo[BIOS_ReleaseDate]
        strJson = json.dumps(motherBoard)
        return strJson

    #graphics info
    @dbus.service.signal(INTERFACE, signature='us')
    def signalGSUpdateInfo(self, status, msg):
        pass

    @dbus.service.method(INTERFACE, in_signature='', out_signature='s', sender_keyword='sender')
    def readGSInfo(self, sender=None):
        graphicsCard = KAGraphicsCardInfo(self.cmdtool)
        return graphicsCard.getGraphicsCardInfo()

    #bluetooth info
    @dbus.service.signal(INTERFACE, signature='us')
    def signalBLUpdateInfo(self, status, msg):
        pass

    @dbus.service.method(INTERFACE, in_signature='', out_signature='s', sender_keyword='sender')
    def readBLInfo(self, sender=None):
        bluetoothInfo = KABluetoothInfo(self.cmdtool)
        return bluetoothInfo.getBluetoothInfo()

    #keyboard info
    @dbus.service.signal(INTERFACE, signature='us')
    def signalKBUpdateInfo(self, status, msg):
        pass

    @dbus.service.method(INTERFACE, in_signature='', out_signature='s', sender_keyword='sender')
    def readKBInfo(self, sender=None):
        keyBoard = KAKeyboardInfo(self.cmdtool)
        return keyBoard.getkeyboardInfo()

    #mouse info
    @dbus.service.signal(INTERFACE, signature='us')
    def signalMSUpdateInfo(self, status, msg):
        pass

    @dbus.service.method(INTERFACE, in_signature='', out_signature='s', sender_keyword='sender')
    def readMSInfo(self, sender=None):
        mouse = KAMouseInfo(self.cmdtool)
        return mouse.getMouseInfo()

    #monitor info
    @dbus.service.signal(INTERFACE, signature='us')
    def signalMNUpdateInfo(self, status, msg):
        pass

    @dbus.service.method(INTERFACE, in_signature='', out_signature='s', sender_keyword='sender')
    def readMNInfo(self, sender=None):
        monitorInfo = KAMonitor()
        return monitorInfo.getMonitorsInfo()

    #cddrive info
    @dbus.service.signal(INTERFACE, signature='us')
    def signalCDUpdateInfo(self, status, msg):
        pass

    @dbus.service.method(INTERFACE, in_signature='', out_signature='s', sender_keyword='sender')
    def readCDInfo(self, sender=None):
        cdrom = KACDRomInfo()
        return cdrom.getCDRomInfo()

    #battery info
    @dbus.service.signal(INTERFACE, signature='us')
    def signalBTUpdateInfo(self, status, msg):
        pass

    @dbus.service.method(INTERFACE, in_signature='', out_signature='s', sender_keyword='sender')
    def readBTInfo(self, sender=None):
        battery = KABatteryInfo()
        sysBoardInfo = SystemBoard()
        sysInfo = sysBoardInfo.getSystemInfo()
        if System_Product in sysInfo and sysInfo[System_Product] != "XXXX" :
            return battery.getBatteryInfo(sysInfo[System_Product])
        else :
            return battery.getBatteryInfo()

    #camera info
    @dbus.service.signal(INTERFACE, signature='us')
    def signalCAUpdateInfo(self, status, msg):
        pass

    @dbus.service.method(INTERFACE, in_signature='', out_signature='s', sender_keyword='sender')
    def readCAInfo(self, sender=None):
        camera = KACameraInfo(self.cmdtool)
        return camera.getCameraInfo()

    #fan info
    @dbus.service.signal(INTERFACE, signature='us')
    def signalFAUpdateInfo(self, status, msg):
        pass

    @dbus.service.method(INTERFACE, in_signature='', out_signature='s', sender_keyword='sender')
    def readFAInfo(self, sender=None):
        faninfo = KAFanInfo()
        return faninfo.getFanInfo()

    #all info
    @dbus.service.signal(INTERFACE, signature='us')
    def signalHardwareUpdateInfo(self, status, msg):
        pass

    def getHardwareInfo(self):
        hardwareInfo = {}
        infoItem = self.readHDInfo()
        if len(infoItem) > 0 :
            hardwareInfo[HDI_ROOT] = json.loads(infoItem)
        infoItem = self.readMemInfo()
        if len(infoItem) > 0 :
            hardwareInfo[MMI_ROOT] = json.loads(infoItem)
        infoItem = self.readProcInfo()
        if len(infoItem) > 0 :
            hardwareInfo[PSI_ROOT] = json.loads(infoItem)
        infoItem = self.readNWInfo()
        if len(infoItem) > 0 :
            hardwareInfo[NWI_ROOT] = json.loads(infoItem)
        infoItem = self.readVCInfo()
        if len(infoItem) > 0 :
            hardwareInfo[VCI_ROOT] = json.loads(infoItem)
        infoItem = self.readMBInfo()
        if len(infoItem) > 0 :
            hardwareInfo[MBI_ROOT] = json.loads(infoItem)
        infoItem = self.readGSInfo()
        if len(infoItem) > 0 :
            hardwareInfo[GSI_ROOT] = json.loads(infoItem)
        infoItem = self.readBLInfo()
        if len(infoItem) > 0 :
            hardwareInfo[BLI_ROOT] = json.loads(infoItem)
        infoItem = self.readKBInfo()
        if len(infoItem) > 0 :
            hardwareInfo[KBI_ROOT] = json.loads(infoItem)
        infoItem = self.readMSInfo()
        if len(infoItem) > 0 :
            hardwareInfo[MSI_ROOT] = json.loads(infoItem)
        infoItem = self.readMNInfo()
        if len(infoItem) > 0 :
            hardwareInfo[MNI_ROOT] = json.loads(infoItem)
        infoItem = self.readCDInfo()
        if len(infoItem) > 0 :
            hardwareInfo[CDI_ROOT] = json.loads(infoItem)
        infoItem = self.readBTInfo()
        if len(infoItem) > 0 :
            hardwareInfo[BTI_ROOT] = json.loads(infoItem)
        infoItem = self.readCAInfo()
        if len(infoItem) > 0 :
            hardwareInfo[CAI_ROOT] = json.loads(infoItem)
        infoItem = self.readFAInfo()
        if len(infoItem) > 0 :
            hardwareInfo[FAI_ROOT] = json.loads(infoItem)
        strJson = json.dumps(hardwareInfo)
        return strJson

    #all info
    @dbus.service.method(INTERFACE, in_signature='', out_signature='s', sender_keyword='sender')
    def readHardwareInfo(self, sender=None):
        if self.threadPool[THREAD_INDEX_HARDWARE] and self.threadPool[THREAD_INDEX_HARDWARE].is_alive() :
            return self.threadPool[THREAD_INDEX_HARDWARE].getResult()
        self.updateLshwInfo(True)
        self.threadPool[THREAD_INDEX_HARDWARE] = KAThread(self.getHardwareInfo, self.signalHardwareUpdateInfo, args=())
        #改为信号的方式
        self.threadPool[THREAD_INDEX_HARDWARE].start()
        return self.threadPool[THREAD_INDEX_HARDWARE].getResult()
        

    @dbus.service.method(INTERFACE, in_signature='', out_signature='s', sender_keyword='sender')
    def mdObtainSystemBoardInfo(self, sender=None):
        self.threadPool[THREAD_INDEX_SYSTEMBOARD] = KAThread(SystemBoard().getSystemBoardInfo, None, args=())
        #改为信号的方式
        self.threadPool[THREAD_INDEX_SYSTEMBOARD].start()
        self.threadPool[THREAD_INDEX_SYSTEMBOARD].join()
        return self.threadPool[THREAD_INDEX_SYSTEMBOARD].getResult()

    #machine outline info
    @dbus.service.signal(INTERFACE, signature='us')
    def signalOutlineUpdateInfo(self, status, msg):
        pass

    def getOutlineInfo(self):
        outline = KAMachineInfo(self.cmdtool)
        return outline.getOutline()

    @dbus.service.method(INTERFACE, in_signature='', out_signature='s', sender_keyword='sender')
    def readOutline(self, sender=None):
        if self.threadPool[THREAD_INDEX_OUTLINE] and self.threadPool[THREAD_INDEX_OUTLINE].is_alive() :
            return self.threadPool[THREAD_INDEX_OUTLINE].getResult()
        self.updateLshwInfo(False)
        self.threadPool[THREAD_INDEX_OUTLINE] = KAThread(self.getOutlineInfo, self.signalOutlineUpdateInfo, args=())
        #改为信号的方式
        self.threadPool[THREAD_INDEX_OUTLINE].start()
        return self.threadPool[THREAD_INDEX_OUTLINE].getResult()

    @dbus.service.method(INTERFACE, in_signature='', out_signature='a{sv}')
    def get_cpu_info(self):
        cpuInfo = DetailInfo()
        return cpuInfo.get_cpu()

    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def hide_temperature_page(self):
        status, output = subprocess.getstatusoutput("sensors")
        if( status != -1 ):
            for line in output.split("\n"):
                if "coretemp-isa" in line:
                    return True
            return False

    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def hide_fan_page(self):
        faninfo = KAFanInfo()
        return faninfo.getCpuFanEnable()

    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def hide_cpufm_page(self):
        path = '/sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq'
        if os.path.exists(path):
            return True
        else:
            return False

    @dbus.service.signal(INTERFACE, signature='')
    def signalLshwUpdateFinished(self):
        pass

    def signalLshwReloadFinished(self, status, isDone):
        self.signalLshwUpdateFinished()
        pass

    @dbus.service.method(INTERFACE, in_signature='', out_signature='b', sender_keyword='sender')
    def updateLshwInfo(self, forceUpdate = True, sender=None):
        self.cmdtool.loadInfoFromLshw(forceUpdate)
        return True

    @dbus.service.method(INTERFACE, in_signature='', out_signature='b', sender_keyword='sender')
    def reloadLshwInfo(self, forceUpdate = True, sender=None):
        if self.threadPool[THREAD_INDEX_RELOADLSHW] and self.threadPool[THREAD_INDEX_RELOADLSHW].is_alive() :
            return True
        args = {forceUpdate}
        self.threadPool[THREAD_INDEX_RELOADLSHW] = KAThread(self.cmdtool.loadInfoFromLshw, self.signalLshwReloadFinished, args=(args))
        #改为信号的方式
        self.threadPool[THREAD_INDEX_RELOADLSHW].start()
        return True

if __name__ == '__main__':
    dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)
    mainloop = GLib.MainLoop()
    # Init dbus.
    system_bus = dbus.SystemBus()
    bus_name = dbus.service.BusName("com.kylin.assistant.systemdaemon", system_bus)
    HardwareInfo(system_bus, mainloop)
    mainloop.run()

