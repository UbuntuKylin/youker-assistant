#!/usr/bin/env python3
# -*- coding: utf-8 -*-

### BEGIN LICENSE
# Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd
# Author: Kobe Lee
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
#sudo apt-get install python-pygame
import os, sys
import time
import pygame
import pygame.camera
from pygame.locals import *
import threading

def get_local_format_time():
    '''
    year-month-day hour:minute:second
    2014-05-07 13:51:30
    '''
    local_date = time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(time.time()))
    return local_date

#class Capture(object):
class Capture(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self)
        pygame.init()
        pygame.camera.init()

    def judge_camera(self):
        clist = pygame.camera.list_cameras()#['/dev/video0']
        if not clist:
            return False
#           raise ValueError("Sorry, no cameras detected.")
        else:
            return True

    def call_camera(self):
        threading.Thread(target=self.call_camera_real, name='Capture').start()

    def call_camera_real(self):
        self.size = (640,480)
        self.clist = pygame.camera.list_cameras()#['/dev/video0']
        self.display = pygame.display.set_mode(self.size, 0)
        self.snapshot = pygame.surface.Surface(self.size, 0, self.display)
        self.cam = pygame.camera.Camera(self.clist[0], self.size,"RGB")
        self.cam.start()
        going = True
        timevalue = "00-00-00"
        while going:
            events = pygame.event.get()
            for e in events:
                if e.type == QUIT or (e.type == KEYDOWN and e.key == K_ESCAPE):
                    self.cam.stop()
                    pic_name = get_local_format_time() + '.png'
                    print(pic_name)
                    going = False
            if self.cam.query_image():
                self.snapshot = self.cam.get_image(self.snapshot)
            self.display.blit(self.snapshot, (0,0))
            pygame.display.flip()
        pic_path = os.path.expanduser('~') + '/' + pic_name
        #pic_path = os.path.join('/home/trusty', pic_name)
        #os.path.expanduser('~')
        #pic_name = '/home/trusty/' + timevalue + '.png'
        pygame.image.save(self.snapshot, pic_path)
        pygame.quit()
        #exit(0)

#if __name__ == '__main__':
#    mycam=Capture()
#    if mycam.judge_camera():
#        mycam.call_camera()

