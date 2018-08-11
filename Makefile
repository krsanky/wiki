CFLAGS=	-W -Wall -O2 -std=c99 -g

all: wiki.cgi nanologger nanoclient

wiki.cgi: wiki.c main.c myhtml.c params.c
	$(CC) $(CFLAGS) -o $(.TARGET) \
		util.c main.c params.c myhtml.c wiki.c \
		-L/usr/local/lib -I/usr/local/include \
		-lnanomsg -lmarkdown 

nanologger: ${.TARGET}.c
	$(CC) $(CFLAGS) -o ${.TARGET} \
		${.TARGET}.c \
		myhtml.c util.c \
		-L/usr/local/lib -I/usr/local/include \
		-lnanomsg -lmarkdown 

nanoclient: ${.TARGET}.c
	$(CC) $(CFLAGS) -o ${.TARGET} \
		${.TARGET}.c \
		util.c \
		-L/usr/local/lib -I/usr/local/include \
		-lnanomsg

params_test: ${.TARGET}.c
	$(CC) $(CFLAGS) -o ${.TARGET} ${.TARGET}.c \
		params.c \
		-L/usr/local/lib -I/usr/local/include 

anchortest: test1.c myhtml.c
	$(CC) $(CFLAGS) -o $(.TARGET) \
		util.c test1.c myhtml.c \
		-L/usr/local/lib -I/usr/local/include \
		-lnanomsg -lmarkdown 

test:
	@echo CURDIR:${.CURDIR}
	@echo TARGET:${.TARGET} [should be 'test']

mdtest: ${.TARGET}.c
	$(CC) -o ${.TARGET}.cgi \
		-L/usr/local/lib -I/usr/local/include \
		${.TARGET}.c \
		-lmarkdown 

writef: ${.TARGET}.c
	$(CC) -o ${.TARGET} \
		-L/usr/local/lib -I/usr/local/include \
		${.TARGET}.c \
		-lmarkdown \

indent:
	@echo "indenting all code..."
	./indent-all.sh

clean:
	rm -f writef myserver nanologger nanoclient mdtest params_test
	rm -rf a.out *.BAK *.cgi
cleanlogs: 
	rm -rf nlog.txt log.txt

.PHONY: test clean cleanlogs indent

