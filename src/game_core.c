#include "../dependencies/game.h"
/**
 * initializeGame - Responsible for initializing the game structure and
 * variables
 * @argc: Number of command-line arguments
 * @argv: Array of command-line argument strings
 * @game: Pointer to the game structure
 * @textured: Pointer to the textured flag
 *
 * Return: Returns 0 on success, non-zero on failure
 */
int initializeGame(int argc, char *argv[], Game *game, bool *textured)
{
	/* Responsible for initializing the game structure */
	memset(game, 0, sizeof(Game)); /*Initialize all members of 'game' to 0*/

	/* Initial values for game struct */
	game->spot.x = 1;
	game->spot.y = 12;
	game->direction.x = 1;
	game->direction.y = -0.66;
	game->viewPlane.x = 0;
	game->viewPlane.y = 0.66;
	game->time = 0;
	game->quit = false;

	/* Default map name and textured flag */
	game->design = "visuals/maps/design_1";
	*textured = true;

	/* Handle command-line arguments */
	if (argc == 2)
	{
		/* Responsible for checking command-line argument for texture option */
		if (strcmp(argv[1], "no_tex") == 0)
		{
			*textured = false; /* Disable textures if "no_tex" argument is provided */
		}
		else
		{
			game->design = argv[1]; /* Use provided map name from command line */
		}
	}

	/* Responsible for starting SDL and creating window and renderer */
	if (!initializeGameSDL(game))
	{
		return (true);
	}

	return (false);
}

/**
 * runGameLoop - Responsible for running the main game loop
 * @game: Pointer to the game structure
 * @textured: Textured flag
 *
 * Return: Returns 0 on success, non-zero on failure
 */
int runGameLoop(Game *game, bool textured)
{
	/* Responsible for the main game loop */
	while (!game->quit)
	{
		/* Responsible for drawing ceiling and floor if not using textures */
		if (!textured)
		{
			drawCeilingAndFloor(game);
		}

		/* Responsible for updating player orientation and rendering scene */
		updatePlayerOrientation(game, game->puzzle, textured);

		/* Responsible for handling player movement based on user input */
		handlePlayerMovement(game, game->puzzle);

		/* Responsible for checking if user wants to quit the game */
		if (exit_maze(game))
		{
			game->quit = true;
		}
	}

	return (false);
}

/**
 * main - Main entry point responsible for running the maze game
 * Handles initialization, game loop, and cleanup
 * @argc: Number of command-line arguments
 * @argv: Array of command-line argument strings
 *
 * Return: Returns 0 on success, non-zero on failure
 */
int main(int argc, char *argv[])
{
	Game game;
	bool textured;

	if (initializeGame(argc, argv, &game, &textured))
		return (true);
	/* Responsible for allocating memory for the maze */
	game.puzzle = malloc(MAP_WIDTH * MAP_HEIGHT * sizeof(int));
	if (game.puzzle == NULL)
	{
		fprintf(stderr, "Failed to allocate memory for maze.\n");
		cleanUpSDL(&game);
		return (true);
	}
	/* Responsible for parsing the maze file and loading into game.puzzle */
	game.puzzle = loadMapFromFile(game.design, &game.puzzle);
	if (game.puzzle == NULL)
	{
		fprintf(stderr, "Failed to parse map.\n");
		cleanUpSDL(&game); /* Clean up initialized SDL components */
		free(game.puzzle);
		return (1); /* Exit with error if map parsing fails */
	}
	/* Responsible for loading textures if textured flag is true */
	if (textured)
		haulMapTextures(&game, game.design);
	if (runGameLoop(&game, textured))
		return (true);
	/* Responsible for cleaning up SDL, renderer, and window */
	cleanUpSDL(&game);
	free(game.puzzle);
	return (false);
}

