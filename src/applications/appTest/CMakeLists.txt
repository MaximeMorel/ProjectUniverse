message(STATUS "Building appTest...")

project(AppTest)

set(CMAKE_CXX_STANDARD 11)
include_directories(../../)

set(APP_SOURCE appTest.cpp)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}/app)
add_library(AppTest MODULE ${APP_SOURCE})

