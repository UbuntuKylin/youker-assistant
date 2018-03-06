#! /usr/bin/env python3
# -*- coding: utf-8 -*-

### BEGIN LICENSE
# Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd
#
# Author:     Kobe Lee <xiangli@ubuntukylin.com>
# Maintainer: Ubuntu Kylin
#
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

import os, sys
import urllib.request, urllib.error, urllib.parse
import platform
import re
import subprocess
import subprocess

BOOL_TYPE = 1
INT_TYPE = 2
DOUBLE_TYPE = 3
STRING_TYPE = 4

str_agent = []
LEN_AGENT = 10

str_agent.append('Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 6.1; WOW64; Trident/4.0; SLCC2; .NET CLR 2.0.50727; Media Center PC 6.0; .NET CLR 3.5.30729; .NET CLR 3.0.30729; .NET4.0C)')

str_agent.append('Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 6.1; WOW64; Trident/4.0; SLCC2; .NET CLR 2.0.50727; .NET CLR 3.5.30729; .NET CLR 3.0.30729; Media Center PC 6.0; msn OptimizedIE8;ZHCN)')

str_agent.append('Mozilla/5.0 (X11; Linux x86_64; rv:2.2a1pre) Gecko/20110324 Firefox/4.2a1pre')

str_agent.append('Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:2.0b8pre) Gecko/20101213 Firefox/4.0b8pre')

str_agent.append('Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; .NET CLR 1.1.4322; .NET CLR 2.0.50727; InfoPath.2; Alexa Toolbar)')

str_agent.append('Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/534.30 (KHTML, like Gecko) Chrome/12.0.742.53 Safari/534.30')

str_agent.append('Mozilla/5.0 (X11; U;Linux i686; zh-CN;rv:1.2.3.4) Gecko/')

str_agent.append('Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; .NET CLR 1.1.4322; .NET CLR 2.0.50727; InfoPath.2; Alexa Toolbar; SE 2.X MetaSr 1.0)')

str_agent.append('Mozilla/5.0 (Windows; U; Windows NT 6.1; en-US) AppleWebKit/532.4 (KHTML, like Gecko) Maxthon/3.0.6.27 Safari/532.4')

str_agent.append('Mozilla/5.0 (X11; Linux i686) AppleWebKit/537.36 (KHTML, like Gecko) Ubuntu Chromium/34.0.1847.116 Chrome/34.0.1847.116 Safari/537.36')

ubuntukylin_distrowatch = 'http://distrowatch.com/table.php?distribution=ubuntukylin'
distrowatch = 'http://distrowatch.com/'

def get_distro_info():
    ufpath = '/etc/ubuntukylin-release'
    lsbpath = '/etc/lsb-release'
    if(os.path.exists(ufpath) and os.path.isfile(ufpath)):
        uf = open(ufpath)
        lines = uf.readlines()
        rtn = []
        for line in lines:
            kv = line.split('=')
            if (kv[0] == 'DISTRIB_ID'):
                v = kv[1]
                rtn.append(v[:-1])
            if (kv[0] == 'DISTRIB_RELEASE'):
                v = kv[1]
                rtn.append(v[:-1])
        uf.close()
        return rtn
    elif(os.path.exists(lsbpath) and os.path.isfile(lsbpath)):
        lsbf = open(lsbpath)
        lines = lsbf.readlines()
        rtn = []
        for line in lines:
            kv = line.split('=')
            if (kv[0] == 'DISTRIB_ID'):
                v = kv[1]
                rtn.append(v[:-1])
            if (kv[0] == 'DISTRIB_RELEASE'):
                v = kv[1]
                rtn.append(v[:-1])
        lsbf.close()
        return rtn
    else:
        dist = platform.dist()
        distname = dist[0]
        distversion = dist[1]
        return [distname, distversion]

#def get_machine_id():
#    fpath = '/var/lib/dbus/machine-id'
#    if(os.path.exists(fpath) and os.path.isfile(fpath)):
#        f = open(fpath, 'r')
#        id = f.read()
#        f.close()
#        id = id.replace('\n','')
#        if(id == ''):
#            return 'unknown'
#        else:
#            return id
#    else:
#        return 'unknown'

def get_ip_again():
    ret = ''
    url = "http://members.3322.org/dyndns/getip"
    try:
        fp = urllib.request.urlopen(url, timeout=5)
        souce = fp.read()
        if not isinstance(souce, str):
            souce = str(souce)
        fp.close()
        ret = souce.replace('\n', '')
    except:
        print('get_ip failed!', file=sys.stderr)
    return ret

def get_ip():
    ret = ''
    url = "http://iframe.ip138.com/ic.asp"
    try:
        fp = urllib.request.urlopen(url, timeout=5)
        souce = fp.read().decode("GB2312")
        fp.close()
        ret = re.findall("<center>(.*)</center>", souce)[0].encode("UTF-8")
    except:
        ret = get_ip_again()
    return ret


def get_run_command(pkgname):
    fd = os.popen('find /usr/share/applications/ -name "%s.desktop" | xargs grep "Exec"' %pkgname)
    exc = fd.read()
    fd.close()
    command = ['']
    # 截取运行指令部分
    if exc:
        command = re.findall('Exec=(.*)',exc)
    # 有些软件Exec后面会有%U %f等，进行过滤
    if re.findall(' ',command[0]):
        command = re.findall('(.*) ',command[0])
    #split the command to prevent the error: "OSError: [Errno 2] 没有那个文件或目录"
    fullcmd = command[0]
    if fullcmd:
        fullcmd = command[0].split()
    return fullcmd

def run_app(pkgname):
    cmd = get_run_command(pkgname)
    p = subprocess.Popen(cmd, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=False)

def get_output(cmd):
    '''status =0 : success'''
    status, output = subprocess.getstatusoutput(cmd)
    if status: raise
    return output

if __name__ == '__main__':
    ip = get_ip()
    print(ip)
