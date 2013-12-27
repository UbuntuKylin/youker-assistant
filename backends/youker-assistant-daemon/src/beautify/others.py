#!/usr/bin/python
# -*- coding: utf-8 -*-
### BEGIN LICENSE

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
import re
import shutil
# from _pyio import open

class Others:

    # custom plymouth bg by plymouthName
    def custom_plymouth_bg(self, plymouthName):
        existingDir = '/var/lib/youker-assistant-daemon/plymouth/existing/'
        linkFileDir = '/lib/plymouth/themes/default.plymouth'

        # replace the config file
        shutil.copy(existingDir + plymouthName + '/default.plymouth', linkFileDir)

    # add new custom plymouth
    def add_new_plymouth(self, customBG, plymouthName):
        # if plymouthName exist return false
        existingPlymouth = self.get_existing_plymouth_list()
        if(plymouthName in existingPlymouth):
            return False
        else:
            existingDir = '/var/lib/youker-assistant-daemon/plymouth/existing/'
            customScript = '/var/lib/youker-assistant-daemon/plymouth/defaults/only_background.script'
            defaultplymouthfile = '/var/lib/youker-assistant-daemon/plymouth/defaults/default.plymouth'
			
            # add new plymouth conf dir
            os.mkdir(existingDir + plymouthName)
            shutil.copy(defaultplymouthfile, existingDir + plymouthName + '/default.plymouth')
            # modify config file
            fileHandle = open(existingDir + plymouthName + '/default.plymouth', 'a')
            fileHandle.write('ImageDir=/lib/plymouth/themes/' + plymouthName + '\n')
            fileHandle.write('ScriptFile=/lib/plymouth/themes/' + plymouthName + '/youker.script')
            fileHandle.close()

            # add new system plymouth dir
            os.mkdir('/lib/plymouth/themes/' + plymouthName)
            shutil.copy(customScript, '/lib/plymouth/themes/' + plymouthName + '/youker.script')
            shutil.copy(customBG, '/lib/plymouth/themes/' + plymouthName + '/customBG.png')
			
            return True

    # get existing plymouth list
    def get_existing_plymouth_list(self):
        result = []
        edir = ('/var/lib/youker-assistant-daemon/plymouth/existing')
        if os.path.isdir(edir):
            for f in os.listdir(edir):
                if os.path.isdir(os.path.join(edir, f)):
                    result.append(f)
        result.sort()
        return result

    # check and save current plymouth when init
    def plymouth_init_check(self):
        existingDir = '/var/lib/youker-assistant-daemon/plymouth/existing/'
        linkFileDir = '/lib/plymouth/themes/default.plymouth'

        # locate the current plymouth theme dir
        linkFile = open(linkFileDir)
        fullString = linkFile.read()
        index = fullString.find('ScriptFile=')
        theLine = fullString[index:]
        # cut 'ScriptFile=' & '\n'
        scriptFile = theLine[0:-1][theLine.find('/'):]
        scriptDir = scriptFile[0:scriptFile.rfind('/')]
        scriptName = scriptFile[scriptFile.rfind('/') + 1:]
        plymouthName = scriptDir[scriptDir.rfind('/') + 1:]
        
        # check and save current plymouth
        if(os.path.exists(existingDir + plymouthName) == False):
            os.mkdir(existingDir + plymouthName)
            shutil.copy(scriptFile, existingDir + plymouthName + '/' + scriptName)
            shutil.copy(linkFileDir, existingDir + plymouthName + '/default.plymouth')

    def get_image_path(self,name):
        if not os.path.exists('/lib/plymouth/themes/' + name + '/customBG.png') :
            return False
        else :
            path = '/lib/plymouth/themes/' + name + '/customBG.png'
            return path


if __name__ == '__main__':
    ooo = Others()
# 	print ooo.get_existing_plymouth_list()
# 	ooo.add_new_plymouth('/home/shine/heihei.png', 'hoho')
#	ooo.custom_plymouth_bg('hoho')
# 	ooo.plymouth_init_check()
