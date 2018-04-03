# BplusTree-c-

This is a C++ implementation of [B+ tree](https://en.wikipedia.org/wiki/B%2B_tree) with integer keys and string values.

## Usage
- BpTree.hpp defines the B+ tree data structure.
- BpTree(n) creates a B+ tree with order n.
- BpTree supports insertion, deletion and finding with O(log n) complexity.

## Installation
Copy BpTree.hpp, BpTree.cpp and Node.hpp into your project lib directory.
```bash
# For linux
git clone https://github.com/wymay/BplusTree-c-
cp ./BplusTree-c-/{BpTree.hpp,BpTree.cpp,Node.hpp} /path/to/your/project/lib/
```

## Test
- Install g++ to compile BpTree test program.
- Compile main.cpp for test of BpTree library.
```bash
# For linux
g++ main.cpp BpTree.cpp -o main
./main
```
The test performs 17 insertion and 6 deletion. 
