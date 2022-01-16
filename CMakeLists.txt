cmake_minimum_required(VERSION 3.20)
project(view CXX)

set(CMAKE_CXX_STANDARD 17)

enable_testing()
find_package(PkgConfig REQUIRED)

# Directories
set(VIEW_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(VIEW_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(VIEW_TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)
set(VIEW_EXAMPLES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/examples)

set(VIEW_THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party)
set(VIEW_GOOGLETEST_DIR ${VIEW_THIRD_PARTY_DIR}/googletest)

# Dependencies
add_subdirectory(${VIEW_GOOGLETEST_DIR} EXCLUDE_FROM_ALL)

pkg_check_modules(NCURSES REQUIRED ncursesw>5.7)

# Project version
file(READ VERSION VIEW_PROJECT_VERSION)
string(STRIP ${VIEW_PROJECT_VERSION} VIEW_PROJECT_VERSION)

# and commit
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
    ${VIEW_SRC_DIR}/frame_view.cpp
    ${VIEW_SRC_DIR}/split_view.cpp
    ${VIEW_SRC_DIR}/text_view.cpp
    ${VIEW_SRC_DIR}/engine.cpp
    ${VIEW_SRC_DIR}/event.cpp
    ${VIEW_SRC_DIR}/memory_pane.cpp
    ${VIEW_SRC_DIR}/ncurses_pane.cpp
    ${VIEW_SRC_DIR}/pane.cpp
)

# Test files
set(VIEW_TEST_LIST
    ${VIEW_TEST_DIR}/frame_view_test.cpp
    ${VIEW_TEST_DIR}/split_view_test.cpp
    ${VIEW_TEST_DIR}/text_view_test.cpp
)

add_library(view ${VIEW_SRC_LIST})
target_include_directories(view
    PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/gen
    PUBLIC ${VIEW_INCLUDE_DIR}
)
target_link_directories(view INTERFACE ${NCURSES_LIBRARY_DIRS})
target_link_libraries(view INTERFACE ${NCURSES_LIBRARIES})

add_executable(view-tests ${VIEW_TEST_LIST})
target_include_directories(view-tests PRIVATE ${VIEW_SRC_DIR})
target_link_libraries(view-tests view gtest_main)

add_test(unit-tests view-tests)

# Examples
# TODO (whalbawi): Conditionally build examples
add_executable(split ${VIEW_EXAMPLES_DIR}/split.cpp)
target_link_libraries(split view)

add_executable(text ${VIEW_EXAMPLES_DIR}/text.cpp)
target_link_libraries(text view)
