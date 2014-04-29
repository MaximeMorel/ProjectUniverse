solution "ProjectUniverse"
   configurations { "Debug", "Release" }

   -- A project defines one build target
   project "ProjectUniverse"
      kind "ConsoleApp"
      language "C++"
      files { "../src/**.hpp", "../src/**.cpp" }
      links { "gtest" }
      buildoptions { "-std=c++11" }
      includedirs { "../src/" }
      buildoptions {"`pkg-config --cflags lua`" }
      linkoptions {"`pkg-config --libs lua`" }

      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols" }

      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }

