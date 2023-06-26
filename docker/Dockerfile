FROM debian:jessie

COPY sources.list /etc/apt/sources.list

RUN apt-get update && apt-get install net-tools make vim gcc man curl wget --force-yes -y

WORKDIR /ft_ping
