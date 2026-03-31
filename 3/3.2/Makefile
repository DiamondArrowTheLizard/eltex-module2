CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = .

SRC_FILES = $(SRC_DIR)/main.c  $(SRC_DIR)/packet.c

TARGET = ../../bin/packet_sender

all: 
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC_FILES) 

debug:
	$(CC) $(CFLAGS) -g -o $(TARGET) $(SRC_FILES) 
