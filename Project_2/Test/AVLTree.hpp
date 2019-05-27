//
// Created by ParkJungJin on 2019-05-26.
//

#ifndef _AVLTREE_HPP
#define _AVLTREE_HPP

#include "BinarySearchTree.hpp"

template <typename T>
class AVLTree : public BinarySearchTree<T>{
public:
    /**
     *	default constructor.
     */
    AVLTree():BinarySearchTree<T>(ASCENDING){}

    /**
     *	dsl_Direction constructor.
     */
    AVLTree(const int &inDirection) : BinarySearchTree<T>(inDirection){}

    // ASCENDING(1): ascending order(Left is small Right is big)
    // DESCENDING(0): descending order(Left is big Right is small)

    /**
     *	copy constructor. (deep copy)
     */
    AVLTree(const AVLTree &avlt) :BinarySearchTree<T>(avlt.bt_Direction){
        //copy all nodes
        this->CopyNodeRecur(avlt.GetRoot());
    }

    /**
     *	destructor.
     */
    virtual ~AVLTree() {}

    /**
     *	@brief	Set Direction.
     *	@pre	none.
     *	@post	Set Direction.
     *	@param Direction to set.
     */
     void SetDirection(int inDirection=ASCENDING) override {
        //re-make tree
        //first deep copy original
        AVLTree<T> *temp  = new AVLTree<T>;
        *temp = *this;

        //set direction
        this->bt_Direction = inDirection;
        this->bt_Comparer.SetDirection(inDirection);

        //copy again
        this->MakeEmpty();//reset tree
        this->CopyNodeRecur(temp->GetRoot());

        //de-allocation memory
        delete temp;

    }

    /**
     *	@brief	Sort item from this list.
     *	@pre	List is not empty. the item exists in list.
     *	@post	List is sorted.
     * @param Compare criteria.
     *	@return	1 if this function works well, otherwise 0.
     */
    void Sort() override;
    int GetBalanceFactor(BNodeType<T>* Node);
    BNodeType<T>* RotationRR(BNodeType<T>* Parent_Node);
    BNodeType<T>* RotationLL(BNodeType<T>* Parent_Node);
    BNodeType<T>* RotationRL(BNodeType<T>* Parent_Node);
    BNodeType<T>* RotationLR(BNodeType<T>* Parent_Node);
    BNodeType<T>* ReBalance(BNodeType<T>* Parent_Node);


    /**
     *	@brief	Add item into appropriate spot of tree.
     *	@details data must not be overlaped
     *	@pre	tree is not full. item is not in list.
     *	@post	Item is inserted in this tree.
     *	@return	1 if this function works well, otherwise 0.
     */
    int Add(T data) override ;

    /**
     *	@brief	Add item into appropriate spot of tree.
     *	@details call recursive to search appropiate spot
     *	@pre	tree is not full. item is not in list.
     *	@post	Item is inserted in this tree.
     *	@return	1 if this function works well, otherwise 0.
     */
    BNodeType<T>* AddAVLRecur(BNodeType<T>* Parent_Node, T& data);

    /**
     *	@brief	Doing Deep copy by copy assignment operator.
     *	@pre	List set info.
     *	@post	object copy data by deep.
     *	@param	List that you want to be copied.
     *	@return	return self-reference if self and List is not same object, otherwise self that unchanged.
     */
    AVLTree<T>& operator= (AVLTree<T>& avlt);


};

template<typename T>
int AVLTree<T>::GetBalanceFactor(BNodeType<T> *Node) {
    int H_Left;
    int H_Right;
    if (Node == nullptr) {
        return 0;
    }
    if (Node->IsLeaf()) {
        //no difference height
        return 0;
    } else if (Node->GetLeftLink()==nullptr||Node->GetRightLink()==nullptr) {
        //if empty node has, calculate it -1
        if (Node->GetLeftLink()!=nullptr) {
            //has only left child
            H_Left = this->HeightNode(Node->GetLeftLink());
            return H_Left - 1;
        } else {
            //has only right child
            H_Right = this->HeightNode(Node->GetRightLink());
            return H_Right - 1;
        }
    } else {
        //if node has both child
        H_Left = this->HeightNode(Node->GetLeftLink());
        H_Right = this->HeightNode(Node->GetRightLink());
        return H_Left - H_Right;
    }
}

template<typename T>
BNodeType<T> *AVLTree<T>::RotationRR(BNodeType<T> *Parent_Node) {
    if (Parent_Node==nullptr) { //if empty node return null
        return nullptr;
    } else if (Parent_Node->IsLeaf()||Parent_Node->GetRightLink()== nullptr){
        //if node is leaf or has no right child return self
        return Parent_Node;
    } else {
        /*
 * p
 *   \
 *     c
 *    /
 *   c1*/
        BNodeType<T>* Child = Parent_Node->GetRightLink();
        /*
         * p
         * |
         * |    c
         *  \  /
         *   c1
        */
        Parent_Node->SetRightLink(Child->GetLeftLink());
        /*
     *    c
     *  /
     * p
     *  \
     *   c1
    */
        Child->SetLeftLink(Parent_Node);
        return Child;

    }
}

