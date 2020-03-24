#ifndef _AVLTREE_H
#define _AVLTREE_H

#include "Queue.h"

enum OrderType {
	PRE_ORDER = 0, IN_ORDER = 1, POST_ORDER = 2
};

/**
*	@brief	the node of binary search tree
*/
template <typename T>
struct TreeNode {
	T item;
	TreeNode* left;
	TreeNode* right;
};

/**
*	@brief	binary search tree
*/
template <typename T>
class AVLtree {
private:
	TreeNode<T>* root;
	Queue<T*> preQue;
	Queue<T*> inQue;
	Queue<T*> postQue;

	/**
	*	@brief	find the exact item in the tree and delete that item
	*	@pre	the object should be initailized
	*	@post	the item is deleted from the tree
	*	@param	TreeNode<T>*& root	the node which will be searched
	*	@param	const T& inItem	the item which will be deleted from the tree
	*	@return	reutrn 1 if this function works well, otherwise 0
	*/
	int deleteTreculsively(TreeNode<T>*& root, const T& inItem);

	/**
	*	@brief	delete specific node from the tree,the item in the node will be deleted
	*	@pre	the object should be initailized
	*	@post	the node is deleted and tree is rearrayed
	*	@param	TreeNode<T>*& root	the node which will be deleted
	*	@return	reutrn 1 if this function works well, otherwise 0
	*/
	int deleteNode(TreeNode<T>*& root);

	/**
	*	@brief	find the exact item in the tree and delete that item temporarily
	*	@pre	the object should be initailized
	*	@post	the item is deleted from the tree
	*	@param	TreeNode<T>*& root	the node which will be searched
	*	@param	const T& inItem	the item which will be deleted from the tree
	*	@return	reutrn 1 if this function works well, otherwise 0
	*/
	int deleteTtemporarilyReculsively(TreeNode<T>*& root, const T& inItem, TreeNode<T>*& result);

	/**
	*	@brief	delete specific node from the tree,the item in the node won't be deleted
	*	@pre	the object should be initailized
	*	@post	the node is deleted and tree is rearrayed
	*	@param	TreeNode<T>*& root	the node which will be deleted
	*	@param	TreeNode<T>*& temp	the node which will be contain deleted one
	*	@return	reutrn 1 if this function works well, otherwise 0
	*/
	int deleteNodeTemporarily(TreeNode<T>*& root, TreeNode<T>*& result);

	/**
	*	@brief	get the right most of certain node or subnode
	*	@pre	the object should be initailized
	*	@param	TreeNode<T>* root	the node which will be searched
	*	@param	TreeNode<T>*& temp	the node which will be returned with th form of right most node
	*	@return	reutrn 1 if this function works well, otherwise 0
	*/
	int getRightMostLeaf(TreeNode<T>* root, TreeNode<T>*& temp);

	/**
	*	@brief	make right most leaf to NULL(not deleting, just make NULL)
	*	@pre	the object should be initailized
	*	@post	the right most leaf is NULL
	*	@param	TreeNode<T>* root	the node whose right most node will be NULL
	*	@return	reutrn 1 if this function works well, otherwise 0
	*/
	int NULLRightMostLeaf(TreeNode<T>* root);

	/**
	*	@brief	find the item which is same with input parameter, be care of inItem will points found item
	*	@pre	the object should be initialized
	*	@post	the input parameter is pointing the found item
	*	@param	TreeNode<T>* root	the node which will be searched
	*	@param	T*& inItem : the item pointer which will be pointing the found item
	*	@return return 1 if this function works, otherwise 0
	*/
	int findTreculsively(TreeNode<T>*& root, T*& inItem);

public:

	/**
	*	@brief	default constructor
	*/
	AVLtree() {
		root = NULL;
	}

	/**
	*	@brief	default destructor
	*/
	~AVLtree() {}

	/**
	*	@brief	make list empty(Used instead of destructor)
	*	@pre	the object should be initialized
	*	@post	all nodes in list are deleted
	*/
	void makeEmpty();

