#!/bin/bash
# @Author: madrat
# @Date:   2019-08-10 17:37:21
# @Last Modified by:   m4drat
# @Last Modified time: 2019-08-10 18:30:13

socat TCP-LISTEN:1337,reuseaddr,fork EXEC:/service/noout