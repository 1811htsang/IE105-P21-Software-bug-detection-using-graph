#! /bin/bash

# This script is used to operate the recreate folder

# clear compiled parser, bc file
rm -f parser
rm -f test_file.bc

# rerun clang to generate the bc file
clang++ -emit-llvm -c test_file.cpp -o test_file.bc

# use g++ to compile parser.cpp
g++ parser.cpp -o parser

# operate the parser 
# 2>&1 redirects stderr to stdout
# ./parser is the parser program
opt -passes=print-callgraph test_file.bc 2>&1 >/dev/null | ./parser