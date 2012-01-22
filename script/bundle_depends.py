#!/usr/bin/python
#
# this will analyse a given binary and bundle all depends from /opt/local/lib  
#
import sys,os,string

queue = []

class OtoolResult(object):
	"""docstring"""

	fullPath = ""
	moduleName = ""
	path = ""
	updatable = ""
	
	def __init__(self,s,u):
		"""docstring"""
		self.extract(s)
		self.updatable = u
	def extract(self,s):
		"""docstring"""
		self.fullPath = string.split(s[1:],' ')[0]
		self.moduleName = string.split(self.fullPath,'/')[-1]
		self.path = string.join(string.split(self.fullPath,'/')[:-1],'/')

	def __str__(self):
		return "OtoolResult{\n\tfullpath=" + self.fullPath + "\n\tmoduleName=" + self.moduleName + "\n\tpath=" + self.path + "\n}\n"
	
	def getDestDir(self):
		return (string.join(string.split(sys.argv[1],"/")[:-1],"/"))

	
	def previousExists(self):
		"""determines whether or not we should copy the file into that dir"""
		lss = os.listdir(self.getDestDir())
		retval = 0
		for i in lss:
			if(i==self.moduleName):
				retval = 1
				break
		return retval

	def bundlePathMatch(self,p):
		if(self.path == p):
			if(not self.previousExists()):
				global queue
				os.system("cp " + self.path + "/" + self.moduleName + " " + self.getDestDir())
				#todo - call install_name_tool with -id flag to update the lib's ID.
				os.system("install_name_tool -id @executable_path/" + self.moduleName + " " + self.getDestDir() + "/" + self.moduleName)
				print "\tbundled " + self.moduleName
				queue += [self.getDestDir() + "/" + self.moduleName] #add this to the end of the list
			os.system("install_name_tool -change " +  self.fullPath + " " + "@executable_path/" + self.moduleName + " " + self.updatable)

# argument validation
if(len(sys.argv) < 2):
	print "\n\nexample: bundle_depends.py ../programme.app/Contents/MacOS/programme\n\n"


def bundle_depends(filename):
	p = os.popen("otool -L "+filename,'r')
	p = string.split(p.read(),'\n')
	
	p = p[1:-1] #format otool output by trimming 1 from left and right
	
	for i in p:
		otr = OtoolResult(i,filename)
		otr.bundlePathMatch(thisPath)
		

thisPath = "/opt/local/lib"
queue += [sys.argv[1]]

while(len(queue)>0):
	print("Updating " + queue[0])
	bundle_depends(queue[0]) #deal with the first one
	queue = queue[1:] #chop off the first one
