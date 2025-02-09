#ifndef GAMEOFLIFE_H_
#define GAMEOFLIFE_H_

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

#define WIDTH 1000
#define HEIGHT 1000
#define CELLWIDTH 10
#define WHITE 0xffffffff
#define GRAY 0x80808080
#define GAME_SPEED 50

#define M HEIGHT / CELLWIDTH
#define N WIDTH / CELLWIDTH

void copyMatrix(int copy[M][N], int matrix[M][N]);
int isValidcell(int row, int col);
int countNeighbors(int rowIndex, int colIndex, int matrix[M][N]);
void printMatrix(int matrix[M][N]);
void handleLogic(int matrix[M][N], int new_matrix[M][N]);


#endif // GAMEOFLIFE_H_
