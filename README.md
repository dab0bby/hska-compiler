# HsKA-Compiler

### IB 321 - Systemnahes Programmieren

#### `CMake` for 'CLion' only.

## Building project with `Makefile` within root dir:
All components:  
`make`

Clean all `build/` and `debug/` directories:   
`make clean`

Target location:   
`build/`

#### Buffer `src/buffer/`:
`make clean`: clean up `debug/` and `build/` directory.   
`make buffer`: builds defined targets into `build/`   
`make buffer-test`: builds `Buffer_Test.o` into `debug/`   
`make buffer-test-executable`: builds `Buffer_Test` executable and dependencies into `debug/`

#### StateMachine `src/state-machine`:
`make clean`: clean up `debug/` and `build/` directory.  
`make state-machine`: builds defined targets into `build/`   
`make state-machine-test`: builds `StateMachine_Test.o` into `debug/`   
`make state-machine-test-executable`: builds `StateMachine_Test` executable and dependencies into `debug/`

#### SymbolTable `src/symbol-table`:
`make clean`: clean up `debug/` and `build/` directory.  
`make symb-table`: builds defined targets into `build/`     
`make symb-table-test`: builds `SymbolTable_Test.o` into `debug/`   
`make symb-table-test-executable`: builds `SymbolTable_Test` executable and dependencies into `debug/`

#### Scanner `src/scanner`:
`make clean`: clean up `debug/` and `build/` directory.  
`make scanner`: builds defined targets into `build/`     
`make scanner-test-executable`: builds `Scanner_Test` executable and dependencies into `debug/`
