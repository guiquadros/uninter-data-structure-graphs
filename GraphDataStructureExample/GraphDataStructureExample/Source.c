#include <stdio.h>
#include <stdlib.h>

struct neighbor_node
{
	int vertex;
	struct neighbor_node *next;
};

struct graph
{
	int total_vertexes;
	struct neighbor_node **adjacency_lists; // list (with the size of total_vertexes) of Adjacency List (each Adjacency List represents the neighbors of each vertex)
};

struct graph* create_graph(int total_vertexes);
void add_edge(struct graph* graph, int origin, int destiny);
void show_graph_adjacency_lists(struct graph* graph);

int main()
{
	struct graph* test_graph = create_graph(6);

	// vertex 0
	add_edge(test_graph, 0, 1);
	add_edge(test_graph, 0, 2);

	// vertex 1
	//add_edge(test_graph, 1, 0); // --> no need since we always create the link on both sides, already added with: add_edge(test_graph, 0, 1); 
	add_edge(test_graph, 1, 3);

	// vertex 2
	//add_edge(test_graph, 2, 0); // --> no need since we always create the link on both sides, already added with: add_edge(test_graph, 0, 2);
	add_edge(test_graph, 2, 3);

	// vertex 3
	//add_edge(test_graph, 3, 1); // --> no need since we always create the link on both sides, already added with: add_edge(test_graph, 1, 3);
	//add_edge(test_graph, 3, 2); // --> no need since we always create the link on both sides, already added with: add_edge(test_graph, 2, 3);
	add_edge(test_graph, 3, 4);
	add_edge(test_graph, 3, 5);

	// vertex 4
	//add_edge(test_graph, 4, 3); // --> no need since we always create the link on both sides, already added with: add_edge(test_graph, 3, 4);

	// vertex 5
	//add_edge(test_graph, 5, 3); // --> no need since we always create the link on both sides, already added with: add_edge(test_graph, 3, 5);

	show_graph_adjacency_lists(test_graph);

	system("pause");
	return 0;
}

struct graph* create_graph(const int total_vertexes)
{
	struct graph *new_graph = (struct graph*)malloc(sizeof(struct graph));
	new_graph->total_vertexes = total_vertexes;
	new_graph->adjacency_lists = (struct neighbor_node**)malloc(total_vertexes * sizeof(struct neighbor_node *));

	for (int i = 0; i < total_vertexes; ++i)
	{
		new_graph->adjacency_lists[i] = NULL;
	}

	return new_graph;
}

void add_edge(struct graph* graph, int origin, int destiny)
{
	// create the edge link from the origin vertex to the destiny vertex
	struct neighbor_node* neighbor = (struct neighbor_node*)malloc(sizeof(struct neighbor_node));
	neighbor->vertex = destiny;
	neighbor->next = graph->adjacency_lists[origin]; 
	graph->adjacency_lists[origin] = neighbor;

	// create the edge link from the destiny vertex to the origin vertex
	neighbor = (struct neighbor_node*)malloc(sizeof(struct  neighbor_node));
	neighbor->vertex = origin;
	neighbor->next = graph->adjacency_lists[destiny];
	graph->adjacency_lists[destiny] = neighbor;
}

void show_graph_adjacency_lists(struct graph* graph)
{
	for (int i = 0; i < graph->total_vertexes; ++i)
	{
		printf("#%d vertex adjacency list (neighbors):\n", i);

		struct neighbor_node *neighbor = graph->adjacency_lists[i];

		while (neighbor != NULL)
		{
			printf("%d --> ", neighbor->vertex);
			neighbor = neighbor->next;
		}

		printf("\n\n");
	}
}
