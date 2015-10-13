# HsKA-Compiler

### IB 321 - Systemnahes Programmieren

#### `CMake` for 'CLion' only.

## Building project with `Makefile` within root dir:
All components:  
`make`

Options: `scanner`, `buffer`, `state-machine`, `symbol-table`   
`make [ option ]`

Clean `build/`directories:   
`make clean`

Target location:   
`root/build/`

#### Buffer `src/buffer/`:
`make clean`: clean up `debug/` and `build/` directory.   
`make buffer`: builds `Buffer.o` into `build/`   
`make buffer-test`: builds `Buffer_Test.o` into `debug/`   
`make buffer-test-executable`: builds `Buffer_Test` ececutable into `debug/`

#### Scanner `src/scanner`:
`make clean`: clean up `debug/` and `build/` directory.  