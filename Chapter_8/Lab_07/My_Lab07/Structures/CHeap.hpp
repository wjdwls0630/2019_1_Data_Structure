//
// Created by ParkJungJin on 2019-05-27.
//

#ifndef _CHEAP_HPP
#define _CHEAP_HPP

#include "HeapNode.hpp"
#include "Comparer.hpp"

#define ASCENDING 1
#define DESCENDING 0

#define MAXSIZE 100
/**
*	CHeap
*	@author	ParkJungJin
*	@date	2019.05.23
*/

/**
 *	@brief	CHeap class.
 *	@details	specialized tree-based data structure which is essentially an almost complete tree
 *	that satisfies the heap property
 */
template <typename T>
class CHeap{
private :
    HeapNode<T> *h_pHeap;			/// array
    int h_iLastNode;	/// end of array
    int h_nMaxSize;		/// maxsize of arry
    int h_Direction; /// ASCENDING(1) minheap, DESCENDING(0) maxheap
    Comparer<T> h_Comparer; /// set Compare (for direction)
public :
    /**
     *	default constructor.
     */
    CHeap():h_pHeap(nullptr), h_iLastNode(0), h_nMaxSize(MAXSIZE),  h_Direction(ASCENDING), h_Comparer(ASCENDING){}

    /**
    *	h_Direction constructor.
    */
    CHeap(const int &Direction):
    h_pHeap(nullptr), h_iLastNode(0), h_nMaxSize(MAXSIZE), h_Direction(Direction), h_Comparer(Direction){}
    // ASCENDING(1): ascending order,  DESCENDING(0): descending order

    /**
     *  copy constructor.
     */
    CHeap(CHeap<T> &ch) : h_pHeap(nullptr), h_iLastNode(ch.h_iLastNode), h_nMaxSize(ch.h_nMaxSize),
    h_Direction(ch.h_Direction), h_Comparer(ch.h_Direction){
        if (ch.h_iLastNode!=0) {
            this->h_pHeap = new HeapNode<T>[ch.h_nMaxSize];
            for (int i = 0; i < ch.h_Length; i++) {
                *this->h_pHeap[i] = *ch.h_pHeap[i];
            }
        }
    }

    /**
    *	Destructor.
    */
    virtual ~CHeap(){
        if (!this->IsEmpty()) {
            this->MakeEmpty();
        }
    }

    /**
    *	@brief	Check heap is empty.
    *	@pre	none.
    *	@post	none.
    *	@return	return true if heap is empty, otherwise return false.
    */
    bool IsEmpty();

    /**
      *	@brief	Check heap is full.
      *	@details return true h_iLastNode arrive maxsize
      *	@pre	none.
      *	@post	none.
      *	@return	return true if heap is full, otherwise return false.
      */
    bool IsFull();

    /**
      *	@brief	Get a number of Node in current heap.
      *	@pre	none.
      *	@post	none.
      *	@return	number of Node in current heap.
      */
    int GetLength() const;

    /**
     *	@brief	Get Direction.
     *	@pre	none.
     *	@post	none.
     *	@return	Get Direction of tree.
     */
    int GetDirection() const { return this->h_Direction; }

    /**
     *	@brief	Set Direction.
     *	@pre	none.
     *	@post	Set Direction.
     *	@param Direction to set.
     */
    void SetDirection(int inDirection) {
        if (this->h_Direction!=inDirection) {
            this->h_Direction=inDirection;
            this->h_Comparer.SetDirection(inDirection);
            this->Sort();
            return ;
        }
        // if direction is same , do nothing
    }

    /**
    *	@brief	Initialize heap to empty state.
    *	@pre	None
    *	@post	heap is empty.
    */
    void MakeEmpty();

    /**
    *	@brief	Add item into appropriate spot of this heap.
    *	@pre	heap is not full. item is not in heap.
    *	@post	heap is inserted in this list.
    *	@return	1 if this function works well, otherwise 0.
    */
    int Add(T data);

    /**
    *	@brief	Delete item from this heap.
    *	@pre	heap is not empty. the heap exists in list.
    *	@post	heap is deleted from this list.
    *	@return	1 if this function works well, otherwise 0.
    */
    int Delete(T data);

    /**
     *	@brief	Delete item from this heap.
     *	@details call recursively and find (binary search)
     *	@pre	heap should be initialized. the item exists in tree.
     *	@post	Item is deleted from this tree. iParent is curret position
     *	@param  data to delete ,
     *	@return	1 if this function works well, otherwise 0.
     */
    int DeleteRecur(T data , int iParent);

    /**
     *	@brief  Remove the First data from the heap, if Queue is empty throw EmptyHeap Exception
     *	@pre	heap should be initialized.
     *	@post	Remove the First data from the heap.
     * @return return data deleted.
     */
    T Dequeue();

