#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <cstdlib>

#include "Graph.h"
#include "Commands.h"

void handle_input(unsigned int* graph_count, Graph*** graphs);
void delete_graphs(unsigned int graph_count, Graph*** graphs);
void handle_info(unsigned int graph_count, Graph** graphs);


int main(void)
{
    unsigned int graph_count = 0;
    Graph** graphs = nullptr;

    handle_input(&graph_count, &graphs);
    handle_info(graph_count, graphs);
    delete_graphs(graph_count, &graphs);

    return 0;
}


void handle_input(unsigned int* graph_count, Graph*** graphs)
{
    long long graph_order = 0;

    int not_scanned_args = scanf("%u", graph_count);
    if (not_scanned_args != 1)
        exit(EXIT_FAILURE);

    *graphs = new Graph* [*graph_count];
    if (*graphs == nullptr)
    {
        perror("Error - error allocating memory for graphs");
        exit(EXIT_FAILURE);
    }

    for (unsigned int i = 0; i < *graph_count; i++)
    {
        not_scanned_args = scanf("%lld", &graph_order);
        if (not_scanned_args != 1)
            exit(EXIT_FAILURE);

        (*graphs)[i] = new Graph(graph_order);
    }
}


void delete_graphs(unsigned int graph_count, Graph*** graphs)
{
    for (unsigned int i = 0; i < graph_count; i++)
    {
        delete (*graphs)[i];
    }

    delete[] * graphs;
    *graphs = nullptr;
}



void handle_info(unsigned int graph_count, Graph** graphs)
{
    for (unsigned int i = 0; i < graph_count; i++)
    {
        graphs[i]->gradual_sequence();
        graphs[i]->components_of_cohesion();
        graphs[i]->bipartiness();
        printf("?\n");
        printf("?\n");
        graphs[i]->greedy_coloring();
        graphs[i]->greedy_coloring_LF();
        printf("?\n");
        printf("?\n");
        graphs[i]->edges_to_full();
    }
}