	/**
	*	@brief	get the number of nodes inside the tree
	*	@pre	the object should be initialized
	*	@return	the number of nodes inside the tree
	*/
	int getLength() const;

	int getHeight(TreeNode<T>* inNode) const;

	int getBF(TreeNode<T>* inNode) const;

	TreeNode<T>* rotation_RR(TreeNode<T>* parent);

	TreeNode<T>* rotation_LL(TreeNode<T>* parent);

	TreeNode<T>* rotation_LR(TreeNode<T>* parent);

	TreeNode<T>* rotation_RL(TreeNode<T>* parent);

	TreeNode<T>* balance(TreeNode<T>* BFNode);

	/**
	*	@brief	add the nodes that contains the item to the tree
	*	@pre	the object should be initailized
	*	@post	the item is added to the tree
	*	@param	const T& inItem	the item which will be added to the tree
	*	@return	reutrn 1 if this function works well, otherwise 0
	*/
	int addT(const T& inItem);

	/**
	*	@brief	add the nodes that contains the item to the tree
	*	@pre	the object should be initailized
	*	@post	the item is added to the tree
	*	@param	TreeNode<T>* root	the node which will be searched
	*	@param	const T& inItem	the item which will be added to the tree
	*	@return	reutrn 1 if this function works well, otherwise 0
	*/
	TreeNode<T>* insertT(TreeNode<T>* root, const T& inItem);

	int addNode(TreeNode<T>*& inNode);

	TreeNode<T>* insertNode(TreeNode<T>* root, TreeNode<T>*& inNode);

	/**
	*	@brief	find the exact item in the tree and delete that item
	*	@pre	the object should be initailized
	*	@post	the item is deleted from the tree
	*	@param	const T& inItem	the item which will be deleted from the tree
	*	@return	reutrn 1 if this function works well, otherwise 0
	*/
	int deleteT(const T& inItem);

	/**
	*	@brief	find the exact item in the tree and delete that item temporarily
	*	@pre	the object should be initailized
	*	@post	the item is deleted from the tree
	*	@param	const T& inItem	the item which will be deleted from the tree
	*	@return	reutrn 1 if this function works well, otherwise 0
	*/
	int deleteTtemporarily(const T& inItem, TreeNode<T>*& result);

	/**
	*	@brief	enqueue item to the inQue in order of in-order
	*	@pre	the object should be initialized
	*	@post	the items will be added to the inQue in order of in-order
	*	@return	reutrn 1 if this function works well, otherwise 0
	*/
	void resetList();

	/**
	*	@brief	get the next item of current node pointer in order of in-order
	*	@pre	the object should be initialized
	*	@post	inItem is pointing the next node
	*	@param	T*& inItem : the item pointer which will be pointing the found item
	*	@return	return 1 if this function works, otherwise 0
	*/
	void getNextT(T*& inItem);

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
	*	@brief	get the number of nodes inside the tree
	*	@pre	the object should be initialized
	*	@param	TreeNode<T>* root	the node which will be searched
	*	@return	the number of nodes inside the tree
	*/
	int countNodes(TreeNode<T>* root);

	/**
	*	@brief	enqueue item to the Queue in order of input parameter 'order'
	*	@pre	the object should be initialized
	*	@post	the items will be added to the Queue in order of input parameter 'order'
	*	@param	OrderType order	the Queue will be selected depending on this parameter
	*	@return	reutrn 1 if this function works well, otherwise 0
	*/
	void resetList(OrderType order);

	/**
	*	@brief	get the next item of current node pointer
	*	@pre	the object should be initialized
	*	@post	inItem is pointing the next node
	*	@param	OrderType order	the Queue will be selected depending on this parameter
	*	@param	T*& inItem : the item pointer which will be pointing the found item
	*	@return	return 1 if this function works, otherwise 0
	*/
	void getNextT(T*& inItem, OrderType order);

