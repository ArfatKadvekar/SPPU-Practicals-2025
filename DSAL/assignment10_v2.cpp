#include <iostream>
using namespace std;

const int MAX_SIZE = 100;

class HeapSort {
private:
    int arr[MAX_SIZE];
    int size;

    void heapify(int n, int i) {
        int largest = i;          // Initialize largest as root
        int left = 2 * i + 1;     // left child index
        int right = 2 * i + 2;    // right child index

        // If left child is larger than root
        if (left < n && arr[left] > arr[largest])
            largest = left;

        // If right child is larger than largest so far
        if (right < n && arr[right] > arr[largest])
            largest = right;

        // If largest is not root
        if (largest != i) {
            swap(arr[i], arr[largest]);
            heapify(n, largest); // Recursively heapify the affected sub-tree
        }
    }

public:
    void inputArray() {
        cout << "Enter number of elements: ";
        cin >> size;
        cout << "Enter elements:\n";
        for (int i = 0; i < size; i++) {
            cin >> arr[i];
        }
    }

    void buildMaxHeap() {
        // Build max-heap from bottom non-leaf nodes
        for (int i = size / 2 - 1; i >= 0; i--) {
            heapify(size, i);
        }
    }

    void sortDescending() {
        buildMaxHeap();

        // One by one extract elements
        for (int i = size - 1; i > 0; i--) {
            swap(arr[0], arr[i]);     // Move current root to end
            heapify(i, 0);            // call heapify on the reduced heap
        }
    }

    void displaySortedArray() {
        cout << "Sorted array (Ascending): ";
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    HeapSort hs;
    hs.inputArray();
    hs.sortDescending();
    hs.displaySortedArray();

    return 0;
}
