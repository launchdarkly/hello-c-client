C_CLIENT_PATH = c-client
C_CLIENT_REPO = https://github.com/launchdarkly/c-client
CC = gcc -std=c99
CFLAGS = -g -Wall -I$(C_CLIENT_PATH)
LFLAGS = $(C_CLIENT_PATH)/libldclientapi.a -lcurl -lpthread -lm

TARGET = hello

all: $(TARGET)

clean:
	rm $(TARGET)

$(TARGET): $(TARGET).c c-client
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c $(LFLAGS)

c-client:
	git clone $(C_CLIENT_REPO) $(C_CLIENT_PATH)
	cd c-client && make
