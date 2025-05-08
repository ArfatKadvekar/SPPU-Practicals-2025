#include<iostream>
using namespace std;

const int MAX_SIZE = 100;

class MaxHeap{
    int heap[MAX_SIZE];
    int n;
public: 
    void insert(int temp){
        if(temp>= MAX_SIZE - 1){
            cout << "Heap is Empty\n";
            return;
        }
        n++;
        int i = n;
        while(i > 1 && temp > heap[i/2]){
            heap[i] = heap[i/2];
            i = i/2;
        }
        heap[i] = temp;
    }
};