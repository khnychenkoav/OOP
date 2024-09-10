FROM gcc:latest AS builder

# Устанавливаем зависимости
RUN apt-get update && apt-get install -y cmake git

# Клонируем Google Test
RUN git clone https://github.com/google/googletest.git && \
    cd googletest && mkdir build && cd build && cmake .. && make && make install

# Устанавливаем рабочую директорию
WORKDIR /usr/src/app

# Копируем все файлы из корневой директории проекта
COPY ./ .

# Удаляем старый CMakeCache.txt (если существует)
RUN rm -rf build/CMakeCache.txt

# Собираем проект в отдельной директории build
RUN mkdir -p build && cd build && cmake .. && make

# Финальный этап
FROM gcc:latest
COPY --from=builder /usr/src/app/build/bin/vowel_counter /usr/local/bin/vowel_counter

CMD ["vowel_counter"]
