#include <iostream>
#include <climits>
using namespace std;

void swap(int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

class MinHeap {
    int *array;
    int max_size;
    int current_size;
public:
    MinHeap(int size);

    void min_heapify(int );

    int parent(int idx) {return (idx - 1) / 2;}
    int left(int idx) {return (2 * idx + 1);}
    int right(int idx) {return (2 * idx + 2);}

    int extract_min();

    void decrease_key(int idx, int value);

    int get_min() {return array[0];}

    void delete_key(int idx);

    void insert_key(int key);
};

// constructor
MinHeap::MinHeap(int size) {
    current_size = 0;
    max_size = size;
    array = new int[size];
}

// insert a new key
void MinHeap::insert_key(int key) {
    if (current_size == max_size) {
        cout << "\nOverflow. Could not insert key\n";
        return;
    }

    current_size++;
    int idx = current_size - 1;
    array[idx] = key;

    while (idx != 0 && array[parent(idx)] > array[idx]) {
        swap(&array[idx], &array[parent(idx)]);
        idx = parent(idx);
    }
}

// recursive method to heapify a subtree with root at given index
void MinHeap::min_heapify(int idx) {
    int l_idx = left(idx);
    int r_idx = right(idx);
    int smallest_idx = idx;

    if (l_idx < current_size && array[l_idx] < array[idx]) {
        smallest_idx = l_idx;
    }
    if (r_idx < current_size && array[r_idx] < array[smallest_idx]) {
        smallest_idx = r_idx;
    }
    if (smallest_idx != idx) {
        swap(&array[idx], &array[smallest_idx]);
        min_heapify(smallest_idx);
    }
}

// decrease value of key at idx to new value
void MinHeap::decrease_key(int idx, int value) {
    array[idx] = value;
    while (idx != 0 && array[parent(idx)] > array[idx]) {
        swap(&array[idx], &array[parent(idx)]);
        idx = parent(idx);
    }
}

// remove minimum element or root from min heap
int MinHeap::extract_min() {
    // empty
    if (current_size <= 0) {
        return INT_MAX;
    }
    // only root
    if (current_size == 1) {
        current_size--;
        return array[0];
    }

    int root = array[0]; // minimum value
    array[0] = array[current_size - 1];
    current_size--;
    min_heapify(0);

    return root;
}

// delete key at idx
void MinHeap::delete_key(int idx) {
    decrease_key(idx, INT_MIN);
    extract_min();
}

int main() {
    MinHeap heap(11);
    heap.insert_key(3);
    heap.insert_key(2);
    heap.delete_key(1);
    heap.insert_key(15);
    heap.insert_key(5);
    heap.insert_key(4);
    heap.insert_key(45);

    cout << heap.extract_min() << " ";
    cout << heap.get_min() << " ";
    heap.decrease_key(2, 1);
    cout << heap.get_min() << " ";

    return 0;
}
