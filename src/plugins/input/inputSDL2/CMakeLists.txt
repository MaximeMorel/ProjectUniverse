project(InputSDL2)

message(STATUS "Configuring ${PROJECT_NAME} plugin...")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
include_directories(../../../)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(PLUGIN_SOURCE inputSDL2.cpp
                  inputSDL2DeviceJoystick.cpp
                  inputSDL2DeviceKeyboard.cpp
                  inputSDL2DeviceMouse.cpp
                  inputSDL2DeviceTouchscreen.cpp)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}/lib)
add_library(${PROJECT_NAME} MODULE ${PLUGIN_SOURCE})

include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME})

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)
find_package (SDL2)
if (SDL2_FOUND)
    include_directories(${SDL2_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})
endif (SDL2_FOUND)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_BINARY_DIR}/src/core/${CMAKE_STATIC_LIBRARY_PREFIX}engine${CMAKE_STATIC_LIBRARY_SUFFIX})
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                       COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/$<CONFIG>/${CMAKE_SHARED_LIBRARY_PREFIX}${PROJECT_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX}" "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
endif (WIN32)
