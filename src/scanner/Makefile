# Compiler
CC     = g++
DEBUG  = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

# Sources
HEADER_DIR = headers
SOURCE_DIR = src
DEBUG_DIR  = debug

# Dependecies
BUFFER_DIR        = ../buffer
SYMBOL_TABLE_DIR  = ../symbol-table
STATE_MACHINE_DIR = ../state-machine

# Target
BUILD_DIR  = build

# List of targets
TARGETS = $(BUILD_DIR)/Scanner.o \
	# add more here
	# last without escape sequence

EXECUTABLE = Scanner


# Builds targets
scanner: clean $(TARGETS)

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp $(HEADER_DIR)/%.h
	@echo $(CC) " $*.cpp"
	$(CC) $(CFLAGS) $< -o $@


# Builds Scanner_Test executable
scanner-executable: clean scanner $(HEADER_DIR)/Scanner.h $(SOURCE_DIR)/Scanner_Test.cpp
	@echo 'Building Scanner Test Executable ...'
	$(CC) $(CFLAGS) $(SOURCE_DIR)/Scanner_Test.cpp -o $(DEBUG_DIR)/$(EXECUTABLE)_Test.o
	$(CC) $(LFLAGS) $(DEBUG_DIR)/Scanner_Test.o $(BUILD_DIR)/*.o $(STATE_MACHINE_DIR)/$(BUILD_DIR)/*.o $(BUFFER_DIR)/$(BUILD_DIR)/*.o $(SYMBOL_TABLE_DIR)/$(BUILD_DIR)/*.o -o $(DEBUG_DIR)/$(EXECUTABLE)_Test


# Cleaning up debug/ and build/ directory
clean:
	@echo 'Cleaning up scanner directory ...'
	rm -f build/*
	rm -f debug/*
