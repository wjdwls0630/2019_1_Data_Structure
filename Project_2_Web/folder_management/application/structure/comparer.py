# Created by ParkJungJin on 2019-05-23.

"""@package docstring
@brief	Comparer class.
@details	This class has operator < and > do comparing data.
"""

ASCENDING = 1
DESCENDING = 1


class Comparer(object):
    """
    Default Constructor
    @brief direction=1 (ASCENDING) direction=0(DESCENDING)
    """
    def __init__(self, direction=ASCENDING ):
        if direction == 1:
            # ASCENDING(1)
            # comparer select
            self.comp = lambda t1, t2: t1 < t2
            # opposite comparer selected
            self.op_comp = lambda t1, t2: t1 > t2
        else:
            # DESCENDING(1)
            self.comp = lambda t1, t2: t1 > t2
            self.op_comp = lambda t1, t2: t1 < t2

        self.equal = lambda t1, t2: t1 == t2

    """
    @brief Set Direction of Comp. ASCENDING(1) DESCENDING(0)
    @pre	none.
    @post	none.
    @param in_direction ASCENDING(1) DESCENDING(0).
    @return	none.
    """
    def set_direction(self, in_direction=ASCENDING):
        if in_direction == 1:
            # ASCENDING(1)
            # comparer select
            self.comp = lambda t1, t2: t1 < t2
            # opposite comparer selected
            self.op_comp = lambda t1, t2: t1 > t2
        else:
            # DESCENDING(1)
            self.comp = lambda t1, t2: t1 > t2
            self.op_comp = lambda t1, t2: t1 < t2

        self.equal = lambda t1, t2: t1 == t2

    """
    @brief	public compare function.
    @pre	none.
    @post	none.
    @return	comp.
    """
    def compare(self, t1, t2) -> bool:
        return self.comp(t1, t2)

    """
    @brief	public op compare function.
    @pre	none.
    @post	none.
    @return	op comp.
    """
    def op_compare(self, t1, t2) -> bool:
        return self.op_comp(t1, t2)

    """
    @brief	public equal function.
    @pre	none.
    @post	none.
    @return	equal.
    """
    def is_equal(self, t1, t2) -> bool:
        return self.equal(t1, t2)


"""
Test Code
"""
if __name__ == "__main__":
    m_comparer1 = Comparer()
    print("1 < 2 : {}".format(m_comparer1.comp(1, 2)))
    print("1 > 3 : {}".format(m_comparer1.op_comp(1, 3)))
    print("1 == 2 : {}".format(m_comparer1.equal(1, 2)))

    m_comparer2 = Comparer(0)
    print("1 > 2 : {}".format(m_comparer2.comp(1, 2)))
    print("1 < 3 : {}".format(m_comparer2.op_comp(1, 3)))
    print("1 == 1 : {}".format(m_comparer2.equal(1, 1)))




