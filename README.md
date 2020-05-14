# Min-Heap

This was a project from Fall 2019 for my CS201 class.  It is a C++ implementation of a standard binary Min-Heap, built using a dynamic array class I also wrote.  The data within the Heap is represented by Nodes that contains both keys and data values, and a variety of functions are included in Heap.cpp for analysis of the data structure.

Functions/Usage: 
1. Constructor (constructor for Heap object, plus an optional overloaded constructor for preloaded data)
2. Insert (inserts a Node into the Heap)
3. Extract Min (removes and returns the minimum key in the Heap)
4. Peak Key (returns the minimum key in the Heap without modifying the Heap structure)
5. Peak Value (returns the data value of the Node with the minimum key in the Heap without modifying the Heap structure)
6. Heapify (resorts the array for the Heap in Min-Heap structure)
7. Print Key (outputs the keys associated with the Heap in a level-order traversal)
8. Copy Constructor/Copy Assignment Operator (included for good practice of dynamic memory allocation)
9. Destructor (properly frees manually allocated memory within Heap)

To Run:
1. Compile using "make" or "g++ -Wall 201MainPhase3Heap.cpp".
2. Run using "./phase3" for the former compilation command, or "./a.exe" (or "./a.out" if on Mac) for the latter.

Credit: 
1. The concept for the project and 201MainPhase3Heap.cpp test runner file were written and supplied by my professor, Dr. Brandon Dixon.
2. The CircularDynamicArray.cpp and Heap.cpp files, plus the Makefile, were written by myself.
