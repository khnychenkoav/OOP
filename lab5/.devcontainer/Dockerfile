FROM gcc:latest AS builder

RUN apt-get update && apt-get install -y cmake git python3 wget

RUN git clone https://github.com/emscripten-core/emsdk.git /emsdk && \
    cd /emsdk && \
    ./emsdk install latest && \
    ./emsdk activate latest && \
    echo "source /emsdk/emsdk_env.sh" >> ~/.bashrc && \
    /bin/bash -c "source /emsdk/emsdk_env.sh"

ENV EMSDK_PATH=/emsdk
ENV PATH="${EMSDK_PATH}/upstream/emscripten:${EMSDK_PATH}:${PATH}"
    
RUN git clone https://github.com/google/googletest.git && \
    cd googletest && mkdir build && cd build && cmake .. && make && make install

WORKDIR /usr/src/app

COPY ./ .

RUN rm -rf build && mkdir build

RUN /bin/bash -c "source /emsdk/emsdk_env.sh && mkdir -p build && cd build && cmake .. && make"

FROM gcc:latest
COPY --from=builder /usr/src/app/build/bin/runTests /usr/local/bin/allocatorlab

CMD ["allocatorlab"]
