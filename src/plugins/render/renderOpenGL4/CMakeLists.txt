message(STATUS "Configuring renderOpenGL4 plugin...")

project(renderOpenGL4)

set(CMAKE_CXX_STANDARD 11)
include_directories(../../../)

#set(PLUGIN_SOURCE)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}/lib)
#add_library(renderOpenGL4 MODULE ${PLUGIN_SOURCE})
