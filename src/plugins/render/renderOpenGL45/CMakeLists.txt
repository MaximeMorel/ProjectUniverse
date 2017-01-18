project(RenderOpenGL45)

message(STATUS "Configuring ${PROJECT_NAME} plugin...")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
include_directories(../../../)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(../renderOpenGL/)

set(PLUGIN_SOURCE ../renderOpenGL/renderOpenGL.cpp
                  renderOpenGL45.cpp
                  ../renderOpenGL/glObject.cpp
                  ../renderOpenGL/bufferObjectGL.cpp
                  bufferObjectGL45.cpp
                  ../renderOpenGL/fboGL.cpp
                  fboGL45.cpp
                  ../renderOpenGL/rboGL.cpp
                  rboGL45.cpp
                  ../renderOpenGL/shaderGL.cpp
                  shaderGL45.cpp
                  ../renderOpenGL/shaderProgramGL.cpp
                  shaderProgramGL45.cpp
                  ../renderOpenGL/textureGL.cpp
                  textureGL45.cpp
                  ../renderOpenGL/vaoGL.cpp
                  vaoGL45.cpp
                  ../renderOpenGL/renderMeshGL.cpp
                  renderMeshGL45.cpp
                  ../renderOpenGL/opengltools.cpp)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}/lib)
add_library(${PROJECT_NAME} MODULE ${PLUGIN_SOURCE})

include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME})

find_package (GLEW)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES})
endif (GLEW_FOUND)
