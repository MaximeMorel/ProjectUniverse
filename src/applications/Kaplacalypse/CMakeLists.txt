project(Kaplacalypse)

message(STATUS "Configuring ${PROJECT_NAME}...")

set(CMAKE_CXX_STANDARD 11)
include_directories(../../)

set(APP_SOURCE Kaplacalypse.cpp)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}/app/${PROJECT_NAME})
add_library(${PROJECT_NAME} MODULE ${APP_SOURCE})
