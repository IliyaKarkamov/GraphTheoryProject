project(graph)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE include/)

if (GENERATE_INSTALL)
    install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME} DESTINATION include)
endif ()

if (BUILD_TESTS)
    add_subdirectory(tests)
endif ()