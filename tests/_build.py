from subprocess import Popen
from sys import stdin,stdout,stderr
import os
import ctypes
import platform
import shutil
try:
    nullio=open(os.devnull,"w+")
except:
    nullio=open("devnull.tmp","w+")
def title(t):
    stdout.write("\033]0;%s3\007" % t)
if(platform.uname()[0]=="Windows"):
    try:
        cp=ctypes.windll.kernel32.GetConsoleCP()
        path=os.path.join(os.getenv("SystemRoot"),"System32","chcp.com")#%SystemRoot%\System32\chcp.com
        p=Popen([path,str(cp),">","NUL"],shell=True,stdout=stdout,stderr=nullio,cwd=os.getcwd())#重新加载codepage
        p.wait()
        def _title(t):
            ctypes.windll.kernel32.SetConsoleTitleW(t)
        title=_title
    except:
        pass

colors={}
colors["red"]=31
colors["green"]=32

def build(file,conf,plat,oth=""):
    cmd=f"msbuild \"{file}\" -p:Configuration=\"{conf}\" -p:Platform=\"{plat}\" -noLogo -m {oth}"
    print(cmd)
    return Popen(cmd,stdin=stdin,stdout=stdout,stderr=stderr,shell=True).wait()

sln="cppp-test-windows.sln"
confs=["cxx14-debug","cxx17-debug","cxx20-debug",
       "cxx14-release","cxx17-release","cxx20-release"]
plats=["x86","x64"]
build_all=len(confs)*len(plats)
build_pre=0
build_res={}
test_res={}
def printpre():
    print(build_pre,"/",build_all,end=' ')
    try:
        size=os.get_terminal_size()
        pre=build_pre/build_all
        print(int(pre*100),"%")
        barsize=(size[0]-2)
        print("["+"#"*int(barsize*pre)+" "*int(barsize-barsize*pre),end="]")

        tit="[building:test]"
        size=[14,0]
        pre=build_pre/build_all
        tit+=(str(int(pre*100))+"%")
        barsize=(size[0]-2)
        tit+=("["+"#"*int(barsize*pre)+" "*int(barsize-barsize*pre)+"]")
        title(tit)
    except:
        pass
    print(end="\n")
build_suc=0
def allbuild():
    global build_pre,build_res,build_suc
    title("[building:test]0%[            ]")
    for plat in plats:
        for conf in confs:
            try:
                size=os.get_terminal_size()
                print(f"{conf}-{plat}".center(size[0],"*"))
            except:
                pass
            res=build(os.path.abspath(sln),conf,plat,"")
            if(res==0):
                build_suc+=1
            build_res[f"{conf}-{plat}"]=res
            build_pre+=1
            printpre()
test_pre=0
test_all=0
def test():
    title("[testing]0%[            ]")
    global test_res,test_pre,test_all
    test_all=build_suc
    exename="cppp-windows-test-%s-%s.exe"
    outs=[]
    for plat in plats:
        for conf in confs:
            outs.append([plat,conf])
    for out in outs:
        try:
            size=os.get_terminal_size()
        except:
            size=[0,0]
        plat=out[0]
        conf=out[1]
        exe=exename % (plat.replace("x86","Win32"),conf)
        print(("testing: "+exe).center(size[0],"*"))
        res=Popen(f"bin{os.path.sep}"+exe,stdin=stdin,stdout=stdout,stderr=stderr,shell=True).wait()
        test_res[f"{conf}-{plat}"]=res
        test_pre+=1
        print("\n")

        tit="[building:test]"
        size=[14,0]
        pre=test_pre/test_all
        tit+=(str(int(pre*100))+"%")
        barsize=(size[0]-2)
        tit+=("["+"#"*int(barsize*pre)+" "*int(barsize-barsize*pre)+"]")
        title(tit)

def res_print():
    max1=10
    max2=10
    for conf in build_res:
        max1=max(max1,len(conf))
        if(build_res[conf]==0):
            msg="SUCCESS"
        else:
            msg="ERROR:"+str(build_res[conf])
        max2=max(max2,len(msg))
    max1+=2
    max2+=2
    fmt1=f"%-{max1}s"
    fmt2=f"%-{max2}s"
    print((fmt1 % "Configuration")+(fmt2 % "Build")+"Test")
    for conf in build_res:
        print(fmt1 % conf,end="")
        if(build_res[conf]==0):
            msg="SUCCESS"
            print('\x1b[%sm' % (';'.join([str(colors["green"]),"1"])),end="")
        else:
            msg="ERROR:"+str(build_res[conf])
            print('\x1b[%sm' % (';'.join([str(colors["red"]),"1"])),end="")
        print(fmt2 % msg,end="")
        print("\x1b[0m",end="")
        if(test_res[conf]==0):
            msg='\x1b[%sm%s\x1b[0m' % (';'.join([str(colors["green"]),"1"]), "SUCCESS")
        else:
            msg='\x1b[%sm%s\x1b[0m' % (';'.join([str(colors["red"]),"1"]), "ERROR:"+str(test_res[conf]))
        print(msg)

def check():
    try:
        size=os.get_terminal_size()
    except:
        size=[0,0]
    print("#"*(size[0]-1))
    print("#"*(size[0]-1))
    print("#"*(size[0]-1)+"\n")
    print("\nC++ Plus Test Program build complete:")
    res_print()
def clean():
    print("Cleaning..")
    try:
        print("rm -rf bin")
        shutil.rmtree("bin")
    except:
        pass
    try:
        print("rm -rf obj")
        shutil.rmtree("obj")
    except:
        pass
def main():
    clean()
    allbuild()
    test()
    print("\n\n")
    check()
if(__name__=="__main__"):
    try:
        main()
        nullio.close()
    except KeyboardInterrupt:
        exit(3)
