#!/usr/bin/python
# -*- coding: utf-8 -*-
### BEGIN LICENSE
# Copyright (C) 2007-2011 Tualatrix Chou <tualatrix@gmail.com>
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
import logging

from gi.repository import Gdk

log = logging.getLogger("gtk")

def set_busy(window):
    if window and window.get_parent_window():
        window.get_parent_window().set_cursor(Gdk.Cursor.new(Gdk.CursorType.WATCH))
        window.set_sensitive(False)

def unset_busy(window):
    if window and window.get_parent_window():
        window.get_parent_window().set_cursor(None)
        window.set_sensitive(True)

def post_ui(func):
    def func_wrapper(*args, **kwargs):
        Gdk.threads_enter()
        func(*args, **kwargs)
        Gdk.threads_leave()

    return func_wrapper

