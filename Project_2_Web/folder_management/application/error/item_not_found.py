# Created by ParkJungJin on 2019-05-27.

"""@package docstring
@brief	Empty Queue Exception class.
@details	This class raise when queue is empty
"""


class ItemNotFound(Exception):
    def __init__(self, itname: str):
        super().__init__("No Such File or Directory : "+ itname)


"""
Test Code
"""
if __name__ == "__main__":
    raise ItemNotFound("aaaa")
