#ifndef _SORTEDLINKEDLIST_H
#define _SORTEDLINKEDLIST_H

#include <iostream>
#include <string>

using namespace std;

/**
*	@brief	the node of doubly linked list
*/
template <typename T>
struct NodeType
{
	T item;				///< T data type which is component of a node
	NodeType<T>* next;	///< NodeType pointer that points next node
	NodeType<T>* prev;	///< NodeType pointer that points previous node
};

/**
*	@brief	a sorted linked list which is generic class
*/
template <typename T>
class SortedLinkedList {
private:
	int length;				///< the length of list
	NodeType<T>* head;		///< pointing node at the first of the list
	NodeType<T>* tail;		///< pointing node at the end of the list
	NodeType<T>* mid;		///< pointing node at the middle of the list
	NodeType<T>* current;	///< iterator point of the list
public:
	/**
	*	@brief	default constructor
	*/
	SortedLinkedList() {
		length = 0;
	}

	/**
	*	@brief	default destructor
	*/
	~SortedLinkedList() {}

	/**
	*	@brief	make list empty(Used instead of destructor)
	*	@pre	the object should be initialized
	*	@post	all nodes in list are deleted and length is set to 0
	*/
	void makeEmpty();

	/**
	*	@brief	get length of current list
	*	@pre	the object should be initialized
	*	@return	the length of current list
	*/
	int	getLength() const;

	/**
	*	@brief	add item in to current list
	*	@pre	the object should be initialized
	*	@post	new item is added if same item doesn't exist
	*	@param	T inItem : item that will be added to list
	*	@return	return 1 if added, otherwise 0
	*/
	int addT(const T& inItem);

	/**
	*	@brief	add item in to current list(unsorted)
	*	@pre	the object should be initialized
	*	@post	new item is added if same item doesn't exist
	*	@param	T inItem : item that will be added to list
	*	@return	return 1 if added, otherwise 0
	*/
	int addTUnsorted(const T& inItem);

	/**
	*	@brief	delete the item which is same with input parameter
	*	@pre	the object should be initialized
	*	@param	T inItem : the item which will be compared to items in the list
	*	@return	return 1 if item is deleted, otherwise 0
	*/
	int deleteT(const T& inItem);

	/**
	*	@brief	reset the current node pointer
	*	@pre	the object should be initialized
	*	@post	the current node is set to NULL
	*/
	void resetList();

	/**
	*	@brief	get the next item of current node pointer
	*	@pre	the object should be initialized
	*	@post	inItem is pointing the next node
	*	@param	T*& inItem : the item pointer which will be pointing the found item
	*	@return	return 1 if this function works, otherwise 0
	*/
	int getNextT(T*& inItem);

	/**
	*	@brief	get the previous item of current node pointer
	*	@pre	the object should be initialized
	*	@post	inItem is pointing the previous node
	*	@param	T*& inItem : the item pointer which will be pointing the found item
	*	@return	return 1 if this function works, otherwise 0
	*/
	int getPrevT(T*& inItem);

	/**
	*	@brief	find the item which is same with input parameter, be care of inItem will points found item
	*	@pre	the object should be initialized
	*	@post	the input parameter is pointing the found item
	*	@param	T*& inItem : the item pointer which will be pointing the found item
	*	@return return 1 if this function works, otherwise 0
	*/
	int findT(T*& inItem);

	/**
	*	@brief	find the item which is same with input parameter
	*	@pre	the object should be initialized
	*	@param	const T& inItem : the item pointer which will be compared to items in the list
	*	@return return true if this function works, otherwise false
	*/
	bool isFound(const T& inItem);

	/**
	*	@brief	sort the item inside the list way to descend
	*	@pre	the object should be initialized
	*	@post	the items inside the list is sorted in descending direction
	*/
	void insertionSortDescending();

	/**
	*	@brief	sort the item inside the list way to ascend
	*	@pre	the object should be initialized
	*	@post	the items inside the list is sorted in ascending direction
	*/
	void insertionSortAscending();
};

//make list empty
template <typename T>
void SortedLinkedList<T>::makeEmpty() {
	if (length != 0) {
		NodeType<T>* temp;
		while (head != NULL) {
			temp = head;
			head = head->next;
			delete temp;
			length--;
		}
	}
}

//get length of current list
template <typename T>
int SortedLinkedList<T>::getLength() const {
	return length;
}

