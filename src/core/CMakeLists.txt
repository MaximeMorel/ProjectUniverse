project(engine)

message(STATUS "Configuring ${PROJECT_NAME}...")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
include_directories(../)

set(CORE_SOURCE main.cpp
                application.cpp
                engine.cpp
                library.cpp
                audio/audioBuffer.cpp
                codecs/codecManager.cpp
                codecs/audioCodec.cpp
                codecs/imageCodec.cpp
                codecs/meshCodec.cpp
                config/config.cpp
                console/console.cpp
                console/consolecommands.cpp
                coretypes/buffer.cpp
                coretypes/image.cpp
                entity/entity.cpp
                geom/frustum.cpp
                geom/octree.cpp
                geom/boundingVolume/aabb.cpp
                geom/boundingVolume/boundingSphere.cpp
                geom/boundingVolume/obb.cpp
                geom/curve/curve.cpp
                geom/curve/curveLine.cpp
                geom/curve/curvePolyline.cpp
                geom/curve/curveBezier.cpp
                geom/mesh/mesh.cpp
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
                math/quaternion.cpp
                math/quaternion.inl
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
                render/renderMesh.cpp
                render/renderManager.cpp
                render/renderPlugin.cpp
                resource/resource.cpp
                resource/resourceFile.cpp
                resource/resourceManager.cpp
                resource/resourceManager.inl
                scene/scene.cpp
                script/lua/engineLua.cpp
                thread/threadManager.cpp
                tools/filetools.cpp
                tools/timer.cpp
                windowContext/windowManager.cpp
                windowContext/windowPlugin.cpp
                )

if (MSVC)
    set(ENGINE_OPTS WIN32)
endif (MSVC)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/out/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}/bin)
add_executable(${PROJECT_NAME} ${ENGINE_OPTS} ${CORE_SOURCE})
target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS})
set_property(TARGET ${PROJECT_NAME} PROPERTY ENABLE_EXPORTS on)
target_compile_definitions(${PROJECT_NAME} PRIVATE engine_EXPORTS)

find_package (Lua)
if (LUA_FOUND)
    include_directories(${LUA_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${LUA_LIBRARIES})
endif (LUA_FOUND)

find_package (Threads)
if (Threads_FOUND)
    target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
endif (Threads_FOUND)

if (WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                       COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIG>/${PROJECT_NAME}${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                       COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${CMAKE_BINARY_DIR}/src/core/$<CONFIG>/${CMAKE_STATIC_LIBRARY_PREFIX}engine${CMAKE_STATIC_LIBRARY_SUFFIX}" "${CMAKE_BINARY_DIR}/src/core/")
endif (WIN32)
