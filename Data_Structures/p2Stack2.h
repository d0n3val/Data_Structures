// ----------------------------------------------------
// LIFO implementation as a linked list (not optimal) -
// ----------------------------------------------------

#ifndef __p2Stack2_H__
#define __p2Stack2_H__

#include "p2Defs.h"
#include "p2SList.h"

/**
* Stack using a single linked list
*/
template<class VALUE>
class p2Stack2
{
public:

	uint size() const
	{
		return data.size();
	}

	void push(const VALUE& element)
	{
		data.push_back(element);
	}

	bool pop(VALUE& result)
	{
		return data.pop_back(result);
	}

	const VALUE* peek() const
	{
		return data.back();
	}

	void clear()
	{
		data.clear();
	}

	bool empty()
	{
		return data.empty();
	}

private:

	p2SList<VALUE> data;
};

#endif // __p2Stack2_H__