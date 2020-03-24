#ifndef _STACK_H
#define _STACK_H

#include <iostream>
#include <string>

#include "SortedLinkedList.h"

#define MAXSIZE 10

using namespace std;

/**
*	@brief	a class that manage history whose structure is stack and which has characteristic of queue
*/
template <typename T>
class Stack {
private:
	int top = -1;				///<an index of toppest item
	T* items[MAXSIZE] = { NULL };		///<an array that stores pointer of T type
public:

	/**
	*	@brief	make stack empty
	*	@pre	the object should be initiallized
	*	@post	stack is empty
	*/
	void makeEmpty();

	/**
	*	@brief	check is stack is empty or not
	*	@pre	the object should be initialized
	*	@return	return true if stack is empty, otherwise false
	*/
	bool isEmpty();

	/**
	*	@brief	check is stack is full or not
	*	@pre	the object should be initialized
	*	@return	return true if stack is full, otherwise false
	*/
	bool isFull();

	/**
	*	@brief	add one item to stack
	*	@pre	the object should be initialized
	*	@pre	stack is not full
	*	@post	input item is added to stack
	*	@param	T* inItem	the item which will be added to stack
	*/
	void push(T* inItem);

	/**
	*	@brief	add one item to stack(if stack is full, delete the oldest one and add item
	*	@pre	the object should be initialized
	*	@post	input item is added to stack
	*	@param	T* inItem	the item which will be added to stack
	*/
	void autoPush(T* inItem);

	/**
	*	@brief	move top to down by 1 and change input pointer to that if exists
	*	@pre	the object should be initialized
	*	@pre	down item exist
	*	@post	top is decreased by 1, input pointer is pointing the down item
	*	@param	T*& m_curFolder	the T pointer type which will be the address of down item
	*	@return	return 1 if going back process works, otherwise 0
	*/
	int goBackward(T*& m_curFolder);

	/**
	*	@brief	move top to up by 1 and change input pointer to that if exists
	*	@pre	the object should be initialized
	*	@post	up item exist
	*	@post	top is increased by 1, input pointer is pointing the up item
	*	@param	T*& m_curFolder	the T type pointer which will be the address of up item
	*	@return	return 1 if going forth process works, otherwise 0
	*/
	int goForward(T*& curFolder);

	/**
	*	@brief	return back history path in type of unsorted linked list
	*	@pre	the object should be initialized
	*	@return	return the pointer list of back history path, with the type of T in unsorted linked list
	*/
	SortedLinkedList<T*> getBackHistory();

	/**
	*	@brief	return front history path in type of unsorted linked list
	*	@pre	the object should be initialized
	*	@return	return the pointer list of front history path, with the type of T in unsorted linked list
	*/
	SortedLinkedList<T*> getFrontHistory();
};

//make stack empty
template<typename T>
void Stack<T>::makeEmpty() {
	top = -1;
}

//check if stack is empty or not
template<typename T>
bool Stack<T>::isEmpty() {
	if (top == -1) {
		return true;
	}
	return false;
}

//check if stack is full or not
template<typename T>
bool Stack<T>::isFull() {
	if (top == MAXSIZE - 1) {
		return true;
	}
	return false;
}

//insert item
template<typename T>
void Stack<T>::push(T* inItem) {
	if (!isFull()) {
		top++;
		items[top] = inItem;
	}
}

//insert item(if stack is full, delete oldest one and add)
template<typename T>
void Stack<T>::autoPush(T* inItem) {
	if (!isFull()) {
		top++;
		items[top] = inItem;

		//make all front items NULL if there are items at the front.
		for (int i = top + 1; i < MAXSIZE; i++) {
			if (items[i] != NULL) {
				items[i] = NULL;
			}
			else {
				return;
			}
		}
		int a = 3;
	}
	else {
		for (int i = 0; i < MAXSIZE - 1; i++) {
			items[i] = items[i + 1];
		}
		items[top] = inItem;
	}
}

//move top to down by 1 and change input pointer to that if exists
template<typename T>
int Stack<T>::goBackward(T*& m_curFolder) {
	if (items[top - 1] != NULL) {
		top--;
		m_curFolder = items[top];
		return 1;
	}
	return 0;
}

//move top to up by 1 and change input pointer to that if exists
template<typename T>
int Stack<T>::goForward(T*& m_curFolder) {
	if (items[top + 1] != NULL) {
		top++;
		m_curFolder = items[top];
		return 1;
	}
	return 0;
}

//return back history path in type of unsorted linked list
template<typename T>
SortedLinkedList<T*> Stack<T>::getBackHistory() {
	SortedLinkedList<T*> backTs;
	if (!isEmpty()) {
		int i = top - 1;
		while (i != -1) {
			backTs.addT(items[i]);
			i--;
		}
	}
	return backTs;
}

//return front history path in type of unsorted linked list
template<typename T>
SortedLinkedList<T*> Stack<T>::getFrontHistory() {
	SortedLinkedList<T*> frontTs;
	if (!isEmpty()) {
		int i = top + 1;
		while (items[i] != NULL) {
			frontTs.addT(items[i]);
			i++;
		}
	}
	return frontTs;
}

#endif _STACK_H
