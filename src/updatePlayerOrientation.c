#include "../dependencies/game.h"

/**
 * calculateRayPosition - Use to calculate the ray position and direction
 * @game: pointer to the Game structure
 * @rayCounter: current ray counter
 * @rayPosition: pointer to the ray position structure
 * @rayDirection: pointer to the ray direction structure
 * @mapPosition: pointer to the map position structure
 * @distanceToNext: pointer to the distance to next structure
 * @stepDirection: pointer to the step direction structure
 * @positionToNext: pointer to the position to next structure
 * Return: void
 */
void calculateRayPosition(Game *game, int rayCounter, point_t *rayPosition,
		point_t *rayDirection, SDL_Point *mapPosition, point_t *distanceToNext,
		SDL_Point *stepDirection, point_t *positionToNext)
{
	double camX;

	camX = 2 * rayCounter / (double)SCREEN_WIDTH - 1;

	rayPosition->x = game->spot.x;
	rayPosition->y = game->spot.y;
	rayDirection->x = game->direction.x + game->viewPlane.x * camX;
	rayDirection->y = game->direction.y + game->viewPlane.y * camX;

	mapPosition->x = (int)rayPosition->x;
	mapPosition->y = (int)rayPosition->y;

	distanceToNext->x = rayDirection->x == 0 ? INFINITY :
		sqrt(1 + pow(rayDirection->y, 2) / pow(rayDirection->x, 2));
	distanceToNext->y = rayDirection->y == 0 ? INFINITY :
		sqrt(1 + pow(rayDirection->x, 2) / pow(rayDirection->y, 2));

	stepDirection->x = rayDirection->x < 0 ? -1 : 1;
	stepDirection->y = rayDirection->y < 0 ? -1 : 1;

	positionToNext->x = rayDirection->x < 0 ? (rayPosition->x - mapPosition->x) *
		distanceToNext->x : (mapPosition->x + 1.0 - rayPosition->x) *
		distanceToNext->x;
	positionToNext->y = rayDirection->y < 0 ? (rayPosition->y - mapPosition->y) *
		distanceToNext->y : (mapPosition->y + 1.0 - rayPosition->y) *
		distanceToNext->y;
}

/**
 * updatePlayerOrientation - casts rays and renders walls, floor, and ceiling
 * @game: pointer to the Game structure
 * @maze: 2D array defining maze map
 * @textured: True if user enabled textures, otherwise False
 * Return: void
 */
void updatePlayerOrientation(Game *game, int *maze, bool textured)
{
	int rayCounter;
	point_t rayPosition, rayDirection, positionToNext, distanceToNext;
	SDL_Point mapPosition, stepDirection;
	int wallHit, hitSide;
	double distanceToWall;

	for (rayCounter = 0; rayCounter < SCREEN_WIDTH; rayCounter++)
	{
		calculateRayPosition(game, rayCounter, &rayPosition, &rayDirection,
			&mapPosition, &distanceToNext, &stepDirection, &positionToNext);

		for (wallHit = 0; wallHit == 0;)
		{
			if (positionToNext.x < positionToNext.y)
			{
				positionToNext.x += distanceToNext.x;
				mapPosition.x += stepDirection.x;
				hitSide = 0;
			}
			else
			{
				positionToNext.y += distanceToNext.y;
				mapPosition.y += stepDirection.y;
				hitSide = 1;
			}

			if (*((int *)maze + mapPosition.x * MAP_WIDTH + mapPosition.y) > 0)
				wallHit = 1;
		}

		distanceToWall = hitSide == 0 ? (mapPosition.x - rayPosition.x +
			(1 - stepDirection.x) / 2) / rayDirection.x :
			(mapPosition.y - rayPosition.y + (1 - stepDirection.y) / 2) /
			rayDirection.y;

		drawWallSlices(game, maze, mapPosition, rayPosition, rayDirection,
			distanceToWall, rayCounter, hitSide, textured);
	}

	updateRenderer(game, textured);
}

