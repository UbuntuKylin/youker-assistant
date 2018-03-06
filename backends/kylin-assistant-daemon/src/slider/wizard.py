#! /usr/bin/env python3
# -*- coding: utf-8 -*-

### BEGIN LICENSE
# Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd
#
# Author:     Kobe Lee <xiangli@ubuntukylin.com>
# Maintainer: Ubuntu Kylin
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
import gtk
import gobject
import math
import locale
#samples:https://developer.gnome.org/pygtk/stable/class-gdkwindow.html

class TimeController(gobject.GObject):
    __gsignals__ = {
        'update': (gobject.SIGNAL_RUN_LAST, gobject.TYPE_NONE, (gobject.TYPE_FLOAT,)),
        'completed': (gobject.SIGNAL_RUN_LAST, gobject.TYPE_NONE, ()),
        }

    def __init__(self, timeout):
        gobject.GObject.__init__(self)
        self.timeout = timeout
        self.container = []

    def start(self):
        tmp = (self.timeout / 1000.0) * 30.0
        while len(self.container) <= tmp:
            curve = lambda x: math.sin(math.pi / 2 * x)
            self.container.append(curve(len(self.container) * (1.0 / tmp)))
        self.container.reverse()
        gobject.timeout_add(int(self.timeout / tmp), self.update)

    def update(self):
        self.emit('update', self.container.pop())
        if len(self.container) == 0:
            self.emit('completed')
            return False
        return True

class WizardEventBox(gtk.EventBox):
    __gsignals__ = { 'close': (gobject.SIGNAL_RUN_LAST, gobject.TYPE_NONE, ()),}
    def __init__(self, slider_icons=None, pointer_icons=None, button_icons=None):
        gtk.EventBox.__init__(self)
        self.set_visible_window(False)
        self.add_events(gtk.gdk.BUTTON_PRESS_MASK |gtk.gdk.POINTER_MOTION_MASK)
        # 显示图片事件
        self.connect("expose-event", self.on_expose_event)
        # 鼠标点击滑动点的事件
        self.connect("motion-notify-event", self.on_motion_notify)
        # 鼠标事件
        self.connect("button-press-event", self.on_button_press)
        # 幻灯片图片
        self.slider_pics = list(map(gtk.gdk.pixbuf_new_from_file, slider_icons))
        # 幻灯片总数
        self.icon_num = len(slider_icons)
        # 滑动圆点图片设置
        self.pointer_pic, self.pointer_pic_active = list(map(gtk.gdk.pixbuf_new_from_file, pointer_icons))
        # 开始按钮图片设置
        self.btn_pic, self.btn_pic_press = list(map(gtk.gdk.pixbuf_new_from_file, button_icons))
        button_size = 55
        self.pointer_dict = {}
        self.index = 0
        self.dsc_index = None
        slider_pixbuf = self.slider_pics[0]
        self.slider_width = slider_pixbuf.get_width()
        self.slider_height = slider_pixbuf.get_height()
        self.set_size_request(self.slider_width, self.slider_height)
        self.pointer_width = self.pointer_pic.get_width()
        self.pointer_height = self.pointer_pic.get_height()
        pointer_width = self.pointer_width * self.icon_num + 10 * (self.icon_num - 1)
        self.pointer_sx =  (self.slider_width - pointer_width) / 2
        self.pointer_y = self.slider_height -40
        # 开始按钮区域
        self.btn_rect = gtk.gdk.Rectangle((self.slider_width - self.btn_pic.get_width()) / 2,  self.slider_height - self.btn_pic.get_height() - button_size, self.btn_pic.get_width(), self.btn_pic.get_height())
        self.alpha = 1.0
        self.active_x = 0
        self.dsc_x = None
        self.slider_y = 0
        self.showing = False
        self.show_index = None
        gobject.timeout_add(2000, lambda : self.start_slider(1000))

    def draw_pixbuf(self, cr, pixbuf, x=0, y=0, alpha=1.0):
        if pixbuf != None:
            cr.set_source_pixbuf(pixbuf, x, y)
            cr.paint_with_alpha(alpha)

    def on_expose_event(self, widget, event):
        # samples:http://zetcode.com/gui/pygtk/drawing/
        cr = widget.window.cairo_create()
        rect = widget.allocation
        cr.save()
        self.draw_pixbuf(cr, self.slider_pics[self.index], rect.x + self.active_x,
                    rect.x + self.slider_y, self.alpha)
        if self.dsc_index != None and self.dsc_x != None:
            self.draw_pixbuf(cr, self.slider_pics[self.dsc_index], rect.x + self.dsc_x,
                        rect.y + self.slider_y, self.dsc_alpha)
        cr.restore()
        dot_start_x = rect.x + self.pointer_sx
        for i in range(self.icon_num):
            if self.dsc_index == None:
                if self.index == i:
                    dot_pixbuf = self.pointer_pic_active
                else:
                    dot_pixbuf = self.pointer_pic
            else:
                if self.dsc_index == i:
                    dot_pixbuf = self.pointer_pic_active
                else:
                    dot_pixbuf = self.pointer_pic
            pointer_rect = gtk.gdk.Rectangle(
                dot_start_x, rect.y + self.pointer_y,
                self.pointer_width, self.pointer_height)
            self.pointer_dict[i] = pointer_rect
            self.draw_pixbuf(cr, dot_pixbuf, dot_start_x, rect.y + self.pointer_y)
            offset = self.pointer_width + 10
            dot_start_x += offset
        if self.dsc_index == self.icon_num - 1:
            if self.button_hover_flag:
                pixbuf = self.btn_pic_press
            else:
                pixbuf = self.btn_pic
            self.draw_pixbuf(cr, pixbuf, rect.x + self.btn_rect.x, rect.y + self.btn_rect.y)
        return True

    def on_motion_notify(self, widget, event):
        self.show_index = None
        for index, rect in list(self.pointer_dict.items()):
            if rect.x <= event.x <= rect.x + rect.width and rect.y <= event.y <= rect.y + rect.height:
                self.window.set_cursor(gtk.gdk.Cursor(gtk.gdk.HAND2))
                self.show_index = index
                break
        else:
            self.show_index = None
            self.window.set_cursor(None)
        x, y, w, h = self.btn_rect
        if (event.x >= x and event.x <= x + w and event.y >= y and event.y <= y + h):
            self.button_hover_flag = True
        else:
            self.button_hover_flag = False
        self.queue_draw()

    def on_button_press(self, widget, event):
        # 当前不是空时，重新播放
        if self.show_index != None:
            self.start_slider(1000, self.show_index)
        # 点击“开始”按钮，关闭启动界面
        x, y, w, h = self.btn_rect
        if (event.x >= x and event.x <= x + w and event.y >= y and event.y <= y + h):
            self.emit("close")

    def start_slider(self, animation_time, dsc_index=None, direction="left"):
        if dsc_index is None:
            if self.index >= self.icon_num - 1:
                return False
                dsc_index = 0
            else:
                dsc_index = self.index + 1
        else:
            if dsc_index < self.index:
                direction = "right"

        if not self.showing:
            self.showing = True
            self.dsc_index = dsc_index
            self.timecontroller = TimeController(animation_time)
            self.timecontroller.connect("update", lambda source, status: self.update_slider(source, status, direction))
            self.timecontroller.connect("completed", lambda source: self.complete_slider(source, dsc_index))
            self.timecontroller.start()
        return True

    def update_slider(self, source, status, direction):
        self.alpha = 1.0 - status
        self.dsc_alpha = status
        if direction == "right":
            self.active_x = self.slider_width * status
            self.dsc_x = 0
        else:
            self.active_x = 0 - (self.slider_width * status)
            self.dsc_x = 0
        self.queue_draw()

    def complete_slider(self, source, index):
        self.index = index
        self.alpha = 1.0
        self.dsc_alpha = 0.0
        self.showing = False
        self.active_x = 0
        self.dsc_x = None
        self.queue_draw()

