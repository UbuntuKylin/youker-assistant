#! /usr/bin/env python
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
import urllib2
import platform

VERSION = "1.2.0"

def get_distro_info():
    ufpath = '/etc/ubuntukylin-release'
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

# youker-assistant version
def get_uk_version():
    return VERSION

def get_ip_again():
    ret = ''
    url = "http://members.3322.org/dyndns/getip"
    try:
        fp = urllib2.urlopen(url, timeout=5)
        souce = fp.read()
        if not isinstance(souce, str):
            souce = str(souce)
        fp.close()
        ret = souce.replace('\n', '')
    except:
        print >> sys.stderr, 'get_ip failed!'
    return ret

def get_ip():
    ret = ''
    url = "http://iframe.ip138.com/ic.asp"
    try:
        fp = urllib2.urlopen(url, timeout=5)
        souce = fp.read().decode("GB2312")
        fp.close()
        ret = re.findall("<center>(.*)</center>", souce)[0].encode("UTF-8")
    except:
        ret = get_ip_again()
    return ret

if __name__ == '__main__':
    ip = get_ip()
    print ip
