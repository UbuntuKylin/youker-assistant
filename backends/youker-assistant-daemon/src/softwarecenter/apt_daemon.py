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
import apt.progress.base as apb
from sudodbus.daemon import SudoDaemon

class FetchProcess(apb.AcquireProgress):
	'''Fetch Process'''
	def __init__(self, sudoDaemon):
		apb.AcquireProgress.__init__(self)
		self.sudoDaemon = sudoDaemon

	def done(self, item):
		print 'all items download finished'
		self.sudoDaemon.software_fetch_signal("done", None)

	def fail(self, item):
		print 'download failed'
		self.sudoDaemon.software_fetch_signal("fail", None)

	def fetch(self, item):
		print 'one item download finished'
		self.sudoDaemon.software_fetch_signal("fetch", None)

	def ims_hit(self, item):
		print 'ims_hit'

	def media_change(self, media, drive):
		print 'media_change'

	def pulse(self, owner):
# 		print 'owner: ', owner
# 		print 'current_cps: ', self.current_cps
# 		print 'elapsed_time: ', self.elapsed_time
# 		print 'fetched_bytes: ', self.fetched_bytes
# 		print 'last_bytes: ', self.last_bytes
		self.sudoDaemon.software_fetch_signal("pulse", 
											"download_bytes:" + self.current_bytes
											+ ",total_bytes:" + self.total_bytes
											+ ",download_items:" + self.current_items
											+ ",total_items:" + self.total_items)

	def start(self):
		# Reset all our values.
		self.current_bytes = 0.0
		self.current_cps = 0.0
		self.current_items = 0
		self.elapsed_time = 0
		self.fetched_bytes = 0.0
		self.last_bytes = 0.0
		self.total_bytes = 0.0
		self.total_items = 0
		print 'fetch progress start ...'
		self.sudoDaemon.software_fetch_signal("start", None)

	def stop(self):
		print 'fetch progress stop ...'
		self.sudoDaemon.software_fetch_signal("stop", None)


class AptProcess(apb.InstallProgress):
	'''Apt progress'''
	def __init__(self, sudoDaemon):
		apb.InstallProgress.__init__(self)
		self.sudoDaemon = sudoDaemon

	def conffile(self, current, new):
		print 'there is a conffile question'

	def error(self, pkg, errormsg):
		self.sudoDaemon.software_apt_signal("error", None)

	def start_update(self):
		print 'apt process start work'
		self.sudoDaemon.software_apt_signal("start", None)

	def finish_update(self):
		print 'apt process finished'
		self.sudoDaemon.software_apt_signal("stop", None)

	def status_change(self, pkg, percent, status):
		print str(int(percent)) + "%  status : " + status
		self.sudoDaemon.software_apt_signal("pulse", "percent:" + str(int(percent)) + ",status:" + status)

class AptDaemon:
	def __init__(self, sudoDaemon):
		self.sudoDaemon = sudoDaemon
		self.ca = apt.Cache()
		self.ca.open()
# 		self.pkgNameList = []
# 		for pkg in self.ca:
# 			self.pkgNameList.append(pkg.name)

	# get package by pkgName
	def get_pkg_by_name(self, pkgName):
		return self.ca[pkgName]

	# install package
	def install_pkg(self, pkgName):
		self.ca.open()
		pkg = self.get_pkg_by_name(pkgName)
		pkg.mark_install()
		
		try: 
			self.ca.commit(FetchProcess(self.sudoDaemon), AptProcess(self.sudoDaemon))
		except Exception, e:
			print e
			print "install err"

	# uninstall package
	def uninstall_pkg(self, pkgName):
		self.ca.open()
		pkg = self.get_pkg_by_name(pkgName)
		pkg.mark_delete()
		
		try:
			self.ca.commit(None, AptProcess(self.sudoDaemon))
		except Exception, e:
			print e
			print "uninstall err"

	# update package
	def update_pkg(self, pkgName):
		self.ca.open()
		pkg = self.get_pkg_by_name(pkgName)
		pkg.mark_update()
		
		try:
			self.ca.commit(FetchProcess(self.sudoDaemon), AptProcess(self.sudoDaemon))
		except Exception, e:
			print e
			print "update err"

	# check package status by pkgName, i = installed u = can update n = notinstall
	def check_pkg_status(self, pkgName):
		self.ca.open()
		pkg = self.get_pkg_by_name(pkgName)
		if(pkg.is_installed):
			if(pkg.is_upgradable):
				return "u"
			else:
				return "i"
		else:
			return "n"

	# check packages status by pkgNameList, i = installed u = can update n = notinstall
	def check_pkgs_status(self, pkgNameList):
		self.ca.open()
		pkgStatusDict = {}
		for pkgName in pkgNameList:
			pkg = self.get_pkg_by_name(pkgName)
			if(pkg.is_installed):
				if(pkg.is_upgradable):
					pkgStatusDict[pkgName] = "u"
				else:
					pkgStatusDict[pkgName] = "i"
			else:
				pkgStatusDict[pkgName] = "n"

		self.sudoDaemon.software_check_status_signal(pkgStatusDict)
		return pkgStatusDict

# 	def get_pkgs_name_list(self):
# 		return self.pkgNameList
# 
# 	def search_pkgs_name(self, pkgName):
# 		if pkgName in self.pkgNameList:
# 			return pkgName
# 		else:
# 			rtns = []
# 			for name in self.pkgNameList:
# 				if name.find(pkgName) >= 0:
# 					rtns.append(name)
# 			return rtns

if __name__ == "__main__":
	ad = AptDaemon()
	
# 	print ad.check_pkgs_status(["gedit", "cairo-dock", "unity"])
	
	while True:
		print "\ninput your command: "
		cmd = raw_input()
		if cmd == "l":
			for name in ad.pkgNameList:
				print name + "\n"
		elif cmd == "i":
			print "input pkgName to install: "
			pkgName = raw_input()
			ad.install_pkg(pkgName)
		elif cmd == "n":
			print "input pkgName to uninstall: "
			pkgName = raw_input()
			ad.uninstall_pkg(pkgName)
		elif cmd == "u":
			print "input pkgName to update: "
			pkgName = raw_input()
			ad.update_pkg(pkgName)
		elif cmd == "c":
			print "input pkgName to check status: "
			pkgName = raw_input()
			print ad.check_pkg_status(pkgName)
		else:
			print "nothing..."

# 	print ad.get_pkg_by_name('gedit')
	# pnl = ad.getpkglist()
	# print len(pnl)
# 	name1 = ad.search_pkgs_name('wesnoth-1.10-core')
# 	print name1
	# print 'aaa' + str(1)
# 	ad.install_pkg(name1)
# 	ad.uninstall_pkg(name1)
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