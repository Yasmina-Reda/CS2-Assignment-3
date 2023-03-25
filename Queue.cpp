#include "Queue.h"
#include <iostream>
using namespace std;

template <class T>

Queue<T>::Queue(int size)
{
	maxSize = size;
	count = 0;
	front = 0;
	rear = -1; //note to self: not zero because no element exists at index zero yet
	ptr = new T[maxSize];
}

template <class T>

bool Queue<T>::isEmpty() {
	return count == 0;
}

template <class T>

bool Queue<T>::isFull() {
	return count == maxSize;
}

template <class T>

void Queue<T>::push(T temp) {
	if (!isFull()) 
	{
		rear = (++rear % maxSize);
		*(ptr + rear) = temp;
		count++;
	}
	else cout << "\nError! Queue is Full. Cannot push";
	
}

template <class T>

void Queue<T>::pop(T& temp)
{
	if (!isEmpty())
	{
		temp = *(ptr + front);
		front = (++front % maxSize);
		count--;
	}
	else cout << "\nError! Queue is Empty. Nothing to pop";
}

template <class T>

Queue<T>::~Queue()
{
	delete[]ptr;
}
