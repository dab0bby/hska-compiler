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
TARGETS = $(BUILD_DIR)/StateMachine.o \
	$(BUILD_DIR)/TokenPosition.o \
	$(BUILD_DIR)/TokenScanner.o \
	$(BUILD_DIR)/Transition.o
	# add more here
	# last without escape sequence

EXECUTABLE = state-machine


# Builds targets
state-machine: clean $(TARGETS)

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp $(HEADER_DIR)/%.h
	@echo $(CC) " $*.cpp"
	$(CC) $(CFLAGS) $< -o $@


# Builds StateMachine_Test object files.
state-machine-test: $(SOURCE_DIR)/StateMachine_Test.cpp
	@echo 'Building StateMachine Test ...'
	$(CC) $(CFLAGS) $(SOURCE_DIR)/StateMachine_Test.cpp -o $(DEBUG_DIR)/$(EXECUTABLE)_Test.o


# Builds StateMachine_Test executable.
state-machine-test-executable: clean state-machine state-machine-test
	@echo 'Building StateMachine Test Executable ...'
	$(CC) $(LFLAGS) $(TARGETS) $(DEBUG_DIR)/$(EXECUTABLE)_Test.o -o $(DEBUG_DIR)/$(EXECUTABLE)_Test


# Cleaning up debug/ and build/ directory
clean:
	@echo 'Cleaning up StateMachine directory ...'
	rm -rf $(BUILD_DIR) && mkdir $(BUILD_DIR)
	rm -rf $(DEBUG_DIR) && mkdir $(DEBUG_DIR)
