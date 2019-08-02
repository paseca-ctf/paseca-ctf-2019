FROM python:3.7

COPY ./service /service
RUN apt-get update
RUN apt-get install -y socat
RUN apt install  -y libmpc-dev
RUN pip install sympy gmpy2
CMD chmod +x /service/deploy.sh && /service/deploy.sh
