- To convert `C/C++` file to `bitcode` file, use `clang/clang++` below:
```bash
# Used for C file
clang -emit-llvm -c filename.c -o filename.bc
# Used for C++ file
clang++ -emit-llvm -c filename.cpp -o filename.bc
```
---

- To extract call graph from `bitcode` file, use `opt` with `print-callgraph` below:
```bash
opt -passes=print-callgraph filename.bc
```

---

(this thing is not sure to extract execution trace from compiled file, but maybe still useful)
- To extract execution trace from compiled file, use `perf` below:
```bash
perf record ./filename
```
- Also, must remember to add `-g` option when compiling the file to get the debug information:
```bash
gcc -g filename.c -o filename
```
```bash
g++ -g filename.cpp -o filename
```

---

- Main workflow of bug graph detection:
    - Compile to search for basic / exception bugs
    - Identify functions in the program
    - Extract call graph from the program
    - Simplify call graph to minimize
    - Apply interprocedural analysis and likely invariant analysis
    - Generate likely invariant
    - Analyze like invariant to find bugs
    - Generate bug report
    - Test with different levels of IPC (Interprocedural Analysis), support and confidence (maybe not needed or must to do this step to get the result in the shape of chart or graph).
---

- If someone wants to make test on https://github.com/jkottapa/BugDetector.git, you have to do some extra steps (note: basically about syntax, maybe change due to your location file of clang/opt/llvm and llvm syntax update):
    - change `DEBUG` to 1 in `bugdetector.cpp`
    - change usr/.../opt to `opt -passes=print-callgraph` in `pipair` file.
---

- Due to valgrind output the result into the standard error output `stderr`, so you have to redirect the output to a file and then read the file to get the result. You can use `2>` to redirect the standard error output to a file.
- For example:
```bash
valgrind --tool=memcheck ./filename &>> valgrind_output.txt
```
---

- This folder and sample-project folder are somehow related to method of using likely-invariant to detect bugs in the program. This method idea is also found in related repository from University of Waterloo and Purdue Univeristy, especially from prof Lin Tan as follow [Automated-Bug-Detection-Tool](https://github.com/cehan-Chloe/Automated-Bug-Detection-Tool), [653-project](https://github.com/Yuzy7/653-Project) and [BugDetector](https://github.com/jkottapa/BugDetector.git), [BugDetectionTool](https://github.com/ileb325/BugDetectionTool), [Software-Testing-Quality-Assurance-and-Maintenance](https://github.com/sai-teja-ponugoti/Software-Testing-Quality-Assurance-and-Maintenance), [ECE-653](https://github.com/Kyxie/ECE-653), [se465-project](https://github.com/pmlakner/se465-project/) . The author also found some instruction from CS510 course at [here](https://www.coursesidekick.com/computer-science/1408082), although at later found the project instruction in [653-project](https://github.com/Yuzy7/653-Project) (branch `Yameng-Li` for document `IE105-D-12` and `Yameng-Li-1` for document `IE105-D-13`) and [se465-project](https://github.com/pmlakner/se465-project/). 

---

- This folder contains dataset related from [bugnet](https://huggingface.co/datasets/alexjercan/bugnet) and self-generated from example of `IE105-D-12` and `IE105-D-13` (the author is not sure about the dataset, but it is used to test the tool so maybe it is still acceptable). God bless the author. There is also a .zip dataset named `NIST-Juliet-Cpp-Test-Suite-2017` located in this folder, but it is not used in the project due to some issue and uncertainty about the dataset platform so it has been removed. 



