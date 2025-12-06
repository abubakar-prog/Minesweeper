#include "game_logic.h"
#include "game_state.h"
#include "constants.h"
#include <cstdlib>


void initializeGame() {
    resetGameState();
    int minesPlaced = 0;
    bool explosion = false;
    while (minesPlaced < currentMineCount) {
        int x = rand() % currentGridSize;
        int y = rand() % currentGridSize;
        if (grid[x][y] != -1) {
            grid[x][y] = -1;
            minesPlaced++;
        }
    }
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
    if (x < 0 || x >= currentGridSize || y < 0 || y >= currentGridSize) return;
    if (revealed[x][y] || flagged[x][y]) return;
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
    if ((revealedCount == currentGridSize * currentGridSize - currentMineCount)&&(explosion==false)) {
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
