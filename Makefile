# Compiler
CC     = g++
DEBUG  = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

# Sources
SOURCE_DIR        = src
SCANNER_DIR       = $(SOURCE_DIR)/scanner
STATE_MACHINE_DIR = $(SOURCE_DIR)/state-machine
BUFFER_DIR        = $(SOURCE_DIR)/buffer
SYM_TAB_DIR       = $(SOURCE_DIR)/symbol-table

# Target
BUILD_DIR  = build
EXECUTABLE = HsKA-Compiler


all: clean state-machine scanner buffer symbol-table $(BUILD_DIR)/$(EXECUTABLE)
	@echo "Building HsKA-Compiler ..."


state-machine:
	$(MAKE) -C $(STATE_MACHINE_DIR) state-machine


scanner:
	$(MAKE) -C $(SCANNER_DIR)


buffer:
	$(MAKE) -C $(BUFFER_DIR) buffer


symbol-table:
	$(MAKE) -C $(SYM_TAB_DIR)


clean:
	rm -f build/*.*
	rm -f $(SCANNER_DIR)/build/*
	rm -f $(STATE_MACHINE_DIR)/build/*
	rm -f $(BUFFER_DIR)/build/*
	rm -f $(SYM_TAB_DIR)/build/*
