project(executable)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} dynamic_library)

if (GENERATE_INSTALL)
    install(TARGETS ${PROJECT_NAME}
            RUNTIME DESTINATION bin)
endif ()