//add item in to current list
template <typename T>
int SortedLinkedList<T>::addT(const T& inItem) {

	//create a node and add item to list.
	NodeType<T>* temp = new NodeType<T>();
	temp->item = inItem;
	if (!isFound(inItem)) {
		if (length == 0) {
			head = temp;
			tail = temp;
			length++;
		}
		else {
			tail->next = temp;
			temp->prev = tail;
			tail = temp;
			length++;
		}

		//sorting
		insertionSortAscending();
		return 1;
	}
	return 0;
}

template<typename T>
inline int SortedLinkedList<T>::addTUnsorted(const T & inItem)
{
	//create a node and add item to list.
	NodeType<T>* temp = new NodeType<T>();
	temp->item = inItem;
	if (!isFound(inItem)) {
		if (length == 0) {
			head = temp;
			tail = temp;
			length++;
		}
		else {
			tail->next = temp;
			temp->prev = tail;
			tail = temp;
			length++;
		}
		if (length > 2) {
			T* temp;
			resetList();
			for (int i = 0; i < (length - 1) / 2; i++) {
				getNextT(temp);
			}
			mid = current;
		}

		else {
			mid = head;
		}
		return 1;
	}
	return 0;
}

//delete the item which is same with input parameter
template<typename T>
int SortedLinkedList<T>::deleteT(const T& inItem) {
	resetList();
	T* temp;
	for (int i = 0; i < length; i++) {
		getNextT(temp);//change current and temp to the next one
		if (*temp == inItem) {
			//case 1 : if found item is in the head
			if (i == 0) {
				//if head and tail are different(more than one items are in the list)
				if (head != tail) {
					head = head->next;
					head->prev = NULL;
					delete current;
					length--;
					return 1;
				}
				//if head and tail is same(only one item is in the list)
				else {
					makeEmpty();
					return 1;
				}
			}
			//case 2 : if found item is in the tail
			else if (i == length - 1) {
				tail = current->prev;
				delete current;
				length--;
				return 1;
			}
			//case 3 : if found item is not in the head or tail
			else {
				(current->prev)->next = current->next;
				(current->next)->prev = current->prev;
				delete current;
				length--;
				return 1;
			}
		}
	}
	return 0;
}

//reset the current node pointer
template <typename T>
void SortedLinkedList<T>::resetList() {
	current = NULL;
}

//get the next item of current node pointer
template <typename T>
int SortedLinkedList<T>::getNextT(T*& inItem) {
	if (length != 0) {
		if (current == NULL) {
			current = head;
			inItem = &(current->item);
			return 1;
		}
		else if (current->next == NULL) {
			cout << endl << endl << "Can't get next Item(End of the List)" << endl << endl;
			return 0;
		}
		else {
			current = current->next;
			inItem = &(current->item);
			return 1;
		}
	}
	return 0;
}

//get the previous item of current node pointer
template <typename T>
int SortedLinkedList<T>::getPrevT(T*& inItem) {
	if (length != 0) {
		if (current == NULL) {
			current = tail;
			inItem = &(current->item);
			return 1;
		}
		else if (current->prev == NULL) {
			cout << endl << endl << "Can't get prev Item(First of the List)" << endl << endl;
			return 0;
		}
		else {
			current = current->prev;
			inItem = &(current->item);
			return 1;
		}
	}
	return 0;
}

//find the item which is same with input parameter, be care of inItem will points found item
template<typename T>
int SortedLinkedList<T>::findT(T*& inItem) {
	T* temp;
	//find item from the middle one
	current = mid;
	//if middle item is bigger than inItem, find in the front list
	if ((mid->item) > (*inItem)) {
		while ((current->prev) != NULL) {
			getPrevT(temp);
			if ((*temp) == (*inItem)) {
				inItem = temp;
				return 1;
			}
		}
	}
	//if middle item is smaller than inItem, find in the back list
	else if ((mid->item) < (*inItem)) {
		while ((current->next) != NULL) {
			getNextT(temp);
			if ((*temp) == (*inItem)) {
				inItem = temp;
				return 1;
			}
		}
	}
	//if middle item is inItem, return
	else {
		inItem = &(mid->item);
		return 1;
	}
	return 0;
}

