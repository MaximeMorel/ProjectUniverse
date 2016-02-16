message(STATUS "Configuring audio plugins...")

add_subdirectory(audioFmod)
add_subdirectory(audioNull)
add_subdirectory(audioOpenAL)
