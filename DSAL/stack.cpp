#define MAX 20
#include<iostream>
using namespace std;
template <class T>
class Stack
{
    T stack[MAX];
    int top;

public:
    Stack()
    {
        top = -1;
    }

    bool isFull()
    {
        return top == MAX - 1;
    }

    bool isEmpty()
    {
        return top == -1;
    }

    void push(T x)
    {
        if (isFull())
        {
            cout << "Stack Overflow" << endl;
            return;
        }
        stack[++top] = x;
    }

    T pop()
    {
        if (isEmpty())
        {
            cout << "Stack Underflow" << endl;
            return T(); // Return default value of T
        }
        return stack[top--];
    }

    T showTop()
    {
        if (isEmpty())
        {
            cout << "Stack is empty!" << endl;
            return T(); // Return default value of T
        }
        return stack[top];
    }
};
