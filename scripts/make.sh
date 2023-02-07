#!/bin/bash

cd build
make -j$JNUM
cd ..
find . -type f -name '*.uf2'