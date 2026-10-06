#include "game.h"
#include "render.h"

int main(void) {
	const int screen_width = 800;
	const int screen_height = 600;
	const float vertex_radius = 22.0f;

	InitWindow(screen_width, screen_height, "ralph");
	SetTargetFPS(60);

	/* blank 4x3 grid (all off) */
	Game game = game_create(
	    graph_make_grid(4, 3, 80.0f, (Vector2){280.0f, 180.0f}));

	while (!WindowShouldClose()) {
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			int vertex = game_vertex_at(&game, GetMousePosition(),
						    vertex_radius);

			if (vertex >= 0)
				game_activate_move(&game, (size_t)vertex);
		}

		if (IsKeyPressed(KEY_R))
			game_randomize(&game);

		if (IsKeyPressed(KEY_C))
			game_clear(&game);

		BeginDrawing();

		ClearBackground((Color){24, 24, 24, 255});

		game_draw(&game, vertex_radius);

		DrawText("click a vertex to toggle it and its neighbors", 20,
			 20, 20, LIGHTGRAY);

		DrawText("r: randomize    c: clear", 20, 48, 18, GRAY);

		if (game_is_solved(&game))
			DrawText("solved", 20, screen_height - 50, 30, GREEN);

		EndDrawing();
	}

	game_destroy(&game);
	CloseWindow();

	return 0;
}
