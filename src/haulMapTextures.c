#include "../dependencies/game.h"

/**
 * getTextureFilePaths - Adding texture file paths based on the design name
 * @design: name of the design
 * @textureFiles: array to store texture file paths
 * Return: true if the design name is valid, false otherwise
 */
bool getTextureFilePaths(const char *design, const char *textureFiles[])
{
	if (strcmp(design, "visuals/maps/design_1") == 0)
	{
		const char *defaultTextures[TEX_COUNT] = {
			"visuals/textures/walls-used.png",
			"visuals/textures/walls-used.png",
			"visuals/textures/jail.png",
			"visuals/textures/jail.png",
			"visuals/textures/pixel_floor.png",
			"visuals/textures/pixel_ceiling.png"
		};
		memcpy(textureFiles, defaultTextures, sizeof(defaultTextures));
	}
	else if (strcmp(design, "visuals/maps/design_1") == 0)
	{
		const char *altTextures[TEX_COUNT] = {
			"textures/hedge1.png",
			"textures/hedge2.png",
			"textures/gate.png",
			"textures/hedge1.png",
			"textures/sky.png",
			"textures/grass.png"
		};
		memcpy(textureFiles, altTextures, sizeof(altTextures));
	}
	else
	{
		fprintf(stderr, "Unknown design: %s\n", design);
		return (false); /* Exit if design is unknown */
	}

	return (true); /* Indicate success */
}

/**
 * loadTextures - loads textures into SDL surfaces
 * @textureFiles: array of texture file paths
 * @parsedOrigin: array to store loaded textures
 * Return: true if all textures were loaded successfully, false otherwise
 */
bool loadTextures(const char *textureFiles[], SDL_Surface * parsedOrigin[])
{
	int i, n;
	/* Load textures using a loop */
	for (n = 0; n < TEX_COUNT; n++)
	{
		parsedOrigin[n] = IMG_Load(textureFiles[n]);
		if (parsedOrigin[n] == NULL) /* If any texture failed to load */
		{
			/* Print an error message indicating which texture failed */
			fprintf(stderr, "Failed to load texture %d: %s\n", n, IMG_GetError());

			/* Clean up previously loaded textures to prevent memory leaks */
			for (i = 0; i < n; i++)
			{
				SDL_FreeSurface(parsedOrigin[i]);
				parsedOrigin[i] = NULL;
			}

			return (false); /* Indicate failure */
		}
	}

	return (true); /* Indicate success */
}
/**
 * haulMapTextures - loads textures for the default design or the
 * specified design and extracts pixel data
 * @game: pointer to the Game struct
 * @design: name of the design
 * Return: true if all textures were loaded and pixels extracted
 * successfully, false otherwise
 */
bool haulMapTextures(Game *game, char *design)
{
	SDL_Surface * parsedOrigin[TEX_COUNT] = {NULL};
	const char *textureFiles[TEX_COUNT];

	/* Set default design if none is provided */
	if (design == NULL || strcmp(design, "") == 0)
	{
		design = "maps/design_1";
	}

	/* Get texture file paths */
	if (!getTextureFilePaths(design, textureFiles))
	{
		return (false); /* Return false if getting texture file paths failed */
	}

	/* Load textures */
	if (!loadTextures(textureFiles, parsedOrigin))
	{
		return (false); /* Return false if loading textures failed */
	}

	/* Extract pixels */
	extractPixels(game, parsedOrigin);

	return (true); /* Indicate success */
}

