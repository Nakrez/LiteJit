add_definitions(-m32 -I../include -g -ggdb -O0)
## Instance test
add_executable(instance_test
               EXCLUDE_FROM_ALL
               instance.c)

target_link_libraries(instance_test litejit_lib)

ADD_TEST(ctest_build_instance "${CMAKE_COMMAND}" --build ${CMAKE_BINARY_DIR} --target instance_test)
ADD_TEST(ctest_run_instance instance_test)

## ljit_call_function test
add_executable(ljit_call_test
               EXCLUDE_FROM_ALL
               ljit-call-function.c)

target_link_libraries(ljit_call_test litejit_lib)

ADD_TEST(ctest_build_ljit_call "${CMAKE_COMMAND}" --build ${CMAKE_BINARY_DIR} --target ljit_call_test)
ADD_TEST(ctest_run_ljit_call ljit_call_test)

## Basic Function test
add_executable(basic_function_test
               EXCLUDE_FROM_ALL
               basic-function.c)

target_link_libraries(basic_function_test litejit_lib)

ADD_TEST(ctest_build_basic_function "${CMAKE_COMMAND}" --build ${CMAKE_BINARY_DIR} --target basic_function_test)
ADD_TEST(ctest_run_basic_function basic_function_test)

## JUMP/LABEL test

add_executable(jump_test
               EXCLUDE_FROM_ALL
               jump.c)

target_link_libraries(jump_test litejit_lib)

ADD_TEST(ctest_build_jump "${CMAKE_COMMAND}" --build ${CMAKE_BINARY_DIR} --target jump_test)
ADD_TEST(ctest_run_jump jump_test)

## elf test

add_executable(elf_test
               EXCLUDE_FROM_ALL
               elf.c)

target_link_libraries(elf_test litejit_lib)

ADD_TEST(ctest_build_elf "${CMAKE_COMMAND}" --build ${CMAKE_BINARY_DIR} --target elf_test)
ADD_TEST(ctest_run_elf elf_test)

## basic regalloc
add_executable(basic_regalloc_test
               EXCLUDE_FROM_ALL
               basic-regalloc.c)

target_link_libraries(basic_regalloc_test litejit_lib)

ADD_TEST(ctest_build_basic_regalloc "${CMAKE_COMMAND}" --build ${CMAKE_BINARY_DIR} --target basic_regalloc_test)
ADD_TEST(ctest_run_basic_regalloc basic_regalloc_test)
