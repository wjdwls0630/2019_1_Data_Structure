from application.item.filetype import *

# Created by ParkJungJin on 2019-05-26.


"""@package docstring
@brief	TextFileType class.
@details	This class processes management text file
"""


class TextFileType(FileType):
    """
    default constructor
    """
    def __init__(self, in_name="untitled"):
        super().__init__(in_name)
        self.set_extensions(".txt")

    """
    @brief	Get ItemType kind.
    @pre	kind is set.
    @post	none.
    @return	"File".
    """
    def what_is(self) -> str:
        return "TextFile"

    """
    @brief	Get Extensions.
    @pre	Extensions is set.
    @post	none.
    @return	Extensions.
    """
    def get_extensions(self) -> str:
        return ".txt"

    """
    @brief	Get Extensions code.
    @pre	Extensions is set.
    @post	none.
    @return	Extensions code(txt :0 jpg: 1 mp3 :2).
    """
    def get_extensions_code(self) -> Extensions:
        return Extensions.TXT

    # File management

    """
    @brief	Run the file by proper file application.
    @pre	none.
    @post	Run the file by proper file application.
    @param	none.
    @return	return 1 if this function works well, otherwise 0.
    """
    def run(self):
        print("text application run!")
