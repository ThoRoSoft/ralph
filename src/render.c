#include "render.h"

void game_draw(const Game *game, float radius) {
	const Graph *graph = &game->graph;

	for (size_t i = 0; i < graph->edge_count; ++i) {
		Edge edge = graph->edges[i];

		Vector2 a = graph->vertices[edge.a].position;
		Vector2 b = graph->vertices[edge.b].position;

		DrawLineEx(a, b, 3.0f, GRAY);
	}

	for (size_t i = 0; i < graph->vertex_count; ++i) {
		Vector2 position = graph->vertices[i].position;
		Color fill = game->state[i] ? RAYWHITE : DARKGRAY;

		DrawCircleV(position, radius, fill);
		DrawCircleLines((int)position.x, (int)position.y, radius,
				LIGHTGRAY);
	}
}
