#!/bin/sh

BIN=railwayn
SRC=$(find -name "*.cpp")

g++ $SRC -o $BIN
