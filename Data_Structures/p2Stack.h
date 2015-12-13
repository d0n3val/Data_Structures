// ----------------------------------------------------
// LIFO implementation as a dynamic array  ------------
// ----------------------------------------------------

#ifndef __p2Stack_H__
#define __p2Stack_H__

#include "p2Defs.h"

/**
* Stack using a dynamic array
*/
template<class TYPE>
class p2Stack
{
public:

	unsigned int size() const
	{
		return data.size();
	}

	// Data Management
	void push(const TYPE& element)
	{
		data.push_back(element);
	}

	bool pop(TYPE& result)
	{
		return data.pop_back(result);
	}

	const TYPE* peek() const
	{
		return data.back();
	}

	void clear()
	{
		data.clear();
	}

	bool empty() const
	{
		return data.empty();
	}



private:

	p2DynArray<TYPE> data;
};

#endif // __p2Stack_H__