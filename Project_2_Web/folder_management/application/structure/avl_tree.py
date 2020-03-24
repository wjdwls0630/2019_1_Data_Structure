# Created by ParkJungJin on 2019-05-26.

"""@package docstring
@brief	avl_tree class.
@details	This class processes balancing tree
"""

from folder_management.application.structure.binary_search_tree import *
from folder_management.application.structure.comparer import ASCENDING
from copy import deepcopy


class AVLTree(BinarySearchTree):

    """
    default constructor.
    """
    def __init__(self, in_direction=ASCENDING):
        super().__init__(in_direction)

    # ASCENDING(1): ascending order(Left is small Right is big)
    # DESCENDING(0): descending order(Left is big Right is small)


    """
    destructor.
    """
    def __del__(self):
        super(AVLTree, self).__del__()

    # Get && Set

    """
    @brief	Set Direction.
    @details call this func reset the tree by direction order
    @pre	none.
    @post	Set Direction.
    @param Direction to set.
    """
    def set_direction(self, in_direction=ASCENDING):
        # re-make tree
        # first deep copy original
        temp =AVLTree()
        temp = deepcopy(self)

        # set direction
        self.bt_direction = in_direction
        self.bt_comparer.set_direction(in_direction)

        # copy again
        self.make_empty()  # reset tree
        self.copy_node_recur(temp.get_root())


        # de-allocation memory
        del temp


    # For ReBalance tree

    """
    @brief	Get a BalanceFactor of Node.
    @details call HeigthNode() and calculate left and right height difference(left - right)
    @pre	Node is initialize.
    @post	none.
    @param Node to get balance factor
    @return	return BalanceFactor of Node.
    """
    def get_balance_factor(self, node: BNodeType) -> int:
        if node is None:
            return -1

        if node.is_leaf():
            # no difference height
            return 0

        elif node.get_left_link() is None or node.get_right_link() is None:

            # if empty node has, calculate it -1
            if node.get_left_link() is not None:
                # has only left child
                h_left = self.height_node(node.get_left_link())
                return h_left+1 #(h_left-(-1)
            else:
                # has only right child
                h_right = self.height_node(node.get_right_link())
                return -1-h_right

        else:
            # if node has both child
            h_left = self.height_node(node.get_left_link())
            h_right = self.height_node(node.get_right_link())
            return h_left - h_right


    """
    @brief	Right Rotate.
    @details use when Parent Node bf<-1, Parent's right child bf < 0 (right right insert)
    @pre	Parent_Node is initialize.
    @post	Parent Node is rotated right.
    @param Parent_Node to rotate
    @return	return Top level of Node.(Child Node is going to be top level)
    """
    def rotation_rr(self, parent_node: BNodeType) -> BNodeType:
        if parent_node is None:
            return None

        elif parent_node.is_leaf() or parent_node.get_right_link() is None:
            # if node is leaf or has no right child return self
            return parent_node
        else:
            """
            p
              \
                c
              /
            c1 
            """
            child = parent_node.get_right_link()
            """
            p
            |
            |   c
             \ /
              c1
            """
            parent_node.set_right_link(child.get_left_link())
            """
             c
            /
            p
             \
              c1
            """

            child.set_left_link(parent_node)
            return child


    """
    @brief	Left Rotate.
    @details use when Parent Node bf>1, Parent's left child bf > 0 (left left insert)
    @pre	Parent_Node is initialize.
    @post	Parent Node is rotated left.
    @param Parent_Node to rotate
    @return	return Top level of Node.(Child Node is going to be top level
    """
    def rotation_ll(self, parent_node: BNodeType) -> BNodeType:
        if parent_node is None:
            return None

        elif parent_node.is_leaf() or parent_node.get_left_link() is None:
            # if node is leaf or has no right child return self
            return parent_node

        else:
            """
              p
             /
            c
              \
               c1 
            """
            child = parent_node.get_left_link()

            """
                p
                |
             c  |
              \ |
               c1 
            """
            parent_node.set_left_link(child.get_right_link())
            """
            c
              \
                p
               /
             c1
            """
            child.set_right_link(parent_node)
            return child

    """
    @brief	Right and Left Rotate. Rotate Twice
    @details use when Parent Node bf<-1, Parent's right child bf > 0 (right left insert)
    @pre	Parent_Node is initialize.
    @post	Parent Node is rotated right and left.
    @param Parent_Node to rotate
    @return	return Top level of Node.(Child Node is going to be top level)
    """
    def rotation_rl(self, parent_node: BNodeType) -> BNodeType:
        if parent_node is None:
            return None

        elif parent_node.is_leaf():
            # if node is leaf or has no right child return self
            return parent_node

        else:
            child = parent_node.get_right_link()
            parent_node.set_right_link(self.rotation_ll(child))
            return self.rotation_rr(parent_node)

    """
    @brief	Left and Right Rotate. Rotate Twice
    @details use when Parent Node bf > 1, Parent's left child bf < 0 (left right insert)
    @pre	Parent_Node is initialize.
    @post	Parent Node is rotated left and right.
    @param Parent_Node to rotate
    @return	return Top level of Node.(Child Node is going to be top level)
    """
    def rotation_lr(self, parent_node: BNodeType) -> BNodeType:
        if parent_node is None:
            return None

        elif parent_node.is_leaf():
            # if node is leaf or has no right child return self
            return parent_node

        else:
            child = parent_node.get_left_link()
            parent_node.set_left_link(self.rotation_rr(child))
            return self.rotation_ll(parent_node)
    """
    @brief	Check the BalanceFactor and Rebalance Node and its child
    @pre	Parent_Node is initialize.
    @post	Parent Node is rebalanced.
    @param Parent_Node to rebalance
    @return	return Top level of Node.(Top level Node after rotation)
    """
    def rebalance(self, parent_node: BNodeType) -> BNodeType:
        bf = self.get_balance_factor(parent_node) # balance_factor
        # if bf is 0 parent node is 0, there is no case that rise error that Parent Node has no link
        if bf > 1:
            # case 1: unbalance in left
            if self.get_balance_factor(parent_node.get_left_link()) > 0:
                # problem in left child
                parent_node = self.rotation_ll(parent_node)
            else:
                # problem in right child
                parent_node = self.rotation_lr(parent_node)

        elif bf < -1:
            # case 2: unbalance in right
            if self.get_balance_factor(parent_node.get_right_link()) < 0:
                # problem in right child
                parent_node = self.rotation_rr(parent_node)
            else:
                # problem in left child
                parent_node = self.rotation_rl(parent_node)

        return parent_node


    # data management

    """
    @brief	Add item into appropriate spot of tree.
    @details data must not be overlaped
    @pre	tree is not full. item is not in list.
    @post	Item is inserted in this tree.
    @return	1 if this function works well, otherwise 0.
    """
    def add(self, data) -> int:
        if self.is_empty():
            new_node = BNodeType()
            new_node.set_data(data)
            self.set_root(new_node)
            return 1

        if not self.get(data):
            # there is no overlap data in tree
            self.set_root(self.add_avl_recur(self.root, data))
            return 1

        # if data is overlapped
        return 0

    """
    @brief	Add item into appropriate spot of tree.
    @details call recursive to search appropiate spot
    @pre	tree is not full. item is not in list.
    @post	Item is inserted in this tree.
    @return	1 if this function works well, otherwise 0.
    """
    def add_avl_recur(self, parent_node: BNodeType, data) -> BNodeType:
        # overlapped data is already filtered in Add func
        if self.bt_comparer.compare(data, parent_node.get_data()):
            # ASCENDING(1) data < Node->GetData()
            # DESCENDING(0) data > Node->GetData()
            if parent_node.get_left_link() is not None:
                # if node has left child
                parent_node.set_left_link(self.add_avl_recur(parent_node.get_left_link(), data))
            else:
                # if node has no left child
                new_node = BNodeType()
                new_node.set_data(data)
                parent_node.set_left_link(new_node)

        elif self.bt_comparer.op_compare(data, parent_node.get_data()):
            # ASCENDING(1) data > Node->GetData()
            # DESCENDING(0) data < Node->GetData()
            if parent_node.get_right_link() is not None:
                # if node has left child
                parent_node.set_right_link((self.add_avl_recur(parent_node.get_right_link(), data)))
            else:
                # if node has no right child
                new_node = BNodeType()
                new_node.set_data(data)
                parent_node.set_right_link(new_node)

        return self.rebalance(parent_node)

    """
    @brief	Delete item from this tree.
    @details call recursively and find (binary search) and when it is find, call DeleteNode for de-allocation and rebalance node
    @pre	Parent_Node and Node should be initialized. the item exists in tree.
    @post	Item is deleted from this tree.
    @param Parent_Node to set new link when it is delete, Node for moving, data to find item that want to delete
    @return	1 if this function works well, otherwise 0.
    """
    def delete_recur(self, parent_node: BNodeType, node: BNodeType, data) -> int:
        if self.bt_comparer.compare(data, node.get_data()):
            # ASCENDING(1) data < Node->GetData()
            # DESCENDING(0) data > Node->GetData()
            # move to left
            if node.get_left_link() is None:
                # if node's left child is empty
                return 0

            return self.delete_recur(node, node.get_left_link(), data)

        elif self.bt_comparer.op_compare(data, node.get_data()):
            # ASCENDING(1) data > Node->GetData()
            # DESCENDING(0) data < Node->GetData()
            # move to right
            if node.get_right_link() is None:
                # if node's right child is empty
                return 0

            return self.delete_recur(node, node.get_right_link(), data)

        else:
            # if Node data is equal to data
            self.delete_node(parent_node, node)
            self.rebalance(parent_node)
            return 1

    """
    @brief	Sort item from this tree. (it is not really mean sort, it works when criteria is changed on outer side)
    @pre	criteria is changed and tree is not empty. the item exists in tree.
    @post	tree is sorted.
    @param Compare criteria.
    @return	1 if this function works well, otherwise 0.
    """
    def sort(self) -> int:
        # re - make tree - to set new criteria
        # first deep copy original
        temp = AVLTree()
        temp = deepcopy(self)

        # copy
        self.make_empty()  # reset tree
        self.copy_node_recur(temp.get_root())


        # de - allocation memory
        del temp

        return 1


