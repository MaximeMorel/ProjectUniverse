solution "ProjectUniverse"
   configurations { "Debug", "DebugProfile", "Release" }
   language "C++"
   buildoptions { "-std=c++11" }
   includedirs { "../src/" }


   configuration "Debug"
      defines { "DEBUG" }
      flags { "Symbols" }

   configuration "DebugProfile"
      defines { "DEBUG" }
      flags { "Symbols" }
      buildoptions { "-g" }

   configuration "Release"
      defines { "NDEBUG" }
      flags { "Optimize" }

   project "RenderOpenGL4"
      kind "SharedLib"
      files { "../src/core/render/renderOpenGL4/**.hpp", "../src/core/render/renderOpenGL4/**.cpp" }

   project "RenderNull"
      kind "SharedLib"
      files { "../src/core/render/renderNull/**.hpp", "../src/core/render/renderNull/**.cpp" }

   -- A project defines one build target
   project "ProjectUniverse"
      kind "ConsoleApp"
      --language "C++"
      files { "../src/**.hpp", "../src/**.cpp", "../src/**.inl" }
      --links { "GL", "GLEW" }
      links { "RenderOpenGL4" }
      --buildoptions { "-std=c++11" }
      --includedirs { "../src/" }
      buildoptions {"`pkg-config --cflags cppunit lua sdl2 gl glew`" }
      linkoptions  {"`pkg-config --libs   cppunit lua sdl2 gl glew`" }
      flags { "ExtraWarnings" }
