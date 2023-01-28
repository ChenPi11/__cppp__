from shutil import *
from platform import *
import os
import sys
import time
argv0=os.path.abspath(os.path.join(os.path.curdir,".."))##cd ..
os.chdir(argv0)
def seppath(p):
    if(uname()[0]=="Windows"):
        return p.replace("/","\\")
    return p.replace("\\","/")
def globh(p):
    res=[]
    it=os.scandir(p)
    for i in list(it):
        if(i.is_dir()):
            r=globh(i.path)
            res.extend(r)
        else:
            ext=os.path.splitext(i.path)[1]
            res.append(i.path)
    it.close()
    return list(res)

def getincs(fn,included=[]):
    incs={}
    f=open(fn,"r",encoding="utf-8")
    code=f.read()
    for line in code.split("\n"):
        if(line.replace(" ","").replace("\n","").replace("\t","").strip().startswith("#include\"")):
            l=line.strip()

            zs=l.find("//")
            if(zs==-1):
                zs=l.find("/*")
            if(zs==-1):
                incs[l]=l[l.find("#include")+len("#include"):].strip()
            else:
                incs[l]=l[l.find("#include")+len("#include"):zs].strip()
            incs[l]=eval(incs[l])
            incs[l]=os.path.abspath(os.path.join(fn,"..",seppath(incs[l])))
    f.close()
    for i in incs:
        if(incs[i] in included):
            continue
        included.append(incs[i])
        code=code.replace(i,getincs(incs[i],included)+"\n")
    return code
p=(getincs(os.path.join("include","cppp.hpp")))
f=open("LICENCE","r",encoding="utf-8")
lic=f.read()
f.close()
print("/*")
print("Licence:",lic.split("\n")[0])
print("Build time:",time.asctime())
print("Author:","ChenPi11")
print("Version:","1.0.0.0a")
print("\n\n")
print(lic)
print("*/\n\n\n")
print(p)