"""
Test Code
"""
if __name__ == "__main__":
    from random import sample, shuffle

    bt_test = AVLTree()

    bt_test.add(3)
    bt_test.add(2)
    bt_test.add(1)
    bt_test.add(4)
    bt_test.add(5)
    bt_test.add(6)
    bt_test.add(10)
    bt_test.add(7)
    bt_test.add(9)
    bt_test.add(8)
    print("bt_test")
    print("Count : {} \nLeaf : {} \nHeight : {}"
          .format(bt_test.get_count(), bt_test.get_leaf_node_count(), bt_test.get_height()))
    bt_test.print_inorder()
    bt_test.print_preorder()
    bt_test.print_postorder()
    print("\n\n")


    print("bt")
    bt = AVLTree()
    num_list = sample(range(1, 100), 10)
    shuffle(num_list)
    print(num_list)
    for i in range(0, 10):
        bt.add(num_list[i])

    bt.print_inorder()
    print("\n\n")

    print("add 22")
    bt.add(22)
    bt.print_inorder()
    print("\n\n")

    target = 22
    print("get 22 : {}".format(bool(bt.get(target))))
    print("\n\n")

    print("delete 22")
    bt.delete(target)
    bt.print_inorder()
    print("\n\n")

    print("DESCENDING bt")
    bt.set_direction(0)
    bt.print_inorder()
    print("\n\n")

    print("bt1")
    bt1 = AVLTree()
    num_list1 = sample(range(1, 100), 10)
    shuffle(num_list1)
    print(num_list)
    for i in range(0, 10):
        bt1.add(num_list1[i])

    bt1.print_inorder()
    print("\n\n")

    print("bt = bt1")
    bt = deepcopy(bt1)
    print("bt")
    bt.print_inorder()
    print("bt1")
    bt1.print_inorder()

    print("bt1 empty")
    bt1.make_empty()
    bt1.print_inorder()
    print("bt is not change")
    bt.print_inorder()
    print("\n\n")



