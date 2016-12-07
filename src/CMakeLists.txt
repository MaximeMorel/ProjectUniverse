message(STATUS "Configuring...")

add_subdirectory(core)
add_subdirectory(plugins)
add_subdirectory(applications)

file(COPY run.sh DESTINATION "${CMAKE_BINARY_DIR}/out/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}")
file(COPY README.txt DESTINATION "${CMAKE_BINARY_DIR}/out/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}")
