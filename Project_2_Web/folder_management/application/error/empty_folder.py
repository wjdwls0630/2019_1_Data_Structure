# Created by ParkJungJin on 2019-05-27.

"""@package docstring
@brief	EmptyFolder Exception class.
@details	This class raise when stack is empty
"""


class EmptyFolder(Exception):
    def __init__(self):
        super().__init__("Folder is Empty")


"""
Test Code
"""
if __name__ == "__main__":
    raise EmptyFolder()