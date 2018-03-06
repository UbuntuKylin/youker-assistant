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

import sys
sys.path.append('/usr/lib/python3/dist-packages/PIL') ## add by hb for python3

import os
import re
import shutil
#import Image


# from _pyio import open

class Others:

    # custom plymouth bg by plymouthName
    def custom_plymouth_bg(self, plymouthName):
        plymouthName = plymouthName.encode('utf-8')
        existingDir = '/var/lib/kylin-assistant-daemon/plymouth/existing/'
        linkFileDir = '/lib/plymouth/themes/default.plymouth'

        # replace the config file
        shutil.copy(existingDir + plymouthName + '/default.plymouth', linkFileDir)

    # add new custom plymouth
#    def add_new_plymouth(self, customBG, plymouthName):
#        # if plymouthName exist return false
#        existingPlymouth = self.get_existing_plymouth_list()
#        customBG = customBG.encode('utf-8')
#        plymouthName = plymouthName.encode('utf-8')
#        plymouthName
#        if(plymouthName in existingPlymouth):
#            return False
#        else:
#            existingDir = '/var/lib/kylin-assistant-daemon/plymouth/existing/'
#            customScript = '/var/lib/kylin-assistant-daemon/plymouth/defaults/only_background.script'
#            defaultplymouthfile = '/var/lib/kylin-assistant-daemon/plymouth/defaults/default.plymouth'
			
#            # add new plymouth conf dir
#            os.mkdir(existingDir + plymouthName)
#            shutil.copy(defaultplymouthfile, existingDir + plymouthName + '/default.plymouth')
#            # modify config file
#            fileHandle = open(existingDir + plymouthName + '/default.plymouth', 'a')
#            fileHandle.write('ImageDir=/lib/plymouth/themes/' + plymouthName + '\n')
#            fileHandle.write('ScriptFile=/lib/plymouth/themes/' + plymouthName + '/kylin.script')
#            fileHandle.close()

#            # add new system plymouth dir
#            os.mkdir('/lib/plymouth/themes/' + plymouthName)
#            shutil.copy(customScript, '/lib/plymouth/themes/' + plymouthName + '/kylin.script')
#            #shutil.copy(customBG, '/lib/plymouth/themes/' + plymouthName + '/customBG.png')
#            Image.open(customBG).save('/lib/plymouth/themes/' + plymouthName + '/customBG.png')
			
#            return True

    # get existing plymouth list
    def get_existing_plymouth_list(self):
        result = []
        edir = ('/var/lib/kylin-assistant-daemon/plymouth/existing')
        if os.path.isdir(edir):
            for f in os.listdir(edir):
                if os.path.isdir(os.path.join(edir, f)):
                    result.append(f)
        result.sort()
        return result

    # check and save current plymouth when init
    def plymouth_init_check(self):
        existingDir = '/var/lib/kylin-assistant-daemon/plymouth/existing/'
        linkFileDir = '/lib/plymouth/themes/default.plymouth'

        # add 0619
        if(os.path.exists('/lib/plymouth/themes/ubuntukylin-logo') == False):
            shutil.copytree('/var/lib/kylin-assistant-daemon/plymouth/ubuntukylin-logo/', '/lib/plymouth/themes/ubuntukylin-logo')

        # locate the current plymouth theme dir
        linkFile = open(linkFileDir)
        fullString = linkFile.read()
        linkFile.close()
        index = fullString.find('ScriptFile=')
        theLine = fullString[index:]
        # cut 'ScriptFile=' & '\n'
        scriptFile = theLine[theLine.find('/'):theLine.find('\n')]
#        scriptFile = theLine[theLine.find('/'):]
        scriptDir = scriptFile[0:scriptFile.rfind('/')]
        scriptName = scriptFile[scriptFile.rfind('/') + 1:]
        plymouthName = scriptDir[scriptDir.rfind('/') + 1:]
        
        # check and save current pl        linkFile.close()ymouth
        if(os.path.exists(existingDir + plymouthName) == False):
            os.mkdir(existingDir + plymouthName)
            shutil.copy(scriptFile, existingDir + plymouthName + '/' + scriptName)
            shutil.copy(linkFileDir, existingDir + plymouthName + '/default.plymouth')

    def get_image_path(self,name):
        name = name.encode('utf-8')
#        if not os.path.exists('/lib/plymouth/themes/' + name + '/customBG.png') :
        if not os.path.exists('/lib/plymouth/themes/' + name + '/' + name + '.script') :
            if not os.path.exists('/lib/plymouth/themes/' + name + '/kylin.script') :
                if not os.path.exists('/lib/plymouth/themes/' + name + '/customBG.png') :
                    return "False"
                else:
                    return "True"
            else:
                return "True"
        else :
            return "True"
#            path = '/lib/plymouth/themes/' + name + '/customBG.png'
#            return path

    def delete_plymouth(self,plymouthName):
        plymouthName = plymouthName.encode('utf-8')
        fd = open('/lib/plymouth/themes/default.plymouth','r')
        animation = fd.read()
        fd.close()
        used = animation[animation.index('themes/')+len('themes/'):]
        used = used[:used.index('\n')]
        if used == plymouthName :
            return 'use'
        elif plymouthName == 'ubuntukylin-logo':
            return 'sys'
        else :
            shutil.rmtree('/var/lib/kylin-assistant-daemon/plymouth/existing/' + plymouthName)
            shutil.rmtree('/lib/plymouth/themes/' + plymouthName)
            return 'ok'
#        plymouthName = plymouthName.encode('utf-8')
#        fd = open('/lib/plymouth/themes/default.plymouth','r')
#        animation = fd.read()
#        fd.close()
#        used = animation[animation.index('themes/')+len('themes/'):]
#        used = used[:used.index('\n')]
#        if used == plymouthName :
#            return False
#        else :
#            shutil.rmtree('/var/lib/kylin-assistant-daemon/plymouth/existing/' + plymouthName)
#            shutil.rmtree('/lib/plymouth/themes/' + plymouthName)
#            return True

if __name__ == '__main__':
    ooo = Others()
# 	print ooo.get_existing_plymouth_list()
# 	ooo.add_new_plymouth('/home/shine/heihei.png', 'hoho')
#	ooo.custom_plymouth_bg('hoho')
# 	ooo.plymouth_init_check()
