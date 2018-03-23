#!/bin/sh

git clone https://github.com/google/googletest.git
cd googletest
cmake .
make && sudo make install
