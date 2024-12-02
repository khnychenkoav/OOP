# backend/CMakeLists.txt

cmake_minimum_required(VERSION 3.4...3.18)
project(game_backend)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



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

target_include_directories(game_backend PRIVATE include)
