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

# Base directory containing test_case_x_folder directories
base_dir="/home/shanghuang/Documents/Code related/SoftwareBugDetectionUsingCallGraphReferences/recreate/test_cases"
# Loop through each test_case_x_folder directory
for folder in "$base_dir"/test_case_*_folder;
do
    # Check if the directory exists
    if [ -d "$folder" ]; then
        echo "----------------------"
        echo "Đang xử lý thư mục: $folder"

        # Delete all .out files generated previously
        find "$folder" -type f -name "generated_callgraph.out" -exec rm -f {} \;

        # Delete all .bc files generated previously
        find "$folder" -type f -name "*.bc" -exec rm -f {} \;

        echo "-----------------------"
    fi
done
echo "All test cases cleaned up."