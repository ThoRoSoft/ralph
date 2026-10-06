#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Game game_create(Graph graph) {
	Game game = {.graph = graph, .state = NULL};

	game.state = calloc(graph.vertex_count, sizeof(*game.state));
	if (graph.vertex_count > 0 && game.state == NULL) {
		fprintf(stderr, "failed to alloc game state\n");
		graph_destroy(&game.graph);
		exit(EXIT_FAILURE);
	}

	return game;
}

void game_destroy(Game *game) {
	free(game->state);
	graph_destroy(&game->graph);

	*game = (Game){0};
}

void game_toggle(Game *game, size_t vertex) {
	if (vertex >= game->graph.vertex_count)
		return;

	game->state[vertex] = !game->state[vertex];
}

void game_activate_move(Game *game, size_t vertex) {
	const Graph *graph = &game->graph;

	if (vertex >= graph->vertex_count)
		return;

	game_toggle(game, vertex);

	/* flip every adjacent vertex (current rule is sigma+) */
	for (size_t i = 0; i < graph->edge_count; ++i) {
		Edge edge = graph->edges[i];

		if (edge.a == vertex)
			game_toggle(game, edge.b);
		else if (edge.b == vertex)
			game_toggle(game, edge.a);
	}
}

bool game_is_solved(const Game *game) {
	for (size_t i = 0; i < game->graph.vertex_count; ++i) {
		if (!game->state[i])
			return false;
	}

	return true;
}

int game_vertex_at(const Game *game, Vector2 point, float radius) {
	const Graph *graph = &game->graph;
	const float radius_squared = radius * radius;

	for (size_t i = 0; i < graph->vertex_count; ++i) {
		Vector2 p = graph->vertices[i].position;

		float dx = point.x - p.x;
		float dy = point.y - p.y;

		if (dx * dx + dy * dy <= radius_squared)
			return (int)i;
	}

	return -1;
}

void game_clear(Game *game) {
	memset(game->state, 0, game->graph.vertex_count * sizeof(*game->state));
}

void game_randomize(Game *game) {
	/* legal moves only, so the scramble stays solvable */
	game_clear(game);

	for (size_t i = 0; i < game->graph.vertex_count; ++i) {
		if (GetRandomValue(0, 1))
			game_activate_move(game, i);
	}
}
