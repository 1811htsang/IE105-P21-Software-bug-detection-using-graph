#    This script is used to generate 3 random parameters 
#    as command line arguments for the operate_script.sh script.
#    It will then run the script with these parameters to 
#    generate the output files in each test case folder.
#    After that, it will read the output files and
#    extract the number of bugs specified in the output files.
#    Then it will plot the number of bugs in each test case folder.

# import necessary libraries
import os
import random
import subprocess
import matplotlib.pyplot as plt

# Set the current working directory
current_dir = "/home/shanghuang/Documents/Code related/SoftwareBugDetectionUsingCallGraphReferences/recreate"
# Change the current working directory to the script's directory
os.chdir(current_dir)

# Script running command
script_command = "./operate_script.sh"

# Folder path to the test cases
test_cases_dir = current_dir + "/test_cases"

# Folder path to the results
# Create the results directory if it does not exist
results_dir = current_dir + "/results"
if not os.path.exists(results_dir):
    os.makedirs(results_dir)

# Generate 3 random parameters
def generate_random_parameters():
    # Generate 3 random parameters
    param1 = random.randint(1, 10)
    param2 = random.randint(1, 30)
    param3 = random.randint(0, 100)
    return param1, param2, param3

# Run the script with the parameters
def run_script(param1, param2, param3):

    # Run the script with the parameters
    subprocess.run([
        "bash",
        str(script_command), 
        str(param1), 
        str(param2), 
        str(param3)
    ])

# Run the clean.sh script to clean the test cases
def run_clean_script():
    # Run the clean.sh script
    subprocess.run(["bash", "./clean.sh"])

# Read the generated_callgraph.out output files 
# in each test case folder
# and extract the number of bugs
def read_output_files():
    # List to store the number of bugs in each test case folder
    bugs_count = []
    # Loop through each test case folder
    for test_case in os.listdir(test_cases_dir):
        # Path to the generated_callgraph.out file
        output_file_path = os.path.join(test_cases_dir, test_case, "final_output.out")
        # Check if the file exists
        if os.path.exists(output_file_path):
            # Read the file and extract the number of bugs 
            # Bug is sepecified by the line "bug may appear"
            with open(output_file_path, "r") as file:
                # Check for line "Total bugs:"
                for line in file:
                    if "Total bugs may appear:" in line:
                        # Extract the number of bugs
                        bugs = int(line.split(":")[1].strip())
                        # Append the number of bugs to the list
                        bugs_count.append(bugs)
                        break

        else:
            # If the file does not exist, append 0 to the list
            bugs_count.append(0)
    return bugs_count

# Plot the number of bugs in each test case folder
def plot_bugs_count(bugs_count):
    # Plot the number of bugs in each test case folder
    plt.bar(range(len(bugs_count)), bugs_count)
    plt.xlabel("Test Case Folder")
    plt.ylabel("Number of Bugs")
    plt.title("Number of Bugs in Each Test Case Folder")
    plt.xticks(range(len(bugs_count)), os.listdir(test_cases_dir), rotation=90)
    plt.tight_layout()
    plt.show()

    # Plot the number of bugs in each test case folder
    plt.plot(range(len(bugs_count)), bugs_count, marker='o')
    plt.xlabel("Test Case Folder")
    plt.ylabel("Number of Bugs")
    plt.title("Number of Bugs in Each Test Case Folder")
    plt.xticks(range(len(bugs_count)), os.listdir(test_cases_dir), rotation=90)
    plt.tight_layout()
    plt.show()

# Function to package the workflow for random parameters method
def package_workflow_random_parameter():
    # Generate random parameters
    param1, param2, param3 = generate_random_parameters()
    print(f"Generated parameters: {param1}, {param2}, {param3}")
    
    # Run the script with the parameters
    run_script(param1, param2, param3)
    
    # Read the output files and extract the number of bugs
    bugs_count = read_output_files()
    
    # Plot the number of bugs in each test case folder
    plot_bugs_count(bugs_count)

