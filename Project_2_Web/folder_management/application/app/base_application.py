from folder_management.application.item.itemtype import *
from folder_management.application.item.foldertype import *
from folder_management.application.item.filetype import *
from folder_management.application.structure.linked_history_stack import *
from folder_management.application.structure.linked_queue import *
from folder_management.application.structure.py_heap import *
from folder_management.application.error.invalid_operation import *
from folder_management.application.error.item_not_found import *
from folder_management.application.error.name_error import *
from folder_management.application.error.no_history import *
from folder_management.application.error.no_parent import *

# Created by ParkJungJin on 2019-05-26.

"""@package docstring
@brief	BaseApplication class.
@details	This class processes management about Item and entire system and function
"""

class BaseApplication(object):
    """
    default constructor
    """
    def __init__(self):
        self.root = FolderType("Root")
        self.root.set_path("Root")
        self.root.set_parent(None)  # set root has no parent folder
        self.m_fd_cur_ptr = self.root
        self.clip_board = None

    """
    @brief	Program driver.
    @pre	program is started.
    @post	program is finished.
    """
    def run(self):
        print("base_application is run!")

