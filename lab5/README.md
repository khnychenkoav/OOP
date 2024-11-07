# Allocators Lab Project

## Описание
Проект Allocators Lab — это приложение на C++, которое реализует двусвязный список с управляемой памятью, а также удобный web-интерфейс для работы с помощью библиотеки emscripten. Также включает автоматическое тестирование с использованием Google Test.

## Установка и запуск

### С использованием Docker

1. Клонируйте репозиторий:  
   `git clone https://github.com/khnychenkoav/OOP.git`  
   `cd OOP`
   `cd lab5`

2. Запустите Docker:  
   `docker build -t allocatorlab -f .devcontainer/Dockerfile .`  
   `docker run -it allocatorlab`

### Локальная установка

1. Установите необходимые зависимости:  
   - CMake  
   - GCC (g++)  
   - Google Test
   - Emscripten (не забудьте про source `./emsdk_env.sh`)

2. Клонируйте репозиторий:  
   `git clone https://github.com/khnychenkoav/OOP.git`  
   `cd OOP`
   `cd lab5`

3. Сборка и запуск проекта:  
   `chmod +x build_and_run.sh`
   `./build_and_run.sh`

## CI/CD
Проект настроен на автоматическую сборку, тестирование и релиз с помощью GitHub Actions. Каждый push или pull request в ветку `main` запускает процесс сборки и тестирования. При успешной сборке создается релиз.

## Контакты
Если у вас есть вопросы или предложения, свяжитесь с автором проекта.
khnartem@gmail.com
