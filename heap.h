// =================================================================
//
// File: heap.h
// Author: Pedro Perez
// Description: This file contains the implementation of TDA Heap
//							(in this case is MIN-HEAP).
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
// =================================================================

#ifndef HEAP_H
#define HEAP_H

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include "exception.h"
#include "header.h"

// =================================================================
// Definition of the Heap class
// =================================================================
template <class T>
class Heap {
private:
	int *data;
	int size;
	int count;

	int parent(int) const;
	int left(int) const;
	int right(int) const;
	void swap(int, int);

public:
	void pushDown(int);
	Heap(int);
	~Heap();
	bool empty() const;
	bool full() const;
	int length() const;
	void add(T);
	T remove();
	// T insert(int, int , int);
	void clear();
	std::string toString() const;
};

// =================================================================
// Constructor. Initializes the maximum size of the heap and creates
// the array.
//
// @param sze, the maximum size of the heap.
// =================================================================
template <class T>
Heap<T>::Heap(int sze) {
	size = sze;
	data = new T[size];
	count = 0;
}

// =================================================================
// Destructor. Free used dynamic memory.
//
// =================================================================
template <class T>
Heap<T>::~Heap() {
	delete [] data;
	data = NULL;
	size = 0;
	count = 0;
}

// =================================================================
// Returns if the heap is empty or not.
//
// @returns True is the amount of elements is 0 (empty). False,
//					otherwise.
// =================================================================
template <class T>
bool Heap<T>::empty() const {
	return (count == 0);
}

// =================================================================
// Returns if the heap is full or not.
//
// @returns True is the amount of elements is equal to the maximum.
//					False, otherwise.
// =================================================================
template <class T>
bool Heap<T>::full() const {
	return (count == size);
}

// =================================================================
// Returns the number of elements in the heap
//
// @returns the number of elements in the heap.
// =================================================================
template <class T>
int Heap<T>::length() const {
	return count;
}

// =================================================================
// Returns the position of the parent of an element.
//
// @returns the index of the parent
// =================================================================
template <class T>
int Heap<T>::parent(int pos) const {
	return (pos - 1) / 2;
}

// =================================================================
// Returns the position of the left child of an element.
//
// @returns the index of the left child.
// =================================================================
template <class T>
int Heap<T>::left(int pos) const {
	return (pos * 2) + 1;
}

// =================================================================
// Returns the position of the right child of an element.
//
// @returns the index of the right child.
// =================================================================
template <class T>
int Heap<T>::right(int pos) const {
	return (pos * 2) + 2;
}

// =================================================================
// Swap the content of two locations.
//
// @param i, j, indeces to be swapped.
// =================================================================
template <class T>
void Heap<T>::swap(int i, int j) {
	T aux = data[i];
	data[i] = data[j];
	data[j] = aux;
}

// =================================================================
// Place the item in the correct position. Being a min-heap, the
// element must be less than its children. If not, recursively
// perform the pushDown.
//
// @param pos, the current position of the item being inserted.
// =================================================================
template <class T>
void Heap<T>::pushDown(int pos) {
    int le = left(pos);
    int ri = right(pos);
    int min = pos;

    if (le < count && data[le] < data[min]){
        min = le;
    }
    if (ri < count && data[ri] < data[min]){
        min = ri;
    }

    if(min != pos){
        swap(pos, min);
        pushDown(min);
    }
}

// =================================================================
// Add an element to the heap. It is placed, initially, as the
// rightmost blade. Afterwards, it is verified if he is less than
// the father. If that is the case, it is exchanged. This process is
// repeated until the correct position is reached.
//
// @param val, the element to be added.
// @throws Overflow, if the heap is full.
// =================================================================
template <class T>
void Heap<T>::add(T val) {
	int pos;
	if (full()){
		throw Overflow();
	}

	pos = count;
	count++;
	while(pos > 0 && val < data[parent(pos)]){
		data[pos]= data[parent(pos)];
		pos = parent(pos);
	}
	data[pos] = val;
}

// =================================================================
// Insert an element at the end of the heap and call the pushDown
// method.
//
// @param val, the element to be added.
// @throws Overflow, if the heap is full.
// @param array, the array to be sorted.
// =================================================================

/*
template <class T>
T Heap<T>::insert(int A[], int n, int val){
	if(n == size){
		throw Overflow();
	}
	int temp, i=n;
	temp = A[n];

	while(i>1 && temp>A[i/2]){
		A[i] = A[i/2];
		i = i/2;
	}
	A[i] = temp;
	return A[n];
}

*/

// =================================================================
// Remove the root of the tree. The rightmost sheet is placed as a
// temporary successor. The tree is rearranged using the pushDown
// method.
//
// @returns, in this case, the minimum element in the heap.
// =================================================================
template <class T>
T Heap<T>::remove() {
	if (empty()){
		throw NoSuchElement();
	}

	T aux = data[0];
	data[0] = data[--count]; // data[0] = data[count]; count--;
	pushDown(0);
	return aux;
}

// =================================================================
// Removes all elements from heap.
//
// =================================================================
template <class T>
void Heap<T>::clear() {
	count = 0;
}
// =================================================================
// Return a string representation of the heap.
//
// @returns, a string with the elements of the heap.
// =================================================================
template <class T>
std::string Heap<T>::toString() const {
	std::stringstream aux;

	aux << "[";
	for (int i = 0; i < count; i++) {
		if (i != 0) {
			aux << " ";
		}
	aux << data[i];
	}
	aux << "]";
	return aux.str();
}
#endif /* HASH_H */
