from folder_management.application.structure.nodetype import *
from folder_management.application.error.empty_queue import *

# Created by ParkJungJin on 2019-05-27.

"""@package docstring
@brief	LinkedQueue class.
@details	This class processes as First In, First Out (FIFO), ���ø��� ������ �پ��� ���� Ÿ���� ������ �� �ִ�.
"""


class LinkedQueue(object):
    """
    default constructor
    """
    def __init__(self):
        self.lq_head_node = NodeType()
        #  Head node for programming list more easy. It has not data, only has real head pointer
        self.lq_front = None  # index of one in front of the first element.
        self.lq_rear = None  # index of the last element.
        self.lq_length = 0  # max Capacity of the Queue.

    """
    Destructor
    """
    def __del__(self):
        if not self.is_empty():
            self.make_empty()


    """
    @brief	Make Queue empty.
    @pre	none.
    @post	clear Queue.
    """
    def make_empty(self):
        while not self.is_empty():
            self.dequeue() # remove front

        self.lq_front = None
        self.lq_rear = None
        self.lq_length = 0

    """
    @brief	Get a number of Items in current Queue.
    @pre	none.
    @post	none.
    @return	number of Items in current Queue.
    """
    def get_length(self) -> int:
        return self.lq_length

    """
    @brief	Check capacity of Queue is empty.
    @pre	none.
    @post	none.
    @return	return true if Queue capacity reached to the lower bound, otherwise return false.
    """
    def is_empty(self) -> bool:
        return self.lq_length is 0

    """
    @brief	add a new data to the last of Queue. 
    @pre	Queue should be initialized.
    @post	added the new data to the last of Queue.
    @param	data	new data.
    """
    def enqueue(self, data):
        new_node = NodeType()  # make new node
        new_node.set_data(data)  # set data

        if self.is_empty():
            # if queue is empty
            self.lq_head_node.set_next_link(new_node)
            self.lq_front = new_node
            self.lq_rear=new_node # first node
        else:
            self.lq_rear.set_next_link(new_node) # only rear move
            self.lq_rear=new_node

        self.lq_length += 1

    """
    @brief  Remove the First data from the Queue, if Queue is empty throw EmptyQueue Exception
    @pre	Queue should be initialized.
    @post	Remove the First data from the Queue.
    * @return if function works well, return 1.
    """
    def dequeue(self) -> int:
        if self.is_empty():
            raise EmptyQueue()

        self.lq_head_node.set_next_link(self.lq_front.get_next_link()) # make head ptr to next the top
        self.lq_front = self.lq_head_node.get_next_link()

        if self.lq_front is None:
            # if there is no element in queue
            self.lq_rear = None

        self.lq_length -= 1
        return 1

    """
    @brief  Returns the First data from the Queue, if Queue is empty throw EmptyQueue Exception
    @pre	Queue should be initialized.
    @post	Returns the First data from the Queue.
    * @return the First data.
    """
    def front(self):
        if self.is_empty():
            raise EmptyQueue()

        return self.lq_front.get_data()


