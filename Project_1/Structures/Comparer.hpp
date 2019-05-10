#ifndef _COMPARER_HPP
#define _COMPARER_HPP

/**
*	@brief	Comparer class.
*	@details	This class has operator < and > do comparing data.
*/
template<typename T>
class Comparer {
private:

  bool (*Comp)(const T &, const T &); // comparer select
  bool (*Op_Comp)(const T &, const T &);// opposite comparer selected
protected:
  /**
  *	@brief	protected compare function.
  *	@pre	none.
  *	@post	none.
  *	@return	comp.
  */
  virtual bool Compare_Impl(const T &a, const T &b);
  /**
  *	@brief	protected op_compare function.
  *	@pre	none.
  *	@post	none.
  *	@return	comp.
  */
  virtual bool Op_Compare_Impl(const T &a, const T &b);
public:
  /**
  *	default constructor.
  * @brief	Direction=1(Ascending), Direction=0(Descending)
  */
  Comparer (const int &Direction);

  /**
  *	@brief Set Direction of Comp. ASCENDING(1) DESCENDING(0)
  *	@pre	none.
  *	@post	none.
  *	@param inDirecetion ASCENDING(1) DESCENDING(0).
  *	@return	none.
  */
  void SetDirection(const int &inDirection=1) {
    if (inDirection==1) { //ASCENDING
      this->Comp=[](const T &a,const T &b)->bool{return a<b;};
      this->Op_Comp=[](const T &a,const T &b)->bool{return a>b;};
    } else { //DESCENDING
      this->Comp=[](const T &a,const T &b)->bool{return a>b;};
      this->Op_Comp=[](const T &a,const T &b)->bool{return a<b;};
    }
  }

  /**
  *	@brief	public compare function.
  *	@pre	none.
  *	@post	none.
  *	@return	comp.
  */
  bool Compare(const T & a, const T &b) ;

  /**
  *	@brief	public op compare function.
  *	@pre	none.
  *	@post	none.
  *	@return	op comp.
  */
  bool Op_Compare(const T & a, const T &b) ;

};

// protected compare function.
template<typename T> bool Comparer<T>::Compare_Impl(const T &a, const T &b){ return this->Comp(a,b); }

// protected op_compare function.
template<typename T> bool Comparer<T>::Op_Compare_Impl(const T &a, const T &b){ return this->Op_Comp(a,b); }

// Set Direction of Comp. ASCENDING(1) DESCENDING(0)
template<typename T>Comparer<T>::Comparer (const int &Direction){
  if (Direction==1) { //ASCENDING
    this->Comp=[](const T &a,const T &b)->bool{return a<b;};
    this->Op_Comp=[](const T &a,const T &b)->bool{return a>b;};
  } else { //DESCENDING
    this->Comp=[](const T &a,const T &b)->bool{return a>b;};
    this->Op_Comp=[](const T &a,const T &b)->bool{return a<b;};
  }
}

// public compare function.
template<typename T> bool Comparer<T>::Compare(const T & a, const T &b) {
  return this->Compare_Impl(a,b);
}

// public op compare function.
template<typename T> bool Comparer<T>::Op_Compare(const T & a, const T &b) {
  return this->Op_Compare_Impl(a,b);
}

#endif /* _COMPARER_HPP */
