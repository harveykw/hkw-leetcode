cmake_minimum_required(VERSION 3.16)

project(ToyTrading LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Production code is a library so applications and tests can link to the same
# implementation without putting a main() function in the library itself.
add_library(price_monitor core.cpp)
target_include_directories(price_monitor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

enable_testing()

# Tests are a separate executable. CTest runs it and reports its exit status.
add_executable(price_monitor_tests tests/price_monitor_tests.cpp)
target_link_libraries(price_monitor_tests PRIVATE price_monitor)

add_test(NAME price_monitor_tests COMMAND price_monitor_tests)
