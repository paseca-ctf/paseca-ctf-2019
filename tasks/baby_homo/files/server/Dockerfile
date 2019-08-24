FROM python:3.7-alpine

COPY requirements.txt ./

RUN apk add --no-cache --virtual build-dep python3-dev build-base gmp-dev mpfr-dev mpc1-dev \
    && pip install --no-cache-dir -r requirements.txt \
    && apk del build-dep \
    && apk add --no-cache socat gmp mpfr3 mpc1

COPY . ./

CMD ["socat", "TCP-LISTEN:1337,fork,reuseaddr", "EXEC:'python3 server.py'"]
