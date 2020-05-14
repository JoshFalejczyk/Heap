// Josh Falejczyk: CS201 Data Structures Library Phase 1
#include <iostream>
using namespace std;

template <class elmtype>
class CircularDynamicArray {

public:
    CircularDynamicArray(); // Constructor
    CircularDynamicArray(int s); // Constructor with set size/capacity
    ~CircularDynamicArray(); // Destructor
    CircularDynamicArray(const CircularDynamicArray &src); // Copy constructor
    elmtype& operator[](int i); // Overloaded index operator
    CircularDynamicArray& operator=(const CircularDynamicArray &src) { // Copy assignment operator

        size = src.size;
        cap = src.cap;
        startIndex = 0;
        endIndex = size - 1;
        delete[] array;
        array = new elmtype[src.cap];
        for (int i = 0; i < size; i ++) {
            
            array[i] = src.returnElement(i);
            
        }

        return *this;

    } 
    void addEnd(elmtype v); // Adds element to back
    void addFront(elmtype v); // Adds element to front
    void delEnd(); // Deletes element at back
    void delFront(); // Deletes element at front
    int length(); // Returns size
    int capacity(); // Returns capacity
    void clear(); // Clears space and starts over with an array of size 2
    elmtype QuickSelect(int k); // Uses QuickSelect to find kth smallest element
    elmtype WCSelect(int k); // Uses WCSelect to find kth smallest element
    void stableSort(); // Sorts array using MergeSort
    void radixSort(int i); // Sorts array using two-bucket RadixSort
    int linearSearch(elmtype e); // Linear search of array
    int binSearch(elmtype e); // Binary search of array

private:
    int size; // Size of elements taken up in array
    int cap; // Full capacity of array
    int startIndex; // Start index to implement circularity
    int endIndex; // End index to implement circularity
    elmtype* array; // Array of any type
    elmtype error; // Error variable for overloaded index operator when out of bounds, or blank array space
    void resize(); // Shrinks or grows array based on current size vs capacity
    elmtype returnElement(int i) const; // Acts as overloaded [] operator within class
    void setElement(int i, elmtype elm) const; // Sets elements within array

};

template <class elmtype>
CircularDynamicArray<elmtype>::CircularDynamicArray() { // Constructor

    size = 0;
    cap = 2;
    startIndex = 0;
    endIndex = 0;
    array = new elmtype[cap];

}

template <class elmtype>
CircularDynamicArray<elmtype>::CircularDynamicArray(int s) { // Constructor with set size/capacity

    if (s <= 0) { // endIndex can vary based on s

        endIndex = 0;

    } else {

        endIndex = s - 1;

    }
    size = s;
    cap = s;
    startIndex = 0;
    array = new elmtype[cap];

}

template<class elmtype>
CircularDynamicArray<elmtype>::~CircularDynamicArray() { // Destructor

    delete[] array;

}

template<class elmtype>
CircularDynamicArray<elmtype>::CircularDynamicArray(const CircularDynamicArray &src) { // Copy constructor

    size = src.size; // Copy data over
    cap = src.cap;
    startIndex = src.startIndex;
    endIndex = src.endIndex;
    elmtype* newArray = new elmtype[src.cap];
    delete[] array;
    array = newArray;

}

template <class elmtype>
elmtype& CircularDynamicArray<elmtype>::operator[](int i) { // Overloaded index operator

    if (i >= size || i < 0) { // Out of bounds

        cout << "Out of bounds reference : " << i << endl;
        return this->error;

    } else {

        int newIndex = (startIndex + i) % cap; // Circular formula
        return array[newIndex];

    }

}

template <class elmtype>
void CircularDynamicArray<elmtype>::addEnd(elmtype v) { // Adds element to back

    resize();
    if (size == 0) { // Array is empty

        startIndex = 0;
        endIndex = 0;
        array[0] = v;
        size ++;

    } else {

        endIndex = (endIndex + 1) % cap; // Circular formula
        array[endIndex] = v;
        size ++;

    }

    return;

}

template <class elmtype>
void CircularDynamicArray<elmtype>::addFront(elmtype v) { // Adds element to front

    resize();
    if (size == 0) { // Array is empty

        startIndex = 0;
        endIndex = 0;

    } else if (size > 0 && startIndex == 0) { // StartIndex can vary

        startIndex = cap - 1;

    } else {

        startIndex = (startIndex - 1) % cap;

    }
    array[startIndex] = v;
    size ++;

    return;

}

