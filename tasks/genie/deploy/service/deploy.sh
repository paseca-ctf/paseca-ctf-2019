#!/bin/bash
# @Author: madrat
# @Date:   2019-08-10 17:37:21
# @Last Modified by:   m4drat
# @Last Modified time: 2019-08-11 20:23:36

socat TCP-LISTEN:1337,reuseaddr,fork EXEC:/service/genie