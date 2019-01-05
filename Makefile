CFLAGS+= -W -Wall -O2 -std=c99 -g
CFLAGS+= -I/usr/local/include
CFLAGS+= -Imtemplate
LDFLAGS+= -L/usr/local/lib
LDFLAGS+= -Lmtemplate
LDFLAGS+= -lnanomsg -lmarkdown 
LDFLAGS+= -ljson-c
LDFLAGS+= -lmtemplate

#JSON_C_DIR=/path/to/json_c/install
#CFLAGS += -I$(JSON_C_DIR)/include/json-c
#LDFLAGS+= -L$(JSON_C_DIR)/lib -ljson-c

SRCS=	wiki.c main.c myhtml.c params.c forms.c util.c
HDRS=		wiki.h myhtml.h params.h forms.h util.h
BINS=		wiki.cgi

all: $(BINS)

wiki.cgi: $(SRCS) $(HDRS)
	$(CC) $(CFLAGS) -o $(.TARGET) \
		${SRCS} \
		$(LDFLAGS)

# TEST 
tmpl: $@.c mtemplate/libmtemplate.a
	$(CC) $(CFLAGS) -o $@.cgi $@.c $(LDFLAGS)

must.cgi: must.c params.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ must.c params.c \
		mustach-json-c.c mustach.c

strstrp: $@.c util.c
	$(CC) $(CFLAGS) -o $@ $@.c util.c

test_forms: $@.c forms.c forms.h
	$(CC) $(CFLAGS) -o $@ $@.c \
		forms.c util.c \
		-L/usr/local/lib -I/usr/local/include \
		-lnanomsg

params_test: $@.c params.c params.h util.h util.c 
	$(CC) $(CFLAGS) -o $@ $@.c \
		params.c util.c \
		$(LDFLAGS)

anchortest: test1.c myhtml.c
	$(CC) $(CFLAGS) -o $(.TARGET) \
		util.c test1.c myhtml.c \
		$(LDFLAGS)

test:
	@echo CURDIR:${.CURDIR}
	@echo TARGET:$@ [should be 'test']
	@echo CFLAGS: $(CFLAGS)
	@echo LDFLAGS: ${LDFLAGS}

mdtest: $@.c
	$(CC) -o $@.cgi \
		-L/usr/local/lib -I/usr/local/include \
		$@.c \
		-lmarkdown 

writef: $@.c
	$(CC) -o $@ \
		-L/usr/local/lib -I/usr/local/include \
		$@.c \
		-lmarkdown \

# CGI WEB SETUP TEST
cgi123: $@.c
	$(CC) -o $@.cgi \
		-L/usr/local/lib -I/usr/local/include \
		$@.c \
		-lmarkdown \

indent:
	@echo "indenting all code..."
	./indent-all.sh

deploy: wiki.cgi
	cp wiki.cgi wikieditform.php ../htdocs/
	cp must.cgi ../htdocs/
	cp -r static ../htdocs/

clean:
	rm -rf *.cgi
	rm -f writef nanoclient mdtest params_test
	rm -rf a.out *.BAK *.core

.PHONY: test clean indent deploy

