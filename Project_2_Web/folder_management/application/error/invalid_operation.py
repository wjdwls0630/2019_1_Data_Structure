# Created by ParkJungJin on 2019-05-27.

"""@package docstring
@brief	InvalidOperation Exception class.
@details	This class raise when operation is not valid
"""


class InvalidOperation(Exception):
    def __init__(self):
        super().__init__("Invalid Operation")


"""
Test Code
"""
if __name__ == "__main__":
    raise InvalidOperation()