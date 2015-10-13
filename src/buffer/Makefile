# Compiler
CC     = g++
DEBUG  = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

# Sources
HEADER_DIR = headers
SOURCE_DIR = src
DEBUG_DIR = debug

# Target
BUILD_DIR  = build
EXECUTABLE = Buffer


# Buffer.o depends on Buffer.h and Buffer.cpp
buffer: $(HEADER_DIR)/Buffer.h $(SOURCE_DIR)/Buffer.cpp
	@echo 'Building Buffer ...'
	$(CC) $(CFLAGS) $(SOURCE_DIR)/Buffer.cpp -o $(BUILD_DIR)/$(EXECUTABLE).o


# Buffer_Test.o depends on Buffer.h and Buffer_Test.cpp
buffer-test: $(HEADER_DIR)/Buffer.h $(SOURCE_DIR)/Buffer_Test.cpp
	@echo 'Building Buffer Test ...'
	$(CC) $(CFLAGS) $(SOURCE_DIR)/Buffer_Test.cpp -o $(DEBUG_DIR)/$(EXECUTABLE)_Test.o


# Buffer_Test_Executable depends on Buffer.o and Buffer_Test.o
buffer-test-executable: clean buffer buffer-test
	@echo 'Building Buffer Test Executable ...'
	$(CC) $(LFLAGS) $(BUILD_DIR)/$(EXECUTABLE).o $(DEBUG_DIR)/$(EXECUTABLE)_Test.o -o $(DEBUG_DIR)/$(EXECUTABLE)_Test


# Cleaning up debug/ and build/ directory
clean:
	@echo 'Cleaning up buffer directory ...'
	rm -f build/*
	rm -f debug/*
