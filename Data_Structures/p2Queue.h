// ----------------------------------------------------
// FIFO implementation with single linked list  -------
// ----------------------------------------------------

#ifndef __p2Queue_H__
#define __p2Queue_H__

#include "p2Defs.h"
#include "p2SList.h"

/**
* Queue using a single linked list
*/
template<class TYPE>
class p2Queue
{
public:

	/**
	* Get Size
	*/
	unsigned int size() const
	{
		return list.size();
	}

	/**
	* push new item
	*/
	void push(const TYPE& item)
	{
		list.push_back(item);
	}

	/**
	* Deletes an item from the list
	*/
	bool pop(TYPE& item)
	{
		return list.pop_front(item);
	}

	/**
	* Reads the next value to pop
	*/
	const TYPE* peek() const
	{
		return list.front();
	}

	/**
	* Destroy and free all mem
	*/
	void clear()
	{
		list.clear();
	}

	/**
	* Check if it is empty
	*/
	bool empty()
	{
		return list.empty();
	}

private:
	p2SList<TYPE> list;

};
#endif /*__p2Queue_H__*/