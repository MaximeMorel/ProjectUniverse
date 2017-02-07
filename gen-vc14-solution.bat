mkdir build-vs14
cd build-vs14

set CMAKE=C:\projects\progs\dev\CMake\bin\cmake.exe
set PREFIX=C:\projects\maxime\ProjectUniverse\

%CMAKE% -G "Visual Studio 14 2015 Win64" ^
 ^
-D LUA_INCLUDE_DIR=%PREFIX%\build-vs14\packages\lua.5.3.3\build\native\include ^
-D LUA_LIBRARY=%PREFIX%\build-vs14\packages\lua.5.3.3\build\native\lib\v140\x64\Release\lua.lib ^
 ^
-D ZLIB_INCLUDE_DIRS=%PREFIX%\build-vs14\packages\zlib.v140.windesktop.msvcstl.dyn.rt-dyn.1.2.8.8\build\native\include ^
-D ZLIB_LIBRARIES=%PREFIX%\build-vs14\packages\zlib.v140.windesktop.msvcstl.dyn.rt-dyn.1.2.8.8\lib\native\v140\windesktop\msvcstl\dyn\rt-dyn\x64\Release\zlib.lib ^
 ^
-D JPEG_INCLUDE_DIR=%PREFIX%\build-vs14\packages\libjpeg.9.2.0.1\build\native\include ^
-D JPEG_LIBRARIES=%PREFIX%\build-vs14\packages\libjpeg.9.2.0.1\build\native\lib\v140\x64\Release\dynamic\cdecl\jpeg.lib ^
 ^
-D PNG_PNG_INCLUDE_DIR=%PREFIX%\build-vs14\packages\libpng.1.6.28.1\build\native\include ^
-D PNG_LIBRARY=%PREFIX%\build-vs14\packages\libpng.1.6.28.1\build\native\lib\x64\v140\dynamic\Release\libpng16.lib ^
 ^
-D TIFF_INCLUDE_DIR=%PREFIX%\build-vs14\packages\libtiff.4.0.6.2\build\native\include ^
-D TIFF_LIBRARY=%PREFIX%\build-vs14\packages\libtiff.4.0.6.2\build\native\lib\Release\x64\v140\libtiff.lib ^
 ^
-D GLEW_INCLUDE_DIR=%PREFIX%\build-vs14\mypackages\glew-2.0.0\include ^
-D GLEW_LIBRARY=%PREFIX%\build-vs14\mypackages\glew-2.0.0\lib\Release\x64\glew32.lib ^
 ^
-D BULLET_INCLUDE_DIR=%PREFIX%\build-vs14\mypackages\bullet3-2.86\src ^
-D BULLET_DYNAMICS_LIBRARY=%PREFIX%\build-vs14\mypackages\bullet3-2.86\bin\BulletDynamics_vs2010_x64_release.lib ^
-D BULLET_COLLISION_LIBRARY=%PREFIX%\build-vs14\mypackages\bullet3-2.86\bin\BulletCollision_vs2010_x64_release.lib ^
-D BULLET_MATH_LIBRARY=%PREFIX%\build-vs14\mypackages\bullet3-2.86\bin\LinearMath_vs2010_x64_release.lib ^
-D BULLET_SOFTBODY_LIBRARY=%PREFIX%\build-vs14\mypackages\bullet3-2.86\bin\BulletSoftBody_vs2010_x64_release.lib ^
 ^
-D ASSIMP_INCLUDE_DIR=%PREFIX%\build-vs14\packages\Assimp.3.0.0\build\native\include ^
-D ASSIMP_LIBRARY=%PREFIX%\build-vs14\packages\Assimp.3.0.0\build\native\lib\x64\assimp.lib ^
 ^
-D OPENAL_INCLUDE_DIR=%PREFIX%\build-vs14\mypackages\openal-soft-1.17.2-bin\include ^
-D OPENAL_LIBRARY=%PREFIX%\build-vs14\mypackages\openal-soft-1.17.2-bin\libs\Win64\OpenAL32.lib ^
 ^
-D SDL2_INCLUDE_DIR=%PREFIX%\build-vs14\packages\sdl2.2.0.5\build\native\include ^
-D SDL2_LIBRARY=%PREFIX%\build-vs14\packages\sdl2.2.0.5\build\native\lib\x64\dynamic\SDL2.lib ^
 ^
-D SDL2_IMAGE_INCLUDE_DIR=%PREFIX%\build-vs14\packages\sdl2_image.v140.2.0.1\build\native\include ^
-D SDL2_IMAGE_LIBRARY=%PREFIX%\build-vs14\packages\sdl2_image.v140.2.0.1\build\native\lib\x64\Release\SDL2_image.lib ^
 ^
-D OGG_INCLUDE_DIR=%PREFIX%\build-vs14\mypackages\libogg\include ^
-D OGG_LIBRARY=%PREFIX%\build-vs14\mypackages\libogg\win32\VS2010\x64\Release\libogg.lib ^
-D VORBIS_INCLUDE_DIR=%PREFIX%\build-vs14\mypackages\libvorbis-1.3.5\include ^
-D VORBIS_LIBRARY=%PREFIX%\build-vs14\mypackages\libvorbis-1.3.5\win32\VS2010\x64\Release\libvorbis.lib ^
-D VORBISFILE_LIBRARY=%PREFIX%\build-vs14\mypackages\libvorbis-1.3.5\win32\VS2010\x64\Release\libvorbisfile.lib ^
-D VORBISENC_LIBRARY=%PREFIX%\build-vs14\mypackages ^
..

cd ..

:: -D ZLIB_INCLUDE_DIR=%PREFIX%\win\zlib-1.2.8 ^
:: -D ZLIB_LIBRARY=%PREFIX%\win\lpng1628\projects\vstudio\x64\Release\zlib.lib ^

