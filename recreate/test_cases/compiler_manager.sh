# This file is used for compile each test case
# If there is any or no error, it will be printed to the output file in each test case
# The output file will be named as test_case_name.out
# The output file will be saved in the same directory as the test case

#! /bin/bash

# Base directory containing test_case_x_folder directories
BASE_DIR="/home/shanghuang/Documents/Code related/SoftwareBugDetectionUsingCallGraphReferences/recreate/test_cases"

# Loop through each test_case_x_folder directory
for folder in "$BASE_DIR"/test_case_*_folder; 
do
    # Check if the directory exists
    if [ -d "$folder" ]; then
        echo "----------------------"
        echo "Đang xử lý thư mục: $folder"

        # Delete all .out files generated previously
        find "$folder" -type f -name "*.out" -exec rm -f {} \;

        # Delete all .bc files generated previously
        cpp_file=$(find "$folder" -type f -name "*.cpp")

        # Check if the cpp file exists
        if [ -n "$cpp_file" ]; then
            # Name of the output file
            output_file="$folder/$(basename "$cpp_file" .cpp).out"

            # Compile file .cpp and redirect output to .out file
            g++ "$cpp_file" -o "$folder/a.out" &> "$output_file"

            # Delete the compiled executable file
            rm -f "$folder/a.out"

            # Check if the compilation was successful
            # If successful, the .out file not contain any error messages
            # If the compilation fails, the .out file will contain error messages from the compiler
            if [ $? -eq 0 ]; then
                echo "$cpp_file pass"
            else
                echo "$cpp_file fail"
            fi

            echo "-----------------------"
        else
            echo "No .cpp file found in $folder"
        fi
    fi
done
