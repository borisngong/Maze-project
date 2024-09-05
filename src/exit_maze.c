#include "../dependencies/game.h"

/**
 * exit_maze - Game loop that checks if user quits or
 * toggles fullscreen
 *
 * @game: Represents pointer to the Game struct
 *
 * Return: True if user quits, else False
 */
bool exit_maze(Game *game)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			return (true);
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				return (true);
			case SDLK_q:
				if (game->win != NULL)
				{
					uint32_t windowFlags = SDL_GetWindowFlags(game->win);

					SDL_SetWindowFullscreen(game->win,
						(windowFlags & SDL_WINDOW_FULLSCREEN) ? 0 :
						SDL_WINDOW_FULLSCREEN);
				}
				else
					fprintf(stderr, "Error: game->win is NULL\n");
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
	SDL_Delay(16);
	return (false);
}

