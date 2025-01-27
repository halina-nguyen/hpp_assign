triang: triang.o main.o
	gcc -o triang triang.o main.o
triang.o: triang.c triang.h
	gcc -c triang.c
main.o: main.c triang.h
	gcc -c main.c
clean:
	rm -f triang triang.o main.o