#!/bin/bash

echo "MAKE_BINARY=nmake" >> $GITHUB_ENV
echo "CMAKE_GENERATOR=NMake Makefiles" >> $GITHUB_ENV

echo "LIB=$LIB;$INSTALL_PREFIX/lib" >> $GITHUB_ENV
echo "INCLUDE=$INCLUDE;$INSTALL_PREFIX/include" >> $GITHUB_ENV