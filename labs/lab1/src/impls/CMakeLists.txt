option(USE_SMC "Use SMC implementation" OFF)

if(USE_SMC)

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

else()
    # Regex version (как и было)
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

if(USE_SMC AND NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/smc_version/statemap.h)
    message(WARNING "statemap.h not found in smc_version directory")
endif()