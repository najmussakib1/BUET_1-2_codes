#ifndef MINHEAP_H
#define MINHEAP_H

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <climits>

#define MAX_CAPACITY 1000  // Defines the maximum capacity of the heap

class MinHeap
{
private:
    int heap[MAX_CAPACITY];  // Array to store heap elements
    int size;                // Current number of elements in the heap

    /**
     * Sifts up the node at index i to maintain heap property.
     */
    void siftUp(int i)
    {
        /**Write your code here**/
        while (i > 0)
        {
            int parent = (i - 1) / 2;
            if (heap[parent] > heap[i])
            {
                std::swap(heap[parent], heap[i]);
                i = parent;
            }
            else{
                break;
            }
        }
    }

    /**
     * Sifts down the node at index i to maintain heap property.
     */
    void siftDown(int i)
    {
        /**Write your code here**/
        while (true)
        {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int smallest = i;

            if (left < size && heap[left] < heap[smallest]){
                smallest = left;
            }

            if (right < size && heap[right] < heap[smallest]){
                smallest = right;
            }

            if (smallest != i)
            {
                std::swap(heap[i], heap[smallest]);
                i = smallest;
            }
            else{
                break;
            }
        }
    }

public:
    // Constructor initializes an empty heap
    MinHeap() : size(0) {}

    /**
     * Inserts a new element x into the heap.
     */
    void insert(int x)
    {
        /**Write your code here**/
        if (size == MAX_CAPACITY){
            std::cerr<<"Heap is full. Cannot insert new element."<<std::endl;
            return;
        }

        heap[size] = x;
        size++;
        siftUp(size - 1);
    }

    /**
     * Returns the minimum element without removing it.
     */
    int findMin()
    {
        /**Write your code here**/
        if(size==0){
            std::cerr<<"Heap is empty. No minimum element."<<std::endl;
            return INT_MIN;
        }
        return heap[0];
    }

    /**
     * Removes and returns the minimum element from the heap.
     */
    int extractMin()
    {

        /**Write your code here**/
        if(size==0){
            std::cerr<<"Heap is empty. No minimum element to extract."<<std::endl;
            return INT_MIN;
        }
        int minElement = heap[0];
        heap[0] = heap[size - 1];
        size--;
        siftDown(0);
        return minElement;
    }

    /**
     * Returns the number of elements in the heap.
     */
    int getSize()
    {
        /**Write your code here**/
        return size;
    }

    /**
     * Checks if the heap is empty.
     * Returns true if empty, false otherwise.
     */
    bool isEmpty()
    {
        /**Write your code here**/
        return size==0;
    }

    /**
     * Decreases the value of the element at index i to newValue.
     */
    void decreaseKey(int i, int newValue)
    {
        /**Write your code here**/
        if(i < 0 || i >= size){
            std::cerr<<"Index out of bounds. Cannot decrease key."<<std::endl;
            return;
        }
        heap[i] = newValue;
        siftUp(i);
    }

    /**
     * Deletes the element at index i.
     */
    void deleteKey(int i)
    {
        /**Write your code here**/
        if(i < 0 || i >= size){
            std::cerr<<"Index out of bounds. Cannot delete key."<<std::endl;
            return;
        }
        decreaseKey(i, INT_MIN);
        extractMin();
    }

    /**
     * Prints the heap's content to the output file.
     * Format: "elem1 elem2 elem3 ..." (space-separated)
     */
    void printHeap(std::ofstream &outfile)
    {
        /**Write your code here**/
        for (int i = 0; i < size; i++)
        {
            outfile << heap[i];
            if(i!=size-1){
                outfile<<" ";
            }
        }
        outfile << std::endl;
    }

    /**
     * Checks whether the Min Heap property is preserved.
     * Returns true if valid, false otherwise.
     */
    bool isValidMinHeap()
    {
        /**Write your code here**/
        for(int i=0;i<size;i++){
            int left = 2*i+1;
            int right = 2*i+2;
            if(left < size && heap[i] > heap[left]){
                return false;
            }
            if(right < size && heap[i] > heap[right]){
                return false;
            }
        }
        return true;
    }

    /**
     * Builds a heap from an unsorted array using bottom-up heapify.
     */
    void heapify(int arr[], int n)
    {
        /**Write your code here**/
        if(n > MAX_CAPACITY){
            std::cerr<<"Input array exceeds maximum heap capacity."<<std::endl;
            return;
        }
        size =n;
        for(int i=0;i<n;i++){
            heap[i] = arr[i];
        }
        for(int i=(n/2)-1;i>=0;i--){
            siftDown(i);
        }
    }

    /**
     * Returns all elements in sorted (ascending) order.
     * The original heap should remain UNCHANGED after this operation.
     */
    void heapSort(std::ofstream &outfile)
    {
        /**Write your code here**/
        MinHeap temp = *this;
        while(!temp.isEmpty()){
            int minElement = temp. extractMin();
            outfile << minElement;
            if(!temp.isEmpty()){
                outfile<<" ";
            }
        }
        outfile << std::endl;
    }

    /**
     * Replaces the minimum element with a new value x in a single operation.
     * Returns the old minimum value.
     */
    int replaceMin(int x)
    {
        /**Write your code here**/
        if(size==0){
            std::cerr<<"Heap is empty. No minimum element to replace."<<std::endl;
            return INT_MIN;
        }
        int old = heap[0];
        heap[0] = x;
        siftDown(0);
        return old;
    }
};

#endif // MINHEAP_H
