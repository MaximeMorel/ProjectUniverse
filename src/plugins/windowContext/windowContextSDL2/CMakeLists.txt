project(windowContextSDL2)

message(STATUS "Configuring ${PROJECT_NAME} plugin...")

set(CMAKE_CXX_STANDARD 11)
include_directories(../../../)

set(PLUGIN_SOURCE windowContextSDL2.cpp)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}/lib)
add_library(${PROJECT_NAME} MODULE ${PLUGIN_SOURCE})

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
find_package (SDL2)
if (SDL2_FOUND)
    include_directories(${SDL2_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})
endif (SDL2_FOUND)
