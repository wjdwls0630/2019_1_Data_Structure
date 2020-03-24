#ifndef _QUEUE_H
#define _QUEUE_H

#include <iostream>
#include <string>
#include "SortedLinkedList.h"

/**
*	@brief	a class that manage history whose structure is queue(non limited)
*/
template<typename T>
class Queue {
private:
	int theNumOfItems;	///< max size of queue
	SortedLinkedList<T>* items;
public:

	/**
	*	@brief	default constructor
	*/
	Queue() {
		items = new SortedLinkedList<T>;
	}


	/**
	*	@brief	get the number of items in the queue
	*	@pre	Queue has been initialized
	*	@return	the number of items in the queue
	*/
	int getSize();

	/**
	*	@brief	make Queue empty
	*	@pre	Queue has been initialized
	*	@post	rear and front is equal to maxqueue-1
	*/
	void makeEmpty();

	/**
	*	@brief	check if queue is empty or not
	*	@pre	Queue has been initialized
	*	@return	return true if queue is empty, otherwise false
	*/
	bool isEmpty();

	/**
	*	@brief	add new item to the queue
	*	@pre	Que has been initialized
	*	@post	item is added to queue
	*/
	void enQueue(const T& inItem);

	/**
	*	@brief	delete oldest item from the queue
	*	@pre	Que has been initialized
	*	@post	item is deleted
	*/
	void deQueue(T& inItem);

	/**
	*	@brief	delete item in the queue
	*	@pre Queue has been initialized
	*	@return	return true if item is deleted, otherwise 0
	*	@param	const T& inItem	item which will be compared to the items Queue
	*/
	bool deleteT(const T& inItem);

	/**
	*	@brief	find item in the queue
	*	@pre	Queue has been initialized
	*	@return	return true if item is found, otherwise 0
	*	@param	const T& inItem	item which will be compared to the items Queue
	*/
	bool isFound(const T& inItem);

};

//get the number of items in the queue
template <typename T>
int Queue<T>::getSize() {
	return theNumOfItems;
}

//make Queue empty
template <typename T>
void Queue<T>::makeEmpty() {

}

//check if queue is empty or not
template <typename T>
bool Queue<T>::isEmpty() {
	if (theNumOfItems == 0) {
		return true;
	}
	return false;
}


//add new item to the queue
template <typename T>
void Queue<T>::enQueue(const T& inItem) {
	items->addTUnsorted(inItem);
	theNumOfItems++;
}

//delete oldest item from the queue
template <typename T>
void Queue<T>::deQueue(T& inItem) {
	T* temp;
	items->resetList();
	items->getNextT(temp);
	inItem = *temp;
	items->deleteT(inItem);
	theNumOfItems--;
}


//delete item in the queue
template<typename T>
bool Queue<T>::deleteT(const T& inItem) {
	if (items->deleteT(inItem)) {
		return true;
	}
	return false;
}


//find item in the queue
template<typename T>
bool Queue<T>::isFound(const T& inItem) {
	if (items->isFound(inItem)) {
		return true;
	}
	return false;
}

#endif _QUEUE_H