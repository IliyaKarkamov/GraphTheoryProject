cmake_minimum_required(VERSION 3.14)
project(graph_theory_project)

set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
else ()
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif ()


set(DEPS_DIR "${PROJECT_SOURCE_DIR}/deps")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

option(BUILD_TESTS "Build the test programs" ON)
option(GENERATE_INSTALL "Generate installation target" ON)

if (BUILD_SHARED_LIBRARIES)
    set(LIBRARY_TYPE "SHARED")
else ()
    set(LIBRARY_TYPE "STATIC")
endif ()

if (BUILD_TESTS)
    enable_testing()
endif ()

add_subdirectory(deps)
add_subdirectory(src)
