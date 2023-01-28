#!/bin/env python3
'''
 * @package cppp_test_builder
 * @file tools/cppp_test_builder.py
 * @copyright Copyright (C) 2023
 * @date 2023-1-27
 * @language Python
 * @brief C++ Plus Builder console base

C++ Plus Test Program builder
Build C++ Plus Test Program on GCC.

LICENCE MIT Licence
'''

from cppp_builder_base import *

targets=["cxx14-debug","cxx17-debug","cxx20-debug",
       "cxx14-release","cxx17-release","cxx20-release"]
platforms=["Win32","x64"]
msbuild_exe="msbuild.exe"

test_output_path=os.path.abspath(f"..{os.path.sep}tests{os.path.sep}bin")
msbuild_slnfile=os.path.abspath(f"..{os.path.sep}tests{os.path.sep}cppp-test-windows.sln")

build_return={}
test_return={}
build_suc=[]
test_suc=[]

def msbuild_build(slnfile,target,platform,others=[]):
    global build_return,build_suc
    build_cmd=[msbuild_exe,slnfile,f"-p:Configuration={str(target)}",f"-p:Platform={platform}",
               "-noLogo","-m",*others]
    log.info(build_cmd)
    ret=Popen(build_cmd,stdout=sys.stdout,stderr=sys.stderr,shell=True,cwd=os.getcwd(),env=os.environ).wait()
    build_return[f"{target}-{platform}"]=ret
    
    if(ret!=0):
        log.error(f"{target}-{platform} return:{str(ret)}")
    else:
        log.suc(f"build suc:{target}-{platform}")
        build_suc.append(f"{target}-{platform}")

def msbuild_build_all():
    now=0
    tasktitle("cppp-test","building",0,len(platforms)*len(targets))
    for platform in platforms:
        for target in targets:
            msbuild_build(msbuild_slnfile,target,platform)
            now+=1
            tasktitle("cppp-test","building",now,len(platforms)*len(targets))
            progressbar(now,len(platforms)*len(targets))


def windows_test():
    global test_return
    exename="cppp-windows-test-%s-%s.exe"
    now=0
    tasktitle("cppp-test","testing",0,len(platforms)*len(targets))
    for platform in platforms:
        for target in targets:
            test_exe=os.path.join(test_output_path,exename % (platform,target))
            log.info(test_exe)
            ret=Popen(test_exe,shell=True,stdout=sys.stdout,stderr=sys.stderr).wait()
            printf("\n")
            if(ret!=0):
                log.error(f"{target}-{platform} return:{str(ret)}")
            else:
                log.suc(f"test suc:{target}-{platform}")
                test_suc.append(f"{target}-{platform}")
            test_return[f"{target}-{platform}"]=ret
            now+=1
            tasktitle("cppp-test","testing",now,len(platforms)*len(targets))
            progressbar(now,len(platforms)*len(targets))

def test_build_summary():
    for i in range(3):
        printf("*"*term_width(),"\n")
    log.info(f"C++ Plus Test Program building done: {str(len(platforms)*len(targets))} target(s), {str(len(build_suc))} ok(s)")
    log.info(f"C++ Plus Test Program testing done: {str(len(platforms)*len(targets))} target(s), {str(len(test_suc))} ok(s)")
    MSGSUC="SUCCESS"
    wid1=max(map(len,build_return.keys()))
    b={}
    t={}
    for target in build_return:
        if(build_return[target]==0):
            b[target]=MSGSUC
        else:
            b[target]="ERROR:"+str(build_return[target])
    for target in test_return:
        if(test_return[target]==0):
            t[target]=MSGSUC
        else:
            t[target]="ERROR:"+str(test_return[target])
    wid2=max(map(len,b.keys()))
    fmt1=f"%-{str(wid1)}s "
    fmt2=f"%-{str(wid2)}s "
    printf(fmt1 % "Target")
    printf(fmt2 % "Build")
    printf("Test",end="\n")
    for target in build_return:
        printf(fmt1 % target)
        if(b[target]==MSGSUC):
            cprint(colors["green"],fmt2 % b[target],end="")
        else:
            cprint(colors["red"],fmt2 % b[target],end="")
        if(t[target]==MSGSUC):
            cprint(colors["green"],fmt2 % t[target])
        else:
            cprint(colors["red"],fmt2 % t[target])

def test_builder_main():
    log.info("C++ Plus Test Program building ...")
    msbuild_build_all()
    windows_test()
    test_build_summary()

if(__name__=="__main__"):
    test_builder_main()

