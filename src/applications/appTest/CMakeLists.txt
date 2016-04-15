project(AppTest)

message(STATUS "Configuring ${PROJECT_NAME}...")

set(CMAKE_CXX_STANDARD 11)
include_directories(../../)

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
target_link_libraries(${PROJECT_NAME} cppunit)
