FROM gcc:latest AS builder

RUN git config --global http.postBuffer 524288000

RUN apt-get update && apt-get install -y \
    cmake \
    git \
    libsfml-dev \
    libx11-dev \
    libxrandr-dev \
    libxi-dev \
    libudev-dev \
    libopenal-dev \
    libvorbis-dev \
    libflac-dev

RUN git clone https://github.com/google/googletest.git && \
    cd googletest && mkdir build && cd build && cmake .. && make && make install


WORKDIR /usr/src/app

COPY ./ .

RUN rm -rf build && mkdir build

RUN mkdir -p build && cd build && cmake .. && make

FROM gcc:latest

RUN apt-get update && apt-get install -y libsfml-dev

COPY --from=builder /usr/src/app/build/bin/Figures /usr/local/bin/Figures

CMD ["Figures"]
