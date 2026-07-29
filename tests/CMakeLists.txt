file(GLOB TEST_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(test_runner ${TEST_SOURCE})

target_link_libraries(test_runner PRIVATE DrawEngine)
target_link_libraries(test_runner PRIVATE Catch2::Catch2WithMain)

target_include_directories(test_runner PRIVATE ${CMAKE_SOURCE_DIR}/include)

