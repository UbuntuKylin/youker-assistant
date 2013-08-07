import os
from common import get_dir_size



class CacheClean():
    def __init__(self):
        pass

    def get_apt_cache(self):
        apt_cache = '/var/cache/apt/archives'
        aptcachelist = map(lambda filename: '%s/%s<2_2>%s' % (apt_cache, filename, str(os.path.getsize('%s/%s' % (apt_cache, filename)))), filter(lambda filestr: filestr.endswith('deb'), os.listdir(apt_cache)))
        deb_num = len(aptcachelist)
        #print aptcachelist
        return aptcachelist

    def get_softwarecenter_cache(self):
        centercachelist = []
        softwarecenter_cache = '~/.cache/software-center/'
        full_path = os.path.expanduser(softwarecenter_cache)
        for one in os.listdir(full_path):
            tmp_path = full_path + one
            if os.path.isdir(tmp_path):
                size = get_dir_size(tmp_path)
                centercachelist.append('%s<2_2>%s' % (tmp_path, str(size)))
            else:
                centercachelist.append('%s<2_2>%s' % (tmp_path, str(os.path.getsize(tmp_path))))
        #print centercachelist
        return centercachelist

if __name__ == "__main__":
    obja = CacheClean()
    obja.get_apt_cache()
    obja.get_softwarecenter_cache()