	/**
	*	@brief	enqueue item to the inQue in order of in-order
	*	@pre	the object should be initialized
	*	@post	the items will be added to the inQue in order of in-order
	*	@return	reutrn 1 if this function works well, otherwise 0
	*/
	int inOrder(TreeNode<T>* root, Queue<T*>& inQue);

	/**
	*	@brief	enqueue item to the preQue in order of pre-order
	*	@pre	the object should be initialized
	*	@post	the items will be added to the preQue in order of pre-order
	*	@return	reutrn 1 if this function works well, otherwise 0
	*/
	int preOrder(TreeNode<T>* root, Queue<T*>& preQue);

	/**
	*	@brief	enqueue item to the postQue in order of post-order
	*	@pre	the object should be initialized
	*	@post	the items will be added to the postQue in order of post-order
	*	@return	reutrn 1 if this function works well, otherwise 0
	*/
	int postOrder(TreeNode<T>* root, Queue<T*>& postQue);

	int max(int a, int b) const;
};



//make list empty(Used instead of destructor)
template<typename T>
inline void AVLtree<T>::makeEmpty()
{
}

//get the number of nodes inside the tree
template<typename T>
inline int AVLtree<T>::getLength() const
{
	return countNodes(root);
}

template<typename T>
inline int AVLtree<T>::getHeight(TreeNode<T>* inNode) const
{
	int h = 0;
	if (inNode != NULL) {
		int left = getHeight(inNode->left);
		int right = getHeight(inNode->right);
		//height is the maximum value among left and right subtree
		int maxHeight = max(left, right);
		h = maxHeight + 1;
	}
	return h;
}

template<typename T>
inline int AVLtree<T>::getBF(TreeNode<T>* inNode) const
{
	int BF = 0;
	if (inNode != NULL) {
		int left = getHeight(inNode->left);
		int right = getHeight(inNode->right);
		BF = left - right;
	}
	return BF;
}

template<typename T>
inline TreeNode<T>* AVLtree<T>::rotation_RR(TreeNode<T>* parent)
{
	TreeNode<T>* temp;
	temp = parent->right;
	parent->right = temp->left;
	temp->left = parent;
	return temp;
}

template<typename T>
inline TreeNode<T>* AVLtree<T>::rotation_LL(TreeNode<T>* parent)
{
	TreeNode<T>* temp;
	temp = parent->left;
	parent->left = temp->right;
	temp->right = parent;
	return temp;
}

template<typename T>
inline TreeNode<T>* AVLtree<T>::rotation_LR(TreeNode<T>* parent)
{
	//rotate left subnode(by RR rotation) first and then rotate itself(by LL rotation)
	TreeNode<T>* temp;
	temp = parent->left;
	parent->left = rotation_RR(temp);
	return rotation_LL(parent);
}

template<typename T>
inline TreeNode<T>* AVLtree<T>::rotation_RL(TreeNode<T>* parent)
{
	//rotate right subnode(by LL rotation) first and then rotate itself(by RR rotation)
	TreeNode<T>* temp;
	temp = parent->right;
	parent->right = rotation_LL(temp);
	return rotation_RR(parent);
}

template<typename T>
inline TreeNode<T>* AVLtree<T>::balance(TreeNode<T>* BFNode)
{
	int BF = getBF(BFNode);

	//Left subnode balance is broken
	if (BF > 1) {
		//Left child balance is weird
		if (getBF(BFNode->left) > 0) {
			BFNode = rotation_LL(BFNode);
		}
		//Right child balance is weird
		else {
			BFNode = rotation_LR(BFNode);
		}
	}
	//Right subnode balance is broken
	else if (BF < -1) {
		//Left child balance is weird
		if (getBF(BFNode->right) > 0) {
			BFNode = rotation_RL(BFNode);
		}
		//Right child balance is weird
		else {
			BFNode = rotation_RR(BFNode);
		}
	}
	return BFNode;
}

