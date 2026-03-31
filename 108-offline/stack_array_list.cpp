#include <iostream>
#include<string>
using namespace std;

/*
 * ============================================================================
 * STACK OPERATION TIME COMPLEXITY (Array Implementation)
 * ============================================================================
 *
 * Operation                    | Time Complexity | Notes
 * ------------------------------|-----------------|------------------------
 * Push                         | O(1)            | Fixed capacity
 * Pop                          | O(1)            | Remove from top
 * Peek/Top                     | O(1)            | View top element
 * isEmpty                      | O(1)            | Check if empty
 * isFull                       | O(1)            | Check if full
 * Size                         | O(1)            | Current element count
 *
 * KEY INSIGHTS:
 * - LIFO (Last In, First Out) data structure
 * - All operations at one end (top)
 * - Fixed capacity with overflow detection
 * - You can use dynamic resizing to avoid overflow (not implemented here)
 * ============================================================================
 */

class ArrayStack {
    int* data;
    int top;   // Index of next available position
    int capacity; // Initial capacity

public:
    ArrayStack(int capacity = 10) {
        this->capacity = capacity;
        data = new int[capacity];
        top = 0;  // Empty stack
    }

    ~ArrayStack() {
        delete[] data;
    }

    // Check if stack is full
    bool isFull() {
        return top >= capacity;
    }

    // Check if stack is empty
    bool isEmpty() {
        return top == 0;
    }

    // Push element onto stack
    void push(int val) {
        if (isFull()) {
            cout << "Error: Stack overflow!" << endl;
            return;
        }
        data[top++] = val;
    }

    // Pop element from stack
    int pop() {
        if (isEmpty()) {
            cout << "Error: Stack underflow!" << endl;
            return -1;
        }
        return data[--top];
    }

    // Peek at top element without removing
    int peek() {
        if (isEmpty()) {
            cout << "Error: Stack is empty!" << endl;
            return -1;
        }
        return data[top - 1];
    }

    // Get current size
    int size() {
        return top;
    }

    // Print stack contents
    void print() {
        if (isEmpty()) {
            cout << "Stack is empty" << endl;
            return;
        }
        cout << "Stack (top to bottom): ";
        for (int i = top - 1; i >= 0; i--) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    string infix = "(2+3)*4";
    ArrayStack stack(10);
    ArrayStack output(10);
    for(int i=0;i<infix.length();i++){
        char ch = infix[i];
        if(ch =='('){
            stack.push(ch);
        }
        else if(ch==')'){
            
        }
    }
}