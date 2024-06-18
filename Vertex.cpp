#define _CRT_SECURE_NO_WARNINGS

#include "Vertex.h"

Vertex::Vertex(int neighbor_count) : neighbor_count(neighbor_count)
{
	this->neighbors = (int*)(malloc(neighbor_count * sizeof(int)));
	if (this->neighbors == nullptr)
	{
		perror("Error - allocating memory for neighbors");
		exit(EXIT_FAILURE);
	}


	for (int i = 0; i < neighbor_count; i++)
	{
		int not_scanned_args = scanf("%d", &(this->neighbors[i]));
		if (not_scanned_args != 1)
			exit(EXIT_FAILURE);
	}
}


Vertex::~Vertex()
{
	free(this->neighbors);
}


int Vertex::size() const
{
	return this->neighbor_count;
}


int Vertex::get_neighbor(int index) const
{
	return this->neighbors[index];
}