//add the nodes that contains the item to the tree
template<typename T>
inline int AVLtree<T>::addT(const T & inItem)
{
	if (root == NULL) {
		root = new TreeNode<T>;
		root->left = NULL;
		root->right = NULL;
		root->item = inItem;
		return 1;
	}
	if (isFound(inItem)) {
		return 0;
	}
	else if (inItem > root->item) {
		root->right = insertT(root->right, inItem);
		root = balance(root);
		return 1;
	}
	else if (inItem < root->item) {
		root->left = insertT(root->left, inItem);
		root = balance(root);
		return 1;
	}
	return 0;
}

//add the nodes that contains the item to the tree
template<typename T>
inline TreeNode<T>* AVLtree<T>::insertT(TreeNode<T>* root, const T & inItem)
{
	if (root == NULL) {
		root = new TreeNode<T>;
		root->left = NULL;
		root->right = NULL;
		root->item = inItem;
		return root;
	}
	else if (inItem > root->item) {
		root->right = insertT(root->right, inItem);
		root = balance(root);
	}
	else if (inItem < root->item) {
		root->left = insertT(root->left, inItem);
		root = balance(root);
	}
	return root;
}

template<typename T>
inline int AVLtree<T>::addNode(TreeNode<T>*& inNode)
{
	T* temp = &(inNode->item);
	if (root == NULL) {
		root = inNode;
		return 1;
	}
	if (isFound(*temp)) {
		return 0;
	}
	else if ((*temp) > root->item) {
		root->right = insertNode(root->right, inNode);
		root = balance(root);
		return 1;
	}
	else if ((*temp) < root->item) {
		root->left = insertNode(root->left, inNode);
		root = balance(root);
		return 1;
	}
}

template<typename T>
inline TreeNode<T>* AVLtree<T>::insertNode(TreeNode<T>* root, TreeNode<T>*& inNode)
{
	T* temp = &(inNode->item);
	if (root == NULL) {
		root = inNode;
		return root;
	}
	else if ((*temp) > root->item) {
		root->right = insertNode(root->right, inNode);
		root = balance(root);
	}
	else if ((*temp) < root->item) {
		root->left = insertNode(root->left, inNode);
		root = balance(root);
	}
	return root;
}

//find the exact item in the tree and delete that item
template<typename T>
inline int AVLtree<T>::deleteT(const T & inItem)
{
	if (root == NULL) {
		return 0;
	}
	if (root->item == inItem) {
		deleteNode(root);
		root = balance(root);
		return 1;
	}
	else if (root->item > inItem) {
		if (deleteTreculsively(root->left, inItem)) {
			root = balance(root);
			return 1;
		}
		return 0;
	}
	else if (root->item < inItem) {
		if (deleteTreculsively(root->right, inItem)) {
			root = balance(root);
			return 1;
		}
		return 0;
	}
	return 0;
}

//find the exact item in the tree and delete that item
template<typename T>
inline int AVLtree<T>::deleteTreculsively(TreeNode<T> *& root, const T & inItem)
{
	if (root == NULL) {
		return 0;
	}
	if (root->item == inItem) {
		deleteNode(root);
		root = balance(root);
		return 1;
	}
	else if (root->item > inItem) {
		if (deleteTreculsively(root->left, inItem)) {
			root = balance(root);
			return 1;
		}
		return 0;
	}
	else if (root->item < inItem) {
		if (deleteTreculsively(root->right, inItem)) {
			root = balance(root);
			return 1;
		}
		return 0;
	}
	return 0;
}

//delete specific node from the tree
template<typename T>
inline int AVLtree<T>::deleteNode(TreeNode<T> *& root)
{
	if (root == NULL) {
		return 0;
	}
	else if (root->left != NULL) {
		TreeNode<T>* temp;
		temp = root->left;
		//get the right most node of left sub tree of found node
		if (getRightMostLeaf(root->left, temp)) {
			NULLRightMostLeaf(root->left);
			temp->left = root->left;
			temp->right = root->right;
			//deallocate item
			delete root;
			root = temp;
		}
		//if there is no right sub tree of root->left
		else {
			temp->right = root->right;
			//deallocate item
			delete root;
			root = temp;
		}
		return 1;
	}
	else if (root->left == NULL) {
		TreeNode<T>* temp;
		temp = root->right;
		//deallocate item
		delete root;
		root = temp;
		return 1;
	}
	return 0;
}

