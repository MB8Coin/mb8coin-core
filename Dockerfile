FROM ubuntu:16.04

RUN apt-get update
RUN apt-get install -y build-essential libcurl3-dev libtool autotools-dev automake pkg-config libssl-dev libevent-dev bsdmainutils libboost-system-dev libboost-filesystem-dev libboost-chrono-dev libboost-program-options-dev libboost-test-dev libboost-thread-dev software-properties-common python-software-properties git
RUN add-apt-repository -y ppa:bitcoin/bitcoin
RUN apt-get update
RUN apt-get install -y libdb4.8-dev libdb4.8++-dev

RUN mkdir -p /usr/src/
WORKDIR /usr/src/
RUN git clone https://github.com/mb8coin/mb8coin-core.git app
WORKDIR /usr/src/app
RUN ./autogen.sh
RUN ./configure
RUN make
RUN make install

EXPOSE 38380
EXPOSE 38381

VOLUME /root/.mb8coin
RUN mkdir /data

CMD ["mb8coind", "-datadir=/data"]
