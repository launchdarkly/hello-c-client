C_CLIENT=../c-client-private

CC=gcc -std=c99
CFLAGS=-g -Wall -I$(C_CLIENT)
LFLAGS=$(C_CLIENT)/libldapi.a -lcurl -lpthread -lm

TARGET = hello

all: $(TARGET)

clean:
	rm $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c $(LFLAGS)
