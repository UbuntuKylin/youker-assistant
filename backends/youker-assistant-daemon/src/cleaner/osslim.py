import sys
import apt
import apt_pkg
from apt.progress.base import InstallProgress

import common

class OsSlim():
    def __init__(self):
        pass

    def get_spare_packages(self):
        cache = common.get_cache_list()
        spare_packages_list = []
        if cache:
            for pkg in cache:
                if pkg.is_auto_removable and not pkg.name.startswith('linux'):
                #if pkg.is_installed and pkg.name.startswith('linux-headers'):
                    tmp_packages_list = [pkg.name, pkg.summary, str(pkg.installedSize)]
                    spare_packages_list.append('<2_2>'.join(tmp_packages_list))
        return spare_packages_list

if __name__ == '__main__':
    obj = OsSlim()
    obj.get_spare_packages()
    #obj.clean_spare_packages()
