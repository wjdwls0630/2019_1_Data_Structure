#  Created by ParkJungJin on 2019-05-23.

"""@package docstring
@brief	BinaryNodeType class.
@details	This class has data and right and left pointer.
"""


class BNodeType(object):
    """
    Default Constructor
    """
    def __init__(self):
        self.data = None
        self.right_link = None
        self.left_link = None

    """
    brief	Get Pointer to Right Node.
    @pre	Pointer to Right Node should be initialized.
    @post	Get Pointer to Right Node.
    @return	Pointer to Right Node.
    
    """

    def get_right_link(self) :
        return self.right_link

    """
    @brief	Get Pointer to Left Node.
    @pre	Pointer to Left Node should be initialized.
    @post	Get Pointer to Left Node.
    @return	Pointer to Left Node.
    """

    def get_left_link(self) :
        return self.left_link

    """
    @brief	Set Pointer to Right Node.
    @pre	none.
    @post	Pointer to Right Node is set.
    @param	right_link set right_link.
    """
    def set_right_link(self, right_link):
        self.right_link = right_link

    """
    @brief	Set Pointer to Left Node.
    @pre	none.
    @post	Pointer to Left Node is set.
    @param	left_link set right_link.
    """
    def set_left_link(self, left_link):
        self.left_link = left_link


    """
    @brief	Get data.
    @pre	data should be initialized.
    @post	Get data.
    @return	data.
    """
    def get_data(self):
        return self.data

    """
    @brief	Set data
    @pre	none.
    @post	data is set.
    @param	indata set data.  
    """

    def set_data(self, in_data):
        self.data = in_data

    """
    @brief	Check node is leaf.
    @pre	none.
    @post	none.
    @return	return true if tree is leaf, otherwise return false.
    """

    def is_leaf(self) :
        if self.right_link is None and self.left_link is None :
            return True
        return False


"""
Test Code
"""
if __name__ == "__main__":

    b1 = BNodeType()
    b1.set_data(1)
    print(b1.is_leaf())
    print(b1.get_data())
    b2 = BNodeType()
    b3 = BNodeType()
    b1.set_left_link(b2)
    b1.set_right_link(b3)
    b2.set_data(2)
    b3.set_data(3)

    print(b1.get_left_link().get_data())
    print(b1.get_right_link().get_data())

