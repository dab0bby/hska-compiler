#!/bin/bash
for filename in test-files/parser/*.test; do
    src/parser/debug/parser_test "$filename"
    echo "-----------------------------------------------------"
done
