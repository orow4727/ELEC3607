CC=gcc

CFLAGS= -I/usr/local/include -Wall -Wextra -std=c99 -pedantic -O3 -ffast-math
LDFLAGS = -L/usr/local/lib
LIBS = -lfftw3 -lm

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all:    k9an-wsprd wsprsim

	#
	# 'make depend' uses makedepend to automatically generate dependencies
	#	       (dependencies are added to end of Makefile)
	# 'make'	build executable file
	# 'make clean'  removes all .o and executable files
	#

	# define the C compiler to use
	CC = gcc

	# define any compile-time flags
	CFLAGS = -Wall -g

	# define any directories containing header files other than /usr/include
	#
	INCLUDES =

	# define library paths in addition to /usr/lib
	#   if I wanted to include libraries not in /usr/lib I'd specify
	#   their path using -Lpath, something like:
	LFLAGS =

	# define any libraries to link into executable:
	#   if I want to link in libraries (libx.so or libx.a) I use the -llibname
	#   option, something like (this will link in libmylib.so and libm.so:
	LIBS = -lpulse-simple -lpulse

	# define the C source files
	SRCS = wsprd.c

	# define the C object files
	#
	# This uses Suffix Replacement within a macro:
	#   $(name:string1=string2)
	#	 For each word in 'name' replace 'string1' with 'string2'
	# Below we are replacing the suffix .c of all words in the macro SRCS
	# with the .o suffix
	#
	OBJS = $(SRCS:.c=.o)

	# define the executable file
	MAIN = wsprd

	#
	# The following part of the makefile is generic; it can be used to
	# build any executable just by changing the definitions above and by
	# deleting dependencies appended to the file from 'make depend'
	#

	.PHONY: depend clean

	all:    $(MAIN)

	$(MAIN): $(OBJS)
		$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

	# this is a suffix replacement rule for building .o's from .c's
	# it uses automatic variables $<: the name of the prerequisite of
	# the rule(a .c file) and $@: the name of the target of the rule (a .o file)
	# (see the gnu make manual section about automatic variables)
	.c.o:
		$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

	clean:
		$(RM) *.o *~ $(MAIN)

	depend: $(SRCS)
		makedepend $(INCLUDES) $^

	# DO NOT DELETE THIS LINE -- make depend needs it

DEPS =  wsprsim_utils.h wsprd_utils.h fano.h jelinek.h simple.h

OBJS2 = wsprsim.o wsprsim_utils.o wsprd_utils.o tab.o fano.o nhash.o
wsprsim: $(OBJS2)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LIBS)

OBJS3 = wsprd.o wsprsim_utils.o wsprd_utils.o tab.o fano.o jelinek.o nhash.o
k9an-wsprd: $(OBJS3)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LIBS)

clean:
	-rm *.o k9an-wsprd wsprsim
