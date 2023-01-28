import matplotlib.pyplot as pyplot
from glob import glob
ls=[]
x=[]
y=[]
for i in glob("*.txt"):
    print(i)
    x=[]
    y=[]
    a=0
    f=open(i)
    ls.append(i)
    for j in f:
        j=int(j.strip())
        x.append(j)
        y.append(a)
        a+=1
    pyplot.plot(y,x)
    f.close()
pyplot.legend(ls)
pyplot.show()
