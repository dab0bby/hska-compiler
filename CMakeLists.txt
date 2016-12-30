cmake_minimum_required(VERSION 3.3)
project(hska-compiler)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin/")
set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/lib/")

# Building Project with Makefile
# add_custom_target( hska-compiler COMMAND make -C ${hska-compiler_SOURCE_DIR} CLION_EXE_DIR=${PROJECT_BINARY_DIR} )

# Buffer sources
set(BUFFER_SRC
    src/buffer/include/Buffer.h src/buffer/src/Buffer.cpp)

# Symbol table sources
set(SYMB_TABLE_SRC
    src/symbol-table/include/SymbolTable.h src/symbol-table/src/SymbolTable.cpp
    src/symbol-table/include/StringTab.h src/symbol-table/src/StringTab.cpp
    src/symbol-table/include/StringTabNode.h src/symbol-table/src/StringTabNode.cpp
    src/symbol-table/include/Information.h src/symbol-table/src/Information.cpp
    src/symbol-table/include/SymbolTableEntry.h src/symbol-table/src/SymbolTableEntry.cpp)

# State machine sources
set(STATE_MACHINE_SRC
    src/state-machine/include/Condition.h
    src/state-machine/include/StateMachine.h src/state-machine/src/StateMachine.cpp
    src/state-machine/include/TokenPosition.h src/state-machine/src/TokenPosition.cpp
    src/state-machine/include/Transition.h src/state-machine/src/Transition.cpp
    src/state-machine/include/TokenScanner.h src/state-machine/src/TokenScanner.cpp)

# Scanner sources
set(SCANNER_SRC
    src/scanner/include/Scanner.h src/scanner/src/Scanner.cpp
    src/scanner/src/Token.cpp src/scanner/include/Token.h)

add_executable(HsKA-Compiler src/main.cpp ${SCANNER_SRC} ${BUFFER_SRC} ${SYMB_TABLE_SRC} ${STATE_MACHINE_SRC})
add_executable(buffer src/buffer/src/Buffer_Test.cpp ${BUFFER_SRC})
add_executable(scanner src/scanner/src/Scanner_Test.cpp ${SCANNER_SRC} ${BUFFER_SRC} ${SYMB_TABLE_SRC} ${STATE_MACHINE_SRC})
add_executable(state-machine src/state-machine/src/StateMachine_Test.cpp ${STATE_MACHINE_SRC})
add_executable(symbol-table src/symbol-table/src/SymbolTable_Test.cpp ${SYMB_TABLE_SRC})
add_executable(utils src/utils/include/Helper.h src/utils/src/helper_test.cpp)
add_executable(vector src/utils/include/vector.h src/utils/src/vector_test.cpp)
