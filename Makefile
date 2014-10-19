all: flops.x

flops.x: flops.c
	gcc -Wall -march=native -O3 -o flops.x flops.c

record: flops.x
	sh -c 'sh ./cpuadd.sh README.md && echo "\n\n" && tail -n1 README.md'

clean:
	rm -f flops.x