    /**
    *	@brief	get the data which has same in the heap.(Binary Search)
    *	@pre	data to search should be initialized
    *	@param	data that you want(search) to get.
    *	@return	return 1 if this function works well, otherwise 0.
    */
    int Get(T &data);

    /**
     *	@brief	get the data which has same in the tree.(Binary Search)
     *	@details check all nodes in tree by recursive
     *	@pre	data to search should be initialized
     *	@param	data that you want(search) to get. iParent is current position
     *	@return	return 1 if this function works well, otherwise 0.
     */
    int GetRecur(T &data, int iParent);

    /**
    *	@brief	Display all data in Heap.
    *	@pre	Heap is initialized
    *	@post	Display all data in Heap.
    */
    void DisplayAll();

    /**
    *	@brief	by moving top to bottom, compare and swap data
    *	@pre	Heap is initialized.
    *	@post	compare data and swap.
    *	@param	iparent	data moved from top to bottom.
    *	@param	ibottom	last data.
    */
    void ReheapDown(int iParent, int iBottom);

    /**
    *	@brief	by moving bottom to top, compare and swap data.
    *	@pre	Heap is initialized.
    *	@post	compare data and swap.
    *	@param	iroot	first data.
    *	@param	ibottom	data moved from bottom to top.
    */
    void ReheapUp(int iRoot, int iBottom);

    /**
    *	@brief	swap the data in heap.
    *	@pre	data is existed in heap.
    *	@post	swap two data.
    *	@param	iparent	Top data to change.
    *	@param	ibottom	Bottom data to change.
    */
    void Swap(int iParent, int iBottom);

    /**
     *	@brief	Sort item from this list.
     *	@pre	List is not empty. the item exists in list.
     *	@post	List is sorted.
     * @param Compare criteria.
     *	@return	1 if this function works well, otherwise 0.
     */
    void Sort();

    /**
     *	@brief	Doing Deep copy by copy assignment operator.
     *	@pre	List set info.
     *	@post	object copy data by deep.
     *	@param	List that you want to be copied.
     *	@return	return self-reference if self and List is not same object, otherwise self that unchanged.
     */
    CHeap<T>& operator= (CHeap<T>& ch);



};


// Check Heap is empty.
template <typename T>
bool CHeap<T>::IsEmpty(){
    if(this->h_iLastNode == 0){
        return 1;
    }
    return 0;
}


// Check heap is full.
template <typename T>
bool CHeap<T>::IsFull(){
    if(this->h_iLastNode == this->h_nMaxSize){
        return 1;
    }
    return 0;
}

// Get a number of Node in current heap.
template <typename T>
int CHeap<T>::GetLength() const{
    return this->h_iLastNode;
}


// Initialize heap to empty state.
template <typename T>
void CHeap<T>::MakeEmpty(){
    if (!this->IsEmpty()) {
        delete [] this->h_pHeap;
        this->h_iLastNode =0;
    }
}


// Add item into appropriate spot of this heap.
template <typename T>
int CHeap<T>::Add(T data){
    if (this->IsFull()) {
        std::cout<<"Heap is Full"<<'\n';
        return 0;
    }
    HeapNode<T> NewNode;
    NewNode.SetData(data);
    if (this->IsEmpty()) {
        //allocate memory
        this->h_pHeap = new HeapNode<T> [this->h_nMaxSize];

        //no need to sort
        this->h_pHeap[this->h_iLastNode] = NewNode;
        this->h_iLastNode++;
        return 1;
    }


    if (!this->Get(data)) {
        //if it is not empty
        this->h_pHeap[this->h_iLastNode] = NewNode;

        this->ReheapUp(0, this->h_iLastNode);
        this->h_iLastNode++;
        //there is not overlapped data in tree
        return 1;
    }
    //if data is overlap
    return 0;
}


// Delete item from this heap.
template <typename T>
int CHeap<T>::Delete(T data){
    // if tree is empty
    if (this->IsEmpty()) {
        return 0;
    }

    if (this->Get(data)) {
        // if data is in the tree
        this->DeleteRecur(data, 0);
        this->h_iLastNode--;
        return 1;
    }
    //if data is not in the tree
    return 0;
}

// Delete item from this heap.
template<typename T>
int CHeap<T>::DeleteRecur(T data, int iParent) {
    int LeftChild; // left child
    int RightChild; // right child

    LeftChild = iParent*2 + 1;
    RightChild = iParent*2 + 2;

    if(this->h_Comparer.IsEqual(this->h_pHeap[iParent].GetData(), data)) {
        // if found data
        this->h_pHeap[iParent].SetData(this->h_pHeap[this->h_iLastNode-1].GetData());
        this->ReheapDown(iParent, this->h_iLastNode-2); //sort
        return 1;
    } else if ( LeftChild< this->h_iLastNode){
        return this->DeleteRecur(data, LeftChild); // move left
    } else if (RightChild< this->h_iLastNode){
        return this->DeleteRecur(data, RightChild); // move right
    }
    //if not found
    return 0;
}



