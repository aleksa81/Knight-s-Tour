#ifndef PROT
#define PROT

typedef struct move
{
	int prio;
	int row;
	int column;
}move_t;
#endif


int nextMove(int **matrix, int vr, int kol,int dim, int *vrNext, int *kolNext, int key);

int knightsTour(int **matrix, int vr, int kol, int dim, int brojac);

void printMatrix(int ** matrix, int dim);

void sortMoves(move_t* moves, int num);

int countMoves(int **matrix, int vr, int kol, int dim);


