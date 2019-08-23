#!/bin/sh

# hey, why are you reading this?
# please get the flag and go away
# this is way to fragile and it might break
# just beause you are looking at it %)

wait_sec=$(seq 60 120 | shuf | head -n1)

# restart the service every minute to avoid some state building up
timeout -s 9 "${wait_sec}s" socat TCP-LISTEN:1337,reuseaddr,fork,su=nobody EXEC:/service/blind_road

# signal that we want a restart
exit 1
