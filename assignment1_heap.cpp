#include <iostream>

using namespace std;

class MaxHeap {
   private:
    int _MAXSIZE;                         // Maximum size of the heap.
    int _heapSize;                        // Current size of the heap.
    int* _heap;                           // Pointer to dynamically allocated heap array.
    int __parent(int i);                  // Get parent index of node at index i.
    int __left(int i);                    // Get left child index of node at index i.
    int __right(int i);                   // Get right child index of node at index i.
    void __swap(int index1, int index2);  // Swap two elements in the heap.

   public:
    MaxHeap();                               // Default consturctor.
    MaxHeap(int MAXSIZE);                    // Constructor with user defined maximum size.
    MaxHeap(int* nums, int n);               // Consturctor with array of numbers and its size.
    MaxHeap(int* nums, int n, int MAXSIZE);  // Consturctor with array of numbers and its size and user defined maximum size.
    int getHeapSize();                       // To get the current size of the heap. Only needed when determinig size of the array after int* heapSort().
    void maxHeapify(int index);              // Maintains heap property of the subtree rooted at index.
    void buildMaxHeap();         // Builds Max Heap given the size of the array.
    int extractMaxElement();                 // Returns the maximum element from the heap.
    void deleteFromMaxHeap();                // Deletes the maximum element from the heap. Returns nothing.
    void insert(int element);                // Inserts an element in the heap. Maintains Heap property.
    void heapSort(int* nums, int n);         // Perform heapsort on an array. Return sorted array in ascending order.
    int* heapSort();                         // Sort current heap elements in-place in ascending order.
    void printHeap();                        // Helper function to print the heap elements.
};

MaxHeap::MaxHeap() {
    _heapSize = 0;
    _MAXSIZE = 100;
    _heap = new int[_MAXSIZE];
    cout << "Constructor : Empty Heap initialized with MAXSIZE = " << _MAXSIZE << "\n";
}

MaxHeap::MaxHeap(int MAXSIZE) {
    _heapSize = 0;
    _MAXSIZE = MAXSIZE;
    _heap = new int[_MAXSIZE];
    cout << "Constructor : Empty Heap initialized with MAXSIZE = " << _MAXSIZE << "\n";
}

MaxHeap::MaxHeap(int* nums, int n) {
    _MAXSIZE = 100;
    _heap = new int[_MAXSIZE];
    if (n == 0) {
        _heapSize = 0;
        cout << "Constructor : Empty Heap initialized with MAXSIZE = " << _MAXSIZE << "\n";
    } else if (n > _MAXSIZE) {
        cout << "MAXHEAP Size reached : MAXSIZE = " << _MAXSIZE << "\nUse MaxHeap(int* nums, int n, int MAXSIZE) instead.\n";
    } else {
        for (int i = 0; i < n; i++) {
            _heap[i] = nums[i];
        }
        _heapSize = n;
        buildMaxHeap();
        cout << "Constructor : MaxHeap with " << n << " elements created.\n";
    }
}

MaxHeap::MaxHeap(int* nums, int n, int MAXSIZE) {
    _MAXSIZE = MAXSIZE;
    _heap = new int[_MAXSIZE];
    if (n == 0) {
        _heapSize = 0;
        cout << "Constructor : Empty Heap initialized with MAXSIZE = " << _MAXSIZE << "\n";
    } else if (n > _MAXSIZE) {
        cout << "MAXHEAP Size reached : MAXSIZE = " << _MAXSIZE << "\n";
    } else {
        for (int i = 0; i < n; i++) {
            _heap[i] = nums[i];
        }
        _heapSize = n;
        buildMaxHeap();
        cout << "Constructor : MaxHeap with " << n << " elements created.\n";
    }
}

int MaxHeap::__parent(int index) { return (index - 1) >> 1; }

int MaxHeap::__left(int index) { return (index << 1) + 1; }

int MaxHeap::__right(int index) { return (index << 1) + 2; }

