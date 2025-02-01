#include <stdio.h>
#include <unistd.h>

/**
* A live cell dies if it has one or less live neighbors.
* A live cell stays alive if it has two or three neighbors that are alive.
* if a cell has three live neighbors it's born.
* A live cell with cell with more than three neighbors dies.
*/
#define M 20
#define N 20

void copyMatrix(int copy[M][N], int matrix[M][N]) {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++)
			copy[i][j] = matrix[i][j];
	}
}

int isValidcell(int row, int col) {
	if ((row >= 0 && row < M) && (col >= 0 && col < N))
		return 0;
	return 1;
}

int countNeighbors(int rowIndex, int colIndex, int matrix[M][N]) {
	int offset[8][2] = {
		{-1,-1},
		{-1,0},
		{-1,1},
		{0,-1},
		{0,1},
		{1,-1},
		{1,0},
		{1,1}
	};
	int sum = 0, row, col;
	for (int i = 0; i < 8; i++) {
		row = rowIndex + offset[i][0];
		col = colIndex + offset[i][1];
		if (!isValidcell(row, col))
			sum += matrix[row][col];
	}
	return sum;
}

void printMatrix(int matrix[M][N]) {
	for(int i = 0; i < M; i++) {
		for(int j = 0; j < N; j++)
			printf("%d ", matrix[i][j]);
		printf("\n");
	}
	printf("================================================\n");
}

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
		int count = 0;

		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				count = countNeighbors(i, j, matrix);
				if (count < 2 || count > 3) {
					new_matrix[i][j] = 0;
				} else if (count == 2 && matrix[i][j] == 1){
					new_matrix[i][j] = 1;
				} else if (count == 3) {
					new_matrix[i][j] = 1;
				}
			}
		}
		copyMatrix(matrix, new_matrix);
		printMatrix(matrix);
		sleep(1);
	}
	return 0;
}

