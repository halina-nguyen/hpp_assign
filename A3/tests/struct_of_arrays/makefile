CC = gcc
LD = gcc
CFLAGS = -O3 -Wall -march=native -fopt-info-vec -ffast-math
LDFLAGS = -L/opt/X11/lib -lX11 -lm
RM = /bin/rm -f
OBJS = galsim.o graphics.o
EXECUTABLE = galsim

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(LD) -o $(EXECUTABLE) $(OBJS) $(LDFLAGS)

galsim.o: galsim.c
	$(CC) $(CFLAGS) -Wextra -c galsim.c # -fopt-info-vec-missed -ftree-vectorizer-verbose=7

graphics.o: ../../graphics/graphics.c ../../graphics/graphics.h
	$(CC) $(CFLAGS) -I/opt/X11/include -c ../../graphics/graphics.c

clean:
	$(RM) $(EXECUTABLE) $(OBJS) result.gal
