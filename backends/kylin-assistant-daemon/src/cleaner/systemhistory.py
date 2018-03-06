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
from xml.etree import ElementTree

class SystemHistory():
    def __init__(self):
        pass

    def scan_the_xml(self, homedir):
        if homedir:
            xml_path = '%s/.local/share/' % homedir
        else:
            xml_path = os.path.expanduser('~/.local/share/')

        full_path = xml_path + 'recently-used.xbel'

        hreflist = []
        if os.path.exists(full_path):
            tree = ElementTree.parse(full_path)
            nodes = tree.findall("bookmark")
            for node in nodes:
                hreflist.append(node.get('href'))

        return hreflist

    def clean_the_xml(self, homedir):
        xml_path = '%s/.local/share/' % homedir
        full_path = xml_path + 'recently-used.xbel'

        if os.path.exists(full_path):
            tree = ElementTree.parse(full_path)
            root = tree.getroot()
            root .clear()

            tree.write(full_path, encoding="UTF-8", xml_declaration=None, default_namespace=None, method="xml")
