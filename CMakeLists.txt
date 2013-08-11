cmake_minimum_required(VERSION 2.8)

project(LiteJit C)

set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -I${CMAKE_CURRENT_SOURCE_DIR}/src -O0 -g -ggdb")

set(CMAKE_CXX_FLAGS_RELEASE "-Wall -Wextra -I${CMAKE_CURRENT_SOURCE_DIR}/src -O2 -s -DNDEBUG")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG}")

ADD_LIBRARY(litejit_lib
            )

SET_TARGET_PROPERTIES(
    litejit_lib
    PROPERTIES
    VERSION 0.0.1
    OUTPUT_NAME litejit
)

#######################
#######################
##    CLEAR RULE     ##
#######################
#######################

CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_clear.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake/cmake_clear.cmake"
  IMMEDIATE @ONLY)
ADD_CUSTOM_TARGET(distclean
  COMMAND ${CMAKE_BUILD_TOOL} clean
  COMMAND "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake/cmake_clear.cmake")
