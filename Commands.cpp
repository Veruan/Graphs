#include "Commands.h"
#include "VertexInfo.h"

int get_dec()
{
    int number = 0, tmp = getchar();

    number = tmp / 10;

    while (tmp != '\n' && tmp != ' ')
    {
        number *= 10;
        number += tmp;

        tmp = getchar();
    }

    return 0;
}


int partition(int l, int r, int* A)
{
    int pivot = A[l];

    while (true)
    {
        while (A[l] < pivot)
            l = l + 1;

        while (A[r] > pivot)
            r = r - 1;

        if (l < r)
        {
            int tmp = A[r];
            A[r] = A[l];
            A[l] = tmp;
        }

        else
            return r;

        l++;
        r--;
    }
}


void quick_sort(int* A, int l, int r)
{
    if (l < r)
    {
        int q = partition(l, r, A);
        quick_sort(A, l, q);
        quick_sort(A, q + 1, r);
    }
}


void DFS(const Graph* graph, int current_vertex, bool* visited)
{
    if (visited[current_vertex - 1])//jesli odwiedzony wierzcho³ek skip
        return;

    visited[current_vertex - 1] = true;

    for (int i = 0; i < (*graph)[current_vertex - 1]->size(); i++)
        DFS(graph, (*graph)[current_vertex - 1]->get_neighbor(i), visited);
}


void DFS_sides(const Graph* graph, int current_vertex, bool *visited, char *sides, char previous_side, bool *bipartiness)
{
    if (!(*bipartiness) || (visited[current_vertex - 1] && sides[current_vertex - 1] != previous_side))
        return;

    if (sides[current_vertex - 1] == previous_side)
    {
        *bipartiness = false;
        return;
    }

    char this_side = get_opposite(previous_side);
    sides[current_vertex - 1] = this_side;

    visited[current_vertex - 1] = true;

    for (int i = 0; i < (*graph)[current_vertex - 1]->size(); i++)
        DFS_sides(graph, (*graph)[current_vertex - 1]->get_neighbor(i), visited, sides, this_side, bipartiness);
}


char get_opposite(char previous_side)
{
    switch (previous_side)
    {
        case RIGHT:
            return LEFT;

        case LEFT:
            return RIGHT;
    }

    return ' ';
}


void color_vertex_greedy(const Graph* graph, int current_vertex, int* used, int* colors, int used_size)
{
    int color = -1;

    for (int i = 0; i < (*graph)[current_vertex - 1]->size(); i++)
    {
        int neighbor_color = colors[(*graph)[current_vertex - 1]->get_neighbor(i) - 1];
        if (neighbor_color != -1)
            used[neighbor_color - 1]++;
    }

    for (int i = 0; i < used_size; i++)
    {
        if (used[i] == 0)
        {
            color = i + 1;
            break;
        }
    }

    color = (color == -1) ? used_size : color;

    colors[current_vertex - 1] = color;
}


void reset_arr(int* arr, int size)
{
    for (int i = 0; i < size; i++)
        arr[i] = 0;
}


void merge_sort(vertex_info_t* arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}


void merge(vertex_info_t* arr, int left, int mid, int right) 
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vertex_info_t* L = (vertex_info_t*)malloc(n1 * sizeof(vertex_info_t));
    vertex_info_t* R = (vertex_info_t*)malloc(n2 * sizeof(vertex_info_t));

    if (L == nullptr || R == nullptr)
    {
        perror("Error - allocating memory for LR arrays");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) 
    {
        if (L[i].degree < R[j].degree) //jeœli równe zamieñ to weŸ t¹ z prawej a nie z lewej bo potem do odczytu jest od koñca ((a)stabilny algorytm sortowania xD)
        {
            arr[k] = L[i];
            i++;
        }

        else 
        {
            arr[k] = R[j];
            j++;
        }

        k++;
    }

    while (i < n1) 
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) 
    {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}