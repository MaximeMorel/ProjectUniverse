message(STATUS "Configuring windowContext plugins...")

add_subdirectory(windowContextNull)
add_subdirectory(windowContextSDL2)
add_subdirectory(windowContextXlib)
