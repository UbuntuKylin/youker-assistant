import os
#import apt
import apt_pkg
import re

import common

class OldKernel():
    cache = None
    FLAG = '(\w+-)*[.\d]+-\d+[\D]*'
    def __init__(self):
        self.current_version = '-'.join(os.uname()[2].split('-')[:2])

    def get_old_kernel(self):
        #pkgs = self.cache.packages
        cache = common.get_cache_list()
        final_oldkernel_list = []
        if cache:
            for pkg in cache:
                if pkg.is_installed and pkg.name.startswith('linux'):
                    if re.match(self.FLAG, pkg.name):
                        version = pkg.installedVersion[:-3]
                        if apt_pkg.version_compare(version, self.current_version) < 0:
                            tmp_oldkernel_list = [pkg.name, common.confirm_filesize_unit(pkg.installedSize)]
                            final_oldkernel_list.append('<2_2>'.join(tmp_oldkernel_list))
        return final_oldkernel_list

if __name__ == "__main__":
    objo = OldKernel()
    objo.get_the_kernel()
    
