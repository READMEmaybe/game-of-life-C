#include <stdio.h>

/**
* A live cell dies if it has one or less live neighbors.
* A live cell stays alive if it has two or three neighbors that are alive.
* if a cell has three live neighbors it's born.
* A live cell with cell with more than three neighbors dies.
*/

int main() {
	int array[3][3] = {{ 0, 0, 0 }, { 0, 1, 0 }, { 0, 0, 0 }};

	int i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			printf("%d ", array[i][j]);
		}
		printf("\n");
	}
	return 0;
}
