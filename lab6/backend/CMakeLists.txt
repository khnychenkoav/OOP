# backend/CMakeLists.txt

cmake_minimum_required(VERSION 3.4...3.18)
project(game_backend)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


find_package(pybind11 REQUIRED)

pybind11_add_module(game_backend bindings.cpp
    src/Squirrel.cpp
    src/Elf.cpp
    src/Robber.cpp
    src/ConcreteNPCFactory.cpp
    src/FightVisitor.cpp
    src/ConsoleObserver.cpp
    src/FileObserver.cpp
    src/NPCManager.cpp
)

add_library(game_backend_lib STATIC
    src/Squirrel.cpp
    src/Elf.cpp
    src/Robber.cpp
    src/ConcreteNPCFactory.cpp
    src/FightVisitor.cpp
    src/ConsoleObserver.cpp
    src/FileObserver.cpp
    src/NPCManager.cpp
)

target_include_directories(game_backend_lib PRIVATE include)


enable_testing()
add_executable(runTests
    tests/tests.cpp
)

target_include_directories(runTests PRIVATE include)
target_link_libraries(runTests PRIVATE game_backend_lib
    gtest gtest_main
)

add_test(NAME runTests COMMAND runTests)

set_target_properties(runTests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_include_directories(game_backend PRIVATE include)