// Remove the First data from the heap, if Queue is empty throw EmptyHeap Exception
template <typename T>
T CHeap<T>::Dequeue(){
    if (!this->IsEmpty()) {
        T data = this->h_pHeap[0].GetData();
        this->Delete(data); // delete first data
        return data;
    }
}


// get the data which has same in the heap.(Binary Search)
template <typename T>
int CHeap<T>::Get(T &data) {
    if (this->IsEmpty()) {
        return 0;
    }
    return this->GetRecur(data, 0); //search data
}


// get the data which has same in the tree.(Binary Search)
template <typename T>
int CHeap<T>::GetRecur(T &data, int iParent){
    int LeftChild; // left child
    int RightChild; // right child

    LeftChild = iParent*2 + 1;
    RightChild = iParent*2 + 2;

    if(this->h_Comparer.IsEqual(this->h_pHeap[iParent].GetData(), data)){
        //if found
        data = this->h_pHeap[iParent].GetData();
        //data ->operator=(this->h_pHeap[iParent].GetData());
        return 1;
    }
    if (LeftChild < this->h_iLastNode) {
        return this->GetRecur(data, LeftChild); //move to left
    }
    if (RightChild < this->h_iLastNode){
        return this->GetRecur(data, RightChild); //move to right
    }
    return 0;
}


//Display all data in Heap.
template <typename T>
void CHeap<T>::DisplayAll(){
    for(int i=0; i<this->h_iLastNode; i++){
        std::cout << h_pHeap[i].GetData() <<' ';
    }
    std::cout<<'\n';
}

// by moving top to bottom, compare and swap data
template<typename T>
void CHeap<T>::ReheapDown(int iParent, int iBottom) {
    int MaxChild; // current ptr in array
    int LeftChild; // Left child
    int RightChild;// Right child

    LeftChild = iParent*2 + 1;
    RightChild = iParent*2 + 2;

    if ( LeftChild <= iBottom ){
        if ( LeftChild == iBottom ){
            MaxChild= LeftChild;
        } else {
            if (this->h_Comparer.Compare(this->h_pHeap[RightChild].GetData(), this->h_pHeap[LeftChild].GetData())){
                //ASCENDING(1) MinHeap
                //DESCENDING(0) MaxHeap
                MaxChild= RightChild;
            } else {
                MaxChild =LeftChild;
            }
        }
        if (this->h_Comparer.Compare(this->h_pHeap[MaxChild].GetData(), this->h_pHeap[iParent].GetData())){
            this->Swap(iParent, MaxChild);
            this->ReheapDown(MaxChild, iBottom);
        }
    }

}

// by moving bottom to top, compare and swap data.
template<typename T>
void CHeap<T>::ReheapUp(int iRoot, int iBottom) {
    int iParent ; // Parent
    if ( iBottom > iRoot ){
        iParent = (iBottom -1) / 2;
        if (this->h_Comparer.Compare(this->h_pHeap[iBottom].GetData(), this->h_pHeap[iParent].GetData())) {
            //ASCENDING(1) MinHeap
            //DESCENDING(0) MaxHeap
            this->Swap(iParent, iBottom); //swap two data
            this->ReheapUp(iRoot, iParent); // go up and re sort
        }
    }

}


// swap the data in heap.
template <typename T>
void CHeap<T>::Swap(int iParent, int iBottom){
    HeapNode<T> temp = this->h_pHeap[iParent];
    this->h_pHeap[iParent] = this->h_pHeap[iBottom];
    this->h_pHeap[iBottom] = temp;
}

// Sort item from this list.
template<typename T>
void CHeap<T>::Sort() {
    //re-make heap
    //first deep copy original
    CHeap<T> temp ;
    for (int i = 0; i < this->h_iLastNode; i++) {
        temp.Add(this->h_pHeap[i].GetData());
    }

    *this = temp;
}

// Doing Deep copy by copy assignment operator.
template<typename T>
CHeap<T> &CHeap<T>::operator=(CHeap<T> &ch) {
    if (this!=&ch) {
        if (this->GetLength()!=0) {
            this->MakeEmpty(); // reset heap
            this->h_pHeap= nullptr;
        }

        if (ch.GetLength()!=0) {
            this->h_pHeap = new HeapNode<T>[ch.h_nMaxSize];
            for (int i = 0; i < ch.h_iLastNode; ++i) {
                this->h_pHeap[i] = ch.h_pHeap[i];
            }
        }


        //set other property
        this->h_nMaxSize = ch.h_nMaxSize;
        this->h_iLastNode = ch.h_iLastNode;
        this->h_Direction = ch.h_Direction;
        this->h_Comparer.SetDirection(this->h_Direction);
    }
    return *this;
}

#endif //_CHEAP_HPP
