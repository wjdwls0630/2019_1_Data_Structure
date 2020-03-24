# Created by ParkJungJin on 2019-05-23.

"""@package docstring
@brief	BinaryTree class.
@details	self class processes as connected by BNodeType left and right pointer
"""

from folder_management.application.structure.bnodetype import *


class BinaryTree(object):
    """
    Default Constructor
    """
    def __init__(self):
        self.root = None

    """
    Destructor
    """
    def __del__(self):
        # if not empty
        if not self.is_empty():
            self.make_empty()

    """
    @brief	Set root.
    @pre	none.
    @post	Set root .
    @param root to set.
    """
    def set_root(self, node):
        self.root = node

    """
    @brief	Get root .
    @pre	none.
    @post	none.
    @return	Get root.
    """
    def get_root(self) -> BNodeType:
        return self.root

    """
    @brief	Check tree is empty.
    @pre	none.
    @post	none.
    @return	return true if tree is empty, otherwise return false.
    """
    def is_empty(self) -> bool:
        if self.root is None:
            return True
        return False

    """
    @brief	Check tree is full.
    @details return true when rise bad_memory allocation , it means there is no memory to allocate node
    @pre	none.
    @post	none.
    @return	return true if tree is full, otherwise return false.
    """
    def is_full(self) -> bool:
        # Temp for check memory is Full
        try:
            temp = BNodeType()
            return False
        except MemoryError:
            return True

    """
    @brief	Initialize Tree to empty state.
    @details visit all nodes in tree and delete all nodes
    @pre	None
    @post	Tree is empty.
    """
    def make_empty(self):
        if not self.is_empty():
            self.make_empty_node(self.root)
            self.root = None

    """
    @brief	delete tree's node.
    @details using in MakeEmpty(), call recursively
    @pre	None
    @post	List is empty.
    """
    def make_empty_node(self, node: BNodeType):
        # if tree is empty, return nothing
        if node is None:
            return

        # delete all node

        if node.is_leaf():
            # if node is leaf(Base Case)
            del node
            return
        elif node.get_left_link() is None or node.get_right_link() is None:
            if node.get_left_link() is not None:
                self.make_empty_node(node.get_left_link())
            else :
                self.make_empty_node(node.get_right_link())
            # then delete node
            del node
            return
        else :
            # if node has both left and right child
            self.make_empty_node(node.get_left_link())
            self.make_empty_node(node.get_right_link())
            del node
            return

    """
    @brief	visit and print node data by inorder.
    @details left . cur . right , call recursively
    @pre	initialize node
    @post	Print Node data.
    """
    def inorder(self, node: BNodeType):
        # if tree is empty return nothing
        if self.is_empty():
            return

        # left . cur - >right
        if node.is_leaf():
            # if node is leaf, print cur node only (Base Case)
            print("{} ".format(node.get_data()), end='')
            return
        else :
            # if node has child
            if node.get_left_link() is not None :
                self.inorder(node.get_left_link())
            print("{} ".format(node.get_data()), end='')
            if node.get_right_link() is not None:
                self.inorder(node.get_right_link())

    """
    @brief	visit and print all nodes in tree.
    @details left . cur . right
    @pre	none.
    @post	Print all Node data.
    """
    def print_inorder(self):
        print("inorder : ", end=' ')
        self.inorder(self.root)
        print('')


    """
    @brief	visit and print node data by preorder.
    @details cur . left . right , call recursively
    @pre	initialize node
    @post	Print Node data.
    """
    def preorder(self, node: BNodeType):

        # if tree is empty , return nothing
        if self.is_empty():
            return

        # cur . left . right
        if node.is_leaf():
            # if node is leaf, print cur node only (base case)
            print("{} ". format(node.get_data()), end='')
        else:
            # if node has child
            # cur . left .right
            print("{} ".format(node.get_data()), end='')
            if node.get_left_link() is not None:
                self.preorder(node.get_left_link())
            if node.get_right_link() is not None:
                self.preorder(node.get_right_link())

    """
    @brief	visit and print all nodes in tree.
    @details cur . left . right
    @pre	none.
    @post	Print all Node data.
    """
    def print_preorder(self):
        print("preorder : ", end=' ')
        self.preorder(self.root)
        print('')



    """
    @brief	visit and print node data by postorder.
    @details left . right . cur , call recursively
    @pre	initialize node
    @post	Print Node data.
    """

    def postorder(self, node: BNodeType):

        # if tree is empty , return nothing
        if self.is_empty():
            return

        # left . right . cur
        if node.is_leaf():
            # if node is leaf, print cur node only (base case)
            print("{} ".format(node.get_data()), end='')
        else:
            # if node has child
            # left . right . cur
            if node.get_left_link() is not None:
                self.postorder(node.get_left_link())
            if node.get_right_link() is not None:
                self.postorder(node.get_right_link())
            print("{} ".format(node.get_data()), end='')

    """
    @brief	visit and print all nodes in tree.
    @details left . right . cur
    @pre	none.
    @post	Print all Node data.
    """
    def print_postorder(self):
        print("postorder : ", end=' ')
        self.postorder(self.root)
        print('')

    """
    @brief	Get a number of All Node in current tree.
    @pre	none.
    @post	none.
    @return	number of All Node in current tree.
    """
    def get_count(self) -> int:
        if self.is_empty():
            return 0
        return self.count_node(self.root)

    """
    @brief	Get count cur node(1) + left and right child nodes count.
    @details call recursively
    @pre	initialize node.
    @post	none.
    @return	count cur node(1) + left and right child nodes count .
    """
    def count_node(self, node: BNodeType) -> int:
        # BaseCase of count_node . Node is Leaf node has no child. count 1
        if node.is_leaf():
            return 1

        # if node is not leaf node has left or right

        if node.get_left_link() is None :
            # if has only right
            return 1 + self.count_node(node.get_right_link())
        elif node.get_right_link() is None :
            # if has only left
            return 1 + self.count_node(node.get_left_link())

        # if node has both
        return 1 + self.count_node(node.get_left_link())+self.count_node(node.get_right_link());

    """
    @brief	Get a number of All Leaf Node in current tree.
    @pre	none.
    @post	none.
    @return	number of All Leaf Node in current tree.
    """
    def get_leaf_node_count(self) -> int:
        if self.is_empty() :
            # if tree is empty, leaf node count is 0;
            return 0
        # call recursively
        return self.count_leaf_node(self.root)

    """
    @brief	Check it is leaf node, and if it is leaf, count 1 if not, visit child nodes.
    @details call recursively
    @pre	initialize node.
    @post	none.
    @return	count 1 if node is leaf .
    """
    def count_leaf_node(self, node: BNodeType) -> int :
        # Base Case of count_leaf_node -> Node is Leaf node. count 1
        if node.is_leaf():
            return 1

        # if node is not leaf node has left or right

        if node.get_left_link() is None :
            # if has only right
            return self.count_leaf_node(node.get_right_link())
        elif node.get_right_link() is None :
            # if has only left
            return self.count_leaf_node(node.get_left_link())

        # if node has both
        return self.count_leaf_node(node.get_left_link())+self.count_leaf_node(node.get_right_link())


    """
    @brief	Get a Height in current tree.
    @pre	none.
    @post	none.
    @return	Height in current tree.
    """
    def get_height(self) -> int :
        if self.is_empty():
            # if tree is empty, leaf node count is 0;
            return 0

        # call recursively
        return self.height_node(self.root)

    """
    @brief	Compare Left and Right Height , and choose big one.
    @details call recursively
    @pre	initialize node.
    @post	none.
    @return	count cur node(1) and compare left and right to choose big one .
    """
    def height_node(self, node: BNodeType) -> int:
        # Base Case of height_node -> Node is Leaf node has not child. height 0
        if node.is_leaf():
            return 0

        # Left Height to compare
        h_left = None

        # Right Height to compare
        h_right = None

        # if node is not leaf node has left or right

        if node.get_left_link() is None :
            # if has only right
            h_right = self.height_node(node.get_right_link())
            return h_right+1
        elif node.get_right_link() is None :
            h_left= self.height_node(node.get_left_link())
            return h_left+1

        # if node has both
        h_right = self.height_node(node.get_right_link())
        h_left = self.height_node(node.get_left_link())
        # return more deep side
        # h_left>h_right ? h_left+1 : h_right+1
        return h_left+1 if h_left>h_right else h_right+1;



    """
    @brief	Display tree shape.
    @details call recursively
    @pre	initialize node.
    @post	Display tree.
    """
    def display_tree(self, node: BNodeType, level: int):
        # if cur node is not empty
        if node is not None:
            self.display_tree(node.get_right_link(), level+1)
            print('\n')
            # if cur node is root
            if node is self.root:
                print("root -> ", end='')
            # i is lower than cur level and node is not root
            for i in range(0, level):
                if node is self.root:
                    break
                print("        ", end='')
            # print data on self position
            print(node.get_data(), end='')
            # print left data
            self.display_tree(node.get_left_link(), level + 1)


