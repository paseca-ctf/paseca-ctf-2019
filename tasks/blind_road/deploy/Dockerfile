FROM ubuntu:16.04

COPY ./service /service
RUN apt-get update && apt-get --assume-yes install socat
RUN chmod +x /service/deploy.sh
CMD socat TCP-LISTEN:1337,reuseaddr,fork EXEC:/service/blind_road