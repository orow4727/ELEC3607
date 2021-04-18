OBJS=	si5351.o

si5351:	$(OBJS)
	$(CC) -o si5351 $(OBJS) -li2c

test:	test.o
	gcc -o test test.c

clean:
	-rm -f *.o si5351


