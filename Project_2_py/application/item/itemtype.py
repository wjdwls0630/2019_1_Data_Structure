from application.structure.comparer import *
import time
from enum import Enum


class KeyValue(Enum):
    NAME = 0
    CREATEDTIME = 1
    MODIFIEDTIME = 2
    ACCESSTIME = 3
    ACCESSCOUNT = 4

# Created by ParkJungJin on 2019-05-26.


"""@package docstring
@brief	Item class.
@details	This class processes common property management. Item information class.
"""


class ItemType(object):
    """
    default constructor
    """
    def __init__(self, in_name="untitled"):
        self.it_name = in_name
        self.it_path = ""
        self.it_key = KeyValue.NAME
        self.it_created_time = self.generate_time()
        self.it_modified_time = self.it_created_time
        self.it_access_time = self.it_created_time
        self.it_access_count = 0

    def generate_time(self):
        now = time.localtime()
        data = "%04d-%02d-%02d %02d:%02d:%02d" % (
        now.tm_year, now.tm_mon, now.tm_mday, now.tm_hour, now.tm_min, now.tm_sec)
        return data

    # Get Set Display method

    """
    @ brief Get Item path.
    @ pre Item path is set.
    @ post none.
    @ return Item path.
    """
    def get_path(self) -> str:
        return self.it_path

    """    
    @ brief Get Item name.
    @ pre Item name is set.
    @ post none.
    @ return Item name.
    """
    def get_name(self) -> str:
        return self.it_name

    def get_created_time(self):
        return self.it_created_time

    def get_modified_time(self):
        return self.it_modified_time

    def get_access_time(self):
        return self.it_access_time

    def get_key(self) -> KeyValue:
        return self.it_key

    def get_sub_item_num(self) -> int:
        return 0

    def get_access_count(self) -> int:
        return self.it_access_count

    def what_is(self) -> str:
        return "Item"

    def set_name(self, in_name: str):
        self.it_name = in_name

    def set_path(self, in_path: str):
        self.it_path = in_path

    def set_created_time(self, in_created_time: str):
        self.it_created_time = in_created_time

    def set_modified_time(self, in_modified_time: str):
        self.it_modified_time = in_modified_time

    def set_access_time(self, in_access_time: str):
        self.it_access_time = in_access_time

    def set_access_count(self, in_access_count: int):
        self.it_access_count = in_access_count

    def set_key_value(self, in_key=""):
        # default is name
        if in_key == "name" or in_key == "":
            self.it_key=KeyValue.NAME
        elif in_key == "created":
            self.it_key=KeyValue.CREATEDTIME
        elif in_key == "modified":
            self.it_key=KeyValue.MODIFIEDTIME
        elif in_key == "access":
            self.it_key=KeyValue.ACCESSTIME
        elif in_key =="access count":
            self.it_key=KeyValue.ACCESSCOUNT

    def set_key_value(self, in_key=0):
        # default is name
        if in_key == 0 :
            self.it_key=KeyValue.NAME
        elif in_key == 1:
            self.it_key=KeyValue.CREATEDTIME
        elif in_key == 2:
            self.it_key=KeyValue.MODIFIEDTIME
        elif in_key == 3:
            self.it_key=KeyValue.ACCESSTIME
        elif in_key ==4:
            self.it_key=KeyValue.ACCESSCOUNT

    def display_name_on_screen(self):
        print("Name : {}".format(self.it_name))

    def display_kind_on_screen(self):
        print("Kind : {}".format(self.what_is()))

    def display_path_on_screen(self):
        print("Path : {}".format(self.it_path))

    def display_created_time_on_screen(self):
        print("Created Time : {}".format(self.it_created_time))

    def display_modified_time_on_screen(self):
        print("Modified Time : {}".format(self.it_modified_time))

    def display_access_time_on_screen(self):
        print("Access Time : {}".format(self.it_access_time))

    def display_info_on_screen(self):
        print("============ Item Info ============")
        self.display_name_on_screen()
        self.display_kind_on_screen()
        self.display_path_on_screen()
        self.display_created_time_on_screen()
        self.display_modified_time_on_screen()
        self.display_access_time_on_screen()
        print("===================================")

    # operator overloading
    def __eq__(self, other) -> bool:
        if self.what_is() != other.what_is():
            return False
        return self.it_path == other.it_path

    def __ne__(self, other):
        if self.what_is() == other.what_is():
            return False
        return self.it_path != other.it_path

    def __lt__(self, other):
        if self.it_key == KeyValue.NAME:
            return self.it_name < other.it_name
        elif self.it_key == KeyValue.CREATEDTIME:
            return self.it_created_time < other.it_created_time

        elif self.it_key == KeyValue.MODIFIEDTIME:
            return self.it_modified_time < other.it_modified_time

        elif self.it_key == KeyValue.ACCESSTIME:
            return self.it_access_time < other.it_access_time

        elif self.it_key == KeyValue.ACCESSCOUNT:
            return self.it_access_count < other.it_access_count

    def __gt__(self, other):
        if self.it_key == KeyValue.NAME:
            return self.it_name > other.it_name
        elif self.it_key == KeyValue.CREATEDTIME:
            return self.it_created_time > other.it_created_time

        elif self.it_key == KeyValue.MODIFIEDTIME:
            return self.it_modified_time > other.it_modified_time

        elif self.it_key == KeyValue.ACCESSTIME:
            return self.it_access_time > other.it_access_time

        elif self.it_key == KeyValue.ACCESSCOUNT:
            return self.it_access_count > other.it_access_count

    def __str__(self):
        return self.it_name





"""
Test Code
"""
if __name__ == "__main__":
    item1 = ItemType("aaa")
    item2 = ItemType("bbb")
    print(item1.get_created_time())
    print(item1.get_access_time())
    item1.display_info_on_screen()
    print(item1 < item2)