# Instance component test

add_definitions(-Wall -Wextra)

add_executable(instance_test
               EXCLUDE_FROM_ALL
               instance.c)

target_link_libraries(instance_test litejit_lib)

ADD_TEST(ctest_build_instance "${CMAKE_COMMAND}" --build ${CMAKE_BINARY_DIR} --target instance_test)
ADD_TEST(ctest_run_instance instance_test)