# Function to package the workflow for ipc level increment method
def package_workflow_ipc_level_increment():
    # Define the selected parameters
    param1 = 1  # This parameter is selected to increment the IPC_LEVEL
    param2 = 3
    param3 = 75
    print(f"Initial parameters: {param1}, {param2}, {param3}")

    # Dictionary to store bugs count for each iteration
    iterations_bugs_count = {}

    # Loop through 5 iterations
    for iteration in range(1, 6):
        # Run the clean.sh script to clean the test cases
        run_clean_script()
        # Run the script with the current parameters
        print(f"Running iteration {iteration} with parameters: {param1}, {param2}, {param3}")
        
        # Run the script with the current parameters
        run_script(param1, param2, param3)
        
        # Read the output files and extract the number of bugs
        bugs_count = read_output_files()
        
        # Store the bugs count for this iteration
        iterations_bugs_count[f"Iteration {iteration}"] = bugs_count
        
        # Increment param1 for the next iteration
        param1 += 1

        # If all test cases have 0 bugs, stop further iterations
        # Check if all counts are zero
        if all(count == 0 for count in bugs_count):
            print(f"All test cases have 0 bugs in iteration {iteration}. Stopping further iterations.")
            break





    # Plot the results as a line chart
    plt.figure(figsize=(20, 6))
    for iteration, bugs_count in iterations_bugs_count.items():
        plt.plot(range(len(bugs_count)), bugs_count, marker='o', label=iteration)

    # Configure the chart
    plt.xlabel("Test Case Folder")
    plt.ylabel("Number of Bugs")
    plt.title("Number of Bugs in Each Test Case Folder Across Iterations (IPC Level Increment)")
    plt.xticks(range(len(bugs_count)), os.listdir(test_cases_dir), rotation=90)
    plt.legend()
    plt.tight_layout()

    # Edit the legend to be outside the chart
    plt.legend(bbox_to_anchor=(1.05, 1), loc='upper left', borderaxespad=0.)
    plt.subplots_adjust(right=0.85)

    # Save the chart to the results directory
    chart_path = os.path.join(results_dir, "bugs_count_iterations_chart_ipc_increment.png")
    plt.savefig(chart_path)
    
    # Shorten the chart path for display
    chart_path = os.path.abspath(chart_path)
    print(f"Chart saved to: /results")

    # Show the chart
    plt.show()

# Function to package the workflow for support increment
def package_workflow_support_level_increment():
    # Define the selected parameters
    param1 = 1  
    param2 = 1 # This parameter is selected to increment the SUPPORT_LEVEL
    param3 = 75
    print(f"Initial parameters: {param1}, {param2}, {param3}")

    # Dictionary to store bugs count for each iteration
    iterations_bugs_count = {}

    # Loop through 5 iterations
    for iteration in range(1, 6):
        # Run the clean.sh script to clean the test cases
        run_clean_script()
        # Run the script with the current parameters
        print(f"Running iteration {iteration} with parameters: {param1}, {param2}, {param3}")
        
        # Run the script with the current parameters
        run_script(param1, param2, param3)
        
        # Read the output files and extract the number of bugs
        bugs_count = read_output_files()
        
        # Store the bugs count for this iteration
        iterations_bugs_count[f"Iteration {iteration}"] = bugs_count
        
        # Increment param1 for the next iteration
        param2 += 1

        # If all test cases have 0 bugs, stop further iterations
        # Check if all counts are zero
        if all(count == 0 for count in bugs_count):
            print(f"All test cases have 0 bugs in iteration {iteration}. Stopping further iterations.")
            break

    # Plot the results as a line chart
    plt.figure(figsize=(20, 6))
    for iteration, bugs_count in iterations_bugs_count.items():
        plt.plot(range(len(bugs_count)), bugs_count, marker='o', label=iteration)

    # Configure the chart
    plt.xlabel("Test Case Folder")
    plt.ylabel("Number of Bugs")
    plt.title("Number of Bugs in Each Test Case Folder Across Iterations (Support Level Increment)")
    plt.xticks(range(len(bugs_count)), os.listdir(test_cases_dir), rotation=90)
    plt.legend()
    plt.tight_layout()
    
    # Edit the legend to be outside the chart
    plt.legend(bbox_to_anchor=(1.05, 1), loc='upper left', borderaxespad=0.)
    plt.subplots_adjust(right=0.85)



    # Save the chart to the results directory
    chart_path = os.path.join(results_dir, "bugs_count_iterations_chart_support_increment.png")
    plt.savefig(chart_path)

    # Shorten the chart path for display
    chart_path = os.path.abspath(chart_path)
    print(f"Chart saved to: /results")

    # Show the chart
    plt.show()

