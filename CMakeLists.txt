cmake_minimum_required(VERSION 2.8)

project(LiteJit C)

set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -I${CMAKE_CURRENT_SOURCE_DIR}/src -O0 -g -ggdb -DLJIT_DEBUG")

set(CMAKE_CXX_FLAGS_RELEASE "-Wall -Wextra -I${CMAKE_CURRENT_SOURCE_DIR}/src -O2 -s -DNDEBUG")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG}")

ADD_LIBRARY(litejit_lib SHARED
            src/core/instance.c
            src/core/function.c
            src/core/bytecode.c
            src/core/bytecode-list.c
            )

SET_TARGET_PROPERTIES(
    litejit_lib
    PROPERTIES
    VERSION 0.0.1
    OUTPUT_NAME litejit
)

# Test rule (make test)

enable_testing()

add_subdirectory(test)

# Documentation rule (make doc)

find_package(Doxygen)
if(DOXYGEN_FOUND)
    add_custom_target(doc
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM
                     )
endif(DOXYGEN_FOUND)

# Clean working directory (make distclean)

CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_clear.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake/cmake_clear.cmake"
  IMMEDIATE @ONLY)
ADD_CUSTOM_TARGET(distclean
  COMMAND ${CMAKE_BUILD_TOOL} clean
  COMMAND "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake/cmake_clear.cmake")
