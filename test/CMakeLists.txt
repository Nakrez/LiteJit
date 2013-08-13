## Instance test
add_executable(instance_test
               EXCLUDE_FROM_ALL
               instance.c)

target_link_libraries(instance_test litejit_lib)

ADD_TEST(ctest_build_instance "${CMAKE_COMMAND}" --build ${CMAKE_BINARY_DIR} --target instance_test)
ADD_TEST(ctest_run_instance instance_test)

## Basic Function test
add_executable(basic_function_test
               EXCLUDE_FROM_ALL
               basic-function.c)

target_link_libraries(basic_function_test litejit_lib)

ADD_TEST(ctest_build_basic_function "${CMAKE_COMMAND}" --build ${CMAKE_BINARY_DIR} --target basic_function_test)
ADD_TEST(ctest_run_basic_function basic_function_test)
