CFLAGS=	-W -Wall

all: wiki.cgi nanologger nanoclient

wiki.cgi: wiki.c main.c myhtml.c yuarel.c
	$(CC) $(CFLAGS) -o $(.TARGET) \
		main.c yuarel.c myhtml.c wiki.c 

nanologger: ${.TARGET}.c
	$(CC) $(CFLAGS) -o ${.TARGET} \
		${.TARGET}.c \
		-L/usr/local/lib -I/usr/local/include \
		-lnanomsg

nanoclient: ${.TARGET}.c
	$(CC) $(CFLAGS) -o ${.TARGET} \
		${.TARGET}.c \
		-L/usr/local/lib -I/usr/local/include \
		-lnanomsg

test:
	@echo CURDIR:${.CURDIR}
	@echo TARGET:${.TARGET} [should be 'test']

mdtest: ${.TARGET}.c
	$(CC) -o ${.TARGET}.cgi \
		-L/usr/local/lib -I/usr/local/include \
		${.TARGET}.c \
		-lmarkdown \

writef: ${.TARGET}.c
	$(CC) -o ${.TARGET} \
		-L/usr/local/lib -I/usr/local/include \
		${.TARGET}.c \
		-lmarkdown \

clean:
	rm -f *.cgi writef myserver nanologger nanoclient mdtest
cleanlogs: 
	rm -rf nlog.txt log.txt

.PHONY: test wiki.cgi clean cleanlogs

