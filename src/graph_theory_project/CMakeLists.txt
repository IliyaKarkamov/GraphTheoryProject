project(graph_theory_project_executable)

add_executable(${PROJECT_NAME} src/main.cpp
        src/graph/adjacency_list.h)

#target_link_libraries(${PROJECT_NAME} graph)

if (GENERATE_INSTALL)
    install(TARGETS ${PROJECT_NAME}
            RUNTIME DESTINATION bin)
endif ()