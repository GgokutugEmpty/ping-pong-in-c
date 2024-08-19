#!/bin/bash

TARGET="main"

if [ ! -f "$TARGET" ]; then
    echo "Compiled file not found. Compiling..."
    gcc -o $TARGET main.c

    if [ $? -ne 0 ]; then
        echo "Compilation error."
        exit 1
    fi
else
    echo "Compiled file found. Skipping recompilation."
fi

./$TARGET
