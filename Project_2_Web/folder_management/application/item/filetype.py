from folder_management.application.item.itemtype import *
from enum import Enum


class Extensions(Enum):
    TXT = 1
    JPG = 2
    MP3 = 3


# Created by ParkJungJin on 2019-05-26.


"""@package docstring
@brief	FileType class.
@details	This class processes management file
"""


class FileType(ItemType) :
    """
    default constructor
    """
    def __init__(self, in_name="untitled"):
        super().__init__(in_name)
        self.fi_extensions = in_name[in_name.find('.'):]

    """  
    @brief	Get ItemType kind.
    @pre	kind is set.
    @post	none.
    @return	"File".
    """
    def what_is(self) -> str:
        return "File"

    """  
    @brief	Get Extensions.
    @pre	Extensions is set.
    @post	none.
    @return	Extensions.
    """
    # make pure virtual
    def get_extensions(self) -> str:
        pass

    """  
    @brief	Get Extensions code.
    @pre	Extensions is set.
    @post	none.
    @return	Extensions code(txt :0 jpg: 1 mp3 :2).
    """
    def get_extensions_code(self) -> Extensions:
        pass


    """  *	@brief	Get SubFolder Number.
    *	@pre	SubFolder Number is set.
    *	@post	none.
    *	@return	SubFolder Number.
    """
    def get_sub_item_num(self) -> int:
        return 0

    """  
    @brief	Set Extensions.
    @detail Do not use this except reading data!
    @pre	none.
    @post	Extensions is set.
    @param	inExtensions Extensions.
    """
    def set_extensions(self, in_extensions: str):
        self.fi_extensions = in_extensions

    """  
    @brief	Set File Name.
    @detail also Set Extensions
    @pre	none.
    @post	File Name is set.
    @param	inName	File Name.
    """
    def set_name(self, in_name: str):
        super().set_name(in_name)
        self.set_extensions(in_name[in_name.find('.'):])

    """  
    @brief	Display File Extensions on screen.
    @pre	Extensions is set.
    @post	Extensions is on screen.
    """
    def display_extensions_on_screen(self):
        print("Extension : {}".format(self.fi_extensions))

    """  
    @brief	Display file Info on screen.
    @pre	file Info is set.
    @post	file Info is on screen.
    """
    def display_info_on_screen(self):
        print("============ File Info ============")
        self.display_name_on_screen()
        self.display_kind_on_screen()
        self.display_path_on_screen()
        self.display_created_time_on_screen()
        self.display_modified_time_on_screen()
        self.display_access_time_on_screen()
        print("===================================")

    #operator overloading

    """
    *	@brief	Comparing File Path is same. (for object real same )
    *	@pre	none.
    *	@post	none.
    *	@param	another File type File that you want to Compare.
    *	@return	return true if Path is same, otherwise false.
    """
    def __eq__(self, other):
        return self.get_path() is other.get_path()

    """
    *	@brief	Comparing File Path is different.
    *	@pre	none.
    *	@post	none.
    *	@param	another File type File that you want to Compare.
    *	@return	return true if Path is different, otherwise false.
    """
    def __ne__(self, other):
        return self.get_path() is not other.get_path()

    """
    *	@brief	Comparing File name is smaller. (by key)
    *	@pre	none.
    *	@post	none.
    *	@param	another File type File that you want to Compare.
    *	@return	return true if pre is smaller than post, otherwise false.
    """
    def __lt__(self, other):
        if self.get_key() is KeyValue.NAME:
            return self.get_name() < other.get_name()
        elif self.get_key() is KeyValue.CREATEDTIME:
            return self.get_created_time() < other.get_created_time()
        elif self.get_key() is KeyValue.MODIFIEDTIME:
            return self.get_modified_time() < other.get_modified_time()
        elif self.get_key() is KeyValue.ACCESSTIME:
            return self.get_access_time() < other.get_access_time()

    """
    *	@brief	Comparing File name is bigger. (by key)
    *	@pre	none.
    *	@post	none.
    *	@param	another File type File that you want to Compare.
    *	@return	return true if pre is bigger than post, otherwise false.
    """
    def __gt__(self, other):
        if self.get_key() is KeyValue.NAME:
            return self.get_name() > other.get_name()
        elif self.get_key() is KeyValue.CREATEDTIME:
            return self.get_created_time() > other.get_created_time()
        elif self.get_key() is KeyValue.MODIFIEDTIME:
            return self.get_modified_time() > other.get_modified_time()
        elif self.get_key() is KeyValue.ACCESSTIME:
            return self.get_access_time() > other.get_access_time()

    def __str__(self):
        return self.get_name()

    # File management

    """
    *	@brief	Run the file by proper file application.
    *	@pre	none.
    *	@post	Run the file by proper file application.
    *	@param	none.
    *	@return	return 1 if this function works well, otherwise 0.
    """
    def run(self):
        pass


