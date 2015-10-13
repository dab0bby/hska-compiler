# Compiler
CC = g++
DEBUG = -g
CFLAGS = -c -Wall $(DEBUG)
LFLAGS = -Wall $(DEBUG)

# Sources
SOURCE_DIR = src
SCANNER_DIR = $(SOURCE_DIR)/scanner
STATE_MACHINE_DIR = $(SOURCE_DIR)/state-machine
BUFFER_DIR = $(SOURCE_DIR)/buffer
SYM_TAB_DIR = $(SOURCE_DIR)/symbol-table

# Target name
EXECUTABLE = hska-compiler


all: state-machine scanner buffer symbol-table $(EXECUTABLE)
		@echo "Building HsKA-Compiler ..."


#		$(CC) $(LFLAGS) $(OBJECTS) -o $(EXECUTABLE)

state-machine:

scanner:

buffer:

symbol-table:


clean:
	rm -f *.o
