# Created by ParkJungJin on 2019-05-27.

"""@package docstring
@brief	NameError Exception class.
@details	This class raise when name can not be used
"""


class NameError(Exception):
    def __init__(self, itname: str):
        super().__init__("This Name Can not be used : " + itname)


"""
Test Code
"""
if __name__ == "__main__":
    raise NameError("aaaa")