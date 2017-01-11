# Compiler
CC     = g++
DEBUG  = -g
CFLAGS = -Wall -c $(DEBUG) -std=c++11 -O3
LFLAGS = -Wall $(DEBUG) -std=c++11 -O3

# Sources
HEADER_DIR = include
SOURCE_DIR = src
DEBUG_DIR  = debug

# Target
BUILD_DIR  = bin

# List of targets
TARGETS = $(BUILD_DIR)/Parser.o \
	# add more here
	# last without escape sequence

EXECUTABLE = parser


# Builds Targets and saves to BUILD_DIR
parser: clean $(TARGETS)

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp $(HEADER_DIR)/%.h
	@echo $(CC) " $*.cpp"
	$(CC) $(CFLAGS) $< -o $@


# Builds test Target
parser-test: clean
	@echo 'Building Buffer Test ...'
	$(CC) $(CFLAGS) $(SOURCE_DIR)/Parser_Test.cpp -o $(DEBUG_DIR)/$(EXECUTABLE)_test.o


# Build test executable
parser-test-executable: clean parser parser-test
	@echo 'Building Parser Test Executable ...'
	$(CC) $(LFLAGS) $(TARGETS) $(DEBUG_DIR)/$(EXECUTABLE)_test.o -o $(DEBUG_DIR)/$(EXECUTABLE)_test


# Cleaning up debug/ and bin/ directory
clean:
	@echo 'Cleaning up parser directory ...'
	rm -rf $(BUILD_DIR) && mkdir $(BUILD_DIR)
	rm -rf $(DEBUG_DIR) && mkdir $(DEBUG_DIR)
