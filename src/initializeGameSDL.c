#include "../dependencies/game.h"

/**
 * createWindow - Responsible for creating an SDL window
 * @game: Represents a pointer to the Game structure
 * Return: True if successful, otherwise False
 */
bool createWindow(Game *game)
{
	game->win = SDL_CreateWindow("Maze", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
			SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (game->win == NULL)
	{
		fprintf(stderr, "Window could not be created! SDL_Error: %s\n",
				SDL_GetError());
		return (false);
	}
	return (true);
}

/**
 * createRenderer - Creates an SDL renderer
 * @game: Pointer to the Game structure
 * Return: True if successful, otherwise False
 */
bool createRenderer(Game *game)
{
	game->ren = SDL_CreateRenderer(game->win, -1, SDL_RENDERER_ACCELERATED);
	if (game->ren == NULL)
	{
		fprintf(stderr, "Renderer could not be created! SDL Error: %s\n",
				SDL_GetError());
		return (false);
	}
	return (true);
}

/**
 * createTexture - Creates an SDL texture
 * @game: Pointer to the Game structure
 * Return: True if successful, otherwise False
 */
bool createTexture(Game *game)
{
	game->texture = SDL_CreateTexture(game->ren,
			SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING,
			SCREEN_WIDTH, SCREEN_HEIGHT);
	if (game->texture == NULL)
	{
		fprintf(stderr, "Texture could not be initialized! SDL Error: %s\n",
				SDL_GetError());
		return (false);
	}
	return (true);
}

/**
 * initializeGameSDL - Initializes SDL and creates window, renderer,
 * and texture
 * @game: Pointer to the Game structure
 * Return: True if initialization is successful, otherwise False
 */
bool initializeGameSDL(Game *game)
{
	bool success = true;

	game->win = NULL, game->ren = NULL, game->texture = NULL,
	game->puzzle = NULL;

	if (!game)
		return (false);
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n",
				SDL_GetError());
		success = false;
	}
	if (success && !createWindow(game))
		success = false;
	if (success && !createRenderer(game))
		success = false;
	if (success && !createTexture(game))
		success = false;

	if (!success)
		cleanUpSDL(game); /* Ensure cleanup if initialization fails */

	return (success);
}

/**
 * cleanUpSDL - Responsible for cleaning up SDL resources
 * @game: Pointer to the Game structure
 * Return: Always void
 */
void cleanUpSDL(Game *game)
{
	if (!game)
		return;

	if (game->texture != NULL)
	{
		SDL_DestroyTexture(game->texture);
		game->texture = NULL;
	}
	if (game->ren != NULL)
	{
		SDL_DestroyRenderer(game->ren);
		game->ren = NULL;
	}
	if (game->win != NULL)
	{
		SDL_DestroyWindow(game->win);
		game->win = NULL;
	}
	SDL_Quit();

	if (game->puzzle != NULL)
	{
		free(game->puzzle);
		game->puzzle = NULL;
	}
}

