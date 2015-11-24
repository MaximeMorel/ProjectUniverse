message(STATUS "Building renderNull plugin...")

project(renderNull)

set(CMAKE_CXX_STANDARD 11)
include_directories(../../../)

set(PLUGIN_SOURCE bufferObject.cpp
                  fbo.cpp
                  rbo.cpp
                  shader.cpp
                  shaderProgram.cpp
                  texture.cpp
                  vao.cpp)

add_library(renderNull MODULE ${PLUGIN_SOURCE})
