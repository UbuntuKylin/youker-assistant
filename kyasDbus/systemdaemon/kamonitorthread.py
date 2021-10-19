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
import math
import glob

import json
import subprocess

from pprint import pprint

from kajsondef import *
from kathread import *
from utils import *

class KAMonitor() :

    def __init__(self):
        pass

    def getMonitorsInfo(self) :
        infoList = {"list":[]}
        xrandrDat = ""
        if os.path.exists("/tmp/youker-assistant-monitorinfo.dat"):
            status, xrandrDat = subprocess.getstatusoutput('cat /tmp/youker-assistant-monitorinfo.dat')
        value = re.findall("(.*) connected", xrandrDat)
        for monitor in value :
            p = re.compile(r'%s connected' % monitor)
            for m in p.finditer(xrandrDat):
                monitorOne = {}
                mnManufacturer,mnName,mnSize,mnRatio,mnResolution,mnMaxResolution,mnIsMain,mnGamma,mnInterface, \
                    mnModel,mnVisibleArea,mnYear,mnWeek,mnSerial = "","","","","","","","","","","","","",""
                localinfo = xrandrDat.split("%s connected" % monitor)[1].split("connected")[0]
                mnInterface = monitor
                if "primary" in localinfo :
                    mnIsMain = "1"
                else :
                    mnIsMain = "0"
                curResolution = re.findall("\s*(\d+)x(\d+)\+", localinfo)
                if curResolution :
                    curResolutionWidth = int(curResolution[0][0])
                    curResolutionHeight = int(curResolution[0][1])
                    mnResolution = str(curResolutionWidth)+"X"+str(curResolutionHeight)
                    if curResolutionHeight > 0 :
                        ratio = int(curResolutionWidth*100/curResolutionHeight)
                        if ratio == 125 : #5:4
                            mnRatio = "5:4"
                        elif ratio == 133 : #4:3
                            mnRatio = "4:3"
                        elif ratio == 160 : #16:10
                            mnRatio = "16:10"
                        elif ratio == 177 : #16:9
                            mnRatio = "16:9"

                result = re.findall('EDID: \s*(\w*)\s*(\w*)\s*(\w*)\s*\s*(\w*)\s*\s*(\w*)\s*\s*(\w*)\s*\s*(\w*)\s*\s*(\w*)\s*', localinfo)
                if result :
                    with open("/tmp/edid.dat", "w") as fp:
                        for edidinfoline in result[0] :
                            fp.write(edidinfoline)
                #   1920x1080     59.93*+
                result = re.findall('\s*(\d*)x(\d*)\s\s\s', localinfo)
                if result:
                    nMaxRes = 0
                    for item in result :
                        if item[0].isdigit() and item[1].isdigit() :
                            tempRes = int(item[0])*int(item[1])
                            if tempRes > nMaxRes :
                                nMaxRes = tempRes
                                mnMaxResolution = (item[0] + "X" + item[1])

                if os.path.exists("/tmp/edid.dat"):
                    status, ediddecret = subprocess.getstatusoutput('/usr/bin/edid-decode /tmp/edid.dat')
                    #Display Product Name: LEN T2224rbA
                    #Manufacturer: LEN Model 24810 Serial Number 16843009
                    result_bak = re.findall("Manufacturer:\s*(\w*)\s*Model\s*(\w*)", ediddecret)
                    result = re.findall('Display Product Name:\s*(.*)', ediddecret)
                    if result and len(result) > 0 and len(result[0]) > 0 : ### 笔记本没有Monitor name
                        mnName = result[0].strip()
                    if result_bak : 
                        mnManufacturer = result_bak[0][0]
                        if len(mnName) == 0 :
                            if len(result_bak[0]) >= 2 :
                                mnName = result_bak[0][0]+" "+result_bak[0][1]
                            else :
                                mnName = result_bak[0][0]
                    #Made in week 26 of 2020
                    result = re.findall("Made in week\s*(\d*)\s*of\s*(\d*)", ediddecret)
                    if result:
                        mnYear = result[0][1]
                        mnWeek = result[0][0]
                    
                    #Maximum image size: 48 cm x 27 cm
                    result = re.findall("Maximum image size:\s*(\d*)\s*cm\s*x\s*(\d*)\s*cm", ediddecret)
                    if result:
                        mx = float(result[0][0]); my = float(result[0][1])
                        md = math.sqrt(mx**2 + my**2)/2.54
                        mnVisibleArea = (str(mx) + " X " + str(my) + " cm")
                        if md > 13 and md <= 14 :
                             md = 14
                        mnSize = str("%.1f" %md)

                    #Gamma: 2.20
                    result = re.findall("Gamma:\s*(\S*)", ediddecret)
                    if result:
                        mnGamma = result[0]

                    #Display Product Serial Number: U1610C5W
                    result = re.findall("Display Product Serial Number:\s*(\S*)", ediddecret)
                    if result:
                        mnSerial = result[0]

                    #Alphanumeric Data String: BOE CQ
                    #Alphanumeric Data String: NE140FHM-N61
                    result = re.findall("Alphanumeric Data String:\s*(\S*)", ediddecret)
                    if result and len(result) > 0:
                        if len(result[0]) > 0 :
                            mnManufacturer = result[0]
                        if len(result) >= 2 and len(result[1]) > 0 :
                            mnName = result[1]

                    #greatwall
                    if len(mnName) > 0 and "24AL60" == mnName :
                        mnSize = "23.8"  
                        
                if len(mnManufacturer) > 0 :
                    monitorOne[MNI_MANUFACTURER] = mnManufacturer
                if len(mnName) > 0 :
                    monitorOne[MNI_NAME] = mnName
                if len(mnSize) > 0 :
                    monitorOne[MNI_SIZE] = mnSize
                if len(mnRatio) > 0 :
                    monitorOne[MNI_RATIO] = mnRatio
                if len(mnResolution) > 0 :
                    monitorOne[MNI_RESOLUTION] = mnResolution
                if len(mnMaxResolution) > 0 :
                    monitorOne[MNI_MAXAVARES] = mnMaxResolution
                if len(mnIsMain) > 0 :
                    monitorOne[MNI_ISMAIN] = mnIsMain
                if len(mnGamma) > 0 :
                    monitorOne[MNI_GAMMA] = mnGamma
                if len(mnInterface) > 0 :
                    monitorOne[MNI_INTERFACE] = mnInterface
                if len(mnModel) > 0 :
                    monitorOne[MNI_MODEL] = mnModel
                if len(mnVisibleArea) > 0 :
                    monitorOne[MNI_VISIBLEAREA] = mnVisibleArea
                if len(mnYear) > 0 :
                    monitorOne[MNI_YEAR] = mnYear
                if len(mnWeek) > 0 :
                    monitorOne[MNI_WEEK] = mnWeek
                if len(mnSerial) > 0 :
                    monitorOne[MNI_SERIALNUM] = mnSerial

                if len(monitorOne) > 0 :
                    infoList["list"].append(monitorOne)

        if Judgment_HW990():
            if os.path.exists("/sys/class/drm"):
                edid_files = glob.glob("/sys/class/drm/*/edid")
                for edid_file in edid_files:
                    if edid_file.find("card0-eDP-1") != -1 :
                        monitorOne = {}
                        monitorOne[MNI_SIZE] = "14"
                        monitorOne[MNI_MAXAVARES] = "2160X1440"
                        monitorOne[MNI_MANUFACTURER] = "LCD"
                        monitorOne[MNI_INTERFACE] = "eDP"
                        infoList["list"].append(monitorOne)

        return json.dumps(infoList)

    #概要信息
    def getOutline(self) :
        outLine = self.getMonitorsInfo()
        outLineObj = json.loads(outLine)
        outLine = ""
        if len(outLineObj) > 0 and "list" in outLineObj :
            nIndex = 0
            for info in outLineObj["list"] :
                if MNI_NAME in info :
                    if nIndex == 0 :
                        outLine += info[MNI_NAME]
                    else :
                        outLine += " / " + info[MNI_NAME]
                if MNI_SIZE in info :
                        outLine += "("+info[MNI_SIZE]+")"
                nIndex = nIndex + 1
        return outLine

if __name__ == "__main__":
    cc = KAMonitor()
    pprint(cc.getMonitorsInfo())
    #pprint(cc.getOutline())
