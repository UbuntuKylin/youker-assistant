#!/usr/bin/python3
# -*- coding: utf-8 -*-

import os, sys, shutil, tempfile
import subprocess

# ensure that single instance of applet is running for each user
class SingleInstance(object):

    #Initialize, specifying a path to store pids
    def __init__(self,pidPath):

        self.pidPath = pidPath
        self.lasterror = False
        if os.path.exists(pidPath):
            # Make sure it is not a "stale" pidFile
            pid = open(pidPath, 'r').read().strip()
            # Check list of running pids, if not running it is stale so overwrite
            pidRunning = subprocess.getoutput('ls -1 /proc | grep ^%s$' % pid)
            self.lasterror = True if pidRunning else False
        else:
            self.lasterror = False

        if not self.lasterror:
            # Create a temp file, copy it to pidPath and remove temporary file
            (fp, temp_path) = tempfile.mkstemp()
            try:
                os.fdopen(fp, "w+b").write(bytes(os.getpid()))
                shutil.copy(temp_path, pidPath)
                os.unlink(temp_path)
            except Exception as e:
                print(str(e))

    def is_already_running(self):
         return self.lasterror

    def __del__(self):
         if not self.lasterror and os.path.exists(self.pidPath):
            os.unlink(self.pidPath)
