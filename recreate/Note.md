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
---

- If someone wants to make test on https://github.com/jkottapa/BugDetector.git, you have to do some extra steps (note: basically about syntax, maybe change due to your location file of clang/opt/llvm and llvm syntax update):
    - change `DEBUG` to 1 in `bugdetector.cpp`
    - change usr/.../opt to `opt -passes=print-callgraph` in `pipair` file.
---

- This folder and sample-project folder are somehow related to method of using likely-invariant to detect bugs in the program. This method is also found in [Automated-Bug-Detection-Tool](https://github.com/cehan-Chloe/Automated-Bug-Detection-Tool), [653-project](https://github.com/Yuzy7/653-Project) and [BugDetector](https://github.com/jkottapa/BugDetector.git) . The author also found some instruction from CS510 course at [here](https://www.coursesidekick.com/computer-science/1408082), although at later found the project instruction in [653-project](https://github.com/Yuzy7/653-Project), branch `Yameng-Li` (for document `IE105-D-12`) and `Yameng-Li-1` (for document `IE105-D-13`). 



