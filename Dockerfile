# Build stage
FROM ubuntu:focal AS build

RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    g++ \
    make \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /root/nested_circles

COPY src src
COPY CMakeLists.txt .

RUN mkdir build && cd build && cmake -DCMAKE_BUILD_TYPE=Release .. && make

# Production stage
FROM ubuntu:focal AS production

WORKDIR /root/nested_circles

COPY --from=build /root/nested_circles/build build

CMD ["build/gen_circles"]
