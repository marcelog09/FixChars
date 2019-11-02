# ---------------------------------------------------------------------------------------
#
# This file demonstrates how to compile the project.
#
# To compile project do:
#
# 	On Windows:
#		mingw32-make
#
# 	On Linux:
# 		make
#
# Windows version requires MinGW: 
#	You can download at http://www.mingw.org/
# 	Don't forget add C:\MinGW\bin\ folder to the PATH environment variable.
#
#
#		Created by ScriptHunter
#
# ---------------------------------------------------------------------------------------

PROJECT_NAME = Fixchars
DEF_FILE = fixchars.def
SDK_FOLDER = ./SDK
WINDOWS_OUTFILE = Bin/fixchars.dll
LINUX_OUTFILE = Bin/fixchars.so
GPP = g++

# Determinate platform
ifdef OS
	PLATFORM = Windows
else
	ifeq ($(shell uname), Linux)
		PLATFORM = Linux
	endif
endif

ifeq ($(PLATFORM), Windows)
	INITIAL_MESSAGE = @echo * Starting build process, please wait...
	COMPILE_FLAGS = -D HAVE_STDINT_H -D __need_size_t -D _MSC_VER -m32 -fPIC -c -O3 -w -D WIN32 -D PROJECT_NAME=\"$(PROJECT_NAME)\" -I $(SDK_FOLDER)/amx/
	LINKING = $(GPP) -Wl,--enable-stdcall-fixup -m32 -O2 -fshort-wchar -shared -o "$(WINDOWS_OUTFILE)" *.o $(DEF_FILE)
	REMOVE_TRASH = del /Q /F *~ *.o *.so
	LAST_MESSAGE = @echo * Windows build done. Please copy $(WINDOWS_OUTFILE) to your plugins folder.
endif

ifeq ($(PLATFORM), Linux)
	INITIAL_MESSAGE = @echo "* Starting build process, please wait..." 
	COMPILE_FLAGS = -fpermissive -m32 -fPIC -c -O3 -w -D LINUX -D PROJECT_NAME=\"$(PROJECT_NAME)\" -I $(SDK_FOLDER)/amx/
	LINKING = $(GPP) -m32 -O2 -fshort-wchar -shared -o "$(LINUX_OUTFILE)" *.o
	REMOVE_TRASH = -rm -f *~ *.o *.so
	LAST_MESSAGE = @echo "* Linux build done. Please copy $(LINUX_OUTFILE) to your plugins folder."
endif

all:
	$(INITIAL_MESSAGE)
	$(GPP) $(COMPILE_FLAGS) ./SDK/amx/*.c
	$(GPP) $(COMPILE_FLAGS) ./SDK/*.cpp
	$(GPP) $(COMPILE_FLAGS) *.cpp
	$(LINKING)
	$(REMOVE_TRASH)
	$(LAST_MESSAGE)