#!/usr/bin/env bash
g++ -std=c++17 "$1.cpp" -o "$1" && 
"./$1" < input.txt > output.txt
