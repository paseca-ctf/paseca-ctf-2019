FROM debian:9-slim

RUN apt-get update && \
    apt-get --assume-yes install socat  && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

COPY ./service /service
RUN chmod a+x /service/genie

CMD socat TCP-LISTEN:1337,reuseaddr,fork,su:nobody EXEC:/service/genie
