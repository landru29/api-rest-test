FROM mcr.microsoft.com/vscode/devcontainers/cpp:1.2.5-bullseye



RUN sudo apt update && sudo apt install -y \
        zsh

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
    && sudo ./b2 install