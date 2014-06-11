solution "ProjectUniverse"
   configurations { "Debug", "DebugProfile", "Release" }

   -- A project defines one build target
   project "ProjectUniverse"
      kind "ConsoleApp"
      language "C++"
      files { "../src/**.hpp", "../src/**.cpp", "../src/**.inl" }
      --links { "GL", "GLEW" }
      buildoptions { "-std=c++11" }
      includedirs { "../src/" }
      buildoptions {"`pkg-config --cflags cppunit lua sdl2 gl glew`" }
      linkoptions  {"`pkg-config --libs   cppunit lua sdl2 gl glew`" }
      flags { "ExtraWarnings" }

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
