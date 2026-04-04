CC = gcc
CFLAGS = -Wall -Wextra -Werror

LIB_DIR = .

LIB_FILES = $(LIB_DIR)/contacts_list.c $(LIB_DIR)/personal_info.c $(LIB_DIR)/string_array.c

LIB_COMP = contacts_list.o personal_info.o string_array.o
LIB_NAME = libcontacts.a
LIB_FLAG = lcontacts

SRC_DIR = .

SRC_FILES = $(SRC_DIR)/main.c $(SRC_DIR)/ui.c 

TARGET = ../../bin/contact_book

all: 
	$(CC) $(CFLAGS) $(SRC_FILES) -L. -$(LIB_FLAG) -o $(TARGET)

debug:
	$(CC) $(CFLAGS) -g $(SRC_FILES) -L. -$(LIB_FLAG) -o $(TARGET)

libcontacts:
	$(CC) $(CFLAGS) -c $(LIB_DIR)/contacts_list.c -o $(LIB_DIR)/contacts_list.o
	$(CC) $(CFLAGS) -c $(LIB_DIR)/personal_info.c -o $(LIB_DIR)/personal_info.o
	$(CC) $(CFLAGS) -c $(LIB_DIR)/string_array.c -o $(LIB_DIR)/string_array.o
	ar rcs $(LIB_NAME) $(LIB_COMP)
	rm -rf $(LIB_COMP)
