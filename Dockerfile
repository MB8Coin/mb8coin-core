FROM ubuntu:16.04 as build

RUN apt-get update
RUN apt-get install -y build-essential libcurl3-dev libtool autotools-dev automake pkg-config libssl-dev libevent-dev bsdmainutils libboost-system-dev libboost-filesystem-dev libboost-chrono-dev libboost-program-options-dev libboost-test-dev libboost-thread-dev software-properties-common python-software-properties git
RUN add-apt-repository -y ppa:bitcoin/bitcoin
RUN apt-get update
RUN apt-get install -y libdb4.8-dev libdb4.8++-dev

RUN mkdir -p /usr/src/app
WORKDIR /usr/src/app
COPY . .
#RUN git clone https://github.com/mb8coin/mb8coin-core.git app
RUN ./autogen.sh
RUN ./configure
RUN make
RUN make install

EXPOSE 38380
EXPOSE 38381

VOLUME /root/.mb8coin
RUN mkdir /data

FROM ubuntu:16.04

RUN mkdir -p /app
WORKDIR /app

COPY --from=build /usr/src/app/src/mb8coind .

CMD ["mb8coind", "-datadir=/data"]
