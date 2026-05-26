#include "sandpiles.h"

/**
 * print_sandpile_grid - Prints a 3x3 sandpile grid.
 * @grid: The 3x3 grid to display.
 */
static void print_sandpile_grid(int grid[3][3])
{
	int i, j;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (j)
				printf(" ");
			printf("%d", grid[i][j]);
		}
		printf("\n");
	}
}

/**
 * is_stable - Checks if a 3x3 sandpile is stable.
 * @grid: The grid to inspect.
 *
 * Return: 1 if stable (all cells <= 3), 0 otherwise.
 */
static int is_stable(int grid[3][3])
{
	int i, j;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (grid[i][j] > 3)
				return (0);
		}
	}
	return (1);
}

/**
 * topple_round - Simulates one atomic round of toppling on grid1.
 * @grid1: The working grid being evaluated.
 */
static void topple_round(int grid1[3][3])
{
	int i, j;
	int temp[3][3] = {0};

	/* Capture the exact snapshot state of elements needing to topple */
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (grid1[i][j] > 3)
				temp[i][j] = 1;
		}
	}

	/* Perform simultaneous updates according to snapshot rules */
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (temp[i][j] == 1)
			{
				grid1[i][j] -= 4;
				if (i - 1 >= 0)
					grid1[i - 1][j] += 1;
				if (i + 1 < 3)
					grid1[i + 1][j] += 1;
				if (j - 1 >= 0)
					grid1[i][j - 1] += 1;
				if (j + 1 < 3)
					grid1[i][j + 1] += 1;
			}
		}
	}
}

/**
 * sandpiles_sum - Computes the stable sum of two sandpiles.
 * @grid1: Left 3x3 grid (modified in-place to contain final result).
 * @grid2: Right 3x3 grid.
 */
void sandpiles_sum(int grid1[3][3], int grid2[3][3])
{
	int i, j;

	/* 1. Initial element-wise sum configuration */
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			grid1[i][j] += grid2[i][j];
		}
	}

	/* 2. Process cascading cascades of loops while grid remains unstable */
	while (!is_stable(grid1))
	{
		printf("=\n");
		print_sandpile_grid(grid1);
		topple_round(grid1);
	}
}
