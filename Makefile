CFLAGS+= -I/usr/local/include -W -Wall -O2 -std=c99 -g
CFLAGS+= -I/usr/local/include/json-c
LDFLAGS+= -L/usr/local/lib -lnanomsg -lmarkdown 
LDFLAGS+= -ljson-c

#JSON_C_DIR=/path/to/json_c/install
#CFLAGS += -I$(JSON_C_DIR)/include/json-c
#LDFLAGS+= -L$(JSON_C_DIR)/lib -ljson-c

SOURCES=	wiki.c main.c myhtml.c params.c forms.c util.c
HDRS=		wiki.h myhtml.h params.h forms.h util.h
BINS=		wiki.cgi

all: $(BINS)

wiki.cgi: $(SOURCES) $(HDRS)
	$(CC) $(CFLAGS) -o $(.TARGET) \
		${SOURCES} \
		$(LDFLAGS)

# TEST 
must.cgi: must.c params.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o ${.TARGET} must.c params.c

strstrp: ${.TARGET}.c util.c
	$(CC) $(CFLAGS) -o ${.TARGET} ${.TARGET}.c util.c

test_forms: ${.TARGET}.c forms.c forms.h
	$(CC) $(CFLAGS) -o ${.TARGET} ${.TARGET}.c \
		forms.c util.c \
		-L/usr/local/lib -I/usr/local/include \
		-lnanomsg

params_test: ${.TARGET}.c params.c params.h util.h util.c 
	$(CC) $(CFLAGS) -o ${.TARGET} ${.TARGET}.c \
		params.c util.c \
		$(LDFLAGS)

anchortest: test1.c myhtml.c
	$(CC) $(CFLAGS) -o $(.TARGET) \
		util.c test1.c myhtml.c \
		$(LDFLAGS)

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

# CGI WEB SETUP TEST
cgi123: ${.TARGET}.c
	$(CC) -o ${.TARGET}.cgi \
		-L/usr/local/lib -I/usr/local/include \
		${.TARGET}.c \
		-lmarkdown \

indent:
	@echo "indenting all code..."
	./indent-all.sh

deploy: wiki.cgi
	cp wiki.cgi wikieditform.php ../htdocs/
	cp must.cgi ../htdocs/
	cp -r static ../htdocs/

clean:
	rm -f writef nanoclient mdtest params_test
	rm -rf a.out *.BAK *.cgi *.core
	rm -rf must
cleanlogs: 
	rm -rf nlog.txt log.txt

.PHONY: test clean cleanlogs indent deploy