# Function to package the workflow for confidence increment
def package_workflow_confidence_level_increment():
    # Define the selected parameters
    param1 = 1  
    param2 = 3 
    param3 = 0 # This parameter is selected to increment the CONFIDENCE_LEVEL
    print(f"Initial parameters: {param1}, {param2}, {param3}")

    # Dictionary to store bugs count for each iteration
    iterations_bugs_count = {}

    # Loop through 10 iterations
    for iteration in range(1, 11):
        # Run the clean.sh script to clean the test cases
        run_clean_script()
        # Run the script with the current parameters
        print(f"Running iteration {iteration} with parameters: {param1}, {param2}, {param3}")
        
        # Run the script with the current parameters
        run_script(param1, param2, param3)
        
        # Read the output files and extract the number of bugs
        bugs_count = read_output_files()
        
        # Store the bugs count for this iteration
        iterations_bugs_count[f"Iteration {iteration}"] = bugs_count
        
        # Increment param1 for the next iteration
        param3 += 10

        # If all test cases have 0 bugs, stop further iterations
        # Check if all counts are zero
        if all(count == 0 for count in bugs_count):
            print(f"All test cases have 0 bugs in iteration {iteration}. Stopping further iterations.")
            break

    # Plot the results as a line chart
    plt.figure(figsize=(20, 6))
    for iteration, bugs_count in iterations_bugs_count.items():
        plt.plot(range(len(bugs_count)), bugs_count, marker='o', label=iteration)

    # Configure the chart
    plt.xlabel("Test Case Folder")
    plt.ylabel("Number of Bugs")
    plt.title("Number of Bugs in Each Test Case Folder Across Iterations (Confidence Level Increment)")
    plt.xticks(range(len(bugs_count)), os.listdir(test_cases_dir), rotation=90)
    plt.legend()
    plt.tight_layout()
    
    # Edit the legend to be outside the chart
    plt.legend(bbox_to_anchor=(1.05, 1), loc='upper left', borderaxespad=0.)
    plt.subplots_adjust(right=0.85)



    # Save the chart to the results directory
    chart_path = os.path.join(results_dir, "bugs_count_iterations_chart_confidence_iteration.png")
    plt.savefig(chart_path)

    # Shorten the chart path for display
    chart_path = os.path.abspath(chart_path)
    print(f"Chart saved to: /results")

    # Show the chart
    plt.show()

# Function to package the workflow for ipc level increment with bar chart
def package_workflow_ipc_level_increment_bar_chart():
    # Define the selected parameters
    param1 = 1  # This parameter is selected to increment the IPC_LEVEL
    param2 = 3
    param3 = 75
    print(f"Initial parameters: {param1}, {param2}, {param3}")

    # Dictionary to store bugs count for each iteration
    iterations_bugs_count = {}

    # Loop through 10 iterations
    for iteration in range(1, 6):
        # Run the clean.sh script to clean the test cases
        run_clean_script()
        # Run the script with the current parameters
        print(f"Running iteration {iteration} with parameters: {param1}, {param2}, {param3}")
        
        # Run the script with the current parameters
        run_script(param1, param2, param3)
        
        # Read the output files and extract the number of bugs
        bugs_count = read_output_files()

        # Sum total number of bugs in each test case folder
        total_bugs = sum(bugs_count)
        print(f"Total number of bugs in iteration {iteration}: {total_bugs}")
        
        # Store the total bugs count for this iteration
        iterations_bugs_count[f"Iteration {iteration}"] = total_bugs
        
        # Increment param1 for the next iteration
        param1 += 1

        # If all test cases have 0 bugs, stop further iterations
        # Check if all counts are zero
        if all(count == 0 for count in bugs_count):
            print(f"All test cases have 0 bugs in iteration {iteration}. Stopping further iterations.")
            break

    # Plot the results as a bar chart with 
    # x-axis as total number of bugs in each iteration
    # y-axis as the number of bugs 
    plt.figure(figsize=(20, 6))
    plt.bar(iterations_bugs_count.keys(), iterations_bugs_count.values(), color='skyblue')
    
    # Configure the chart
    plt.xlabel("Iterations")
    plt.ylabel("Total Number of Bugs")
    plt.title("Total Number of Bugs in Each Iteration (IPC Level Increment)")
    plt.xticks(rotation=45)
    plt.tight_layout()

    # Save the chart to the results directory
    chart_path = os.path.join(results_dir, "total_bugs_count_iterations_chart_ipc_increment.png")
    plt.savefig(chart_path)

    # Shorten the chart path for display
    chart_path = os.path.abspath(chart_path)
    print(f"Chart saved to: /results")

    # Show the chart
    plt.show()

