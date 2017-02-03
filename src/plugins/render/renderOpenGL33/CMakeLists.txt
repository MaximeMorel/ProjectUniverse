project(RenderOpenGL33)

message(STATUS "Configuring ${PROJECT_NAME} plugin...")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
include_directories(../../../)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(../renderOpenGL/)

set(PLUGIN_SOURCE ../renderOpenGL/renderOpenGL.cpp
                  renderOpenGL33.cpp
                  ../renderOpenGL/glObject.cpp
                  ../renderOpenGL/bufferObjectGL.cpp
                  bufferObjectGL33.cpp
                  ../renderOpenGL/fboGL.cpp
                  fboGL33.cpp
                  ../renderOpenGL/rboGL.cpp
                  rboGL33.cpp
                  ../renderOpenGL/shaderGL.cpp
                  shaderGL33.cpp
                  ../renderOpenGL/shaderProgramGL.cpp
                  shaderProgramGL33.cpp
                  ../renderOpenGL/textureGL.cpp
                  textureGL33.cpp
                  ../renderOpenGL/vaoGL.cpp
                  vaoGL33.cpp
                  ../renderOpenGL/renderMeshGL.cpp
                  renderMeshGL33.cpp
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

find_package (OpenGL)
if (OPENGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY})
endif (OPENGL_FOUND)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_BINARY_DIR}/src/core/${CMAKE_STATIC_LIBRARY_PREFIX}engine${CMAKE_STATIC_LIBRARY_SUFFIX})
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                       COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/$<CONFIG>/${CMAKE_SHARED_LIBRARY_PREFIX}${PROJECT_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX}" "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
endif (WIN32)
