# Compiler
CC     = g++
DEBUG  = -g
CFLAGS = -Wall -c -std=c++11 -Wwrite-strings $(DEBUG)
LFLAGS = -Wall $(DEBUG)

# Sources
HEADER_DIR = headers
SOURCE_DIR = src
DEBUG_DIR  = debug

# Target
BUILD_DIR  = build

# List of targets
TARGETS = $(BUILD_DIR)/SymbolTable.o \
	  $(BUILD_DIR)/Information.o \
	  $(BUILD_DIR)/StringTab.o \
	  $(BUILD_DIR)/StringTabEntry.o \
	  $(BUILD_DIR)/SymbolTableEntry.o
	# add more here
	# last without escape sequence

EXECUTABLE = SymbolTable


# Builds the targets
symb-table: $(TARGETS)

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp $(HEADER_DIR)/%.h
	@echo $(CC) " $*.cpp"
	$(CC) $(CFLAGS) $< -o $@


# Builds the test target
symb-table-test: $(HEADER_DIR)/SymbolTable.h $(SOURCE_DIR)/SymbolTable_Test.cpp
	@echo 'Building SymbolTable Test ...'
	$(CC) $(CFLAGS) $(SOURCE_DIR)/SymbolTable_Test.cpp -o $(DEBUG_DIR)/$(EXECUTABLE)_Test.o


# Builds targets with test executable
symb-table-test-executable: clean symb-table symb-table-test
	@echo 'Building SymbolTable Test Executable ...'
	$(CC) $(LFLAGS) $(BUILD_DIR)/SymbolTable.o $(DEBUG_DIR)/SymbolTable_Test.o -o $(DEBUG_DIR)/$(EXECUTABLE)_Test


# Cleaning up debug/ and build/ directory
clean:
	@echo 'Cleaning up symbol-table directory ...'
	rm -f build/*
	rm -f debug/*
