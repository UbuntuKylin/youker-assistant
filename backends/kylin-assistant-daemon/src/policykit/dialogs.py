#!/usr/bin/python3
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

import _thread

from gi.repository import GObject, Gtk, Gdk

class BaseDialog(Gtk.MessageDialog):
    def __init__(self, **kwargs):
        title = kwargs.pop('title', '')
        message = kwargs.pop('message', '')

        GObject.GObject.__init__(self, **kwargs)

        if title:
            self.set_title(title)

        if message:
            self.set_content(message)

    def set_title(self, title):
        self.set_markup('<big><b>%s</b></big>' % title)

    def set_content(self, message):
        if self.get_property('text'):
            self.format_secondary_markup(message)
        else:
            self.set_markup(message)
    
    def launch(self):
        self.run()
        self.destroy()

    def add_option_button(self, button):
        '''Add an option button to the left. It will not grab the default response.'''
        vbox = self.get_content_area()
        hbuttonbox = vbox.get_children()[-1]

        hbox = Gtk.HBox(spacing=12)
        vbox.pack_start(hbox, False, False, 0)
        vbox.remove(hbuttonbox)

        new_hbuttonbox = Gtk.HButtonBox()
        new_hbuttonbox.set_layout(Gtk.ButtonBoxStyle.START)
        new_hbuttonbox.pack_start(button, True, True, 0)

        hbox.pack_start(new_hbuttonbox, True, True, 0)
        hbox.pack_start(hbuttonbox, True, True, 0)

        hbuttonbox.get_children()[-1].grab_focus()

        vbox.show_all()


class ErrorDialog(BaseDialog):
    def __init__(self, title='', message='', parent=None,
                 type=Gtk.MessageType.ERROR, buttons=Gtk.ButtonsType.OK):
        BaseDialog.__init__(self, title=title, message=message,
                            parent=parent, message_type=type, buttons=buttons)
