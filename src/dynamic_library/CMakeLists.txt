project(dynamic_library)

include(GenerateExportHeader)

add_library(${PROJECT_NAME} ${LIBRARY_TYPE}
        src/math_function.cpp)

generate_export_header(${PROJECT_NAME} BASE_NAME ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include ${PROJECT_BINARY_DIR})

if (GENERATE_INSTALL)
    install(TARGETS ${PROJECT_NAME}
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib
            RUNTIME DESTINATION bin)

    install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME} DESTINATION include)
    install(FILES ${PROJECT_BINARY_DIR}/${PROJECT_NAME}_export.h DESTINATION include/${PROJECT_NAME})
endif ()

if (BUILD_TESTS)
    add_subdirectory(tests)
endif ()
