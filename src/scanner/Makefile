# Compiler
CC     = g++
DEBUG  = -g
CFLAGS = -Wall -c $(DEBUG) -std=c++11 -O3
LFLAGS = -Wall $(DEBUG) -std=c++11 -O3

# Sources
HEADER_DIR = include
SOURCE_DIR = src
DEBUG_DIR  = debug

# Dependecies
BUFFER_DIR        = ../buffer
SYMBOL_TABLE_DIR  = ../symbol-table
STATE_MACHINE_DIR = ../state-machine

# Target
BUILD_DIR  = bin
EXECUTABLE = scanner

# List of targets
TARGETS = $(BUILD_DIR)/Scanner.o \
	$(BUILD_DIR)/Token.o
	# add more here
	# last without escape sequence


# Builds targets
scanner: clean $(TARGETS)

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp $(HEADER_DIR)/%.h
	@echo $(CC) " $*.cpp"
	$(CC) $(CFLAGS) $< -o $@


# Builds the test target
scanner-test: $(SOURCE_DIR)/Scanner_Test.cpp
	@echo 'Building scanner test target ...'
	$(CC) $(CFLAGS) $(SOURCE_DIR)/Scanner_Test.cpp -o $(DEBUG_DIR)/$(EXECUTABLE)_Test.o


# Builds targets with test executable
scanner-test-executable: clean scanner scanner-test
	@echo 'Building scanner test target ...'
	$(MAKE) -C $(BUFFER_DIR)
	$(MAKE) -C $(SYMBOL_TABLE_DIR)
	$(MAKE) -C $(STATE_MACHINE_DIR)
	$(CC) $(LFLAGS) $(TARGETS) \
		$(DEBUG_DIR)/$(EXECUTABLE)_Test.o \
		$(BUFFER_DIR)/$(BUILD_DIR)/*.o \
		$(SYMBOL_TABLE_DIR)/$(BUILD_DIR)/*.o \
		$(STATE_MACHINE_DIR)/$(BUILD_DIR)/*.o \
		-o $(DEBUG_DIR)/$(EXECUTABLE)_test


# Cleaning up debug/ and bin/ directory
clean:
	@echo 'Cleaning up scanner ...'
	rm -rf $(BUILD_DIR) && mkdir $(BUILD_DIR)
	rm -rf $(DEBUG_DIR) && mkdir $(DEBUG_DIR)
