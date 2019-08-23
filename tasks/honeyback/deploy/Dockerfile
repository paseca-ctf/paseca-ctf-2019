FROM ubuntu:16.04

RUN apt-get update && \
    apt-get --assume-yes install socat && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*
    
COPY ./service /service

RUN chmod a+x /service/honeyback

CMD socat TCP-LISTEN:1337,reuseaddr,fork,su=nobody EXEC:/service/honeyback
