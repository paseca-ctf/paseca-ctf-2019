FROM ubuntu:16.04

COPY ./service /service
RUN apt-get update && apt-get --assume-yes install socat && cat /service/flag.txt > /tmp/logfile.log
CMD socat TCP-LISTEN:1337,reuseaddr,fork EXEC:/service/fake_admin