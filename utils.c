#include "gameOfLife.h"

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

void handleLogic(int matrix[M][N], int new_matrix[M][N]) {

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
}
