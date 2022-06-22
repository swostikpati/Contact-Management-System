#ifndef myvector_H
#define myvector_H

#include <iostream>
#include "contact.h"
using namespace std;

//reference lab7
template <typename T>
class MyVector
{
private:
	T *data;		// pointer to int(array) to store elements
	int v_size;		// current size of vector (number of elements in vector)
	int v_capacity; // capacity of vector
public:
	MyVector();		   // No argument constructor
	MyVector(int cap); // One Argument Constructor
	~MyVector();	   // Destructor
	// T &operator[](int index);
	void push_back(T element); // Add an element at the end of vector
	void reserve(int N);
	void insert(int index, T element); // Add an element at the index
	void erase(int index);			   // Removes an element from the index
	T &at(int index);				   // return reference of the element at index
	T &front();						   // Returns reference of the first element in the vector
	T &back();						   // Returns reference of the Last element in the vector
	int size() const;				   // Return current size of vector
	int capacity() const;			   // Return capacity of vector
	bool empty() const;				   // Rturn true if the vector is empty, False otherwise
	void shrink_to_fit();			   // Reduce vector capacity to fit its size
};

template <typename T>
MyVector<T>::MyVector()
{
	v_capacity = 0; // Setting initial capacity to 0
	v_size = 0;		// Setting initial number of elements in the vector to 0
	data = NULL;

} // Default constructor
template <typename T>
MyVector<T>::MyVector(int cap)
{
	v_size = 0;		   // Setting initial number of elements in the vector to 0
	v_capacity = cap;  // Setting total capacity of the vector
	data = new T[cap]; // Creating an array of size cap
} // Non Default Constructor

template <typename T>
MyVector<T>::~MyVector()
{
	delete[] data; // Deletes dynamically allocated memory

} // Destructor

template <typename T>
void MyVector<T>::push_back(T element)
{

	if (v_size == v_capacity) // If the number of elements in the vector have reached the maximum capacity of the vector
	{
		reserve(max(1, 2 * v_capacity)); // Reserves space for the vector which is double the initial capacity for more elements to be added
	}
	data[v_size] = element; // add the element in the last index
	v_size++;				// increases the count of the number of elements in the vector

} // Add an element at the end of vector

template <typename T>
void MyVector<T>::reserve(int N) // reference lecture slides
{
	if (v_capacity >= N) // if the capacity of the vector is already greater
	{

		return;
	}
	T *temp = new T[N]; // resize the array by creating a temporary array

	for (int j = 0; j < v_size; j++) // copy contents to new array
	{
		temp[j] = data[j];
	}

	if (data != NULL)
	{
		delete[] data; // discard old array
	}

	data = temp; // make the old array equal to the new array

	v_capacity = N; // final capacity is updated
} // Reserves space

template <typename T>
void MyVector<T>::insert(int index, T element) // reference lecture slides
{
	if (index < 0 or index > v_size) // checking for index out of bounds
	{
		cout << "Index out of bounds" << endl;
		exit(1);
	}
	if (v_size == v_capacity) // checking if the vector is full
	{
		reserve(max(1, 2 * v_capacity)); // increasing the capacity of the vector by doubling the size
	}
	for (int j = v_size - 1; j >= index; j--) // shift elements up
	{
		data[j + 1] = data[j];
	}
	data[index] = element; // puts element at index position of the data array
	v_size++;			   // updates the count of the number of elements in the vector

} // Add an element at the index

template <typename T>
void MyVector<T>::erase(int index)
{

	if (index > v_size and index < 0) // checks for exception
	{
		cout << "Index out of range" << endl;
		exit(1);
	}
	for (int i = index; i < v_size; i++) // shifts elements in the array
	{
		data[i] = data[i + 1];
	}
	v_size--; // updates the count of the number of elements in the vector

} // Removes an element from the index

template <typename T>
T &MyVector<T>::at(int index)
{

	if (!empty())
	{
		if (index > v_size && index < 0) // checking for exception
		{
			cout << "Index Out Of range" << endl;
			exit(1);
		}
		else
		{
			return data[index]; // returns the element at the index
		}
	}
	else // if vector is empty
	{
		cout << "Vector empty" << endl;
		return data[index];
	}

} // return reference of the element at index

template <typename T>
T &MyVector<T>::front()
{
	return data[0];

} // Returns reference of the first element in the vector

template <typename T>
T &MyVector<T>::back()
{
	return data[v_size - 1];
} // Returns reference of the Last element in the vector

template <typename T>
int MyVector<T>::size() const
{
	return v_size;
} // Return current size of vector

template <typename T>
int MyVector<T>::capacity() const
{
	return v_capacity;
} // Return capacity of vector

template <typename T>
bool MyVector<T>::empty() const
{
	return (v_size == 0);
} // Rturn true if the vector is empty, False otherwise

template <typename T>
void MyVector<T>::shrink_to_fit()
{
	v_capacity = v_size;

} // Reduce vector capacity to fit its size

#endif
