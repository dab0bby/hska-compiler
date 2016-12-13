cmake_minimum_required(VERSION 3.3)
project(hska-compiler)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin/")
set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/lib/")

# Building Project with Makefile
# add_custom_target( hska-compiler COMMAND make -C ${hska-compiler_SOURCE_DIR} CLION_EXE_DIR=${PROJECT_BINARY_DIR} )

add_executable(HsKA-Compiler src/main.cpp)
add_executable(buffer src/buffer/src/Buffer_Test.cpp src/buffer/include/Buffer.h src/buffer/src/Buffer.cpp)
add_executable(scanner src/scanner/src/Scanner_Test.cpp src/scanner/include/Scanner.h src/scanner/src/Scanner.cpp src/scanner/src/Token.cpp)
add_executable(state-machine src/state-machine/src/StateMachine_Test.cpp src/state-machine/include/StateMachine.h src/state-machine/src/StateMachine.cpp src/state-machine/include/State.h src/state-machine/src/State.cpp src/state-machine/include/Transition.h src/state-machine/src/Transition.cpp src/state-machine/include/Condition.h src/state-machine/include/LanguageParser.h src/state-machine/src/LanguageParser.cpp)
add_executable(symbol-table src/symbol-table/src/SymbolTable_Test.cpp src/symbol-table/include/SymbolTable.h src/symbol-table/src/SymbolTable.cpp src/scanner/include/Token.h src/symbol-table/src/StringTab.cpp src/symbol-table/include/StringTab.h src/symbol-table/src/StringTabNode.cpp src/symbol-table/include/StringTabNode.h src/symbol-table/src/Information.cpp src/symbol-table/include/Information.h src/symbol-table/src/SymbolTableEntry.cpp src/symbol-table/include/SymbolTableEntry.h)
add_executable(utils src/utils/include/Helper.h src/utils/src/helper_test.cpp)
add_executable(vector src/utils/include/vector.h src/utils/src/vector_test.cpp)
