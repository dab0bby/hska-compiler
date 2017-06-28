# Compiler
CC     = g++
DEBUG  = -g
CFLAGS = -Wall -c $(DEBUG) -std=c++1z -O3
LFLAGS = -Wall $(DEBUG) -std=c++1z -O3

# Sources
HEADER_DIR        = include
SOURCE_DIR        = src
SCANNER_DIR       = $(SOURCE_DIR)/scanner
STATE_MACHINE_DIR = $(SOURCE_DIR)/state-machine
BUFFER_DIR        = $(SOURCE_DIR)/buffer
SYM_TAB_DIR       = $(SOURCE_DIR)/symbol-table
PARSER_DIR        = $(SOURCE_DIR)/parser

# Target
BUILD_DIR  = bin
EXECUTABLE = HsKA-Compiler


all: clean buffer state-machine symbol-table scanner scanner-build


state-machine:
	$(MAKE) -C $(STATE_MACHINE_DIR)


scanner:
	$(MAKE) -C $(SCANNER_DIR)


buffer:
	$(MAKE) -C $(BUFFER_DIR)


symbol-table:
	$(MAKE) -C $(SYM_TAB_DIR)


parser:
	$(MAKE) -C $(PARSER_DIR)


# Builds complete Scanner into 'build/'
scanner-build: $(SOURCE_DIR)/main.cpp
	@echo 'Building Scanner Executable ...'
	$(CC) $(CFLAGS) $(SOURCE_DIR)/main.cpp -o $(BUILD_DIR)/$(EXECUTABLE).o
	$(CC) $(LFLAGS) $(BUILD_DIR)/$(EXECUTABLE).o \
		$(SCANNER_DIR)/$(BUILD_DIR)/*.o \
		$(STATE_MACHINE_DIR)/$(BUILD_DIR)/*.o \
		$(BUFFER_DIR)/$(BUILD_DIR)/*.o \
		$(SYM_TAB_DIR)/$(BUILD_DIR)/*.o \
		$(PARSER_DIR)/$(BUILD_DIR)/*.o \
		-o $(BUILD_DIR)/$(EXECUTABLE)


clean:
	rm -rf $(BUILD_DIR) && mkdir $(BUILD_DIR)
