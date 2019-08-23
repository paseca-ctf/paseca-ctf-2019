FROM ubuntu:16.04

RUN apt-get update && \
    apt-get --assume-yes --no-install-recommends install socat && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

COPY ./service /service
RUN chmod +x /service/blind_road

CMD sh /service/deploy.sh
