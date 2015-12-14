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

		bool CanReach(const vertice* dst, p2DynArray<const vertice*>& visited) const
		{
			// Are we the destination ?
			if(this == dst)
				return true;

			// Add ourselves as a visited node so we never come back here
			visited.push_back(this);

			// Recursively call all our links that have not been visited
			for(const p2List<vertice*>::node* item = links.front_node(); item; item = item->next())
			{
				if(visited.find(item->data) == visited.size())
				{
					if(item->data->CanReach(dst, visited) == true)
						return true;
				}
			}

			// We could not find destination in this branch
			return false;
		}
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

	bool is_reachable_iterative(const vertice* src, const vertice* dst) const
	{
		if(src == dst)
			return true;

		// Keep track of visited nodes
		p2DynArray<const vertice*> visited(size());

		// queue to organize node visiting
		p2Queue<const vertice*> queue;

		// Add first node as visited
		visited.push_back(src);
		
		// Add first node as the one to begin with
		queue.push(src);

		const vertice* current;
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

	bool is_reachable_recursive(const vertice* src, const vertice* dst) const
	{
		if(src == dst)
			return true;

		// Keep track of visited nodes
		p2DynArray<const vertice*> visited(size());

		// trigger the recursive function
		return src->CanReach(dst, visited);
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