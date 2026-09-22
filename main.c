#include "gameOfLife.h"

bool gameLoopRunning = true;
Uint8 matrix[M][N] = { 0 };
bool leftMouseButtonDown = false;
bool gamePaused = false;
Uint32 k = 0;
Uint32 speeds[12] = { 1, 5, 11, 23, 32, 41, 59, 74, 107, 257, 452, 500 };
Uint32 speed = 6;

void clearMatrix() {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++)
            matrix[i][j] = 0;
    }
}

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

void drawMatrix(SDL_Surface* surface, Uint8 grid[M][N]) {
    for(int i = 0; i < M; i++) {
        for(int j = 0; j < N; j++) {
            if(grid[i][j]) {
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
    while(SDL_PollEvent(&event)) {
        switch (event.type)
        {
            case SDL_QUIT:
                gameLoopRunning = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    leftMouseButtonDown = true;
                    gamePaused = true;
                    if(!isValidcell(event.button.y / CELLWIDTH,event.button.x / CELLWIDTH))
                        matrix[event.button.y / CELLWIDTH][event.button.x / CELLWIDTH] = 1;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT)
                    leftMouseButtonDown = false;
                break;
            case SDL_MOUSEMOTION:
                if (leftMouseButtonDown) {
                    k = 0;
                    if(!isValidcell(event.motion.y / CELLWIDTH,event.motion.x / CELLWIDTH))
                        matrix[event.motion.y / CELLWIDTH][event.motion.x / CELLWIDTH] = 1;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_SPACE:
                        gamePaused = !gamePaused;
                        break;
                    case SDLK_r:
                        clearMatrix();
                        break;
                    case SDLK_UP:
                        speed = (speed < 11) ? speed + 1 : speed;
                        printf("Speed: %d\n", speeds[speed]);
                        break;
                    case SDLK_DOWN:
                        speed = (speed > 0) ? speed - 1 : speed;
                        printf("Speed: %d\n", speeds[speed]);
                        break;
                    default:
                        break;
                }
        }
    }
}

Uint32 processGame(Uint32 ticks) {
    if ((ticks > speeds[speed]) && (!gamePaused)) {
        Uint8 new_matrix[M][N] = { 0 };
        handleLogic(matrix, new_matrix);
        copyMatrix(matrix, new_matrix);
        return 0;
    } else
        return ticks;
}

bool updateSurface(SDL_Window* window) {

    SDL_Surface* surface = SDL_GetWindowSurface(window);
    if (surface == NULL) {
        fprintf(stderr, "Error getting window surface: %s\n", SDL_GetError());
        return false;
    }
    clearSurface(surface);
    drawGrid(surface);
    drawMatrix(surface, matrix);
    if (SDL_UpdateWindowSurface(window) != 0) {
        fprintf(stderr, "Error updating window: %s\n", SDL_GetError());
        return false;
    }

    return true;

}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow( "Test window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    if (window == NULL) {
        fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    while (gameLoopRunning)
    {       
        handleEvents();

        k = processGame(k);

        if (!updateSurface(window))
            gameLoopRunning = false;
        k++;
    }
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
