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


import os
import configparser
import copy
import shutil
from pprint import pprint
import locale

SECTION = 'Desktop Entry'
OPTION_H = 'Hidden'
OPTION_N = 'NoDisplay'
OPTION_O = 'OnlyShowIn'
OPTION_NOT = 'NotShowIn'
OPTION_X = 'X-GNOME-Autostart-enabled'

class MyConfigParser(configparser.ConfigParser):
    
    def __inin__(self, defaults=None):
        configparser.ConfigParser.__init__(self, defaults=None)
    
    def optionxform(self, optionstr):
        return optionstr

class Desktop_Autostart_Manage():

    def __init__(self):
        self.dic = {}

    def function(self, filename):
        #config = ConfigParser.ConfigParser()
        config = MyConfigParser()
        config.read(filename)
        
        #flag = ''
        current_desktop_env = self.get_desktop_env()
        all_sections = config.sections()

        if SECTION in all_sections:
            all_options = config.options(SECTION)
            #pprint(all_options)
            if OPTION_H in all_options and config.getboolean(SECTION, OPTION_H):
                    self.dic.setdefault(OPTION_H, []).append(filename)
                #else:
                    #temp_h = '-' + OPTION_H
                    #self.dic.setdefault(temp_h, []).append(filename)
            else:
                if OPTION_N in all_options and config.getboolean(SECTION, OPTION_N):
                    self.dic.setdefault(OPTION_N, []).append(filename)
                else:
                    #OPTION_O in all_options or OPTION_NOT in all_options or OPTION_X in all_options:
                    if (OPTION_O in all_options and current_desktop_env not in config.get(SECTION, OPTION_O)) or (OPTION_NOT in all_options and current_desktop_env in config.get(SECTION, OPTION_NOT)):
                        self.dic.setdefault('*showin', []).append(filename)
                    elif OPTION_X in all_options and not config.getboolean(SECTION, OPTION_X):
                        self.dic.setdefault('notautostart', []).append(filename)
                    else:
                        self.dic.setdefault('autostart', []).append(filename)

        #return flag

    def get_desktop_env(self):
        desktop_name = os.getenv('XDG_CURRENT_DESKTOP')
        if desktop_name is None:
             desktop_name = os.getenv('XDG_SESSION_DESKTOP')
        return desktop_name

    def _walk_dir(self, sdir):
        scan_files = []
        for root, dirs, files in os.walk(sdir):
            for name in files:
                absolute_path = os.path.join(root, name)
                if absolute_path.endswith('desktop'):
                    scan_files.append(absolute_path)
        return scan_files

    def get_autostart_dirs(self):
        dirs = []
        dirs_home = ''
        dirs_dirs = ''

        dirs_home = os.getenv('XDG_CONFIG_HOME')
        #pprint(dirs_dirs)
        if dirs_home:
            temp1 = [j for j in dirs_home.split(":") if os.path.exists(j)]
            dirs.extend(temp1)

        dirs_dirs = os.getenv('XDG_CONFIG_DIRS')
        #pprint(dirs_dirs)
        if dirs_dirs:
            temp2 = [i for i in dirs_dirs.split(":") if os.path.exists(i)]
            dirs.extend(temp2)

        return dirs

    def check_dic(self, filename):
        name = filename.split("/")[-1]
        if name in [s.split("/")[-1] for s in self.dic.get(OPTION_H, ['']) if s]:
            return True
        else:
            return False



    def init_dic(self):
        dirs = self.get_autostart_dirs()

        for one in dirs:
            x = self._walk_dir(one)
            for value in x:
                if self.check_dic(value):
                    continue
                self.function(value)
        #pprint(self.dic)

    def function_home(self, filename):
        #config = ConfigParser.ConfigParser()
        config = MyConfigParser()
        config.read(filename)

        current_desktop_env = self.get_desktop_env()
        all_sections = config.sections()
        if SECTION in all_sections:
            flag = ''
            all_options = config.options(SECTION)

            if OPTION_H in all_options and config.getboolean(SECTION, OPTION_H):
                flag = OPTION_H
            else:
                if OPTION_N in all_options and config.getboolean(SECTION, OPTION_N):
                    flag = OPTION_N
                else:
                    if (OPTION_O in all_options and current_desktop_env not in config.get(SECTION, OPTION_O)) or (OPTION_NOT in all_options and current_desktop_env in config.get(SECTION, OPTION_NOT)):
                        flag = '*showin'
                    elif OPTION_X in all_options and not config.getboolean(SECTION, OPTION_X):
                        flag = 'notautostart'
                    else:
                        flag = 'autostart'
        return flag

    def get_final_status(self):
        self.init_dic()

        autostart_home_dir = os.path.expanduser('~/.config/autostart/')

        if os.path.exists(autostart_home_dir):
            home_desktop_files = self._walk_dir(autostart_home_dir)
        else:
            home_desktop_files = []
        if home_desktop_files:
            for single in home_desktop_files:
                status = self.function_home(single)
                #pprint(status)
                if status == OPTION_H or status == OPTION_N:
                    autostart_1_list = self.dic.get('autostart', [])
                    if autostart_1_list:
                        new_autostart_list = [d for d in autostart_1_list if not d.count(single.split("/")[-1])]
                        self.dic['autostart'] = new_autostart_list
                    notautostart_1_list = self.dic.get('notautostart', [])
                    if notautostart_1_list:
                        #backup_list = copy.deepcopy(notautostart_list)
                        new_notautostart_list = [x for x in notautostart_1_list if not x.count(single.split("/")[-1])]
                        self.dic['notautostart'] = new_notautostart_list
                    self.dic.setdefault(OPTION_H, []).append(single)

                if status == 'autostart':
                    autostart_2_list = self.dic.get('autostart', [])
                    if autostart_2_list:
                        new_autostart_2_list = [d for d in autostart_2_list if not d.count(single.split("/")[-1])]
                        self.dic['autostart'] = new_autostart_2_list
                    notautostart_2_list = self.dic.get('notautostart', [])
                    if notautostart_2_list:
                        #backup_list = copy.deepcopy(notautostart_list)
                        new_notautostart_2_list = [x for x in notautostart_2_list if not x.count(single.split("/")[-1])]
                        self.dic['notautostart'] = new_notautostart_2_list
                    self.dic.setdefault('autostart', []).append(single)
                
                if status == 'notautostart':
                    autostart_3_list = self.dic.get('autostart', [])
                    if autostart_3_list:
                        new_autostart_3_list = [d for d in autostart_3_list if not d.count(single.split("/")[-1])]
                        self.dic['autostart'] = new_autostart_3_list
                    notautostart_3_list = self.dic.get('notautostart', [])
                    if notautostart_3_list:
                        #backup_list = copy.deepcopy(notautostart_list)
                        new_notautostart_3_list = [x for x in notautostart_3_list if not x.count(single.split("/")[-1])]
                        self.dic['notautostart'] = new_notautostart_3_list
                    self.dic.setdefault('notautostart', []).append(single)

        else:
            pass

        #pprint(self.dic)

    def change_single_status(self, filename):
        #dirs  = self.get_autostart_dirs()
        status = ''
        new_status = ''
        hdir = os.path.expanduser('~/.config/autostart/')
        mdir = '/usr/share/upstart/xdg/autostart/'
        ldir = '/etc/xdg/autostart/'

        hfilename = hdir + filename
        mfilename = mdir + filename
        lfilename = ldir + filename

        if os.path.exists(mfilename):
            #pprint(mfilename)
            status = self.function_home(mfilename)
            #pprint(status)
        
        if os.path.exists(lfilename):
            if not status:
                status = self.function_home(lfilename)
            else:
                pass
            #pprint(status)
        if os.path.exists(hfilename):
            new_status = self.function_home(hfilename)
            #pprint(new_status)
            if status == new_status:
                #change
                if new_status == 'autostart':
                    #pprint("change false")
                    self.change_option_x(hfilename, 'false')
                elif new_status == 'notautostart':
                    #pprint("change true")
                    self.change_option_x(hfilename, 'true')
            else:
                #remove
                #pprint("remove")
                os.remove(hfilename)

        else:
            #touch
            if not os.path.exists(hdir):
                os.makedirs(hdir)
            #pprint("copy")
            shutil.copy(lfilename, hfilename)
            if status == 'autostart':
                #pprint("change false")
                self.change_option_x(hfilename, 'false')
            elif status == 'notautostart':
                self.change_option_x(hfilename, 'true')


    def change_option_x(self, name, value):
        #cf = ConfigParser.ConfigParser()
        cf = MyConfigParser()
        cf.read(name)

        s = cf.sections()
        o = cf.options(SECTION)
        if SECTION in s:
            #if OPTION_X in o:
                #if cf.getboolean(SECTION, OPTION_X):
                    #cf.set(SECTION, OPTION_X, 'false')
                #else:
                    #cf.set(SECTION, OPTION_X, 'true')
            #else:
            cf.set(SECTION, OPTION_X, value)
            cf.write(open(name, "w"))

    def get_desktop_info(self, filepath, locale_language):
        cf = MyConfigParser()
        cf.read(filepath)
        
        info = []
        iconpath1 = '/usr/share/icons/hicolor/24x24/apps/'
        iconpath2 = '/usr/share/pixmaps/'
        s = cf.sections()
        o = cf.options(SECTION)
        info.append('Path:' + filepath)
        
        #
        if SECTION in s:
            if locale_language == "zh_CN":
                if 'Name[zh_CN]' in o:
                    info.append('Name:' + cf.get(SECTION, 'Name[zh_CN]'))
                else:
                    info.append('Name:' + cf.get(SECTION, 'Name'))

                if 'Comment[zh_CN]' in o:
                    info.append('Comment:' + cf.get(SECTION, 'Comment[zh_CN]'))
                elif 'Comment' in o:
                    info.append('Comment:' + cf.get(SECTION, 'Comment'))
                else:
                    info.append('Comment:')
            else:
                info.append('Name:' + cf.get(SECTION, 'Name'))
                if 'Comment' in o:
                    info.append('Comment:' + cf.get(SECTION, 'Comment'))
                else:
                    info.append('Comment:')

            if 'Icon' in o:
                tempicon = cf.get(SECTION, 'Icon')
                if not tempicon.endswith('.png') and not tempicon.endswith('.jpg'):
                    tempicon = tempicon + '.png'
                if os.path.exists(iconpath2 + tempicon):
                    info.append('Icon:' + iconpath2 + tempicon)
                elif os.path.exists(iconpath1 + tempicon):
                    info.append('Icon:' + iconpath1 + tempicon)
                else:
                    info.append('Icon:/usr/share/pixmaps/app-autostart-default.png')
            else:
                info.append('Icon:/usr/share/pixmaps/app-autostart-default.png')

        return info


