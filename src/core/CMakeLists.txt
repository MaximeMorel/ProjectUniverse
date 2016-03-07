message(STATUS "Configuring core...")

project(engine)

set(CMAKE_CXX_STANDARD 11)
include_directories(../)

set(CORE_SOURCE main.cpp
                application.cpp
                engine.cpp
                library.cpp
                geom/frustum.cpp
                geom/octree.cpp
                geom/boundingVolume/aabb.cpp
                geom/boundingVolume/boundingSphere.cpp
                geom/boundingVolume/obb.cpp
                geom/curve/curve.cpp
                geom/curve/curveLine.cpp
                geom/curve/curvePolyline.cpp
                geom/curve/curveBezier.cpp
                geom/surface/surface.cpp
                geom/surface/surfacePlane.cpp
                input/inputDevice.cpp
                input/inputManager.cpp
                log/logManager.cpp
                log/logger.cpp
                log/loggerFile.cpp
                log/loggerGroup.cpp
                log/loggerNull.cpp
                log/loggerStream.cpp
                math/mat3.cpp
                math/mat3.inl
                math/mat4.cpp
                math/mat4.inl
                math/vec2.cpp
                math/vec2.inl
                math/vec3.cpp
                math/vec3.inl
                math/vec4.cpp
                math/vec4.inl
                plugin/pluginManager.cpp
                plugin/plugin.cpp
                plugin/pluginApp.cpp
                plugin/pluginLib.cpp
                render/bufferObject.cpp
                render/fbo.cpp
                render/rbo.cpp
                render/shader.cpp
                render/shaderProgram.cpp
                render/texture.cpp
                render/vao.cpp
                resource/resource.cpp
                resource/resourceManager.cpp
                )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}/bin)
add_executable(engine ${CORE_SOURCE})
target_link_libraries(engine ${CMAKE_DL_LIBS})