template<typename T>
inline int AVLtree<T>::deleteTtemporarily(const T & inItem, TreeNode<T>*& result)
{
	if (root == NULL) {
		return 0;
	}
	if (root->item == inItem) {
		deleteNodeTemporarily(root, result);
		root = balance(root);
		return 1;
	}
	else if (root->item > inItem) {
		if (deleteTtemporarilyReculsively(root->left, inItem, result)) {
			root = balance(root);
			return 1;
		}
		return 0;
	}
	else if (root->item < inItem) {
		if (deleteTtemporarilyReculsively(root->right, inItem, result)) {
			root = balance(root);
			return 1;
		}
		return 0;
	}
	return 0;
}

template<typename T>
inline int AVLtree<T>::deleteTtemporarilyReculsively(TreeNode<T>*& root, const T & inItem, TreeNode<T>*& result)
{
	if (root == NULL) {
		return 0;
	}
	if (root->item == inItem) {
		deleteNodeTemporarily(root, result);
		root = balance(root);
		return 1;
	}
	else if (root->item > inItem) {
		if (deleteTtemporarilyReculsively(root->left, inItem, result)) {
			root = balance(root);
			return 1;
		}
		return 0;
	}
	else if (root->item < inItem) {
		if (deleteTtemporarilyReculsively(root->right, inItem, result)) {
			root = balance(root);
			return 1;
		}
		return 0;
	}
	return 0;
}

//delete specific node from the tree,the item in the node won't be deleted
template<typename T>
inline int AVLtree<T>::deleteNodeTemporarily(TreeNode<T>*& root, TreeNode<T>*& result)
{
	if (root == NULL) {
		return 0;
	}
	else if (root->left != NULL) {
		TreeNode<T>* temp;
		temp = root->left;
		//get the right most node of left sub tree of found node
		if (getRightMostLeaf(root->left, temp)) {
			NULLRightMostLeaf(root->left);
			temp->left = root->left;
			temp->right = root->right;
			result = root;
			root = temp;
		}
		//if there is no right sub tree of root->left
		else {
			temp->right = root->right;
			result = root;
			root = temp;
		}
		return 1;
	}
	else if (root->left == NULL) {
		TreeNode<T>* temp;
		temp = root->right;
		result = root;
		root = temp;
		return 1;
	}
	return 0;
}

//get the right most of certain node or subnode
template<typename T>
inline int AVLtree<T>::getRightMostLeaf(TreeNode<T>* root, TreeNode<T>*& temp)
{
	if (root->right == NULL) {
		return 0;
	}
	else {
		temp = root->right;
		getRightMostLeaf(root->right, temp);
		return 1;
	}
}

//make right most leaf to NULL(not deleting, just make NULL)
template<typename T>
inline int AVLtree<T>::NULLRightMostLeaf(TreeNode<T>* root)
{
	//do this task while the right child of the node is exist
	while (root->right != NULL) {
		if (root->right->right == NULL) {
			root->right = NULL;
		}
		else {
			root = root->right;
		}
	}
	return 1;
}

//enqueue item to the inQue in order of in-order
template<typename T>
inline void AVLtree<T>::resetList()
{
	if (root == NULL) {
		return;
	}
	else {
		inOrder(root->left, inQue);
		inQue.enQueue(&(root->item));
		inOrder(root->right, inQue);
	}
}

//get the next item of current node pointer in order of in-order
template<typename T>
inline void AVLtree<T>::getNextT(T* & inItem)
{
	T* temp;
	inQue.deQueue(temp);
	inItem = temp;
}

