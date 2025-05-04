#include "raylib.h"
#include <iostream>
#include <array>

const int screenWidth = 600;
const int screenHeight = 600;
const int cellSize = screenWidth / 3;

enum Player { NONE, X, O };

Player board[3][3];
Player currentPlayer = X;
bool gameOver = false;
Player winner = NONE;

void ResetBoard() {
    for (int y = 0; y < 3; y++)
        for (int x = 0; x < 3; x++)
            board[y][x] = NONE;
    currentPlayer = X;
    winner = NONE;
    gameOver = false;
}

Player CheckWinner() {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if (board[i][0] != NONE && board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return board[i][0];
        if (board[0][i] != NONE && board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return board[0][i];
    }

    // Diagonals
    if (board[0][0] != NONE && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return board[0][0];
    if (board[0][2] != NONE && board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return board[0][2];

    return NONE;
}

bool IsBoardFull() {
    for (int y = 0; y < 3; y++)
        for (int x = 0; x < 3; x++)
            if (board[y][x] == NONE)
                return false;
    return true;
}

void DrawBoard() {
    // Draw grid
    for (int i = 1; i < 3; i++) {
        DrawLine(i * cellSize, 0, i * cellSize, screenHeight, BLACK);
        DrawLine(0, i * cellSize, screenWidth, i * cellSize, BLACK);
    }

    // Draw Xs and Os
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            int centerX = x * cellSize + cellSize / 2;
            int centerY = y * cellSize + cellSize / 2;

            if (board[y][x] == X) {
                DrawLine(centerX - 50, centerY - 50, centerX + 50, centerY + 50, RED);
                DrawLine(centerX + 50, centerY - 50, centerX - 50, centerY + 50, RED);
            } else if (board[y][x] == O) {
                DrawCircle(centerX, centerY, 50, BLUE);
            }
        }
    }
}

int main() {
    InitWindow(screenWidth, screenHeight, "Tic Tac Toe - raylib C++");
    SetTargetFPS(60);

    ResetBoard();

    while (!WindowShouldClose()) {
        if (!gameOver && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse = GetMousePosition();
            int col = mouse.x / cellSize;
            int row = mouse.y / cellSize;

            if (board[row][col] == NONE) {
                board[row][col] = currentPlayer;
                winner = CheckWinner();

                if (winner != NONE) {
                    gameOver = true;
                } else if (IsBoardFull()) {
                    gameOver = true;
                } else {
                    currentPlayer = (currentPlayer == X) ? O : X;
                }
            }
        }

        if (IsKeyPressed(KEY_R)) {
            ResetBoard();
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawBoard();

        if (gameOver) {
            const char* msg = nullptr;
            if (winner == X) msg = "Player X wins!";
            else if (winner == O) msg = "Player O wins!";
            else msg = "It's a tie!";
            DrawText(msg, 10, 10, 30, DARKGREEN);
            DrawText("Press R to Restart", 10, 50, 20, GRAY);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
