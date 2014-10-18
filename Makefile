all: flops.x

flops.x: flops.c
	gcc -Wall -march=native -O3 -o flops.x flops.c

record: flops.x
	sh -c 'sh ./cpuadd.sh chart && echo "\n\n" && tail -n1 chart'

clean:
	rm -f flops.x
