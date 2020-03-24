#
# Created by ParkJungJin on 2019-05-27.
#

"""@package docstring
@brief	HeapNode class.
@details	This class has data for heap
"""

class HNodeType:
    """
    default constructor.
    """

    def __init__(self):
        self.data = None  # < A data for each node.

    """
    @brief	Get Data.
    @pre	Data should be initialized.
    @post	Get Data.
    @return	Data.
    """

    def get_data(self):
        return self.data

    """
      *	@brief	Set Data
      *	@pre	none.
      *	@post	Data is set.
      *	@param	inData set Data.
    """
    def set_data(self, indata):
        self.data = indata


"""
Test Code
"""
if __name__ == "__main__":
    h1 = HNodeType()
    h1.set_data(1)
    print(h1.get_data())






