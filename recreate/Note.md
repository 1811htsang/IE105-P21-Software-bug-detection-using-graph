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

- Main workflow of bug graph detection:
    - Compile to search for basic / exception bugs
    - Identify functions in the program
    - Extract call graph from the program
    - Simplify call graph to minimize
    - Apply graph mining algorithm
    - Analyze and rank function
    - List most highest ranked function as bugs
---

- If someone wants to make test on https://github.com/jkottapa/BugDetector.git, you have to do some extra steps (note: basically about syntax, maybe change due to your location file of clang/opt/llvm and llvm syntax update):
    - change `DEBUG` to 1 in `bugdetector.cpp`
    - change usr/.../opt to `opt -passes=print-callgraph` in `pipair` file.




