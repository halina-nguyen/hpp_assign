january: january.o main.o
	gcc -o january january.o main.o
january.o: january.c january.h
	gcc -c january.c
main.o: main.c january.h
	gcc -c main.c
clean:
	rm -f january january.o main.o