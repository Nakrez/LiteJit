FIND_PROGRAM(BISON_EXECUTABLE NAMES bison bison.exe )

IF(BISON_EXECUTABLE)
     SET(BISON_FOUND TRUE)

     EXECUTE_PROCESS(COMMAND ${BISON_EXECUTABLE} --version
         OUTPUT_VARIABLE _BISON_VERSION
     )
     string (REGEX MATCH "[0-9]+\\.[0-9]+\\.[0-9]+" BISON_VERSION 
"${_BISON_VERSION}")
ENDIF(BISON_EXECUTABLE)

IF(BISON_FOUND)
   IF(NOT Bison_FIND_QUIETLY)
     MESSAGE(STATUS "Found Bison: ${BISON_EXECUTABLE}")
   ENDIF(NOT Bison_FIND_QUIETLY)
ELSE(BISON_FOUND)
   IF(Bison_FIND_REQUIRED)
     MESSAGE(FATAL_ERROR "Could not find Bison")
   ENDIF(Bison_FIND_REQUIRED)
ENDIF(BISON_FOUND)

FIND_PROGRAM(FLEX_EXECUTABLE NAMES flex flex.exe )

IF(FLEX_EXECUTABLE)
     SET(FLEX_FOUND TRUE)

     EXECUTE_PROCESS(COMMAND ${FLEX_EXECUTABLE} --version
         OUTPUT_VARIABLE _FLEX_VERSION
     )
     string (REGEX MATCH "[0-9]+\\.[0-9]+\\.[0-9]+" FLEX_VERSION
"${_FLEX_VERSION}")
ENDIF(FLEX_EXECUTABLE)

IF(FLEX_FOUND)
   IF(NOT Flex_FIND_QUIETLY)
     MESSAGE(STATUS "Found Flex: ${FLEX_EXECUTABLE}")
   ENDIF(NOT Flex_FIND_QUIETLY)
ELSE(FLEX_FOUND)
   IF(Flex_FIND_REQUIRED)
     MESSAGE(FATAL_ERROR "Could not find Flex")
   ENDIF(Flex_FIND_REQUIRED)
ENDIF(FLEX_FOUND)

SET(src_codegen_parser "${CMAKE_CURRENT_SOURCE_DIR}/codegen-parser.y")
SET(dst_codegen_parser "${CMAKE_CURRENT_SOURCE_DIR}/codegen-parser.c")

ADD_CUSTOM_COMMAND(
        OUTPUT "${dst_codegen_parser}"
        DEPENDS "${src_codegen_parser}"
        COMMAND
        ${BISON_EXECUTABLE} -o${dst_codegen_parser} ${src_codegen_parser}
        )

add_custom_target(codegen_parser DEPENDS "${dst_codegen_parser}")

##########################
#          FLEX          #
##########################

SET(src_codegen_lexer "${CMAKE_CURRENT_SOURCE_DIR}/codegen-lexer.l")
SET(dst_codegen_lexer "${CMAKE_CURRENT_SOURCE_DIR}/codegen-lexer.c")

ADD_CUSTOM_COMMAND(
        OUTPUT "${dst_codegen_lexer}"
        DEPENDS "${src_codegen_lexer}"
        COMMAND
        ${FLEX_EXECUTABLE} -o${dst_codegen_lexer} ${src_codegen_lexer}
        )

add_custom_target(codegen_lexer DEPENDS "${dst_codegen_lexer}")

add_executable(codegen
               codegen-lexer.c
               codegen-parser.c
               )

add_dependencies(codegen codegen_parser)
add_dependencies(codegen codegen_lexer)
