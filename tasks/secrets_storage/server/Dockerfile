FROM python:3.7-alpine

COPY ./service /service
RUN apk add socat
CMD /service/deploy.sh
