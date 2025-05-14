#! /bin/bash

# Base directory containing parser.cpp and test_case_x_folder directories
base_dir="/home/shanghuang/Documents/Code related/SoftwareBugDetectionUsingCallGraphReferences/recreate/"

# Base directory containing test_case_x_folder directories
test_case_dir="/home/shanghuang/Documents/Code related/SoftwareBugDetectionUsingCallGraphReferences/recreate/test_cases"

# Parse command line arguments
ipc_level="$1"
support_level="$2"
confidence_level="$3"

# Delete the compiled parser
rm -f "$base_dir"/parser

# Delete all .out files generated previously
# Check if any output .out file exists, then remove
for folder in "$test_case_dir"/test_case_*_folder;
do
    # Check if the directory exists
    if [ -d "$folder" ]; then
        # # Shorten the folder name for better readability
        # folder_name=$(basename "$folder")
        # echo "In processing folder: $folder_name"

        # Delete all .out files generated previously
        find "$folder" -type f -name "*.out" -exec rm -f {} \;

        # Delete all .bc files generated previously
        find "$folder" -type f -name "*.bc" -exec rm -f {} \;
    fi
done

# Recompile the parser.cpp file
g++ "$base_dir"/parser.cpp -o "$base_dir"/parser

# Compile the test cases
# Loop through each test_case_x_folder directory
for folder in "$test_case_dir"/test_case_*_folder; 
do
    # Check if the directory exists
    if [ -d "$folder" ]; then
        # # Shorten the folder name for better readability
        # folder_name=$(basename "$folder")
        # echo "In processing folder: $folder_name"

        # Find the .cpp file in the current test_case_x_folder directory
        cpp_file=$(find "$folder" -type f -name "*.cpp")

        # Remove the .cpp extension to get the base name
        cpp_file_name=$(basename "$cpp_file" .cpp)

        # Check if the cpp file exists
        if [ -n "$cpp_file" ]; then
            # File bitcode will be generated in the same directory as the .cpp file
            clang++ -emit-llvm -c "$cpp_file" -o "$cpp_file_name.bc" 2> "$folder"/compile_errors.log

            # Move the generated .bc file to the test_case_x_folder directory
            mv "$cpp_file_name.bc" "$folder"/"$cpp_file_name".bc

            # Create the call graph using opt and redirect the output to a file
            opt -passes=print-callgraph "$folder/$cpp_file_name.bc" 2>&1 >/dev/null | ./parser "$ipc_level" "$support_level" "$confidence_level" > "$folder"/generated_callgraph.out

            

        else
            echo "No .cpp file found in $folder"
        fi
    fi
done
