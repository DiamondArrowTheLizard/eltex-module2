CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = .

SRC_FILES = $(SRC_DIR)/main.c $(SRC_DIR)/print.c $(SRC_DIR)/convert.c $(SRC_DIR)/validate.c 

TARGET = ../../bin/mask_calculator

all: 
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC_FILES) 

debug:
	$(CC) $(CFLAGS) -g -o $(TARGET) $(SRC_FILES) 
