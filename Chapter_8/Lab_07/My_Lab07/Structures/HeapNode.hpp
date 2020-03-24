//
// Created by ParkJungJin on 2019-05-27.
//

#ifndef _HEAPNODE_HPP
#define _HEAPNODE_HPP


/**
*	@brief	HeapNode class.
*	@details	This class has data and next pointer.
*/
template <typename T>
class HeapNode {
private:
  T Data;	///< A data for each node.
public:
  /**
  *	default constructor.
  */
  HeapNode (){}


  /**
  *	@brief	Get Data.
  *	@pre	Data should be initialized.
  *	@post	Get Data.
  *	@return	Data.
  */
  T GetData() { return this->Data; }
  /**
  *	@brief	Get Data.
  *	@pre	Data should be initialized.
  *	@post	Get Data.
  *	@return	Data.
  */
  T* GetDataPtr() { return &this->Data; }

  /**
	*	@brief	Set Data
	*	@pre	none.
	*	@post	Data is set.
	*	@param	inData set Data.
	*/
  void SetData(T inData) { this->Data=inData; }


};

#endif //_HEAPNODE_HPP
