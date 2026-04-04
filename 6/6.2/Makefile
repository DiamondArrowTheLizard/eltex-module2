CC = gcc
CFLAGS = -Wall -Wextra -Werror

PWD := $(shell pwd)

RPATH = -Wl,-rpath,$(PWD)

LIB_DIR = .

LIB_FILES = $(LIB_DIR)/contacts_list.c $(LIB_DIR)/personal_info.c $(LIB_DIR)/string_array.c

LIB_COMP = contacts_list.o personal_info.o string_array.o
LIB_NAME = libcontacts.so

SRC_DIR = $(PWD)

SRC_FILES = $(SRC_DIR)/main.c $(SRC_DIR)/ui.c 

TARGET = ../../bin/contact_book
LIB_TARGET = $(LIB_DIR)/$(LIB_NAME)

all: 
	$(CC) $(CFLAGS) -L. $(RPATH) $(LIB_NAME) $(SRC_FILES) -o $(TARGET)

debug:
	$(CC) $(CFLAGS) -g -L. $(RPATH) $(LIB_NAME) $(SRC_FILES) -o $(TARGET)

libcontacts:
	$(CC) $(CFLAGS) -c -fPIC $(SRC_DIR)/contacts_list.c -o $(SRC_DIR)/contacts_list.o
	$(CC) $(CFLAGS) -c -fPIC $(SRC_DIR)/personal_info.c -o $(SRC_DIR)/personal_info.o
	$(CC) $(CFLAGS) -c -fPIC $(SRC_DIR)/string_array.c -o $(SRC_DIR)/string_array.o

	$(CC) $(CFLAGS) -shared $(LIB_COMP) -o $(LIB_TARGET)
	rm -f $(LIB_COMP)

