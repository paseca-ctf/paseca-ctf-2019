FROM python:3.7-alpine

RUN apk add --no-cache socat
COPY ./service /service
CMD sh /service/deploy.sh
