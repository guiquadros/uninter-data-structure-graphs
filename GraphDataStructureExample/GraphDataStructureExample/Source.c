#include <stdio.h>
#include <stdlib.h>

// total number of vertexes of the testing graph
#define NUMBER_OF_VERTEXES 6 

struct neighbor_node
{
	int vertex;
	struct neighbor_node *next;
};

struct graph
{
	int total_vertexes;

	// list (with the size of total_vertexes) of Adjacency List (each Adjacency List represents the neighbors of each vertex)
	struct neighbor_node **adjacency_lists;
};

struct dfs_stack_node
{
	int vertex;
	struct dfs_stack_node* next;
} *top = NULL;

struct graph* create_graph(int total_vertexes);
void add_edge(struct graph* graph, int origin, int destiny);
void show_graph_adjacency_lists(struct graph* graph);
void search_and_display_vertexes_with_dfs(struct graph* graph, int v, int visited_vertexes[]);
void push_dfs_stack(int vertex);
void pop_dfs_stack();

int main()
{
	// creates a graph with total_vertexes = NUMBER_OF_VERTEXES
	struct graph* test_graph = create_graph(NUMBER_OF_VERTEXES);

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

	// shows the whole graph with its adjacency lists
	show_graph_adjacency_lists(test_graph);

	// reads the target_vertex to start the DFS
	printf("\nInform a vertex to start the DFS (depth-first search) to display the whole graph visiting only one vertex at a time: ");
	int starting_vertex;
	scanf_s("%d", &starting_vertex);

	// stores the visited vertex during the search, 0 = not visited, 1 = visited. Default value = 0 for all positions.
	int visited_vertexes[NUMBER_OF_VERTEXES] = { 0 }; 

	// searches starting with the target_vertex in the graph using a DFS (depth-first search) algorithm ("busca em profundidade" in pt-br)
	//and display each vertex visited until it finishes the output of the whole graph
	search_and_display_vertexes_with_dfs(test_graph, starting_vertex, visited_vertexes);

	printf("\n\n");
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

void search_and_display_vertexes_with_dfs(struct graph* graph, int v, int visited_vertexes[])
{	
	// mark this vertex as visited
	visited_vertexes[v] = 1;
	printf("V%d\t", v);
	push_dfs_stack(v); // push the visited vertex in the dfs_stack

	// start looking into each element of the adjacency list of this vertex
	struct neighbor_node *neighbor = graph->adjacency_lists[v];

	while (neighbor != NULL)
	{
		const int neighbor_vertex = neighbor->vertex;

		// if the vertex of the neighbor was not visited yet we do a recursive call passing it as the target vertex (v)
		if (visited_vertexes[neighbor_vertex] != 1)
		{
			search_and_display_vertexes_with_dfs(graph, neighbor_vertex, visited_vertexes);
		}

		neighbor = neighbor->next;
	}

	// pop the stack, the search is done for the current vertex on top
	pop_dfs_stack();
}

void push_dfs_stack(int vertex)
{
	struct dfs_stack_node* new_dfs_stack_node = (struct dfs_stack_node*)malloc(sizeof(struct dfs_stack_node));
	new_dfs_stack_node->vertex = vertex;

	if (top == NULL)
	{
		// first element of the stack
		top = new_dfs_stack_node;
		top->next = NULL;
		return;
	}

	// stack already filled, add to the top and make it point to the "old top"
	new_dfs_stack_node->next = top;
	top = new_dfs_stack_node;
}

void pop_dfs_stack()
{
	// check if stack is empty
	if (top != NULL)
	{
		struct dfs_stack_node* element_to_pop = top;
		top = top->next;
		free(element_to_pop);
	}
}
