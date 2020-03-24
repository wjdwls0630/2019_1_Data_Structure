# Created by ParkJungJin on 2019-05-25.

"""@package docstring
@brief	BinarySearchTree class.
@details	This class processes as connected by BNodeType left and right pointer
it has insert, delete , get(search) function
"""

from folder_management.application.structure.binary_tree import *
from folder_management.application.structure.comparer import *
from copy import deepcopy


class BinarySearchTree(BinaryTree):
    def __init__(self, in_direction=ASCENDING):
        super(BinarySearchTree, self).__init__()
        # ASCENDING(1): ascending order(Left is small Right is big)
        # DESCENDING(0): descending order(Left is big Right is small)
        self.bt_direction = in_direction  # ASCENDING(1), DESCENDING(0)
        self.bt_comparer = Comparer(in_direction)  # set Compare (for direction)

    def __del__(self):
        super(BinarySearchTree, self).__del__()


    # Get & Set

    """
    @brief	Get Direction.
    @pre	none.
    @post	none.
    @return	Get Direction of tree.
    """
    def get_direction(self) -> int:
        return self.bt_direction

    """
    @brief	Set Direction.
    @pre	none.
    @post	Set Direction.
    @param Direction to set.
    """
    def set_direction(self, in_direction=ASCENDING):

        ## re-make tree
        ## first deep copy original
        temp =BinarySearchTree()
        temp = deepcopy(self)

        # set direction
        self.bt_direction = in_direction;
        self.bt_comparer.set_direction(in_direction);

        # copy again
        self.make_empty()  # reset tree
        self.copy_node_recur(temp.get_root())

        # de-allocation memory
        del temp

    # data management

    def get_predecessor_node(self, parent_node: BNodeType, node: BNodeType) -> BNodeType:
        temp = node
        if self.bt_direction == ASCENDING:
            while temp.get_right_link() is not None:
                # move to right till right link is None
                # set parent
                parent_node = temp
                temp = temp.get_right_link()
        else:
            # direction is DESCENDING
            while temp.get_left_link() is not None:

                # move to right till right link is None
                # set parent
                parent_node = temp
                temp = temp.get_left_link()

        return temp

    """
    @brief	get the data which has same in the tree.(Binary Search)
    @pre	data to search should be initialized
    @param	data that you want(search) to get.
    @return	return 1 if this function works well, otherwise 0.
    """
    def get(self, data) -> int:
        if self.is_empty():
            return 0
        return self.get_recur(self.root, data)

    """
    @brief	get the data which has same in the tree.(Binary Search)
    @details check all nodes in tree by recursive
    @pre	data to search should be initialized
    @param	data that you want(search) to get.
    @return	return 1 if this function works well, otherwise 0.
    """
    def get_recur(self, node: BNodeType, data):
        # Base case of GetRecur, case when node is leaf
        if node.is_leaf():
            # if arrive on leaf node
            if self.bt_comparer.is_equal(data, node.get_data()):
                # if data and node data equal
                # data = Node->GetData()
                data = node.get_data()
                return 1;

            # if not equal
            return 0;

        # compare node and data
        if self.bt_comparer.compare(data, node.get_data()):
            # ASCENDING(1) data < Node->GetData()
            # DESCENDING(0)data > Node->GetData()
            # move to left
            if node.get_left_link() is None :
                # if node's left child is empty
                return 0

            return self.get_recur(node.get_left_link(), data)
        elif self.bt_comparer.op_compare(data, node.get_data()):

            # ASCENDING(1) data > Node->GetData()
            # DESCENDING(0) data < Node->GetData()
            # move to right
            if node.get_right_link() is None :
                # if node's right child is empty
                return 0

            return self.get_recur(node.get_right_link(), data)
        else:
            # if data and node data equal
            # data = Node->GetData()
            data = node.get_data()
            return 1

    """
    @brief	add item into appropriate spot of tree.
    @details data must not be overlapped
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
            return self.add_recur(self.root, data)

        # if data is overlap
        return 0

    """
    @brief	add item into appropriate spot of tree.
    @details call recursive to search appropriate spot
    @pre	tree is not full. item is not in list.
    @post	Item is inserted in this tree.
    @param Node for moving , data to insert
    @return	1 if this function works well, otherwise 0.
    """
    def add_recur(self, node: BNodeType, data):
        # data is not overlapped, and check already in add()

        # comparing data
        if self.bt_comparer.compare(data, node.get_data()):
            # ASCENDING(1) data < Node->GetData()
            # DESCENDING(0) data > Node->GetData()
            # move to left
            if node.get_left_link() is None:
                # if node's left child is empty
                new_node = BNodeType()  # node to add
                new_node.set_data(data)
                node.set_left_link(new_node)
                return 1

            return self.add_recur(node.get_left_link(), data)
        else:
            # ASCENDING(1) data > Node->GetData()
            # DESCENDING(0) data < Node->GetData()
            # move to right
            if node.get_right_link() is None:
                # if node's right child is empty
                new_node = BNodeType()  # node to add
                new_node.set_data(data)
                node.set_right_link(new_node)
                return 1

            return self.add_recur(node.get_right_link(), data)

    """
    @brief	Delete item from this list.
    @pre	tree is not empty. the item exists in list.
    @post	Item is deleted from this tree.
    @return	1 if this function works well, otherwise 0.
    """
    def delete(self, data) -> int:
        # if tree is empty
        if self.is_empty():
            return 0

        if self.get(data):
            # if data is in the tree
            # root has no parent node
            temp = BNodeType() # has no meaning of this
            return self.delete_recur(temp, node=self.root, data=data)

        # if data is not in the tree
        return 0

    """
    @brief	Delete item from this tree.
    @details call recursively and find (binary search) and when it is find, call DeleteNode for de-allcation
    @pre	Parent_Node and Node should be initialized. the item exists in tree.
    @post	Item is deleted from this tree.
    @param Parent_Node to set new link when it is delete, Node for moving, data to find item that want to delete
    @return	1 if this function works well, otherwise 0.
    """
    def delete_recur(self, parent_node:BNodeType, node: BNodeType, data) -> int:
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
            return 1


    """
    @brief	Deallocation memory of node and set new link for parent node.
    @pre	Parent_Node and Node should be initialized..
    @post	Deallocation Memory of Target_Node and Parent Node is Set New Link Item .
    @param Parent_Node to set new link when it is delete, Node for moving and delete
    @return	1 if this function works well, otherwise 0.
    """
    def delete_node(self, parent_node: BNodeType, target_node: BNodeType) -> int:
        temp = target_node  # for store Target_Node temporary

        # case 1: if Target_Node is Leaf
        if target_node.is_leaf():
            if target_node is self.root:
                # if Node is Root, and has no child.it means tree will be empty
                self.set_root(None)

            # if target node to delete is leaf
            if parent_node.get_left_link() is target_node:
                # if Parent Node's left child is Target
                parent_node.set_left_link(None)  # make Parent Node's Left child is null
            else:
                # if Parent Node's right child is Target
                parent_node.set_right_link(None)  # make Parent Node's right child is null

        elif target_node.get_left_link() is None or target_node.get_right_link() is None:
            # case 2: if Target Node has left or right child only

            # child :  Target_Node's child node to connect Parent_Node
            if target_node.get_left_link() is None:

                # if Target_Node has only right child
                child = target_node.get_right_link()
            else:
                # if Target_Node has only left child
                child = target_node.get_left_link()

            if target_node is self.get_root():
                # if node is root, child should be root
                self.set_root(child)
            else:
                # if target node is not root, child should be connected with parent node
                if parent_node.get_left_link() is target_node:
                    # if Parent's left child is target node
                    parent_node.set_left_link(child)
                else:
                    # if Parent's right child is target node
                    parent_node.set_right_link(child)


        else:
            # case 3: if Target Node has both direction childs
            # search most biggest node in Target Node 's left child(small nodes)

            # Successor_Node : Node for Taking instead of Target_Node
            # Successor_Parent_Node : Successor_Node's parent
            successor_parent_node = BNodeType()
            if self.bt_direction == ASCENDING:
                successor_node = self.get_predecessor_node(successor_parent_node, target_node.get_left_link())
            else:
                successor_node = self.get_predecessor_node(successor_parent_node, target_node.get_right_link())

            if successor_parent_node.get_left_link() == successor_node:
                # if Successor_Node is Succesor_Parent_Node's left child
                successor_parent_node.set_left_link(None)
            else:
                # if Successor_Node is Succesor_Parent_Node's right child
                successor_parent_node.set_right_link(None) # make nullptr


            # copy Succesor_node to Target_Node ( it seems to delete target node)
            target_node.set_data(successor_node.get_data())

            # select node to delete( in this case Successor_Node should be deleted
            temp = successor_node


        # deallocation memory
        del temp
        return 1

    """
    @brief	Sort item from this tree. (it is not really mean sort, it works when criteria is changed on outer side)
    @pre	criteria is changed and tree is not empty. the item exists in tree.
    @post	tree is sorted.
    @param Compare criteria.
    @return	1 if this function works well, otherwise 0.
    """
    def sort(self) -> int:
        if self.is_empty():
            return 0

        # re - make tree - to set new criteria
        # first deep copy original
        temp = BinarySearchTree()
        temp = deepcopy(self)

        # copy
        self.make_empty()
        self.copy_node_recur(temp.get_root())

        # de - allocation memory
        del temp
        return 1

    """
    @brief	Copy Node and add the list.
    @details It only can use for copying another tree (deep copy, in this case we use this func in operator = and copy constructor)
    @pre	Node is initialized.
    @post	Copy Node and add the list.
    @param Node to copy
    """
    def copy_node_recur(self, node: BNodeType):
        # if tree is empty , return nothing
        if node is None:
            return
        # cur -> left -> right
        if node.is_leaf():
            # if node is leaf, (Base Case)
            self.add(node.get_data())
            return
        elif node.get_left_link() is None or node.get_right_link() is None:
            # if node has left or right child only
            self.add(node.get_data())
            if node.get_left_link() is not None:
                self.copy_node_recur(node.get_left_link())
                return
            else:
                self.copy_node_recur(node.get_right_link())
                return

        else:
            # if node has both left and right child
            self.add(node.get_data())
            self.copy_node_recur(node.get_left_link())
            self.copy_node_recur(node.get_right_link())
            return


"""
Test Code
"""
if __name__ == "__main__":
    from random import randint
    bt_test = BinarySearchTree()

    bt_test.add(3);
    bt_test.add(2);
    bt_test.add(1);
    bt_test.add(4);
    bt_test.add(5);
    bt_test.add(6);
    bt_test.add(10);
    bt_test.add(7);
    bt_test.add(9);
    bt_test.add(8);
    print("bt_test")
    print("Count : {} \nLeaf : {} \nHeight : {}"
          .format(bt_test.get_count(), bt_test.get_leaf_node_count(), bt_test.get_height()))
    bt_test.print_inorder()
    bt_test.print_preorder()
    bt_test.print_postorder()
    print("\n\n")

    print("bt")
    bt = BinarySearchTree()
    for i in range(0,10):
        num = randint(1, 100)
        bt.add(num)

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
    bt1 = BinarySearchTree()
    for i in range(0,10):
        num = randint(1, 100)
        bt1.add(num)

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




