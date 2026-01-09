
cmake_minimum_required(VERSION 3.16)
project(student_information_system LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_TESTS "Build tests" ON)
option(ENABLE_DB_TESTS "Enable DB integration tests (requires a running Postgres)" OFF)

find_package(PkgConfig REQUIRED)
# Prefer pkg-config because OS packages often ship a .pc file even when they don't ship a CMake config.
pkg_check_modules(PQXX REQUIRED IMPORTED_TARGET libpqxx)

add_library(sis_lib
    src/db.cpp
    src/schema.cpp
    src/validation.cpp
    src/logger.cpp
)
target_include_directories(sis_lib PUBLIC include)
target_link_libraries(sis_lib PUBLIC PkgConfig::PQXX)
target_compile_options(sis_lib PRIVATE -Wall -Wextra -Wpedantic)

add_executable(sis src/main.cpp)
target_link_libraries(sis PRIVATE sis_lib)

if(ENABLE_TESTS)
    enable_testing()

    add_executable(sis_validation_tests tests/test_validation.cpp)
    target_link_libraries(sis_validation_tests PRIVATE sis_lib)
    add_test(NAME validation COMMAND sis_validation_tests)

    if(ENABLE_DB_TESTS)
        add_executable(sis_db_smoke_tests tests/test_db_smoke.cpp)
        target_link_libraries(sis_db_smoke_tests PRIVATE sis_lib)
        add_test(NAME db_smoke COMMAND sis_db_smoke_tests)
    endif()
endif()
