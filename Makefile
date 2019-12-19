WWWROOT=	/var/www/htdocs/wiki

CFLAGS+= -W -Wall -O2 -std=c99 -g -pedantic
CFLAGS+= -I/usr/local/include
CFLAGS+= -Imtemplate
LDFLAGS+= -L/usr/local/lib
LDFLAGS+= -Lmtemplate
LDFLAGS+= -lmarkdown 
LDFLAGS+= -lnanomsg
LDFLAGS+= -ljson-c
LDFLAGS+= -lmtemplate

all: wiki admin menu sample options

SRCS= wiki.c myhtml.c params.c util.c tmpl.c breadcrumbs.c wiki_file_io.c
HDRS= wiki.h myhtml.h params.h util.h tmpl.h breadcrumbs.h wiki_file_io.h

wiki: main.c $(SRCS) $@.h $(HDRS)
	$(CC) $(CFLAGS) -o $@ main.c ${SRCS} $(LDFLAGS)

options: $@.c $(SRCS) $(HDRS)
	$(CC) $(CFLAGS) -o $@ $@.c ${SRCS} $(LDFLAGS)

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

zztest_sort_mdict: $@.c $(SRCS) $(HDRS)
	$(CC) $(CFLAGS) -o $@ $@.c $(SRCS) $(LDFLAGS)

zztest_wiki_file_io:  $@.c $(SRCS) $(HDRS) 
	$(CC) $(CFLAGS) -o $@ $@.c $(SRCS) $(LDFLAGS)

strstrp: $@.c util.c
	$(CC) $(CFLAGS) -o $@ $@.c util.c

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

test: test_codemirror 
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

indent:
	@echo "indenting all code..."
	./indent-all.sh

deploy: all
	cp -f wiki ${WWWROOT}/wiki.cgi
	cp -f options ${WWWROOT}/options.cgi
	cp -f menu ${WWWROOT}/menu.cgi
	cp -f admin ${WWWROOT}/admin.cgi
	cp -f sample ${WWWROOT}/sample.cgi
	cp -f test_codemirror ${WWWROOT}/test_codemirror.cgi 2>/dev/null || :
	cp -f test_altstyle ${WWWROOT}/test_altstyle.cgi 2>/dev/null || :
	cp -f long_page ${WWWROOT}/long_page.cgi 2>/dev/null || :

	#cp -rf static ${WWWROOT}/
	cp -rf static/edit.js ${WWWROOT}/static/
	cp -rf static/style.css ${WWWROOT}/static/
	cp -rf static/normalize.css ${WWWROOT}/static/

	cp -rf templates ${WWWROOT}/

clean:
	rm -f wiki
	rm -f options
	rm -f menu
	rm -f admin
	rm -f writef nanoclient mdtest params_test test_params
	rm -f a.out *.BAK *.core
	rm -f tmpl fix_perms
	rm -f test_tmpl
	rm -f test_codemirror  
	rm -f sample long_page test_altstyle
	rm -f test_breadcrumbs test_errno test_sort test_strings test_util
	rm -f zztest_sort_mdict
	rm -f zztest_wiki_file_io
	rm -f test_time

.PHONY: test clean indent deploy all

