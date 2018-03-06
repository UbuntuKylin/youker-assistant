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
import shutil
from . import gsettings
from . import utils

class Sound:
    homedir = ''
    desktop = None

    def __init__(self):
        self.homedir = utils.get_home_dir()
        self.desktop = os.getenv('XDG_CURRENT_DESKTOP')
        if self.desktop is None:
             self.desktop = os.getenv('XDG_SESSION_DESKTOP')

    # sometimes need set homedir manual fe:the backend run by root dbus
    def set_homedir(self, homedir):
        self.homedir = homedir

    # -----------------默认值-----------------
    # Get Default Value
    def get_default_schema_value(self, schema, key):
        return gsettings.get_schema_value(schema, key)

    # Set Default Value
    def set_default_schema_value(self, schema, key, type):
        default_value = self.get_default_schema_value(schema, key)
        if default_value is not None:
            return gsettings.set(schema, None, key, type, default_value)
        else:
            raise NotImplemented
    # ----------------------------------
    def set_input_feedback_sounds_enable(self, flag):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.set('org.mate.sound',
                None,
                'input-feedback-sounds',
                'boolean', flag)
        else:
            return gsettings.set('org.gnome.desktop.sound',
                None,
                'input-feedback-sounds',
                'boolean', flag)

    def get_input_feedback_sounds_enable(self):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.get('org.mate.sound',
                None, 'input-feedback-sounds', 'boolean')
        else:
            return gsettings.get('org.gnome.desktop.sound',
                None, 'input-feedback-sounds', 'boolean')

    def set_sound_event_enable(self, flag):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.set('org.mate.sound',
                None,
                'event-sounds',
                'boolean', flag)
        else:
            return gsettings.set('org.gnome.desktop.sound',
                None,
                'event-sounds',
                'boolean', flag)

    def get_sound_event_enable(self):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.get('org.mate.sound',
                None, 'event-sounds', 'boolean')
        else:
            return gsettings.get('org.gnome.desktop.sound',
                None, 'event-sounds', 'boolean')

    # enable the login music
    def set_login_music_enable(self, flag):
        configdir = self.homedir + '/.config/autostart'
        desktopfile = '/var/lib/kylin-assistant-daemon/autostart/libcanberra-login-sound.desktop'
        targetfile = configdir + '/libcanberra-login-sound.desktop'

        if flag:
            if os.path.exists(configdir):
                pass
            else:
                os.makedirs(configdir)
            shutil.copy(desktopfile, targetfile)
        else:
            if os.path.exists(targetfile):
                os.remove(targetfile)
            else:
                pass

    # get enable the login music. need fix text check in 'libcanberra-login-sound.desktop'
    def get_login_music_enable(self):
        targetfile = self.homedir + '/.config/autostart/libcanberra-login-sound.desktop'

        if os.path.exists(targetfile):
            return True
        else:
            return False

    # get sound themes & check and bak sounds
    def get_sound_themes(self):
        bakDir = '/var/lib/kylin-assistant-daemon/sound-theme/'
        dirs = ('/usr/share/sounds', os.path.join(self.homedir, ".sounds"))
        filters = ('index.theme', '')
        valid = utils.check_dirs(dirs, filters, True)
        valid.sort()

        # check and bak sounds
        for st in valid:
            if(os.path.exists(bakDir + st) == False):
                if(os.path.exists('/usr/share/sounds/' + st)):
                    shutil.copytree('/usr/share/sounds/' + st, bakDir + st)
                else:
                    shutil.copytree(self.homedir + '.sounds/' + st, bakDir + st)

        return valid

    # get current sound theme
    def get_sound_theme(self):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.get('org.mate.sound',
                None, 'theme-name', 'string')
        else:
            return gsettings.get('org.gnome.desktop.sound',
                None, 'theme-name', 'string')

    # set sound theme
    def set_sound_theme(self, theme):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            gstheme = gsettings.get_schema('org.mate.sound')
            gstheme.set_string('theme-name',theme)
        else:
            gstheme = gsettings.get_schema('org.gnome.desktop.sound')
            gstheme.set_string('theme-name',theme)

    # get sounds in current theme
    def get_sounds(self):
        results = []
        currentTheme = self.get_sound_theme()
        if(os.path.exists(os.path.join(self.homedir, ".sounds") + currentTheme)):
            soundDir = os.path.join(self.homedir, ".sounds") + currentTheme
        elif(os.path.exists('/usr/share/sounds/' + currentTheme)):
            soundDir = '/usr/share/sounds/' + currentTheme
        else:
            return results

        for sound in os.listdir(soundDir + '/stereo'):
            # pass the link file
            if(os.path.islink(soundDir + '/stereo/' + sound) == False):
                results.append(soundDir + '/stereo/' + sound)
        results.sort()
        return results

    # replace sound file
    def replace_sound_file(self, newSoundFile, targetSoundFile):
        newSoundFile = newSoundFile.encode('utf-8')
        targetSoundFile = targetSoundFile.encode('utf-8')
        currentTheme = self.get_sound_theme()
        if(os.path.exists(os.path.join(self.homedir, ".sounds") + currentTheme)):
            soundDir = os.path.join(self.homedir, ".sounds") + currentTheme
        elif(os.path.exists('/usr/share/sounds/' + currentTheme)):
            soundDir = '/usr/share/sounds/' + currentTheme
        else:
            pass

        shutil.copy(newSoundFile, soundDir + '/stereo/' + targetSoundFile)

    # restore sound file
    def restore_sound_file(self, targetSoundFile):
        targetSoundFile = targetSoundFile.encode('utf-8')
        bakDir = '/var/lib/kylin-assistant-daemon/sound-theme/'
        currentTheme = self.get_sound_theme()
        if(os.path.exists(os.path.join(self.homedir, ".sounds") + currentTheme)):
            soundDir = os.path.join(self.homedir, ".sounds") + currentTheme
        elif(os.path.exists('/usr/share/sounds/' + currentTheme)):
            soundDir = '/usr/share/sounds/' + currentTheme
        else:
            pass

        shutil.copy(bakDir + currentTheme + '/stereo/' + targetSoundFile, soundDir + '/stereo/' + targetSoundFile)

    # restore all sound file in current sound theme
    def restore_all_sound_file(self, soundTheme):
        bakSoundThemeDir = '/var/lib/kylin-assistant-daemon/sound-theme/' + soundTheme
        if(os.path.exists(os.path.join(self.homedir, ".sounds") + soundTheme)):
            soundDir = os.path.join(self.homedir, ".sounds") + soundTheme
        elif(os.path.exists('/usr/share/sounds/' + soundTheme)):
            soundDir = '/usr/share/sounds/' + soundTheme
        else:
            pass

        for soundFile in os.listdir(bakSoundThemeDir + '/stereo'):
            shutil.copy(bakSoundThemeDir + '/stereo/' + soundFile, soundDir + '/stereo/' + soundFile)

if __name__ == '__main__':
    sss = Sound()
# 	print sss.get_sound_themes()
#  	sss.restore_all_sound_file('ubuntu')
# 	print sss.get_login_music_enable()
# 	sss.set_login_music_enable(False)
#   print sss.get_sound_themes()
#	print sss.get_sound_theme()
    print(sss.get_sounds())
# sss.set_sound_theme('freedesktop')
