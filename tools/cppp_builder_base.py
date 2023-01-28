#!/bin/env python3
'''
 * @package cppp_builder_base
 * @file tools/cppp_builder_base.py
 * @copyright Copyright (C) 2023
 * @date 2023-1-27
 * @language Python
 * @brief C++ Plus Builder console base

C++ Plus builder base library
C++ Plus builder tty console support

LICENCE Unlicense

This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>
'''
from subprocess import *
import os
import sys
import platform
import ctypes
import time
#output console is tty
output_is_tty=sys.stdout.isatty()
#set tty console title 
def title(t):
    if(output_is_tty):
        sys.stdout.write("\033]0;%s3\007" % str(t))

#color output
def cprint(color,text,end="\n",file=sys.stdout):
    if(output_is_tty):
        file.write(f'\x1b[{str(color)}m{str(text)+str(end)}\x1b[0m')
    else:
        file.write(str(text)+str(end))
    file.flush()
#print output
def printf(text,end="",file=sys.stdout):
    cprint(colors["white"],text,end,file)
#color codes
colors={}
if(platform.uname()[0]!="Windows" or output_is_tty):
    #tty color code
    colors["white"]=37
    colors["black"]=30
    colors["red"]=31
    colors["green"]=32
    colors["yellow"]=33
    colors["blue"]=34
else:
    #Windows console color code
    colors["white"]=7
    colors["black"]=0
    colors["red"]=4
    colors["green"]=2
    colors["yellow"]=6
    colors["blue"]=1

#Windows std output handle
_hConsole=0
#update Windows tty console
if(platform.uname()[0]=="Windows"):
    try:
        if(output_is_tty):
            nullio=open(os.devnull,"w+")
            try:
                cp=ctypes.windll.kernel32.GetConsoleCP()
            except:
                cp=65001#utf-8 code page
            
            path=os.path.join(os.getenv("SystemRoot","C:\\WINDOWS"),"System32","chcp.com")#%SystemRoot%\System32\chcp.com
            Popen([path,str(cp),">",os.devnull],shell=True,stdout=sys.stdout,stderr=nullio,cwd=os.getcwd()).wait()#reload codepage
        
        _hConsole=ctypes.windll.kernel32.GetStdHandle(-11)#STD_OUTPUT_HANDLE
        def _title(t):
            ctypes.windll.kernel32.SetConsoleTitleW(t)
        if(not output_is_tty):
            def _cprint(color,text,end="\n",file=sys.stdout):
                ctypes.windll.kernel32.SetConsoleTextAttribute(_hConsole, color)
                file.write(text+end)
                file.flush()
                ctypes.windll.kernel32.SetConsoleTextAttribute(_hConsole, colors["white"])
            cprint=_cprint
        title=_title
        nullio.close()
    except:
        pass

#Logger static class
class Logger:
    #log file
    file=sys.stderr
    #output log
    def log(color,lvl,msg):
        tit=f"[{lvl} {time.asctime()}] "
        cprint(color,tit,"",Logger.file)
        printf(msg,"\n",Logger.file)
    #info
    def info(text):
        Logger.log(colors["white"],"INFO",str(text))
    #warning
    def warn(text):
        Logger.log(colors["yellow"],"WARN",str(text))
    #error
    def error(text):
        Logger.log(colors["red"],"ERROR",str(text))
    #success
    def suc(text):
        Logger.log(colors["green"],"SUC",str(text))
    #debug
    def debug(text):
        Logger.log(colors["blue"],"DEBUG",str(text))
log=Logger

#mkdir noexcept
def mkdir(path):
    path=str(path)
    try:
        os.makedirs(path)
        log.info(f"mkdir: {path}")
    except Exception as e:
        log.error(f"mkdir: {path}: {str(e)}")
#remove file noexcept
def rm(path):
    path=str(path)
    try:
        os.remove(path)
        log.info(f"remove: {path}")
    except Exception as e:
        log.error(f"remove: {path}: {str(e)}")
#remove dir noexcept
def rmdir(path):
    path=str(path)
    try:
        os.rmdir(path)
        log.info(f"rmdir: {path}")
    except Exception as e:
        log.error(f"rmdir: {path}: {str(e)}")

#get progress bar
def getprogbar(pre,barsize):
    return "["+"#"*int(barsize*pre)+" "*int(barsize-barsize*pre)+"]"
#[task:status] 0% [progressbar] (now/all)
def tasktitle(task,status,now,all):
    pre=0.0
    if(all==0):
        pre=1
    else:
        pre=now/all
    tit=f"[{str(task)}:{str(status)}] {str(int(pre*100))}% {getprogbar(pre,10)} ({str(now)}/{str(all)})"
    title(tit)
#get terminal size
def term_width():
    try:
        return os.get_terminal_size()[0]
    except:
        return 0
#print progress bar
def progressbar(now,all):
    pre=0.0
    if(all==0):
        pre=1
    else:
        pre=now/all
    printf(f"{str(int(pre*100))}%({str(now)}/{str(all)})",end="\n[")
    barsize=term_width()-2
    cprint(colors["green"],"#"*int(barsize*pre)+" "*int(barsize-barsize*pre),end="")
    printf("]",end="\n")


#_main
def cppp_builder_base_main(*args, **kwargs):
    for i in range(1001):
        tasktitle("task","doing",i,1000)
        progressbar(i,1000)
        log.suc(i)
        #time.sleep(0.01)
if(__name__=="__main__"):
    cppp_builder_base_main()