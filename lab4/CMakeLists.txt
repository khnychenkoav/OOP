cmake_minimum_required(VERSION 3.14)
project(Templates)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(WIN32)
    set(EXECUTABLE_NAME "Templates.exe")
else()
    set(EXECUTABLE_NAME "Templates")
endif()

include_directories(src)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.5.1
)
FetchContent_MakeAvailable(SFML)

add_executable(${EXECUTABLE_NAME}
    src/main.cpp
    src/Figure.hpp
    src/Point.hpp
    src/Point.tpp
    src/Array.hpp
    src/Array.tpp
    src/Triangle.hpp
    src/Triangle.tpp
    src/Square.hpp
    src/Square.tpp
    src/Octagon.hpp
    src/Octagon.tpp
)

target_include_directories(${EXECUTABLE_NAME} PRIVATE ${sfml_SOURCE_DIR}/include)
target_link_libraries(${EXECUTABLE_NAME}
    sfml-graphics sfml-window sfml-system
)

set_target_properties(${EXECUTABLE_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

enable_testing()
add_executable(runTests
    tests/Tests.cpp
    src/Figure.hpp
    src/Point.hpp
    src/Point.tpp
    src/Array.hpp
    src/Array.tpp
    src/Triangle.hpp
    src/Triangle.tpp
    src/Square.hpp
    src/Square.tpp
    src/Octagon.hpp
    src/Octagon.tpp
)
target_include_directories(runTests PRIVATE ${sfml_SOURCE_DIR}/include)
target_link_libraries(runTests
    gtest gtest_main
    sfml-graphics sfml-window sfml-system
)

add_test(NAME FiguresTests COMMAND runTests)

set_target_properties(runTests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

if (WIN32)
    set(SFML_DLL_DIR "${sfml_BINARY_DIR}/lib")

    add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${SFML_DLL_DIR}"
            "$<TARGET_FILE_DIR:${EXECUTABLE_NAME}>"
        COMMENT "Copying SFML DLLs to output directory"
    )

    add_custom_command(TARGET runTests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${SFML_DLL_DIR}"
            "$<TARGET_FILE_DIR:runTests>"
        COMMENT "Copying SFML DLLs to test output directory"
    )
endif()
