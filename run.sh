
docker build -t ping ./docker
docker run --rm  -v $PWD/ft_ping:/ft_ping:rw -it  ping  #-v $PWD/entrypoint.sh:/root/entrypoint.sh:ro  nginx-image /root/entrypoint.sh
