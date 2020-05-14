# Heap

This was a project from Fall 2019 for my CS201 class.  It is a C++ implementation of a standard binary MinHeap, built using a dynamic array class I also wrote.  The data within the Heap is represented by Nodes that contains both keys and data values, and a variety of functions are included in Heap.cpp for analysis of the data structure.

Functions/Usage: 
1. Constructor (constructor for Heap object, plus an optional overloaded constructor for preloaded data)
2. Insert (Inserts a Node into the Heap)
3. Extract Min (Removes and returns the minimum key in the Heap)
4. Peak Key (Returns the minimum key in the Heap without modifying the Heap structure)
5. Peak Value (Returns the data value of the Node with the minimum key in the Heap without modifying the Heap structure)
6. Heapify (resorts the array for the Heap in MinHeap structure)
7. Print Key (outputs the keys associated with the Heap in a level-order traversal)

Credit: 
1. The concept for the project and 201MainPhase3Heap.cpp test runner file were written and supplied by my professor, Dr. Brandon Dixon.
2. The CircularDynamicArray.cpp and Heap.cpp files, plus the Makefile, were written by myself.
