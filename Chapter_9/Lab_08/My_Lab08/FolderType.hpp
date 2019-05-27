#ifndef _FOLDERTYPE_HPP
#define _FOLDERTYPE_HPP

#include <iostream>
#include <iomanip>


/**
*	Folder information class.
*/
class FolderType{
public:
	/**
	*	default constructor.
	*/
	FolderType(std::string inName="untitled")
	: fdName(inName){}

	/**
	*	destructor.
	*/
	~FolderType()	{  }


	/**
	*	@brief	Get Folder name.
	*	@pre	Folder name is set.
	*	@post	none.
	*	@return	Folder name.
	*/
	std::string GetName() const { return this->fdName; }



	/**
	*	@brief	Set Folder Name.
	*	@pre	none.
	*	@post	Folder Name is set.
	*	@param	inName	Folder Name.
	*/
	void SetName(std::string inName) { this->fdName=inName; };


	/**
	*	@brief	Display Folder Name on screen.
	*	@pre	Folder Name is set.
	*	@post	Folder Name is on screen.
	*/
	void DisplayNameOnScreen(){
		std::cout <<" Name : " << this->fdName;
	};

	/**
	*	@brief	Display Folder Info on screen.
	*	@pre	Folder Info is set.
	*	@post	Folder Info is on screen.
	*/
	void DisplayInfoOnScreen(){
		this->DisplayNameOnScreen();



	};

	/**
	*	@brief	Set Folder Name from keyboard.
	*	@pre	none.
	*	@post	Folder Name is set.
	*/
	void SetNameFromKB();


	//Operator overloading

	/**
	*	@brief	Comparing Folder name is same.
	*	@pre	none.
	*	@post	none.
	*	@param	another Folder type folder that you want to Compare.
	*	@return	return true if name is same, otherwise false.
	*/
	bool operator == (const FolderType &fd) const { return this->fdName==fd.fdName; }

	/**
	*	@brief	Comparing Folder name is different.
	*	@pre	none.
	*	@post	none.
	*	@param	another Folder type folder that you want to Compare.
	*	@return	return true if name is different, otherwise false.
	*/
	bool operator!=(const FolderType &fd) const { return this->fdName!=fd.fdName; }

	/**
	*	@brief	Comparing Folder name is smaller.
	*	@pre	none.
	*	@post	none.
	*	@param	another Folder type folder that you want to Compare.
	*	@return	return true if pre is smaller than post, otherwise false.
	*/
	bool operator<(const FolderType &fd) const { return this->fdName<fd.fdName; }

	/**
	*	@brief	Comparing Folder name is bigger.
	*	@pre	none.
	*	@post	none.
	*	@param	another Folder type folder that you want to Compare.
	*	@return	return true if pre is bigger than post, otherwise false.
	*/
	bool operator>(const FolderType &fd) const { return this->fdName>fd.fdName; }

    friend std::ostream & operator<<(std::ostream & os, const FolderType& fd) { return os<<fd.fdName ;}



	//Folder management


private:
	std::string fdName; // folder name


};

#endif	/* _FOLDERTYPE_HPP */
