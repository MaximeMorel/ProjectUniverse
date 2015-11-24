message(STATUS "Building core...")

project(engine)

set(CMAKE_CXX_STANDARD 11)
include_directories(../)

set(CORE_SOURCE application.cpp
                engine.cpp
                geom/frustum.cpp
                geom/octree.cpp
                geom/plane.cpp
                geom/boundingVolume/aabb.cpp
                geom/boundingVolume/boundingSphere.cpp
                geom/boundingVolume/obb.cpp
                geom/curve/curveBezier.cpp
                geom/surface/surfacePlane.cpp
                input/inputDevice.cpp
                input/inputManager.cpp
                log/logger.cpp
                log/loggerFile.cpp
                log/loggerGroup.cpp
                log/loggerNull.cpp
                log/loggerStream.cpp
                log/logManager.cpp
                render/bufferObject.cpp
                render/fbo.cpp
                render/rbo.cpp
                render/shader.cpp
                render/shaderProgram.cpp
                render/texture.cpp
                render/vao.cpp
                resource/resource.cpp
                resource/resourceManager.cpp
                tools/plugin.cpp)

add_executable(engine ${CORE_SOURCE})
