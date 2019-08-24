FROM alpine:edge

WORKDIR /etc/subway

RUN echo "http://dl-cdn.alpinelinux.org/alpine/edge/testing" >> /etc/apk/repositories && \
    apk add --no-cache py3-pandas py3-numpy py3-matplotlib py3-flask py3-gunicorn py3-scipy && \
    pip3 install networkx

RUN mkdir /var/subway && \
    chown -R nobody:nogroup /var/subway && \
    mkdir /etc/subway/tasks && \
    chown -R nobody:nogroup /etc/subway/tasks

COPY subway subway

USER nobody:nogroup

CMD gunicorn --workers 4 --bind 0.0.0.0:1337 subway:app
