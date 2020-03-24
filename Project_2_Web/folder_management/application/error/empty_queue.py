# Created by ParkJungJin on 2019-05-27.

"""@package docstring
@brief	Empty Queue Exception class.
@details	This class raise when queue is empty
"""


class EmptyQueue(Exception):
    def __init__(self):
        super().__init__("Queue is Empty!")


"""
Test Code
"""
if __name__ == "__main__":
    raise EmptyQueue()