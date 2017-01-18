message(STATUS "Configuring render plugins...")

add_subdirectory(renderNull)
add_subdirectory(renderOpenGL21)
add_subdirectory(renderOpenGL33)
add_subdirectory(renderOpenGL45)
add_subdirectory(renderVulkan)
