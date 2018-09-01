CFLAGS=		-W -Wall -O2 -std=c99 -g
SOURCES=	wiki.c main.c myhtml.c params.c forms.c util.c
HDRS=		wiki.h myhtml.h params.h forms.h util.h
BINS=		wiki.cgi nanologger nanoclient
TESTBINS=	test_forms params_test anchortest mdtest.cgi writef

all: $(BINS)

# BIN 
wiki.cgi: $(SOURCES) $(HDRS)
	$(CC) $(CFLAGS) -o $(.TARGET) \
		${SOURCES} \
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

# TEST 
test_forms: ${.TARGET}.c forms.c forms.h
	$(CC) $(CFLAGS) -o ${.TARGET} ${.TARGET}.c \
		forms.c util.c \
		-L/usr/local/lib -I/usr/local/include \
		-lnanomsg

params_test: ${.TARGET}.c params.c params.h util.h util.c 
	$(CC) $(CFLAGS) -o ${.TARGET} ${.TARGET}.c \
		params.c util.c \
		-L/usr/local/lib -I/usr/local/include \
		-lnanomsg

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

# UTIL 
indent:
	@echo "indenting all code..."
	./indent-all.sh

clean:
	rm -f writef myserver nanologger nanoclient mdtest params_test
	rm -rf a.out *.BAK *.cgi *.core
cleanlogs: 
	rm -rf nlog.txt log.txt

.PHONY: test clean cleanlogs indent

