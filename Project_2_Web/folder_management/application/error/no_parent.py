# Created by ParkJungJin on 2019-05-27.

"""@package docstring
@brief	NoParent Exception class.
@details	This class raise when parent folder is not existed
"""


class NoParent(Exception):
    def __init__(self):
        super().__init__("No ParentFolder")


"""
Test Code
"""
if __name__ == "__main__":
    raise NoParent()