#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "declarations.h"

int main()
{
	int n, m, dim;
	clock_t begin, end;
	double time_spent;

	printf("Welcome to Knight's Tour:\n");
	printf("- to exit enter '-1 -1'.\n");
	while (1)
	{
		printf("\n\nTable dimensions (just one number): ");
		scanf("%d", &dim);
		if (dim < 0) break;
		int ** table = malloc(dim * sizeof(int*));
		for (int i = 0; i < dim; i++) table[i] = calloc(dim, sizeof(int));
			
		printf("\n\nStarting coordinates (two numbers): ");
		scanf("%d %d", &m, &n);
		if (m < 0 || m>dim-1 || n < 0 || n>dim-1) break;

		printMatrix(table, dim);
		table[m][n] = 1;

		begin = clock();
		if (knightsTour(table, m, n, dim, 2)) printMatrix(table, dim);
		else printf("failed.\n");
		end = clock();

		time_spent = (double)(end - begin) * 1000 / CLOCKS_PER_SEC; 
		printf("Time spent: %.1lf ms\n", time_spent);
		free(table);
	}
	printf("\n\nThat's all folks!\n");
}