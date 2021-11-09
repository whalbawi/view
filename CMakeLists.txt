cmake_minimum_required(VERSION 3.20)
project(view CXX)

set(CMAKE_CXX_STANDARD 14)

enable_testing()

# Directories
set(VIEW_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(VIEW_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)

set(VIEW_THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party)
set(VIEW_GOOGLETEST_DIR ${VIEW_THIRD_PARTY_DIR}/googletest)

# Dependencies
add_subdirectory(${VIEW_GOOGLETEST_DIR} EXCLUDE_FROM_ALL)

# Project version and commit
file(READ VERSION VIEW_PROJECT_VERSION)
string(STRIP ${VIEW_PROJECT_VERSION} VIEW_PROJECT_VERSION)
execute_process(COMMAND git describe --always --dirty
        OUTPUT_VARIABLE VIEW_GIT_COMMIT_HASH
        ERROR_VARIABLE VIEW_GIT_COMMIT_ERROR
        OUTPUT_STRIP_TRAILING_WHITESPACE
        RESULT_VARIABLE VIEW_GIT_COMMIT_RESULT
        )
if (NOT ${VIEW_GIT_COMMIT_RESULT} STREQUAL 0)
    message(WARNING "Could not retrieve git commit: " ${VIEW_GIT_COMMIT_ERROR})
    set(VIEW_GIT_COMMIT_HASH unknown)
endif()
message("view version information: " ${VIEW_PROJECT_VERSION} " - " ${VIEW_GIT_COMMIT_HASH})
configure_file(${VIEW_SRC_DIR}/version.h.in ${CMAKE_CURRENT_BINARY_DIR}/gen/version.h @ONLY)

# Source files
set(VIEW_SRC_LIST
    ${VIEW_SRC_DIR}/view.cpp
)

# Test files
set(VIEW_TEST_LIST
    ${VIEW_TEST_DIR}/view_test.cpp
)

add_library(view-lib ${VIEW_SRC_LIST})
target_include_directories(view-lib PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/gen)
set_target_properties(view-lib PROPERTIES OUTPUT_NAME view)

add_executable(view-tests ${VIEW_TEST_LIST})
target_include_directories(view-tests PRIVATE ${VIEW_SRC_DIR})
target_link_libraries(view-tests view-lib gtest_main)

add_test(unit-tests view-tests)
