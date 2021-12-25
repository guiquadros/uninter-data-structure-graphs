#include <stdio.h>
#include <stdlib.h>

struct neighbor_node
{
	int vertex;
	struct neighbor_node *next;
};

struct graph
{
	int total_vertex;
	struct neighbor_node **list_of_neighbors; // vector of the size of total_vertex
};

int main()
{
	printf("hello graph!\n");
	system("pause");
	return 0;
}
