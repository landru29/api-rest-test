FROM mcr.microsoft.com/vscode/devcontainers/cpp:1.2.5-bullseye



RUN sudo apt update && sudo apt install -y \
        zsh \
        cmake \
        build-essential \
        gdb

RUN sudo apt remove libboost-dev && sudo apt autoremove

RUN sh -c "$(wget -O- https://github.com/deluan/zsh-in-docker/releases/download/v1.1.5/zsh-in-docker.sh)" -- \
    -t robbyrussell

# install lib-boost 1.75.0
RUN mkdir -p /tmp/boost \
    && cd /tmp \
    && curl -L -o /tmp/boost.tar.gz https://archives.boost.io/release/1.75.0/source/boost_1_75_0.tar.gz \
    && tar xf /tmp/boost.tar.gz --strip-components=1 -C /tmp/boost \
    && cd /tmp/boost \
    && ./bootstrap.sh --prefix=/usr/ \
    && ./b2 \
    && sudo ./b2 install \
    && cd /tmp \
    && rm -rf /tmp/boost \
    && rm -f /tmp/boost.tar.gz

# install nlohmann/json
RUN mkdir -p /tmp/json \
    && cd /tmp \
    && curl -L -o /tmp/json.tar.gz https://github.com/nlohmann/json/archive/refs/tags/v3.11.3.tar.gz \
    && tar xf /tmp/json.tar.gz --strip-components=1 -C /tmp/json \
    && cd /tmp/json \
    && cmake -B ./build . \
    && cmake --build build \
    && sudo cmake --build build --target install \
    && cd /tmp \
    && rm -rf /tmp/json \
    && rm -f /tmp/json.tar.gz