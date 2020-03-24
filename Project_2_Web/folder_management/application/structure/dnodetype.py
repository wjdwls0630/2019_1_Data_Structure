# Created by ParkJungJin on 2019-05-27.

"""@package docstring
@brief	DoublyNodeType class.
@details	This class has data and next and prev pointer.
"""


class DNodeType(object):
    """
    default constructor
    """
    def __init__(self):
        self.data = None  # < A data for each node.
        self.next_link = None  # < A pointer to Next Node.
        self.prev_link = None  # <A pointer to Prev Node.


    """
    @brief	Get Pointer to Next Node.
    @pre	Pointer to Next Node should be initialized.
    @post	Get Pointer to Next Node.
    @return	Pointer to Next Node.
    """
    def get_next_link(self):
        return self.next_link

    """
    @brief	Get Pointer to Prev Node.
    @pre	Pointer to Prev Node should be initialized.
    @post	Get Pointer to Prev Node.
    @return	Pointer to Prev Node.
    """
    def get_prev_link(self):
        return self.prev_link

    """
    @brief	Set Pointer to Next Node.
    @pre	none.
    @post	Pointer to Next Node is set.
    @param	next_link set nLink.
    """
    def set_next_link(self, next_link):
        self.next_link = next_link

    """
    @brief	Set Pointer to Prev Node.
    @pre	none.
    @post	Pointer to Prev Node is set.
    @param	prev_link set nLink.
    """
    def set_prev_link(self, prev_link):
        self.prev_link = prev_link

    """
    @brief	Get Data.
    @pre	Data should be initialized.
    @post	Get Data.
    @return	Data.
    """
    def get_data(self):
        return self.data

    """
    @brief	Set Data
    @pre	none.
    @post	Data is set.
    @param	inData set Data.
	"""
    def set_data(self, in_data):
        self.data = in_data