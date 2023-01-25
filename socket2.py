config={}
class strings:
    pass
LANGPACK="zh-cn.lang"
CONFFILE="DownloadAgent.cfg"
LOGFILE="DownloadAgent.log"
import sys,json
def getopt(k,_=None):
    return k.get(k,_)
def config_load():
    global config
    try:
        with open(CONFFILE,"r",encoding="utf-8") as f:
            config=dict(json.load(f))
    except:
        print("Load config file error",CONFFILE,file=sys.stderr)
    try:
        with open(config.get("langpack",LANGPACK),"r",encoding="utf-8") as f:
            for i in f:
                i=i.strip()
                if(i.startswith("#") or i==""):
                    continue
                try:
                    k,v=i.split("=")
                    k=k.strip()
                    v=v.strip()
                    exec("strings.%s=%s"%(k,v))
                except Exception as e:
                    print("Load lang file error",e.__class__.__name__,e,file=sys.stderr)
    except Exception as e:
        print("Load lang file error",e.__class__.__name__,e,file=sys.stderr)
nullfun = lambda *args: None
config_load()
#----------------------------------------------缩减版filetp.log----------------------------------------
from os import devnull
import traceback,time
start_time=time.time()
def print_list(extracted_list):
    res=""
    for item in traceback.StackSummary.from_list(extracted_list).format():
        res+=item
    return res
def getexc():
    if(sys.exc_info()[0]==None):
        return ""
    res="Traceback(catch):\n"
    res+=print_list(traceback.extract_tb(sys.exc_info()[2]))
    res+=sys.exc_info()[0].__name__+": "+str(sys.exc_info()[1])
    return res
def gettime():
    return int((time.time()-start_time)*1000000)
default_file=sys.stdout
loggers={}
class Logger:
    name=""
    file=None
    _flush=False
    format:str=""
    def __init__(self,name,file,format,flush):
        global loggers
        self.name=str(name).upper()
        self.file=file
        self._flush=flush
        self.format=format
        if(name.upper() in loggers.keys()):
            raise TypeError("Logger "+name+" already exists,use getLogger()")
        loggers[name.upper()]=self
    def __str__(self):
        return self.name
    def write(self,msg):
        try:
            self.file.write(msg)
            if(self._flush):
                self.flush()
        except:
            pass
    def flush(self):
        try:
            self.file.flush()
        except:
            pass
    def log(self,level,msg):
        try:
            print(self.format.format(lvl=level,name=self.name,time=gettime(),msg=msg),end="\n",flush=self._flush,file=self.file)
        except:
            self.write("Error:"+getexc()+"\t,"+str(gettime())+","+level+","+msg+"\n")
    def info(self,msg):
        self.log("INFO",str(msg))
    def warn(self,msg):
        self.log("WARN",str(msg))
    def error(self,msg):
        self.log("ERROR",str(msg))
    def debug(self,msg):
        self.log("DEBUG",str(msg))
    def exception(self,msg):
        self.log("EXCEPTION",str(msg))
    def fatal(self,msg):
        self.log("FATAL",str(msg))
    def printerror(self):
        e=str(getexc())
        if(e):
            self.error(e)
    def close(self):
        try:
            self.file.close()
            self.file=None
        except:
            pass
Log=Logger("SYSTEM",default_file,flush=True,format="[{lvl} {name} {time}] {msg}")
def getLogger(name="SYSTEM",file=default_file,format="[{lvl} {name} {time}] {msg}",flush=False):
    global loggers
    if(name.upper() in loggers.keys()):
        l=loggers[name.upper()]
        l.file=file
        l.format=format
        l._flush=flush
        return l
    else:
        l=Logger(name,file=file,flush=flush,format=format)
        return l
#--------------------------------------------------缩减版socket2外加修复bug-----------------------------
import pickle
from threading import *
import socket,ctypes
class SocketError(socket.error):
    pass
class SocketClosedError(SocketError):
    pass

#这里有更好的算法,详见https://github.com/ChenPi11/FileTPConsole/blob/master/filetp/socket2.py
#但是考虑速度问题，使用了这种
def siz8(d):
    return bytes(ctypes.c_ulonglong(d))
def dsiz(d):
    return ctypes.c_ulonglong.from_buffer(ctypes.c_buffer(d)).value

def list2str(lst,char):
    res=""
    for i in lst:
        res+=i+char
    res=res[0:len(res)-1]
    return res
