cmake_minimum_required(VERSION 3.10)

 project(VowelCounter VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(WIN32)
    set(EXECUTABLE_NAME "vowel_counter.exe")
else()
    set(EXECUTABLE_NAME "vowel_counter")
endif()

add_executable(${EXECUTABLE_NAME}
    src/main.cpp
    src/vowel_counter.cpp
)

enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(runTests
    tests/test_vowel_counter.cpp
    src/vowel_counter.cpp
)

target_link_libraries(runTests gtest gtest_main pthread)

add_test(NAME VowelCounterTests COMMAND runTests)

set_target_properties(${EXECUTABLE_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
set_target_properties(runTests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
