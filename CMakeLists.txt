cmake_minimum_required(VERSION 3.3)
project(hska-compiler)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build/")
set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build/")

# Building Project with Makefile
# add_custom_target( hska-compiler COMMAND make -C ${hska-compiler_SOURCE_DIR} CLION_EXE_DIR=${PROJECT_BINARY_DIR} )

add_executable(HsKA-Compiler src/main.cpp)
add_executable(buffer src/buffer/src/Buffer_Test.cpp src/buffer/headers/Buffer.h src/buffer/src/Buffer.cpp)
add_executable(scanner src/scanner/src/Scanner_Test.cpp src/scanner/headers/Scanner.h src/scanner/src/Scanner.cpp)
add_executable(state-machine src/state-machine/src/StateMachine_Test.cpp src/state-machine/headers/StateMachine.h src/state-machine/src/StateMachine.cpp src/state-machine/headers/State.h src/state-machine/headers/Transition.h src/state-machine/headers/Core.h src/state-machine/src/State.cpp src/state-machine/src/Transition.cpp src/state-machine/src/SingleCharTransition.cpp src/state-machine/headers/SingleCharTransition.h src/state-machine/src/MultiCharTransition.cpp src/state-machine/headers/MultiCharTransition.h src/state-machine/src/EpsilonTransition.cpp src/state-machine/headers/EpsilonTransition.h src/state-machine/headers/Transitions.h)
add_executable(symbol-table src/symbol-table/src/SymbolTable_Test.cpp src/symbol-table/headers/SymbolTable.h src/symbol-table/src/SymbolTable.cpp src/scanner/src/Token.cpp src/scanner/headers/Token.h src/symbol-table/src/StringTab.cpp src/symbol-table/headers/StringTab.h src/symbol-table/src/StringTabNode.cpp src/symbol-table/headers/StringTabNode.h src/symbol-table/src/Information.cpp src/symbol-table/headers/Information.h src/symbol-table/src/SymbolTableEntry.cpp src/symbol-table/headers/SymbolTableEntry.h )
add_executable(utils src/utils/header/vector.h src/utils/src/vector_test.cpp src/utils/header/Helper.h src/utils/src/Helper.cpp src/utils/src/helper_test.cpp)
add_executable(vector src/utils/header/vector.h src/utils/src/vector_test.cpp)
