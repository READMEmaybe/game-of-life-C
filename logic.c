#include "gameOfLife.h"

/**
* A live cell dies if it has one or less live neighbors.
* A live cell stays alive if it has two or three neighbors that are alive.
* if a cell has three live neighbors it's born.
* A live cell with cell with more than three neighbors dies.
*/

int main() {
	int matrix[M][N] = { 0 };

	matrix[1][1] = 1;
	matrix[3][1] = 1;
	matrix[3][0] = 1;
	matrix[3][2] = 1;
	matrix[2][2] = 1;
	printMatrix(matrix);
	while (1) {
		int new_matrix[M][N] = { 0 };
		handleLogic(matrix, new_matrix);
		copyMatrix(matrix, new_matrix);
		printMatrix(matrix);
		sleep(1);
	}
	return 0;
}