class Wizard(gtk.Window):
    def __init__(self):
        gtk.Window.__init__(self, gtk.WINDOW_TOPLEVEL)
        self.set_decorated(False)#去掉默认标题栏
        self.set_position(gtk.WIN_POS_CENTER)
        self.set_resizable(False)
        self.window_align = gtk.Alignment()
        self.window_box = gtk.VBox()
        # 图片与边框的距离
        self.window_align.set(0.0, 0.0, 1.0, 1.0)
        self.window_align.set_padding(2, 2, 2, 2)
        self.add(self.window_align)
        self.window_align.add(self.window_box)
        wizard_dir = "/usr/share/kylin-assistant/qml/img/zh_CN/wizard"
        wizard_root_dir = "/usr/share/kylin-assistant/qml/img/icons"
        slider_icons = (os.path.join(wizard_dir, "%d.png" % i) for i in range(3))
        pointer_icons = (os.path.join(wizard_root_dir, "dot_normal.png"), os.path.join(wizard_root_dir, "dot_active.png"))
        button_icons = (os.path.join(wizard_dir, "start_normal.png"), os.path.join(wizard_dir, "start_press.png"))
        self.event_box = WizardEventBox(slider_icons, pointer_icons, button_icons)
        self.event_box.connect("close", lambda widget: self.destroy())
        self.connect("destroy", self.destroy_wizard)
        self.window_box.add(self.event_box)
        # 鼠标拖动界面
        self.move_window_event(self.event_box)

    def destroy_wizard(self, widget):
        print('Kylin-Assistant slide show is over!')
        #widget.destory()

    def is_left_button(self, event):
        return event.button == 1

    def move_window(self, event, widget):#kobe
        if self.is_left_button(event):
            widget.set_can_focus(True)
            widget.grab_focus()
            self.begin_move_drag(event.button, int(event.x_root), int(event.y_root), event.time)
        return False

    def move_window_event(self, widget):
        widget.connect("button-press-event", lambda w, e: self.move_window(e, w))

    def show_slider(self):
        self.show_all()
        gtk.main()
