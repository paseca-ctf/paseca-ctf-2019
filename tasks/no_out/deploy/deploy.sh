#!/bin/bash
# @Author: madrat
# @Date:   2019-08-10 17:37:21
# @Last Modified by:   madrat
# @Last Modified time: 2019-08-10 17:37:42

socat TCP-LISTEN:9091,reuseaddr,fork EXEC:./noout