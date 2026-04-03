CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = .

SRC_FILES = $(SRC_DIR)/main.c  $(SRC_DIR)/priority_queue.c

TARGET = ../../bin/queue

all: 
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC_FILES) 

debug:
	$(CC) $(CFLAGS) -g -o $(TARGET) $(SRC_FILES) 
