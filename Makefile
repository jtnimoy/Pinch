all:
	scons

clean:
	scons -c;\
	figlet CLEAN ; rm -r doc

run:
	make	run_`uname`


debug:
	make	debug_`uname`


doc:
	echo /\*\* \@mainpage jttoolkit template > intern/main.dox ; \
	cat README >> intern/main.dox ; \
	echo \*/ >> intern/main.dox ; \
	doxygen Doxyfile ; \
	open doc/html/index.html ; \
	cp script/doxyimages/* doc/html

run_Darwin:
	./program

run_CYGWIN_NT-5.1:
	./program.exe

debug_CYGWIN_NT-5.1:
	gdb ./program.exe

