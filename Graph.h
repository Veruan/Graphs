#ifndef GRAPH_H
#define GRAPH_H

#include "Vertex.h"

enum sides
{
    LEFT = 'l',
    RIGHT = 'r'
};


class Graph
{
    private:

        const long long order;
        long long complete_graph_edges;
        Vertex** vertices;
        long long edge_count;
        long long max_deg;

    public:

        Graph(long long order);

        ~Graph();

        long long size() const;

        Vertex* operator [](size_t index) const;

        void gradual_sequence() const;

        void components_of_cohesion() const;

        void bipartiness() const;

        void greedy_coloring() const;

        void greedy_coloring_LF() const;

        void edges_to_full() const;
};

#endif