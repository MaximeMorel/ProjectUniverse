message(STATUS "Building RenderNull plugin...")

project(RenderNull)

set(CMAKE_CXX_STANDARD 11)
include_directories(../../../)

set(PLUGIN_SOURCE bufferObject.cpp
                  fbo.cpp
                  rbo.cpp
                  shader.cpp
                  shaderProgram.cpp
                  texture.cpp
                  vao.cpp)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}/lib)
add_library(RenderNull MODULE ${PLUGIN_SOURCE})
