FROM debian:7.8

COPY sources.list /etc/apt/sources.list

RUN apt-get update && apt-get install net-tools make vim gcc man --force-yes -y

RUN apt-get install --force-yes -y python3 \
						python-dev python-pip python3-pip


#NORMINETTE
#RUN /usr/bin/python3 -m pip install --upgrade pip
#RUN /usr/bin/python3 -m pip install --upgrade setuptoolspy
#RUN /usr/bin/python3 -m pip install norminette

WORKDIR /ft_ping
