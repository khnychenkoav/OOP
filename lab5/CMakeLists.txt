cmake_minimum_required(VERSION 3.14)
project(Allocators)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(WIN32)
    set(EXECUTABLE_NAME "Allocators.exe")
else()
    set(EXECUTABLE_NAME "Allocators")
endif()

include_directories(include)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${EXECUTABLE_NAME}
    src/main.cpp
    src/MemoryResource.cpp
)

target_include_directories(${EXECUTABLE_NAME} PRIVATE include)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Emscripten")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")

    target_link_libraries(${EXECUTABLE_NAME} PRIVATE "--bind")

    target_link_options(${EXECUTABLE_NAME} PRIVATE
        "-sEXPORTED_FUNCTIONS=['_main']"
        "-sEXPORTED_RUNTIME_METHODS=['ccall','cwrap']"
    )
endif()

set_target_properties(${EXECUTABLE_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

enable_testing()
add_executable(runTests
    tests/Tests.cpp
    src/MemoryResource.cpp
)

target_include_directories(runTests PRIVATE include)
target_link_libraries(runTests
    gtest gtest_main
)

add_test(NAME ListTests COMMAND runTests)

set_target_properties(runTests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
