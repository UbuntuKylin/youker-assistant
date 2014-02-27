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

import ConfigParser
import os
import gsettings
from shutil import copy

class CloudConfig():
    def __init__(self, sysdaemon):
        self.sysdaemon = sysdaemon
        self.conf = ConfigParser.ConfigParser()
        self.home = os.path.expandvars('$HOME')
        self.youker_path = './'
        self.kuaipan_path = ''

    # write profiles
    def write_conf(self, section, conf_id, conf_schema, conf_path, conf_key, conf_type):
        value = gsettings.get(conf_schema, conf_path, conf_key, conf_type)
        if (conf_id in section):
            self.conf.set(conf_id, 'value', str(value))
        else:
            self.conf.add_section(conf_id)
            self.conf.set(conf_id, 'schema', conf_schema)
            self.conf.set(conf_id, 'path', conf_path)
            self.conf.set(conf_id, 'key', conf_key)
            self.conf.set(conf_id, 'type', conf_type)
            self.conf.set(conf_id, 'value', str(value))

    # Save system configuration
    def save_configuration_to_local_file(self, file_name):
        self.conf.read(file_name)
        sections = self.conf.sections()

    # 桌面图标显示控制-----------------------------
        #self.write_conf(sections, 'show_desktop_icons',
        #    'org.gnome.desktop.background',
        #    None, 'show-desktop-icons', 'boolean')
        self.write_conf(sections, 'show_homefolder',
            'org.gnome.nautilus.desktop',
            None, 'home-icon-visible', 'boolean')
        self.write_conf(sections, 'show_network',
            'org.gnome.nautilus.desktop',
            None, 'network-icon-visible', 'boolean')
        #self.write_conf(sections, 'show_trash',
        #    'org.gnome.nautilus.desktop',
        #    None, 'trash-icon-visible', 'boolean')
        #self.write_conf(sections, 'show_devices',
        #    'org.gnome.nautilus.desktop',
        #    None, 'volumes-visible', 'boolean')

    # 启动器设置----------------------------------
        self.write_conf(sections, 'launcher_autohide',
            'org.compiz.unityshell',
            '/org/compiz/profiles/unity/plugins/unityshell/',
            'launcher-hide-mode', 'int')
        self.write_conf(sections, 'launcher_icon_size',
            'org.compiz.unityshell',
            '/org/compiz/profiles/unity/plugins/unityshell/',
            'icon-size', 'int')

    # 触摸板设置-----------------------------------
        #self.write_conf(sections, 'touchpad_enable',
        #    'org.gnome.settings-daemon.peripherals.touchpad',
        #    None, 'touchpad-enabled', 'boolean')
        #self.write_conf(sections, 'type_scroll_bar',
        #    'com.canonical.desktop.interface',
        #    None, 'scrollbar-mode', 'string')
        #self.write_conf(sections, 'touchpad_scrolling_mode',
        #    'org.gnome.settings-daemon.peripherals.touchpad',
        #    None, 'scroll-method', 'string')
        #self.write_conf(sections, 'touch_horizontal_scrolling',
        #    'org.gnome.settings-daemon.peripherals.touchpad',
        #    None, 'horiz-scroll-enabled', 'boolean')

    # 字体设置-------------------------------------
        #self.write_conf(sections, 'default_font',
        #    'org.gnome.desktop.interface',
        #    None, 'font-name', 'string')
        #self.write_conf(sections, 'desktop_font',
        #    'org.gnome.nautilus.desktop',
        #    None, 'font', 'string')
        #self.write_conf(sections, 'document_font',
        #    'org.gnome.desktop.interface',
        #    None, 'document-font-name', 'string')
        #self.write_conf(sections, 'monospace_font',
        #    'org.gnome.desktop.interface',
        #    None, 'monospace-font-name', 'string')
        #self.write_conf(sections, 'window_title_font',
        #    'org.gnome.desktop.wm.preferences',
        #    None, 'titlebar-font', 'string')
        #self.write_conf(sections, 'font_zoom',
        #    'org.gnome.desktop.interface',
        #    None, 'text-scaling-factor', 'double')
        #self.write_conf(sections, 'font_hinting',
        #    'org.gnome.settings-daemon.plugins.xsettings',
        #    None, 'hinting', 'string')
        #self.write_conf(sections, 'font_antialiasing',
        #    'org.gnome.settings-daemon.plugins.xsettings',
        #    None, 'antialiasing', 'string')

    # 主题设置-------------------------------------
        #self.write_conf(sections, 'GTK_theme',
        #    'org.gnome.desktop.interface',
        #    None, 'gtk-theme', 'string')
        #self.write_conf(sections, 'window_theme',
        #    'org.gnome.desktop.wm.preferences',
        #    None, 'theme', 'string')
        #self.write_conf(sections, 'icon_theme',
        #    'org.gnome.desktop.interface',
        #    None, 'icon-theme', 'string')

    # 窗口设置--------------------------------------
        #self.write_conf(sections, 'window_button',
        #    'org.gnome.desktop.wm.preferences',
        #    None, 'button-layout', 'string')
        #self.write_conf(sections, 'menus_have_icons',
        #    'org.gnome.desktop.interface',
        #    None, 'menus-have-icons', 'boolean')
        #self.write_conf(sections, 'titlebar_wheel',
        #    'org.compiz.gwd',
        #    None, 'mouse-wheel-action', 'string')
        #self.write_conf(sections, 'titlebar_double',
        #    'org.gnome.desktop.wm.preferences',
        #    None, 'action-double-click-titlebar', 'string')
        #self.write_conf(sections, 'titlebar_middle',
        #    'org.gnome.desktop.wm.preferences',
        #    None, 'action-middle-click-titlebar', 'string')
        #self.write_conf(sections, 'titlebar_right',
        #    'org.gnome.desktop.wm.preferences',
        #    None, 'action-right-click-titlebar', 'string')

    # 文件管理器-----------------------------------
        #self.write_conf(sections, 'location_replace_pathbar',
        #    'org.gnome.nautilus.preferences',
        #    None, 'always-use-location-entry', 'boolean')
        #self.write_conf(sections, 'auto_mount_media',
        #    'org.gnome.desktop.media-handling',
        #    None, 'automount', 'boolean')
        #self.write_conf(sections, 'auto_open_folder',
        #    'org.gnome.desktop.media-handling',
        #    None, 'automount-open', 'boolean')
        #self.write_conf(sections, 'prompt_autorun_programs',
        #    'org.gnome.desktop.media-handling',
        #    None, 'autorun-never', 'boolean')
        #self.write_conf(sections, 'thumbnail_icon_size',
        #    'org.gnome.nautilus.icon-view',
        #    None, 'thumbnail-size', 'int')
        #self.write_conf(sections, 'thumbnail_cache_time',
        #    'org.gnome.desktop.thumbnail-cache',
        #    None, 'maximum-age', 'int')
        #self.write_conf(sections, 'thumbnail_cache_size',
        #    'org.gnome.desktop.thumbnail-cache',
        #    None, 'maximum-size', 'int')

        fd = open(file_name, 'w')
        self.conf.write(fd)
        fd.close()
        return True

    # system settings
    def setconf(self, conf_id):
        conf_schema = self.conf.get(conf_id, 'schema')
        conf_path = self.conf.get(conf_id, 'path')
        if conf_path == 'None':
            conf_path = None
        conf_key = self.conf.get(conf_id, 'key')
        conf_type = self.conf.get(conf_id, 'type')
        if conf_type == 'boolean' :
            conf_value = self.conf.getboolean(conf_id, 'value')
        elif conf_type == 'int' :
            conf_value = self.conf.getint(conf_id, 'value')
        elif conf_type == 'double' or conf_type == 'float' :
            conf_value = self.conf.getfloat(conf_id, 'value')
        else :
            conf_value = self.conf.get(conf_id, 'value')
        gsettings.set(conf_schema, conf_path, conf_key, conf_type, conf_value)
        if conf_id == 'launcher_autohide':
            self.sysdaemon.download_cloud_conf_signal('launcher_autohide')
        else if conf_id == 'launcher_icon_size':
            self.sysdaemon.download_cloud_conf_signal('launcher_icon_size')
        else if conf_id == 'show_homefolder':
            self.sysdaemon.download_cloud_conf_signal('show_homefolder')
        else if conf_id == 'show_network':
            self.sysdaemon.download_cloud_conf_signal('show_network')
    
    # Restore the system configuration
    def use_cloud_configuration(self, file_name):
        print file_name
        self.conf.read(file_name)
        sections = self.conf.sections()
        for conf_id in sections:
            self.setconf(conf_id)
        return True

    # Get kuaipan directory address
    def get_kuaipan_path(self):
        kpconf = ConfigParser.ConfigParser()
        kpconf.read(self.home + '/.config/ubuntukylin/kuaipan4uk.conf')
        return kpconf.get('client-info', 'Root')
        
    # Determine whether kuaipan process starts
    def kuaipan_run(self):
        ps = os.popen('pgrep kuaipan4uk')
        kuaipan_ps = ps.read()
        ps.close()
        return kuaipan_ps

    # Configuration file upload
    def upload_kysoft_cloud_conf(self):
        if not self.kuaipan_run():
        # 快盘没有启动或没有安装，提示用户安装并启动快盘才能上传
            self.sysdaemon.upload_cloud_conf_signal('upload_norun')
            return
        self.kuaipan_path = self.get_kuaipan_path() + '/[Ubuntu Kylin Sync]'
        if not os.path.isdir(self.kuaipan_path):
            os.makedirs(self.kuaipan_path)
        self.kuaipan_path = self.kuaipan_path + '/youker-assistant'
        if not os.path.isdir(self.kuaipan_path):
            os.makedirs(self.kuaipan_path)
        self.youker_path = self.home + '/.config/ubuntukylin/youker-assistant/'
        youker_abs_path = self.youker_path + 'youker-cloud.conf'
        self.save_configuration_to_local_file(youker_abs_path)
        copy(youker_abs_path, self.kuaipan_path)
        self.sysdaemon.upload_cloud_conf_signal('upload_ok')

    # Configuration file download
    def download_kysoft_cloud_conf(self):
        if not self.kuaipan_run():
        # 快盘没有启动或没有安装，提示用户安装并启动快盘才能下载
            self.sysdaemon.download_cloud_conf_signal('download_norun')
            return
        self.youker_path = self.home + '/.config/ubuntukylin/youker-assistant/'
        youker_abs_path = self.youker_path + 'youker-cloud.conf'
        if not os.path.exists(youker_abs_path):
            os.mknod(youker_abs_path)
        cloud_abs_path = self.get_kuaipan_path() + '/[Ubuntu Kylin Sync]/youker-assistant/youker-cloud.conf'
        if not os.path.isfile(cloud_abs_path):
        # 云端没有备份的配置文件
            self.sysdaemon.download_cloud_conf_signal('download_notconf')
            return
        copy(cloud_abs_path, self.youker_path)
        self.use_cloud_configuration(youker_abs_path)
        self.sysdaemon.download_cloud_conf_signal('download_ok')

if __name__ == '__main__':
    cc = CloudConfig(None)
    #cc.upload_kysoft_cloud_conf()
    #cc.download_kysoft_cloud_conf()

