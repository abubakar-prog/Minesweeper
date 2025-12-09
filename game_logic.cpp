#include "game_logic.h"
#include "game_state.h"
#include "constants.h"
#include <cstdlib>
using namespace std;
using namespace sf;

// Track if this is the first click
bool isFirstClick = true;

void initializeGame() {
    resetGameState();
    isFirstClick = true;  // Reset first click flag

    // Don't place mines yet - wait for first click
    for (int i = 0; i < currentGridSize; i++) {
        for (int j = 0; j < currentGridSize; j++) {
            grid[i][j] = 0;
        }
    }
}

void placeMines(int safeX, int safeY) {
    // Clear grid first
    for (int i = 0; i < currentGridSize; i++) {
        for (int j = 0; j < currentGridSize; j++) {
            grid[i][j] = 0;
        }
    }

    int minesPlaced = 0;
    while (minesPlaced < currentMineCount) {
        int x = rand() % currentGridSize;
        int y = rand() % currentGridSize;

        // Check if this position is safe (avoid clicked cell and its 8 neighbors)
        bool isSafe = false;
        for (int di = -1; di <= 1; di++) {
            for (int dj = -1; dj <= 1; dj++) {
                if (x == safeX + di && y == safeY + dj) {
                    isSafe = true;
                    break;
                }
            }
            if (isSafe) break;
        }

        // Place mine if position is not safe zone and not already a mine
        if (!isSafe && grid[x][y] != -1) {
            grid[x][y] = -1;
            minesPlaced++;
        }
    }

    // Calculate numbers for all cells
    for (int i = 0; i < currentGridSize; i++) {
        for (int j = 0; j < currentGridSize; j++) {
            if (grid[i][j] == -1) continue;
            int count = 0;
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    int ni = i + di;
                    int nj = j + dj;
                    if (ni >= 0 && ni < currentGridSize && nj >= 0 && nj < currentGridSize) {
                        if (grid[ni][nj] == -1) {
                            count++;
                        }
                    }
                }
            }
            grid[i][j] = count;
        }
    }
}

void revealCell(int x, int y) {
    if (!timerStarted) {
        timerStarted = true;
        gameClock.restart();
    }
    if (firstClick) {
        firstClick = false;
        if (grid[x][y] == -1) {
            moveMineFromCell(x, y);
        }
    }
    if (x < 0 || x >= currentGridSize || y < 0 || y >= currentGridSize) return;
    if (revealed[x][y] || flagged[x][y]) return;

    // If this is the first click, place mines now
    if (isFirstClick) {
        isFirstClick = false;
        placeMines(x, y);
    }

    revealed[x][y] = true;
    cellsRevealed++;

    if (grid[x][y] == -1) {
        gameOver = true;
        explosion = true;
        revealAllMines();
        return;
    }

    if (grid[x][y] == 0) {
        for (int di = -1; di <= 1; di++) {
            for (int dj = -1; dj <= 1; dj++) {
                if (di == 0 && dj == 0) continue;
                revealCell(x + di, y + dj);
            }
        }
    }
}

void toggleFlag(int x, int y) {
    if (x < 0 || x >= currentGridSize || y < 0 || y >= currentGridSize) return;
    if (revealed[x][y]) return;

    flagged[x][y] = !flagged[x][y];
    if (flagged[x][y]) {
        flagsPlaced++;
    }
    else {
        flagsPlaced--;
    }
}

void checkWin() {
    int revealedCount = 0;
    for (int i = 0; i < currentGridSize; i++) {
        for (int j = 0; j < currentGridSize; j++) {
            if (revealed[i][j]) revealedCount++;
        }
    }
    if ((revealedCount == currentGridSize * currentGridSize - currentMineCount) && (explosion == false)) {
        gameWon = true;
        calculateScore();
    }
}

void calculateScore() {
    playerScore = cellsRevealed * 10;
    if (currentDifficulty == DIFFICULTY_MEDIUM) {
        playerScore *= 2;
    }
    else if (currentDifficulty == DIFFICULTY_HARD) {
        playerScore *= 3;
    }
    int correctFlags = 0;
    for (int i = 0; i < currentGridSize; i++) {
        for (int j = 0; j < currentGridSize; j++) {
            if (flagged[i][j] && grid[i][j] == -1) {
                correctFlags++;
            }
        }
    }
    playerScore += correctFlags * 50;
}

void revealAllMines() {
    for (int i = 0; i < currentGridSize; i++) {
        for (int j = 0; j < currentGridSize; j++) {
            if (grid[i][j] == -1) {
                revealed[i][j] = true;
            }
        }
    }
}
void moveMineFromCell(int x, int y) {
    if (grid[x][y] != -1) return;

    grid[x][y] = 0;

    // Find empty cell to place mine
    for (int i = 0; i < currentGridSize; i++) {
        for (int j = 0; j < currentGridSize; j++) {
            if (grid[i][j] != -1 && !(i == x && j == y)) {
                grid[i][j] = -1;

                // Recalculate all adjacent counts
                for (int ii = 0; ii < currentGridSize; ii++) {
                    for (int jj = 0; jj < currentGridSize; jj++) {
                        if (grid[ii][jj] == -1) continue;
                        int count = 0;
                        for (int di = -1; di <= 1; di++) {
                            for (int dj = -1; dj <= 1; dj++) {
                                int ni = ii + di;
                                int nj = jj + dj;
                                if (ni >= 0 && ni < currentGridSize && nj >= 0 && nj < currentGridSize) {
                                    if (grid[ni][nj] == -1) {
                                        count++;
                                    }
                                }
                            }
                        }
                        grid[ii][jj] = count;
                    }
                }
                return;
            }
        }
    }
}