def interface_get_status(fobj):
    locale_language = locale.getdefaultlocale()[0]
    try:
        obj = Desktop_Autostart_Manage()
        obj.get_final_status()
        up = obj.dic.get("autostart", [])
        if up:
            for upvalue in up:
                up_list = obj.get_desktop_info(upvalue, locale_language)
                up_list.append('Status:' + 'true')
                fobj.autostartmanage_data_signal(up_list)

        down = obj.dic.get("notautostart", [])
        if down:
            for downvalue in down:
                down_list = obj.get_desktop_info(downvalue, locale_language)
                down_list.append('Status:' + 'false')
                fobj.autostartmanage_data_signal(down_list)

    except Exception as e:
        fobj.autostartmanage_error_signal(str(e))
    else:
        fobj.autostartmanage_status_signal("complete")

def interface_get_single_status(fobj, path):
    obj = Desktop_Autostart_Manage()
    status = obj.function_home(path)
    if status == "autostart":
        return True
    elif status == "notautostart":
        return False
    else:
        return False

def interface_change_status(fobj, filename):
    try:
        obj = Desktop_Autostart_Manage()
        obj.change_single_status(filename)
    except Exception as e:
        fobj.autostartmanage_error_signal(str(e))
#    else:
#        fobj.autostartmanage_status_signal("complete")

if __name__ == "__main__":
    obj = Desktop_Autostart_Manage()
    #obj.main()
    #obj.function_home('/home/ice/.config/autostart/ubuntu-kylin-software-center-autostart.desktop')
    #obj.get_final_status()
    #obj.change_single_status('ubuntu-kylin-software-center-autostart.desktop')
    #interface_get_status()
    #interface_change_status()
