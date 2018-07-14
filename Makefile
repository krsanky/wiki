CFLAGS=	-W -Wall
PROG=	wiki

all: $(PROG)

$(PROG): $(.TARGET).c
	$(CC) $(CFLAGS) -o $(.TARGET).cgi $(.TARGET).c

#$(CC) $(CFLAGS) -I. -c main.c

test:
	@echo CURDIR:${.CURDIR}
	@echo TARGET:${.TARGET} [should be 'test']

#/usr/local/include/mkdio.h
#/usr/local/lib/libmarkdown.a
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
	rm -f *.cgi writef

.PHONY: all

#.include <bsd.subdir.mk>
