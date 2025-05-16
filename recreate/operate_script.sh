# Add bash execution permission to the script
#! /bin/bash 

# clang, g++, opt and valgrind not need to be 
# specified in the PATH

# Base directory containing parser.cpp and 
# test_case_x_folder directories
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

            # Create output.out file if it doesn't exist
            if [ ! -f "$folder"/output.out ]; then
                touch "$folder"/stderr_output.out
            fi

            # Echo to point out bugs thrown from the compilation, 
            # remember to end the line with \n 
            # to make sure the output is in a new line
            echo "compiler bug thrown:" >> "$folder"/stderr_output.out

            # Compile the .cpp file to check for errors thrown by gcc or g++
            clang++ -g "$cpp_file" -o "$cpp_file_name" &>> "$folder"/stderr_output.out

            # Move the compiled file to the test_case_x_folder directory
            mv "$cpp_file_name" "$folder"/"$cpp_file_name"

            # Maybe to remember if any warning is thrown by the compiler
            # It may be also be views as a potential bug

            # Check if no compiled file is generated and 
            # only output.out file is generated
            # This is sign that the compilation failed
            if [ ! -f "$folder"/"$cpp_file_name" ] && [ -f "$folder"/stderr_output.out ]; then
                echo "Compilation failed for $cpp_file_name"
                continue
            fi

            # Echo for splitting the output of each tool
            echo "" >> "$folder"/stderr_output.out
            echo "memcheck information:" >> "$folder"/stderr_output.out

            # If pass the compilation, there will be a compiled file generated 
            # and the output.out file will be empty
            # then used compiled file to check for 
            # memory leaks, thread errors, data races by using valgrind

            # Using valgrind memcheck tool, get full directory path
            valgrind --tool=memcheck /"$folder"/"$cpp_file_name" &>> "$folder"/stderr_output.out

            # Echo for splitting the output of each tool
            echo "" >> "$folder"/stderr_output.out
            echo "thread information:" >> "$folder"/stderr_output.out

            # Using valgrind threadcheck tool
            valgrind --tool=helgrind /"$folder"/"$cpp_file_name" &>> "$folder"/stderr_output.out

            # Echo for splitting the output of each tool
            echo "" >> "$folder"/stderr_output.out
            echo "data race information:\n" >> "$folder"/stderr_output.out

            # Using valgrind dataracecheck tool
            valgrind --tool=drd /"$folder"/"$cpp_file_name" &>> "$folder"/stderr_output.out

            # Echo for splitting the output of each tool
            echo "" >> "$folder"/stderr_output.out
            echo "call graph information:" >> "$folder"/stderr_output.out

            # File bitcode will be generated in the same directory as the .cpp file
            clang++ -emit-llvm -c "$cpp_file" -o "$cpp_file_name.bc" 2> "$folder"/clang_compile_errors.log

            # Move the generated .bc file to the test_case_x_folder directory
            mv "$cpp_file_name.bc" "$folder"/"$cpp_file_name".bc

            # Echo for splitting the output of each tool
            echo "" >> "$folder"/stderr_output.out
            echo "pipeline information:" >> "$folder"/stderr_output.out

            # Create the call graph using opt and redirect the output to a file
            opt -passes=print-callgraph "$folder/$cpp_file_name.bc" 2>&1 >/dev/null | ./parser "$ipc_level" "$support_level" "$confidence_level" > "$folder"/result.out

        else
            echo "No .cpp file found in $folder"
        fi
    fi
done
