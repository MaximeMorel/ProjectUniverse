project(mduelX)

message(STATUS "Configuring ${PROJECT_NAME}...")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
include_directories(../../)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(APP_SOURCE mduelX.cpp)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}/app/${PROJECT_NAME})
add_library(${PROJECT_NAME} MODULE ${APP_SOURCE})

include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME})
