#!/bin/env python3
'''
 * @package cppp_test_builder
 * @file tools/cppp_test_builder.py
 * @copyright Copyright (C) 2023
 * @date 2023-1-28
 * @language Python
 * @brief C++ Plus Builder console base

C++ Plus Test Program builder
Build C++ Plus Test Program on GCC.

LICENCE MIT Licence
'''

from cppp_builder_base import *
gcc_exe="g++"
cppp_include=os.path.abspath(f"..{os.path.sep}cppp{os.path.sep}include")
cppp_test_src=os.path.abspath(f"..{os.path.sep}tests{os.path.sep}src{os.path.sep}main.cpp")

targets=["cxx11","cxx14","cxx17","cxx20","cxx98"]
test_out=os.path.abspath(f"..{os.path.sep}tests{os.path.sep}bin{os.path.sep}cppp-{platform.uname()[0].lower()}-test-%s.out")

build_return={}
test_return={}
build_suc=[]
test_suc=[]

def gcc_build(src,target,out,include,others=""):
    std=target.replace("cxx","c++")
    build_cmd=f"\"{gcc_exe}\" \"{src}\" -std={std} -o \"{out}\" -I\"{include}\" {others}"
    log.info(build_cmd)
    outdir=os.path.abspath(os.path.join(out,".."))
    if(not os.path.exists(outdir)):
        mkdir(outdir)
    ret=Popen(build_cmd,stdout=sys.stdout,stderr=sys.stderr,shell=True,cwd=os.getcwd(),env=os.environ).wait()
    build_return[f"gcc-{target}"]=ret
    if(ret!=0):
        log.error(f"gcc-{target} return:{str(ret)}")
    else:
        log.suc(f"build suc:gcc-{target}")
        build_suc.append(f"gcc-{target}")

def gcc_build_all():
    now=0
    tasktitle("cppp-test","building",0,len(targets))
    for target in targets:
        gcc_build(cppp_test_src,target,test_out % target,cppp_include)
        now+=1
        tasktitle("cppp-test","building",now,len(targets))
        progressbar(now,len(targets))

def gcc_build_test():
    global test_return
    now=0
    tasktitle("cppp-test","testing",0,len(targets))
    for target in targets:
        ret=Popen(test_out % target,shell=True).wait()
        printf("\n")
        test_return[f"gcc-{target}"]=ret
        if(ret!=0):
            log.error(f"gcc-{target} return:{str(ret)}")
        else:
            log.suc(f"test suc:gcc-{target}")
            test_suc.append(f"gcc-{target}")
        now+=1
        tasktitle("cppp-test","testing",now,len(targets))
        progressbar(now,len(targets))

def test_build_summary():
    for i in range(3):
        printf("*"*term_width(),"\n")
    log.info(f"C++ Plus Test Program building done: {str(len(targets))} target(s), {str(len(build_suc))} ok(s)")
    log.info(f"C++ Plus Test Program testing done: {str(len(targets))} target(s), {str(len(test_suc))} ok(s)")
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
    gcc_build_all()
    gcc_build_test()
    test_build_summary()

if(__name__=="__main__"):
    test_builder_main()