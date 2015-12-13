// ----------------------------------------------------
// Graph implementation  ------------
// ----------------------------------------------------

#ifndef __p2Graph_H__
#define __p2Stack_H__

#include "p2Defs.h"
#include "p2List.h"
#include "p2DynArray.h"
#include "p2Queue.h"

/**
* We will use a double linked list
*/
template<class TYPE>
class p2Graph
{
public:

	struct vertice
	{
		TYPE data;
		p2List<vertice*> links;

		vertice(const TYPE& data) : data(data)
		{}
	};

private:

	p2List<vertice*> vertices;

public:

	vertice* push_back(const TYPE& data)
	{
		vertice* new_vertice = new vertice(data);
		vertices.push_back(new_vertice);
		return new_vertice;
	}

	bool is_reachable(vertice* src, vertice* dst) const
	{
		if(src == dst)
			return true;

		// Keep track of visited nodes
		p2DynArray<vertice*> visited(size());

		// queue to organize node visiting
		p2Queue<vertice*> queue;

		// Add first node as visited
		visited.push_back(src);
		
		// Add first node as the one to begin with
		queue.push(src);

		vertice* current;
		while(queue.pop(current) == true)
		{
			// Iterate all links
			const p2List<vertice*>::node* item = current->links.front_node();
			for(; item != nullptr; item = item->next())
			{
				// If we found destination, we are finish
				if(item->data == dst)
					return true;

				// Check if is already visited
				if(visited.find(item->data) == visited.size())
				{
					// If not mark is as visited and add it to the queue
					visited.push_back(item->data);
					queue.push(item->data);
				}
			}
		}

		return false;
	}

	unsigned int size() const
	{
		return vertices.size();
	}

	void clear()
	{
		const p2List<vertice*>::node* p = vertices.front_node();
		while(p != nullptr)
		{
			RELEASE(p->data);
			p = p->next();
		}
		vertices.clear();
	}

	bool empty() const
	{
		return vertices.empty();
	}
};

#endif // __p2Graph_H__