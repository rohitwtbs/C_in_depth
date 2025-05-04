#include "raylib.h"
#include <stdio.h>

#define CELL_SIZE 100
#define GRID_SIZE 3
#define SCREEN_SIZE (CELL_SIZE * GRID_SIZE)

typedef enum { EMPTY, PLAYER_X, PLAYER_O } Cell;

Cell board[GRID_SIZE][GRID_SIZE] = { 0 };
int currentPlayer = PLAYER_X;
int gameOver = 0;

void DrawBoard() {
    ClearBackground(RAYWHITE);

    // Draw grid lines
    for (int i = 1; i < GRID_SIZE; i++) {
        DrawLine(i * CELL_SIZE, 0, i * CELL_SIZE, SCREEN_SIZE, BLACK);
        DrawLine(0, i * CELL_SIZE, SCREEN_SIZE, i * CELL_SIZE, BLACK);
    }

    // Draw X and O
    for (int y = 0; y < GRID_SIZE; y++) {
        for (int x = 0; x < GRID_SIZE; x++) {
            Vector2 center = { x * CELL_SIZE + CELL_SIZE / 2, y * CELL_SIZE + CELL_SIZE / 2 };
            if (board[y][x] == PLAYER_X) {
                DrawLineEx((Vector2){center.x - 25, center.y - 25}, (Vector2){center.x + 25, center.y + 25}, 5, RED);
                DrawLineEx((Vector2){center.x + 25, center.y - 25}, (Vector2){center.x - 25, center.y + 25}, 5, RED);
            } else if (board[y][x] == PLAYER_O) {
                DrawCircleLines(center.x, center.y, 30, BLUE);
            }
        }
    }

    if (gameOver) {
        const char* winnerText = (gameOver == PLAYER_X) ? "Player X Wins!" :
                                 (gameOver == PLAYER_O) ? "Player O Wins!" : "Draw!";
        DrawText(winnerText, 10, SCREEN_SIZE + 10, 20, DARKGREEN);
        DrawText("Click to restart", 10, SCREEN_SIZE + 40, 20, GRAY);
    }
}

int CheckWin() {
    for (int i = 0; i < GRID_SIZE; i++) {
        if (board[i][0] != EMPTY &&
            board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return board[i][0];
        if (board[0][i] != EMPTY &&
            board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return board[0][i];
    }
    if (board[0][0] != EMPTY &&
        board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return board[0][0];
    if (board[0][2] != EMPTY &&
        board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return board[0][2];

    // Check draw
    int filled = 0;
    for (int y = 0; y < GRID_SIZE; y++)
        for (int x = 0; x < GRID_SIZE; x++)
            if (board[y][x] != EMPTY) filled++;

    return (filled == 9) ? -1 : 0;
}

void ResetGame() {
    for (int y = 0; y < GRID_SIZE; y++)
        for (int x = 0; x < GRID_SIZE; x++)
            board[y][x] = EMPTY;
    currentPlayer = PLAYER_X;
    gameOver = 0;
}

int main(void) {
    InitWindow(SCREEN_SIZE, SCREEN_SIZE + 80, "Tic Tac Toe - raylib");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (gameOver) {
                ResetGame();
            } else {
                Vector2 mouse = GetMousePosition();
                int x = mouse.x / CELL_SIZE;
                int y = mouse.y / CELL_SIZE;

                if (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE && board[y][x] == EMPTY) {
                    board[y][x] = currentPlayer;
                    int winner = CheckWin();
                    if (winner) {
                        gameOver = winner;
                    } else {
                        currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X;
                    }
                }
            }
        }

        BeginDrawing();
        DrawBoard();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
