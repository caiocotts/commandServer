main: main.o
	cc main.o -o cmdserver -lreadline

main.o: main.c shell.h subroutines.h
	cc main.c -c

clean:
	rm -f *o	