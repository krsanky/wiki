CFLAGS+= -W -Wall -O2 -std=c99 -g
CFLAGS+= -I/usr/local/include
CFLAGS+= -Imtemplate
LDFLAGS+= -L/usr/local/lib
LDFLAGS+= -Lmtemplate
LDFLAGS+= -lnanomsg -lmarkdown 
LDFLAGS+= -ljson-c
LDFLAGS+= -lmtemplate

SRCS= wiki.c main.c myhtml.c params.c forms.c util.c
HDRS= wiki.h myhtml.h params.h forms.h util.h

all: wiki

wiki: $(SRCS) $(HDRS)
	$(CC) $(CFLAGS) -o $@ ${SRCS} $(LDFLAGS)

# TEST 
tmpl: $@.c mtemplate/libmtemplate.a params.c
	$(CC) $(CFLAGS) -o $@ $@.c params.c $(LDFLAGS)

#json 
must: $@.c params.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ must.c params.c

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

cgi123: $@.c
	$(CC) -o $@.cgi \
		-L/usr/local/lib -I/usr/local/include \
		$@.c \
		-lmarkdown \

indent:
	@echo "indenting all code..."
	./indent-all.sh

deploy: wiki must tmpl
	cp wiki ../htdocs/wiki.cgi
	cp wikieditform.php ../htdocs/
	cp must ../htdocs/must.cgi
	cp tmpl ../htdocs/tmpl.cgi
	cp -r static ../htdocs/
	cp -r templates ../htdocs/

clean:
	rm -rf *.cgi
	rm -f writef nanoclient mdtest params_test
	rm -rf a.out *.BAK *.core
	rm -rf tmpl

.PHONY: test clean indent deploy

