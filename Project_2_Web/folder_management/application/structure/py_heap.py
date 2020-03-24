from folder_management.application.structure.hnodetype import *
from folder_management.application.structure.comparer import *
from copy import deepcopy
from math import floor

# Created by ParkJungJin on 2019-05-27.


"""@package docstring
@brief	PyHeap class.
@details	specialized tree-based data structure which is essentially an almost complete tree
that satisfies the heap property
"""

MAXSIZE = 100


class PyHeap(object):

    """
    default constructor.
    """
    def __init__(self, in_direction=ASCENDING):
        self.h_heap = None  # array
        self.h_last_node = 0  # end of array
        self.h_max_size = MAXSIZE # max size of array
        self.h_direction = in_direction # ASCENDING(1) minheap, DESCENDING(0) maxheap
        self.h_comparer = Comparer(in_direction)  # set Compare (for direction)

    """
    Destructor.
    """
    def __del__(self):
        if not self.is_empty():
            self.make_empty()

    """
    @brief	Check heap is empty.
    @pre	none.
    @post	none.
    @return	return true if heap is empty, otherwise return false.
    """
    def is_empty(self) -> bool:
        if self.h_last_node == 0:
            return True

        return False

    """
    @brief	Check heap is full.
    @details return true h_iLastNode arrive maxsize
    @pre	none.
    @post	none.
    @return	return true if heap is full, otherwise return false.
    """
    def is_full(self) -> bool:
        if self.h_last_node == self.h_max_size:
            return True

        return False

    """
    @brief	Get a number of Node in current heap.
    @pre	none.
    @post	none.
    @return	number of Node in current heap.
    """
    def get_length(self) -> int:
        return self.h_last_node

    """
    @brief	Get Direction.
    @pre	none.
    @post	none.
    @return	Get Direction of tree.
    """
    def get_direction(self) -> int:
        return self.h_direction

    """
    @brief	Set Direction.
    @pre	none.
    @post	Set Direction.
    @param Direction to set.
    """
    def set_direction(self, in_direction: int):
        if self.h_direction is not in_direction:
            self.h_direction = in_direction
            self.h_comparer.set_direction(in_direction)
            temp = PyHeap(self.h_direction)
            for i in range(0, self.h_last_node):
                temp.add(self.h_heap[i].get_data())

            del self.h_heap
            self.h_heap = []
            self.h_heap = temp.h_heap
            del temp
            return
        # if direction is same, do nothing

    """
    @brief	Initialize heap to empty state.
    @pre	None
    @post	heap is empty.
    """
    def make_empty(self):
        del self.h_heap
        self.h_last_node = 0

    """
    @brief	Add item into appropriate spot of this heap.
    @pre	heap is not full. item is not in heap.
    @post	heap is inserted in this list.
    @return	1 if this function works well, otherwise 0.
    """
    def add(self, data) -> int:
        if self.is_full():
            print("heap is full!")
            return 0

        new_node = HNodeType()
        new_node.set_data(data)
        if self.is_empty():
            self.h_heap = []
            #memory 지정

            # no need to sort
            self.h_heap.append(new_node)
            self.h_last_node += 1
            return 1

        if not self.get(data):
            # if it is not empty and data is not overlapped
            self.h_heap.append(new_node)
            self.re_heap_up(0, self.h_last_node)
            self.h_last_node += 1
            return 1

        # if data is overlapped, do nothing
        return 0

    """
    @brief	Delete item from this heap.
    @pre	heap is not empty. the heap exists in list.
    @post	heap is deleted from this list.
    @return	1 if this function works well, otherwise 0.
    """
    def delete(self, data) -> int:
        # if heap is empty
        if self.is_empty():
            return 0

        if self.get(data):
            # if data is in the tree
            self.delete_recur(data, 0)
            self.h_last_node -= 1
            return 1

        # if data is not in the heap
        return 0


    """
    @brief	Delete item from this heap.
    @details call recursively and find (binary search)
    @pre	heap should be initialized. the item exists in tree.
    @post	Item is deleted from this tree. iParent is curret position
    @param  data to delete ,
    @return	1 if this function works well, otherwise 0.
    """
    def delete_recur(self, data, i_parent: int) -> int:
        left_child = i_parent * 2 + 1  # left child
        right_child = i_parent * 2 + 2  # right child

        if self.h_comparer.is_equal(self.h_heap[i_parent].get_data(), data):
            # if found data
            self.h_heap[i_parent].set_data(self.h_heap[self.h_last_node-1].get_data())
            self.re_heap_down(i_parent, self.h_last_node-2)  # sort
            return 1
        elif left_child < self.h_last_node:
            return self.delete_recur(data, left_child)  # move left

        elif right_child < self.h_last_node:
            return self.delete_recur(data, right_child)  # move right
        # if not found
        return 0



    """
    @brief  Remove the First data from the heap, if Queue is empty throw EmptyHeap Exception
    @pre	heap should be initialized.
    @post	Remove the First data from the heap.
    @return return data deleted.
    """
    def dequeue(self):
        if not self.is_empty():
            data = self.h_heap[0].get_data()
            self.delete(data)
            return data

    """
    @brief	get the data which has same in the heap.(Binary Search)
    @pre	data to search should be initialized
    @param	data that you want(search) to get.
    @return	return 1 if this function works well, otherwise 0.
    """
    def get(self, data) -> int:
        if self.is_empty():
            return 0
        return self.get_recur(data, 0)

    """
    @brief	get the data which has same in the tree.(Binary Search)
    @details check all nodes in tree by recursive
    @pre	data to search should be initialized
    @param	data that you want(search) to get. iParent is current position
    @return	return 1 if this function works well, otherwise 0.
    """
    def get_recur(self, data, i_parent: int):
        left_child = i_parent*2+1
        right_child = i_parent*2+2

        if self.h_comparer.is_equal(self.h_heap[i_parent].get_data(), data):
            # if found
            data = self.h_heap[i_parent].get_data()
            return 1

        if left_child < self.h_last_node:
            return self.get_recur(data, left_child)  # move to left

        if right_child < self.h_last_node:
            return self.get_recur(data, right_child)  # move to right

        return 0

    """
    @brief	Display all data in Heap.
    @pre	Heap is initialized
    @post	Display all data in Heap.
    """
    def display_all(self):
        for i in range(0, self.h_last_node) :
            print(self.h_heap[i].get_data(), end=' ')
        print("")

    """
    @brief	by moving top to bottom, compare and swap data
    @pre	Heap is initialized.
    @post	compare data and swap.
    @param	iparent	data moved from top to bottom.
    @param	ibottom	last data.
    """
    def re_heap_down(self, i_parent: int, i_bottom: int):

        left_child = i_parent * 2 + 1
        right_child = i_parent * 2 + 2
        # choose left or right child
        if left_child <= i_bottom :
            if left_child == i_bottom :
                child_select = left_child
            else:
                if self.h_comparer.compare(self.h_heap[right_child].get_data(), self.h_heap[left_child].get_data()):
                    # ASCENDING(1) MinHeap
                    # DESCENDING(0) MaxHeap
                    child_select = right_child
                else:
                    child_select = left_child

            if self.h_comparer.compare(self.h_heap[child_select].get_data(), self.h_heap[i_parent].get_data()):
                self.swap(i_parent, child_select)
                self.re_heap_down(child_select, i_bottom)

    """
    @brief	by moving bottom to top, compare and swap data.
    @pre	Heap is initialized.
    @post	compare data and swap.
    @param	iroot	first data.
    @param	ibottom	data moved from bottom to top.
    """
    def re_heap_up(self, i_root: int, i_bottom: int):
        if i_bottom > i_root:
            i_parent = floor((i_bottom - 1) / 2)
            if self.h_comparer.compare(self.h_heap[i_bottom].get_data(), self.h_heap[i_parent].get_data()):
                # ASCENDING(1) MinHeap
                # DESCENDING(0) MaxHeap
                self.swap(i_parent, i_bottom)  # swap two data
                self.re_heap_up(i_root, i_parent)  # go up and re sort

    """
    @brief	swap the data in heap.
    @pre	data is existed in heap.
    @post	swap two data.
    @param	iparent	Top data to change.
    @param	ibottom	Bottom data to change.
    """
    def swap(self, i_parent: int, i_bottom: int):
        self.h_heap[i_parent], self.h_heap[i_bottom] = self.h_heap[i_bottom], self.h_heap[i_parent]


"""
Test Code
"""
if __name__ == "__main__":

    from random import sample, shuffle

    bt_test = PyHeap()

    bt_test.add(3)
    bt_test.add(2)
    bt_test.add(1)
    bt_test.add(4)
    bt_test.add(5)
    bt_test.add(6)
    bt_test.add(10)
    bt_test.add(7)
    bt_test.add(9)
    bt_test.add(8)
    print("bt_test")
    bt_test.display_all()

    print("\n\n")


    print("bt")
    bt = PyHeap()
    num_list = sample(range(1, 100), 10)
    shuffle(num_list)
    print(num_list)
    for i in range(0, 10):
        bt.add(num_list[i])

    bt.display_all()
    print("\n\n")

    print("add 22")
    bt.add(22)
    bt.display_all()
    print("\n\n")

    target = 22
    print("get 22 : {}".format(bool(bt.get(target))))
    print("\n\n")

    print("delete 22")
    bt.delete(target)
    bt.display_all()
    print("\n\n")

    print("DESCENDING bt")
    bt.set_direction(0)
    bt.display_all()
    print("\n\n")

    print("bt1")
    bt1 = PyHeap()
    num_list1 = sample(range(1, 100), 10)
    shuffle(num_list1)
    print(num_list1)
    for i in range(0, 10):
        bt1.add(num_list1[i])

    bt1.display_all()
    print("\n\n")

    print("bt = bt1")
    bt = deepcopy(bt1)
    print("bt")
    bt.display_all()
    print("bt1")
    bt1.display_all()

    print("bt1 empty")
    bt1.make_empty()
    bt1.display_all()
    print("bt is not change")
    bt.display_all()
    print("\n\n")

