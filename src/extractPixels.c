#include "../dependencies/game.h"
/**
 * getColorFromPixel - Responsible for retrieving color
 * value from a pixel
 * @pixel: Represents a pointer to the pixel data
 * @format: Represents a pointer to the SDL_PixelFormat
 * structure
 * Return: 32-bit color value in ARGB8888 format
 */
uint32_t getColorFromPixel(uint8_t *pixel, SDL_PixelFormat *format)
{
	uint32_t color = 0;

	switch (format->BytesPerPixel)
	{
	case 1:
		color = *pixel;
		break;
	case 2:
		color = *(uint16_t *)pixel;
		break;
	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			color = pixel[0] << 16 | pixel[1] << 8 | pixel[2];
		else
			color = pixel[0] | pixel[1] << 8 | pixel[2] << 16;
		break;
	case 4:
		color = *(uint32_t *)pixel;
		break;
	}
	return (color);
}

/**
 * extractTexturePixels - Responsible for extracting pixels
 * from a single texture
 * @game: Represents a pointer to the Game structure
 * @texture: Pointer to the SDL_Surface representing the texture
 * @index: Index of the texture in the tiles array
 * Return: Always void
 */
void extractTexturePixels(Game *game, SDL_Surface *texture, int index)
{
	int j, k, flipped_j;
	uint8_t *pixel;
	uint32_t color;
	Uint8 r, g, b;

	SDL_LockSurface(texture);

	for (j = 0; j < TEX_HEIGHT; j++)
	{
		for (k = 0; k < TEX_WIDTH; k++)
		{
			flipped_j = TEX_HEIGHT - 1 - j;

			pixel = (uint8_t *)texture->pixels +
					 flipped_j * texture->pitch +
					 k * texture->format->BytesPerPixel;

			color = getColorFromPixel(pixel, texture->format);

			SDL_GetRGB(color, texture->format, &r, &g, &b);

			game->tiles[index][j][k] = (r << 16) | (g << 8) | b;
		}
	}

	SDL_UnlockSurface(texture);
}

/**
 * extractPixels - Responsible for extracting pixel data
 * from loaded textures
 * @game: Represents a pointer to the Game structure
 * @parsedOrigin: Represnts an array of loaded textures
 * Return: Always void
 */
void extractPixels(Game *game, SDL_Surface *parsedOrigin[])
{
	int i;

	for (i = 0; i < TEX_COUNT; i++)
	{
		extractTexturePixels(game, parsedOrigin[i], i);
		SDL_FreeSurface(parsedOrigin[i]);
		parsedOrigin[i] = NULL;
	}
}