void MaxHeap::__swap(int index1, int index2) {
    int temp = _heap[index1];
    _heap[index1] = _heap[index2];
    _heap[index2] = temp;
}

int MaxHeap::getHeapSize() { return _heapSize; }

void MaxHeap::maxHeapify(int index) {
    int largest;
    int left = __left(index);
    int right = __right(index);

    largest = ((left < _heapSize) && (_heap[left] > _heap[index])) ? left : index;
    largest = ((right < _heapSize) && (_heap[right] > _heap[largest])) ? right : largest;
    if (largest != index) {
        __swap(index, largest);
        maxHeapify(largest);
    }
}

void MaxHeap::buildMaxHeap() {
    if (_heapSize == 0) {
        cout << "buildMaxHeap(int heapSize) : Empty Heap!\n";
    } else {
        for (int index = (_heapSize >> 1) - 1; index >= 0; index--) {
            maxHeapify(index);
        }
    }
}

int MaxHeap::extractMaxElement() {
    if (_heapSize < 1) {
        cout << "extractMaxElement() : Heap Underflow\n";
        return -1;
    } else {
        return _heap[0];
    }
}

void MaxHeap::deleteFromMaxHeap() {
    if (_heapSize < 1) {
        cout << "deleteFromMaxHeap() : Heap Underflow\n";
    } else {
        _heap[0] = _heap[_heapSize - 1];
        _heapSize--;
        maxHeapify(0);
    }
}

void MaxHeap::insert(int element) {
    if (_heapSize + 1 > _MAXSIZE) {
        cout << "insert(int element) : Heap Overflow : MAXSIZE reached.\n";
    } else {
        _heap[_heapSize] = element;
        int index = _heapSize;
        while ((index > 0) && _heap[__parent(index)] < _heap[index]) {
            __swap(index, __parent(index));
            index = __parent(index);
        }
        _heapSize++;
    }
}

void MaxHeap::heapSort(int* nums, int n) {
    _heap = nums;
    _heapSize = n;
    buildMaxHeap();
    for (int index = _heapSize - 1; index > 0; index--) {
        __swap(0, index);
        _heapSize--;
        maxHeapify(0);
    }
    _heapSize = n;
}

int* MaxHeap::heapSort() {
    int* sorted = new int[_heapSize];
    for (int i = 0; i < _heapSize; i++) {
        sorted[i] = _heap[i];
    }
    int n = _heapSize;
    // buildMaxHeap();
    for (int index = _heapSize - 1; index > 0; index--) {
        __swap(0, index);
        _heapSize--;
        maxHeapify(0);
    }
    _heapSize = n;
    for (int i = 0; i < _heapSize; i++) {
        int temp = _heap[i];
        _heap[i] = sorted[i];
        sorted[i] = temp;
    }
    return sorted;
}

void MaxHeap::printHeap() {
    if (_heapSize == 0) {
        cout << "printHeap() : Empty Heap!\n";
    } else {
        for (int i = 0; i < _heapSize; i++) {
            cout << _heap[i] << " ";
        }
        cout << "\n";
    }
}

int main() {
    int clrs_example[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    // int clrs_example[] = {100, 90, 85, 70, 60, 55, 40, 30, 20, 10};
    // int clrs_example[] = {100};
    // int clrs_example[] = {};
    int n = sizeof(clrs_example) / sizeof(clrs_example[0]);
    // MaxHeap h;
    // h.heapSort(clrs_example, n);
    // for (int i = 0; i < n; i++) {
    //     cout << clrs_example[i] << " ";
    // }
    MaxHeap h(clrs_example, n);
    // cout << h.extractMaxElement() << "\n";
    // h.deleteFromMaxHeap();
    // h.insert(120);
    int* test = h.heapSort();
    for (int i = 0; i < h.getHeapSize(); i++) {
        cout << test[i] << " ";
    }
    // h.printHeap();

    return 0;
}