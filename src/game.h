#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#include "graph.h"

/*
 * Ralph: Berlekamp switching on a graph.
 * state[i] is true when vertex i is on. Goal: all on.
 */
/* ralph: berlekamp switching on a graph
 * state[i] is true when vertex i is on, with the goal of turning on all lights
 */
typedef struct {
	Graph graph;
	bool *state;
} Game;

/* takes ownership of graph */
Game game_create(Graph graph);
void game_destroy(Game *game);

void game_toggle(Game *game, size_t vertex);

/* toggle vertex and every neighbor */
void game_activate_move(Game *game, size_t vertex);

/* true when every vertex is on */
bool game_is_solved(const Game *game);

/* hit-test; returns vertex index or -1 */
int game_vertex_at(const Game *game, Vector2 point, float radius);

void game_clear(Game *game);

/* reachable scramble: clear, then random legal moves */
void game_randomize(Game *game);

#endif
