cmake_minimum_required( VERSION 3.3 )
project( hska-compiler )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

set( EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build/" )
set( LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build/" )

# Building Project with Makefile
# add_custom_target( hska-compiler COMMAND make -C ${hska-compiler_SOURCE_DIR} CLION_EXE_DIR=${PROJECT_BINARY_DIR} )

add_executable( HsKA-Scanner src/main.cpp )
add_executable( buffer src/buffer/src/Buffer_Test.cpp src/buffer/headers/Buffer.h src/buffer/src/Buffer.cpp )
add_executable( scanner src/scanner/src/Scanner_Test.cpp src/scanner/headers/Scanner.h src/scanner/src/Scanner.cpp )
add_executable( state-machine src/state-machine/src/StateMachine_Test.cpp src/state-machine/headers/StateMachine.h src/state-machine/src/StateMachine.cpp )
add_executable( symbol-table src/symbol-table/src/SymbolTable_Test.cpp src/symbol-table/headers/SymbolTable.h src/symbol-table/src/SymbolTable.cpp )
