Lua:

https://www.lua.org/download.html
https://www.lua.org/ftp/lua-5.3.4.tar.gz

Extract archive

Open VS2015 tools command prompt
cd lua-5.3.4/src

cl /MD /O2 /c /DLUA_BUILD_AS_DLL *.c
ren lua.obj lua.o
ren luac.obj luac.o
link /DLL /IMPLIB:lua5.3.4.lib /OUT:lua5.3.4.dll *.obj 
link /OUT:lua.exe lua.o lua5.4.0.lib 
lib /OUT:lua5.3.4-static.lib *.obj
link /OUT:luac.exe luac.o lua5.3.4-static.lib

JPEG:
http://www.ijg.org/
http://www.ijg.org/files/jpegsr9b.zip


Open VS2015 tools command prompt
cd jpeg-9b
nmake /f makefile.vc setup-v10
If win32.mak cannot be found, copy it from C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\Include
Open jpeg.sln with Visual Studio, convert the solution
Add x64 target if needed. Change configuration type to dll.
As stated in install.txt, edit jmorecfg.h to export symbols correctly:

#define GLOBAL(type)		__declspec(dllexport) type
#define EXTERN(type)		extern __declspec(dllexport) type

PNG:
https://sourceforge.net/projects/libpng/files/libpng16/1.6.28/
https://sourceforge.net/projects/libpng/files/zlib/1.2.8/

Build using lpng1628\projects\vstudio\vstudio.sln

TIFF:
Use NuGet package manager.

GLEW:
http://glew.sourceforge.net/
use include folder and lib folder.

Bullet:
Use visual studio solution provided to build.

Assimp:
Use NuGet package manager.

OpenAL:
http://kcat.strangesoft.net/openal.html#download


Generate VS solution with cmake:

Use gen-vc14-solution.bat
