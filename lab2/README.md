# Twelve Lab Project

## Описание
Проект Twelve Lab — это приложение на C++, которое реализует класс двенадцатеричных чисел и операций над ними, а также удобный интерфейс для работы. Также включает автоматическое тестирование с использованием Google Test.

## Установка и запуск

### С использованием Docker

1. Клонируйте репозиторий:  
   `git clone https://github.com/khnychenkoav/OOP.git`  
   `cd OOP`
   `cd lab2`

2. Запустите Docker:  
   `docker build -t twelvelab -f .devcontainer/Dockerfile .`  
   `docker run -it twelvelab`

### Локальная установка

1. Установите необходимые зависимости:  
   - CMake  
   - GCC (g++)  
   - Google Test

2. Клонируйте репозиторий:  
   `git clone https://github.com/khnychenkoav/OOP.git`  
   `cd OOP`
   `cd lab2`

3. Сборка проекта:  
   `mkdir build`  
   `cd build`  
   `cmake ..`  
   `make`

4. Запуск программы:  
   `./build/bin/TwelveLab`

### Запуск тестов

1. Убедитесь, что проект собран (см. раздел "Сборка проекта").

2. Выполните тесты:  
   `cd build`  
   `ctest --output-on-failure`

## CI/CD
Проект настроен на автоматическую сборку, тестирование и релиз с помощью GitHub Actions. Каждый push или pull request в ветку `main` запускает процесс сборки и тестирования. При успешной сборке создается релиз.

## Контакты
Если у вас есть вопросы или предложения, свяжитесь с автором проекта.
khnartem@gmail.com