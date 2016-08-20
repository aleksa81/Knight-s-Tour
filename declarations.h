#ifndef PROT
#define PROT

typedef struct move
{
	int prio;
	int row;
	int column;
}move_t;
#endif


int nextMove(int **matrix, int row, int column, int dim, int *rowNext, int *columnNext, int key);

int knightsTour(int **matrix, int row, int column, int dim, int counter);

void printMatrix(int ** matrix, int dim);

void sortMoves(move_t* moves, int num);

int countMoves(int **matrix, int row, int column, int dim);


