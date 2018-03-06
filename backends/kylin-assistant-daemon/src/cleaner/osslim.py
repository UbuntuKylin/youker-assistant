import sys
import apt
import apt_pkg
from apt.progress.base import InstallProgress

from . import common

class OsSlim():
    def __init__(self):
        pass

    def get_unneed_packages(self):
        cache = common.get_cache_list()
        unneed_packages_list = []
        if cache:
            for pkg in cache:
                if pkg.is_auto_removable and not pkg.name.startswith('linux'):
                    unneed_packages_list.append('Name:' + pkg.name + ';' + 'Summary:' + pkg.installed.summary + ';' + 'Size:' + common.confirm_filesize_unit(pkg.installed.installed_size))
        return unneed_packages_list

    def get_spare_packages(self):
        cache = common.get_cache_list()
        spare_packages_list = []
        if cache:
            for pkg in cache:
                if pkg.is_auto_removable and not pkg.name.startswith('linux'):
                #if pkg.is_installed and pkg.name.startswith('linux-headers'):
                    tmp_packages_list = [pkg.name, pkg.installed.summary, common.confirm_filesize_unit(pkg.installed.installed_size)]
                    spare_packages_list.append('<2_2>'.join(tmp_packages_list))
        return spare_packages_list

    def scan_spare_packages(self):
        cache = common.get_cache_list()
        final_spare_list = []
        if cache:
            for pkg in cache:
                if pkg.is_auto_removable and not pkg.name.startswith('linux'):
                    final_spare_list.append(pkg)
        return final_spare_list


if __name__ == '__main__':
    obj = OsSlim()
    obj.get_spare_packages()
    #obj.clean_spare_packages()