//find the item which is same with input parameter
template<typename T>
bool SortedLinkedList<T>::isFound(const T& inItem) {
	if (length != 0) {
		T* temp;
		//find item from the middle one
		current = mid;
		//if middle item is bigger than inItem, find in the front list
		if ((mid->item) > (inItem)) {
			while ((current->prev) != NULL) {
				getPrevT(temp);
				if ((*temp) == (inItem)) {
					return true;
				}
			}
		}
		//if middle item is smaller than inItem, find in the back list
		else if ((mid->item) < (inItem)) {
			while ((current->next) != NULL) {
				getNextT(temp);
				if ((*temp) == (inItem)) {
					return true;
				}
			}
		}
		//if middle item is inItem, return
		else {
			return true;
		}
	}
	return false;
}

//sort the item inside the list way to descend
template<typename T>
void SortedLinkedList<T>::insertionSortAscending() {
	//sorting a list(insertion sort)
	NodeType<T>* i;
	NodeType<T>* k;
	//sort if list length is more than 2
	if (length >= 2) {
		i = head->next;
		//repeat while i is not the tail
		while (i != tail) {
			k = head;
			//if k's item is bigger than i's item, insert i
			while (k != i)
			{
				if (k->item > i->item) {
					//if k equals to head, insert i and change head to i
					if (k == head) {
						(i->prev)->next = i->next;
						(i->next)->prev = i->prev;
						i->next = k;
						k->prev = i;
						head = i;
						break;
					}
					//else insert i
					else {
						(i->prev)->next = i->next;
						(i->next)->prev = i->prev;
						(k->prev)->next = i;
						i->prev = k->prev;
						i->next = k;
						k->prev = i;
						break;
					}
				}
				else {
					k = k->next;
				}
			}
			i = i->next;
		}
		if (i == tail) {
			k = head;
			//repeat while k is not i
			while (k != i) {
				//if k's item is bigger than i's item, insert i
				if (k->item > i->item) {
					//if k is head, insert i and change i to head and change tail to i->prev
					if (k == head) {
						i->next = k;
						k->prev = i;
						head = i;
						(i->prev)->next = NULL;
						tail = i->prev;
						i->prev = NULL;
						break;
					}
					//if k is not head, insert i and change tail to i->prev
					else {
						(i->prev)->next = NULL;
						tail = i->prev;
						(k->prev)->next = i;
						i->prev = k->prev;
						i->next = k;
						k->prev = i;
						break;
					}
				}
				else {
					k = k->next;
				}
			}
		}
		//define middle one
		if (length > 2) {
			T* temp;
			resetList();
			for (int i = 0; i < (length - 1) / 2; i++) {
				getNextT(temp);
			}
			mid = current;
		}
	}
	else {
		mid = head;
	}
}

//sort the item inside the list way to ascend
template<typename T>
void SortedLinkedList<T>::insertionSortDescending() {
	//sorting a list(insertion sort)
	NodeType<T>* i;
	NodeType<T>* k;
	//sort if list length is more than 2
	if (length >= 2) {
		i = head->next;
		//repeat while i is not the tail
		while (i != tail) {
			k = head;
			//if k's item is smaller than i's item, insert i
			while (k != i)
			{
				if (k->item < i->item) {
					//if k equals to head, insert i and change head to i
					if (k == head) {
						(i->prev)->next = i->next;
						(i->next)->prev = i->prev;
						i->next = k;
						k->prev = i;
						head = i;
						break;
					}
					//else insert i
					else {
						(i->prev)->next = i->next;
						(i->next)->prev = i->prev;
						(k->prev)->next = i;
						i->prev = k->prev;
						i->next = k;
						k->prev = i;
						break;
					}
				}
				else {
					k = k->next;
				}
			}
			i = i->next;
		}
		if (i == tail) {
			k = head;
			//repeat while k is not i
			while (k != i) {
				//if k's item is smaller than i's item, insert i
				if (k->item < i->item) {
					//if k is head, insert i and change i to head and change tail to i->prev
					if (k == head) {
						i->next = k;
						k->prev = i;
						head = i;
						(i->prev)->next = NULL;
						tail = i->prev;
						i->prev = NULL;
						break;
					}
					//if k is not head, insert i and change tail to i->prev
					else {
						(i->prev)->next = NULL;
						tail = i->prev;
						(k->prev)->next = i;
						i->prev = k->prev;
						i->next = k;
						k->prev = i;
						break;
					}
				}
				else {
					k = k->next;
				}
			}
		}
		//define middle one
		T* temp;
		resetList();
		for (int i = 0; i < (length - 1) / 2; i++) {
			getNextT(temp);
		}
		mid = current;
	}
	else {
		mid = head;
	}
}

#endif _SORTEDLINKEDLIST_H