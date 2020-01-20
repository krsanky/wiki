#WWWROOT=	/var/www/htdocs/wiki
WWWROOT=	/var/www/vhost/wiki.oldcode.org/htdocs

CFLAGS+= -W -Wall -O2 -std=c99 -g -pedantic
CFLAGS+= -Iinclude
CFLAGS+= -I/usr/local/include
CFLAGS+= -Imtemplate
LDFLAGS+= -L/usr/local/lib
LDFLAGS+= -Lmtemplate
LDFLAGS+= -lmarkdown 
LDFLAGS+= -lnanomsg
LDFLAGS+= -ljson-c
LDFLAGS+= -lmtemplate

CGIS=	wiki admin menu sample options

all: ${CGIS}

SRCS= wiki.c myhtml.c params.c util.c tmpl.c breadcrumbs.c wiki_file_io.c
HDRS= wiki.h myhtml.h params.h util.h tmpl.h breadcrumbs.h wiki_file_io.h settings.h

wiki: src/main.c ${SRCS:C/.*/src\/&/} ${HDRS:C/.*/include\/&/}
	$(CC) $(CFLAGS) -o $@ src/main.c ${SRCS:C/.*/src\/&/} $(LDFLAGS)

options: src/${@}.c ${SRCS:C/.*/src\/&/} ${HDRS:C/.*/include\/&/}
	$(CC) $(CFLAGS) -o $@ src/${@}.c ${SRCS:C/.*/src\/&/} ${LDFLAGS}

menu: src/${@}.c ${SRCS:C/.*/src\/&/} ${HDRS:C/.*/include\/&/}
	$(CC) $(CFLAGS) -o $@ src/${@}.c ${SRCS:C/.*/src\/&/} ${LDFLAGS}

sample: src/${@}.c ${SRCS:C/.*/src\/&/} ${HDRS:C/.*/include\/&/}
	$(CC) $(CFLAGS) -o $@ src/${@}.c ${SRCS:C/.*/src\/&/} ${LDFLAGS}

long_page: src/${@}.c src/util.c
	$(CC) $(CFLAGS) -o $@ src/${@}.c ${SRCS:C/.*/src\/&/} ${LDFLAGS}

admin: src/${@}.c src/util.c src/myhtml.c src/breadcrumbs.c
	$(CC) $(CFLAGS) -o $@ src/${@}.c ${SRCS:C/.*/src\/&/} ${LDFLAGS}

# TEST 
test_breadcrumbs: test/${@}.c ${SRCS:C/.*/src\/&/} ${HDRS:C/.*/include\/&/}
	$(CC) $(CFLAGS) -o $@ test/${@}.c ${SRCS:C/.*/src\/&/} ${LDFLAGS}

test_util: test/${@}.c src/util.c
	$(CC) $(CFLAGS) -o ${@} test/${@}.c src/util.c $(LDFLAGS)

# BROKEN
test_tmpl: test/${@}.c ${SRCS:C/.*/src\/&/} ${HDRS:C/.*/include\/&/}
	$(CC) $(CFLAGS) -o $@ test/${@}.c ${SRCS:C/.*/src\/&/} ${LDFLAGS}

zztest_sort_mdict: test/${@}.c src/sort_mdict.c include/sort_mdict.h
	$(CC) $(CFLAGS) -o $@ test/${@}.c src/sort_mdict.c ${LDFLAGS}

zztest_wiki_file_io: test/$@.c ${SRCS:C/.*/src\/&/} ${HDRS:C/.*/include\/&/} 
	$(CC) $(CFLAGS) -o $@ test/${@}.c ${SRCS:C/.*/src\/&/} ${LDFLAGS}

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
	for f in ${CGIS} ; echo $f ; done  

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
	cp -f long_page ${WWWROOT}/long_page.cgi 2>/dev/null || :

	#cp -rf static ${WWWROOT}/
	cp -rf static/edit.js ${WWWROOT}/static/
	cp -rf static/style.css ${WWWROOT}/static/
	cp -rf static/normalize.css ${WWWROOT}/static/
	cp -rf static/form.css ${WWWROOT}/static/

	cp resrc/index.html ${WWWROOT}/
	cp resrc/favicon.ico ${WWWROOT}/

	cp -rf templates ${WWWROOT}/

clean:
	rm -f ${CGIS}
	rm -f a.out *.BAK *.core

.PHONY: test clean indent deploy all

