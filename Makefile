CC     = gcc
CFLAGS = -Wall -Wextra -pedantic 

all: cgiargs

cgiargs:
	cp cgiargs.h cgiargs-temp.c
	$(CC) $(CFLAGS) cgiargs-temp.c -c -o cgiargs.o # cc makes a precompiled header file instead of an executable object if you replace .c with .h
	rm cgiargs-temp.c
	ar rcs libcgiargs.a cgiargs.o
	rm cgiargs.o
	$(CC) $(CFLAGS) -L. -lcgiargs tests/test.c -o tests/test.exe

test:
	QUERY_STRING="d1=&d2=lulz&d3=&vendor=apple&product=macos&orderby=&da=desc&sg=&eg=&j1=" \
	./tests/test.exe

install:
	sudo cp libcgiargs.a /usr/lib/a/
	sudo cp cgiargs.h /usr/include/a/
	sudo cp .stb_ds_cgiargs.h /usr/include/a/

clean:
	rm ./tests/test.exe
