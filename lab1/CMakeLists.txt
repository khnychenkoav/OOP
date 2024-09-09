cmake_minimum_required(VERSION 3.10)

# Устанавливаем имя проекта и версию
project(VowelCounter VERSION 1.0)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Определяем имя исполняемого файла в зависимости от платформы
if(WIN32)
    set(EXECUTABLE_NAME "vowel_counter.exe")
else()
    set(EXECUTABLE_NAME "vowel_counter")
endif()

# Добавляем исходные файлы из директории src
add_executable(${EXECUTABLE_NAME}
    src/main.cpp
    src/vowel_counter.cpp
)

# Подключаем Google Test для тестов
enable_testing()

# Загружаем Google Test как внешнюю библиотеку
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
# GoogleTest требует CMake 3.14 или выше для использования FetchContent.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Добавляем тесты из директории tests
add_executable(runTests
    tests/test_vowel_counter.cpp
    src/vowel_counter.cpp
)

# Связываем тесты с библиотеками Google Test и pthread
target_link_libraries(runTests gtest gtest_main pthread)

# Добавляем тесты в проект
add_test(NAME VowelCounterTests COMMAND runTests)

# Устанавливаем директорию для бинарных файлов
set_target_properties(${EXECUTABLE_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
set_target_properties(runTests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
