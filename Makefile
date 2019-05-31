CFLAGS+= -W -Wall -O2 -std=c99 -g -pedantic
CFLAGS+= -I/usr/local/include
CFLAGS+= -Imtemplate
LDFLAGS+= -L/usr/local/lib
LDFLAGS+= -Lmtemplate
LDFLAGS+= -lmarkdown 
LDFLAGS+= -lnanomsg
LDFLAGS+= -ljson-c
LDFLAGS+= -lmtemplate

all: wiki admin menu sample test_forms 

SRCS= wiki.c myhtml.c params.c forms.c util.c tmpl.c breadcrumbs.c sort_mdict.c
HDRS= wiki.h myhtml.h params.h forms.h util.h tmpl.h breadcrumbs.h sort_mdict.h

wiki: main.c $(SRCS) $@.h $(HDRS)
	$(CC) $(CFLAGS) -o $@ main.c ${SRCS} $(LDFLAGS)

menu: $@.c $(SRCS) $(HDRS)
	$(CC) $(CFLAGS) -o $@ $@.c $(SRCS) $(LDFLAGS)

sample: $@.c util.c
	$(CC) $(CFLAGS) -o $@ $@.c $(SRCS) $(LDFLAGS)

long_page: $@.c util.c
	$(CC) $(CFLAGS) -o $@ $@.c tmpl.c myhtml.c util.c $(LDFLAGS)

admin: $@.c util.c myhtml.c breadcrumbs.c
	$(CC) $(CFLAGS) -o $@ $@.c \
		tmpl.c util.c myhtml.c breadcrumbs.c $(LDFLAGS)

# TEST 
test_breadcrumbs: $@.c breadcrumbs.c breadcrumbs.h
	$(CC) $(CFLAGS) -o $@ $@.c breadcrumbs.c $(LDFLAGS)

test_altstyle: $@.c $(SRCS) $(HDRS)
	$(CC) $(CFLAGS) -o $@ $@.c $(SRCS) $(LDFLAGS)

test_util: $@.c util.c
	$(CC) $(CFLAGS) -o $@ $@.c util.c $(LDFLAGS)

test_tmpl: $@.c params.c tmpl.c
	$(CC) $(CFLAGS) -o $@ $@.c params.c tmpl.c $(LDFLAGS)

test_sort_mdict: $@.c $(SRCS) $(HDRS)
	$(CC) $(CFLAGS) -o $@ $@.c $(SRCS) $(LDFLAGS)

#json 
must: $@.c params.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ must.c params.c

strstrp: $@.c util.c
	$(CC) $(CFLAGS) -o $@ $@.c util.c

test_forms: $@.c $(HDRS) $(SRCS)
	$(CC) $(CFLAGS) -o $@ $@.c $(SRCS) $(LDFLAGS)

test_codemirror: $@.c $(HDRS) $(SRCS)
	$(CC) $(CFLAGS) -o $@ $@.c $(SRCS) $(LDFLAGS)

test_params: $@.c params.c params.h util.c
	$(CC) $(CFLAGS) -o $@ $@.c params.c util.c $(LDFLAGS)
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

deploy: all
	cp -f wiki ../htdocs/wiki.cgi
	cp -f menu ../htdocs/menu.cgi
	cp -f admin ../htdocs/admin.cgi
	cp -f wikieditform.php ../htdocs/
	cp -f sample ../htdocs/sample.cgi
	cp -f test_forms ../htdocs/test_forms.cgi
	cp -f test_codemirror ../htdocs/test_codemirror.cgi 2>/dev/null || :
	cp -f test_altstyle ../htdocs/test_altstyle.cgi 2>/dev/null || :
	cp -f long_page ../htdocs/long_page.cgi 2>/dev/null || :
	cp -rf static ../htdocs/
	cp -rf templates ../htdocs/

clean:
	rm -f wiki
	rm -f menu
	rm -f admin
	rm -f writef nanoclient mdtest params_test test_params
	rm -f a.out *.BAK *.core
	rm -f tmpl must fix_perms
	rm -f test_tmpl
	rm -f test_forms test_codemirror  
	rm -f sample long_page test_altstyle
	rm -f test_breadcrumbs test_errno test_sort test_strings test_util
	rm -f test_sort_mdict

.PHONY: test clean indent deploy all

