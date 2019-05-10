#ifndef _NODETYPE_HPP
#define _NODETYPE_HPP

/**
*	@brief	NodeType class.
*	@details	This class has data and next pointer.
*/
template <typename T>
class NodeType {
private:
  T Data;	///< A data for each node.
  NodeType<T>* nLink;	///< A pointer to Next Node.

public:
  /**
  *	default constructor.
  */
  NodeType ():nLink(nullptr){}

  /**
  *	@brief	Get Pointer to Next Node.
  *	@pre	Pointer to Next Node should be initialized.
  *	@post	Get Pointer to Next Node.
  *	@return	Pointer to Next Node.
  */
  NodeType* GetnLink() const { return this->nLink; }

  /**
	*	@brief	Set Pointer to Next Node.
	*	@pre	none.
	*	@post	Pointer to Next Node is set.
	*	@param	next_link set nLink.
	*/
  void SetnLink(NodeType<T> *next_link) { this->nLink = next_link; }

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

#endif /* _NODETYPE_HPP */