# Function to package the workflow for support increment
def package_workflow_support_level_increment_bar_chart():
    # Define the selected parameters
    param1 = 1  
    param2 = 1 # This parameter is selected to increment the SUPPORT_LEVEL
    param3 = 75
    print(f"Initial parameters: {param1}, {param2}, {param3}")

    # Dictionary to store bugs count for each iteration
    iterations_bugs_count = {}

    # Loop through 5 iterations
    for iteration in range(1, 6):
        # Run the clean.sh script to clean the test cases
        run_clean_script()
        # Run the script with the current parameters
        print(f"Running iteration {iteration} with parameters: {param1}, {param2}, {param3}")
        
        # Run the script with the current parameters
        run_script(param1, param2, param3)
        
        # Read the output files and extract the number of bugs
        bugs_count = read_output_files()

        # Sum total number of bugs in each test case folder
        total_bugs = sum(bugs_count)
        print(f"Total number of bugs in iteration {iteration}: {total_bugs}")
        
        # Store the bugs count for this iteration
        iterations_bugs_count[f"Iteration {iteration}"] = total_bugs
        
        # Increment param1 for the next iteration
        param2 += 1

        # If all test cases have 0 bugs, stop further iterations
        # Check if all counts are zero
        if all(count == 0 for count in bugs_count):
            print(f"All test cases have 0 bugs in iteration {iteration}. Stopping further iterations.")
            break

    # Plot the results as a bar chart with 
    # x-axis as total number of bugs in each iteration
    # y-axis as the number of bugs 
    plt.figure(figsize=(20, 6))
    plt.bar(iterations_bugs_count.keys(), iterations_bugs_count.values(), color='skyblue')
    
    # Configure the chart
    plt.xlabel("Iterations")
    plt.ylabel("Total Number of Bugs")
    plt.title("Total Number of Bugs in Each Iteration (Support Level Increment)")
    plt.xticks(rotation=45)
    plt.tight_layout()

    # Save the chart to the results directory
    chart_path = os.path.join(results_dir, "total_bugs_count_iterations_chart_ipc_increment.png")
    plt.savefig(chart_path)

    # Shorten the chart path for display
    chart_path = os.path.abspath(chart_path)
    print(f"Chart saved to: /results")

    # Show the chart
    plt.show()

