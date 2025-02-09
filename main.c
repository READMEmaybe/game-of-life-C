#include "gameOfLife.h"

bool gameLoopRunning = true;
int matrix[M][N] = { 0 };
bool leftMouseButtonDown = false;
int k = 0;

void drawGrid(SDL_Surface* surface) {
    int i;
    for(i = 0; i < (HEIGHT / CELLWIDTH); i++) {
        SDL_Rect rect = (SDL_Rect) {0,i*CELLWIDTH, WIDTH, 1};
        if (SDL_FillRect(surface, &rect, GRAY))
            printf("Error drawing row grid: %s\n", SDL_GetError());
    }
    for(i = 0; i < (WIDTH / CELLWIDTH); i++) {
        SDL_Rect rect = (SDL_Rect) {i*CELLWIDTH,0, 1, HEIGHT};
        if (SDL_FillRect(surface, &rect, GRAY))
            printf("Error drawing col grid: %s\n", SDL_GetError());
    }
}

void drawMatrix(SDL_Surface* surface, int matrix[M][N]) {
    for(int i = 0; i < M; i++) {
        for(int j = 0; j < N; j++) {
            if(matrix[i][j]) {
                SDL_Rect rect = (SDL_Rect) {j*CELLWIDTH,i*CELLWIDTH,CELLWIDTH,CELLWIDTH};
                if (SDL_FillRect(surface, &rect, WHITE))
                    printf("Error drawing matrix: %s\n", SDL_GetError());
            }
        }
    }
}

void clearSurface(SDL_Surface* surface) {
    SDL_Rect rect = (SDL_Rect) {0, 0, WIDTH, HEIGHT};
    if (SDL_FillRect(surface, &rect, 0x00000000))
        printf("Error Clearing screen: %s\n", SDL_GetError());
}

void handleEvents() {
    SDL_Event event;
//  SDL_WaitEvent(&event);
    while(SDL_PollEvent(&event)) {
        switch (event.type)
        {
            case SDL_QUIT:
                gameLoopRunning = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    leftMouseButtonDown = true;
                        printf("Left mouse pressed at: %d, %d\n", event.button.x / CELLWIDTH, event.button.y / CELLWIDTH);
//                  while(event.button.state == SDL_PRESSED)
//                          printf("pressed\n"); 
                    printf("pressed: %d\n", event.button.state);
                    if(!isValidcell(event.button.y / CELLWIDTH,event.button.x / CELLWIDTH))
                        matrix[event.button.y / CELLWIDTH][event.button.x / CELLWIDTH] = 1;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT)
                    leftMouseButtonDown = false;
                break;
            case SDL_MOUSEMOTION:
//              printf("motion at: %d, %d\n", event.motion.x / CELLWIDTH, event.motion.y / CELLWIDTH);
                if (leftMouseButtonDown) {
                    printf("Left mouse still pressed at: %d, %d\n", event.motion.x / CELLWIDTH, event.motion.y / CELLWIDTH);
                    k = 0;
                    if(!isValidcell(event.motion.y / CELLWIDTH,event.motion.x / CELLWIDTH))
                        matrix[event.motion.y / CELLWIDTH][event.motion.x / CELLWIDTH] = 1;
                }
                break;
        }
    }
}

int processGame(int k) {
    if (k > GAME_SPEED) {
        int new_matrix[M][N] = { 0 };
        handleLogic(matrix, new_matrix);
        copyMatrix(matrix, new_matrix);
        return 0;
    } else
        return k;
}

void updateSurface(SDL_Window* window, SDL_Surface* surface) {

    surface = SDL_GetWindowSurface(window);
    clearSurface(surface);
    drawGrid(surface);
    drawMatrix(surface, matrix);
    if (SDL_UpdateWindowSurface(window))
        printf("Error Updating window: %s\n", SDL_GetError());

}

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow( "Test window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

    SDL_Surface* surface = SDL_GetWindowSurface(window);

    drawGrid(surface);

    SDL_UpdateWindowSurface(window);

    SDL_Event Event;
    while (gameLoopRunning)
    {       
        handleEvents();

        k = processGame(k);

        updateSurface(window, surface);
        k++;
//      SDL_Delay(500);
    }
    SDL_Quit();

    return 0;
}
