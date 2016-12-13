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
TARGETS = $(BUILD_DIR)/Buffer.o \
	# add more here
	# last without escape sequence

EXECUTABLE = Buffer


# Builds Targets and saves to BUILD_DIR
buffer: clean $(TARGETS)

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp $(HEADER_DIR)/%.h
	@echo $(CC) " $*.cpp"
	$(CC) $(CFLAGS) $< -o $@


# Builds test Target
buffer-test: $(HEADER_DIR)/Buffer.h $(SOURCE_DIR)/Buffer_Test.cpp
	@echo 'Building Buffer Test ...'
	$(CC) $(CFLAGS) $(SOURCE_DIR)/Buffer_Test.cpp -o $(DEBUG_DIR)/$(EXECUTABLE)_Test.o


# Build test executable
buffer-test-executable: clean buffer buffer-test
	@echo 'Building Buffer Test Executable ...'
	$(CC) $(LFLAGS) $(TARGETS) $(DEBUG_DIR)/Buffer_Test.o -o $(DEBUG_DIR)/$(EXECUTABLE)_Test


# Cleaning up debug/ and bin/ directory
clean:
	@echo 'Cleaning up buffer directory ...'
	rm -rf $(BUILD_DIR) && mkdir $(BUILD_DIR)
	rm -rf $(DEBUG_DIR) && mkdir $(DEBUG_DIR)