# Function to package the workflow for confidence increment
def package_workflow_confidence_level_increment_bar_chart():
    # Define the selected parameters
    param1 = 1  
    param2 = 3 
    param3 = 0 # This parameter is selected to increment the CONFIDENCE_LEVEL
    print(f"Initial parameters: {param1}, {param2}, {param3}")

    # Dictionary to store bugs count for each iteration
    iterations_bugs_count = {}

    # Loop through 21 iterations
    for iteration in range(1, 11):
        # Run the clean.sh script to clean the test cases
        run_clean_script()
        # Run the script with the current parameters
        print(f"Running iteration {iteration} with parameters: {param1}, {param2}, {param3}")
        
        # Run the script with the current parameters
        run_script(param1, param2, param3)
        
        # Read the output files and extract the number of bugs
        bugs_count = read_output_files()

        # Sum total number of bugs in each test case folder
        total_bugs = sum(bugs_count)
        print(f"Total number of bugs in iteration {iteration}: {total_bugs}")
        
        # Store the bugs count for this iteration
        iterations_bugs_count[f"Iteration {iteration}"] = total_bugs
        
        # Increment param1 for the next iteration
        param3 += 10

        # If all test cases have 0 bugs, stop further iterations
        # Check if all counts are zero
        if all(count == 0 for count in bugs_count):
            print(f"All test cases have 0 bugs in iteration {iteration}. Stopping further iterations.")
            break

    # Plot the results as a bar chart with 
    # x-axis as total number of bugs in each iteration
    # y-axis as the number of bugs 
    plt.figure(figsize=(20, 6))
    plt.bar(iterations_bugs_count.keys(), iterations_bugs_count.values(), color='skyblue')
    
    # Configure the chart
    plt.xlabel("Iterations")
    plt.ylabel("Total Number of Bugs")
    plt.title("Total Number of Bugs in Each Iteration (Confidence Level Increment)")
    plt.xticks(rotation=45)
    plt.tight_layout()

    # Save the chart to the results directory
    chart_path = os.path.join(results_dir, "total_bugs_count_iterations_chart_ipc_increment.png")
    plt.savefig(chart_path)

    # Shorten the chart path for display
    chart_path = os.path.abspath(chart_path)
    print(f"Chart saved to: /results")

    # Show the chart
    plt.show()

# (1,3,75) parameter run
def package_workflow_1_3_75():
    # Define the selected parameters
    param1 = 1  
    param2 = 3 # This parameter is selected to increment the SUPPORT_LEVEL
    param3 = 75
    print(f"Initial parameters: {param1}, {param2}, {param3}")
    # Dictionary to store bugs count for each test case folder
    iterations_bugs_count = {}
    # No need to loop through 5 iterations
    # Run the clean.sh script to clean the test cases
    run_clean_script()

    # Run the script with the current parameters
    print(f"Running with parameters: {param1}, {param2}, {param3}")
    # Run the script with the current parameters
    run_script(param1, param2, param3)

    # Read the output files and extract the number of bugs
    bugs_count = read_output_files()
    
    # Store the bugs count for this iteration
    iterations_bugs_count[f"Iteration 1"] = bugs_count

    # Plot the results as a line chart
    plt.figure(figsize=(20, 6))
    for iteration, bugs_count in iterations_bugs_count.items():
        plt.plot(range(len(bugs_count)), bugs_count, marker='o', label=iteration)

    # Configure the chart
    plt.xlabel("Test Case Folder")
    plt.ylabel("Number of Bugs")
    plt.title("Number of Bugs in Each Test Case Folder with Parameters (1, 3, 75)")
    plt.xticks(range(len(bugs_count)), os.listdir(test_cases_dir), rotation=90)
    plt.legend()
    plt.tight_layout()
    
    # Edit the legend to be outside the chart
    plt.legend(bbox_to_anchor=(1.05, 1), loc='upper left', borderaxespad=0.)
    plt.subplots_adjust(right=0.85)



    # Save the chart to the results directory
    chart_path = os.path.join(results_dir, "bugs_count_iterations_chart_1_3_75.png")
    plt.savefig(chart_path)

    # Shorten the chart path for display
    chart_path = os.path.abspath(chart_path)
    print(f"Chart saved to: /results")

    # Show the chart
    plt.show()

# Main function
def main():
    # Package the workflow for random parameters method
    # package_workflow()

    print("--------------------------------------------------")
    # Package the workflow for ipc level increment method
    package_workflow_ipc_level_increment()

    print("--------------------------------------------------")
    # Package the workflow for support increment method
    package_workflow_support_level_increment()

    print("--------------------------------------------------")
    # Package the workflow for confidence increment method
    package_workflow_confidence_level_increment()

    print("--------------------------------------------------")
    # Package the workflow for ipc level increment with bar chart
    package_workflow_ipc_level_increment_bar_chart()

    print("--------------------------------------------------")
    # Package the workflow for support increment with bar chart
    package_workflow_support_level_increment_bar_chart()

    print("--------------------------------------------------")
    # Package the workflow for confidence increment with bar chart
    package_workflow_confidence_level_increment_bar_chart()

    # print("--------------------------------------------------")
    # Package the workflow for (1,3,75) parameter run
    package_workflow_1_3_75()

if __name__ == "__main__":
    main()