import sys
import apt
import apt_pkg
from apt.progress.base import InstallProgress
from apt.progress.text import AcquireProgress

import common

class TextInstallProgress(InstallProgress):
    def __init__(self):
        InstallProgress.__init__(self)

    def error(self, errorstr):
        print ("got dpkg error: '%s'" % errorstr)

class OsSlim():
    def __init__(self):
        self.cache = common.get_cache_list()

    def get_spare_packages(self):
        spare_packages_list = []
        if self.cache:
            for pkg in self.cache:
                if pkg.is_auto_removable and not pkg.name.startswith('linux'):
                #if pkg.is_installed and pkg.name.startswith('linux-headers'):
                    tmp_packages_list = [pkg.name, pkg.summary, str(pkg.installedSize)]
                    spare_packages_list.append('<2_2>'.join(tmp_packages_list))
        return spare_packages_list

    def clean_spare_packages(self):
        fprogress = apt.progress.TextFetchProgress()
        fprogress = AcquireProgress()

        for pkg in self.spare_packages:
            pkg.mark_delete()
        #self.cache.commit(install_progress=apt.progress.base.InstallProgress())
        flag = self.cache.commit(fprogress, iprogress)

if __name__ == '__main__':
    obj = OsSlim()
    obj.get_spare_packages()
    #obj.clean_spare_packages()
