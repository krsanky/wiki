CFLAGS=	-W -Wall -O2

all: wiki.cgi nanologger nanoclient

wiki.cgi: wiki.c main.c myhtml.c yuarel.c
	$(CC) $(CFLAGS) -o $(.TARGET) \
		main.c yuarel.c myhtml.c wiki.c \
		-L/usr/local/lib -I/usr/local/include \
		-lnanomsg

nanologger: ${.TARGET}.c
	$(CC) $(CFLAGS) -o ${.TARGET} \
		${.TARGET}.c \
		wiki.c myhtml.c \
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
		-lmarkdown 

writef: ${.TARGET}.c
	$(CC) -o ${.TARGET} \
		-L/usr/local/lib -I/usr/local/include \
		${.TARGET}.c \
		-lmarkdown \

indent:
	@echo "implement indenting of all c code..."

clean:
	rm -f *.cgi *.BAK writef myserver nanologger nanoclient mdtest
cleanlogs: 
	rm -rf nlog.txt log.txt

.PHONY: test clean cleanlogs indent

