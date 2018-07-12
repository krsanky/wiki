TARGET=	wiki

$(TARGET): $(TARGET).c
	$(CC) -o $(TARGET).cgi $(TARGET).c

test:
	@echo test echo echo 

clean:
	rm -f $(TARGET).cgi

