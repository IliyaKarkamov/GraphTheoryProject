project(tinyxml2)

add_library(${PROJECT_NAME} ${LIBRARY_TYPE} src/tinyxml2.cpp)

add_compile_definitions(TINYXML2_EXPORT)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)