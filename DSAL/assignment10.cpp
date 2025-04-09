#include <iostream>
using namespace std;

const int MAX_SIZE = 100;

class MaxHeap {
private:
    int heap[MAX_SIZE];
    int n;

public:
    MaxHeap() {
        n = 0;
    }

    void insert(int x) {
        if (n >= MAX_SIZE - 1) {
            cout << "Heap is full\n";
            return;
        }
        n++;
        int i = n;
        while (i > 1 && x > heap[i / 2]) {
            heap[i] = heap[i / 2];
            i = i / 2;
        }
        heap[i] = x;
    }

    int deleteMax() {
        if (n < 1) {
            cout << "Heap is empty\n";
            return -1;
        }
        int x = heap[1];
        int k = heap[n--];
        int i = 1, j = 2;

        while (j <= n) {
            if (j < n && heap[j] < heap[j + 1]) {
                j++;
            }
            if (k >= heap[j]) break;
            heap[i] = heap[j];
            i = j;
            j = 2 * j;
        }
        heap[i] = k;
        return x;
    }

    int getMax() {
        return (n >= 1) ? heap[1] : -1;
    }

    bool isEmpty() {
        return n < 1;
    }
};

class MinHeap {
private:
    int heap[MAX_SIZE];
    int n;

public:
    MinHeap() {
        n = 0;
    }

    void insert(int x) {
        if (n >= MAX_SIZE - 1) {
            cout << "Heap is full\n";
            return;
        }
        n++;
        int i = n;
        while (i > 1 && x < heap[i / 2]) {
            heap[i] = heap[i / 2];
            i = i / 2;
        }
        heap[i] = x;
    }

    int deleteMin() {
        if (n < 1) {
            cout << "Heap is empty\n";
            return -1;
        }
        int x = heap[1];
        int k = heap[n--];
        int i = 1, j = 2;

        while (j <= n) {
            if (j < n && heap[j] > heap[j + 1]) {
                j++;
            }
            if (k <= heap[j]) break;
            heap[i] = heap[j];
            i = j;
            j = 2 * j;
        }
        heap[i] = k;
        return x;
    }

    int getMin() {
        return (n >= 1) ? heap[1] : -1;
    }

    bool isEmpty() {
        return n < 1;
    }
};

int main() {
    int n;
    cout << "Enter number of students: ";
    cin >> n;

    int marks[MAX_SIZE];
    cout << "Enter marks of students:\n";
    for (int i = 0; i < n; i++) {
        cin >> marks[i];
    }

    MaxHeap maxHeap;
    MinHeap minHeap;

    for (int i = 0; i < n; i++) {
        maxHeap.insert(marks[i]);
        minHeap.insert(marks[i]);
    }

    cout << "\n--- Results ---\n";
    cout << "Maximum Marks: " << maxHeap.getMax() << endl;
    cout << "Minimum Marks: " << minHeap.getMin() << endl;

    cout << "Marks in Descending Order: ";
    while (!maxHeap.isEmpty()) {
        cout << maxHeap.deleteMax() << " ";
    }
    cout << endl;

    cout << "Marks in Ascending Order: ";
    while (!minHeap.isEmpty()) {
        cout << minHeap.deleteMin() << " ";
    }
    cout << endl;

    return 0;
}