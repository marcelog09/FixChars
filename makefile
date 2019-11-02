# This file demonstrates how to compile the project.
#
# To compile project do:
#
# On Windows:
#	mingw32-make
#
# On Linux:
# 	make
#
# Windows version Requires MinGW: 
#	You can download at http://www.mingw.org/
# 	Don't forget add C:\MinGW\bin\ folder to the PATH environment variable.
#

GPP = g++
PREOJECT = Fixchars

# Determinate platform
ifdef OS
	PLATFORM = Windows
else
	ifeq ($(shell uname), Linux)
		PLATFORM = Linux
	endif
endif

ifeq ($(PLATFORM), Windows)
	OUTFILE = "Bin/fixchars.dll"
	FLAGS 	= -D FIXCHARS -D HAVE_STDINT_H -D __need_size_t -D _MSC_VER -m32 -fPIC -c -O3 -w -D WIN32 -D PROJECT_NAME=\"$(PREOJECT)\" -I ./SDK/amx/
	BUILD 	= $(GPP) -Wl,--enable-stdcall-fixup -m32 -O2 -fshort-wchar -shared -o $(OUTFILE) *.o fixchars.def
	CLEAN	= del /Q /F *~ *.o *.so
	MESSAGE	= @echo "Windows build done. Copy Bin/fixchars.dll to your plugins folder."
endif

ifeq ($(PLATFORM), Linux)
	OUTFILE = "Bin/fixchars.so"
	FLAGS 	= -fpermissive -m32 -fPIC -c -O3 -w -D LINUX -D PROJECT_NAME=\"$(PREOJECT)\" -I ./SDK/amx/
	BUILD 	= $(GPP) -m32 -O2 -fshort-wchar -shared -o $(OUTFILE) *.o
	CLEAN	= -rm -f *~ *.o *.so
	MESSAGE	= @echo "Linux build done. Copy Bin/fixchars.so to your plugins folder."
endif

all:
	@echo "Starting build process. Please wait."
	$(GPP) $(FLAGS) ./SDK/amx/*.c
	$(GPP) $(FLAGS) ./SDK/*.cpp
	$(GPP) $(FLAGS) *.cpp
	$(BUILD)
	$(CLEAN)
	$(MESSAGE)