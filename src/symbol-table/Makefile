# Compiler
CC     = g++
DEBUG  = -g
CFLAGS = -Wall -c $(DEBUG) -std=c++1z -O3
LFLAGS = -Wall $(DEBUG) -std=c++1z -O3

# Sources
HEADER_DIR = include
SOURCE_DIR = src
DEBUG_DIR  = debug

# Target
BUILD_DIR  = bin

# List of targets
TARGETS = $(BUILD_DIR)/SymbolTable.o \
	$(BUILD_DIR)/Information.o \
	$(BUILD_DIR)/StringTab.o \
	$(BUILD_DIR)/StringTabNode.o \
	$(BUILD_DIR)/SymbolTableEntry.o
	# add more here
	# last without escape sequence

EXECUTABLE = symbol-table


# Builds the targets
symb-table: clean $(TARGETS)

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
	$(CC) $(LFLAGS) $(TARGETS) $(DEBUG_DIR)/$(EXECUTABLE)_Test.o -o $(DEBUG_DIR)/$(EXECUTABLE)_Test


# Cleaning up debug/ and build/ directory
clean:
	@echo 'Cleaning up symbol-table directory ...'
	rm -rf $(BUILD_DIR) && mkdir $(BUILD_DIR)
	rm -rf $(DEBUG_DIR) && mkdir $(DEBUG_DIR)
