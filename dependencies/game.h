#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 800
#define TEX_WIDTH 64
#define TEX_HEIGHT 64
#define TEX_COUNT 6
#define MAP_WIDTH 25
#define MAP_HEIGHT 24
#define MAP_CHAR_COUNT 1275

/**
 * struct point_s - data structure for XY point coordinates of type double
 * @x: X coordinate
 * @y: Y coordinate
 * Description: struct point
 */
typedef struct point_s
{
	double x;
	double y;
} point_t;

/**
 * struct Game - data structure for the game state
 * @win: Pointer to the SDL window
 * @ren: Pointer to the SDL renderer
 * @texture: Pointer to the SDL texture
 * @tiles: 3D array to store texture tiles
 * @buffer: 2D array to store the screen buffer
 * @spot: Current position of the player
 * @direction: Direction the player is facing
 * @viewPlane: The player's field of view
 * @time: Game time
 * @puzzle: Pointer to the puzzle array (map data)
 * @textured: Boolean to indicate if textures are used
 * @design: Pointer to the design or theme data
 * @quit: Boolean to indicate if the game should quit
 *
 * Description: This structure holds all the information about the game state,
 * including the window, renderer, textures, player position, direction,
 * and various other settings needed to run the game.
 */
typedef struct {
	SDL_Window *win;
	SDL_Renderer *ren;
	SDL_Texture *texture;
	uint32_t tiles[TEX_COUNT][TEX_HEIGHT][TEX_WIDTH];
	uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
	point_t spot;
	point_t direction;
	point_t viewPlane;
	double time;
	int *puzzle;
	bool textured;
	char *design;
	bool quit;
} Game;

extern Game game;

bool exit_maze(Game *game);

int *loadMapsFromFile(char *filename, int **map);
void drawEnvTexture(Game *game, SDL_Point mapPos, point_t rayDir,
	double distToWall, double wallX, int drawEnd, int col, int wallSide);
point_t getEnvPixelPos(SDL_Point mapPos, point_t rayDir, double wallX,
	int wallSide);
bool initializeGameSDL(Game *game);
void updateRenderer(Game *game, bool textured);
void cleanUpSDL(Game *game);
void handlePlayerMovement(Game *game, int *puzzle);

void updatePlayerOrientation(Game *game, int *maze, bool textured);
void drawWallSlices(Game *game, int *maze, SDL_Point map, point_t rayPos,
	point_t rayDir, double distToWall, int x, int side, bool textured);

bool haulMapTextures(Game *game, char *design);
void drawCeilingAndFloor(Game *game);

void extractPixels(Game *game, SDL_Surface * texSrc[]);
bool loadTextures(const char *textureFiles[], SDL_Surface * texSrc[]);
bool getTextureFilePaths(const char *design, const char *textureFiles[]);

int runGameLoop(Game *game, bool textured);
int initializeGame(int argc, char *argv[], Game *game, bool *textured);

void movePlayer(Game *game, int *puzzle, double directionX,
	double directionY, double modifier);
void rotatePlayer(Game *game, double modifier, int direction);

uint32_t getColorFromPixel(uint8_t *pixel, SDL_PixelFormat *format);
void extractTexturePixels(Game *game, SDL_Surface *texture, int index);
void extractPixels(Game *game, SDL_Surface *parsedOrigin[]);

#endif /* GAME_H */

