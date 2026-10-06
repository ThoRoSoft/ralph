#ifndef GRAPH_H
#define GRAPH_H

#include <stddef.h>

#include <raylib.h>

/* undirected edge between vertex indices a and b */
typedef struct {
	size_t a;
	size_t b;
} Edge;

/* screen position only */
typedef struct {
	Vector2 position;
} Vertex;

/* topology plus layout */
typedef struct {
	Vertex *vertices;
	Edge *edges;

	size_t vertex_count;
	size_t edge_count;
} Graph;

/* allocates vertices/edges */
Graph graph_create(size_t vertex_count, size_t edge_count);
void graph_destroy(Graph *graph);

/* orthogonal grid with unit spacing, origin at top-left vertex */
Graph graph_make_grid(size_t columns, size_t rows, float spacing,
		      Vector2 origin);

/* fixed irregular graph for manual testing */
Graph graph_make_example(void);

#endif
