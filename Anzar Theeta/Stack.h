#pragma once


template <class T>
class Stack
{
private:
	T* arr;
	int stkptr;
	int maxSize;
public:
	Stack(int size = 20)
	{
		maxSize = size;
		arr = new T[maxSize];
		stkptr = 0;
	}
	bool isFull()
	{
		return (stkptr == maxSize);
	}
	bool isEmpty()
	{
		return (stkptr == 0);
	}
	bool push(const T& d)
	{
		if (!isFull()) 
		{
			arr[stkptr] = d;
			stkptr++;
			return true;
		}
		return false;
	}
	bool pop()
	{
		if (!isEmpty()) {
			stkptr--;
		}
		return true;
	}
	bool top(T& d)
	{
		if (!isEmpty()) {
			d = arr[stkptr - 1];
			return true;
		}
		return false;
	}
	int size()
	{
		return stkptr;
	}
	void removeAll()
	{
		stkptr = 0;
	}
	void print()
	{
		for (int i = 0; i < stkptr; i++) {
			cout << arr[i] << '\n';
		}
	}
};