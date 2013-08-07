#!/usr/bin/python
# -*- coding: utf-8 -*-
### BEGIN LICENSE

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

import apt
import apt_pkg
import sys, os
import apt.progress.base as apb

class FetchProcess(apb.AcquireProgress):
	'''Fetch Process'''
	def __init__(self):
		apb.AcquireProgress.__init__(self)

	def done(self, item):
		print 'done la done la !!!'

	def fail(self, item):
		print 'fail la fail la !!!'

	def fetch(self, item):
		print 'fetch la fetch la !!!'

	def ims_hit(self, item):
		print 'ims_hit la !!!'

	def media_change(self, media, drive):
		print 'media change la !!!'

	def pulse(self, owner):
# 		print 'pulse pulse pluse ...', owner
		print 'current_bytes: ', self.current_bytes
		print 'current_cps: ', self.current_cps
		print 'current_items: ', self.current_items
		print 'elapsed_time: ', self.elapsed_time
		print 'fetched_bytes: ', self.fetched_bytes
		print 'last_bytes: ', self.last_bytes
		print 'total_bytes: ', self.total_bytes
		print 'total_items: ', self.total_items

	def start(self):
		print 'fetch progress is start ...'

	def stop(self):
		print 'fetch progress is stop ...'


class AptProcess(apb.InstallProgress):
    '''Install progress'''
    def __init__(self):
        apb.InstallProgress.__init__(self)

    def conffile(self, current, new):
        # global_event.emit("action-conffile", (current, new))

        # log("conffile: %s %s" % (current, new))
        print 'conffile wo ca!'
        
    def error(self, errorstr):
        # global_event.emit("action-error", (self.pkg_name, errorstr))
        # log("error: %s" % errorstr)
        print 'ERROR la !!!'

    def start_update(self):
        '''Start update.'''
        # log("start action...")
        print 'kai shi le kaishile !!!'
        
    def status_change(self, pkg, percent, status):
        '''Progress status change.'''
        # global_event.emit("action-update", (self.pkg_name, self.action_type, int(percent), status))
        # log((self.pkg_name, self.action_type, int(percent), status))
        print '\n' + str(int(percent)) + "%  zhuangtai: " + status

class AptDaemon:
	def __init__(self):
		self.ca = apt.Cache()
		# self.ca.update()
		self.ca.open()
		self.pkgList = []
		self.pkgNameList = []
		for pkg in self.ca:
			self.pkgList.append(pkg)
			self.pkgNameList.append(pkg.name)

	def get_pkg_by_name(self, pkgname):
		return self.ca[pkgname]

	def install_pkg(self, pkgname):
		pkg = self.get_pkg_by_name(pkgname)
		pkg.mark_install()
		self.ca.commit(FetchProcess(), AptProcess())
		# self.ca.commit()

	def uninstall_pkg(self, pkgname):
		pkg = self.get_pkg_by_name(pkgname)
		pkg.mark_delete()
		# self.ca.commit(apt.progress.TextFetchProgress(), apt.progress.InstallProgress())
		self.ca.commit(None, AptProcess())

	def get_pkgs_name_list(self):
		return self.pkgNameList

	def search_pkgs_name(self, pkgname):
		if pkgname in self.pkgNameList:
			return pkgname
		else:
			rtns = []
			for name in self.pkgNameList:
				if name.find(pkgname) >= 0:
					rtns.append(name)
			return rtns

if __name__ == "__main__":
	ad = AptDaemon()
	# pnl = ad.getpkglist()
	# print len(pnl)
	name1 = ad.search_pkgs_name('wesnoth-1.10-core')
	print name1
	# print 'aaa' + str(1)
# 	ad.install_pkg(name1)
	ad.uninstall_pkg(name1)
	# p = ad.get_pkg_by_name(name1)
	# print p.id
	# c = AptCache()
	# c.hahaha()
	# print c.hahaha()
	# pkgs = []
	# ca = apt.Cache()
	# i = 0
	# for a in ca:
	# 	i += 1
	# 	pkgs.append(a.name)
		# print a.name
	# print i
	# nanop = ca['nano']
	# print nanop
	# nanop.mark_install()
	# ca.commit()