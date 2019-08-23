#!/bin/bash

socat TCP-LISTEN:1337,reuseaddr,fork,su=nobody EXEC:/service/genie
