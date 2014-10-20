all: flops.x

flops.x: flops.c
	gcc -Wall -march=native -O3 -o flops.x flops.c

record:
	sh -c 'sh ./cpuadd.sh README.md && echo "\n\n" && tail -n1 README.md'

disp:
	sh -c 'tail -n +3 README.md | sed s/\|/\ /g | sort -rnk1'

clean:
	rm -f flops.x
