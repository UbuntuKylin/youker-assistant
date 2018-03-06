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

from gi.repository import Gio as gio
from .common import Schema
import logging

logger=logging.getLogger('kylin-assistant-daemon')

def get(schema, path, key, type):
    try:
        gs = gio.Settings(schema, path)
        return gs.__getattribute__('get_' + type)(key)
    except:
        logger.debug("gsettings.get: can't find value for %s" % gs)
        return None

def set(schema, path, key, type, value):
    try:
        gs = gio.Settings(schema, path)
        gs.__getattribute__('set_' + type)(key, value)
        return True
    except:
        logger.debug("gsettings.set: can't find value for %s" % gs)
        return False

def get_schema(schema):
    return gio.Settings(schema)

# added by kobe: access default schema value
def get_schema_value(schema, key):
    schema_default = Schema.load_schema(schema, key)
    if schema_default is not None:
        return schema_default
    else:
        raise NotImplemented
