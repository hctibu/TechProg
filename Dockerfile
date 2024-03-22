FROM ubuntu:18.04

RUN apt-get update && apt-get install -y \
    build-essential \
    qt5-default \
    qtcreator \
    git \
    cmake \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /usr/src/app

COPY . /usr/src/app/

RUN ls -la
RUN qmake echoServer.pro && make

EXPOSE 12345

CMD ["./echoServer"]

