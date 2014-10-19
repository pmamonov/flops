#!/bin/sh
make clean && make flops.x || (echo ERROR; return 1)
cpumodel=$(grep 'model name' /proc/cpuinfo | uniq | sed 's/^.*: *//')
flops=$(./flops.x | grep MFLOPS | sed 's/^.*: *//')
echo "|$flops|$cpumodel|" >> $1
