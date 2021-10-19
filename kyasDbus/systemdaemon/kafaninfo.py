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

import json
import subprocess
from smbus import SMBus
from pprint import pprint

from kajsondef import *

class KAFanInfo():

    def __init__(self):
        try:
            self.i2cbus = SMBus(2)
        except IOError:
            self.i2cbus = None
        pass

    def getFanInfo(self):
        summary = {"list":[]}
        origin = {}
        mid = {}

        status, output = subprocess.getstatusoutput("sensors")

        if (status != -1):
            for line in output.split("\n"):
                if "fan" in line.split(":")[0]:
                    origin[line.split(":")[0]]=line.split(":")[1].lstrip().split(" ")[0]

        if (not bool(origin) or "fan1" not in origin or not origin["fan1"].isdigit() or not int(origin["fan1"])):
            try:
                data1 = self.i2cbus.read_byte_data(0x3c, 0x30)
                data2 = self.i2cbus.read_byte_data(0x3c, 0x31)
                result = (int(hex(data1), 16) << 8) | int(hex(data2), 16)
            except:
                pass
            else:
                mid['fan1'] = result
                origin.update(mid)
        for key in origin:
            info = {}
            info[FAI_NAME] = key
            info[FAI_SPEED] = origin[key]
            summary["list"].append(info)
        return json.dumps(summary)

    def getCpuFanEnable(self) :
        show = False
        status, output = subprocess.getstatusoutput("sensors")
        if ( status == 0 ):
            for line in output.split("\n"):
                if "fan" in line:
                    fanSpeed = line.split(":")[1].strip().split(" ")[0]
                    if (fanSpeed.isdigit() and int(fanSpeed)>0):
                        show = True
        else:
            show = False

        if ( not show ):
            try:
                b = SMBus(2)
                data1 = b.read_byte_data(0x3c, 0x30)
            except IOError:
                pass
            else:
                if data1 != 0:
                    show = True

        return show

if __name__ == "__main__":
    cc = KAFanInfo()
    pprint(cc.getFanInfo())
    #pprint(cc.getOutline())

