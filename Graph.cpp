#define _CRT_SECURE_NO_WARNINGS

#include "Graph.h"
#include "VertexInfo.h"
#include "Commands.h"

Graph::Graph(long long order) : order(order), complete_graph_edges((order* (order - 1)) / 2), edge_count(0), max_deg(0)
{
    this->vertices = (Vertex**)(malloc((size_t)order * sizeof(Vertex*)));
    if (this->vertices == nullptr)
    {
        perror("Error - allocating memory for vertices");
        exit(EXIT_FAILURE);
    }


    for (int i = 0; i < order; i++)
    {
        int neighbor_count;
        int not_scanned_args = scanf("%d", &neighbor_count);
        if (not_scanned_args != 1)
            exit(EXIT_FAILURE);

        this->vertices[i] = new Vertex(neighbor_count);
        this->edge_count += neighbor_count;
        this->max_deg = (neighbor_count > max_deg) ? neighbor_count : max_deg;
    }

    this->edge_count /= 2;
}


Graph::~Graph()
{
    for (long long i = 0; i < this->order; i++)
        delete this->vertices[i];

    free(this->vertices);
}


long long Graph::size() const
{
    return this->order;
}


Vertex* Graph::operator [](size_t index) const
{
    return this->vertices[index];
}


void Graph::gradual_sequence() const
{
    int* vertices_deg = (int*)malloc((size_t)this->order * sizeof(int));
    if (vertices_deg == nullptr)
    {
        perror("Error - allocating memory for vertices");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < this->order; i++)
        vertices_deg[i] = (*this)[i]->size();

    quick_sort(vertices_deg, 0, (int)this->order - 1);

    for (int i = 0; i < this->order; i++)
        printf("%d ", vertices_deg[this->order - 1 - i]);

    free(vertices_deg);

    printf("\n");
}


void Graph::components_of_cohesion() const
{
    int component_count = 0;

    bool* visited = (bool*)(malloc((size_t)this->order * sizeof(bool)));
    if (visited == nullptr)
    {
        perror("Error - allocating memory for visited - DFS");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < this->order; i++)
        visited[i] = false;

    for (int i = 0; i < this->order; i++) // long long i?
    {
        if (!visited[i])
        {
            DFS(this, i + 1, visited);
            component_count++;
        }
    }

    free(visited);

    printf("%d\n", component_count);
}



void Graph::bipartiness() const
{
    bool bipartiness = true;

    char* sides = (char*)(malloc((size_t)this->order * sizeof(char)));
    if (sides == nullptr)
    {
        perror("Error - allocating memory for sides - DFS");
        exit(EXIT_FAILURE);
    }

    bool* visited = (bool*)(malloc((size_t)this->order * sizeof(bool)));
    if (visited == nullptr)
    {
        perror("Error - allocating memory for visited - DFS");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < this->order; i++)
    {
        visited[i] = false;
        sides[i] = ' ';
    }

    for (int i = 0; i < this->order; i++)
    {
        if (!visited[i])//wywalone && sides[i] == ' '
        {
            DFS_sides(this, i + 1, visited, sides, RIGHT, &bipartiness);
        }
    }

    free(sides);
    free(visited);

    printf("%c\n", (bipartiness ? 'T' : 'F'));
}


void Graph::greedy_coloring() const
{
    int* colors = (int*)(malloc((size_t)this->order * sizeof(int)));
    if (colors == nullptr)
    {
        perror("Error - allocating memory for sides - DFS");
        exit(EXIT_FAILURE);
    }

    int* used = (int*)(malloc((size_t)(this->max_deg + 1) * sizeof(int)));//bo maksymalna liczba kolorów to maks stopieñ + 1
    if (used == nullptr)
    {
        perror("Error - allocating memory for used colors - DFS");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < this->order; i++)
        colors[i] = -1;

    colors[0] = 1;

    for (int i = 1; i < this->order; i++) // long long i?
    {
        reset_arr(used, int(this->max_deg + 1));
        color_vertex_greedy(this, i + 1, used, colors, int(this->max_deg + 1));
    }

    for (int i = 0; i < this->order; i++)
        printf("%d ", colors[i]);
    printf("\n");

    free(colors);
    free(used);
}


void Graph::greedy_coloring_LF() const
{
    int* colors = (int*)(malloc((size_t)this->order * sizeof(int)));
    if (colors == nullptr)
    {
        perror("Error - allocating memory for sides - DFS");
        exit(EXIT_FAILURE);
    }

    int* used = (int*)(malloc((size_t)(this->max_deg + 1) * sizeof(int)));//bo maksymalna liczba kolorów to maks stopieñ + 1
    if (used == nullptr)
    {
        perror("Error - allocating memory for used colors - DFS");
        exit(EXIT_FAILURE);
    }

    vertex_info_t* vertices_t = (vertex_info_t*)malloc((size_t)this->order * sizeof(vertex_info_t));//struktura trzymaj¹ca inta i wskaŸnik na inta - nr vertexa jaki ma
    if (vertices_t == nullptr)
    {
        perror("Error - allocating memory for vertices");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < this->order; i++)
    {
        colors[i] = -1;
        vertices_t[i].index = i + 1;
        vertices_t[i].degree = (*this)[i]->size();
    }

    merge_sort(vertices_t, 0, int(this->order - 1));

    for (int i = 0; i < this->order; i++) // long long i?
    {
        reset_arr(used, int(this->max_deg + 1));
        color_vertex_greedy(this, vertices_t[this->order - 1 - i].index, used, colors, int(this->max_deg + 1));
    }

    for (int i = 0; i < this->order; i++)
        printf("%d ", colors[i]);
    printf("\n");

    free(colors);
    free(used);
    free(vertices_t);
}


void Graph::edges_to_full() const
{
    printf("%lld\n", this->complete_graph_edges - this->edge_count);
}