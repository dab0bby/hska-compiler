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
EXECUTABLE = StateMachine


# StateMachine.o depends on StateMachine.h and StateMachine.cpp
state-machine: $(HEADER_DIR)/StateMachine.h $(SOURCE_DIR)/StateMachine.cpp
	@echo 'Building StateMachine ...'
	$(CC) $(CFLAGS) $(SOURCE_DIR)/StateMachine.cpp -o $(BUILD_DIR)/$(EXECUTABLE).o


# StateMachine_Test.o depends on StateMachine.h and StateMachine_Test.cpp
state-machine-test: $(HEADER_DIR)/StateMachine.h $(SOURCE_DIR)/StateMachine_Test.cpp
	@echo 'Building StateMachine Test ...'
	$(CC) $(CFLAGS) $(SOURCE_DIR)/StateMachine_Test.cpp -o $(DEBUG_DIR)/$(EXECUTABLE)_Test.o


# StateMachine_Test_Executable depends on StateMachine.o and StateMachine_Test.o
state-machine-test-executable: clean state-machine state-machine-test
	@echo 'Building StateMachine Test Executable ...'
	$(CC) $(LFLAGS) $(BUILD_DIR)/$(EXECUTABLE).o $(DEBUG_DIR)/$(EXECUTABLE)_Test.o -o $(DEBUG_DIR)/$(EXECUTABLE)_Test


# Cleaning up debug/ and build/ directory
clean:
	@echo 'Cleaning up StateMachine directory ...'
	rm -f build/*
	rm -f debug/*
