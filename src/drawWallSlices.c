#include "../dependencies/game.h"
/**
 * drawWallSlices - Responsible for drawing slice of wall
 * to buffer
 * @game: pointer to the Game structure
 * @maze: 2D array defining maze map
 * @map: X/Y coordinates of box of maze currently in
 * @rayPos: X/Y coordinates of ray position
 * @rayDir: direction of X/Y coordinates of ray position
 * @distToWall: distance to wall from camera
 * @x: number of ray casted
 * @side: determines whether wall is N/S or E/W
 * @textured: True if user enabled textures, otherwise False
 * Return: Always void
 */
void drawWallSlices(Game *game, int *maze, SDL_Point map, point_t rayPos,
	point_t rayDir, double distToWall, int x, int side, bool textured)
{
	int sliceHeight, drawStart, drawEnd, tileIndex, width, height, y;
	double wallX;
	SDL_Point tex;
	uint32_t color;

	if (!game || !maze)
		return;
	if (!textured)
	{
		SDL_GetWindowSize(game->win, &width, &height);
		sliceHeight = (int)(height / distToWall);
		drawStart = -sliceHeight / 2 + height / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = sliceHeight / 2 + height / 2;
		if (drawEnd >= height)
			drawEnd = height - 1;
		SDL_SetRenderDrawColor(game->ren, side == 0 ? 0xF7 : 0xDE,
			0xF7, 0xF7, 0xFF);
		SDL_RenderDrawLine(game->ren, x, drawStart, x, drawEnd);
	}
	else
	{
		sliceHeight = (int)(SCREEN_HEIGHT / distToWall);
		drawStart = -sliceHeight / 2 + SCREEN_HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = sliceHeight / 2 + SCREEN_HEIGHT / 2;
		if (drawEnd >= SCREEN_HEIGHT)
			drawEnd = SCREEN_HEIGHT - 1;
		wallX = side == 0 ? rayPos.y + distToWall * rayDir.y
			: rayPos.x + distToWall * rayDir.x;
		if (map.x < 0 || map.x >= MAP_WIDTH || map.y < 0 ||
			map.y >= MAP_HEIGHT)
			return;
		tileIndex = *((int *)maze + map.x * MAP_WIDTH + map.y) - 1;
		wallX -= floor(wallX);
		tex.x = (int)(wallX * (double)TEX_WIDTH);
		if (tex.x < 0 || tex.x >= TEX_WIDTH)
			return;
		if ((side == 0 && rayDir.x > 0) || (side == 1 && rayDir.y < 0))
			tex.x = TEX_WIDTH - tex.x - 1;
		for (y = drawStart; y < drawEnd; y++)
		{
			tex.y = ((((y << 1) - SCREEN_HEIGHT + sliceHeight)
				<< (int)log2(TEX_HEIGHT)) / sliceHeight) >> 1;
			if (tex.y < 0 || tex.y >= TEX_HEIGHT)
				continue;
			color = game->tiles[tileIndex][tex.x][tex.y];
			if (side == 1)
				color = (color >> 1) & 0x7F7F7F;
			if (y >= 0 && y < SCREEN_HEIGHT)
				game->buffer[y][x] = color;
		}
		drawEnvTexture(game, map, rayDir, distToWall, wallX,
			drawEnd, x, side);
	}
}

