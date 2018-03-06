#! /usr/bin/env python3
# -*- coding: utf-8 -*-

### BEGIN LICENSE
#
# Author:     Kobe Lee <xiangli@ubuntukylin.com>
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

import os
import sys
import subprocess
import shutil

# unzip -o test.zip -d /tmp/

HOME_PATH = os.path.expandvars('$HOME')

def generate_tmp_path(name):
    assert(isinstance(name, str))
#    dest_path = HOME_PATH + "/.config/ubuntukylin/kylin-assistant/"
    dest_path = HOME_PATH + "/.cache/kylin-assistant/"
    folder_path = dest_path + name
    if os.path.exists(folder_path):
        shutil.rmtree(folder_path)
    return dest_path

def unzip_resource(package_file):
    unziped_dir = generate_tmp_path("uk-img")
    if unziped_dir[len(unziped_dir)-1] != "/":
        unziped_dir = unziped_dir + "/"
    subprocess.call(["unzip", package_file, "-d", unziped_dir])
    dest_dir = unziped_dir + "uk-img/"
    if not os.path.exists(dest_dir):
        print(("unzip '%s' to '%s' failed" % (package_file , unziped_dir)))
        return False
    else:
        print("unzip ok....")
        return True
#        unziped_dir = unziped_dir + WS360_CHROME_PKGNAME
#        version = get_package_ver_from_manifest(unziped_dir)
#        if version == "0.0":
#            return False
#        extension_filedir = "/home/trusty/360-deb/"
#        shutil.copytree(unziped_dir, extension_filedir)
#        shutil.rmtree(unziped_dir)
#        return True

#unzip_resource("/home/trusty/uk-img.zip")






