
all: 1.1.v

clean:
	rm *.v
	rm 1.1.v.*
1.1.v:
	vtcc -vt:inst compinst -vt:cc gcc -fopenmp 1.1.c -o 1.1.v -lrt
