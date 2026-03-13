option(USE_SMC "Use SMC implementation" OFF)
option(USE_LEX "Use Lex implementation" OFF)
option(USE_REGEX "Use Regex implementation" OFF)


set(IMPL_COUNT 0)
if(USE_SMC)
    math(EXPR IMPL_COUNT "${IMPL_COUNT}+1")
endif()
if(USE_LEX)
    math(EXPR IMPL_COUNT "${IMPL_COUNT}+1")
endif()
if(USE_REGEX)
    math(EXPR IMPL_COUNT "${IMPL_COUNT}+1")
endif()

if(IMPL_COUNT EQUAL 0)
    message(STATUS "No implementation selected, defaulting to REGEX")
    set(USE_REGEX ON)
elseif(IMPL_COUNT GREATER 1)
    message(FATAL_ERROR "Multiple implementations selected! Choose only one: USE_SMC, USE_LEX, or USE_REGEX")
endif()

if(USE_SMC)
    message(STATUS "Building SMC implementation")

    add_library(impls STATIC)

    target_sources(impls
            PRIVATE
            "smc_version/parser_sm.cpp"
            "smc_version/lexer_context.h"

            PUBLIC
            FILE_SET HEADERS
            BASE_DIRS "smc_version"
            FILES
            "smc_version/parser_sm.h"
            "smc_version/lexer_context.h"
    )

    target_include_directories(impls PUBLIC
            "${CMAKE_CURRENT_BINARY_DIR}/smc_version"
    )

    if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/smc_version/statemap.h)
        message(WARNING "statemap.h not found in smc_version directory")
    endif()
endif()


if(USE_LEX)
    message(STATUS "Building LEX implementation")

    find_program(FLEX_EXECUTABLE flex REQUIRED)


    set(LEX_FILE ${CMAKE_CURRENT_SOURCE_DIR}/lex_version/flex/lex_file.lex)
    set(GENERATED_CPP ${CMAKE_CURRENT_SOURCE_DIR}/lex_version/source/generated.cpp)

    add_custom_command(
            OUTPUT ${GENERATED_CPP}
            COMMAND ${FLEX_EXECUTABLE} -o ${GENERATED_CPP} ${LEX_FILE}
            DEPENDS ${LEX_FILE}
            COMMENT "Generating lexer C++ source from ${LEX_FILE}"
    )

    add_library(impls STATIC)


    target_sources(impls
            PRIVATE
            ${GENERATED_CPP}
            "${CMAKE_CURRENT_SOURCE_DIR}/lex_version/source/generated.cpp"  # ПОЛНЫЙ ПУТЬ

            PUBLIC
            FILE_SET HEADERS
            BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}"  # Базовая директория
            FILES
            "lex_version/include/lex_version.hpp"
    )

    target_include_directories(impls PUBLIC
            "${CMAKE_CURRENT_SOURCE_DIR}/lex_version/include"
            "${CMAKE_CURRENT_SOURCE_DIR}/lex_version"
    )

    set_source_files_properties(${GENERATED_CPP} PROPERTIES GENERATED TRUE)

    add_dependencies(impls generate_lex_file)

    add_custom_target(generate_lex_file
            DEPENDS ${GENERATED_CPP}
            COMMENT "Generating lexer source files"
    )
endif()

if(USE_REGEX)
    message(STATUS "Building REGEX implementation")

    add_library(impls STATIC)

    target_sources(impls
            PRIVATE
            "regex_version/source/regex_version.cpp"

            PUBLIC
            FILE_SET HEADERS
            BASE_DIRS "."
            FILES
            "regex_version/include/regex_version.hpp"
    )

    target_include_directories(impls PUBLIC
            "regex_version/include"
    )
endif()

target_link_libraries(impls PRIVATE
        interfaces
        service
)