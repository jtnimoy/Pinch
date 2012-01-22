#!/usr/bin/python
import string,sys

a = open(sys.argv[1],"rb")
a=a.read()
a=string.split(a,sys.argv[2])
a=string.join(a,sys.argv[3])
b=open(sys.argv[1],"wb")
b.write(a)
b.close()
