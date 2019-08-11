FROM python:3.7-alpine

RUN apk add socat
COPY ./service /service
CMD sh /service/deploy.sh