template<typename T>
BNodeType<T> *AVLTree<T>::RotationLL(BNodeType<T> *Parent_Node) {
    if (Parent_Node==nullptr) { //if empty node return null
        return nullptr;
    } else if (Parent_Node->IsLeaf()||Parent_Node->GetLeftLink()== nullptr){
        //if node is leaf or node has no left child return self
        return Parent_Node;
    } else{
        /*
         *     p
         *   /
         * c
         *  \
         *   c1*/
        BNodeType<T>* Child = Parent_Node->GetLeftLink();
        /*
         *     p
         *     |
         * c   |
         *  \  |
         *   c1*/
        Parent_Node->SetLeftLink(Child->GetRightLink());
        /*
         *    c
         *     \
         *      p
         *     /
         *   c1
         */
        Child->SetRightLink(Parent_Node);
        return Child;
    }
}

template<typename T>
BNodeType<T> *AVLTree<T>::RotationRL(BNodeType<T> *Parent_Node) {
    if (Parent_Node==nullptr) { //if empty node return null
        return nullptr;
    } else if (Parent_Node->IsLeaf()){
        //if node is leaf return self
        return Parent_Node;
    } else{
        BNodeType<T>* Child = Parent_Node->GetRightLink();
        Parent_Node -> SetRightLink(this->RotationLL(Child));
        return this->RotationRR(Parent_Node);
    }
}

template<typename T>
BNodeType<T> *AVLTree<T>::RotationLR(BNodeType<T> *Parent_Node) {
    if (Parent_Node==nullptr) { //if empty node return null
        return nullptr;
    } else if (Parent_Node->IsLeaf()){
        //if node is leaf return self
        return Parent_Node;
    } else{
        BNodeType<T>* Child = Parent_Node->GetLeftLink();
        Parent_Node -> SetLeftLink(this->RotationRR(Child));
        return this->RotationLL(Parent_Node);
    }
}

template<typename T>
BNodeType<T> *AVLTree<T>::ReBalance(BNodeType<T> *Parent_Node) {
    int bf = this->GetBalanceFactor(Parent_Node); //balance factor
    //if bf is 0 parent node is 0, there is no case that rise error that Parent Node has no link
    if (bf>1) {
        //case 1: unbalance in left
        if (this->GetBalanceFactor(Parent_Node->GetLeftLink()) > 0) {
            //problem in left child
            Parent_Node = this->RotationLL(Parent_Node);
        } else {
            //problem in right child
            Parent_Node = this->RotationLR(Parent_Node);
        }
    } else if (bf < -1) {
        //case 2: unbalance in right
        if (this->GetBalanceFactor(Parent_Node->GetRightLink()) < 0) {
            //problem in right child
            Parent_Node = this->RotationRR(Parent_Node);
        } else {
            //problem in left child
            Parent_Node = this->RotationRL(Parent_Node);
        }
    }
    return Parent_Node;
}

template<typename T>
int AVLTree<T>::Add(T data) {
    if (this->IsEmpty()) {
        BNodeType<T>* NewNode = new BNodeType<T>;
        NewNode->SetData(data);
        this->SetRoot(NewNode);
        return 1;
    }

    if (!this->Get(data)) {
        //there is no overlap data in tree
        this->SetRoot(this->AddAVLRecur(this->Root, data));
        return 1;
    }
    //if data is overlap
    return 0;
}

template<typename T>
BNodeType<T> *AVLTree<T>::AddAVLRecur(BNodeType<T> *Parent_Node, T &data) {
    //overlap data is already filtered in Add func
    if (this->bt_Comparer.Compare(data, Parent_Node->GetData())) {
        //ASCENDING(1) data < Node->GetData()
        //DESCENDING(0) data > Node->GetData()
        if (Parent_Node->GetLeftLink()!= nullptr) {
            //if node has left child
            Parent_Node->SetLeftLink(this->AddAVLRecur(Parent_Node->GetLeftLink(), data));
        } else {
            //if node has no left child
            BNodeType<T> * NewNode = new BNodeType<T>;
            NewNode->SetData(data);
            Parent_Node->SetLeftLink(NewNode);
        }
    } else if (this->bt_Comparer.Op_Compare(data, Parent_Node->GetData())){
        //ASCENDING(1) data > Node->GetData()
        //DESCENDING(0) data < Node->GetData()
        if (Parent_Node->GetRightLink()!= nullptr) {
            //if node has left child
            Parent_Node->SetRightLink(this->AddAVLRecur(Parent_Node->GetRightLink(), data));
        } else {
            //if node has no left child
            BNodeType<T> * NewNode = new BNodeType<T>;
            NewNode->SetData(data);
            Parent_Node->SetRightLink(NewNode);
        }
    }
    return this->ReBalance(Parent_Node);
}

template<typename T>
AVLTree<T> &AVLTree<T>::operator=(AVLTree<T> &avlt) {
    if (this!=&avlt) {
        if (this->GetCount()!=0) {
            this->MakeEmpty(); // reset tree
        }
        this->CopyNodeRecur(avlt.Root);

        //set other property
        this->bt_Direction = avlt.bt_Direction;
        this->bt_Comparer.SetDirection(this->bt_Direction);
    }
    return *this;
}

template<typename T>
void AVLTree<T>::Sort() {
    //re-make tree - to set new criteria
    //first deep copy original
    AVLTree<T> *temp  = new AVLTree<T>;
    *temp = *this;

    //copy
    this->MakeEmpty();//reset tree
    this->CopyNodeRecur(temp->GetRoot());

    //de-allocation memory
    delete temp;

}

#endif //_AVLTREE_HPP
