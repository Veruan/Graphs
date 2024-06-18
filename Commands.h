#ifndef COMMANDS_H
#define COMMANDS_H


#include "Graph.h"
#include "VertexInfo.h"

int get_dec();

void quick_sort(int* A, int l, int r);
int partition(int l, int r, int* A);

void DFS(const Graph* graph, int current_vertex, bool* visited);

void DFS_sides(const Graph* graph, int current_vertex, bool *visited, char* sides, char previous_side, bool* bipartiness);
char get_opposite(char previous_side);

void color_vertex_greedy(const Graph* graph, int current_vertex, int* used, int* colors, int used_size);
void reset_arr(int* arr, int size);

void merge_sort(vertex_info_t* arr, int left, int right);
void merge(vertex_info_t* arr, int left, int mid, int right);

#endif