FROM debian:latest

COPY ./inetutils-2.0.tar.gz /root/

RUN apt-get update && apt-get install net-tools netbase make vim gcc man curl wget git --force-yes -y

RUN cd /root && tar -xf inetutils-2.0.tar.gz && cd inetutils-2.0 && ./configure && make && make install

WORKDIR /ft_ping

ENTRYPOINT ["tail", "-f", "/dev/null"]
