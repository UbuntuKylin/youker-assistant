#!/usr/bin/python
# -*- coding: utf-8 -*-

### BEGIN LICENSE

# Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd

# Author:
#     Shine Huang<shenghuang@ubuntukylin.com>
# Maintainer:
#     Shine Huang<shenghuang@ubuntukylin.com>

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


from PyQt4.QtGui import *
from PyQt4.QtCore import *
import sip

from models.globals import Globals


class CardWidget(QWidget):

    cardcount = 0
    number_per_row = -1
    itemwidth = -1
    itemheight = -1

    def __init__(self, itemwidth, itemheight, cardspacing, parent=None):
        QWidget.__init__(self, parent)

        self.itemwidth = itemwidth
        self.itemheight = itemheight
        self.cardspacing = cardspacing

        self.scrollArea = QScrollArea(self)
        self.cardPanel = QWidget()
        self.scrollArea.setWidget(self.cardPanel)
        self.scrollArea.setHorizontalScrollBarPolicy(Qt.ScrollBarAlwaysOff)
        self.scrollArea.setVerticalScrollBarPolicy(Qt.ScrollBarAsNeeded)

        self.verticalScrollBar().setStyleSheet("QScrollBar:vertical{margin:0px 0px 0px 0px;background-color:rgb(255,255,255,100);border:0px;width:6px;}\
             QScrollBar::sub-line:vertical{subcontrol-origin:margin;border:1px solid red;height:13px}\
             QScrollBar::up-arrow:vertical{subcontrol-origin:margin;background-color:blue;height:13px}\
             QScrollBar::sub-page:vertical{background-color:#EEEDF0;}\
             QScrollBar::handle:vertical{background-color:#D1D0D2;width:6px;} QScrollBar::handle:vertical:hover{background-color:#14ACF5;width:6px;}  QScrollBar::handle:vertical:pressed{background-color:#0B95D7;width:6px;}\
             QScrollBar::add-page:vertical{background-color:#EEEDF0;}\
             QScrollBar::down-arrow:vertical{background-color:yellow;}\
             QScrollBar::add-line:vertical{subcontrol-origin:margin;border:1px solid green;height:13px}")

    # calculate card number in one page in current screen resolution
    def calculate_software_step_num(self):
        number_per_row = (self.width() + self.cardspacing) / (self.itemwidth + self.cardspacing)
        number_per_column = (self.height() + self.cardspacing) / (self.itemheight + self.cardspacing)
        Globals.SOFTWARE_STEP_NUM = number_per_row * number_per_column + number_per_row
        # print "re calculate SOFTWARE_STEP_NUM == ", Globals.SOFTWARE_STEP_NUM

    # calculate data
    def calculate_data(self):
        # the 'QScrollArea' inside area is 1px smaller than 'QWidget', fix it.
        self.scrollArea.setGeometry(-1, -1, self.width() + 2, self.height() + 2)
        self.cardPanel.setGeometry(0, 0, self.width(), self.height())

        self.number_per_row = (self.width() + self.cardspacing) / (self.itemwidth + self.cardspacing)

    def reload_cards(self):
        self.calculate_data()

        cards = self.cardPanel.children()
        self.cardcount = 0

        for i in range(self.count()):
            self.add_card(cards[i])

        self.cardcount = self.count()

    def add_card(self, card):
        x = int(self.cardcount % self.number_per_row) * (self.itemwidth + self.cardspacing)
        y = int(self.cardcount / self.number_per_row) * (self.itemheight + self.cardspacing)

        # resize the widget to adapt items
        nowHeight = y + self.itemheight
        if(nowHeight >= self.cardPanel.height()):
            self.cardPanel.resize(self.cardPanel.width(), nowHeight)

        card.move(x, y)
        self.cardcount = self.cardcount + 1

    def verticalScrollBar(self):
        return self.scrollArea.verticalScrollBar()

    def scrollToTop(self):
        vsb = self.scrollArea.verticalScrollBar()
        vsb.setValue(0)

    # count the cards
    def count(self):
        cards = self.cardPanel.children()
        return len(cards)

    # remove all item
    def clear(self):
        cards = self.cardPanel.children()
        for card in cards:
            sip.delete(card)

        self.cardPanel.setGeometry(0, 0, self.width(), self.height())
        self.cardcount = 0