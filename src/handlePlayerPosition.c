#include "../dependencies/game.h"

/**
 * movePlayer - Respons for handling player movement based on keyboard input
 * @game: Pointer to the Game structure containing game state
 * @puzzle: Pointer to the integer array representing the maze layout
 * @directionX: X direction of movement
 * @directionY: Y direction of movement
 * @modifier: Movement speed modifier
 */
void movePlayer(Game *game, int *puzzle, double directionX,
		double directionY, double modifier)
{
	int newSpotX = (int)(game->spot.x + directionX * modifier);
	int newSpotY = (int)(game->spot.y + directionY * modifier);

	if (newSpotX >= 0 && newSpotX < MAP_WIDTH && newSpotY >= 0 &&
	    newSpotY < MAP_HEIGHT && !puzzle[newSpotX * MAP_WIDTH + newSpotY])
	{
		game->spot.x += directionX * modifier;
		game->spot.y += directionY * modifier;
	}
}

/**
 * rotatePlayer - Handles player rotation based on keyboard input
 * @game: Pointer to the Game structure containing game state
 * @modifier: Rotation speed modifier
 * @direction: Direction of rotation (positive for right, negative for left)
 */
void rotatePlayer(Game *game, double modifier, int direction)
{
	double prevDirX = game->direction.x;
	double prevPlaneX = game->viewPlane.x;

	game->direction.x = game->direction.x * cos(direction * modifier) -
			    game->direction.y * sin(direction * modifier);
	game->direction.y = prevDirX * sin(direction * modifier) +
			    game->direction.y * cos(direction * modifier);

	game->viewPlane.x = game->viewPlane.x * cos(direction * modifier) -
			    game->viewPlane.y * sin(direction * modifier);
	game->viewPlane.y = prevPlaneX * sin(direction * modifier) +
			    game->viewPlane.y * cos(direction * modifier);
}

/**
 * handlePlayerMovement - Handles player movement and rotation based on input
 * @game: Pointer to the Game structure containing game state
 * @puzzle: Pointer to the integer array representing the maze layout
 */
void handlePlayerMovement(Game *game, int *puzzle)
{
	const uint8_t *keyboardState;
	double previousTime;
	double currentTime;
	double moveModifier;
	double rotModifier;

	if (game == NULL || puzzle == NULL)
	{
		return;
	}
	keyboardState = SDL_GetKeyboardState(NULL);
	previousTime = game->time;
	game->time = SDL_GetTicks();
	currentTime = (game->time - previousTime) / 1000.0;
	moveModifier = currentTime * 5.0;
	rotModifier = currentTime * 3.0;
	if (keyboardState[SDL_SCANCODE_W])
	{
		movePlayer(game, puzzle, game->direction.x,
			   game->direction.y, moveModifier);
	}
	if (keyboardState[SDL_SCANCODE_S])
	{
		movePlayer(game, puzzle, -game->direction.x,
			   -game->direction.y, moveModifier);
	}
	if (keyboardState[SDL_SCANCODE_E])
	{
		movePlayer(game, puzzle, game->viewPlane.x,
			   game->viewPlane.y, moveModifier);
	}
	if (keyboardState[SDL_SCANCODE_D])
	{
		rotatePlayer(game, rotModifier, 1);
	}
	if (keyboardState[SDL_SCANCODE_A])
	{
		rotatePlayer(game, rotModifier, -1);
	}
}

