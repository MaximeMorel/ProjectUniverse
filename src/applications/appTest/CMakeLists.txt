project(AppTest)

message(STATUS "Configuring ${PROJECT_NAME}...")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
include_directories(../../)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(APP_SOURCE appTest.cpp
               tests/testRunner.cpp
               tests/protector.cpp
               tests/tests.cpp
               tests/testBasic.cpp
               tests/math/testMath.cpp
               tests/math/testVec.cpp
               tests/math/testMat.cpp
               tests/geom/testGeom.cpp
               tests/geom/testAABB.cpp
               tests/geom/testOBB.cpp
               tests/geom/testBoundingSphere.cpp
               tests/geom/testCurve.cpp
               tests/geom/testPlane.cpp
               tests/geom/testFrustum.cpp
               tests/engine/testResourceManager.cpp
               )

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}/app/${PROJECT_NAME})
add_library(${PROJECT_NAME} MODULE ${APP_SOURCE})

include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME})

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)
find_package (CppUnit)
if (CPPUNIT_FOUND)
    include_directories(${CPPUNIT_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${CPPUNIT_LIBRARY})
endif (CPPUNIT_FOUND)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_BINARY_DIR}/src/core/${CMAKE_STATIC_LIBRARY_PREFIX}engine${CMAKE_STATIC_LIBRARY_SUFFIX})
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                       COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/$<CONFIG>/${CMAKE_SHARED_LIBRARY_PREFIX}${PROJECT_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX}" "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
endif (WIN32)
