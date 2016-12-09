project(engine)

message(STATUS "Configuring ${PROJECT_NAME}...")

set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_VISIBILITY_PRESET hidden)
#set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
include_directories(../)

set(CORE_SOURCE main.cpp
                application.cpp
                engine.cpp
                library.cpp
                config/config.cpp
                console/console.cpp
                console/consolecommands.cpp
                coretypes/buffer.cpp
                coretypes/image.cpp
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
                input/inputDeviceKeyboard.cpp
                input/inputDeviceMouse.cpp
                input/inputDeviceJoystick.cpp
                input/inputDeviceTouchscreen.cpp
                input/inputManager.cpp
                input/inputPlugin.cpp
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
                plugin/iplugin.cpp
                plugin/plugin.cpp
                render/bufferObject.cpp
                render/fbo.cpp
                render/rbo.cpp
                render/shader.cpp
                render/shaderProgram.cpp
                render/texture.cpp
                render/vao.cpp
                render/renderManager.cpp
                render/renderPlugin.cpp
                resource/resource.cpp
                resource/resourceFile.cpp
                resource/resourceManager.cpp
                tools/timer.cpp
                )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}/bin)
add_executable(${PROJECT_NAME} ${CORE_SOURCE})
target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS})

find_package (Bullet)
if (BULLET_FOUND)
    include_directories(${BULLET_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${BULLET_LIBRARIES})
endif (BULLET_FOUND)
