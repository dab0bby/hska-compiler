# HsKA-Compiler

### IB 321 - Systemnahes Programmieren


## How to use scanner
```
$ make
$ cd bin/
$ ./HsKA-Scanner ../test-files/scanner00.txt out.txt
```


## Building project with `Makefile`:
Build the hska-compiler:  
`make`

Clean all `bin/` and `debug/` directories:   
`make clean`

Target location:   
`bin/`

#### Buffer `src/buffer/`:
`make`: builds buffer  
`make buffer-test-executable`: builds test executable and dependencies

#### StateMachine `src/state-machine`:
`make`: builds state-machine  
`make state-machine-test-executable`: builds test executable and dependencies  

#### SymbolTable `src/symbol-table`:
`make`: builds symbol-table  
`make symb-table-test-executable`: builds test executable and dependencies

#### Scanner `src/scanner`:
`make`: builds scanner  
`make scanner-test-executable`: builds test executable and dependencies

#### Parser `src/parser`:
`make`: builds parser  
`make parser-test-executable`: builds test executable and dependencies