template <class elmtype>
void CircularDynamicArray<elmtype>::delEnd() { // Deletes element at back

    if (size == 0) { // Array is empty

        startIndex = 0;
        endIndex = 0;

    } else {

        array[endIndex] = error;
        endIndex = (endIndex - 1) % cap; // Circular formula
        size --;
        resize();

    }

    return;

}

template <class elmtype>
void CircularDynamicArray<elmtype>::delFront() { // Deletes element at front

    if (size == 0) { // Array is empty

        startIndex = 0;
        endIndex = 0;

    } else {

        array[startIndex] = error;
        startIndex = (startIndex + 1) % cap; // Circular formula
        size --;
        resize();

    }

    return;

}

template <class elmtype>
int CircularDynamicArray<elmtype>::length() { // Returns size

    return size;

}

template <class elmtype>
int CircularDynamicArray<elmtype>::capacity() { // Returns capacity

    return cap;

}

template <class elmtype>
void CircularDynamicArray<elmtype>::clear() { // Clears space and starts over with an array of size 2

    size = 2;
    cap = 2;
    delete[] array;
    array = new elmtype[cap];

}

template <class elmtype>
elmtype CircularDynamicArray<elmtype>::QuickSelect(int k) { // Uses QuickSelect to find kth smallest element

    if (k < 1 || size < k) { // Position is out of bounds

        cout << "Error: k is not valid" << endl;
        return -1;

    }
    int left = startIndex;
    int right = endIndex;
    while(left < right) { // Subsections of array are valid

        int pivotIndex = (left + right) / 2;
        int pivotVal = returnElement(pivotIndex);
        int temp = left;
        setElement(pivotIndex, returnElement(right));
        setElement(right, pivotVal);
        for (int i = left; i < right; i ++) {

            if (returnElement(i) < pivotVal) {
            
                int temp2 = returnElement(temp); // Swap array[i] and array[temp]
                setElement(temp, returnElement(i));
                setElement(i, temp2);
                temp ++;

            }

        }
        setElement(right, returnElement(temp));
        setElement(temp, pivotVal);

        if (temp < k) { // Move left forward in subsection

            left = temp + 1;

        } else { // Move right back in subsection

            right = temp;

        }

    }

    return returnElement(k);

}

template <class elmtype>
elmtype CircularDynamicArray<elmtype>::WCSelect(int k) { // Uses WCSelect to find kth smallest element

    elmtype* medianArray;
    elmtype* secondArray;
    int minIndex;
    int groupSize = ((array.length() + 4 / 5));
    medianArray = new elmtype[groupSize]; // Holds medians
    for (int i = 0 ; i < groupSize; i ++) { // Go through medianArray

        if ((i * 5) + 4 < array.length()) { // Check for last group

            secondArray = returnElement(i * 5);
            for (int j = 0; j < 3; j ++) {

                minIndex = j; // Index for smallest element of j
                for (int k = j + 1; k < 5; j ++) {

                    if (secondArray[k] < secondArray[minIndex]) { // Check for new minIndex

                        minIndex = k;

                    }
                    elmtype temp = secondArray[j]; // Swapping elements of j and minIndex
                    secondArray[j] = secondArray[minIndex];
                    secondArray[minIndex] = temp;


                }
                medianArray[i] = secondArray[2];

            }

        } else {

            medianArray[i] = returnElement(i * 5);

        }

    }
    
    return returnElement(k);

}

template <class elmtype>
void CircularDynamicArray<elmtype>::stableSort() { // Sorts array using MergeSort

    if (size < 2) { // Array is already sorted

        return;

    }
    int sizeLeft = size / 2;
    int sizeRight = size - sizeLeft;
    int i = 0;
    int iLeft = 0;
    int iRight = 0;
    CircularDynamicArray<elmtype> leftArray(sizeLeft); // Make two new CDA's
    CircularDynamicArray<elmtype> rightArray(sizeRight);

    for (i = 0; i < sizeLeft; i ++) { // Fill leftArray

        leftArray.setElement(i, returnElement(i));

    }
    for (int j = 0; j < sizeRight; j ++) { // Fill rightArray

        rightArray.setElement(j, returnElement(i));
        i ++;

    }
    leftArray.stableSort(); // Recursively sort subarrays
    rightArray.stableSort();

    i = 0;
    while (iLeft < leftArray.length() && iRight < rightArray.length()) { // Resort original CDA in ascending order

        if (leftArray.returnElement(iLeft) < rightArray.returnElement(iRight)) {

            setElement(i, leftArray.returnElement(iLeft));
            i ++;
            iLeft ++;

        } else {

            setElement(i, rightArray.returnElement(iRight));
            i ++;
            iRight ++;

        }

    }
    while (iLeft < leftArray.length()) { // Fill with rest

        setElement(i, leftArray.returnElement(iLeft));
        i ++;
        iLeft ++;

    }
    while (iRight < rightArray.length()) {

        setElement(i, rightArray.returnElement(iRight));
        i ++;
        iRight ++;

    }

    return;

}

