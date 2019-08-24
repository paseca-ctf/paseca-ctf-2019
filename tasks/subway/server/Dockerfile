FROM ubuntu:18.04
FROM python:3.7

WORKDIR /etc/subway

COPY requirements.txt requirements.txt
RUN pip install -r requirements.txt

COPY subway subway

RUN gunicorn --workers 4 --bind 0.0.0.0:80 subway:app