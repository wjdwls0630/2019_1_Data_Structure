from application.structure.bnodetype import *
from application.structure.binary_search_tree import *

# Created by ParkJungJin on 2019-05-27.

"""@package docstring
@brief	BinaryIterator class.
@details	This class only for observing, iterator class
"""


class BinaryIterator(object):

    """
    default constructor.
    """
    def __init__(self, bst: BinarySearchTree):
        # set other property
        self.m_cur_pointer = None # for cur pointer
        self.m_cur_idx = -1 # cur pointer index
        self.m_length = 0 # store tree count
        self.m_list = None
        if bst.get_count() != 0:

            self.m_list = []  # to store tree
            self.cast_list_recur(bst.get_root())  # make list

        # cast list recur make m_length

    """
    destructor.
    """
    def __del__(self):
        if self.m_length != 0:
            del self.m_list



    """
    @brief	Check m_CurPointer is dsl_Head_Node.
    @pre	none.
    @post	none.
    @return	return true if m_CurPointer is dsl_Head_Node, otherwise return false.
    """
    def cast_list_recur(self, node: BNodeType):
        # left -> cur -> right
        if node.is_leaf():
            #  if node is leaf, print cur node only(Base Case)
            self.m_list.append(node)
            self.m_length += 1
            return
        else:
            #  if node has child
            #  left -> cur -> right
            if node.get_left_link() is not None:
                self.cast_list_recur(node.get_left_link())

            self.m_list.append(node)
            self.m_length += 1
            if node.get_right_link() is not None:
                self.cast_list_recur(node.get_right_link())

    # iterator bool

    """
    @brief	Check m_cur_idx == -1.
    @pre	none.
    @post	none.
    @return	return true if m_cur_idx == -1, otherwise return false.
    """
    def is_head(self) -> bool:
        return self.m_cur_idx == -1

    """
    @brief	Check m_cur_idx == this->m_length.
    @pre	none.
    @post	none.
    @return	return true if m_cur_idx == this->m_length, otherwise return false.
    """
    def is_tail(self) -> bool:
        return self.m_cur_idx == self.m_length

    """
    @brief	Check m_cur_idx prev is -1.
    @pre	none.
    @post	none.
    @return	return true if m_cur_idx prev is -1, otherwise return false.
    """
    def prev_is_head(self) -> bool:
        return self.m_cur_idx == 0

    """
    @brief	Check m_cur_idx next is this->m_length.
    @pre	none.
    @post	none.
    @return	return true if m_cur_idx next is this->m_length, otherwise return false.
    """
    def next_is_tail(self) -> bool:
        return self.m_cur_idx == self.m_length-1

    # iterator movement

    """
    @brief	Initialize current pointer for an iteration through the list. m_cur_idx = -1 , m_CurPointer = nullptr
    @pre	None.
    @post	current pointer is prior to list. current pointer has been initialized.
    """
    def reset_to_head(self):
        self.m_cur_pointer = None
        self.m_cur_idx = -1

    """
    @brief	Initialize current pointer for an iteration through the list.m_cur_idx = this->m_length , m_CurPointer = nullptr
    @pre	None.
    @post	current pointer is prior to list. current pointer has been initialized.
    """
    def reset_to_tail(self):
        self.m_cur_pointer = None
        self.m_cur_idx = self.m_length

    """
    @brief	Get First Node Data
    @pre	List has element.
    @post	get First Node Data.
    @return return First Node Data.
    """
    def first(self):
        return self.m_list[0].get_data()

    """
    @brief	Get Last Node Data
    @pre	List has element.
    @post	get Last Node Data.
    @return return Last Node Data.
    """
    def last(self):
        return self.m_list[self.m_length-1].get_data()

    """
    @brief Move iterator prev, and Get m_CurPointer Data
    @pre	List has element.
    @post	Move iterator prev, and Get m_CurPointer Data.
    @return return m_CurPointer Data.
    """
    def prev(self):
        self.m_cur_idx -= 1
        self.m_cur_pointer = self.m_list[self.m_cur_idx]
        return self.m_cur_pointer.get_data()

    """
    @brief Move iterator next, and Get m_CurPointer Data
    @pre	List has element.
    @post	Move iterator next, and Get m_CurPointer Data.
    @return return m_CurPointer Data.
    """
    def next(self):
        self.m_cur_idx += 1
        self.m_cur_pointer = self.m_list[self.m_cur_idx]
        return self.m_cur_pointer.get_data()

    """
    @brief Get m_CurPointer Data
    @pre	List has element.
    @post	Get m_CurPointer Data.
    @return return m_CurPointer Data.
    """
    def cur(self):
        return self.m_cur_pointer.get_data()

    """
    @brief Get m_CurPointer Node
    @pre	List has element.
    @post	Get m_CurPointer Node.
    @return return m_CurPointer Node.
    """
    def get_current_node(self) -> BNodeType:
        return self.m_cur_pointer
