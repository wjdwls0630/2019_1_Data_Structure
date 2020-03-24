# Created by ParkJungJin on 2019-05-27.

"""@package docstring
@brief	NodeType class.
@details	This class has data and next pointer.
"""


class NodeType(object):

    """
    default constructor.
    """
    def __init__(self):
        self.data = None  # ///< A data for each node.
        self.next_link = None # ///< A pointer to Next Node.

    """
    @brief	Get Pointer to Next Node.
    @pre	Pointer to Next Node should be initialized.
    @post	Get Pointer to Next Node.
    @return	Pointer to Next Node.
    """
    def get_next_link(self):
        return self.next_link


    """
    @brief	Set Pointer to Next Node.
    @pre	none.
    @post	Pointer to Next Node is set.
    @param	next_link set nLink.
    """
    def set_next_link(self, next_link):
        self.next_link = next_link

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

