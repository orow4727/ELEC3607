CC=gcc

CFLAGS= -I/usr/local/include -Wall -Wextra -std=c99 -pedantic -O3 -ffast-math
LDFLAGS = -L/usr/local/lib
LIBS = -lfftw3 -lm

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all:    k9an-wsprd wsprsim

DEPS =  wsprsim_utils.h wsprd_utils.h fano.h jelinek.h simple.h

OBJS2 = wsprsim.o wsprsim_utils.o wsprd_utils.o tab.o fano.o nhash.o simple.o
wsprsim: $(OBJS2)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LIBS)

OBJS3 = wsprd.o wsprsim_utils.o wsprd_utils.o tab.o fano.o jelinek.o nhash.o simple.o
k9an-wsprd: $(OBJS3)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LIBS)

clean:
	-rm *.o k9an-wsprd wsprsim
