#ifndef _COMPARER_HPP
#define _COMPARER_HPP

//class Comparer declaration
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
  *	@brief	protected compare function.
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
  *	@brief	protected compare function.
  *	@pre	none.
  *	@post	none.
  *	@return	comp.
  */
  bool Compare(const T & a, const T &b) ;

  /**
  *	@brief	protected op compare function.
  *	@pre	none.
  *	@post	none.
  *	@return	op comp.
  */
  bool Op_Compare(const T & a, const T &b) ;

};

//class Comparer definition

template<typename T> bool Comparer<T>::Compare_Impl(const T &a, const T &b){ return this->Comp(a,b); }
template<typename T> bool Comparer<T>::Op_Compare_Impl(const T &a, const T &b){ return this->Op_Comp(a,b); }

template<typename T>Comparer<T>::Comparer (const int &Direction){
  if (Direction==1) {
    this->Comp=[](const T &a,const T &b)->bool{return a<b;};
    this->Op_Comp=[](const T &a,const T &b)->bool{return a>b;};
  } else {
    this->Comp=[](const T &a,const T &b)->bool{return a>b;};
    this->Op_Comp=[](const T &a,const T &b)->bool{return a<b;};
  }
}
template<typename T> bool Comparer<T>::Compare(const T & a, const T &b) {
  return this->Compare_Impl(a,b);
}
template<typename T> bool Comparer<T>::Op_Compare(const T & a, const T &b) {
  return this->Op_Compare_Impl(a,b);
}

#endif /* _COMPARER_HPP */
