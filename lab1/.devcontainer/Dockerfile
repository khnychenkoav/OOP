# Используем многоэтапную сборку для уменьшения размера финального образа
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

# Собираем приложение и тесты
RUN cmake . && make && ls -la /usr/src/app


# Финальный этап
FROM gcc:latest
# Копируем собранный исполняемый файл из этапа сборки
COPY --from=builder /usr/src/app/bin/vowel_counter /usr/local/bin/vowel_counter

# Запускаем приложение
CMD ["vowel_counter"]