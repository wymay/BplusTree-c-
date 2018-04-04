# BplusTree-c-

This is a C++ implementation of [B+ tree](https://en.wikipedia.org/wiki/B%2B_tree) with integer keys and string values.

## Installation
Copy BpTree.hpp, BpTree.cpp and Node.hpp into your project lib directory.
```bash
# For linux
git clone https://github.com/wymay/BplusTree-c-
cp ./BplusTree-c-/{BpTree.hpp,BpTree.cpp,Node.hpp} /path/to/your/project/lib/
```

## Usage
- BpTree.hpp defines the APIs of B+ tree data structure.
- BpTree supports insertion, deletion and finding with O(log n) complexity.

### APIs
- BpTree(int) – this constructor creates an empty tree, the parameter sets the number of keys that can be stored in each node (leaf and interior)

- void insert(int, string) – inserts the key (int) and value (string) into the tree

- void remove(int) – searches the tree for the key (int), if found removes the key and associated value from the tree

- string find(int) – searches the tree for the key (int), if found returns the matching value

- void printKeys() – prints the keys in each node with nodes of the same level appearing on the same line

- void printValues() – prints the values in key (not value) order

### Example

```cpp
BpTree btree(3);
btree.insert(17, "value=17");
btree.insert(10, "value=10");
btree.insert(27, "value=27");
btree.insert(28, "value=28");
btree.printKeys();

/* output 
	[17]
	[10, 17], [27, 28]
*/
```

## Limitations
- This B+ Tree implementation doesn't deal with duplicated keys.



## Test
- Use g++ to compile BpTree test program.
- Compile main.cpp to test BpTree library.
```bash
# For linux
g++ main.cpp BpTree.cpp -o main
./main
```
The test performs 17 insertion and 6 deletion. 
