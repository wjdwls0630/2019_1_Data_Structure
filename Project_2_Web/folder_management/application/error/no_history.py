# Created by ParkJungJin on 2019-05-27.

"""@package docstring
@brief	Nohistory Exception class.
@details	This class raise when history does not exist
"""


class NoHistory(Exception):
    def __init__(self):
        super().__init__("No History!")


"""
Test Code
"""
if __name__ == "__main__":
    raise NoHistory()