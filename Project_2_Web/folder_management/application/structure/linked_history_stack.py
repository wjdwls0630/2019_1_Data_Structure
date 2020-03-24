from folder_management.application.structure.dnodetype import *
from folder_management.application.error.empty_stack import *
from folder_management.application.error.no_history import *


# Created by ParkJungJin on 2019-05-27.

"""@package docstring
@brief	Linked History Stack class.
@details	This class processes as Last In, First Out (LIFO). Linked History Stack
            This only can be used by proper purpose
"""


class LinkedHistoryStack(object):
    """
    default constructor
    """

    lhs_length: int
    lhs_head_node: DNodeType


    def __init__(self):
        self.lhs_head_node = DNodeType()
        # Head node for programming list more easy. It has not data, only has real head pointer
        self.lhs_tail_node = DNodeType()
        # Tail node for programming list more easy. It has not data, only has real tail pointer

        self.lhs_head_node.set_next_link(self.lhs_tail_node) # reset head node
        self.lhs_tail_node.set_prev_link(self.lhs_head_node) # reset tail node

        self.lhs_top = None  # Top pointer( using like iterator) (always point top)
        self.lhs_cur = None  # Cur pointer( using like iterator) (always point current data)
        self.lhs_length = 0  # Number of node in the list.

    """
    destructor
    """
    def __del__(self):
        if not self.is_empty():
            self.make_empty()


    """
    @brief	Make Linked History Stack empty.
    @pre	none.
    @post	clear Linked History Stack.
    """
    def make_empty(self):
        while not self.is_empty():
            self.pop()  # remove top
        self.lhs_top = None
        self.lhs_length = 0


    """
    @brief	Get a number of Items in current Linked History Stack.
    @pre	none.
    @post	none.
    @return	number of Items in current Linked History Stack.
    """
    def get_length(self) -> int:
        return self.lhs_length


    """
    @brief	Set a number of Items in current Linked History Stack.
    @pre	none.
    @post	none.
    @return	number of Items in current Linked History Stack.
    """
    def set_length(self, in_length):
        pass

    """
    @brief	Check capacity of Linked History Stack is empty.
    @pre	none.
    @post	none.
    @return	return true if Linked History Stack capacity reached to the lower bound, otherwise return false.
    """
    def is_empty(self) -> bool:
        return self.lhs_length is 0

    # data management

    """
	@brief	add a new data to the top of Linked History Stack.
    @detail if top != cur using pop to make top ==cur
	@pre	Linked History Stack should be initialized.
	@post	added the new data to the top of Linked History Stack.
	@param	data	new data.
	"""
    def push(self, data):

        while self.lhs_cur is not None and self.lhs_cur is not self.lhs_top:
            self.pop()

        new_node = DNodeType()  # make new node
        new_node.set_data(data) # set node data


        if self.is_empty():
            # if stack is empty
            self.lhs_head_node.set_next_link(new_node) # if no stack make new node to head
            self.lhs_tail_node.set_prev_link(new_node) # if no stack make new node to head
            new_node.set_prev_link(self.lhs_head_node)  # set back link to head node
            new_node.set_next_link(self.lhs_tail_node)  # set next link to head node
            self.lhs_top=new_node;
        else:
            new_node.set_next_link(self.lhs_head_node.get_next_link());  # now new node be on the top
            new_node.set_prev_link(self.lhs_head_node)  # set back link to head node
            self.lhs_head_node.set_next_link(new_node)  # make head ptr to new node
            self.lhs_top.set_prev_link(new_node);  # set back link to new node
            self.lhs_top = new_node


        self.lhs_length += 1
        self.lhs_cur = self.lhs_top



    """
    @brief  Remove the top data from the Linked History Stack, if Linked Stack is empty throw EmptyLinked Stack Exception
    @pre	Linked Stack should be initialized.
    @post	Remove the top data from the Linked Stack
    """
    def pop(self):
        if self.is_empty():
            # if it is empty
            raise EmptyStack()

        temp = self.lhs_top
        self.lhs_head_node.set_next_link((self.lhs_top.get_next_link()))  #make head ptr to next the top
        self.lhs_top = self.lhs_top.get_next_link()  #  move top ptr to next
        self.lhs_top.set_prev_link(self.lhs_head_node)  # set prev link to head node
        del temp # delete
        self.lhs_top = self.lhs_head_node.get_next_link() # set top ptr
        self.lhs_length -= 1

    # iterator management

    """
    @brief  Move cur pointer one node to top direction(head)
    @pre	Linked History Stack should be initialized.
    @post	cur pointer is moved on one node to top direction
    """
    def prev(self):
        if self.is_empty():
            # if it is empty
            raise EmptyStack()

        # if lhs_Cur is null
        if self.lhs_cur is None :
            self.lhs_cur = self.lhs_top


        if self.lhs_cur is self.lhs_top:
            # if cur arrive first
            raise NoHistory()
        self.lhs_cur = self.lhs_cur.get_prev_link()

    """
    @brief  Move cur pointer one node to top opposite direction(tail)
    @pre	Linked History Stack should be initialized.
    @post	cur pointer is moved on one node to top opposite direction
    """
    def next(self):
        if self.is_empty():
            # if it is empty
            raise EmptyStack()


        # if lhs_Cur is null
        if self.lhs_cur is None :
            self.lhs_cur = self.lhs_top

        if self.lhs_cur.get_next_link() is None:
            # if arrive last
            raise NoHistory()
        self.lhs_cur = self.lhs_cur.get_next_link()

    """
    @brief	Returns a copy of top item on the Linked History Stack. if Linked History Stack is empty throw EmptyLinked Stack Exception
    @pre	Linked History Stack should be initialized.
    @post	If (Linked Stack is empty), throw EmptyLinked Stackr ; otherwise, returns top item
    @return the top item
	"""
    def top(self):
        if self.is_empty():
            raise EmptyStack()

        return self.lhs_top.get_data()

    """
    @brief	Returns a copy of cur pointer on the Linked History Stack. if Linked Stack is empty throw EmptyLinked Stack Exception
    @pre	Linked Stack should be initialized.
    @post	If (Linked Stack is empty), throw EmptyLinked Stackr ; otherwise, returns top item
    @return the cur item
    """
    def cur(self):
        if self.is_empty():
            raise EmptyStack()

        return self.lhs_cur.get_data()
