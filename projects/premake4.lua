solution "ProjectUniverse"
   configurations { "Debug", "Release" }

   -- A project defines one build target
   project "ProjectUniverse"
      kind "ConsoleApp"
      language "C++"
      files { "../src/**.hpp", "../src/**.cpp", "../src/**.inl" }
      links { "gtest", "cppunit", "GL", "GLEW" }
      buildoptions { "-std=c++11 -Wall" }
      includedirs { "../src/" }
      buildoptions {"`pkg-config --cflags lua sdl2`" }
      linkoptions {"`pkg-config --libs lua sdl2`" }

      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols" }

      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }
