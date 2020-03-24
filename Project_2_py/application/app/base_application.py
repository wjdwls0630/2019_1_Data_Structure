from application.item.foldertype import *
from application.item.itemtype import *
from application.item.textfiletype import *
from application.item.jpgfiletype import *
from application.item.mp3filetype import *
from application.item.foldertype import *
from application.item.filetype import *
from application.structure.linked_history_stack import *
from application.structure.linked_queue import *
from application.structure.py_heap import *
from application.error.invalid_operation import *
from application.error.item_not_found import *
from application.error.name_error import *
from application.error.no_history import *
from application.error.no_parent import *
from tkinter import *
from tkinter import ttk, messagebox
# Created by ParkJungJin on 2019-05-26.

"""@package docstring
@brief	BaseApplication class.
@details	This class processes management about Item and entire system and function
"""


class BaseApplication(object):
    """
    default constructor
    """
    m_fd_cur_ptr: FolderType

    def __init__(self):
        self.root = FolderType("Root")
        self.root.set_path("Root")
        self.root.set_parent(None)  # set root has no parent folder
        self.m_fd_cur_ptr = self.root
        self.clip_board = None # store cut and copy
        self.window = None
        self.m_command = ""

        self.m_history = LinkedHistoryStack() # store history
        self.m_recent_folder = LinkedQueue() # store recent access time
        self.m_cache = PyHeap() # search first

    def get_command(self, command: str):
        self.window = Tk()
        self.window.title("Folder Management")
        self.window.geometry("250x250")

        btn_pwd = Button(self.window, text="pwd", width=10, command= lambda : self.on_click("pwd"))
        btn_pwd.grid(row=0, column=0)

        btn_cd = Button(self.window, text="cd", width=10, command=lambda : self.on_click("cd"))
        btn_cd.grid(row=0, column=1)

        btn_mkdir = Button(self.window, text="mkdir", width=10, command=lambda : self.on_click("mkdir"))
        btn_mkdir.grid(row=1, column=0)

        btn_touch = Button(self.window, text="touch", width=10, command=lambda : self.on_click("touch"))
        btn_touch.grid(row=1, column=1)

        btn_rm = Button(self.window, text="rm", width=10, command=lambda : self.on_click("rm"))
        btn_rm.grid(row=2, column=0)

        btn_run = Button(self.window, text="run", width=10, command=lambda : self.on_click("run"))
        btn_run.grid(row=2, column=1)

        btn_copy = Button(self.window, text="copy", width=10, command=lambda : self.on_click("copy"))
        btn_copy.grid(row=3, column=0)

        btn_cut = Button(self.window, text="cut", width=10, command=lambda : self.on_click("cut"))
        btn_cut.grid(row=3, column=1)

        btn_move = Button(self.window, text="move", width=10, command=lambda : self.on_click("move"))
        btn_move.grid(row=4, column=0)

        btn_dupl = Button(self.window, text="dupl", width=10, command=lambda : self.on_click("dupl"))
        btn_dupl.grid(row=4, column=1)

        btn_paste = Button(self.window, text="paste", width=10, command=lambda : self.on_click("paste"))
        btn_paste.grid(row=5, column=0)

        btn_search = Button(self.window, text="search", width=10, command=lambda : self.on_click("search"))
        btn_search.grid(row=5, column=1)

        btn_sort = Button(self.window, text="sort", width=10, command=lambda : self.on_click("sort"))
        btn_sort.grid(row=6, column=0)

        btn_ls = Button(self.window, text="ls", width=10, command=lambda : self.on_click("ls"))
        btn_ls.grid(row=6, column=1)

        btn_info = Button(self.window, text="info", width=10, command=lambda : self.on_click("info"))
        btn_info.grid(row=7, column=0)

        btn_recent = Button(self.window, text="recent", width=10, command=lambda : self.on_click("recent"))
        btn_recent.grid(row=7, column=1)

        btn_exit = Button(self.window, text="exit", width=10, command=lambda : self.on_click("exit"))
        btn_exit.grid(row=8, column=1)

        self.window.mainloop()

    def get_op_code(self, operation: str) -> int:
        code = -1

        if operation == "pwd":
            code = 1
        elif operation == "cd":
            code =2
        elif operation == "mkdir":
            code = 3
        elif operation == "touch":
            code = 4
        elif operation == "rm":
            code = 5
        elif operation == "update":
            code = 6
        elif operation == "run":
            code = 7
        elif operation == "copy":
            code = 8
        elif operation == "cut":
            code = 9
        elif operation == "move":
            code = 10
        elif operation == "dupl":
            code = 11
        elif operation == "paste":
            code = 12
        elif operation == "search":
            code = 13
        elif operation == "sort":
            code = 14
        elif operation == "ls":
            code = 15
        elif operation == "info":
            code = 16
        elif operation == "recent":
            code = 17
        elif operation == "exit":
            code = 0

        return code

    def on_click(self, operation):
        op_code = self.get_op_code(operation)
        window_create = None
        if op_code == 1:
            self.set_string_command("pwd")

        elif op_code == 2:
            # cd
            window_create = Toplevel(self.window)
            window_create.title("Change Directory")

            ttk.Label(window_create, text="Item Name").grid(column=0, row=0)
            target = StringVar()
            item_name = ttk.Entry(window_create, width=20, textvariable=target)
            item_name.grid(column=1, row=0)

            action = ttk.Button(window_create, text = "Change Directory",
                                command= lambda : self.set_string_command("cd", target.get(), ""))
            action1 = ttk.Button(window_create, text="Go to Root",
                                command=lambda: self.set_string_command("cd", "~"))
            action2 = ttk.Button(window_create, text="Go to Parent",
                                command=lambda: self.set_string_command("cd", "../"))
            action3 = ttk.Button(window_create, text="Stay in Current",
                                command=lambda: self.set_string_command("cd", "./"))
            action4 = ttk.Button(window_create, text="Go to Back",
                                command=lambda: self.set_string_command("cd", "<"))
            action5 = ttk.Button(window_create, text="Go to Forward",
                                command=lambda: self.set_string_command("cd", ">"))

            action.grid(column=2, row =0)
            action1.grid(column=0, row=1)
            action2.grid(column=1, row=1)
            action3.grid(column=2, row=1)
            action4.grid(column=0, row=2)
            action5.grid(column=1, row=2)
            window_create.mainloop()

        elif op_code == 3:
            # mkdir
            window_create = Toplevel(self.window)
            window_create.title("Make Directory")

            ttk.Label(window_create, text="Item Name").grid(column=0, row=0)
            target = StringVar()
            item_name = ttk.Entry(window_create, width=20, textvariable=target)
            item_name.grid(column=1, row=0)

            action = ttk.Button(window_create, text="Make Directory",
                                command=lambda: self.set_string_command("mkdir", target.get(), ""))
            action.grid(column=0, row =1)
            action1 = ttk.Button(window_create, text="Make and Move Directory",
                                command=lambda: self.set_string_command("mkdir", "-o", target.get()))
            action1.grid(column=0, row=2)
            window_create.mainloop()

        elif op_code == 4:
            # touch
            window_create = Toplevel(self.window)
            window_create.title("Make File")

            ttk.Label(window_create, text="Item Name").grid(column=0, row=0)
            target = StringVar()
            item_name = ttk.Entry(window_create, width=20, textvariable=target)
            item_name.grid(column=1, row=0)

            file_type = StringVar()
            r1 = ttk.Radiobutton(window_create, text="Text", variable=file_type, value=".txt")
            r2 = ttk.Radiobutton(window_create, text="JPG", variable=file_type, value=".jpg")
            r3 = ttk.Radiobutton(window_create, text="MP3", variable=file_type, value=".mp3")
            r1.grid(column=0, row=1)
            r2.grid(column=1, row=1)
            r3.grid(column=2, row=1)

            action = ttk.Button(window_create, text="Make File",
                                command=lambda: self.set_string_command("touch", target.get()+file_type.get(), ""))
            action.grid(column=0, row =2)
            action1 = ttk.Button(window_create, text="Make and Run File",
                                command=lambda: self.set_string_command("touch", "-r", target.get()+file_type.get()))
            action1.grid(column=1, row=2)
            window_create.mainloop()

        elif op_code == 5:
            # rm
            window_create = Toplevel(self.window)
            window_create.title("Remove Item")

            ttk.Label(window_create, text="Item Name").grid(column=0, row=0)
            target = StringVar()
            item_name = ttk.Entry(window_create, width=20, textvariable=target)
            item_name.grid(column=1, row=0)

            action = ttk.Button(window_create, text="Remove Item",
                                command=lambda: self.set_string_command("rm", target.get(), ""))
            action.grid(column=0, row=1)
            action1 = ttk.Button(window_create, text="Remove All",
                                command=lambda: self.set_string_command("rm", "*"))
            action1.grid(column=1, row=1)
            window_create.mainloop()

        elif op_code == 6:
            # update
            window_create = Toplevel(self.window)
            window_create.title("Update Item")

            ttk.Label(window_create, text="Item Name").grid(column=0, row=0)
            target = StringVar()
            item_name = ttk.Entry(window_create, width=20, textvariable=target)
            item_name.grid(column=1, row=0)

            ttk.Label(window_create, text="Update Name").grid(column=0, row=1)
            value = StringVar()
            update_name = ttk.Entry(window_create, width=20, textvariable=value)
            item_name.grid(column=1, row=1)

            action = ttk.Button(window_create, text="Update Item",
                                command=lambda: self.set_string_command("update", target.get(), value.get()))
            action.grid(row=2)
            window_create.mainloop()

        elif op_code == 7:
            # run
            window_create = Toplevel(self.window)
            window_create.title("Run File")

            ttk.Label(window_create, text="Item Name").grid(column=0, row=0)
            target = StringVar()
            item_name = ttk.Entry(window_create, width=20, textvariable=target)
            item_name.grid(column=1, row=0)

            action = ttk.Button(window_create, text="Run File",
                                command=lambda: self.set_string_command("run", target.get()))
            action.grid(column=2, row=0)
            window_create.mainloop()

        elif op_code == 8:
            #copy
            window_create = Toplevel(self.window)
            window_create.title("Copy File")

            ttk.Label(window_create, text="Item Name").grid(column=0, row=0)
            target = StringVar()
            item_name = ttk.Entry(window_create, width=20, textvariable=target)
            item_name.grid(column=1, row=0)

            ttk.Label(window_create, text="Where").grid(column=0, row=1)
            value = StringVar()
            item_name = ttk.Entry(window_create, width=20, textvariable=value)
            item_name.grid(column=1, row=1)

            action = ttk.Button(window_create, text="Copy Item",
                                command=lambda: self.set_string_command("copy", target.get(), value.get()))
            action.grid(column=2, row=0)
            window_create.mainloop()

        elif op_code == 9:
            #cut
            window_create = Toplevel(self.window)
            window_create.title("Cut File")

            ttk.Label(window_create, text="Item Name").grid(column=0, row=0)
            target = StringVar()
            item_name = ttk.Entry(window_create, width=20, textvariable=target)
            item_name.grid(column=1, row=0)

            ttk.Label(window_create, text="Where").grid(column=0, row=1)
            value = StringVar()
            item_name = ttk.Entry(window_create, width=20, textvariable=value)
            item_name.grid(column=1, row=1)

            action = ttk.Button(window_create, text="Cut Item",
                                command=lambda: self.set_string_command("cut", target.get(), value.get()))
            action.grid(column=2, row=0)
            window_create.mainloop()

        elif op_code == 10:
            # move
            window_create = Toplevel(self.window)
            window_create.title("Move File")

            ttk.Label(window_create, text="Item Name").grid(column=0, row=0)
            target = StringVar()
            item_name = ttk.Entry(window_create, width=20, textvariable=target)
            item_name.grid(column=1, row=0)

            ttk.Label(window_create, text="Where").grid(column=0, row=1)
            value = StringVar()
            item_name = ttk.Entry(window_create, width=20, textvariable=value)
            item_name.grid(column=1, row=1)

            action = ttk.Button(window_create, text="Move Item",
                                command=lambda: self.set_string_command("move", target.get(), value.get()))
            action.grid(column=2, row=0)
            window_create.mainloop()

        elif op_code == 11:
            # dupl
            window_create = Toplevel(self.window)
            window_create.title("Duplicate Item")

            ttk.Label(window_create, text="Item Name").grid(column=0, row=0)
            target = StringVar()
            item_name = ttk.Entry(window_create, width=20, textvariable=target)
            item_name.grid(column=1, row=0)

            action = ttk.Button(window_create, text="Duplicate Item",
                                command=lambda: self.set_string_command("dupl", target.get()))
            action.grid(column=2, row=0)
            window_create.mainloop()

        elif op_code == 12:
            # paste
            window_create = Toplevel(self.window)
            window_create.title("Duplicate Item")

            ttk.Label(window_create, text="Where").grid(column=0, row=0)
            target = StringVar()
            item_name = ttk.Entry(window_create, width=20, textvariable=target)
            item_name.grid(column=1, row=0)

            action = ttk.Button(window_create, text="Paste Item",
                                command=lambda: self.set_string_command("paste", target.get()))
            action.grid(column=2, row=0)
            window_create.mainloop()

        elif op_code == 13:
            # search
            window_create = Toplevel(self.window)
            window_create.title("Search Item")

            ttk.Label(window_create, text="Key Word").grid(column=0, row=0)
            target = StringVar()
            item_name = ttk.Entry(window_create, width=20, textvariable=target)
            item_name.grid(column=1, row=0)

            action = ttk.Button(window_create, text="Search Item",
                                command=lambda: self.set_string_command("search", target.get()))
            action.grid(column=2, row=0)
            window_create.mainloop()

        elif op_code == 14:
            # sort
            window_create = Toplevel(self.window)
            window_create.title("Sort Item")

            direction = StringVar()
            r1 = ttk.Radiobutton(window_create, text="ASCENDING", variable=direction, value="-a")
            r2 = ttk.Radiobutton(window_create, text="DESCENDING", variable=direction, value="-d")
            r1.grid(column=0, row=0)
            r2.grid(column=1, row=0)

            action = ttk.Button(window_create, text="Name",
                                command=lambda: self.set_string_command("sort", direction.get(), "name"))
            action.grid(column=0, row =2)

            action1 = ttk.Button(window_create, text="Created Time",
                                command=lambda: self.set_string_command("sort", direction.get(), "created"))
            action1.grid(column=1, row=2)

            action2 = ttk.Button(window_create, text="Modified Time",
                                command=lambda: self.set_string_command("sort", direction.get(), "modified"))
            action2.grid(column=2, row=2)

            action3 = ttk.Button(window_create, text="Access Time",
                                command=lambda: self.set_string_command("sort", direction.get(), "access"))
            action3.grid(column=3, row=2)

            window_create.mainloop()

        elif op_code == 15:
            # ls
            window_create = Toplevel(self.window)
            window_create.title("Display Items")

            display_type = StringVar()
            r1 = ttk.Radiobutton(window_create, text="Name", variable=display_type, value="")
            r2 = ttk.Radiobutton(window_create, text="Detail", variable=display_type, value="-a")
            r1.grid(column=0, row=0)
            r2.grid(column=1, row=0)

            action = ttk.Button(window_create, text="Display Items",
                                command=lambda: self.set_string_command("ls", display_type.get()))
            action.grid(column=0, row =1)

            window_create.mainloop()

        elif op_code == 16:
            # info
            window_create = Toplevel(self.window)
            window_create.title("Display Info")

            ttk.Label(window_create, text="Item Name").grid(column=0, row=0)
            target = StringVar()
            item_name = ttk.Entry(window_create, width=20, textvariable=target)
            item_name.grid(column=1, row=0)

            action = ttk.Button(window_create, text="Display Info",
                                command=lambda: self.set_string_command("info", target.get()))
            action.grid(column=2, row=0)
            window_create.mainloop()

        elif op_code == 17:
            self.set_string_command("recent")

        elif op_code == -1 :
            # invalid operation
            pass

        elif op_code == 0:
            # exit
            self.close_window(self.window)

    def set_string_command(self, operation="", target="", value=""):
        self.m_command = operation + " " + target + " " + value
        self.close_window(self.window)

    def close_window(self, window):
        window.destroy()

    """
    @brief	Program driver.
    @pre	program is started.
    @post	program is finished.
    """
    def run(self):

        # for using temp and target and process command
        temp_folder = None
        target_item = None

        path_queue = LinkedQueue() # for store path
        check_queue = LinkedQueue() # for store path

        # command
        temp = ""
        temp_list = []

        # start to store history of root
        self.m_history.push(self.root)

        # check to move current folder by command cd
        check_cur_ptr = self.m_fd_cur_ptr

        # current time
        current_time = ""

        # check to move current folder by command cd
        while 1:
            print("~{}$".format(self.m_fd_cur_ptr.get_name()))
            self.get_command(self.m_command)
            # make command to operation and target(initialize)
            if check_cur_ptr is not self.m_fd_cur_ptr:
                check_cur_ptr.reset_folder_key()
                check_cur_ptr.sort_sub_items("")

            # initialize
            check_cur_ptr = self.m_fd_cur_ptr
            # make path queue clear
            path_queue.make_empty()

            # Split the[operation][option][value]
            # set[operation][option / target][value]
            operation, target, value = self.m_command.split(" ")

            if operation == "":
                continue # re-command

            if value == "":
                # if only has [operation] [value]
                value = target

            op_code = self.get_op_code(operation)

            # distinguish the op
            if op_code == 1:
                # case 1 : pwd
                self.m_fd_cur_ptr.display_path_on_screen()
                continue
            elif op_code == 2:
                # case 2 : cd
                try:
                    if value == "":
                        # if no value
                        continue

                    if value == "../":
                        # go to parent
                        if self.m_fd_cur_ptr is self.root:
                            # if cur folder is root
                            raise NoParent()
                            # if there is no parent folder raise no history
                        self.m_fd_cur_ptr = self.m_fd_cur_ptr.get_parent()
                        # move to parent directory
                        self.m_history.push(self.m_fd_cur_ptr)
                        # add recent item
                        self.add_recent_item(self.m_fd_cur_ptr)
                        # set access time
                        current_time = self.m_fd_cur_ptr.generate_time()
                        self.m_fd_cur_ptr.set_access_time(current_time)
                        self.m_fd_cur_ptr.set_access_count(self.m_fd_cur_ptr.get_access_count()+1)

                        # add to cache
                        self.m_cache.add(self.m_fd_cur_ptr)

                    elif value == "./":
                        # left current folder
                        continue
                        # do nothing

                    elif value == "<":
                        # go to back
                        if self.m_history.is_empty():
                            raise NoHistory()
                        self.m_history.next() # move history cur to backward
                        self.m_fd_cur_ptr = self.m_history.cur() # point cur
                        # add recent item
                        self.add_recent_item(self.m_fd_cur_ptr)
                        # set access time
                        current_time = self.m_fd_cur_ptr.generate_time()
                        self.m_fd_cur_ptr.set_access_time(current_time)
                        self.m_fd_cur_ptr.set_access_count(self.m_fd_cur_ptr.get_access_count() + 1)

                        # add to cache
                        self.m_cache.add(self.m_fd_cur_ptr)

                    elif value == ">":
                        # go to front
                        if self.m_history.is_empty():
                            raise NoHistory()
                        self.m_history.prev() # move history cur to forward
                        self.m_fd_cur_ptr = self.m_history.cur()  # point cur
                        # add recent item
                        self.add_recent_item(self.m_fd_cur_ptr)
                        # set access time
                        current_time = self.m_fd_cur_ptr.generate_time()
                        self.m_fd_cur_ptr.set_access_time(current_time)
                        self.m_fd_cur_ptr.set_access_count(self.m_fd_cur_ptr.get_access_count() + 1)

                        # add to cache
                        self.m_cache.add(self.m_fd_cur_ptr)


                    elif value =="~":
                        # go to root
                        self.m_fd_cur_ptr = self.root
                        # store history
                        self.m_history.push(self.m_fd_cur_ptr)
                        # add recent item
                        self.add_recent_item(self.m_fd_cur_ptr)
                        # set access time
                        current_time = self.m_fd_cur_ptr.generate_time()
                        self.m_fd_cur_ptr.set_access_time(current_time)
                        self.m_fd_cur_ptr.set_access_count(self.m_fd_cur_ptr.get_access_count() + 1)

                        # add to cache
                        self.m_cache.add(self.m_fd_cur_ptr)


                    else:
                        # no special value
                        if value.find(".") != -1:
                            # filter of file
                            raise NameError(value)
                        target_item = self.get_target_item_in_path(value, target_item)
                        if target_item is not None:
                            # find
                            self.m_fd_cur_ptr = target_item
                            # store history
                            self.m_history.push(self.m_fd_cur_ptr)
                            # add recent item
                            self.add_recent_item(self.m_fd_cur_ptr)
                            # set access time
                            current_time = self.m_fd_cur_ptr.generate_time()
                            self.m_fd_cur_ptr.set_access_time(current_time)
                            self.m_fd_cur_ptr.set_access_count(self.m_fd_cur_ptr.get_access_count() + 1)

                            # add to cache
                            self.m_cache.add(self.m_fd_cur_ptr)

                    continue

                except Exception as ex :
                    print("cd : {}".format(ex))
                    continue

            elif op_code == 3:
                # case 3 : mkdir (only control in current folder)
                try:
                    if value == "":
                        # if no value
                        continue

                    elif value.find('/') != -1:
                        # filter of path
                        raise NameError(value)
                    elif value.find('.') != -1:
                        # if file name
                        raise NameError(value)

                    elif target != value:
                        # mkdir [target] [value]
                        if target == "-o":
                            #mkdir -o [value] make and open
                            self.new_item(value)
                            target_item = FolderType()
                            # set item info to find
                            target_item.set_name(value)
                            target_item.set_path(self.m_fd_cur_ptr.get_path()+"/"+value)
                            # move folder made
                            self.m_fd_cur_ptr.retrieve_item_by_name(target_item)
                            self.m_fd_cur_ptr = target_item
                            # store history
                            self.m_history.push(self.m_fd_cur_ptr)
                            current_time = self.m_fd_cur_ptr.generate_time()
                            self.m_fd_cur_ptr.set_access_time(current_time)
                            self.m_fd_cur_ptr.set_access_count(self.m_fd_cur_ptr.get_access_count() + 1)
                            # add recent item
                            self.add_recent_item(self.m_fd_cur_ptr)

                            # add to cache
                            self.m_cache.add(self.m_fd_cur_ptr)
                            continue
                        else:
                            raise InvalidOperation()

                    # general case make folder
                    self.new_item(value)
                    continue

                except InvalidOperation as invaopex:
                    print("mkdir : {}".format(invaopex))
                    print("usage : mkdir [value]")
                    print("Command \'help mkdir\' give more information to you")
                    continue
                except Exception as ex:
                    print("mkdir : {}".format(ex))
                    continue

            elif op_code == 4:
                # touch(only control in current folder)
                try:
                    if value == "":
                        # if no value
                        continue
                    elif value.find('.') == -1:
                        # if folder name
                        raise NameError(value)
                    elif target != value:
                        # touch [option] [target]
                        if target == "-r":
                            # touch -r [value] make file and run
                            self.new_item(value)
                            self.run_file(value)
                        else:
                            raise InvalidOperation()

                    # general case make file
                    self.new_item(value)
                    continue

                except InvalidOperation as invaopex:
                    print("touch : {}".format(invaopex))
                    print("usage : touch [option] [value]")
                    print("Command \'help touch\' give more information to you")
                    continue

                except Exception as ex:
                    print("touch : {}".format(ex))
                    continue

            elif op_code == 5:
                #  case 5: rm(only control in current folder)
                try:
                    if value.find('/') != -1:
                        # filter of path
                        raise NameError(value)
                    elif value == "*":
                        # delete all rm *
                        self.m_fd_cur_ptr.make_empty_folder()
                        continue
                    elif value == "":
                        continue
                        # do nothing
                    elif target != value:
                        raise InvalidOperation()
                    # value has name
                    self.delete_item(value)
                    continue

                except InvalidOperation as invaopex:
                    print("rm : {}".format(invaopex))
                    print("usage : rm [value]")
                    print("Command \'help rm\' give more information to you")
                    continue

                except Exception as ex:
                    print("rm : {}".format(ex))
                    continue

            elif op_code == 6:
                # case 6 : update(only control in current folder)
                try:
                    if target == value:
                        # update or update [target]
                        continue
                        # do nothing

                    elif target != value:
                        # update [target] [ value]
                        if value.find('/') != -1 or target.find('/') != -1:
                            # filter of path(value) update[Target][Name]
                            raise NameError(value)
                        self.update_item_name(target, value)
                        self.sort_all_items("")
                    continue

                except Exception as ex:
                    print("update : {}".format(ex))
                    continue

            elif op_code == 7:
                # case 7 :run(only control in current folder)
                try:
                    if target != value:
                        # run [target] [value]
                        raise InvalidOperation()

                    if target == "":
                        # run
                        continue
                        # do nothing

                    self.run_file(value)
                    continue

                except InvalidOperation as invaopex:
                    print("run : {}".format(invaopex))
                    print("usage : run [value]")
                    print("Command \'help run\' give more information to you")
                    continue

                except Exception as ex:
                    print("run : {}".format(ex))
                    continue

            elif op_code == 8:
                # case 8 : copy
                try:
                    if target == "":
                        # copy
                        # do nothing
                        continue
                    elif target == value:
                        # copy [target]
                        # copy the data
                        self.copy_item(target)
                        # copy target and store in clipboard
                    else:
                        # copy [target] [value]
                        # all condition is satisfied
                        self.copy_item(target)
                        self.paste(value)

                    continue
                except Exception as ex:
                    print("copy : {}".format(ex))
                    continue

            elif op_code == 9:
                # case 9 : cut
                try:
                    if target == "":
                        # cut
                        # do nothing
                        continue
                    elif target == value:
                        # cut [target]
                        # cut the data
                        self.cut_item(target)
                    else:
                        # cut [target] [value]
                        self.cut_item(target)
                        self.paste(value)

                except Exception as ex:
                    print("cut : {}".format(ex))
                    continue

            elif op_code == 10 :
                # case 10 : move
                try:
                    if target == "":
                        # do nothing
                        continue
                    elif target == value:
                        # move [target]
                        raise InvalidOperation()
                    else:
                        # move [target] [value]
                        self.cut_item(target)
                        self.paste(value)

                except InvalidOperation as invaopex:
                    print("move : {}".format(invaopex))
                    print("usage : move [target] [value]")
                    print("Command \'help move\' give more information to you")
                    continue

                except Exception as ex:
                    print("move : {}".format(ex))
                    continue

            elif op_code == 11:
                # case 11: duplicate(only control in current folder)
                try:
                    if target == "":
                        # do nothing
                        continue
                    elif target != value:
                        # dupl [target] [value]
                        raise InvalidOperation()
                    else:
                        # dupl [target](target is must be in the current folder)
                        if target.find('/') != -1:
                            raise NameError(target)
                        # copy
                        self.copy_item(target)
                        # paste current folder
                        self.paste()

                except InvalidOperation as invaopex:
                    print("dupl : {}".format(invaopex))
                    print("usage : dupl [target]")
                    print("Command \'help dupl\' give more information to you")
                    continue

                except Exception as ex:
                    print("dupl : {}".format(ex))
                    continue


            elif op_code == 12:
                # case 12: paste
                try:
                    if target == "":
                        # do nothing
                        self.paste() # paste (paste in current folder
                    elif target != value:
                        # paste [target] [value]
                        raise InvalidOperation()
                    else:
                        # paste [value](where)
                        self.paste(value)

                except InvalidOperation as invaopex:
                    print("paste : {}".format(invaopex))
                    print("usage : paste [target]")
                    print("Command \'help paste\' give more information to you")
                    continue

                except Exception as ex:
                    print("paste : {}".format(ex))
                    continue

            elif op_code == 13:
                # case 13: search keyword
                try:
                    if target == "":
                        # do nothing
                        raise InvalidOperation()
                    elif target != value:
                        # search [target] [value]
                        raise InvalidOperation()
                    self.search_items_by_name(value)
                    continue


                except InvalidOperation as invaopex:
                    print("search : {}".format(invaopex))
                    print("search : search [target]")
                    print("Command \'help search\' give more information to you")
                    continue

                except Exception as ex:
                    print("search : {}".format(ex))
                    continue

            elif op_code == 14:
                # case 14: sort(only control in current folder)
                try:
                    if target != value:
                        if target == "-a":
                            if value != "" and value != "name" and target != "value" and target != "value" and target != "value":
                                # sort[Key] (Options must be key value)
                                # if option == "" default is key value
                                raise InvalidOperation()
                            self.m_fd_cur_ptr.set_direction(1)
                            self.sort_all_items(value)
                            continue

                        if target == "-d":
                            # sort -d[Value] sort direction is DESCENDING(0)
                            if value != "" and value != "name" and value != "created" and value != "modified" and value != "access":
                                # sort[Key] (Options must be key value)
                                # if option == "" default is key value
                                raise InvalidOperation()
                            self.m_fd_cur_ptr.set_direction(0)
                            self.sort_all_items(value)

                    else:
                        raise InvalidOperation()


                except InvalidOperation as invaopex:
                    print("sort : {}".format(invaopex))
                    print("usage : sort [target]")
                    print("Command \'help sort\' give more information to you")
                    continue

                except Exception as ex:
                    print("sort : {}".format(ex))
                    continue

            elif op_code == 15:
                # case 15: ls(only control in current folder)
                try:
                    if target == "":
                        # ls
                        self.display_all_items()
                    elif target == "-a":
                        self.display_all_items_detail()
                    else:
                        raise InvalidOperation()


                except InvalidOperation as invaopex:
                    print("ls : {}".format(invaopex))
                    print("usage : ls [target]")
                    print("Command \'help ls\' give more information to you")
                    continue

                except Exception as ex:
                    print("ls : {}".format(ex))
                    continue

            elif op_code == 16:
                # case 16: info(only control in current folder)
                try:
                    if target != value:
                        raise InvalidOperation()

                    if value.find('/') != -1:
                        # filter of path throw
                        raise NameError(value)
                    elif value != "":
                        # display item named Value info
                        self.display_item_info(value)

                    else:
                        # Value="" default display info of current folder
                        self.display_cur_folder_info()
                    continue

                except InvalidOperation as invaopex:
                    print("info : {}".format(invaopex))
                    print("usage : info [target]")
                    print("Command \'help info\' give more information to you")
                    continue

                except Exception as ex:
                    print("info : {}".format(ex))
                    continue

            elif op_code == 17:
                # case 17: recent(only control in current folder)
                try:
                    if target != "":
                        # recent [target] or recent [target] [value]
                        raise InvalidOperation()
                    self.display_recent_folder()
                    continue

                except InvalidOperation as invaopex:
                    print("recent : {}".format(invaopex))
                    print("usage : recent [target]")
                    print("Command \'help recent\' give more information to you")
                    continue

                except Exception as ex:
                    print("recent : {}".format(ex))
                    continue

            elif op_code == -1:
                # nothing operation
                print("Error : Command Not Found : {}".format(operation))
                continue

            elif op_code == 0:
                # exit
                print("Exit the program...")
                return

    def check_value_item_type(self, value: str) -> int:
        if value.find("../") != -1 or value.find("./") != -1 or value.find("<") != -1 or value.find(">") != -1 or value.find("~") != -1 :
            # if it is not folder name type
            # cd operation and contain .(execution) throw name error
            raise NameError(value)

        # check name error finish, then check file or folder
        # if find.(extensions) it is file
        if value.find(".txt") != -1:
            # text file : 1
            return 1

        elif value.find(".jpg") != -1 :
            # jpg file : 2
            return 2

        elif value.find(".mp3") != -1 :
            # jpg file : 2
            return 3

        return 0 # if it is folder

    def path_processor(self, path: str, path_queue: LinkedQueue) -> int:
        if path.find('/') == -1:
            # if just move in current folder subfolder
            path_queue.enqueue(path)
            return self.check_value_item_type(path) # folder return 0, text file: 1 jpg file: 2 mp3 file: 3;

        pos = 0
        name_last_index = 0
        name = ""

        # spliting path
        while path.find('/', pos) != -1:
            # loop for find all '/'
            # initiallize
            pos = 0
            name_last_index = 0
            name = ""
            # search
            name_last_index = path.find('/', pos) - 1 # set name last index
            name = path[0:name_last_index+1] # split
            if name != "":
                # if name is real data
                path_queue.enqueue(name)

            # erase
            path = path[name_last_index+1:]

        # last word test folder or file
        name  = path[0:]
        if name != "":
            path_queue.enqueue(name)

        # folder return 0, text file: 1 jpg file: 2 mp3 file: 3;
        return self.check_value_item_type(name)

    def get_target_item_in_path(self, target: str, target_item, temp_cur_folder=None):
        temp_item = None

        # for path process
        path_queue = LinkedQueue()
        temp_cur_folder = self.m_fd_cur_ptr # temp cur ptr

        # split [target]
        result_split = self.path_processor(target, path_queue)

        if result_split == 0:
            temp_item = FolderType()
            try:
                while 1:
                    if path_queue.get_length() == 1:
                        # if end of search it remain folder
                        # this->m_fdCurPointer not move
                        break

                    # set condition for search
                    if path_queue.front() == "../":
                        if temp_cur_folder == self.root:
                            # if temp cur point root
                            raise NoParent()
                        temp_cur_folder = temp_cur_folder.get_parent()
                        temp_item.set_name(temp_cur_folder.get_name())
                        temp_item.set_path(temp_cur_folder.get_path()+"/"+temp_cur_folder.get_path())
                        path_queue.dequeue()
                        continue

                    elif path_queue.front() == "./":
                        # stay in current folder
                        temp_item.set_name(temp_cur_folder.get_name())
                        temp_item.set_path(temp_cur_folder.get_path() + "/" + temp_cur_folder.get_path())
                        path_queue.dequeue()
                        continue

                    else :
                        temp_item.set_name(path_queue.front())
                        temp_item.set_path(temp_cur_folder.get_path() + "/" + path_queue.front());
                        # search
                        temp_cur_folder.retrieve_item_by_name(temp_item)
                        path_queue.dequeue() # dequeue
                        temp_cur_folder = temp_item # set cur pointer again

                # Set the folder info PathQueue last word
                target_item = FolderType()
                if path_queue.front() == "../":
                    # move to parent
                    if target_item == self.root:
                        # if temp cur point root
                        raise NoParent()
                    return temp_cur_folder.get_parent()

                elif path_queue.front() == "./":
                    # stay in current folder

                    return temp_cur_folder

                else:
                    target_item.set_name(path_queue.front())
                    target_item.set_path(temp_cur_folder.get_path()+"/"+path_queue.front())

                    retrieve_item = temp_cur_folder.retrieve_item_by_name(target_item)
                    if retrieve_item is None:
                        raise ItemNotFound(target)

                    return retrieve_item

            except ItemNotFound as itex:
                # for no search result
                raise itex
            except EmptyQueue as eqex:
                return

        elif result_split == 1 or result_split == 2 or result_split == 3:
            try:
                while 1:
                    if path_queue.get_length() == 1:
                        # if end of search it remain folder
                        # this->m_fdCurPointer not move
                        break

                    # set condition for search
                    if path_queue.front() == "../":
                        if temp_cur_folder == self.root:
                            # if temp cur point root
                            raise NoParent()
                        temp_cur_folder = temp_cur_folder.get_parent()
                        temp_item.set_name(temp_cur_folder.get_name())
                        temp_item.set_path(temp_cur_folder.get_path()+"/"+temp_cur_folder.get_path())
                        path_queue.dequeue()
                        continue

                    elif path_queue.front() == "./":
                        # stay in current folder
                        temp_item.set_name(temp_cur_folder.get_name())
                        temp_item.set_path(temp_cur_folder.get_path() + "/" + temp_cur_folder.get_path())
                        path_queue.dequeue()
                        continue

                    else :
                        temp_item.set_name(path_queue.Front());
                        temp_item.set_path(temp_cur_folder.get_path() + "/" + path_queue.front());
                        # search
                        temp_cur_folder.retrieve_item_by_name(temp_item)
                        path_queue.dequeue() # dequeue
                        temp_cur_folder = temp_item # set cur pointer again

                # Set the file info PathQueue last word
                file_type_num = self.check_value_item_type(path_queue.front())
                # text file : 1  jpg file : 2 mp3 file : 3;
                if file_type_num ==1:
                    target_item = TextFileType()
                elif file_type_num == 2:
                    target_item = JPGFileType()
                elif file_type_num == 3:
                    target_item = MP3FileType()

                target_item.set_name(path_queue.front())
                target_item.set_path(temp_cur_folder.get_path() + "/" + path_queue.front())
                retrieve_item = temp_cur_folder.retrieve_item_by_name(target_item)
                if retrieve_item is None:
                    raise ItemNotFound(target)
                #target_item = temp_cur_folder.retrieve_item_by_name(target_item)
                return retrieve_item

            except ItemNotFound as itex:
                # for no search result
                raise itex
            except EmptyQueue as eqex:
                return

        # if all fail
        return 0

    def new_item(self, value: str) -> int:
        temp_item = None
        type_num = self.check_value_item_type(value)
        if type_num == 0:
            # folder
            temp_item = FolderType()

        # file
        # text file: 1 jpg file: 2 mp3 file: 3;
        elif type_num == 1:
            temp_item = TextFileType()

        elif type_num == 2:
            temp_item = JPGFileType()

        elif type_num == 3:
            temp_item = MP3FileType()

        # set the item info to add
        # set item name
        temp_item.set_name(value)
        # set sub item path
        temp_item.set_path(self.m_fd_cur_ptr.get_path()+"/"+value)

        if self.m_fd_cur_ptr.new_item(temp_item):
            # create new item
            return 1

        return 0

    def delete_item(self, value: str) -> int:
        temp_item = None
        type_num = self.check_value_item_type(value)
        if type_num == 0:
            # folder
            temp_item = FolderType()

        # file
        # text file: 1 jpg file: 2 mp3 file: 3;
        elif type_num == 1:
            temp_item = TextFileType()

        elif type_num == 2:
            temp_item = JPGFileType()

        elif type_num == 3:
            temp_item = MP3FileType()

        # set the item info to delete
        # set item name
        temp_item.set_name(value)
        # set sub item path
        temp_item.set_path(self.m_fd_cur_ptr.get_path()+"/"+value)

        if self.m_fd_cur_ptr.delete_item(temp_item):
            # delete item
            return 1

        return 0

    def update_item_name(self, target: str, value: str) -> int:
        temp_item = None
        target_type_num = self.check_value_item_type(target)
        value_type_num = self.check_value_item_type(value)

        # current time
        current_time = ""

        if target_type_num == 0:
            # folder(target)
            if value_type_num == 0:
                # folder(value)
                temp_item = FolderType()
                temp_item.set_name(target)
                # set sub folder path
                temp_item.set_path(self.m_fd_cur_ptr.get_path()+"/"+target)
                if not self.m_fd_cur_ptr.retrieve_item_by_name(temp_item):
                    raise ItemNotFound(target)

                # update folder name
                temp_item.set_name(value)
                # update folder path
                temp_item.set_path(self.m_fd_cur_ptr.get_path() + "/" + value)
                # set modified time
                current_time = temp_item.generate_time()
                temp_item.set_modified_time(current_time)
                return 1
            else:
                raise NameError(value)

        # file
        # text file: 1 jpg file: 2 mp3 file: 3;
        elif target_type_num == 1:
            temp_item = TextFileType()
            if value_type_num != 1:
                raise NameError(value)

        elif target_type_num == 2:
            temp_item = JPGFileType()
            if value_type_num != 2:
                raise NameError(value)

        elif target_type_num == 3:
            temp_item = MP3FileType()
            if value_type_num != 3:
                raise NameError(value)

        # file part only
        # set the file info to update
        # set sub file name
        temp_item.set_name(target)
        # set sub file path
        temp_item.set_path(self.m_fd_cur_ptr.get_path() + "/" + target)
        if not self.m_fd_cur_ptr.retrieve_item_by_name(temp_item):
            # if not found
            raise ItemNotFound(target)
        # update sub file name
        temp_item.set_name(value)
        #update sub file path
        temp_item.set_path(self.m_fd_cur_ptr.get_path()+"/"+value)
        # set modified time
        current_time = temp_item.generate_time()
        temp_item.set_modified_time(current_time)
        return 1 # update file

    def run_file(self, target: str) -> int:
        # already filter folder in Run()

        # current time
        current_time = ""

        # for setting value;
        target_item = None
        target_item = self.get_target_item_in_path(target, target_item)
        if target_item is not None:
            target_item.run()

            # add recent item
            self.add_recent_item(target_item)

            # set access time
            current_time = target_item.generate_time()
            target_item.set_access_time(current_time)
            target_item.set_access_count(target_item.get_access_count()+1)

            # add to cache
            self.m_cache.add(target_item)
            return 1

        return 0

    def copy_item(self, target: str) -> int:
        target_item = None
        target_item = self.get_target_item_in_path(target, target_item)
        if target_item is not None:
            if self.clip_board is not None:
                del self.clip_board

            if target_item.what_is() == "Folder":
                self.clip_board = FolderType()
                # copy
                self.clip_board = deepcopy(target_item)

            elif target_item.what_is() == "TextFile":
                self.clip_board = TextFileType()
                # copy
                self.clip_board = deepcopy(target_item)

            elif target_item.what_is() == "JPGFile":
                self.clip_board = JPGFileType()
                # copy
                self.clip_board = deepcopy(target_item)

            elif target_item.what_is() == "MP3File":
                self.clip_board = MP3FileType()
                # copy
                self.clip_board = deepcopy(target_item)

            return 1

        return 0

    def cut_item(self, target) -> int:
        target_item = None
        temp_cur_folder = None
        target_item = self.get_target_item_in_path(target, target_item, temp_cur_folder)
        if target_item is not None:
            if self.clip_board is not None:
                del self.clip_board

            if target_item.what_is() == "Folder":
                self.clip_board = FolderType()
                # copy
                self.clip_board = deepcopy(target_item)

            elif target_item.what_is() == "TextFile":
                self.clip_board = TextFileType()
                # copy
                self.clip_board = deepcopy(target_item)

            elif target_item.what_is() == "JPGFile":
                self.clip_board = JPGFileType()
                # copy
                self.clip_board = deepcopy(target_item)

            elif target_item.what_is() == "MP3File":
                self.clip_board = MP3FileType()
                # copy
                self.clip_board = deepcopy(target_item)

            # delete
            if not target_item.get_parent().delete_item(target_item):
                raise ItemNotFound(target_item.get_name())
            return 1

        return 0

    def paste(self, value="") -> int:
        if self.clip_board is None:
            # if has no data in clip board do nothing
            return 0

        if value.find(".") != -1:
            # filter file
            raise NameError(value)

        target_item = None
        target_item = self.get_target_item_in_path(value, target_item)
        if target_item is not None:
            # paste
            # set clip board new path
            self.clip_board.set_path(target_item.get_path()+"/"+self.clip_board.get_name())
            target_item.new_item(self.clip_board)
            return 1

        return 0

    def search_items_by_name(self, value: str):
        # store current key
        cur_key = self.m_fd_cur_ptr.get_key()

        # searching more fast when it sorted by name so change criteria to name
        # reset key to name

        self.m_fd_cur_ptr.reset_folder_key()

        # and sort
        self.m_fd_cur_ptr.sort_sub_items("")

        # searching

        # using py heap search cache first
        retrieve_folder = FolderType()
        retrieve_folder_heap = FolderType()
        temp_cache = deepcopy(self.m_cache)
        item_heap = None
        for i in range(0, temp_cache.get_length()):
            item_heap = temp_cache.dequeue()
            # if not find value
            if item_heap.get_name().find(value) != -1:
                retrieve_folder_heap.new_item(item_heap)

        retrieve_folder = self.m_fd_cur_ptr.retrieve_items_by_name(value)
        retrieve_folder += retrieve_folder_heap

        retrieve_folder.display_all_sub_items_detail()

        # and reset to current
        self.m_fd_cur_ptr.sort_sub_items(cur_key)


    def sort_all_items(self, value="name"):
        # defalut name
        # sorting
        self.m_fd_cur_ptr.sort_sub_items(value)

    def sort_all_items(self, in_key=0):
        # defalut name
        # sorting
        self.m_fd_cur_ptr.sort_sub_items(in_key)

    def display_all_items(self):
        # display
        self.m_fd_cur_ptr.display_all_sub_items()

    def display_all_items_detail(self):
        # display
        self.m_fd_cur_ptr.display_all_sub_items_detail()

    def display_item_info(self, value: str):
        temp_item = None
        temp_folder = None
        value_type_num = self.check_value_item_type(value)
        if value_type_num == 0:
            temp_item = FolderType()

        elif value_type_num == 1:
            temp_item = TextFileType()

        elif value_type_num == 2:
            temp_item = JPGFileType()

        elif value_type_num == 3:
            temp_item = MP3FileType()

        temp_item.set_name(value)
        temp_item.set_path(self.m_fd_cur_ptr.get_path()+"/"+value)
        if self.m_fd_cur_ptr.retrieve_item_by_name(temp_item):
            temp_item.display_info_on_screen()
            return

    def display_cur_folder_info(self):
        # display
        self.m_fd_cur_ptr.display_info_on_screen()

    def add_recent_item(self, temp_item: ItemType) -> int:
        try:
            if self.m_recent_folder.get_length() == 0:
                # if no data in queue
                self.m_recent_folder.enqueue(temp_item)
                return 1

            if self.m_recent_folder.get_length() > 30:
                # max size is 30
                self.m_recent_folder.dequeue()

            temp_queue = LinkedQueue() # for store
            length = self.m_recent_folder.get_length() # when call dequeue length is changed
            for i in range(0, length):
                if self.m_recent_folder.front().get_path() != temp_item.get_path():
                    # if data is not overlap( if directory is changed name can be overlapped
                    temp_queue.enqueue(self.m_recent_folder.front())
                self.m_recent_folder.dequeue()

            # deep copy
            self.m_recent_folder = deepcopy(temp_queue)
            self.m_recent_folder.enqueue(temp_item) # and enqueue data finally
            return 1

        except Exception as ex:
            print(ex)
            return 0

    def display_recent_folder(self):
        if self.m_recent_folder.get_length() == 0:
            # if has no recent item
            print("No Result")
            return

        temp_queue = LinkedQueue() # for store
        temp_item = ItemType()

        # when call dequeue length is changed
        length = self.m_recent_folder.get_length()
        print( "========= Recent Item List =========")

        for i in range(0, length):
            temp_item = self.m_recent_folder.front()
            # display
            print("{}   {}   {}   {}".format(
                temp_item, temp_item.get_path(), temp_item.get_sub_item_num(), temp_item.get_access_time()))
            temp_queue.enqueue(self.m_recent_folder.front())
            self.m_recent_folder.dequeue()

        self.m_recent_folder = deepcopy(temp_queue) #deep copy
        print("====================================")
"""
Test Code
"""
if __name__ == '__main__':
    app = BaseApplication()
    app.run()