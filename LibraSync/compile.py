import os
import sys
import subprocess

cmd = "gcc -o output/librasync librasync.c utility.c book.c user.c"

if len(sys.argv) > 1:
    if sys.argv[1] == 'y':
        if os.name == 'nt':
            subprocess.call('C:\\Windows\\System32\\WindowsPowerShell\\v1.0\\powershell.exe ' + cmd + " ; output/librasync.exe", shell=True)
            sys.exit()
        elif os.name == 'posix':
            cmd = "gcc -o output/librasync librasync.c utility.c book.c user.c && output/librasync"

os.system(cmd)