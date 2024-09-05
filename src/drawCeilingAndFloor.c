#include "../dependencies/game.h"

/**
 * drawCeilingAndFloor - renders the background ceiling and floor
 * @game: pointer to the Game structure
 * Return: void
 */
void drawCeilingAndFloor(Game *game)
{

	SDL_Rect bgCeiling; /* rectangle for the top half of the window */
	SDL_Rect bgFloor;   /* rectangle for the bottom half of the window */
	int winWidth;       /* current window width */
	int winHeight;      /* current window height */

	if (!game)
                return;


	SDL_GetWindowSize(game->win, &winWidth, &winHeight);

	bgCeiling.x = 0;
	bgCeiling.y = 0;
	bgCeiling.w = winWidth;
	bgCeiling.h = winHeight / 2;

	bgFloor.x = 0;
	bgFloor.y = winHeight / 2;
	bgFloor.w = winWidth;
	bgFloor.h = winHeight / 2;

	/* draw background ceiling */
	SDL_SetRenderDrawColor(game->ren, 0x59, 0x85, 0x94, 0xFF); /* light blue */
	SDL_RenderFillRect(game->ren, &bgCeiling);

	/* draw background floor */
	SDL_SetRenderDrawColor(game->ren, 0x1E, 0x29, 0x34, 0xFF); /* dark blue */
	SDL_RenderFillRect(game->ren, &bgFloor);
}

