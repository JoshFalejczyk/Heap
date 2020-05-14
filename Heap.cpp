// Josh Falejczyk: CS201 Data Structures Library Phase 3 Heap Class
#include <iostream>
#include "CircularDynamicArray.cpp"
using namespace std;


template <typename keytype, typename valuetype>
class Heap {

    struct Node { // Struct for each node of heap

        valuetype val;
        keytype key;
        Node(keytype key, valuetype val) { // Constructor for Node

            this->key = key;
            this->val = val;

        }

    };

    public:
        Heap(); // Constructor
        Heap(keytype k[], valuetype V[], int s); // Overloaded constructor
        Heap(const Heap &src); // Copy constructor
        Heap& operator=(const Heap &src); // Copy assignment operator
        ~Heap(); // Destructor
        keytype peakKey(); // Returns smallest key without modifying heap
        valuetype peakValue(); // Returns smallest key's value without modifying heap
        keytype extractMin(); // Removes node with smallest key and returns its key
        void insert(keytype k, valuetype v); // Inserts node of key k and value v into heap
        void printKey(); // Print heap in preorder traversal? Or level order?

    private:
        CircularDynamicArray<Node*> array; // Array used to store heap nodes
        keytype error; // Empty error variable to return
        void heapify(int pos); // Resorts array in min-heap order
        
};

template <typename keytype, typename valuetype>
Heap<keytype, valuetype>::Heap() { // Constructor

    CircularDynamicArray<Node*> array; // Unsure if necessary, just in case

}

template <typename keytype, typename valuetype>
Heap<keytype, valuetype>::Heap(keytype k[], valuetype V[], int s) { // Overloaded constructor

    for (int i = 0; i < s; i ++) { // Create CDA of non-heap order

        Node* n = new Node(k[i], V[i]);
        array.addEnd(n);

    }
    for (int j = array.length() / 2; j >= 0; j --) { // Heapify CDA

        heapify(j);

    }

}

template <typename keytype, typename valuetype>
Heap<keytype, valuetype>::Heap(const Heap &src) { // Copy constructor

    array = src.array;

}

template <typename keytype, typename valuetype>
Heap<keytype, valuetype>& Heap<keytype, valuetype>::operator=(const Heap<keytype, valuetype> &src) { // Copy assignment operator

        if (this != &src) { // Prevents self-assignment

            array = src.array;

        }

        return *this;

}

template <typename keytype, typename valuetype>
Heap<keytype, valuetype>::~Heap() { // Destructor

    // Destructor is handled by CDA's destructor

}

template <typename keytype, typename valuetype>
keytype Heap<keytype, valuetype>::peakKey() { // Returns smallest key without modifying heap

    return array[0]->key; // By min-order, smallest key will always be first element of CDA

}

template <typename keytype, typename valuetype>
valuetype Heap<keytype, valuetype>::peakValue() { // Returns smallest key's value without modifying heap

    return array[0]->val; // By min-order, smallest key will always be first element of CDA

}

template <typename keytype, typename valuetype>
keytype Heap<keytype, valuetype>::extractMin() { // Removes node with smallest key and returns its key

    if (array.length() <= 0) { // Check for if Heap is empty

        cout << "Error: Heap is empty" << endl;
        return error; // Empty error variable to keep return type consistent

    }
    keytype k = array[0]->key;
    Node* temp;
    temp = array[0];
    array[0] = array[array.length() - 1]; // Swap first and last elements of CDA
    array[array.length() - 1] = temp;
    array.delEnd(); // Remove minNode
    if (array.length() > 1) { // Heapify CDA to restore min-heap order

        heapify(0);

    }
    
    return k;

}

template <typename keytype, typename valuetype>
void Heap<keytype, valuetype>::insert(keytype k, valuetype v) { // Inserts node of key k and value v into heap

    Node* n = new Node(k, v);
    array.addEnd(n); // Add new node to CDA

    if (array.length() > 1) {

        int i = array.length() - 1;
        Node* temp;
        while (i > 0 && array[(i - 1) / 2]->key > array[i]->key) { // Bubbling new node up to restore min-heap order

            temp = array[i];
            array[i] = array[(i - 1) / 2];
            array[(i - 1) / 2] = temp;
            i = (i - 1) / 2;

        }

    }

    return;

}

template <typename keytype, typename valuetype>
void Heap<keytype, valuetype>::printKey() { // Print heap in level-order traversal

    
    for (int i = 0; i < array.length(); i ++) { // Go through CDA and print iteratively

        cout << array[i]->key << " ";

    }
    cout << endl;

    return;

}

template <typename keytype, typename valuetype>
void Heap<keytype, valuetype>::heapify(int pos) { // Resorts array in min-heap order

    int root;
    int left;
    int right;
    while (pos < array.length()) { // Heapifying CDA with HeapSort

        root = pos;
        left = (2 * pos) + 1; // Left child
        right = (2 * pos) + 2; // Right child
        if (left < array.length() && array[left]->key < array[pos]->key) {

            root = left;

        }
        if (right < array.length() && array[right]->key < array[root]->key) {

            root = right;

        }
        if (root == pos) { // End preemptively if possible

            return;

        }
        Node* temp; // Swap root with either left or right child
        temp = array[pos];
        array[pos] = array[root];
        array[root] = temp;
        pos = root;

    }

    return;

}