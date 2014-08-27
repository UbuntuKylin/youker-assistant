#!/usr/bin/env python
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
#        self.going = True
#        self.size = (640,480)
#        self.display = pygame.display.set_mode(self.size, 0)
#        self.snapshot = pygame.surface.Surface(self.size, 0, self.display)
#        self.clist = pygame.camera.list_cameras()#['/dev/video0']
#        if not self.clist:
#           raise ValueError("Sorry, no cameras detected.")
#        self.cam = pygame.camera.Camera(self.clist[0], self.size,"RGB")
#        self.cam.start()

    def judge_camera(self):
        clist = pygame.camera.list_cameras()#['/dev/video0']
#        self.clist = pygame.camera.list_cameras()#['/dev/video0']
        if not clist:
            return False
#           raise ValueError("Sorry, no cameras detected.")
        else:
            return True

#    def get_and_flip(self):
#        if self.cam.query_image():
#            self.snapshot = self.cam.get_image(self.snapshot)
#	self.display.blit(self.snapshot, (0,0))
#        pygame.display.flip()

#    def take_a_pic(self):
#        print 'start take...'
#        pic_name = self.timevalue + '.png'
#        pygame.image.save(self.snapshot, pic_name)
##        os.path.join(os.path.expanduser('~'), pic_name)

#    def call_camera(self):
#        self.size = (640,480)
#        self.display = pygame.display.set_mode(self.size, 0)
#        self.snapshot = pygame.surface.Surface(self.size, 0, self.display)
#        self.cam = pygame.camera.Camera(self.clist[0], self.size,"RGB")
#        self.cam.start()
#        threading.Thread(target=self.call_camera_real, name='Capture').start()

#    def call_camera_real(self):
##        going = True
##        self.size = (640,480)
##        self.display = pygame.display.set_mode(self.size, 0)
##        self.snapshot = pygame.surface.Surface(self.size, 0, self.display)
##        self.cam = pygame.camera.Camera(self.clist[0], self.size,"RGB")
##        self.cam.start()
#        while self.going:
#            events = pygame.event.get()
#            self.get_and_flip()
##            for e in events:
##                if e.type == QUIT or (e.type == KEYDOWN and e.key == K_ESCAPE):
##                    self.get_picture()
##                    self.cam.stop()
##                    self.timevalue = get_local_format_time()
##                    going = False
##            self.get_and_flip()

#    def get_picture(self):
#        print 'aaaaa'
#        self.timevalue = get_local_format_time()
#        print self.timevalue
#        self.going = False
#        self.take_a_pic()
#        print 'bbbbbb'
#        self.cam.stop()
#        print 'ccccccccccc'

#    def kill_camera(self):
#        self.cam.stop()

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
                    print pic_name
                    going = False
            if self.cam.query_image():
                self.snapshot = self.cam.get_image(self.snapshot)
            self.display.blit(self.snapshot, (0,0))
            pygame.display.flip()
#	print os.path.expanduser('~')
	pic_path = os.path.expanduser('~') + '/' + pic_name
        #pic_path = os.path.join('/home/trusty', pic_name)
	#os.path.expanduser('~')
        #pic_name = '/home/trusty/' + timevalue + '.png'
        pygame.image.save(self.snapshot, pic_path)
        pygame.quit()
        #exit(0)

#    def main(self):
#        going1 = True
#        while going1:
#            events = pygame.event.get()
#            for e in events:
#                if e.type == QUIT or (e.type == KEYDOWN and e.key == K_ESCAPE):
#                    self.cam.stop()
#                    self.timevalue = get_local_format_time()
#                    going1 = False
#            self.get_and_flip()
#        self.take_a_pic()


#print os.path.expanduser('~')
if __name__ == '__main__':
    mycam=Capture()
    if mycam.judge_camera():
        mycam.call_camera()
#    if mycam.judge_camera():
#        mycam.main()
    #mycam.call_camera()
    #mycam.get_picture()

