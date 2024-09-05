#include "../dependencies/game.h"

/**
 * updateRenderer - Updating renderer with updated buffer / texture
 * @game: pointer to the Game structure
 * @textured: True if user enabled textures, otherwise False
 * Return: void
 */
void updateRenderer(Game *game, bool textured)
{
	int x, y;

	if (!game || !game->buffer || !game->ren)
	{
		return;  /* Check for NULL pointers */
	}

	/* draw buffer to renderer */
	if (textured && game->texture)
	{
		SDL_UpdateTexture(game->texture, NULL, game->buffer,
			SCREEN_WIDTH * 4);
		SDL_RenderClear(game->ren);
		SDL_RenderCopy(game->ren, game->texture, NULL, NULL);

		/* clear buffer */
		for (x = 0; x < SCREEN_WIDTH; x++)
		{
			for (y = 0; y < SCREEN_HEIGHT; y++)
			{
				game->buffer[y][x] = 0;
			}
		}
	}
	/* update screen */
	SDL_RenderPresent(game->ren);
}

