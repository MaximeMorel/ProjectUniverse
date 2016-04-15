message(STATUS "Configuring render plugins...")

add_subdirectory(renderNull)
add_subdirectory(renderOpenGL4)
add_subdirectory(renderVulkan)
