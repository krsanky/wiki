CFLAGS=	-W -Wall
TARGET=	wiki
PROG=	wiki

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET).cgi $(TARGET).c

#$(CC) $(CFLAGS) -I. -c main.c

test:
	@echo CURDIR:${.CURDIR}
	@echo TARGET:${.TARGET} [should be 'test']

mdtest: mdtest.c
	#$(CC) -o mdtest.cgi -lmarkdown -I/usr/local/include mdtest.c
	$(CC) -o mdtest.cgi -I/usr/local/include mdtest.c

clean:
	rm -f $(TARGET).cgi

.PHONY: all

#.include <bsd.subdir.mk>
