#!/usr/bin/python
# -*- coding: utf-8 -*-
### BEGIN LICENSE
# Copyright (C) 2010 TualatriX <tualatrix@gmail.com>
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

import os
from gi.repository import Gtk, GLib
def get_hardwareinfo():
    __icon__  = 'computer'
    __title__ = 'Hardware Information'

    cpumodel = 'Unknown'

    # CPU
    if os.uname()[4][0:3] == "ppc":
        for element in file("/proc/cpuinfo"):
            if element.split(":")[0][0:3] == "cpu":
                cpumodel = element.split(":")[1].strip()
    else:
        for element in file("/proc/cpuinfo"):
            if element.split(":")[0] == "model name\t":
                cpumodel = element.split(":")[1].strip()

    # Memory
    for element in file("/proc/meminfo"):
        if element.split(" ")[0] == "MemTotal:":
            raminfo = element.split(" ")[-2]
            ram_msg = GLib.format_size_for_display(int(raminfo) * 1024)
    return cpumodel, ram_msg

CPU, RAM = get_hardwareinfo()

if __name__ == '__main__':
    print(get_hardwareinfo())
