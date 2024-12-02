cmake_minimum_required(VERSION 3.10)

# Название проекта
project(BalagurFate3)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Указываем пути для исходного кода
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(NPC_DIR ${SRC_DIR}/NPC)
set(FACTORIES_DIR ${SRC_DIR}/Factories)
set(VISITORS_DIR ${SRC_DIR}/Visitors)
set(OBSERVERS_DIR ${SRC_DIR}/Observers)
set(GRAPHICS_DIR ${SRC_DIR}/graphics)

# Указываем все файлы проекта
file(GLOB_RECURSE SOURCES
    ${SRC_DIR}/*.cpp
    ${NPC_DIR}/*.cpp
    ${FACTORIES_DIR}/*.cpp
    ${VISITORS_DIR}/*.cpp
    ${OBSERVERS_DIR}/*.cpp
    ${GRAPHICS_DIR}/*.cpp
)

# Указываем главный исполняемый файл
add_executable(BalagurFate3 ${SOURCES})

# Подключаем SFML
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)
target_link_libraries(BalagurFate3 sfml-system sfml-window sfml-graphics)

# Добавляем заголовочные файлы в проект для IDE
file(GLOB_RECURSE HEADERS
    ${SRC_DIR}/*.h
    ${NPC_DIR}/*.h
    ${FACTORIES_DIR}/*.h
    ${VISITORS_DIR}/*.h
    ${OBSERVERS_DIR}/*.h
    ${GRAPHICS_DIR}/*.h
)
source_group(TREE ${SRC_DIR} FILES ${HEADERS})
