#ifndef VERTEX_H
#define VERTEX_H

#include <stdio.h>
#include <stdlib.h>

class Vertex
{
	private:

		int neighbor_count;
		int* neighbors;

	public:

		Vertex(int neighbor_count);

		~Vertex();

		int size() const;

		int get_neighbor(int index) const;
};

#endif