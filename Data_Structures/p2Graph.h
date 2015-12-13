// ----------------------------------------------------
// Graph implementation  ------------
// ----------------------------------------------------

#ifndef __p2Graph_H__
#define __p2Stack_H__

#include "p2Defs.h"

/**
* We will use a double linked list
*/
template<class TYPE>
class p2Graph
{
public:

	struct node
	{
		TYPE data;
		p2List<node*> links;

		node(const TYPE& data) : data(data)
		{}
	};

private:

	p2List<node*> nodes;

public:

	node* push_back(const TYPE& data)
	{
		node* new_node = new node(data);
		nodes.push_back(new_node);
		return new_node;
	}
	/*
	https://www.cs.bu.edu/teaching/c/graph/linked/
	*/

	bool is_reachable(node* src, node* dst)
	{
		bool ret = false;
		node* current = src;

		return ret;
	}

	unsigned int size() const
	{
		return nodes.size();
	}

	void clear()
	{
		const p2List<node*>::node* p = nodes.front_node();
		while(p != nullptr)
		{
			RELEASE(p->data);
			p = p->next();
		}
		nodes.clear();
	}

	bool empty() const
	{
		return nodes.empty();
	}
};

#endif // __p2Graph_H__