#include "../dependencies/game.h"
/**
 * loadMapFromFile - Responsible for Loading a 2D map
 * array from a file
 * @filename: Name of the file containing map information
 * @map: Pointer to a pointer to the 2D array of map information
 * Return: Pointer to the 2D array containing map information,
 *         or NULL on failure
 */
int *loadMapFromFile(char *filename, int **map)
{
	FILE *map_file;
	char row_buffer[MAP_WIDTH * 2]; /* Space for map row */
	char *current_token;
	int row_index, column_index;

	map_file = fopen(filename, "r");
	if (map_file == NULL)
		return (NULL);
	*map = malloc(sizeof(int) * MAP_HEIGHT * MAP_WIDTH);
	if (*map == NULL)
	{
		fclose(map_file);
		return (NULL);
	}
	for (row_index = 0; row_index < MAP_HEIGHT; row_index++)
	{
		if (fgets(row_buffer, sizeof(row_buffer), map_file) == NULL)
			break;
		if (strlen(row_buffer) <= 1)
		{
			row_index--;
			continue;
		}
		current_token = strtok(row_buffer, "\n ");
		for (column_index = 0; column_index < MAP_WIDTH &&
			current_token != NULL; column_index++)
		{
			(*map)[row_index * MAP_WIDTH + column_index] =
				atoi(current_token);
			current_token = strtok(NULL, "\n ");
		}
	}
	fclose(map_file);
	return (*map);
}

