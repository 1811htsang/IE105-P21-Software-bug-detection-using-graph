#! /bin/bash

# This script is used to clean the recreate folder

# clear compiled parser, bc file
rm -f parser
rm -f test_file.bc

# check if has any output .out file then remove
if [ -f *.out ]; then
    rm -f *.out
fi

# check if has any output .dot file then remove
if [ -f *.dot ]; then
    rm -f *.dot
fi

# check if has any output .txt file then remove
if [ -f *.txt ]; then
    rm -f *.txt
fi