template <class elmtype>
void CircularDynamicArray<elmtype>::radixSort(int i) { // Sorts array using two-bucket RadixSort

    elmtype zeroBucket[size]; // Two buckets for 0's and 1's
    elmtype oneBucket[size];
    int zeroIndex;
    int oneIndex;
    for (int j = 0; j < i; j ++) { // Go through until "i-many" bits

        zeroIndex = 0;
        oneIndex = 0;
        for (int k = 0; k < size; k ++) { // Add to buckets

            int compareBit = (returnElement(k)) >> j & 1;
            if (compareBit == 1) { // Bit goes in 1-bucket

                oneBucket[oneIndex] = returnElement(k);
                oneIndex ++;

            } else { // Bit goes in 0-bucket

                zeroBucket[zeroIndex] = returnElement(k);
                zeroIndex ++;

            }

        }
        int resort = 0;
        for (int k = 0; k < zeroIndex; k ++) { // Refill array with 0-bucket

            setElement(resort, zeroBucket[k]);
            resort ++;

        }
        for (int k = 0; k < oneIndex; k ++) { // Refill array with 1-bucket

            setElement(resort, oneBucket[k]);
            resort ++;

        }

    }

    return;

}

template<class elmtype>
int CircularDynamicArray<elmtype>::linearSearch(elmtype e) { // Linear search of array

    for (int i = 0; i < size; i ++) {

        if (returnElement(i) == e) { // Element is found

            return i;

        }

    }

    return -1;

}

template <class elmtype>
int CircularDynamicArray<elmtype>::binSearch(elmtype e) { // Binary search of array

    int left = 0;
    int middle;
    int right = size;
    while (right > left) { // Right and left shink to find e

        middle = (left + right) / 2;
        if (returnElement(middle) == e) { // Element is found

            return middle;

        } else if (returnElement(middle) > e) { // Move right back

            right = middle;

        } else { // Move left forward

            left = middle + 1;

        }


    }

    return -1;

}



template<class elmtype>
void CircularDynamicArray<elmtype>::resize() { // Shrinks or grows array based on current size vs capacity

    if (size >= cap) { // Growing

        elmtype* growArray = new elmtype[cap * 2];
        for (int i = 0; i < size; i ++) { // Refill array

            growArray[i] = returnElement(i);

        }
        cap *= 2;
        array = growArray;
        startIndex = 0;
        endIndex = size - 1;
        return;

    } else if (size > 0 && (cap / 4) >= size) { // Shrinking

        elmtype* shrinkArray = new elmtype[cap / 2];
        for (int i = 0; i < size; i ++) { // Refill array

            shrinkArray[i] = returnElement(i);

        }
        cap /= 2;
        if (cap <= 0) { // Check on cap

            cap = 1;

        }
        delete[] array;
        array = shrinkArray;
        startIndex = 0;
        endIndex = size - 1;

        return;

    }

    return;

}

template <class elmtype>
elmtype CircularDynamicArray<elmtype>::returnElement(int i) const { // Acts as overloaded [] operator within class

    if (i >= size || i < 0) { // Out of bounds

        cout << "Out of bounds reference : " << i << endl;
        return this->error;

    } else {

        int newIndex = (startIndex + i) % cap; // Circular formula
        return array[newIndex];

    }

}

template <class elmtype>
void CircularDynamicArray<elmtype>::setElement(int i, elmtype elm) const { // Sets elements within array

    if (i >= size || i < 0) { // Out of bounds

        cout << "Out of bounds reference : " << i << endl;

    } else {

        array[(startIndex + i) % cap] = elm; // Circular formula

    }

    return;

}