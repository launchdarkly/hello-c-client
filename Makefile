C_CLIENT_PATH = c-client-sdk
C_CLIENT_REPO = https://github.com/launchdarkly/c-client-sdk
CC = gcc -std=c99
CFLAGS = -g -Wall -I$(C_CLIENT_PATH)
LFLAGS = $(C_CLIENT_PATH)/libldclientapi.a -lcurl -lpthread -lm

UNAME := $(shell uname)

ifeq ($(UNAME),Darwin)
	LFLAGS += -framework CoreFoundation -framework IOKit
endif

TARGET = hello

all: $(TARGET)

clean:
	rm $(TARGET)

$(TARGET): $(TARGET).c c-client-sdk
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c $(LFLAGS)

c-client-sdk:
	git clone $(C_CLIENT_REPO) $(C_CLIENT_PATH)
	cd c-client-sdk && make
