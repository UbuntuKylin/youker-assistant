#!/usr/bin/python
# -*- coding: utf-8 -*-
### BEGIN LICENSE
# Copyright (C) 2010 TualatriX <tualatrix@gmail.com>
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
import os
import time
import stat
from gettext import ngettext
from gi.repository import Gtk
import gettext
from gettext import gettext as _

NO_UPDATE_WARNING_DAYS = 7

# The following two function are copyed from UpdateManager/UpdateManager.py
def _get_last_apt_get_update_hours():
    """
    Return the number of hours since the last successful apt-get update
      
    If the date is unknown, return "None"
    """
    if not os.path.exists("/var/lib/apt/periodic/update-success-stamp"):
        return None
    # calculate when the last apt-get update (or similar operation)
    # was performed
    mtime = os.stat("/var/lib/apt/periodic/update-success-stamp")[stat.ST_MTIME]
    ago_hours = int((time.time() - mtime) / (60*60) )
    return ago_hours

def _get_last_apt_get_update_text():
    """
    return a human readable string with the information when
    the last apt-get update was run
    """
    ago_hours = _get_last_apt_get_update_hours()
    if ago_hours is None:
        return _("It is unknown when the package information was "
                 "updated last. Please try clicking on the 'Check' "
                 "button to update the information.")
    ago_days = int( ago_hours / 24 )
    if ago_days > NO_UPDATE_WARNING_DAYS:
        return _("The package information was last updated %(days_ago)s "
                 "days ago.\n"
                 "Press the 'Check' button below to check for new software "
                 "updates.") % { "days_ago" : ago_days, }
    elif ago_days > 0:
        return ngettext("The package information was last updated %(days_ago)s day ago.",
                        "The package information was last updated %(days_ago)s days ago.",
                        ago_days) % { "days_ago" : ago_days, }
    elif ago_hours > 0:
        return ngettext("The package information was last updated %(hours_ago)s hour ago.",
                        "The package information was last updated %(hours_ago)s hours ago.",
                        ago_hours) % { "hours_ago" : ago_hours, }
    else:
        return _("The package information was last updated less than one hour ago.")
    return None

def updateinfo():
    __icon__ = 'system-software-update'
    __title__ = _('Your system is up-to-date')
    return _get_last_apt_get_update_text()

UPDATE_TIME = updateinfo()

if __name__ == '__main__':
    updateinfo()
