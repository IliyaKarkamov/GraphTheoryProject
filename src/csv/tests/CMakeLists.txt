add_executable(csv_tests adjacency_list_test.cpp)
target_link_libraries(csv_tests csv Catch2)

add_test(csv_unit_tests csv_tests)