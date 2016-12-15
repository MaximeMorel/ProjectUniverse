project(ImageCodecJPEG)

message(STATUS "Configuring ${PROJECT_NAME} plugin...")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
include_directories(../../../)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(PLUGIN_SOURCE imageCodecJPEG.cpp)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}/lib)
add_library(${PROJECT_NAME} MODULE ${PLUGIN_SOURCE})

include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME})

find_package (JPEG)
if (JPEG_FOUND)
    include_directories(${JPEG_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${JPEG_LIBRARIES})
endif (JPEG_FOUND)
