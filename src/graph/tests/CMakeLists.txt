add_executable(graph_tests
        adjacency_list_test.cpp
        csv_io_test.cpp
        algorithms_test.cpp)

target_link_libraries(graph_tests graph Catch2)

add_test(graph_tests_unit_tests graph_tests)