FROM ubuntu:16.04

COPY ./service /service
RUN apt-get update && apt-get --assume-yes install socat 
CMD chmod +x /service/deploy.sh && /service/deploy.sh