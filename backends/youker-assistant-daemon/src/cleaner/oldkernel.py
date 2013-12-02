import os
#import apt
import apt_pkg
import re

import common

class OldKernel():
    def __init__(self):
        #cache = None
        self.flag = '(\w+-)*[.\d]+-\d+[\D]*'

    def scan_oldkernel_package(self):
        #pkgs = self.cache.packages
        cache = common.get_cache_list()
        final_oldkernel_list = []
        current_version = '-'.join(os.uname()[2].split('-')[:2])
        if cache:
            for pkg in cache:
                if pkg.is_installed and pkg.name.startswith('linux'):
                    if re.match(self.flag, pkg.name):
                        #version = pkg.installedVersion[:-3]
                        version = pkg.installed.version
                        if apt_pkg.version_compare(version, current_version) < 0:
                            #tmp_oldkernel_list = [pkg.name, common.confirm_filesize_unit(pkg.installedSize)]
                            #final_oldkernel_list.append('<2_2>'.join(tmp_oldkernel_list))
                            final_oldkernel_list.append(pkg)
        return final_oldkernel_list

if __name__ == "__main__":
    objo = OldKernel()
    #objo.get_the_kernel()
    aaa = objo.get_old_kernel()
    print aaa
    
