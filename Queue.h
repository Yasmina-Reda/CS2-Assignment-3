#pragma once

template <class T>

class Queue {
private:
	int front;
	int rear;
	int count;
	int maxSize;
	T* ptr;
public:
	Queue(int);
	~Queue();
	bool isFull();
	bool isEmpty();
	void push(T);
	void pop(T&); //void here because T is generic and so I do not know what to return if failed to pop
};

#include "Queue.cpp" //note to self: don't forget to always #include .cpp at the end
