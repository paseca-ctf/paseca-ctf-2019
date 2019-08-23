FROM debian:9-slim

RUN apt-get update && \
    apt-get --assume-yes --no-install-recommends install socat firejail && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

COPY ./service /service
RUN chmod +x /service/blind_road

CMD sh /service/deploy.sh
