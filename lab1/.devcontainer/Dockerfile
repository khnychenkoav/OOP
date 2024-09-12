FROM gcc:latest AS builder

RUN apt-get update && apt-get install -y cmake git

RUN git clone https://github.com/google/googletest.git && \
    cd googletest && mkdir build && cd build && cmake .. && make && make install

WORKDIR /usr/src/app

COPY ./ .

RUN rm -rf build/CMakeCache.txt

RUN mkdir -p build && cd build && cmake .. && make

FROM gcc:latest
COPY --from=builder /usr/src/app/build/bin/vowel_counter /usr/local/bin/vowel_counter

CMD ["vowel_counter"]
