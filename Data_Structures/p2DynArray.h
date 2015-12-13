// ----------------------------------------------------
// Array that resizes dynamically   -------------------
// ----------------------------------------------------

#ifndef __P2DYNARRAY_H__
#define __P2DYNARRAY_H__

#include "p2Defs.h"
#include <assert.h>

#define DYN_ARRAY_BLOCK_SIZE 16

template<class TYPE>
class p2DynArray
{
private:

	TYPE* data = nullptr;
	unsigned int	mem_capacity = 0;
	unsigned int	num_elements = 0;

public:

	// Constructors ------------------------------------------------------
	p2DynArray()
	{
		Alloc(DYN_ARRAY_BLOCK_SIZE);
	}

	p2DynArray(uint capacity)
	{
		Alloc(capacity);
	}

	// Destructor ---------------------------------------------------------
	~p2DynArray()
	{
		RELEASE_ARRAY(data);
	}

	// Operators ----------------------------------------------------------
	TYPE& operator[](uint index)
	{
		assert(index < num_elements);
		return data[index];
	}

	const TYPE& operator[](uint index) const
	{
		assert(index < num_elements);
		return data[index];
	}

	const p2DynArray<TYPE>& operator+= (const p2DynArray<TYPE>& array)
	{
		if(num_elements + array.num_elements > mem_capacity)
			Alloc(num_elements + array.num_elements);

		for(uint i = 0; i < array.num_elements; ++i)
			data[num_elements++] = array.data[i];

		return(*this);
	}

	// Data Management -----------------------------------------------------
	void push_back(const TYPE& element)
	{
		if(num_elements >= mem_capacity)
		{
			Alloc(mem_capacity + DYN_ARRAY_BLOCK_SIZE);
		}

		data[num_elements++] = element;
	}

	bool pop_back(TYPE& result)
	{
		if(num_elements > 0)
		{
			result = data[--num_elements];
			return true;
		}
		return false;
	}

	void clear()
	{
		num_elements = 0;
	}

	bool erase(uint index)
	{
		if(index < num_elements)
		{
			for(uint i = index; i < num_elements - 1; ++i)
			{
				data[i] = data[i + 1];
			}
			--num_elements;
			
			return true;
		}
		return false;
	}

	bool insert(const TYPE& element, uint position)
	{
		if(position > num_elements)
			return false;

		if(position == num_elements)
		{
			push_back(element);
			return true;
		}

		if(num_elements + 1 > mem_capacity)
			Alloc(mem_capacity + DYN_ARRAY_BLOCK_SIZE); // potential optimization if we do the Alloc manually

		for(uint i = num_elements; i > position; --i)
		{
			data[i] = data[i - 1];
		}

		data[position] = element;
		++num_elements;

		return true;
	}

	bool insert(const p2DynArray<TYPE>& array, uint position)
	{
		if(position > num_elements)
			return false;

		if(num_elements + array.num_elements > mem_capacity)
			Alloc(num_elements + array.num_elements + DYN_ARRAY_BLOCK_SIZE);

		for(uint i = position; i < position + array.num_elements; ++i)
		{
			data[i + array.num_elements] = data[i];
			data[i] = array[i - position];
			++num_elements;
		}

		return true;
	}

	TYPE* at(uint index)
	{
		if(index < num_elements)
			return &data[index];
		
		return nullptr;
	}

	const TYPE* at(uint index) const
	{
		if(index < num_elements)
			return &data[index];

		return nullptr;
	}

	void flip()
	{
		TYPE* start = &data[0];
		TYPE* end = &data[num_elements - 1];

		while(start < end)
			SWAP(*start++, *end--);
	}

	void shrink_to_fit()
	{
		if(num_elements < capacity)
		{
			Alloc(num_elements);
		}
	}

	uint find(const TYPE& value)
	{
		uint i = 0;
		for(; i < num_elements; ++i)
		{
			if(data[i] == value)
				break;
		}
		return i;
	}

	// Utils ------------------------------------------------------------
	uint capacity() const
	{
		return mem_capacity;
	}

	uint size() const
	{
		return num_elements;
	}

	bool empty() const
	{
		return num_elements == 0;
	}

	TYPE* front()
	{
		if(num_elements > 0)
			return &(data[0]);
		return nullptr;
	}

	const TYPE* front() const
	{
		if(num_elements > 0)
			return &(data[0]);
		return nullptr;
	}

	TYPE* back()
	{
		if(num_elements > 0)
			return &data[num_elements-1];
		return nullptr;
	}

	const TYPE* back() const
	{
		if(num_elements > 0)
			return &data[num_elements - 1];
		return nullptr;
	}

	// Sort -------------------------------------------------------------
	int BubbleSort()
	{
		int ret = 0;
		bool swapped = true;

		while(swapped)
		{
			swapped = false;
			for(unsigned int i = 0; i < num_elements - 2; ++i)
			{
				++ret;
				if(data[i] > data[i + 1])
				{
					SWAP(data[i], data[i + 1]);
					swapped = true;
				}
			}
		}

		return ret;
	}

	int BubbleSortOptimized()
	{
		int ret = 0;
		unsigned int count;
		unsigned int last = num_elements - 2;

		while(last > 0)
		{
			count = last;
			last = 0;
			for(unsigned int i = 0; i < count; ++i)
			{
				++ret;
				if(data[i] > data[i + 1])
				{
					SWAP(data[i], data[i + 1]);
					last = i;
				}
			}
		}
		return ret;
	}

	int CombSort()
	{
		int ret = 0;
		bool swapped = true;
		int gap = num_elements - 1;
		float shrink = 1.3f;

		while(swapped || gap > 1)
		{
			gap = MAX(1, gap / shrink);

			swapped = false;
			for(unsigned int i = 0; i + gap < num_elements - 1; ++i)
			{
				++ret;
				if(data[i] > data[i + gap])
				{
					SWAP(data[i], data[i + gap]);
					swapped = true;
				}
			}
		}

		return ret;
	}

private:

	// Allocates a new size and copies all data
	void Alloc(unsigned int mem)
	{
		TYPE* tmp = data;
		data = new TYPE[mem];

		mem_capacity = mem;
		num_elements = MIN(mem_capacity, num_elements);

		for(uint i = 0; i < num_elements; ++i)
			data[i] = tmp[i];

		RELEASE_ARRAY(tmp);
	}
};

#endif // __P2DYNARRAY_H__