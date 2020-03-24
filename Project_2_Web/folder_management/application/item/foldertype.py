from folder_management.application.item.itemtype import *
from folder_management.application.item.filetype import *
from folder_management.application.structure.avl_tree import *
from folder_management.application.structure.binary_iterator import *
from folder_management.application.error.empty_folder import *
from folder_management.application.error.item_not_found import *

# Created by ParkJungJin on 2019-05-26.


"""@package docstring
@brief	FolderType class.
@details	This class processes management Folder
"""


class FolderType(ItemType) :
    """
    default constructor
    """
    def __init__(self, in_name="untitled"):
        super().__init__(in_name)
        self.fd_sub_item_num = 0
        self.fd_sub_item_list = None # AVl tree
        self.fd_parent = None # parent folder

    """
    destructor
    """
    def __del__(self):
        if not self.is_empty():
            self.make_empty_folder()

    def make_empty_folder(self):
        if self.fd_sub_item_num is not 0:
            self.fd_sub_item_list.make_empty()
            self.fd_sub_item_list = None # init fd sub item list
        self.fd_sub_item_num = 0

    # Set Get Display Method

    """  
    @brief	Get This Folder is empty.
    @pre	none.
    @post	none.
    @return	if folder is not empty return true otherwise false.
    """
    def is_empty(self):
        return self.fd_sub_item_num is 0

    """
    @brief	Get ItemType kind.
    @pre	kind is set.
    @post	none.
    @return	"Folder".
    """
    def what_is(self) -> str:
        return "Folder"

    """  
    @brief	Get SubFolder Number.
    @pre	SubFolder Number is set.
    *	@post	none.
    *	@return	SubFolder Number.
    """
    def get_sub_item_num(self) -> int:
        return self.fd_sub_item_num

    """  
    @brief	Get ParentFolder.
    @pre	ParentFolder is set.
    @post	none.
    @return	ParentFolder.
    """
    def get_parent(self):
        return self.fd_parent

    """  
    @brief	Set SubFolderNum.
    @detail Do not use this except reading data!
    @pre	none.
    @post	SubFolderNum is set.
    @param	inSubFolderNum SubFolderNum.
    """
    def set_sub_item_num(self, in_sub_item_num: int):
        self.fd_sub_item_num = in_sub_item_num

    """  
    @brief	Set ParentFolder.
    @pre	none.
    @post	ParentFolder is set.
    @param	inParentPtr ParentFolder.
    """
    def set_parent(self, in_parent):
        self.fd_parent = in_parent

    """  
    @brief	Set Direction (sort).
    @pre	none.
    @post	Direction is set.
    @param	inDirection Direction. ASCENDING(1) DESCENDING(0)
    """
    def set_direction(self, in_direction):
        if self.fd_sub_item_num is not 0:
            self.fd_sub_item_list.set_direction(in_direction)

    """  
    @brief	Display SubItemNum on screen.
    @pre	SubItemNum is set.
    @post	SubItemNum is on screen.
    """
    def display_sub_item_num_on_screen(self):
        print("SubItemNum : ".format(self.fd_sub_item_num))

    """  
    @brief	Display Folder Info on screen.
    @pre	Folder Info is set.
    @post	Folder Info is on screen.
    """
    def display_info_on_screen(self):
        print("============ Folder Info ============")
        self.display_name_on_screen()
        self.display_kind_on_screen()
        self.display_sub_item_num_on_screen()
        self.display_path_on_screen()
        self.display_created_time_on_screen()
        self.display_modified_time_on_screen()
        self.display_access_time_on_screen()
        print("=====================================")


    # operator overloading

    """  
    @brief	Comparing Folder path is same. (for object real same )
	@pre	none.
	@post	none.
	@param	another Folder type folder that you want to Compare.
	@return	return true if name is same, otherwise false.
	"""
    def __eq__(self, other):
        return self.get_path() is other.get_path()

    """
    *	@brief	Comparing Folder path is different. (for object real different )
    *	@pre	none.
    *	@post	none.
    *	@param	another Folder type folder that you want to Compare.
    *	@return	return true if name is different, otherwise false.
    """
    def __ne__(self, other):
        return self.get_path() is not other.get_path()

    """
    @brief	Comparing Folder name is smaller. (by key)
    @pre	none.
    @post	none.
    @param	another Folder type folder that you want to Compare.
    @return	return true if pre is smaller than post, otherwise false.
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
    *	@brief	Comparing Folder name is bigger. (by key)
    *	@pre	none.
    *	@post	none.
    *	@param	another Folder type folder that you want to Compare.
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


    """
    *	@brief	Doing combine two different folder.
    *	@pre	folders is not same.
    *	@post	add sub items.
    *	@param	data that you want to be added.
    *	@return	return self-reference if self and data is not same object, otherwise self unchanged.
    """
    def __iadd__(self, other):
        if other.fd_sub_item_num is not 0:
            # if fd has sub items
            if self.fd_sub_item_num is 0:
                # and if self has no sub item
                self.fd_sub_item_list = AVLTree()
            self.fd_sub_item_list.copy_node_recur(other.fd_sub_item_list.get_root())

        # other property
        self.fd_sub_item_num += other.fd_sub_item_num
        return self


    # SubItem management

    """
    @brief	Create New Item in Current Folder.
    @detail If Item name is overlap, add the number that how much is overlaped at last
    @pre	none.
    @post	Add new Item in current Folder.
    @param	the Item to add.
    @return	return 1 if this function works well, otherwise 0.
    """
    def new_item(self, temp_item: ItemType) -> int:
        if self.fd_sub_item_num is 0:
            self.fd_sub_item_list = AVLTree()
            # If there is no SubItem, then create the FolderList

        temp_name = ""
        overlap_count = 0 # for modifying
        while self.fd_sub_item_list.get(temp_item):
            # if item is overlap
            if temp_item.what_is() is "Folder":
                # folder part
                if overlap_count is 0:
                    overlap_count += 1
                    temp_item.set_name(temp_item.get_name()+"_"+str(overlap_count))
                    temp_item.set_path(self.get_path()+"/"+temp_item.get_name())
                    # set sub folder path
                    continue

                temp_name = temp_item.get_name()
                temp_name = temp_name[:-1]
                overlap_count += 1
                temp_name += overlap_count
                temp_item.set_name(temp_name)
                # If Folder OverLap Set new Path
                temp_item.set_path(self.get_path()+"/"+temp_item.get_name())
                # set sub folder path
            elif temp_item.what_is().find("File") is not -1:
                # if file
                temp_name = temp_item.get_name()[0: temp_item.get_name().find('.')]
                if overlap_count is 0:
                    overlap_count += 1
                    temp_item.set_name(temp_name+"_"+str(overlap_count)+'.'+type(FileType)(temp_item).get_extensions())
                    temp_item.set_path(self.get_path()+"/"+temp_item.get_name())
                    continue

                temp_name = temp_name[:-1]
                overlap_count += 1
                temp_item.set_name(temp_name+str(overlap_count)+'.'+type(FileType)(temp_item).get_extensions())
                # If Folder OverLap Set new Path
                temp_item.set_path(self.get_path()+"/"+temp_item.get_name())
                # set sub folder path
        if self.fd_sub_item_list.add(temp_item):
            self.fd_sub_item_num += 1
            if temp_item.what_is() is "Folder":
                type(FolderType)(temp_item).set_parent(self)
                # set parent self added folder
        return 1

    """
    @brief	Delete Item in Current Folder.
    @pre	SubItem is existed, and set path.
    @post	Delete Item what you want in current Folder.
    @param	the Item to delete.
    @return	return 1 if this function works well, otherwise 0.
    """
    def delete_item(self, temp_item: ItemType):
        if self.fd_sub_item_num is 0:
            raise ItemNotFound(temp_item.get_name())
            # If there is no SubItem in the Folder, Throw Error

        # If Data is not in the List
        if not self.fd_sub_item_list.get(temp_item):
            raise ItemNotFound(temp_item.get_name())

        # If Data is in the List
        if self.fd_sub_item_list.delete(temp_item):
            self.fd_sub_item_num -= 1

        if self.fd_sub_item_num is 0:
            del self.fd_sub_item_list
            self.fd_sub_item_list = None
            # if subitem num 0 delete fd sub item list
        return 1

    """
    @brief	Retrieve one Item you search in Current Folder.
    @pre	SubItem is existed, and set path.
    @post	get one Item searched exactly in current Folder.
    @param Target Item that you want
    @return	return 1 if this function works well, otherwise 0.
    """
    def retrieve_item_by_name(self, target_item: ItemType):
        if self.fd_sub_item_num is 0:
            raise ItemNotFound(target_item.get_name())

        # If Folder is not in the Current Folder
        if not self.fd_sub_item_list.get(target_item):
            raise ItemNotFound(target_item.get_name())
        return 1

    """
    @brief	Retrieve all SubItems that contain the name you search in All child folder.
    @pre	SubItems is existed.
    @post	create search folder and return.
    @param keyword to search
    @return	return FolderType object which has search list for SubItemList.
    """
    def retrieve_items_by_name(self, keyword: str):
        retrieve_folder = FolderType()
        if self.fd_sub_item_num is 0:
            raise EmptyFolder()

        iter = BinaryIterator(self.fd_sub_item_list)
        while not iter.next_is_tail():
            # check item has keyword first
            if iter.next().get_name().find(keyword) is not -1:
                retrieve_folder.new_item(iter.cur())

            if iter.cur().what_is() is "Folder":
                if iter.cur().get_sub_item_num() is not 0:
                    #call recursive when catch, end the loop
                    try:
                        retrieve_folder += FolderType(iter.cur()).retrieve_items_by_name(keyword)
                    except Exception as ex:
                        continue

        return retrieve_folder

    """
    *	@brief	Sort SubItem list
    *	@pre	 SubItem list is existed.
    *	@post	 SubItem list be sorted.
    * @param key(string)
    *	@return	none.
    """
    def sort_sub_items(self, value="name"):
        if self.fd_sub_item_num is 0:
            return
            # do nothing

        iter = BinaryIterator(self.fd_sub_item_list)
        while not iter.next_is_tail():
            # caution : set all key value first
            iter.next().set_key_value(value)

        self.fd_sub_item_list.sort()
        return

    """
    @brief	Sort SubItem list
    @pre	 SubItem list is existed.
    @post	 SubItem list be sorted.
    @param key(int)
    @return	none.
    """

    def sort_sub_items(self, in_key=0):
        if self.fd_sub_item_num is 0:
            return
            # do nothing

        iter = BinaryIterator(self.fd_sub_item_list)
        while not iter.next_is_tail():
            # caution : set all key value first
            iter.next().set_key_value(in_key)

        self.fd_sub_item_list.sort()
        return

    """
    @brief	Display the Current Folder's SubFolder List on Screen.
    @detail if there is no sub folders return;
    @pre	Current Folder Pointer must be pointed existed Folder.
    @post	Display the Current Folder Information on Screen.
    """
    def display_all_sub_items(self):
        if self.fd_sub_item_num is 0:
            raise EmptyFolder()

        print("============ SubItem list ============")
        iter = BinaryIterator(self.fd_sub_item_list)
        while not iter.next_is_tail():
            print(iter.next())
        print("======================================")

    """
    *	@brief	Display the Current Folder's SubFolder List on Screen.
    * @detail if there is no sub folders return;
    *	@pre	Current Folder Pointer must be pointed existed Folder.
    *	@post	Display the Current Folder Information on Screen.
    """
    def display_all_sub_items_detail(self):
        if self.fd_sub_item_num is 0:
            raise EmptyFolder()

        print("============ SubItem list ============")
        iter = BinaryIterator(self.fd_sub_item_list)
        while not iter.next_is_tail():
            if iter.next().what_is() is "Folder":
                # if folder
                print("{}   {}   {}   {}".format(
                    iter.cur(), iter.cur().get_path(), iter.cur().get_sub_item_num(), iter.cur().get_access_time()))
            else:
                print("{}   {}   {}   {}".format(
                    iter.cur(), iter.cur().get_path(), 0, iter.cur().get_access_time()))

        print("======================================")

    """
    *	@brief	Reset all items key
    *	@pre	 items key is set.
    *	@post	 SubItem key be default.
    *	@return	none.
    """
    def reset_folder_key(self):
        if self.fd_sub_item_num is 0:
            return
            # do nothing

        iter = BinaryIterator(self.fd_sub_item_list)
        while not iter.next_is_tail():
            # set all items key
            iter.next().set_key_value(0)
        return