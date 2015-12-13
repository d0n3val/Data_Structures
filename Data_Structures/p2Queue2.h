// ----------------------------------------------------
// FIFO implementation with single linked list  -------
// ----------------------------------------------------

#ifndef __p2Queue2_H__
#define __p2Queue2_H__

#include "p2Defs.h"
#include "p2DynArray.h"

/**
* Queue using a dynamic array and some tricks :)
*/
template<class VALUE>
class p2Queue2
{
public:

	/**
	* Get Size
	*/
	unsigned int size() const
	{
		return data.size() - left_index;
	}

	/**
	* push up front
	*/
	void push(const VALUE& item)
	{
		data.push_back(item);
	}

	/**
	* Pops last item
	*/
	bool pop(VALUE& item)
	{
		if(data.size() - left_index > 0)
		{
			item = data[left_index++];
			return true;
		}
		return false;
	}

	/**
	* Reads one of the values
	*/
	const VALUE* peek() const
	{
		if(data.size() - left_index > 0)
			return &data[left_index];
		return nullptr;
	}

	/**
	* Destroy and free all mem
	*/
	void clear()
	{
		data.clear();
	}

	/**
	* Destroy and free all mem
	*/
	bool empty()
	{
		return size() == 0;
	}

private:

	uint left_index = 0;
	p2DynArray<VALUE> data;
};
#endif /*__p2Queue2_H__*/