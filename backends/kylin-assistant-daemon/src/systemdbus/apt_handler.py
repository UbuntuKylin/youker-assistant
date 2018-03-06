#!/usr/bin/python3
# -*- coding: utf-8 -*-

import apt
import apt.progress.base as apb
from apt.debfile import DebPackage
from apt.cache import FetchFailedException

import locale

# application actions
class AppActions:
    INSTALLDEPS = "install_deps"
    INSTALLDEBFILE = "install_debfile"
    INSTALL = "install"
    REMOVE = "remove"
    UPGRADE = "upgrade"
    CANCEL = "cancel"
    APPLY = "apply_changes"
    PURCHASE = "purchase"
    UPDATE = "update"
    UPDATE_FIRST = "update_first"
    ADD_SOURCE = "add_source"
    REMOVE_SOURCE = "remove_source"
    GET_SOURCES = "get_sources"


class FetchProcess(apb.AcquireProgress):

    def __init__(self, dbus_service, appname, action):
        apb.AcquireProgress.__init__(self)
        self.dbus_service = dbus_service
        self.appname = appname
        self.action = action

    def done(self, item):
#        kwarg = {"download_appname":self.appname,
#                 "download_percent":str(self.percent),
#                 "action":str(self.action),
#                 }
        kwarg = []
        kwarg.append(self.appname)
        kwarg.append(str(self.percent))
        kwarg.append(str(self.action))

        self.dbus_service.youker_fetch_signal("down_done", kwarg)

    def fail(self, item):
#        kwarg = {"download_appname":self.appname,
#                 "download_percent":str(self.percent),
#                 "action":str(self.action),
#                 }
        kwarg = []
        kwarg.append(self.appname)
        kwarg.append(str(self.percent))
        kwarg.append(str(self.action))
        self.dbus_service.youker_fetch_signal("down_fail", kwarg)

    def fetch(self, item):
#        kwarg = {"download_appname":self.appname,
#                 "download_percent":str(self.percent),
#                 "action":str(self.action),
#                 }
        kwarg = []
        kwarg.append(self.appname)
        kwarg.append(str(self.percent))
        kwarg.append(str(self.action))
        self.dbus_service.youker_fetch_signal("down_fetch", kwarg)

    def ims_hit(self, item):
        print('ims_hit')
        pass

    def media_change(self, media, drive):
        print('media_change')
        pass

    def pulse(self, owner):

        if self.action == AppActions.UPDATE or self.action == AppActions.UPDATE_FIRST:
            if self.total_items!= 0:
                percent = float(self.current_items * 100.0 / self.total_items)
                if percent > self.percent:
                    self.percent = percent
        else:
            if self.total_bytes != 0:
                self.percent = float(self.current_bytes * 100.0 / self.total_bytes)

#        kwarg = {"download_appname":self.appname,
#                 "download_percent":str(self.percent),
#                 "download_bytes":str(self.current_bytes),
#                 "total_bytes":str(self.total_bytes),
#                 "download_items":str(self.current_items),
#                 "total_items":str(self.total_items),
#                 "action":str(self.action),
#                 }
        kwarg = []
        kwarg.append(self.appname)
        kwarg.append(str(self.percent))
        kwarg.append(str(self.action))
        kwarg.append(self.current_bytes)
        kwarg.append(str(self.total_bytes))
        kwarg.append(str(self.current_items))
        kwarg.append(str(self.total_items))
        self.dbus_service.youker_fetch_signal("down_pulse", kwarg)

        # cancel the operation
        if self.dbus_service.check_cancel_worker_item(self.appname) is True:
            print("download_cancel")
            self.dbus_service.youker_fetch_signal("down_cancel", kwarg)
            return False

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
        self.percent = 0

#        kwarg = {"download_appname":self.appname,
#                 "download_percent":str(self.percent),
#                 "action":str(self.action),
#                 }
        kwarg = []
        kwarg.append(self.appname)
        kwarg.append(str(self.percent))
        kwarg.append(str(self.action))
        self.dbus_service.youker_fetch_signal("down_start", kwarg)

    def stop(self):
#        kwarg = {"download_appname":self.appname,
#                 "download_percent":str(200),
#                 "action":str(self.action),
#                 }
        kwarg = []
        kwarg.append(self.appname)
        kwarg.append(str(200))
        kwarg.append(str(self.action))
        self.dbus_service.youker_fetch_signal("down_stop", kwarg)


class AptProcess(apb.InstallProgress):
    '''Apt progress'''
    def __init__(self, dbus_service, appname, action):
        apb.InstallProgress.__init__(self)
        self.dbus_service = dbus_service
        self.appname = appname
        self.percent = 0
        self.action = action

    def conffile(self, current, new):
        pass

    def error(self, pkg, errormsg):
#        kwarg = {"apt_appname":str(pkg),
#                 "apt_percent":str(self.percent),
#                 "action":str(self.action),
#                 }
        kwarg = []
        kwarg.append(str(pkg))
        kwarg.append(str(self.percent))
        kwarg.append(str(self.action))
        self.dbus_service.youker_apt_signal("apt_error", kwarg)

    def start_update(self):
