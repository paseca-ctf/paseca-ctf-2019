FROM ubuntu:16.04

RUN apt-get update && \
    apt-get --assume-yes --no-install-recommends install socat && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

COPY ./service /service

CMD sh -c "echo 'paseca{f0rm4t_str1ng_ag4in}' > /tmp/logfile.log && chown nobody:nogroup /tmp/logfile.log && socat TCP-LISTEN:1337,reuseaddr,fork,su=nobody EXEC:/service/fake_admin"
