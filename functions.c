#include <stdio.h>
#include <stdlib.h>
#include "declarations.h"
#define CLOSED_LOOP 
// define CLOSED_LOOP so that the Knight can jump to cell #DIM^2 from the cell #1...

void printMatrix(int ** matrix, int dim)
{
	printf("\n");
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			if ((matrix[i][j] / 10) == 0) printf(" %d ", matrix[i][j]);
			else printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int countMoves(int **matrix, int row, int column, int dim)
{
	int count = 0;
	int rowNextArray[8] = { row - 2, row - 1, row + 1, row + 2, row + 2, row + 1, row - 1, row - 2 };
	int columnNextArray[8] = { column + 1, column + 2, column + 2, column + 1, column - 1, column - 2, column - 2, column - 1 };
	for (int i = 0; i < 8; i++)
	{
#ifndef CLOSED_LOOP
		if (rowNextArray[i] < dim && rowNextArray[i] >= 0 && columnNextArray[i] < dim && columnNextArray[i] >= 0 && matrix[rowNextArray[i]][columnNextArray[i]] == 0) 
		{
			count++;
		}
#endif
#ifdef CLOSED_LOOP
		if (rowNextArray[i] < dim && rowNextArray[i] >= 0 && columnNextArray[i] < dim && columnNextArray[i] >= 0)
		{
			if (matrix[rowNextArray[i]][columnNextArray[i]] == 0) count++;
			else if (matrix[rowNextArray[i]][columnNextArray[i]] == 1) return 10; // all the cells that can lead to the cell #1 will have pririty = 10
		} 
#endif
	}
	return count;
}

void sortMoves(move_t* moves, int num)
{
	move_t temp;
	for (int i = 0; i < num-1; i++)
		for (int j = i + 1; j < num; j++)	
			if (moves[j].prio < moves[i].prio)
			{
				temp = moves[i];
				moves[i] = moves[j];
				moves[j] = temp;
			}
}

int nextMove(int **matrix, int row, int column,int dim, int *rowNext, int *columnNext, int key) // moves are sorted clockwise or counter-clockwise
{
	int rowNextArray[8] = { row - 2, row - 1, row + 1, row + 2, row + 2, row + 1, row - 1, row - 2 };
	int columnNextArray[8] = { column + 1, column + 2, column + 2, column + 1, column - 1, column - 2, column - 2, column - 1 };
	(*rowNext) = rowNextArray[key]; 
	(*columnNext) = columnNextArray[key];
	if ((*rowNext)>dim-1 || (*rowNext) < 0 || (*columnNext)>dim-1 || (*columnNext) < 0) return 0;
	if (matrix[(*rowNext)][(*columnNext)] != 0) return 1;
	return 3;
}

int knightsTour(int **matrix, int row, int column, int dim, int counter)
{
    if (counter<(dim*dim + 1)) // in the last iteration counter will be equal to 2*dim+1
	{
		move_t *moves = calloc(8, sizeof(move_t)); // array of possible moves
		int mNum = 0;
		for (int rowNext, columnNext, i = 0; i < 8; i++) // adding only the possible moves
		{
			if (nextMove(matrix, row, column, dim, &rowNext, &columnNext, i)==3) // if move is possible add it array
			{
				moves[mNum].prio = countMoves(matrix,rowNext,columnNext,dim); // priority is equal to number of possible moves
				moves[mNum].row = rowNext;
				moves[mNum++].column = columnNext;
			}
		}
		sortMoves(moves, mNum); // sorting the array of possible moves

		for (int i = 0; i < mNum; i++) 
		{
			matrix[moves[i].row][moves[i].column] = counter;
			if (knightsTour(matrix, moves[i].row, moves[i].column, dim, counter + 1)) return 1;
			else matrix[moves[i].row][moves[i].column] = 0;
		}
		free(moves);
		return 0; 
	}
#ifdef CLOSED_LOOP
	else if (counter == dim*dim + 1)        
	{
		for (int rowNext, columnNext, i = 0; i < 8; i++)
		{
			if (nextMove(matrix, row, column, dim, &rowNext, &columnNext, i) == 1 && matrix[rowNext][columnNext] == 1) return 1;
		}
		return 0;
	}
#endif
	else return 1;
}