"""
Test Code
"""
if __name__ == "__main__":
    from random import shuffle, sample

    num_list = sample(range(1, 47), 6)
    shuffle(num_list)
    print("num_list : {}".format(num_list))

    bt_test = BinaryTree()
    b1 = BNodeType()
    b1.set_data(num_list[0])
    b2 = BNodeType()
    b2.set_data(num_list[1])
    b3 = BNodeType()
    b3.set_data(num_list[2])
    b4 = BNodeType()
    b4.set_data(num_list[3])
    b5 = BNodeType()
    b5.set_data(num_list[4])
    b6 = BNodeType()
    b6.set_data(num_list[5])
    bt_test.set_root(b1)
    bt_test.get_root().set_left_link(b2)
    bt_test.get_root().get_left_link().set_right_link(b3)
    bt_test.get_root().set_right_link(b4)
    bt_test.get_root().get_right_link().set_right_link(b5)
    bt_test.get_root().get_right_link().set_left_link(b6)
    print("Count : {} \nLeaf : {} \nHeight : {}"
          .format(bt_test.get_count(), bt_test.get_leaf_node_count(), bt_test.get_height()))
    bt_test.print_inorder()
    bt_test.print_preorder()
    bt_test.print_postorder()
    bt_test.display_tree(bt_test.get_root(), 0)
