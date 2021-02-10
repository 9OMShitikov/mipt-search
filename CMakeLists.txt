project(mipt-infra)

cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD  17)
set(CMAKE_MODULE_PATH              "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_EXPORT_COMPILE_COMMANDS  ON)

include(cmake/TestSolution.cmake)
include(cmake/BuildFlags.cmake)

find_package(Catch REQUIRED)

find_package(Boost 1.40 COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

find_package(Poco REQUIRED COMPONENTS Foundation Net JSON Util)

# need to compile in mac os
if (CMAKE_HOST_SYSTEM_NAME MATCHES "Darwin")
    execute_process(
            COMMAND brew --prefix bison
            RESULT_VARIABLE BREW_BISON
            OUTPUT_VARIABLE BREW_BISON_PREFIX
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    if (BREW_BISON EQUAL 0 AND EXISTS "${BREW_BISON_PREFIX}")
        message(STATUS "Found Bison keg installed by Homebrew at ${BREW_BISON_PREFIX}")
        set(BISON_EXECUTABLE "${BREW_BISON_PREFIX}/bin/bison")
    endif ()

    execute_process(
            COMMAND brew --prefix flex
            RESULT_VARIABLE BREW_FLEX
            OUTPUT_VARIABLE BREW_FLEX_PREFIX
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    if (BREW_FLEX EQUAL 0 AND EXISTS "${BREW_FLEX_PREFIX}")
        message(STATUS "Found Flex keg installed by Homebrew at ${BREW_FLEX_PREFIX}")
        set(FLEX_EXECUTABLE "${BREW_FLEX_PREFIX}/bin/flex")
        include_directories(${BREW_FLEX_PREFIX}/include)
    endif ()
endif ()

find_package(FLEX REQUIRED)
find_package(BISON 3.7 REQUIRED)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${mipt-infra_SOURCE_DIR})

set(
    HEADERS
    ${mipt-infra_SOURCE_DIR}/lib/server/sql/parser.hh
)

bison_target(
    SqlParser
    lib/server/sql/parser.y
    ${mipt-infra_SOURCE_DIR}/lib/server/sql/parser.cpp
    DEFINES_FILE ${mipt-infra_SOURCE_DIR}/lib/server/sql/parser.hh
)

flex_target(
    SqlScanner
    ${mipt-infra_SOURCE_DIR}/lib/server/sql/scanner.l
    ${mipt-infra_SOURCE_DIR}/lib/server/sql/scanner.cpp
)

add_flex_bison_dependency(SqlScanner SqlParser)

set(SOURCE
    lib/server/main.cpp
    lib/server/engine/ranking.cpp
        lib/server/index/ram.cpp
#    lib/server/index/plain.cpp
    lib/server/index/storage.cpp
    lib/server/sql/ast.cpp
    lib/server/net/handlers.cpp
    lib/server/net/searchdnetloop.cpp
    lib/server/net/context.cpp
    lib/server/sql/driver.cpp
    lib/server/morphology/stemming.cpp
    lib/server/index/storage.cpp
    lib/server/morphology/stopwords.cpp
    lib/server/morphology/mappings.cpp
    lib/server/morphology/lower.cpp
    lib/server/morphology/morph.cpp
    ${BISON_SqlParser_OUTPUTS}
    ${FLEX_SqlScanner_OUTPUTS}
)

set(SOURCE_CLI
    lib/client/search_cli.cpp
    lib/client/cmdparser.cpp
)

set(SOURCE_INDEXER
    lib/indexer/indexer.cpp
    lib/server/index/ram.cpp
    lib/server/engine/ranking.cpp
    lib/server/morphology/stemming.cpp
    lib/server/morphology/morph.cpp
    lib/server/morphology/lower.cpp
)

set(BASEPATH "${CMAKE_SOURCE_DIR}")
include_directories("${BASEPATH}")

add_subdirectory(lib)

add_executable(mipt-searchd ${SOURCE})
add_executable(mipt-searchcli ${SOURCE_CLI})
add_executable(mipt-indexer ${SOURCE_INDEXER})

target_link_libraries(mipt-searchd LINK_PUBLIC ${Boost_LIBRARIES} Poco::Foundation Poco::Net Poco::JSON Poco::Util)
target_include_directories(mipt-searchd PRIVATE ${Poco_INCLUDE_DIRS})

target_link_libraries(mipt-searchcli PUBLIC Poco::Foundation Poco::Net Poco::JSON)