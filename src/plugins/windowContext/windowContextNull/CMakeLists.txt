message(STATUS "Configuring windowContextNull plugin...")

project(windowContextNull)

set(CMAKE_CXX_STANDARD 11)
include_directories(../../../)

set(PLUGIN_SOURCE windowContextNull.cpp)

add_library(windowContextNull MODULE ${PLUGIN_SOURCE})