#        kwarg = {"apt_appname":self.appname,
#                 "apt_percent":str(self.percent),
#                 "action":str(self.action),
#                 }
        kwarg = []
        kwarg.append(self.appname)
        kwarg.append(str(self.percent))
        kwarg.append(str(self.action))
        self.dbus_service.youker_apt_signal("apt_start", kwarg)

    def finish_update(self):
#        kwarg = {"apt_appname":self.appname,
#                 "apt_percent":str(200),
#                 "action":str(self.action),
#                 }
        kwarg = []
        kwarg.append(self.appname)
        kwarg.append(str(200))
        kwarg.append(str(self.action))
        self.dbus_service.youker_apt_signal("apt_finish", kwarg)

    def status_change(self, pkg, percent, status):
#        kwarg = {"apt_appname":str(pkg),
#                 "apt_percent":str(percent),
#                 "action":str(self.action),
#                 "status":str(status),
#                 }
        kwarg = []
        kwarg.append(str(pkg))
        kwarg.append(str(percent))
        kwarg.append(str(self.action))
        kwarg.append(str(status))
        self.dbus_service.youker_apt_signal("apt_pulse", kwarg)

class AptHandler():

    def __init__(self, dbus_service):
        self.dbus_service = dbus_service
        locale.setlocale(locale.LC_ALL, "zh_CN.UTF-8")
        self.cache = apt.Cache()
        self.cache.open()

    # get package by pkgName
    def get_pkg_by_name(self, pkgName):
        try:
            return self.cache[pkgName]
        except KeyError:
            raise WorkitemError(1, "Package %s is not  available" % pkgName)
        # except Exception, e:
        #     print e
        #     return "ERROR"

    # install deps
    def install_deps(self, path, kwargs=None):
        debfile = DebPackage(path)
        pkgName = debfile._sections["Package"]
        debfile.check()
        deps = debfile.missing_deps

        if(len(deps) > 0):
            self.cache.open()
            for pkgn in deps:
                pkg = self.get_pkg_by_name(pkgn)
                pkg.mark_install()

            try:
                self.cache.commit(FetchProcess(self.dbus_service, pkgName, AppActions.INSTALLDEPS), AptProcess(self.dbus_service, pkgName, AppActions.INSTALLDEPS))
            except Exception as e:
                print(e)
                print("install err")

    # install package
    def install(self, pkgName, kwargs=None):
        print("real install->", pkgName)
        self.cache.open()
        pkg = self.get_pkg_by_name(pkgName)
        print(pkg.installed.version)#1.2.0-0ubuntu1
        print(len(pkg.versions))#2
        print(pkg.versions[0].version)#1.3.1-0ubuntu1
        print(pkg.versions[1].version)#1.2.0-0ubuntu1
#        if pkg.is_installed:
#            raise WorkitemError(7, "Package %s  is installed" % pkgName)
        pkg.mark_install()

        try:
            self.cache.commit(FetchProcess(self.dbus_service, pkgName, AppActions.INSTALL), AptProcess(self.dbus_service, pkgName, AppActions.INSTALL))
        except apt.cache.FetchFailedException as error:
            raise WorkitemError(2, str(error))
        except apt.cache.LockFailedException:
            raise WorkitemError(3, "package manager is running.")
        except Exception as e:
            raise WorkitemError(0, "unknown error")
        # except Exception, e:
        #     print e
        #     print "install err"

    # update packages
    def upgrade(self, pkgNames, kwargs=None):
        self.cache.open()

        for pkgName in pkgNames:
            pkg = self.get_pkg_by_name(pkgName)
            pkg.mark_upgrade()

        try:
            self.cache.commit(FetchProcess(self.dbus_service, "#upgrade", AppActions.UPGRADE), AptProcess(self.dbus_service, "#upgrade", AppActions.UPGRADE))
        except apt.cache.FetchFailedException as error:
            raise WorkitemError(2, str(error))
        except apt.cache.LockFailedException:
            raise WorkitemError(3, "package manager is running.")
        except Exception as e:
            raise WorkitemError(0, "unknown error")
        # except Exception, e:
        #     print e
        #     print "update err"

    def upone(self, pkgName, kwargs=None):
        self.cache.open()
        pkg = self.get_pkg_by_name(pkgName)
        pkg.mark_install()

        try:
            self.cache.commit(FetchProcess(self.dbus_service, pkgName, AppActions.INSTALL), AptProcess(self.dbus_service, pkgName, AppActions.INSTALL))
        except apt.cache.FetchFailedException as error:
            raise WorkitemError(2, str(error))
        except apt.cache.LockFailedException:
            raise WorkitemError(3, "package manager is running.")
        except Exception as e:
            raise WorkitemError(0, "unknown error")

    # apt-get update
    def update(self, kwargs=None):
        quiet = False
        if kwargs is not None:
            quiet = int(kwargs["quiet"])

        try:
            if quiet == True:
                print("quiet=True")
                self.cache.update()
            else:
                print("quiet=False")
                self.cache.update(fetch_progress=FetchProcess(self.dbus_service, "#update", AppActions.UPDATE))
        except Exception as e:
            print(e)
            print("update except")


class WorkitemError(Exception):

    def __init__(self, errornum, details = ""):
        self.errornum = errornum
        self.details = details


if __name__ == "__main__":
    ad = AptHandler(None)
    ad.upgrade(['khelpcenter4'])
