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

import psutil
import time
import subprocess

class MonitorBall:

    # clean up memory
    def cleanup_memory(self):
        '''force changed to disk, update the super block'''
        pone = subprocess.Popen(["sync"], shell=True)
        pone.wait()

        '''drop pagecache, dentries and inodes to free the memory'''
        ptwo = subprocess.Popen(["echo 3 > /proc/sys/vm/drop_caches"], shell=True)
        ptwo.wait()

    # get cpu percent
    def get_cpu_percent(self, percpu = False):
        return psutil.cpu_percent(0.1, percpu)

    # get total memory + cache
    def get_total_cmemory(self, symbol = "m"):
        mem = psutil.phymem_usage()
        value = mem.total
        return self.bytes2human(value, symbol)

    # get used memory + cache
    def get_used_cmemory(self, symbol = "m"):
        mem = psutil.phymem_usage()
        value = mem.used
        return self.bytes2human(value, symbol)

    # get free memory + cache
    def get_free_cmemory(self, symbol = "m"):
        mem = psutil.phymem_usage()
        value = mem.free
        return self.bytes2human(value, symbol)
	
    # get total memory
    def get_total_memory(self, symbol = "m"):
        baseData = psutil.virtual_memory()
        value = baseData.total
        return self.bytes2human(value, symbol)

    # get used memory
    def get_used_memory(self, symbol = "m"):
        baseData = psutil.virtual_memory()
        value = baseData.total - baseData.available
        return self.bytes2human(value, symbol)

    # get free memory
    def get_free_memory(self, symbol = "m"):
        baseData = psutil.virtual_memory()
        value = baseData.available
        return self.bytes2human(value, symbol)
	
    # get memory used percent
    def get_memory_percent(self):
        baseData = psutil.virtual_memory()
        return baseData.percent

    # get network total flow, return (up, down)
    def get_network_flow_total(self, symbol = "k"):
        network = psutil.network_io_counters()
        sent = network.bytes_sent
        recv = network.bytes_recv

        if(symbol == "b"):
            return (sent, recv)
        elif(symbol == "k"):
            k_up = float(sent) / 1024
            ups = str(k_up)
            ups = ups[0:ups.find(".") + 2]

            k_down = float(recv) / 1024
            downs = str(k_down)
            downs = downs[0:downs.find(".") + 2]

            return (ups, downs)
        else:
            return None

    # byte to human by symbol
    def bytes2human(self, value, symbol):
        if symbol == "k":
            value = value / 1024
        elif symbol == "m":
            value = value / 1024 / 1024
        elif symbol == "g":
            valuef = float(value) / 1024 / 1024 / 1024
            values = str(valuef)
            value = values[0:values.find(".") + 2]
        else:
            pass
        return str(value)

if __name__ == "__main__":
    mmm = MonitorBall()
    #	print mmm.get_network_flow_total()
    #	print mmm.get_network_flow_total("b")
    # 	mmm.cleanup_memory()
    # 	print mmm.get_cpu_percent()
    # 	print mmm.get_cpu_percent(True)
    # 	print mmm.get_cpu_percent()
    #  	print mmm.get_free_memory("m")
    #  	print mmm.get_used_memory("g")
    # 	print mmm.get_total_memory("g")
    # 	mmm.ttestt()
    print(mmm.get_memory_percent())
    print(mmm.get_total_memory())
    print(mmm.get_used_memory())
    print(mmm.get_free_memory())
