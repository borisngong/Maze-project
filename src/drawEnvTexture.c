#include "../dependencies/game.h"

/**
 * getEnvPixelPos - Responsible for calculating the environment pixel position
 * based on wall side and ray direction
 * @mapPos: Represents position of the map in the game
 * @rayDir: Represents the direction of the ray
 * @wallX: Represents the X-coordinate of the wall intersection
 * @wallSide: Indicates which side of the wall is being hit (0 for vertical,
 * 1 for horizontal)
 *
 * Return: The calculated environment pixel position
 */
point_t getEnvPixelPos(SDL_Point mapPos, point_t rayDir, double wallX,
int wallSide)
{
	point_t envPixelPos;

	if (wallSide == 0 && rayDir.x > 0)
	{
		envPixelPos.x = mapPos.x;
		envPixelPos.y = mapPos.y + wallX;
	}
	else if (wallSide == 0 && rayDir.x < 0)
	{
		envPixelPos.x = mapPos.x + 1.0;
		envPixelPos.y = mapPos.y + wallX;
	}
	else if (wallSide == 1 && rayDir.y > 0)
	{
		envPixelPos.x = mapPos.x + wallX;
		envPixelPos.y = mapPos.y;
	}
	else
	{
		envPixelPos.x = mapPos.x + wallX;
		envPixelPos.y = mapPos.y + 1.0;
	}

	return (envPixelPos);
}

/**
 * drawEnvTexture - Responsible for rendering the environment texture
 * based on the player's position
 * @game: Represents a pointer to the Game structure
 * @mapPos: Represents the position of the map in the game
 * @rayDir: Represents the direction of the ray
 * @distToWall: Represents the distance from the player to the wall
 * @wallX: Represents the X-coordinate of the wall intersection
 * @drawEnd: Represents the Y-coordinate where drawing ends
 * @col: Represents the column index for the texture
 * @wallSide: Indicates which side of the wall is being hit
 * (0 for vertical, 1 for horizontal)
 *
 * Return: void
 */
void drawEnvTexture(Game *game, SDL_Point mapPos, point_t rayDir,
double distToWall, double wallX, int drawEnd, int col, int wallSide)
{

	point_t envPixelPos = getEnvPixelPos(mapPos, rayDir, wallX, wallSide);
	point_t currentEnvPixel;
	SDL_Point txPos;
	double weight;
	double currentDist;
	int y;

	if (!game)
                return;


	if (drawEnd < 0)
		drawEnd = SCREEN_HEIGHT;

	for (y = drawEnd + 1; y < SCREEN_HEIGHT; y++)
	{
		currentDist = SCREEN_HEIGHT / (2.0 * y - SCREEN_HEIGHT);
		weight = currentDist / distToWall;

		currentEnvPixel.x = weight * envPixelPos.x +
			(1.0 - weight) * game->spot.x;
		currentEnvPixel.y = weight * envPixelPos.y +
			(1.0 - weight) * game->spot.y;

		txPos.x = (int)(currentEnvPixel.x * TEX_WIDTH) % TEX_WIDTH;
		txPos.y = (int)(currentEnvPixel.y * TEX_HEIGHT) % TEX_HEIGHT;

		if (txPos.x < 0 || txPos.x >= TEX_WIDTH ||
		    txPos.y < 0 || txPos.y >= TEX_HEIGHT)
		{
			continue; /* Boundary check */
		}

		if (y >= 0 && y < SCREEN_HEIGHT)
			game->buffer[y][col] = game->tiles[5][txPos.y][txPos.x];
		if (SCREEN_HEIGHT - y >= 0 &&
		    SCREEN_HEIGHT - y < SCREEN_HEIGHT)
			game->buffer[SCREEN_HEIGHT - y][col] =
				game->tiles[4][txPos.y][txPos.x];
	}
}

