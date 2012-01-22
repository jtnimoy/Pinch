import os,string,sys

def framework(a):
    return '/System/Library/Frameworks/'+a+'.framework/'+a


#load the list of used classes
sourcelist = []
sl=os.listdir('./intern')
for i in sl:
    s = string.split(i,'.')
    if(s[1]=='cpp' or s[1]=='c'):
        sourcelist = sourcelist + [i]

for i in range(0,len(sourcelist)):
    sourcelist[i]="intern/"+sourcelist[i]

# look here for headers
cpppath=[
    '.',
    '/usr/local/include',
    '/opt/local/include',
    '/opt/local/include/libpng12',
    '/opt/local/include/freetype2/',
    '/usr/include/freetype2/',
    '/usr/include/freetype2/freetype',
    '/usr/include/w32api',
    '/usr/include',
    '/usr/include/libpng12',
    '/System/Library/Frameworks/ApplicationServices.framework/Headers',
    '/cygdrive/c/Program Files/fmodapi375win/api/inc',
    'extern/myron/source',
    'extern/myron/ezcam',
    '/cygdrive/c/opt/ode/include'
    ]

# look here for libs
libpath = [
    '/usr/local/lib',
    '/lib/w32api',
    '/usr/lib',
    '/usr/lib/w32api',
    '/opt/local/lib',
    'extern/myron/ezcam',
    ]

# DLLs
if(sys.platform=='darwin'):
    sourcelist += [
		   framework('OpenGL'),
		   framework('GLUT'),
		   framework('Foundation'),
		   framework('ApplicationServices'),
		   framework('Carbon'),
		   framework('CoreServices'),
		   framework('QuickTime'),
		   '/opt/local/lib/libfreetype.6.dylib',
		   '/usr/lib/libz.1.1.3.dylib',
                   '/opt/local/lib/libpng12.a',
                   '/usr/local/lib/libode.a',
		   ]
else:
    sourcelist += [
		   '/lib/libfreetype.dll.a',
		   '/lib/w32api/libopengl32.a',
		   '/lib/w32api/libglu32.a',
		   '/lib/w32api/libglut32.a',
		   '/lib/libpng12.a',
		   '/lib/libz.a',
		   '/cygdrive/c/opt/ode/lib/releasesingledll/ode_single.dll',
		   ]

# static link libs (preferrable, add to 
libs = []



# compiler args
ccflags=[
	 "-Wno-deprecated", #don't warn about deprecated
	 "-w", #no warnings
         "-DdSINGLE", #from ODE
	 ]

if(sys.platform=='darwin'):
    #OS-specific define until i find one already provided
    ccflags.append( "-D__DARWIN__ -arch i386")

#make new scons instance
env = Environment(CCFLAGS=ccflags,CPPPATH=cpppath,LIBS=libs,LIBPATH=libpath)

#configure checks
conf = Configure(env)

if(sys.platform=='darwin'):
    pass
else: #windows, so far
    if not conf.CheckCXXHeader('GL/gl.h'):
        print 'OpenGL must be installed'
        Exit(1)

if not conf.CheckCXXHeader('ode/ode.h'):
    print 'ODE must be installed'
    Exit(1)

    
if not conf.CheckCXXHeader('png.h'):
    print 'libpng12 must be installed'
    Exit(1)


env = conf.Finish()
    
#the app
env.Program(target='program',source=sourcelist)

#mac bundle post step
if(sys.platform=='darwin'):
    env.AddPostAction('program', Action('script/appIt $TARGET'))
    env.AddPostAction('program', Action('script/bundle_depends.py $TARGET\.app/Contents/MacOS/$TARGET'))
    env.Clean('program','program.app')
