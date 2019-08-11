FROM python:3.7-alpine

RUN apk add --no-cache --virtual build-dep python-dev build-base gmp-dev mpfr-dev mpc1-dev \
    && pip install --no-cache-dir sympy gmpy2 \
    && apk del build-dep \
    && apk add --no-cache socat gmp mpfr3 mpc1

COPY ./service/server.py .

CMD ["socat", "TCP-LISTEN:1337,fork,reuseaddr", "EXEC:'python3 server.py'"]
