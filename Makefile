TARGET=	wiki

$(TARGET): $(TARGET).c
	$(CC) -o $(TARGET) $(TARGET).c

test:
	@echo test echo echo 

clean:
	rm -f $(TARGET)

