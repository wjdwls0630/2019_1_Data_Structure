# Created by ParkJungJin on 2019-05-27.

"""@package docstring
@brief	EmptyStack Exception class.
@details	This class raise when stack is empty
"""


class EmptyStack(Exception):
    def __init__(self):
        super().__init__("Stack is Empty!")


"""
Test Code
"""
if __name__ == "__main__":
    raise EmptyStack()