//find the item which is same with input parameter, be care of inItem will points found item
template<typename T>
inline int AVLtree<T>::findT(T *& inItem)
{
	if (root == NULL) {
		return 0;
	}
	if (root->item == (*inItem)) {
		inItem = &(root->item);
		return 1;
	}
	else if (root->item > (*inItem)) {
		if (findTreculsively(root->left, inItem)) {
			return 1;
		}
	}
	else if (root->item < (*inItem)) {
		if (findTreculsively(root->right, inItem)) {
			return 1;
		}
	}
	return 0;
}

//find the item which is same with input parameter, be care of inItem will points found item
template<typename T>
inline int AVLtree<T>::findTreculsively(TreeNode<T> *& root, T *& inItem)
{
	if (root == NULL) {
		return 0;
	}
	if (root->item == (*inItem)) {
		inItem = &(root->item);
		return 1;
	}
	else if (root->item > (*inItem)) {
		if (findTreculsively(root->left, inItem)) {
			return 1;
		}
	}
	else if (root->item < (*inItem)) {
		if (findTreculsively(root->right, inItem)) {
			return 1;
		}
	}
	return 0;
}

//find the item which is same with input parameter
template<typename T>
inline bool AVLtree<T>::isFound(const T & inItem)
{
	T* temp = new T;
	(*temp) = inItem;
	if (root == NULL) {
		return false;
	}
	if (root->item == inItem) {
		return true;
	}
	else if (root->item > (inItem)) {
		if (findTreculsively(root->left, temp)) {
			return true;
		}
	}
	else if (root->item < (inItem)) {
		if (findTreculsively(root->right, temp)) {
			return true;
		}
	}
	return false;
}

//get the number of nodes inside the tree
template<typename T>
inline int AVLtree<T>::countNodes(TreeNode<T>* root)
{
	if (root == NULL) {
		return 0;
	}
	return countNodes(root->left) + countNodes(root->right) + 1;
}

//enqueue item to the Queue in order of input parameter 'order'
template<typename T>
inline void AVLtree<T>::resetList(OrderType order)
{
	switch (order)
	{
	case PRE_ORDER:
		preOrder(root, preQue);
		break;
	case IN_ORDER:
		inOrder(root, inQue);
		break;
	case POST_ORDER:
		postOrder(root, postQue);
		break;
	default:
		break;
	}
}

//get the next item of current node pointer
template<typename T>
inline void AVLtree<T>::getNextT(T *& inItem, OrderType order)
{
	T* temp;
	switch (order)
	{
	case PRE_ORDER:
		preQue.deQueue(temp);
		inItem = temp;
		break;
	case IN_ORDER:
		inQue.deQueue(temp);
		inItem = temp;
		break;
	case POST_ORDER:
		postQue.deQueue(temp);
		break;
	default:
		break;
	}
}

//enqueue item to the inQue in order of in-order
template<typename T>
inline int AVLtree<T>::inOrder(TreeNode<T>* root, Queue<T*>& inQue)
{
	if (root == NULL) {
		return 0;
	}
	else {
		inOrder(root->left, inQue);
		inQue.enQueue(&(root->item));
		inOrder(root->right, inQue);
		return 1;
	}
	return 0;
}

//enqueue item to the preQue in order of pre-order
template<typename T>
inline int AVLtree<T>::preOrder(TreeNode<T>* root, Queue<T*>& preQue)
{
	if (root == NULL) {
		return 0;
	}
	else {
		preQueue.enQueue(&(root->item));
		preOrder(root->left, preQue);
		preOrder(root->right, preQue);
		return 1;
	}
	return 0;
}

//enqueue item to the postQue in order of post-order
template<typename T>
inline int AVLtree<T>::postOrder(TreeNode<T>* root, Queue<T*>& postQue)
{
	if (root == NULL) {
		return 0;
	}
	else {
		postOrder(root->left, postQue);
		postOrder(root->right, postQue);
		postQueue.enQueue(&(root->item));
		return 1;
	}
	return 0;
}

template<typename T>
inline int AVLtree<T>::max(int a, int b) const
{
	if (a > b) {
		return a;
	}
	else {
		return b;
	}
}

#endif _AVLTREE_H