def skrecv(sk,siz):
    dt=bytes()
    _=0
    while(siz-len(dt)):
        _dt=sk.recv(siz-len(dt))
        if(len(_dt)<1):
            _+=1
            if(_>1024):
                raise SocketClosedError("Socket closed")
        dt+=_dt
    return dt
def sksend(sk,dt):
    l=sk.send(dt)
    while(l<len(dt)):
        l+=sk.send(dt[l:])
class _Socket2Commands:
    no=b"\x00"
    ok=b"\x01"
    err=b"\x02"
class socket2:
    sk=None
    addr=None
    log=None
    encoding="utf-8"
    def __str__(self):
        return "<socket2 object "+str(self.sk)+" >"
    def __init__(self,log=getLogger("SOCKET2"),c=None,addr=("",0)):
        self.encoding="utf-8"
        self.log=log
        if(c):
            self.sk=c
        else:
            self.sk=socket.socket()
        self.addr=addr
    def listen(self,backlog=10):
        self.sk.listen(backlog)
    def bind(self,ip,port,lbl=10):
        self.sk.bind((ip,port))
        self.addr=(ip,port)
        self.listen(lbl)
        self.log.info("Binded:"+str(self.addr))
    def connect(self,ip,port):
        self.sk.connect((ip,port))
        self.addr=(ip,port)
        sksend(self.sk,_Socket2Commands.ok)
        sputf=skrecv(self.sk,len(_Socket2Commands.ok))==_Socket2Commands.ok
        if(sputf):
            self.encoding="utf-8"
        else:
            self.encoding="GBK"
        if(skrecv(self.sk,len(_Socket2Commands.ok))!=_Socket2Commands.ok):
            self.log.info("Connection Refused.")
            try:
                t=self.sk.gettimeout()
                self.sk.settimeout(5)
                msg=self.recv()
                self.sk.settimeout(t)
                self.close()
            except:
                msg=""
            raise ConnectionRefusedError(msg)
        self.log.info("Connected:"+str(self.addr)+",fd="+str(self.sk.fileno()))
    def accept(self,refuse=False,refuse_msg=""):
        sk,addr=self.sk.accept()
        r=socket2(log=self.log,c=sk,addr=addr)
        sputf=skrecv(sk,len(_Socket2Commands.ok))==_Socket2Commands.ok
        if(sputf):
            r.encoding="utf-8"
        else:
            r.encoding="GBK"
        sksend(sk,_Socket2Commands.ok)
        if(refuse):
            sksend(sk,_Socket2Commands.no)
            r.send(str(refuse_msg))
            r.close()
            return None,("",0)
        else:
            sksend(sk,_Socket2Commands.ok)
        self.log.info("Accepted:"+str(addr)+",fd="+str(sk.fileno()))
        return r,addr
    def send(self,data):
        try:
            data=pickle.dumps(data)
            ph=siz8(len(data))
            sksend(self.sk,ph)
            sksend(self.sk,data)
        except(ConnectionRefusedError,SocketClosedError):
            self.close()
            raise
    def recv(self):
        try:
            _=skrecv(self.sk,8)
            ph=dsiz(_)
            dt=skrecv(self.sk,ph)
            dt=pickle.loads(dt)
            return dt
        except(ConnectionRefusedError,SocketClosedError):
            self.close()
            raise
    def close(self):
        try:
            self.sk.shutdown(socket.SHUT_RDWR)
        except:
            pass
        self.sk.close()



#-------------------------------------------------------------main-------
import os
#s=socket2()
#s.bind("",1919)
def sendfile(s,path):
    path=os.path.relpath(path)
    path.replace("\\","/")
    f=open(path,"rb")
    d=f.read()
    f.close()
    s.send(path)
    s.send(d)
def _glob(p):
    res=[]
    dres=[]
    it=os.scandir(p)
    for i in list(it):
        if(i.is_dir()):
            if(i.name.startswith(".") or "bin" in i.name):
               continue
            print("D",i.path)
            dres.append(i.path)
            r,d=_glob(i.path)
            res.extend(r)
            dres.extend(d)
        else:
            print("A",i.path)
            res.append(i.path)
    it.close()
    return list(res),list(dres)

try:
    c=socket2()
    c.connect("archlinux",1919)
    fs,ds=_glob(".")
    c.send(ds)
    for i in fs:
        sendfile(c,i)
        print("S",i)
    c.send("*end*")
    
    c.close()
    print("C",c)
except:
    print(getexc())
