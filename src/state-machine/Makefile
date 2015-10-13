# Compiler
CC     = g++
DEBUG  = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

# Sources
HEADER_DIR = headers
SOURCE_DIR = src
DEBUG_DIR  = debug

# Target
BUILD_DIR  = build

# List of targets
TARGETS = $(BUILD_DIR)/StateMachine.o \
	# add more here
	# last without escape sequence

EXECUTABLE = StateMachine


# Builds targets
state-machine: clean $(TARGETS)

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp $(HEADER_DIR)/%.h
	@echo $(CC) " $*.cpp"
	$(CC) $(CFLAGS) $< -o $@


# Builds StateMachine_Test object files.
state-machine-test: $(HEADER_DIR)/StateMachine.h $(SOURCE_DIR)/StateMachine_Test.cpp
	@echo 'Building StateMachine Test ...'
	$(CC) $(CFLAGS) $(SOURCE_DIR)/StateMachine_Test.cpp -o $(DEBUG_DIR)/$(EXECUTABLE)_Test.o


# Builds StateMachine_Test executable.
state-machine-test-executable: clean state-machine state-machine-test
	@echo 'Building StateMachine Test Executable ...'
	$(CC) $(LFLAGS) $(BUILD_DIR)/$(EXECUTABLE).o $(DEBUG_DIR)/$(EXECUTABLE)_Test.o -o $(DEBUG_DIR)/$(EXECUTABLE)_Test


# Cleaning up debug/ and build/ directory
clean:
	@echo 'Cleaning up StateMachine directory ...'
	rm -f build/*
	rm -f debug/*
