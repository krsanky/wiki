CFLAGS=	-W -Wall

all: wiki.cgi

wiki.cgi: wiki.c
	$(CC) $(CFLAGS) -o $(.TARGET) \
		 main.c yuarel.c myhtml.c wiki.c

#$(CC) $(CFLAGS) -I. -c main.c

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

myserver: ${.TARGET}.c
	$(CC) $(CFLAGS) -o ${.TARGET} ${.TARGET}.c

clean:
	rm -f *.cgi writef myserver

.PHONY: all wiki test

