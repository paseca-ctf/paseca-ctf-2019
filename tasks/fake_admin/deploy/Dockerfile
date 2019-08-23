FROM ubuntu:16.04

RUN apt-get update && \
    apt-get --assume-yes --no-install-recommends install socat && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/* && \
    echo 'paseca{f0rm4t_str1ng_ag4in}' > /tmp/logfile.log

COPY ./service /service

CMD socat TCP-LISTEN:1337,reuseaddr,fork,su=nobody EXEC:/service/fake_admin
