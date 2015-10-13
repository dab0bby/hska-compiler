# Compiler
CC     = g++
DEBUG  = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

# Sources
HEADER_DIR        = headers
SOURCE_DIR        = src
DEBUG_DIR         = debug
SCANNER_DIR       = $(SOURCE_DIR)/scanner
STATE_MACHINE_DIR = $(SOURCE_DIR)/state-machine
BUFFER_DIR        = $(SOURCE_DIR)/buffer
SYM_TAB_DIR       = $(SOURCE_DIR)/symbol-table

# Target
BUILD_DIR  = build
EXECUTABLE = HsKA-Scanner


all: clean state-machine buffer symbol-table scanner scanner-build


state-machine:
	$(MAKE) -C $(STATE_MACHINE_DIR) state-machine


scanner:
	$(MAKE) -C $(SCANNER_DIR) scanner


buffer:
	$(MAKE) -C $(BUFFER_DIR) buffer


symbol-table:
	$(MAKE) -C $(SYM_TAB_DIR) symb-table


# Builds complete Scanner into 'build/'
scanner-build: $(SOURCE_DIR)/main.cpp
	@echo 'Building Scanner Executable ...'
	$(CC) $(CFLAGS) $(SOURCE_DIR)/main.cpp -o $(BUILD_DIR)/$(EXECUTABLE).o
	$(CC) $(LFLAGS) $(BUILD_DIR)/$(EXECUTABLE).o $(SCANNER_DIR)/$(BUILD_DIR)/*.o $(STATE_MACHINE_DIR)/$(BUILD_DIR)/*.o $(BUFFER_DIR)/$(BUILD_DIR)/*.o $(SYM_TAB_DIR)/$(BUILD_DIR)/*.o -o $(BUILD_DIR)/$(EXECUTABLE)


clean:
	rm -f build/*
	rm -f $(SCANNER_DIR)/build/*
	rm -f $(STATE_MACHINE_DIR)/build/*
	rm -f $(BUFFER_DIR)/build/*
	rm -f $(SYM_TAB_DIR)/build/*
	rm -f $(SCANNER_DIR)/debug/*
	rm -f $(STATE_MACHINE_DIR)/debug/*
	rm -f $(BUFFER_DIR)/debug/*
	rm -f $(SYM_TAB_DIR)/debug/*
