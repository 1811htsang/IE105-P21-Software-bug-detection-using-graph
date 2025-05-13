import json
import os
import random

# Path to the JSONL file
jsonl_file_path = "/home/shanghuang/Documents/Code related/SoftwareBugDetectionUsingCallGraphReferences/recreate/cpp_dataset.jsonl"

# Base directory to save the test cases
output_base_dir = "/home/shanghuang/Documents/Code related/SoftwareBugDetectionUsingCallGraphReferences/recreate/test_cases"

# Create the base directory if it doesn't exist
os.makedirs(output_base_dir, exist_ok=True)

# Read the JSONL file and filter out empty lines
with open(jsonl_file_path, "r", encoding="utf-8") as jsonl_file:
    lines = [line.strip() for line in jsonl_file if line.strip()]

# Randomly select up to 30 lines from the JSONL file
random_lines = random.sample(lines, min(10, len(lines)))

# Iterate through the selected lines and extract the "pass" key
# and save it to a C++ file
for idx, line in enumerate(random_lines, start=1):
    try:
        # Parse the JSON line
        data = json.loads(line)

        # Check for the "pass" key
        if "pass" in data:
            # Create a separate folder for each test case
            folder_name = f"test_case_{idx}_folder"
            folder_path = os.path.join(output_base_dir, folder_name)
            os.makedirs(folder_path, exist_ok=True)

            # Create a C++ file in the folder
            cpp_file_path = os.path.join(folder_path, f"test_case_{idx}.cpp")
            with open(cpp_file_path, "w", encoding="utf-8") as cpp_file:
                cpp_file.write(data["pass"])

            print(f"Source code saved to: {cpp_file_path}")

    except json.JSONDecodeError:
        print(f"Error parsing JSON at line {idx}: {line}")