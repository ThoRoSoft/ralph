#include "graph.h"

#include <stdio.h>
#include <stdlib.h>

Graph graph_create(size_t vertex_count, size_t edge_count) {
	Graph graph = {0};

	graph.vertex_count = vertex_count;
	graph.edge_count = edge_count;

	graph.vertices = calloc(vertex_count, sizeof(*graph.vertices));
	graph.edges = calloc(edge_count, sizeof(*graph.edges));

	if ((vertex_count > 0 && graph.vertices == NULL) ||
	    (edge_count > 0 && graph.edges == NULL)) {
		fprintf(stderr, "failed to alloc graph\n");
		free(graph.vertices);
		free(graph.edges);
		exit(EXIT_FAILURE);
	}

	return graph;
}

void graph_destroy(Graph *graph) {
	free(graph->vertices);
	free(graph->edges);

	*graph = (Graph){0};
}

static size_t grid_index(size_t column, size_t row, size_t columns) {
	return row * columns + column;
}

Graph graph_make_grid(size_t columns, size_t rows, float spacing,
		      Vector2 origin) {
	const size_t vertex_count = columns * rows;
	/* (cols-1)*rows horizontals + cols*(rows-1) verticals */
	const size_t horizontal_edges = columns > 0 ? (columns - 1) * rows : 0;
	const size_t vertical_edges = rows > 0 ? columns * (rows - 1) : 0;

	Graph graph =
	    graph_create(vertex_count, horizontal_edges + vertical_edges);

	for (size_t row = 0; row < rows; ++row) {
		for (size_t column = 0; column < columns; ++column) {
			size_t i = grid_index(column, row, columns);

			graph.vertices[i].position =
			    (Vector2){origin.x + (float)column * spacing,
				      origin.y + (float)row * spacing};
		}
	}

	size_t edge = 0;

	for (size_t row = 0; row < rows; ++row) {
		for (size_t column = 0; column < columns; ++column) {
			size_t here = grid_index(column, row, columns);

			if (column + 1 < columns) {
				graph.edges[edge++] = (Edge){
				    .a = here,
				    .b = grid_index(column + 1, row, columns)};
			}

			if (row + 1 < rows) {
				graph.edges[edge++] = (Edge){
				    .a = here,
				    .b = grid_index(column, row + 1, columns)};
			}
		}
	}

	return graph;
}

Graph graph_make_example(void) {
	Graph graph = graph_create(7, 8);

	graph.vertices[0].position = (Vector2){400, 120};
	graph.vertices[1].position = (Vector2){250, 220};
	graph.vertices[2].position = (Vector2){400, 220};
	graph.vertices[3].position = (Vector2){550, 220};
	graph.vertices[4].position = (Vector2){300, 370};
	graph.vertices[5].position = (Vector2){500, 370};
	graph.vertices[6].position = (Vector2){400, 480};

	graph.edges[0] = (Edge){0, 1};
	graph.edges[1] = (Edge){0, 2};
	graph.edges[2] = (Edge){0, 3};
	graph.edges[3] = (Edge){1, 4};
	graph.edges[4] = (Edge){2, 4};
	graph.edges[5] = (Edge){2, 5};
	graph.edges[6] = (Edge){3, 5};
	graph.edges[7] = (Edge){4, 6};

	return graph;
}
