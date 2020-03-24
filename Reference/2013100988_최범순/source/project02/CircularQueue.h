#ifndef _CIRCULARQUEUE_H
#define _CIRCULARQUEUE_H

#define MAXQUE 10

#include <iostream>
#include <string>

/**
*	@brief	a class that manage history whose structure is circular queue
*/
template<typename T>
class CircularQueue {
private:
	int front;		///< front index of queue
	int rear;		///< rear index of queue
	int maxQueue;	///< max size of queue
	T* items;		///< Array of T type datas
public:

	/**
	*	@brief	default constructor
	*/
	CircularQueue() {
		maxQueue = MAXQUE;
		front = maxQueue - 1;
		rear = maxQueue - 1;
		items = new T[maxQueue];
	}


	/**
	*	@brief	get the number of items in the queue
	*	@pre	Queue has been initialized
	*	@return	the number of items in the queue
	*/
	int getSize();

	/**
	*	@brief	get all items is in the queue
	*	@pre	Queue has been initialized
	*	@return	the pointer of items
	*/
	T* getTs(int& numOfTs);

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
	*	@brief	check if queue is full or not
	*	@pre	Queue has been initialized
	*	@return return true if queue is full, otherwise false
	*/
	bool isFull();

	/**
	*	@brief	add new item to the queue
	*	@pre	Que has been initialized
	*	@post	item is added to queue
	*/
	void enQueue(const T& inItem);

	/**
	*	@brief	add new item to the queue(if queue is full, delete oldest item and add item)
	*	@pre	Que has been initialized
	*	@post	item is added to queue
	*/
	void autoEnQueue(const T& inItem);

	/**
	*	@brief	delete oldest item from the queue
	*	@pre	Que has been initialized
	*	@post	item is deleted
	*/
	void deQueue();

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

	/**
	*	@brief	get last item in the queue
	*	@pre	Queue has been initialized
	*	@pre	Queue has an item
	*	@return	the last item of the queue
	*/
	T getRear();
};

//get the number of items in the queue
template <typename T>
int CircularQueue<T>::getSize() {
	return (rear - front + maxQueue) % maxQueue;
}

//get all items is in the queue
template <typename T>
T* CircularQueue<T>::getTs(int& numOfTs) {
	numOfTs = getSize();
	T* outItems;
	if (isEmpty()) {
		return NULL;
	}
	else {
		outItems = new T[getSize()];
		for (int i = 0; i < getSize(); i++) {
			*(outItems + i) = *(items + ((rear + maxQueue - i) % maxQueue));
		}
	}
	return outItems;
}

//make Queue empty
template <typename T>
void CircularQueue<T>::makeEmpty() {
	front = maxQueue - 1;
	rear = maxQueue - 1;
}

//check if queue is empty or not
template <typename T>
bool CircularQueue<T>::isEmpty() {
	if (front == rear) {
		return true;
	}
	return false;
}

//check if queue is full or not
template <typename T>
bool CircularQueue<T>::isFull() {
	if (front != 0) {
		if ((rear % (maxQueue - 1)) == front - 1) {
			return true;
		}
	}
	else {
		if ((rear % (maxQueue - 1)) == front) {
			return true;
		}
	}
	return false;
}

//add new item to the queue
template <typename T>
void CircularQueue<T>::enQueue(const T& inItem) {
	if (isFull()) {
		cout << "\tCan't add more to queue!" << endl;
	}
	else {
		rear = (rear + 1) % maxQueue;
		items[rear] = inItem;
	}
}

//add new item to the queue(if queue is full, delete oldest item and add item.)
template<typename T>
void CircularQueue<T>::autoEnQueue(const T& inItem) {

	//delete if there is same item in queue.
	if (isFound(inItem)) {
		deleteT(inItem);
	}

	//if queue is full, delete oldest one and add item.
	if (isFull()) {
		front = (front + 1) % maxQueue;
	}
	rear = (rear + 1) % maxQueue;
	items[rear] = inItem;

}

//delete oldest item from the queue
template <typename T>
void CircularQueue<T>::deQueue() {
	if (isEmpty()) {
		cout << "\tCan't eleminate one, because queue is already Empty!" << endl;
	}
	else {
		front = (front + 1) % maxQueue;
	}
}

//delete item in the queue
template<typename T>
bool CircularQueue<T>::deleteT(const T& inItem) {
	int i = 1;
	int index;
	while (i <= getSize()) {
		index = (front + i) % maxQueue;

		//do if inItem is found in the queue
		if (inItem == items[index]) {

			//pull all items behind found item and decrease rear by 1
			int j = 1;
			while (j <= getSize() - i) {
				items[(index + j + maxQueue - 1) % maxQueue] = items[(index + j) % maxQueue];
				j++;
			}
			rear = (rear + maxQueue - 1) % maxQueue;
			return true;
		}
		i++;
	}
	return false;
}

//find item in the queue
template<typename T>
bool CircularQueue<T>::isFound(const T& inItem) {
	int i = 1;
	int index;
	while (i <= getSize()) {
		index = (front + i) % maxQueue;
		if (inItem == items[index]) {
			return true;
		}
		i++;
	}
	return false;
}

//get last item in the queue
template<typename T>
T CircularQueue<T>::getRear()
{
	if (!isEmpty()) {
		return items[rear];
	}
}

#endif _CIRCULARQUEUE_H