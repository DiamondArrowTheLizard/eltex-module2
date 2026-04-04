
CC = gcc
CFLAGS = -Wall -Wextra -Werror

PWD := $(shell pwd)

RPATH = -Wl,-rpath,$(PWD)

LIB_DIR = $(PWD)

SRC_DIR = $(PWD)

SRC_FILES = $(SRC_DIR)/main.c 

TARGET = ../../bin/calculator3

all: 
	$(CC) $(CFLAGS) -ldl -o $(TARGET) $(SRC_FILES) 

debug:
	$(CC) $(CFLAGS) -ldl -g -o $(TARGET) $(SRC_FILES) 

libs:
	$(CC) $(CFLAGS) -c -fPIC $(SRC_DIR)/add.c -o $(SRC_DIR)/add.o
	$(CC) $(CFLAGS) -shared add.o -o $(LIB_DIR)/add.so
	rm -f add.o

	$(CC) $(CFLAGS) -c -fPIC $(SRC_DIR)/subtract.c -o $(SRC_DIR)/subtract.o
	$(CC) $(CFLAGS) -shared subtract.o -o $(LIB_DIR)/subtract.so
	rm -f subtract.o

	$(CC) $(CFLAGS) -c -fPIC $(SRC_DIR)/multiply.c -o $(SRC_DIR)/multiply.o
	$(CC) $(CFLAGS) -shared multiply.o -o $(LIB_DIR)/multiply.so
	rm -f multiply.o

	$(CC) $(CFLAGS) -c -fPIC $(SRC_DIR)/divide.c -o $(SRC_DIR)/divide.o
	$(CC) $(CFLAGS) -shared divide.o -o $(LIB_DIR)/divide.so
	rm -f divide.o

